// Declarations for s5933dk1 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H

#include "generic.h"
#include "..\sys\s5933.h"

#define DRIVERNAME "S5933DK1"				// for use in messages
#define LDRIVERNAME L"S5933DK1"				// for use in UNICODE string constants

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct tagDEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	IO_REMOVE_LOCK RemoveLock;				// removal control locking structure
	UNICODE_STRING devname;
	PGENERIC_EXTENSION pgx;					// device extension for GENERIC.SYS
	LONG handles;							// # open handles
	PVOID thread;							// worker thread object
	KEVENT evKill;							// set this event to kill worker thread
	KEVENT evWork;							// set this event after queuing a work item
	KSPIN_LOCK QueueLock;					// lock for work item queue
	LIST_ENTRY WorkItems;					// queue of work items
	FAST_MUTEX QueueMutex;					// mutex to protect queue operations
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////

struct _WORKITEM;
typedef BOOLEAN (*WORKITEM_CALLBACK)(PDEVICE_EXTENSION pdx, _WORKITEM* item, PVOID context);

typedef struct _WORKITEM {
	LIST_ENTRY List;						// chaining fields
	PIRP Irp;								// complete this IRP when done
	WORKITEM_CALLBACK callback;				// callback routine
	PVOID context;							// context arg for callback
	} WORKITEM, *PWORKITEM;

///////////////////////////////////////////////////////////////////////////////
// Global functions

VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info);
NTSTATUS ResetDevice(PDEVICE_EXTENSION pdx);
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);
VOID StopDevice(PDEVICE_OBJECT fdo, BOOLEAN oktouch = FALSE);

VOID CleanupWorkItems(PDEVICE_EXTENSION pdx, PFILE_OBJECT FileObject);
VOID InitializeWorkItem(PWORKITEM item, WORKITEM_CALLBACK callback, PVOID context, PIRP Irp);
NTSTATUS QueueWorkItem(PDEVICE_EXTENSION pdx, PWORKITEM item);
NTSTATUS StartWorkerThread(PDEVICE_EXTENSION pdx);
VOID StopWorkerThread(PDEVICE_EXTENSION pdx);

// I/O request handlers

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp);

extern BOOLEAN win98;
extern UNICODE_STRING servkey;

#endif // DRIVER_H
