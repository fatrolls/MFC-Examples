// Read/Write request processors for pktdma driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "s5933.h"

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
IO_ALLOCATION_ACTION AdapterControl(PDEVICE_OBJECT fdo, PIRP Irp, PVOID regbase, PDEVICE_EXTENSION pdx);
VOID StartTransfer(PDEVICE_EXTENSION pdx, PHYSICAL_ADDRESS address, BOOLEAN isread);

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

IO_ALLOCATION_ACTION AdapterControl(PDEVICE_OBJECT fdo, PIRP junk, PVOID regbase, PDEVICE_EXTENSION pdx)
	{							// AdapterControl
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	PMDL mdl = Irp->MdlAddress;
	BOOLEAN isread = IoGetCurrentIrpStackLocation(Irp)->MajorFunction == IRP_MJ_READ;
	pdx->regbase = regbase;
	KeFlushIoBuffers(mdl, isread, TRUE);
	PHYSICAL_ADDRESS address = (*pdx->AdapterObject->DmaOperations->MapTransfer)
		(pdx->AdapterObject, mdl, regbase, pdx->vaddr, &pdx->xfer, !isread);

	StartTransfer(pdx, address, isread);

	return DeallocateObjectKeepRegisters;
	}							// AdapterControl

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCleanup
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CLEANUP\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	CleanupRequests(&pdx->dqReadWrite, stack->FileObject, STATUS_CANCELLED);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchCleanup

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCreate
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CREATE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	// Claim the remove lock in Win2K so that removal waits until the
	// handle closes. Don't do this in Win98, however, because this
	// device might be removed by surprise with handles open, whereupon
	// we'll deadlock in HandleRemoveDevice waiting for a close that
	// can never happen because we can't run the user-mode code that
	// would do the close.

	NTSTATUS status;
	if (win98)
		status = STATUS_SUCCESS;
	else 
		status = IoAcquireRemoveLock(&pdx->RemoveLock, stack->FileObject);

	if (NT_SUCCESS(status))
		InterlockedIncrement(&pdx->handles);
	return CompleteRequest(Irp, status, 0);
	}							// DispatchCreate


///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchClose
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CLOSE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	InterlockedDecrement(&pdx->handles);
	
	// Release the remove lock to match the acquisition done in DispatchCreate

	if (!win98)
		IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchReadWrite
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	
	PMDL mdl = Irp->MdlAddress;
	if (!mdl)
		return CompleteRequest(Irp, STATUS_SUCCESS, 0);

	if ((ULONG_PTR) MmGetMdlVirtualAddress(mdl) & fdo->AlignmentRequirement)
		return CompleteRequest(Irp, STATUS_INVALID_PARAMETER, 0);

	IoMarkIrpPending(Irp);
	StartPacket(&pdx->dqReadWrite, fdo, Irp, OnCancelReadWrite);
	return STATUS_PENDING;
	}							// DispatchReadWrite

#pragma LOCKEDCODE

