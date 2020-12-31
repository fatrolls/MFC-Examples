// HANDLE.CPP -- Implementation of handle object
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

///////////////////////////////////////////////////////////////////////////////

VOID CloseHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop)
	{							// CloseHandle
	PHANDLE_OBJECT hop = FindHandle(pdx, fop);
	if (!hop)
		return;
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->lockHandles, &oldirql);
	RemoveEntryList(&hop->link);
	KeReleaseSpinLock(&pdx->lockHandles, oldirql);

	ReleaseHandle(hop);
	ReleaseHandle(hop);
	}							// CloseHandle

///////////////////////////////////////////////////////////////////////////////

VOID DeregisterEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop)
	{							// DeregisterEvent
	PHANDLE_OBJECT hop = FindHandle(pdx, fop);
	if (!hop)
		return;
	if (hop->pevent)
		{						// dereference event
		ObDereferenceObject(hop->pevent);
		hop->pevent = NULL;
		}						// dereference vent
	ReleaseHandle(hop);
	}							// DeregisterEvent

///////////////////////////////////////////////////////////////////////////////

PHANDLE_OBJECT FindHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop)
	{							// FindHandle

	// The FsContext and FsContext2	fields of the file object are for use by
	// whoever actually implements the IRP_MJ_CREATE (us, this case). We 
	// save our handle object pointer there in OpenHandle

	PHANDLE_OBJECT hop = (PHANDLE_OBJECT) fop->FsContext;
	if (hop)
		++hop->refcnt;
	return hop;
	}							// FindHandle

///////////////////////////////////////////////////////////////////////////////

PHANDLE_OBJECT OpenHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop)
	{							// OpenHandle
	PHANDLE_OBJECT hop = (PHANDLE_OBJECT) ExAllocatePool(NonPagedPool, sizeof(HANDLE_OBJECT));
	if (!hop)
		return NULL;
	hop->refcnt = 1;
	hop->pevent = NULL;
	hop->FileObject = fop;
	fop->FsContext = (PVOID) hop;
	ExInterlockedInsertTailList(&pdx->hlist, &hop->link, &pdx->lockHandles);
	return hop;
	}							// OpenHandle

///////////////////////////////////////////////////////////////////////////////

BOOLEAN RegisterEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop, HANDLE hEvent, KPROCESSOR_MODE AccessMode)
	{							// RegisterEvent
	PHANDLE_OBJECT hop = FindHandle(pdx, fop);
	if (!hop)
		return FALSE;			// no handle for this file object??
	if (hop->pevent)
		{						// event already registered
		ObDereferenceObject(hop->pevent);
		hop->pevent = NULL;
		}						// event already registered

	NTSTATUS status = ObReferenceObjectByHandle(hEvent, EVENT_MODIFY_STATE, *ExEventObjectType,
		AccessMode, (PVOID*) &hop->pevent, NULL);
	ReleaseHandle(hop);
	if (!NT_SUCCESS(status))
		{
		KdPrint(("EVWAIT - ObReferenceObjectByHandle failed - %X\n", status));
		return FALSE;
		}
	return TRUE;
	}							// RegisterEvent

///////////////////////////////////////////////////////////////////////////////

VOID ReleaseHandle(PHANDLE_OBJECT hop)
	{							// ReleaseHandle
	if (InterlockedDecrement(&hop->refcnt) > 0)
		return;
	if (hop->pevent)
		ObDereferenceObject(hop->pevent);
	ExFreePool(hop);
	}							// ReleaseHandle

///////////////////////////////////////////////////////////////////////////////

VOID SignalEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop)
	{							// SignalEvent
	PHANDLE_OBJECT hop = FindHandle(pdx, fop);
	if (hop && hop->pevent)
		KeSetEvent(hop->pevent, 0, FALSE);
	if (hop)
		ReleaseHandle(hop);
	}							// SignalEvent
