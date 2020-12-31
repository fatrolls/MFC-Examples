// Read/Write request processors for pci42 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
VOID TransferFirst(PDEVICE_EXTENSION pdx);

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

VOID DpcForIsr(PKDPC Dpc, PDEVICE_OBJECT fdo, PIRP junk, PDEVICE_EXTENSION pdx)
	{							// DpcForIsr
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	StartNextPacket(&pdx->dqReadWrite, fdo);
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	}							// DpcForIsr

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

BOOLEAN OnInterrupt(PKINTERRUPT InterruptObject, PDEVICE_EXTENSION pdx)
	{							// OnInterrupt

	// Read interrupt control/status register and see if an interrupt is pending.
	// If not, return FALSE immediately.

	ULONG intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));
	if (!(intcsr & INTCSR_INTERRUPT_PENDING))
		return FALSE;

	// See if we're really processing an IRP or if new requests are now being rejected
	// because of some PnP event or another

	BOOLEAN dpc = FALSE;		// assume no DPC needed

	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	NTSTATUS status = -1;

	if (pdx->busy)
		{						// see if we need to terminate this IRP
		ASSERT(Irp);
		
		if (Irp->Cancel)
			status = STATUS_CANCELLED;
		else
			status = AreRequestsBeingAborted(&pdx->dqReadWrite);

		if (!NT_SUCCESS(status))
			dpc = TRUE, pdx->nbytes = 0; // terminate IRP after clearing interrupt
		}						// see if we need to terminate this IRP

	// Process pending interrupts. This particular sample driver is only looking
	// for an incoming mailbox interrupt caused by the addon-simulator putting
	// a data byte into byte-0 of mailbox 1

	while (intcsr & INTCSR_INTERRUPT_PENDING)
		{						// clear all interrupts

		// Process incoming mailbox interrupt by reading a data byte

		if ((intcsr & INTCSR_IMBI) && pdx->nbytes && pdx->busy)
			{					// incoming mailbox interrupt
			*pdx->buffer = READ_PORT_UCHAR(pdx->portbase + IMB1);
			++pdx->buffer;
			++pdx->numxfer;
			if (!--pdx->nbytes)
				{			// request finished
				Irp->IoStatus.Information = pdx->numxfer;
				dpc = TRUE;
				status = STATUS_SUCCESS;
				}			// request finished
			}					// incoming mailbox interrupt

		// Interrupt flags on the S5933 are cleared by writing a "1" bit to them,
		// so clear all the interrupts we just examined.

		WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR), intcsr);

		// Check for additional interrupts
		
		intcsr = READ_PORT_ULONG((PULONG) (pdx->portbase + INTCSR));
		}						// clear all interrupts

	// Request a DPC if necessary

	if (dpc)
		{						// request DPC
		pdx->busy = FALSE;
		ASSERT(Irp);
		ASSERT(status != -1);
		Irp->IoStatus.Status = status;
		IoRequestDpc(pdx->DeviceObject, NULL, pdx);
		}						// request DPC

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

	// Clear any pending interrupts by writing 1's

	WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR), INTCSR_INTERRUPT_MASK);
	}							// ResetDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID SetupDevice(PDEVICE_EXTENSION pdx)
	{							// SetupDevice
	WRITE_PORT_ULONG((PULONG) (pdx->portbase + INTCSR),
		  INTCSR_IMBI_ENABLE									// enable incoming mailbox interrupt
		| (INTCSR_MB1 << INTCSR_IMBI_REG_SELECT_SHIFT)			// namely, on mailbox 1
		| (INTCSR_BYTE0 << INTCSR_IMBI_BYTE_SELECT_SHIFT)		// specifically, when byte 0 fills
		);
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

	ResetDevice(pdx);			// reset the device

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

	// Short-circuit a read for zero bytes

	if (!stack->Parameters.Read.Length)
		{						// nothing to do
		StartNextPacket(&pdx->dqReadWrite, fdo);
		CompleteRequest(Irp, STATUS_SUCCESS, 0);
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return;
		}						// nothing to do

	// Save description of current request in the device extension

	pdx->buffer = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
	pdx->nbytes = stack->Parameters.Read.Length;
	pdx->numxfer = 0;

	// See if an input byte is already available. After this first byte, we wait for
	// an interrupt to tell us the next byte is available.

	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) TransferFirst, pdx);
	}							// StartIo

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
	}							// StopDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID TransferFirst(PDEVICE_EXTENSION pdx)
	{							// TransferFirst

	pdx->busy = TRUE;

	// See if a data byte is already pending in the incoming mailbox

	ULONG mbef = READ_PORT_ULONG((PULONG) (pdx->portbase + MBEF));
	if (!(mbef & MBEF_IN1_0))
		return;					// no pending input byte

	*pdx->buffer = READ_PORT_UCHAR(pdx->portbase + IMB1);
	++pdx->buffer;
	++pdx->numxfer;
	if (--pdx->nbytes != 0)
		return;

	pdx->busy = FALSE;
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	ASSERT(Irp);
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = pdx->numxfer;
	IoRequestDpc(pdx->DeviceObject, NULL, pdx);
	}							// TransferFirst
