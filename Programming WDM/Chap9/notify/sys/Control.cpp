// Control.cpp -- IOCTL handlers for notify driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

NTSTATUS CacheControlRequest(PDEVICE_EXTENSION pdx, PIRP Irp, PIRP* pIrp);
VOID OnCancelPendingIoctl(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS OnCompletePendingIoctl(PDEVICE_OBJECT junk, PIRP Irp, PDEVICE_EXTENSION pdx);

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

	case IOCTL_WAIT_NOTIFY:				// code == 0x800
		{						// IOCTL_WAIT_NOTIFY
		if (cbout < sizeof(ULONG))
			status = STATUS_INVALID_PARAMETER;
		else
			status = CacheControlRequest(pdx, Irp, &pdx->NotifyIrp);
		break;
		}						// IOCTL_WAIT_NOTIFY

	case IOCTL_GENERATE_EVENT:				// code == 0x801
		{						// IOCTL_GENERATE_EVENT
		if (cbin < sizeof(ULONG))
			{					// buffer too small
			status = STATUS_INVALID_PARAMETER;
			break;
			}					// buffer too small

		PIRP nfyirp = UncacheControlRequest(pdx, &pdx->NotifyIrp);
		if (nfyirp)
			{					// complete notification IRP
			*(PULONG) nfyirp->AssociatedIrp.SystemBuffer = *(PULONG) Irp->AssociatedIrp.SystemBuffer;
			CompleteRequest(nfyirp, STATUS_SUCCESS, sizeof(ULONG));
			}					// complete notification IRP
		else
			status = STATUS_UNSUCCESSFUL;

		break;
		}						// IOCTL_GENERATE_EVENT

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status == STATUS_PENDING ? status : CompleteRequest(Irp, status, info);
	}							// DispatchControl

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID AbortPendingIoctls(PDEVICE_EXTENSION pdx, NTSTATUS status)
	{							// AbortPendingIoctls
	PAGED_CODE();
	InterlockedExchange(&pdx->IoctlAbortStatus, status);
	CleanupControlRequests(pdx, status, NULL);
	}							// AbortPendingIoctls

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS CacheControlRequest(PDEVICE_EXTENSION pdx, PIRP Irp, PIRP* pIrp)
	{							// CacheControlRequest
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	NTSTATUS status;

	if (*pIrp)
		status = STATUS_UNSUCCESSFUL;	// something already cached here
	else if (pdx->IoctlAbortStatus)
		status = pdx->IoctlAbortStatus;	// rejecting new IRPs for some reason
	else
		{						// try to cache IRP

		// Install a cancel routine and check for this IRP having already been
		// cancelled

		IoSetCancelRoutine(Irp, OnCancelPendingIoctl);
		if (Irp->Cancel && IoSetCancelRoutine(Irp, NULL))
			status = STATUS_CANCELLED;	// already cancelled

		// Put this IRP on our list of pending IOCTLs. Install a completion
		// routine to nullify the cache pointer. Note that AddDevice would have
		// failed if there were no PDO below us, so we know there's at least
		// one free stack location here.

		else
			{					// cache it
			IoMarkIrpPending(Irp);
			status = STATUS_PENDING;

			PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
			stack->Parameters.Others.Argument1 = (PVOID) pIrp;
			IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnCompletePendingIoctl, (PVOID) pdx, TRUE, TRUE, TRUE);
			IoSetNextIrpStackLocation(Irp);	// so our completion routine will get called
			PFILE_OBJECT fop = stack->FileObject;
			stack = IoGetCurrentIrpStackLocation(Irp);
			stack->DeviceObject = pdx->DeviceObject;	// so IoCancelIrp can give us right ptr
			stack->FileObject = fop;	// for cleanup

			*pIrp = Irp;
			InsertTailList(&pdx->PendingIoctlList, &Irp->Tail.Overlay.ListEntry);
			}					// cache it
		}						// try to cache IRP

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);
	return status;
	}							// CacheControlRequest

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID CleanupControlRequests(PDEVICE_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop)
	{							// CleanupControlRequests
	LIST_ENTRY cancellist;
	InitializeListHead(&cancellist);

	// Create a list of IRPs that belong to the same file object

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	PLIST_ENTRY first = &pdx->PendingIoctlList;
	PLIST_ENTRY next;

	for (next = first->Flink; next != first; )
		{						// for each queued IRP
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

		// Follow the chain to the next IRP now (so that the next iteration of
		// the loop is properly setup whether we dequeue this IRP or not)

		PLIST_ENTRY current = next;
		next = next->Flink;

		// Skip this IRP if it's not for the same file object as the
		// current IRP_MJ_CLEANUP.

		if (fop && stack->FileObject != fop)
			continue;			// not for same file object

		// Set the CancelRoutine pointer to NULL and remove the IRP from the
		// queue.

		if (!IoSetCancelRoutine(Irp, NULL))
			continue;			// being cancelled right this instant
		RemoveEntryList(current);
		InsertTailList(&cancellist, current);
		}						// for each queued IRP

	// Release the spin lock. We're about to undertake a potentially time-consuming
	// operation that might conceivably result in a deadlock if we keep the lock.

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	// Complete the selected requests.

	while (!IsListEmpty(&cancellist))
		{						// cancel selected requests
		next = RemoveHeadList(&cancellist);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		Irp->IoStatus.Status = STATUS_CANCELLED;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}						// cancel selected requests
	}							// CleanupControlRequests

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID OnCancelPendingIoctl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// OnCancelPendingIoctl
	KIRQL oldirql = Irp->CancelIrql;
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// Remove the IRP from whatever queue it's on

	KeAcquireSpinLockAtDpcLevel(&pdx->IoctlListLock);
	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);
	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	// Complete the IRP

	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}							// OnCancelPendingIoctl

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnCompletePendingIoctl(PDEVICE_OBJECT junk, PIRP Irp, PDEVICE_EXTENSION pdx)
	{							// OnCompletePendingIoctl
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);
	PIRP* pIrp = (PIRP*) IoGetCurrentIrpStackLocation(Irp)->Parameters.Others.Argument1;
	if (*pIrp == Irp)
		*pIrp = NULL;
	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);
	return STATUS_SUCCESS;
	}							// OnCompletePendingIoctl

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

PIRP UncacheControlRequest(PDEVICE_EXTENSION pdx, PIRP* pIrp)
	{							// UncacheControlRequest
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
	
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	PIRP Irp = (PIRP) InterlockedExchangePointer(pIrp, NULL);

	if (Irp)
		{						// an IRP was cached

		// Clear the cancel pointer for this IRP. Since both we and the
		// completion routine use a spin lock, it cannot happen that this
		// IRP pointer is suddenly invalid but the cache pointer cell
		// wasn't already NULL.

		if (IoSetCancelRoutine(Irp, NULL))
			{
			RemoveEntryList(&Irp->Tail.Overlay.ListEntry);	// N.B.: a macro!!
			}
		else
			Irp = NULL;			// currently being cancelled
		}						// an IRP was cached

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	return Irp;
	}							// UncacheControlRequest
