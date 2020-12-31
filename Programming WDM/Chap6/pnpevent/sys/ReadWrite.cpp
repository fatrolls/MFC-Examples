// Read/Write request processors for pnpevent driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

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

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	return STATUS_SUCCESS;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	}							// StopDevice