VOID OnCancelReadWrite(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// OnCancelReadWrite
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	CancelRequest(&pdx->dqReadWrite, Irp);
	}							// OnCancelReadWrite

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID DpcForIsr(PKDPC Dpc, PDEVICE_OBJECT fdo, PIRP junk, PDEVICE_EXTENSION pdx)
	{							// DpcForIsr
	NTSTATUS status;
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	BOOLEAN isread = IoGetCurrentIrpStackLocation(Irp)->MajorFunction == IRP_MJ_READ;
	PMDL mdl = Irp->MdlAddress;

	(*pdx->AdapterObject->DmaOperations->FlushAdapterBuffers)
		(pdx->AdapterObject, mdl, pdx->regbase, pdx->vaddr, pdx->xfer, !isread);

	pdx->nbytes -= pdx->xfer;
	pdx->numxfer += pdx->xfer;

	// Fetch accumulated interrupt bits and test for an error

	ULONG intcsr = InterlockedExchange((PLONG) &pdx->intcsr, 0);
	if (intcsr & (INTCSR_MASTER_ABORT | INTCSR_TARGET_ABORT))
		status = STATUS_DATA_ERROR;
	else
		status = AreRequestsBeingAborted(&pdx->dqReadWrite);

	if (pdx->nbytes && NT_SUCCESS(status))
		{						// start next stage of transfer
		pdx->vaddr = (PVOID) ((PUCHAR) pdx->vaddr + pdx->xfer);
		pdx->xfer = pdx->nbytes;
		ULONG nregs = ADDRESS_AND_SIZE_TO_SPAN_PAGES(pdx->vaddr, pdx->nbytes);
		if (nregs > pdx->nMapRegistersAllocated)
			{
			nregs = pdx->nMapRegistersAllocated;
			pdx->xfer = nregs * PAGE_SIZE;
			}
		PHYSICAL_ADDRESS address =(*pdx->AdapterObject->DmaOperations->MapTransfer)
			(pdx->AdapterObject, mdl, pdx->regbase, pdx->vaddr, &pdx->xfer, !isread);

		StartTransfer(pdx, address, isread);
		}						// start next stage of transfer

	else
		{						// request is complete
		ULONG numxfer = pdx->numxfer;
		(*pdx->AdapterObject->DmaOperations->FreeMapRegisters)
			(pdx->AdapterObject, pdx->regbase, pdx->nMapRegistersAllocated);
		StartNextPacket(&pdx->dqReadWrite, fdo);
		CompleteRequest(Irp, status, numxfer);
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		}						// request is complete
	}							// DpcForIsr

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID InterlockedOr(PULONG target, ULONG mask)
	{							// InterlockedOr
#if _X86_
	_asm mov eax, target
	_asm mov ecx, mask
	_asm _emit 0xF0				; lock prefix
	_asm or [eax], ecx
#else // not _X86_
	ULONG prevval = target;
	while (TRUE)
		{
		ULONG newval = InterlockedCompareExchange(target, (prevval | mask), prevval);
		if (newval == prevval)
			break;
		prevval = newval;
		}
#endif // not _X86_
	}							// InterlockedOr

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

