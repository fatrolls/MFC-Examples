// DevQueue.cpp -- Custom IRP queuing support
// Copyright (C) 1999 by Walter Oney
// All rights reserved
// @doc

#include "stddcls.h"
#include "driver.h"

///////////////////////////////////////////////////////////////////////////////
// @func Begin rejecting new requests
// @parm Address of queue object
// @parm Status with which to fail new requests, for example:
// @flag STATUS_DELETE_PENDING | Device is being deleted
// @flag STATUS_DEVICE_POWERED_OFF | Device is has been powered off
// @comm Undo the effect of this call by calling AllowRequests

GENERICAPI VOID GENERIC_EXPORT AbortRequests(PDEVQUEUE pdq, NTSTATUS status)
	{							// AbortRequests
	pdq->abortstatus = status;
	CleanupRequests(pdq, NULL, status);
	}							// AbortRequests

///////////////////////////////////////////////////////////////////////////////
// @func Begin accepting new requests
// @parm Address of queue object
// @comm This function undoes the effect of a previous call to AbortRequests

GENERICAPI VOID GENERIC_EXPORT AllowRequests(PDEVQUEUE pdq)
	{							// AllowRequests
	pdq->abortstatus = STATUS_SUCCESS;
	}							// AllowRequests

///////////////////////////////////////////////////////////////////////////////
// @func Determine if new requests are currently being rejected
// @parm Address of queue object
// @rdesc STATUS_SUCCESS if requests aren't being aborted right now, some nonzero
// status code otherwise.

GENERICAPI NTSTATUS GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE pdq)
	{							// AreRequestsBeingAborted
	return pdq->abortstatus;
	}							// AreRequestsBeingAborted

///////////////////////////////////////////////////////////////////////////////
// @func Handle cancellation of an IRP
// @parm Address of queue object
// @parm IRP that's being cancelled
// @comm Call this function from a standard cancel routine while still owning
// the global cancel spin lock.

GENERICAPI VOID GENERIC_EXPORT CancelRequest(PDEVQUEUE pdq, PIRP Irp)
	{							// CancelRequest
	KIRQL oldirql = Irp->CancelIrql;

	// Release the global cancel spin lock as soon as possible

	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	// Acquire our queue-specific queue lock. Note that we stayed at DISPATCH_LEVEL
	// when we released the cancel spin lock

	KeAcquireSpinLockAtDpcLevel(&pdq->lock);

	// (After Peretz & Hanrahan) The IRP is guaranteed to be on *some* queue (maybe a degenerate one),
	// so we unconditionally remove it and complete it.

	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);
	KeReleaseSpinLock(&pdq->lock, oldirql);

	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}							// CancelRequest

///////////////////////////////////////////////////////////////////////////////
// @func Stall queue if not currently busy
// @parm Address of queue object
// @rdesc TRUE if device currently busy. FALSE if device not currently busy, in
// which case this function will also stall the queue to prevent the device from
// becoming busy

GENERICAPI BOOLEAN GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE pdq)
	{							// CheckBusyAndStall
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);
	BOOLEAN busy = pdq->CurrentIrp != NULL;
	if (!busy)
		InterlockedIncrement(&pdq->stallcount);
	KeReleaseSpinLock(&pdq->lock, oldirql);
	return busy;
	}							// CheckBusyAndStall

///////////////////////////////////////////////////////////////////////////////
// @func Complete requests for a given file object
// @parm Address of queue object
// @parm File object for which requests are to be completed. NULL to complete all
// requests on the queue
// @parm Completion status (usually STATUS_CANCELLED)

GENERICAPI VOID GENERIC_EXPORT CleanupRequests(PDEVQUEUE pdq, PFILE_OBJECT fop, NTSTATUS status)
	{							// CleanupRequests
	LIST_ENTRY cancellist;
	InitializeListHead(&cancellist);

	// Create a list of IRPs that belong to the same file object

	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	PLIST_ENTRY first = &pdq->head;
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

		// (After Hanrahan) Set the CancelRoutine pointer to NULL. If it was
		// already NULL, someone is trying to cancel this IRP right now, so just
		// leave it on the queue and let them do it as soon as we release the spin lock.

		if (!IoSetCancelRoutine(Irp, NULL))
			continue;
		RemoveEntryList(current);
		InsertTailList(&cancellist, current);
		}						// for each queued IRP

	// Release the spin lock. We're about to undertake a potentially time-consuming
	// operation that might conceivably result in a deadlock if we keep the lock.

	KeReleaseSpinLock(&pdq->lock, oldirql);

	// Complete the selected requests.

	while (!IsListEmpty(&cancellist))
		{						// cancel selected requests
		next = RemoveHeadList(&cancellist);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		Irp->IoStatus.Status = status;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}						// cancel selected requests
	}							// CleanupRequests

