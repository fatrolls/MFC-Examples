// NonStubs.cpp -- Implementations of selected kernel-mode functions
// Copyright (C) 1999 by Walter Oney
// All rights reserved

// Note: Compile without pre-compiled headers

extern "C" {
#include <ntddk.h>
	}

#pragma intrinsic(memset)

#if DBG
	#undef KdPrint
	extern "C" void LCODE__Debug_Printf_Service(char*, ...);
	#define KdPrint(stuff) LCODE__Debug_Printf_Service stuff

	#undef ASSERT
	#define ASSERT(e) if(!(e)){LCODE__Debug_Printf_Service("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}

#endif // DBG

#include "NonStubs.h"

VOID CallbackWrapper(PIO_WORKITEM item);

///////////////////////////////////////////////////////////////////////////////

PIO_WORKITEM AllocateWorkItem(PDEVICE_OBJECT DeviceObject)
	{							// AllocateWorkItem
	PIO_WORKITEM item = (PIO_WORKITEM) ExAllocatePool(NonPagedPool, sizeof(IO_WORKITEM));
	item->DeviceObject = DeviceObject;
	return item;
	}							// AllocateWorkItem

///////////////////////////////////////////////////////////////////////////////

VOID CallbackWrapper(PIO_WORKITEM item)
	{							// CallbackWrapper
	(*item->Routine)(item->DeviceObject, item->Context);
	ObDereferenceObject(item->DeviceObject);
	}							// CallbackWrapper

///////////////////////////////////////////////////////////////////////////////

VOID FreeWorkItem(PIO_WORKITEM item)
	{							// FreeWorkItem
	ExFreePool(item);
	}							// FreeWorkItem

///////////////////////////////////////////////////////////////////////////////

VOID QueueWorkItem(PIO_WORKITEM item, PIO_WORKITEM_ROUTINE Routine, WORK_QUEUE_TYPE QueueType, PVOID Context)
	{							// QueueWorkItem
	ExInitializeWorkItem(item, (PWORKER_THREAD_ROUTINE) CallbackWrapper, item);
	item->Context = Context;
	item->Routine = Routine;
	ObReferenceObject(item->DeviceObject);
	ExQueueWorkItem(item, QueueType);
	}							// QueueWorkItem

///////////////////////////////////////////////////////////////////////////////

NTSTATUS AcquireRemoveLock(PIO_REMOVE_LOCK p, PVOID tag, PCSTR file, ULONG line, ULONG size)
	{							// AcquireRemoveLock
	LONG count = InterlockedIncrement(&p->Common.IoCount);
	ASSERT(count > 0);
	if (p->Common.Removed)
		{						// device is being removed
		if (InterlockedDecrement(&p->Common.IoCount) == 0)
			KeSetEvent(&p->Common.RemoveEvent, IO_NO_INCREMENT, FALSE);
		return STATUS_DELETE_PENDING;
		}						// device is being removed

#ifdef DEBUG

	if (size < sizeof(IO_REMOVE_LOCK))
		return STATUS_SUCCESS;

	ASSERT(p->Dbg.HighWatermark == 0 || count <= p->Dbg.HighWatermark);

	PIO_REMOVE_LOCK_TRACKING_BLOCK t = (PIO_REMOVE_LOCK_TRACKING_BLOCK) ExAllocatePoolWithTag(NonPagedPool,
		sizeof(IO_REMOVE_LOCK_TRACKING_BLOCK), p->Dbg.AllocateTag);
	if (t)
		{						// initialize tracking block
		RtlZeroMemory(t, sizeof(IO_REMOVE_LOCK_TRACKING_BLOCK));
		t->tag = tag;
		t->file = file;
		t->line = line;
		t->locktime = Get_System_Time();
		t->next = p->Dbg.Blocks;
		p->Dbg.Blocks = t;
		}						// initialize tracking block
	else
		InterlockedIncrement(&p->Dbg.LowMemoryCount);

#endif // DEBUG

	return STATUS_SUCCESS;
	}							// AcquireRemoveLock

///////////////////////////////////////////////////////////////////////////////

