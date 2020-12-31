// Read/Write request processors for piofake driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
BOOLEAN TransferFirst(PDEVICE_EXTENSION pdx);

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
		{						// open the handle
		if (InterlockedIncrement(&pdx->handles) == 1)
			{					// start timer running
			pdx->timer = -1;
			IoStartTimer(fdo);
			}					// start timer running
		}						// open the handle
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
	if (InterlockedDecrement(&pdx->handles) == 0)
		IoStopTimer(fdo);
	
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

VOID CheckTimer(PDEVICE_EXTENSION pdx)
	{							// CheckTimer
	if (pdx->timer <= 0 || --pdx->timer > 0)
		return;					// not counting or hasn't timed out yet
		
	if (!pdx->busy)
		return;					// no request active

	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	ASSERT(Irp);

	pdx->busy = FALSE;
	Irp->IoStatus.Status = STATUS_IO_TIMEOUT;
	Irp->IoStatus.Information = 0;
	IoRequestDpc(pdx->DeviceObject, NULL, pdx);
	}							// CheckTimer

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
	if (!pdx->busy)
		return FALSE;			// spurious interrupt
		
	PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);
	ASSERT(Irp);

	// If we're aborting new requests (e.g., because of surprise removal
	// or some other reason), terminate the request right now. Note that the
	// hardware (if there were any) might be gone at this point

	NTSTATUS status;
	if (Irp->Cancel)
		status = STATUS_CANCELLED;
	else
		status = AreRequestsBeingAborted(&pdx->dqReadWrite);

	if (!NT_SUCCESS(status))
		{						// halt the request
		pdx->busy = FALSE;
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoRequestDpc(pdx->DeviceObject, NULL, pdx);
		return TRUE;
		}						// halt the request

	// Check for the request being complete

	if (!pdx->nbytes)
		{						// request is complete
		pdx->busy = FALSE;
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = pdx->numxfer;
		pdx->timer = -1;
		IoRequestDpc(pdx->DeviceObject, NULL, pdx);
		return TRUE;
		}						// request is complete

	// Output the next data byte

	WRITE_PORT_UCHAR(pdx->portbase, *pdx->buffer);
	++pdx->buffer;
	--pdx->nbytes;
	++pdx->numxfer;

	// Reset the watchdog timer to allow another 10 seconds to elapse before
	// the next interrupt

	pdx->timer = 10;

	return TRUE;
	}							// OnInterrupt

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID OnTimer(PDEVICE_OBJECT fdo, PDEVICE_EXTENSION pdx)
	{							// OnTimer
	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) CheckTimer, pdx);
	}							// OnTimer

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

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

	// Initialize state for a new transfer.

	pdx->buffer = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
	pdx->nbytes = stack->Parameters.Write.Length;
	pdx->numxfer = 0;

	// Transfer the first byte

	KeSynchronizeExecution(pdx->InterruptObject, (PKSYNCHRONIZE_ROUTINE) TransferFirst, pdx);
	}							// StartIo

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

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

BOOLEAN TransferFirst(PDEVICE_EXTENSION pdx)
	{							// TransferFirst
	pdx->timer = 10;			// start 10-second watchdog timer
	pdx->busy = TRUE;
	return OnInterrupt(NULL, pdx);
	}							// TransferFirst
