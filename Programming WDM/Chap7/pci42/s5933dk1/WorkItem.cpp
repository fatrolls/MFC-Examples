// WorkItem.cpp -- Routines for managing work items in S5933DK1.SYS driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID OnCancel(PDEVICE_OBJECT fdo, PIRP Irp);
BOOLEAN ProcessWorkItems(PDEVICE_EXTENSION pdx);
VOID WorkerThreadProc(PDEVICE_EXTENSION pdx);

#define POLLING_INTERVAL 10		// 10 ms polling interval

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID CleanupWorkItems(PDEVICE_EXTENSION pdx, PFILE_OBJECT FileObject)
	{							// CleanupWorkItems
	PLIST_ENTRY list;
	PWORKITEM item;

	// Create an empty list that will end up containing the work items we
	// want to cancel

	LIST_ENTRY cancel;
	InitializeListHead(&cancel);

	// Acquire the workitem mutex to make sure that all active work items are
	// sitting on the queue where we can find them.

	ExAcquireFastMutex(&pdx->QueueMutex);

	// Acquire the queue spin lock to prevent interference from QueueWorkItem

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->QueueLock, &oldirql);

	// Find all work items tied to the file object being cleaned up

	for (list = pdx->WorkItems.Flink; list != &pdx->WorkItems; )
		{						// for each work item
		PLIST_ENTRY next = list;

		item = CONTAINING_RECORD(list, WORKITEM, List);
		PIRP Irp = item->Irp;
		PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
		
		if (FileObject == stack->FileObject)
			{					// item for same file object
			IoSetCancelRoutine(Irp, NULL);
			RemoveEntryList(list);
			InsertTailList(&cancel, list);
			}					// item for same file object

		list = next;			// follow chain to next item
		}						// for each work item

	KeReleaseSpinLock(&pdx->QueueLock, oldirql);
	ExReleaseFastMutex(&pdx->QueueMutex);

	// Cancel the selected work items
	
	while (!IsListEmpty(&cancel))
		{						// cancel selected IRPs
		list = RemoveHeadList(&cancel);
		item = CONTAINING_RECORD(list, WORKITEM, List);
		PIRP Irp = item->Irp;
		ExFreePool(item);
		CompleteRequest(Irp, STATUS_CANCELLED, 0);
		}						// cancel selected IRPs
	}							// CleanupWorkItems

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID InitializeWorkItem(PWORKITEM item, WORKITEM_CALLBACK callback, PVOID context, PIRP Irp)
	{							// InitializeWorkItem
	item->Irp = Irp;
	item->callback = callback;
	item->context = context;
	}							// InitializeWorkItem

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID OnCancel(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// OnCancel
	KIRQL oldirql = Irp->CancelIrql;
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	KeAcquireSpinLockAtDpcLevel(&pdx->QueueLock);

	// See if the IRP that's being cancelled is associated with a queued work item.
	// If so, remove the work item from the queue and complete the IRP. Otherwise,
	// do nothing

	PLIST_ENTRY list;
	for (list = pdx->WorkItems.Flink; list != &pdx->WorkItems; list = list->Flink)
		{						// for each queued work item
		PWORKITEM item = CONTAINING_RECORD(list, WORKITEM, List);
		if (Irp == item->Irp)
			{					// cancelling active work item
			RemoveEntryList(list); // remove from active queue
			KeReleaseSpinLock(&pdx->QueueLock, oldirql);
			ExFreePool(item);
			CompleteRequest(Irp, STATUS_CANCELLED, 0);
			return;
			}					// cancelling active work item
		}						// for each queued work item

	KeReleaseSpinLock(&pdx->QueueLock, oldirql);
	}							// OnCancel

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