VOID ReleaseRemoveLock(PIO_REMOVE_LOCK p, PVOID tag, ULONG size)
	{							// ReleaseRemoveLock
#ifdef DEBUG
	if (size >= sizeof(IO_REMOVE_LOCK))
		{						// check debug info
		LONG curtime = Get_System_Time();
		BOOLEAN found = FALSE;
		PIO_REMOVE_LOCK_TRACKING_BLOCK t = p->Dbg.Blocks;
		PIO_REMOVE_LOCK_TRACKING_BLOCK prev = NULL;
		while (t)
			{					// for each tracking block
			if ((LONG) p->Dbg.MaxLockedTicks && (curtime - t->locktime) >= (LONG) p->Dbg.MaxLockedTicks)
				{				// locked too long
				KdPrint(("RemoveLock acquired from file %s, line %d (tag %X) has been locked too long\n", t->file, t->line, t->tag));
				ASSERT(FALSE);
				}				// locked too long
			
			if (!found && t->tag == tag)
				{				// found the tracking block
				found = TRUE;
				PIO_REMOVE_LOCK_TRACKING_BLOCK next = t->next;
				if (prev)
					prev->next = next;
				else
					p->Dbg.Blocks = next;
				ExFreePool(t);
				t = next;
				}				// found the tracking block
			else
				prev = t, t = t->next;
			}					// for each tracking block

		if (!found && InterlockedDecrement(&p->Dbg.LowMemoryCount) < 0)
			{					// should have found it but didn't
			InterlockedIncrement(&p->Dbg.LowMemoryCount);
			KdPrint(("RemoveLock never acquired with tag %X\n", tag));
			ASSERT(FALSE);
			}					// should have found it but didn't
		}						// check debug info
#endif // DEBUG

	LONG count = InterlockedDecrement(&p->Common.IoCount);
	ASSERT(count >= 0);
	if (count == 0)
		{						// device can be removed
		ASSERT(p->Common.Removed);
		KeSetEvent(&p->Common.RemoveEvent, IO_NO_INCREMENT, FALSE);
		}						// device can be removed
	}							// ReleaseRemoveLock

///////////////////////////////////////////////////////////////////////////////

VOID ReleaseRemoveLockAndWait(PIO_REMOVE_LOCK p, PVOID tag, ULONG size)
	{							// ReleaseRemoveLockAndWait
	p->Common.Removed = TRUE;
	InterlockedDecrement(&p->Common.IoCount);	// account for initialization to 1
	ReleaseRemoveLock(p, tag, size);
	KeWaitForSingleObject(&p->Common.RemoveEvent, Executive, KernelMode, FALSE, NULL);

#ifdef DEBUG
	if (size >= sizeof(IO_REMOVE_LOCK))
		ASSERT(p->Dbg.Blocks == NULL);
#endif // DEBUG
	}							// ReleaseRemoveLockAndWait

///////////////////////////////////////////////////////////////////////////////

VOID InitializeRemoveLock(PIO_REMOVE_LOCK p, ULONG tag, ULONG maxminutes, ULONG hwm, ULONG size)
	{							// InitializeRemoveLock
	RtlZeroMemory(p, size);

	p->Common.IoCount = 1;
	KeInitializeEvent(&p->Common.RemoveEvent, NotificationEvent, FALSE);

#ifdef DEBUG
	if (size < sizeof(IO_REMOVE_LOCK))
		return;					// debugging fields not present

	p->Dbg.Signature = 'COLR';		// RLOC
	p->Dbg.HighWatermark = hwm;
	p->Dbg.MaxLockedTicks = (LONGLONG) (maxminutes * 60 * 1000);
	p->Dbg.AllocateTag = tag;
	
#endif // DEBUG
	}							// InitializeRemoveLock

///////////////////////////////////////////////////////////////////////////////

VOID ReuseIrp(PIRP Irp, NTSTATUS status)
	{							// ReuseIrp
	UCHAR flags = Irp->AllocationFlags;
	CCHAR nstack = Irp->StackCount;

	IoInitializeIrp(Irp, IoSizeOfIrp(nstack), nstack);

	Irp->AllocationFlags = flags;
	Irp->IoStatus.Status = status;
	}							// ReuseIrp