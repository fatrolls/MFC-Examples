// NonStubs.h -- declarations for NonStubs.cpp
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef NONSTUBS_H
#define NONSTUBS_H

typedef VOID (NTAPI *PIO_WORKITEM_ROUTINE)(PDEVICE_OBJECT DeviceObject, PVOID Context);

struct _IO_WORKITEM : public _WORK_QUEUE_ITEM {
	PDEVICE_OBJECT DeviceObject;
	PIO_WORKITEM_ROUTINE Routine;
	PVOID Context;
	};
typedef struct _IO_WORKITEM IO_WORKITEM, *PIO_WORKITEM;

PIO_WORKITEM AllocateWorkItem(PDEVICE_OBJECT DeviceObject);
VOID FreeWorkItem(PIO_WORKITEM item);
VOID QueueWorkItem(PIO_WORKITEM pIOWorkItem, PIO_WORKITEM_ROUTINE Routine, WORK_QUEUE_TYPE QueueType, PVOID Context);

typedef struct _IO_REMOVE_LOCK_TRACKING_BLOCK {
	struct _IO_REMOVE_LOCK_TRACKING_BLOCK* next;	// chain to next lock block
	PVOID tag;										// tag used at lock time
	LONG locktime;									// system time when lock occurred
	PCSTR file;										// source filename
	ULONG line;										// source line number
	} IO_REMOVE_LOCK_TRACKING_BLOCK, *PIO_REMOVE_LOCK_TRACKING_BLOCK;

LONG __stdcall Get_System_Time();

NTSTATUS AcquireRemoveLock(PIO_REMOVE_LOCK p, PVOID tag, PCSTR file, ULONG line, ULONG size);
VOID ReleaseRemoveLock(PIO_REMOVE_LOCK p, PVOID tag, ULONG size);
VOID ReleaseRemoveLockAndWait(PIO_REMOVE_LOCK p, PVOID tag, ULONG size);
VOID InitializeRemoveLock(PIO_REMOVE_LOCK p, ULONG tag, ULONG maxminutes, ULONG hwm, ULONG size);

VOID ReuseIrp(PIRP Irp, NTSTATUS status);

#endif