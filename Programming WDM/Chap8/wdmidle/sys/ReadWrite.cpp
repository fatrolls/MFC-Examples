// Read/Write request processors for wdmidle driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);

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

	InterlockedIncrement(&pdx->handles);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
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
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchReadWrite
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	GenericMarkDeviceBusy(pdx->pgx);
	NTSTATUS status = GenericWakeupFromIdle(pdx->pgx);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

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

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	NTSTATUS status = STATUS_SUCCESS;
	return status;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID StartIo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// StartIo
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	GenericMarkDeviceBusy(pdx->pgx);
	
	ULONG info = 0;
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (NT_SUCCESS(status))
		{						// pretend to read some data
		ULONG nbytes = stack->Parameters.Read.Length;
		static char* data = "Hello, world!";
		if (nbytes > strlen(data) + 1)
			nbytes = strlen(data) + 1;
		RtlCopyBytes(Irp->AssociatedIrp.SystemBuffer, data, nbytes);
		info = nbytes;
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		}						// pretend to read some data

	CompleteRequest(Irp, status, info);
	StartNextPacket(&pdx->dqReadWrite, fdo);
	}							// StartIo

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	}							// StopDevice