///////////////////////////////////////////////////////////////////////////////
// @func Determine the current IRP for a queue
// @parm Address of queue object
// @rdesc The IRP most recently passed to the StartIo routine, or NULL if the
// device is not busy.
// @comm This function serves the same purpose as dereferencing a device object's
// CurrentIrp pointer in the "standard model"

GENERICAPI PIRP GENERIC_EXPORT GetCurrentIrp(PDEVQUEUE pdq)
	{							// GetCurrentIrp
	return pdq->CurrentIrp;
	}							// GetCurrentIrp

///////////////////////////////////////////////////////////////////////////////
// @func Initialize a device queue
// @parm Address of queue object
// @parm Routine to call to start a request

GENERICAPI VOID GENERIC_EXPORT InitializeQueue(PDEVQUEUE pdq, PDRIVER_STARTIO StartIo)
	{							// InitializeQueue
	InitializeListHead(&pdq->head);
	KeInitializeSpinLock(&pdq->lock);
	pdq->StartIo = StartIo;
	pdq->stallcount = 1;
	pdq->CurrentIrp = NULL;
	KeInitializeEvent(&pdq->evStop, NotificationEvent, FALSE);
	pdq->abortstatus = (NTSTATUS) 0;
	pdq->notify = NULL;
	pdq->notifycontext = 0;
	}							// InitializeQueue

///////////////////////////////////////////////////////////////////////////////
// @func Unstall a queue
// @parm Address of queue object
// @parm Address of associated device object
// @comm This function undoes the effect of a previous call to StallRequests or
// CheckBusyAndStall

GENERICAPI VOID GENERIC_EXPORT RestartRequests(PDEVQUEUE pdq, PDEVICE_OBJECT fdo)
	{							// RestartRequests
	if (InterlockedDecrement(&pdq->stallcount) > 0)
		return;
	ASSERT(pdq->stallcount == 0); // guard against excessive restart calls
	StartNextPacket(pdq, fdo);
	}							// RestartRequests

///////////////////////////////////////////////////////////////////////////////
// @func Stall a queue
// @parm Address of queue object
// @comm This function prevents requests from being sent to the StartIo routine.

GENERICAPI VOID GENERIC_EXPORT StallRequests(PDEVQUEUE pdq)
	{							// StallRequests
	InterlockedIncrement(&pdq->stallcount);
	}							// StallRequests

///////////////////////////////////////////////////////////////////////////////
// @func Stall queue and provide notification when current IRP completes
// @parm Address of queue object
// @parm Address of notification function
// @parm Context value to be used as the only argument to the notify function
// @rdesc Standard status code, as follows:
// @flag STATUS_SUCCESS | Queue is stalled and device was idle, so callback function won't be called.
// @flag STATUS_PENDING | Queue is stalled but device isn't idle yet.
// @flag STATUS_INVALID_DEVICE_REQUEST | A StallRequestsAndNotify is already pending for this queue

GENERICAPI NTSTATUS GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE pdq, PQNOTIFYFUNC notify, PVOID context)
	{							// StallRequestsAndNotify
	NTSTATUS status;
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	if (pdq->notify)
		status = STATUS_INVALID_DEVICE_REQUEST;
	else
		{						// valid request
		InterlockedIncrement(&pdq->stallcount);
		if (pdq->CurrentIrp)
			{					// device is busy
			pdq->notify = notify;
			pdq->notifycontext = context;
			status = STATUS_PENDING;
			}					// device is busy
		else
			status = STATUS_SUCCESS; // device is idle
		}						// valid request

	KeReleaseSpinLock(&pdq->lock, oldirql);
	return status;
	}							// StallRequestsAndNotify

///////////////////////////////////////////////////////////////////////////////
// @func Start the next queued request
// @parm Address of queue object
// @parm Address of associated device object
// @rdesc Address of IRP with which device was previously busy (if any)

