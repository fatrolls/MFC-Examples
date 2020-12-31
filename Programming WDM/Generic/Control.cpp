// Control.cpp -- Pending IOCTL support for GENERIC.SYS
// Copyright (C) 1999 by Walter Oney
// All rights reserved
// @doc

#include "stddcls.h"
#include "driver.h"

VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp);
NTSTATUS OnCompletePendingIoctl(PDEVICE_OBJECT junk, PIRP Irp, PGENERIC_EXTENSION pdx);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID AbortPendingIoctls(PGENERIC_EXTENSION pdx, NTSTATUS status)
	{							// AbortPendingIoctls
	PAGED_CODE();
	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return;					// can't be anything to do
	InterlockedExchange(&pdx->IoctlAbortStatus, status);
	GenericCleanupControlRequests(pdx, status, NULL);
	}							// AbortPendingIoctls

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

// @func Cache an asynchronous I/O control request
// @parm Generic.sys device extension
// @parm IRP to cache
// @parm Where to save pointer to cached IRP. The calling driver should not ever access this
// location directly. GENERIC.SYS only accesses it while owning a spin lock that ensures
// thread and multiprocessor safety.
// @rdesc Status code:
// @flag STATUS_PENDING | (Normal return value) IRP has been cached for asynchronous completion
// @flag STATUS_INVALID_DEVICE_REQUEST | GENERIC_PENDING_IOCTLS flag wasn't set in GENERIC_INIT_STRUCT passed to InitializeGenericExtension
// @flag STATUS_INVALID_PARAMETER | IRP doesn't have a free I/O stack location
// @flag (other) | An error of some kind has occurred
// @comm Use this function to cache a pointer to an asynchronous I/O Control request. GENERIC.SYS will
// take care of completing the IRP if it's cancelled or if a PnP or Power event occurs.
// @devnote This routine advances the I/O stack pointer by one location in order to install a
// completion routine. GenericUncacheControlRequest does *not* restore the stack pointer. If you
// plan to pass an uncached IRP down to a lower-level driver, be sure you increase the StackSize
// in your device object by one during your own AddDevice so the IRP will have enough stack.

GENERICAPI NTSTATUS GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION pdx, PIRP Irp, PIRP* pIrp)
	{							// GenericCacheControlRequest
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return STATUS_INVALID_DEVICE_REQUEST;

	// Make sure there's an extra stack location for us to use

	if (Irp->CurrentLocation <= 1)
		return STATUS_INVALID_PARAMETER;	// no stack for us

	// Acquire a global lock that guards pending IOCTL operations for all clients
	// of GENERIC. Our cancel routine needs to use the same lock and has *no* way
	// to find the GENERIC_EXTENSION that belongs to a given device object.

	KIRQL oldirql;
	KeAcquireSpinLock(&IoctlListLock, &oldirql);

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
		// routine to nullify the cache pointer.

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

	KeReleaseSpinLock(&IoctlListLock, oldirql);
	return status;
	}							// GenericCacheControlRequest

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Cleanup cached I/O control requests
// @parm Generic.sys device extension
// @parm Status code to use in completing requests
// @parm File object for which requests are to be completed. NULL if all cached
// requests for the calling driver are to be completed.
// @comm The main purpose of this routine is to help handle an IRP_MJ_CLEANUP when
// the file handle may have been used to submit pending control requests.

GENERICAPI VOID GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop)
	{							// GenericCleanupControlRequests
	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return;					// didn't signup for pending ioctl service!

	LIST_ENTRY cancellist;
	InitializeListHead(&cancellist);

	// Create a list of IRPs that belong to the same file object

	KIRQL oldirql;
	KeAcquireSpinLock(&IoctlListLock, &oldirql);

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

	KeReleaseSpinLock(&IoctlListLock, oldirql);

	// Complete the selected requests.

	while (!IsListEmpty(&cancellist))
		{						// cancel selected requests
		next = RemoveHeadList(&cancellist);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		Irp->IoStatus.Status = STATUS_CANCELLED;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}						// cancel selected requests
	}							// GenericCleanupControlRequests

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

// @func Remove asynchronous I/O control request from the cache
// @parm Generic.sys device extension
// @parm Pointer cell where IRP was cached by GenericCacheControlRequest
// @rdesc Pointer to previously cached IRP, or NULL if none was cached
// @comm The main purpose of this routine is remove the IRP from the cache in preparation for completing it.

GENERICAPI PIRP GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION pdx, PIRP* pIrp)
	{							// GenericUncacheControlRequest
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return NULL;
	
	KIRQL oldirql;
	KeAcquireSpinLock(&IoctlListLock, &oldirql);

	PIRP Irp = (PIRP) InterlockedExchangePointer(pIrp, NULL);

	if (Irp)
		{						// an IRP was cached

		// Clear the cancel pointer for this IRP. Since both we and the
		// completion routine use a spin lock, it cannot happen that this
		// IRP pointer is suddenly invalid but the cache pointer cell
		// wasn't already NULL.

		if (IoSetCancelRoutine(Irp, NULL))
			{					// uncache the IRP
			RemoveEntryList(&Irp->Tail.Overlay.ListEntry);
			}					// uncache the IRP
		else
			Irp = NULL;			// currently being cancelled
		}						// an IRP was cached

	KeReleaseSpinLock(&IoctlListLock, oldirql);
	
	return Irp;
	}							// GenericUncacheControlRequest

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp)
	{							// OnCancelPendingIoctl
	KIRQL oldirql = Irp->CancelIrql;
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	// Remove the IRP from whatever queue it's on

	KeAcquireSpinLockAtDpcLevel(&IoctlListLock);
	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);
	KeReleaseSpinLock(&IoctlListLock, oldirql);

	// Complete the IRP

	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}							// OnCancelPendingIoctl

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnCompletePendingIoctl(PDEVICE_OBJECT junk, PIRP Irp, PGENERIC_EXTENSION pdx)
	{							// OnCompletePendingIoctl
	KIRQL oldirql;
	KeAcquireSpinLock(&IoctlListLock, &oldirql);
	PIRP* pIrp = (PIRP*) IoGetCurrentIrpStackLocation(Irp)->Parameters.Others.Argument1;
	if (*pIrp == Irp)
		*pIrp = NULL;
	KeReleaseSpinLock(&IoctlListLock, oldirql);
	return STATUS_SUCCESS;
	}							// OnCompletePendingIoctl
