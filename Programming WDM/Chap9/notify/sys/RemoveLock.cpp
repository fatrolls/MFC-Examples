// RemoveLock.cpp -- Portable implementation for remove-lock functions
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID InitializeRemoveLock(PREMOVE_LOCK lock, ULONG tag, ULONG minutes, ULONG maxcount)
	{							// InitializeRemoveLock
	PAGED_CODE();
	KeInitializeEvent(&lock->evRemove, NotificationEvent, FALSE);
	lock->usage = 1;
	lock->removing = FALSE;
	}							// InitializeRemoveLock

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS AcquireRemoveLock(PREMOVE_LOCK lock, PVOID tag)
	{							// AcquireRemoveLock
	LONG usage = InterlockedIncrement(&lock->usage);
	if (lock->removing)
		{						// removal in progress
		if (InterlockedDecrement(&lock->usage) == 0)
			KeSetEvent(&lock->evRemove, 0, FALSE);
		return STATUS_DELETE_PENDING;
		}						// removal in progress
	return STATUS_SUCCESS;
	}							// AcquireRemoveLock

///////////////////////////////////////////////////////////////////////////////

VOID ReleaseRemoveLock(PREMOVE_LOCK lock, PVOID tag)
	{							// ReleaseRemoveLock
	if (InterlockedDecrement(&lock->usage) == 0)
		KeSetEvent(&lock->evRemove, 0, FALSE);
	}							// ReleaseRemoveLock

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID ReleaseRemoveLockAndWait(PREMOVE_LOCK lock, PVOID tag)
	{							// ReleaseRemoveLockAndWait
	PAGED_CODE();
	lock->removing = TRUE;
	ReleaseRemoveLock(lock, tag);
	ReleaseRemoveLock(lock, NULL);
	KeWaitForSingleObject(&lock->evRemove, Executive, KernelMode, FALSE, NULL);
	}							// ReleaseRemoveLockAndWait