GENERICAPI PIRP GENERIC_EXPORT StartNextPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo)
	{							// StartNextPacket
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	// Nullify the current IRP pointer after remembering the current one.
	// We'll return the current IRP pointer as our return value so that
	// a DPC routine has a way to know whether an active request got
	// aborted.

	PIRP CurrentIrp = (PIRP) InterlockedExchangePointer(&pdq->CurrentIrp, NULL);

	// If we just finished processing a request, set the event on which
	// WaitForCurrentIrp may be waiting in some other thread.

	if (CurrentIrp)
		KeSetEvent(&pdq->evStop, 0, FALSE);

	// If someone is waiting for notification that this IRP has finished,
	// we'll provide the notification after we release the spin lock. We shouldn't
	// find the queue unstalled if there is a notification routine in place, by
	// the way.

	PQNOTIFYFUNC notify = pdq->notify;
	PVOID notifycontext = pdq->notifycontext;
	pdq->notify = NULL;

	// Start the next IRP

	while (!pdq->stallcount && !pdq->abortstatus && !IsListEmpty(&pdq->head))
		{						// start next packet
		PLIST_ENTRY next = RemoveHeadList(&pdq->head);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);

		// (After Peretz & Hanrahan in part) Nullify the cancel pointer in this IRP. If it was
		// already NULL, someone is trying to cancel this IRP right now. Reinitialize
		// the link pointers so the cancel routine's call to RemoveEntryList won't
		// do anything harmful and look for another IRP. The cancel routine will
		// take over as soon as we release the spin lock

		if (!IoSetCancelRoutine(Irp, NULL))
			{					// IRP being cancelled right now
			ASSERT(Irp->Cancel);	// else CancelRoutine shouldn't be NULL!
			InitializeListHead(&Irp->Tail.Overlay.ListEntry);
			continue;			// with "start next packet"
			}					// IRP being cancelled right now

		pdq->CurrentIrp = Irp;
		KeReleaseSpinLockFromDpcLevel(&pdq->lock);
		(*pdq->StartIo)(fdo, Irp);
		KeLowerIrql(oldirql);
		return CurrentIrp;
		}						// start next packet

	KeReleaseSpinLock(&pdq->lock, oldirql);

	if (notify)
		(*notify)(notifycontext);

	return CurrentIrp;
	}							// StartNextPacket

///////////////////////////////////////////////////////////////////////////////
// @func Queue or start a new request
// @parm Address of queue object
// @parm Address of associated device object
// @parm IRP to start or queue
// @parm Cancel routine
// @comm If the device is currently idle and the queue isn't stalled, this function
// sends the new IRP to the StartIo routine. Otherwise, it puts the IRP onto the queue.

GENERICAPI VOID GENERIC_EXPORT StartPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo, PIRP Irp, PDRIVER_CANCEL cancel)
	{							// StartPacket
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	ASSERT(Irp->CancelRoutine == NULL); // maybe left over from a higher level?

	// If the device has been removed by surprise, complete IRP immediately. Do not
	// pass GO. Do not collect $200.

	NTSTATUS abortstatus = pdq->abortstatus;
	if (abortstatus)
		{						// aborting all requests now
		KeReleaseSpinLock(&pdq->lock, oldirql);
		Irp->IoStatus.Status = abortstatus;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}						// aborting all requests now

	// If the device is busy with another request, or if the queue has
	// been stalled due to some PnP or power event, just put the new IRP
	// onto the queue and set a cancel routine pointer.

	else if (pdq->CurrentIrp || pdq->stallcount)
		{						// queue this irp

		// (After Peretz) See if this IRP was cancelled before it got to us. If so,
		// make sure either we or the cancel routine completes it

		IoSetCancelRoutine(Irp, cancel);
		if (Irp->Cancel && IoSetCancelRoutine(Irp, NULL))
			{					// IRP has already been cancelled
			KeReleaseSpinLock(&pdq->lock, oldirql);
			Irp->IoStatus.Status = STATUS_CANCELLED;
			IoCompleteRequest(Irp, IO_NO_INCREMENT);
			}					// IRP has already been cancelled
		else
			{					// queue IRP
			InsertTailList(&pdq->head, &Irp->Tail.Overlay.ListEntry);
			KeReleaseSpinLock(&pdq->lock, oldirql);
			}					// queue IRP
		}						// queue this irp

	// If the device is idle and not stalled, pass the IRP to the StartIo
	// routine associated with this queue

	else
		{						// start this irp
		pdq->CurrentIrp = Irp;
		KeReleaseSpinLock(&pdq->lock, DISPATCH_LEVEL);
		(*pdq->StartIo)(fdo, Irp);
		KeLowerIrql(oldirql);
		}						// start this irp
	}							// StartPacket

///////////////////////////////////////////////////////////////////////////////
// @func Wait for the current IRP to finish
// @parm Address of queue object
// @comm If the device is currently busy, this function waits for the IRP to complete

GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIrp(PDEVQUEUE pdq)
	{							// WaitForCurrentIrp

	// First reset the event that StartNextPacket sets each time.

	KeClearEvent(&pdq->evStop);

	// Under protection of our spin lock, check to see if there's a current IRP.
	// Since whoever called us should also have stalled requests, no-one can sneak
	// in after we release the spin lock and start a new request behind our back.

	ASSERT(pdq->stallcount != 0);	// should be stalled now!
	
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);
	BOOLEAN mustwait = pdq->CurrentIrp != NULL;
	KeReleaseSpinLock(&pdq->lock, oldirql);

	if (mustwait)
		KeWaitForSingleObject(&pdq->evStop, Executive, KernelMode, FALSE, NULL);
	}							// WaitForCurrentIrp
