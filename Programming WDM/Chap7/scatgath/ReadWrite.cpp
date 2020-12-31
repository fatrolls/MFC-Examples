// Read/Write request processors for scatgath driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID DmaExecutionRoutine(PDEVICE_OBJECT fdo, PIRP Irp, PSCATTER_GATHER_LIST sglist, PDEVICE_EXTENSION pdx);
VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
BOOLEAN StartNextTransfer(PDEVICE_EXTENSION pdx);

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

VOID DmaExecutionRoutine(PDEVICE_OBJECT fdo, PIRP junk, PSCATTER_GATHER_LIST sglist, PDEVICE_EXTENSION pdx)
	{							// DmaExecutionRoutine
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	BOOLEAN isread = IoGetCurrentIrpStackLocation(Irp)->MajorFunction == IRP_MJ_READ;
	pdx->sglist = sglist;		// save for deallocation in DPC routine
	pdx->isg = 0;				// index of current scatter gather element
	pdx->sgdone = 0;			// 0 elements processed so far
	pdx->busy = TRUE;			// indicate device is busy

	// Invoke StartNextTransfer as a synch critical section routine to begin the
	// first stage of a possibly multi-stage transfer

	if (!KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) StartNextTransfer, pdx))
		IoRequestDpc(fdo, NULL, NULL);	// nothing to do
	}							// DmaExecutionRoutine

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID DpcForIsr(PKDPC Dpc, PDEVICE_OBJECT fdo, PIRP junk, PDEVICE_EXTENSION pdx)
	{							// DpcForIsr
	NTSTATUS status;
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	status = Irp->IoStatus.Status;	// get ending status left by ISR
	BOOLEAN isread = IoGetCurrentIrpStackLocation(Irp)->MajorFunction == IRP_MJ_READ;

	// Release the scatter gather list

	(*pdx->AdapterObject->DmaOperations->PutScatterGatherList)
		(pdx->AdapterObject, pdx->sglist, !isread);

	StartNextPacket(&pdx->dqReadWrite, fdo);
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	}							// DpcForIsr

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

BOOLEAN OnInterrupt(PKINTERRUPT InterruptObject, PDEVICE_EXTENSION pdx)
	{							// OnInterrupt
	if (!StartNextTransfer(pdx))
		{
		pdx->busy = FALSE;
		PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
		ASSERT(Irp);
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = pdx->nbytes;
		IoRequestDpc(pdx->DeviceObject, NULL, NULL);
		}
	return TRUE;
	}							// OnInterrupt

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

	// Verify that we got all the resources we were expecting

	if (!(TRUE
		&& gotinterrupt
		&& gotport
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

	// This is a bus-mastering device without scatter/gather capability. Allocate
	// an appropriate adapter object

	DEVICE_DESCRIPTION dd;
	RtlZeroMemory(&dd, sizeof(dd));
	dd.Version = DEVICE_DESCRIPTION_VERSION;
	dd.Master = TRUE;
	dd.InterfaceType = bustype;
	dd.MaximumLength = MAXTRANSFER;		// manifest constant in driver.h
	dd.Dma32BitAddresses = TRUE;

	pdx->AdapterObject = IoGetDmaAdapter(pdx->Pdo, &dd, &pdx->nMapRegisters);
	if (!pdx->AdapterObject)
		{						// unable to creata adapter object
		KdPrint((DRIVERNAME " - Unable to create DMA Adapter Object\n"));
		if (pdx->mappedport)
			MmUnmapIoSpace(pdx->portbase, pdx->nports);
		pdx->portbase = NULL;
		return STATUS_UNSUCCESSFUL;
		}						// unable to create adapter object

	// TODO Temporarily prevent device from interrupt if that's possible.
	// Enable device for interrupts when IoConnectInterrupt returns

	status = IoConnectInterrupt(&pdx->InterruptObject, (PKSERVICE_ROUTINE) OnInterrupt,
		(PVOID) pdx, NULL, vector, irql, irql, mode, irqshare, affinity, FALSE);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - IoConnectInterrupt failed - %X\n", status));
		if (pdx->portbase && pdx->mappedport)
			MmUnmapIoSpace(pdx->portbase, pdx->nports);
		pdx->portbase = NULL;
		return status;
		}

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
	ULONG nbytes = MmGetMdlByteCount(mdl);
	pdx->nbytes = nbytes;
	PVOID vaddr = MmGetMdlVirtualAddress(mdl);
	BOOLEAN isread = stack->MajorFunction == IRP_MJ_READ;

	// Call the adapter's GetScatterGatherList routine to reserve the adapter and the
	// required map registers and to construct a scatter/gather list for the transfer.
	// If the request length requires more map registers than we're allowed to request,
	// GetScatterGatherList will fail with STATUS_INSUFFICIENT_RESOURCES. If so big a
	// request is possible with your device, you can't use the GetScatterGatherList routine
	// to program DMA -- instead, you must use the older method of calling MapTransfer
	// repeatedly to build up your own scatter/gather list.

	status = (*pdx->AdapterObject->DmaOperations->GetScatterGatherList)
		(pdx->AdapterObject, fdo, mdl, vaddr, nbytes,
		(PDRIVER_LIST_CONTROL) DmaExecutionRoutine, pdx, !isread);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - GetScatterGatherList failed - %X\n", status));
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		CompleteRequest(Irp, status, 0);
		StartNextPacket(&pdx->dqReadWrite, fdo);
		}
	}							// StartIo

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

BOOLEAN StartNextTransfer(PDEVICE_EXTENSION pdx)
	{							// StartNextTransfer
	PSCATTER_GATHER_LIST sglist = pdx->sglist;
	ULONG i = pdx->isg += pdx->sgdone;
	ULONG n = sglist->NumberOfElements - i; // # left to do
	if (!n)
		return FALSE;			// request is now finished
	if (n > MAXSG)
		n = MAXSG;				// only do as many as hardware understands
	pdx->sgdone = n;			// save count for next interrupt

	// TODO Program the hardware to transfer data using the address/length pairs
	// sglist->Elements[i].Address and .Length, for the next "n" elements

	return TRUE;
	}							// StartNextTransfer

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	if (pdx->InterruptObject)
		{						// disconnect interrupt

		// TODO prevent device from generating more interrupts if possible

		IoDisconnectInterrupt(pdx->InterruptObject);
		pdx->InterruptObject = NULL;
		}						// disconnect interrupt

	if (pdx->portbase && pdx->mappedport)
		MmUnmapIoSpace(pdx->portbase, pdx->nports);
	pdx->portbase = NULL;
	}							// StopDevice