BOOLEAN OnInterrupt(PKINTERRUPT InterruptObject, PDEVICE_EXTENSION pdx)
	{							// OnInterrupt

	// Read interrupt control/status register and see if an interrupt is pending.
	// If not, return FALSE immediately.

	ULONG intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));
	if (!(intcsr & INTCSR_INTERRUPT_PENDING))
		return FALSE;

	// Disable bus-mastering

	ULONG mcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + MCSR));
	WRITE_PORT_ULONG((PULONG) (pdx->portbase + MCSR), mcsr & ~(MCSR_WRITE_ENABLE | MCSR_READ_ENABLE));

	intcsr &= ~(INTCSR_WTCI_ENABLE | INTCSR_WTCI_ENABLE); // will take effect when we rewrite INTCSR later on

	// Process pending interrupts. We're expecting an interrupt due to a transfer count
	// going to zero, but we might be getting a master or target abort instead

	while (intcsr & INTCSR_INTERRUPT_PENDING)
		{						// clear all interrupts

		InterlockedOr(&pdx->intcsr, intcsr); // merge new interrupts with old

		// Interrupt flags on the S5933 are cleared by writing a "1" bit to them,
		// so clear all the interrupts we just examined.

		WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR), intcsr);

		// Check for additional interrupts
		
		intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));
		}						// clear all interrupts

	// Request a DPC if necessary

	if (pdx->busy)
		{
		pdx->busy = FALSE;
		IoRequestDpc(pdx->DeviceObject, NULL, pdx);
		}

	return TRUE;
	}							// OnInterrupt

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID ResetDevice(PDEVICE_EXTENSION pdx)
	{							// ResetDevice
	PAGED_CODE();

	// Reset the device

	WRITE_PORT_ULONG((PULONG) (pdx->portbase + MCSR), MCSR_RESET);

	// Reset signals to the S5933 itself don't need to be written back as zero. The
	// add-on function reset flag must, however, be cleared. Delay a short period of
	// time to allow the reset to occur, then write back a zero to the add-on reset bit

	LARGE_INTEGER timeout;
	timeout.QuadPart = -10 * 10000; // i.e., 10 milliseconds

	KeDelayExecutionThread(KernelMode, FALSE, &timeout);
	WRITE_PORT_ULONG((PULONG) (pdx->portbase + MCSR), 0);

	// Clear any pending interrupts by writing 1's to any that are currently asserted

	ULONG intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));
	intcsr &= INTCSR_INTERRUPT_MASK;
	WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR), intcsr);
	}							// ResetDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID SetupDevice(PDEVICE_EXTENSION pdx)
	{							// SetupDevice
	}							// SetupDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// Identify the I/O resources we're supposed to use.
	
	ULONG vector;
	KIRQL irql;
	KINTERRUPT_MODE mode;
	KAFFINITY affinity;
	BOOLEAN irqshare;
	BOOLEAN gotinterrupt = FALSE;

	PHYSICAL_ADDRESS portbase;
	BOOLEAN gotport = FALSE;
	
	if (!translated)
		return STATUS_DEVICE_CONFIGURATION_ERROR;		// no resources assigned??

	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = translated->PartialDescriptors;
	ULONG nres = translated->Count;
	for (ULONG i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		switch (resource->Type)
			{					// switch on resource type

		case CmResourceTypePort:
			portbase = resource->u.Port.Start;
			pdx->nports = resource->u.Port.Length;
			pdx->mappedport = (resource->Flags & CM_RESOURCE_PORT_IO) == 0;
			gotport = TRUE;
			break;
	
		case CmResourceTypeInterrupt:
			irql = (KIRQL) resource->u.Interrupt.Level;
			vector = resource->u.Interrupt.Vector;
			affinity = resource->u.Interrupt.Affinity;
			mode = (resource->Flags == CM_RESOURCE_INTERRUPT_LATCHED)
				? Latched : LevelSensitive;
			irqshare = resource->ShareDisposition == CmResourceShareShared;
			gotinterrupt = TRUE;
			break;

		default:
			KdPrint((DRIVERNAME " - Unexpected I/O resource type %d\n", resource->Type));
			break;
			}					// switch on resource type
		}						// for each resource

	if (!(TRUE
		&& gotport
		&& gotinterrupt
		))
		{
		KdPrint((DRIVERNAME " - Didn't get expected I/O resources\n"));
		return STATUS_DEVICE_CONFIGURATION_ERROR;
		}
		
	// Determine bus type before proceeding, just so we don't have a bunch of cleanup
	// to do if this call fails

	INTERFACE_TYPE bustype;
	ULONG junk;
	status = IoGetDeviceProperty(pdx->Pdo, DevicePropertyLegacyBusType, sizeof(bustype),
		&bustype, &junk);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - IoGetDeviceProperty failed - %X\n", status));
		return status;
		}

	if (pdx->mappedport)
		{						// map port address for RISC platform
		pdx->portbase = (PUCHAR) MmMapIoSpace(portbase, pdx->nports, MmNonCached);
		if (!pdx->mappedport)
			{
			KdPrint((DRIVERNAME " - Unable to map port range %I64X, length %X\n", portbase, pdx->nports));
			return STATUS_INSUFFICIENT_RESOURCES;
			}
		}						// map port address for RISC platform
	else
		pdx->portbase = (PUCHAR) portbase.QuadPart;

	// Configure a DMA adapter object

	DEVICE_DESCRIPTION dd;
	RtlZeroMemory(&dd, sizeof(dd));
	dd.Version = DEVICE_DESCRIPTION_VERSION;
	dd.InterfaceType = bustype;
	dd.MaximumLength = 0x1000;
	dd.Dma32BitAddresses = TRUE;
	dd.Master = TRUE;

	pdx->AdapterObject = IoGetDmaAdapter(pdx->Pdo, &dd, &pdx->nMapRegisters);
	if (!pdx->AdapterObject)
		{						// can't create adapter object
		KdPrint((DRIVERNAME " - Unable to create DMA adapter object\n"));
		if (pdx->portbase && pdx->mappedport)
			MmUnmapIoSpace(pdx->portbase, pdx->nports);
		pdx->portbase = NULL;
		return STATUS_UNSUCCESSFUL;
		}						// can't create adapter object

	ResetDevice(pdx);			// reset the device

	status = IoConnectInterrupt(&pdx->InterruptObject, (PKSERVICE_ROUTINE) OnInterrupt,
		(PVOID) pdx, NULL, vector, irql, irql, mode, irqshare, affinity, FALSE);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - IoConnectInterrupt failed - %X\n", status));
		if (pdx->portbase && pdx->mappedport)
			MmUnmapIoSpace(pdx->portbase, pdx->nports);
		pdx->portbase = NULL;
		if (pdx->AdapterObject)
			(*pdx->AdapterObject->DmaOperations->PutDmaAdapter)
				(pdx->AdapterObject);
		pdx->AdapterObject = NULL;
		return status;
		}

	// Initialize the device

	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) SetupDevice, pdx);

	return STATUS_SUCCESS;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID StartIo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// StartIo
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		{
		CompleteRequest(Irp, status, 0);
		return;
		}
	
	PMDL mdl = Irp->MdlAddress;

	pdx->numxfer = 0;
	pdx->xfer = pdx->nbytes = MmGetMdlByteCount(mdl);
	pdx->vaddr = MmGetMdlVirtualAddress(mdl);

	ULONG nregs = ADDRESS_AND_SIZE_TO_SPAN_PAGES(pdx->vaddr, pdx->nbytes);
	if (nregs > pdx->nMapRegisters)
		{						// staged transfer needed
		nregs = pdx->nMapRegisters;
		pdx->xfer = nregs * PAGE_SIZE - MmGetMdlByteOffset(mdl);
		}						// staged transfer needed
	pdx->nMapRegistersAllocated = nregs; // save for deallocation later

	status = (*pdx->AdapterObject->DmaOperations->AllocateAdapterChannel)
		(pdx->AdapterObject, fdo, nregs, (PDRIVER_CONTROL) AdapterControl, pdx);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - AllocateAdapterChannel failed - %X\n", status));
		StartNextPacket(&pdx->dqReadWrite, fdo);
		CompleteRequest(Irp, status, 0);
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		}
	}							// StartIo

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID StartTransfer(PDEVICE_EXTENSION pdx, PHYSICAL_ADDRESS address, BOOLEAN isread)
	{							// StartTransfer
	ULONG mcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + MCSR));
	ULONG intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));

	// Setup read or write transfer registers. Note that the S5933 calls a transfer
	// from memory to the device a "read"

	if (isread)
		{						// read from device
		mcsr |= MCSR_WRITE_NEED4 | MCSR_WRITE_ENABLE;
		intcsr |= INTCSR_WTCI_ENABLE;
		WRITE_PORT_ULONG((PULONG) (pdx->portbase + MWTC), pdx->xfer);
		WRITE_PORT_ULONG((PULONG) (pdx->portbase + MWAR), address.LowPart);
		}						// read from device
	
	else
		{						// write to device
		mcsr |= MCSR_READ_NEED4 | MCSR_READ_ENABLE;
		intcsr |= INTCSR_RTCI_ENABLE;
		WRITE_PORT_ULONG((PULONG) (pdx->portbase + MRTC), pdx->xfer);
		WRITE_PORT_ULONG((PULONG) (pdx->portbase + MRAR), address.LowPart);
		}						// write to device

	// Write modified INTCSR to enable the appropriate interrupt and MCSR to actually
	// start the transfer

	pdx->busy = TRUE;

	WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR), intcsr);
	WRITE_PORT_ULONG((PULONG) (pdx->portbase + MCSR), mcsr);
	}							// StartTransfer

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	if (pdx->InterruptObject)
		{						// disconnect interrupt
		if (oktouch)
			ResetDevice(pdx);
		IoDisconnectInterrupt(pdx->InterruptObject);
		pdx->InterruptObject = NULL;
		}						// disconnect interrupt

	if (pdx->portbase && pdx->mappedport)
		MmUnmapIoSpace(pdx->portbase, pdx->nports);
	pdx->portbase = NULL;

	if (pdx->AdapterObject)
		(*pdx->AdapterObject->DmaOperations->PutDmaAdapter)
			(pdx->AdapterObject);
	pdx->AdapterObject = NULL;
	}							// StopDevice
