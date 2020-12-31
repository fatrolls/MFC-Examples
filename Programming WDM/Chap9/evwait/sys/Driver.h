// Declarations for evwait driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H
#include <generic.h>

#define DRIVERNAME "EVWAIT"				// for use in messages
#define LDRIVERNAME L"EVWAIT"			// for use in UNICODE strings

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct tagDEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	IO_REMOVE_LOCK RemoveLock;				// removal control locking structure
	UNICODE_STRING devname;					// name of device
	PGENERIC_EXTENSION pgx;					// device extension for GENERIC.SYS
	LONG handles;							// # open handles
	KSPIN_LOCK lockHandles;					// lock for handles list
	LIST_ENTRY hlist;						// anchor of handle object list
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////

typedef struct _HANDLE_OBJECT {
	LONG refcnt;							// reference count
	LIST_ENTRY link;						// linking field for pdx->handles list
	PKEVENT pevent;							// registered event object (if any)
	PFILE_OBJECT FileObject;				// file object for which handle opened
	} HANDLE_OBJECT, *PHANDLE_OBJECT;

///////////////////////////////////////////////////////////////////////////////
// Global functions

VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info);
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);
VOID StopDevice(PDEVICE_OBJECT fdo, BOOLEAN oktouch = FALSE);

VOID CloseHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop);
VOID DeregisterEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop);
PHANDLE_OBJECT FindHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop);
PHANDLE_OBJECT OpenHandle(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop);
BOOLEAN RegisterEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop, HANDLE hEvent, KPROCESSOR_MODE AccessMode);
VOID ReleaseHandle(PHANDLE_OBJECT hop);
VOID SignalEvent(PDEVICE_EXTENSION pdx, PFILE_OBJECT fop);

// I/O request handlers

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp);

extern BOOLEAN win98;
extern UNICODE_STRING servkey;

#endif // DRIVER_H