BOOLEAN ProcessWorkItems(PDEVICE_EXTENSION pdx)
	{							// ProcessWorkItems
	LIST_ENTRY active;			// list of still-active items
	InitializeListHead(&active);

	// Pull each work item off the queue and examine it

	PLIST_ENTRY list;
	while ((list = ExInterlockedRemoveHeadList(&pdx->WorkItems, &pdx->QueueLock)))
		{						// for each work item
		PWORKITEM item = CONTAINING_RECORD(list, WORKITEM, List);
		PIRP Irp = item->Irp;

		// If the IRP associated with this item is marked cancelled, what must
		// have happened is that our cancel routine got called too late to
		// remove the work item from the active queue. In that case, it's our
		// responsibility to complete it

		if (Irp->Cancel)
			{					// item was cancelled
			ExFreePool(item);
			CompleteRequest(Irp, STATUS_CANCELLED, 0);
			continue;			// with "for each work item"
			}					// item was cancelled

		// Call the callback routine for this work item. It returns TRUE if
		// the item needs to remain active. Note that, if the item got cancelled
		// in the very immediate past, we won't pick that fact up until the next
		// poll occurs.

		if ((*item->callback)(pdx, item, item->context))
			{
			InsertTailList(&active, &item->List);
			}
		else
			{					// complete the item
			ExFreePool(item);
			IoCompleteRequest(Irp, IO_NO_INCREMENT);
			}					// complete the item
		}						// for each work item

	// Requeue the active items for the next poll

	if (IsListEmpty(&active))
		return FALSE;			// halt polling loop since no more active items

	while (!IsListEmpty(&active))
		{						// repopulate work item list
		list = RemoveHeadList(&active);
		ExInterlockedInsertTailList(&pdx->WorkItems, list, &pdx->QueueLock);
		}						// repopulate work item list

	return TRUE;				// another poll needed
	}							// ProcessWorkItems

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS QueueWorkItem(PDEVICE_EXTENSION pdx, PWORKITEM item)
	{							// QueueWorkItem
	PIRP Irp = item->Irp;

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->QueueLock, &oldirql);

	// Install a cancel routine for the IRP. If we detect the Cancel flag,
	// our cancel routine may or may not have actually been called for this
	// IRP, but it won't have done anything because the work item won't have
	// been queued yet.

	IoSetCancelRoutine(Irp, OnCancel);
	if (Irp->Cancel)
		{						// IRP has already been cancelled
		IoSetCancelRoutine(Irp, NULL);
		KeReleaseSpinLock(&pdx->QueueLock, oldirql);
		return STATUS_CANCELLED;
		}						// IRP has already been cancelled

	InsertTailList(&pdx->WorkItems, &item->List);

	KeReleaseSpinLock(&pdx->QueueLock, oldirql);

	// Alert the worker thread that a new work item has arrived. Then return
	// STATUS_PENDING to indicate that the item has not yet been processed

	KeSetEvent(&pdx->evWork, EVENT_INCREMENT, FALSE);
	return STATUS_PENDING;
	}							// QueueWorkItem

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartWorkerThread(PDEVICE_EXTENSION pdx)
	{							// StartWorkerThread
	PAGED_CODE();

	NTSTATUS status;
	HANDLE hthread;

	KeClearEvent(&pdx->evKill);

	status = PsCreateSystemThread(&hthread, THREAD_ALL_ACCESS, NULL, NULL, NULL,
		(PKSTART_ROUTINE) WorkerThreadProc, pdx);

	if (!NT_SUCCESS(status))
		return status;

	status = ObReferenceObjectByHandle(hthread, THREAD_ALL_ACCESS, NULL, KernelMode,
		(PVOID*) &pdx->thread, NULL);

	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - ObReferenceObjectByHandle failed - %X\n", status));

	ZwClose(hthread);
	return status;
	}							// StartWorkerThread

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopWorkerThread(PDEVICE_EXTENSION pdx)
	{							// StopWorkerThread
	PAGED_CODE();

	if (!pdx->thread)
		return;

	KeSetEvent(&pdx->evKill, IO_NO_INCREMENT, FALSE);

	// In Win98, we don't dare wait on the thread object (it will cause a crash)
	
	if (!win98)
		KeWaitForSingleObject(pdx->thread, Executive, KernelMode, FALSE, NULL);
	
	ObDereferenceObject(pdx->thread);
	pdx->thread = NULL;
	}							// StopWorkerThread

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID WorkerThreadProc(PDEVICE_EXTENSION pdx)
	{							// WorkerThreadProc
	PAGED_CODE();

	KdPrint((DRIVERNAME " - Starting worker thread\n"));

	NTSTATUS status;

	// Event array for main loop (while waiting for work)

	PVOID mainevents[] = {
		(PVOID) &pdx->evKill,
		(PVOID) &pdx->evWork,
		};
	ASSERT(arraysize(mainevents) <= THREAD_WAIT_OBJECTS);

	// Event array for polling loop

	KTIMER timer;
	KeInitializeTimerEx(&timer, SynchronizationTimer);
	PVOID pollevents[] = {
		(PVOID) &pdx->evKill,
		(PVOID) &timer,
		};
	ASSERT(arraysize(pollevents) <= THREAD_WAIT_OBJECTS);

	// Wait for a work item to arrive or for the kill event to be set

	while (TRUE)
		{						// until told to quit
		status = KeWaitForMultipleObjects(arraysize(mainevents), mainevents,
			WaitAny, Executive, KernelMode, FALSE, NULL, NULL);
		if (!NT_SUCCESS(status))
			break;
		if (status == STATUS_WAIT_0)
			break;				// evKill has been set

		// As long as there are work items in the queue, execute a polling loop
		// in which we repeatedly execute the callback routines for each of the
		// items.

		LARGE_INTEGER duetime = {0};	// causes timer to expire immediately 1 time
		KeSetTimerEx(&timer, duetime, POLLING_INTERVAL, NULL); // start repetitive timer

		while (TRUE)
			{					// until no more work items
			status = KeWaitForMultipleObjects(arraysize(pollevents), pollevents, WaitAny, Executive,
				KernelMode, FALSE, NULL, NULL);
			if (status == STATUS_WAIT_0)
				break;			// kill event set

			KeClearEvent(&pdx->evWork);
			if (!ProcessWorkItems(pdx))
				break;			// no more items in the queue
			}					// until no more work items

		KeCancelTimer(&timer);
		}						// until told to quit

	// Purge any queued work items

	PLIST_ENTRY list;
	while ((list = ExInterlockedRemoveHeadList(&pdx->WorkItems, &pdx->QueueLock)))
		{						// purge queued items
		PWORKITEM item = CONTAINING_RECORD(list, WORKITEM, List);
		PIRP Irp = item->Irp;
		ExFreePool(item);
		CompleteRequest(Irp, STATUS_CANCELLED, 0);
		}						// purge queued items

	KdPrint((DRIVERNAME " - Worker thread exiting\n"));
	PsTerminateSystemThread(STATUS_SUCCESS);
	}							// WorkerThreadProc
