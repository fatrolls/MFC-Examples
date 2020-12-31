// Control.cpp -- IOCTL handlers for workitem driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

struct _RANDOM_JUNK :  public _WORK_QUEUE_ITEM
	{
	PDEVICE_EXTENSION DeviceExtension;
	ULONG value;
	PIRP nfyirp;
	};
typedef _RANDOM_JUNK RANDOM_JUNK, *PRANDOM_JUNK;

VOID WorkItemCallback(PRANDOM_JUNK item);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchControl
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
		{						// process request

	case IOCTL_SUBMIT_ITEM:				// code == 0x800
		{						// IOCTL_SUBMIT_ITEM
		if (cbout < sizeof(ULONG))
			status = STATUS_INVALID_PARAMETER;
		else
			status = GenericCacheControlRequest(pdx->pgx, Irp, &pdx->NotifyIrp);

		if (status != STATUS_PENDING)
			break;				// something wrong, so quit

		// Create an executive work item that will complete the notification IRP.
		// Since there's no way to cancel a queued work item, leave the remove
		// lock claim we already have in place

		// Allocate memory for a structure that begins with a work queue item. Use
		// the address of this structure as the context argument for the work item

		PRANDOM_JUNK item = (PRANDOM_JUNK) ExAllocatePool(PagedPool, sizeof(RANDOM_JUNK));
		ExInitializeWorkItem(item, (PWORKER_THREAD_ROUTINE) WorkItemCallback, (PVOID) item);
		item->DeviceExtension = pdx;
		item->value = *(PULONG) Irp->AssociatedIrp.SystemBuffer;
		item->nfyirp = Irp;		// only used in call to IoReleaseRemoveLock
		
		// Queue the work item for delayed execution
		
		ExQueueWorkItem(item, DelayedWorkQueue);
		KdPrint((DRIVERNAME " - Work item queued\n"));

		return STATUS_PENDING;
		}						// IOCTL_SUBMIT_ITEM

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status == STATUS_PENDING ? status : CompleteRequest(Irp, status, info);
	}							// DispatchControl

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID WorkItemCallback(PRANDOM_JUNK item)
	{							// WorkItemCallback
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Work item callback has occurred\n"));
	PDEVICE_EXTENSION pdx = item->DeviceExtension;
	ULONG value = item->value;

	PIRP nfyirp = GenericUncacheControlRequest(pdx->pgx, &pdx->NotifyIrp);

	if (nfyirp)
		{						// complete the notification IRP	
		*(PULONG) nfyirp->AssociatedIrp.SystemBuffer = item->value;
		CompleteRequest(nfyirp, STATUS_SUCCESS, sizeof(ULONG));
		}						// complete the notification IRP

	IoReleaseRemoveLock(&pdx->RemoveLock, item->nfyirp);
	ExFreePool(item);
	}							// WorkItemCallback
