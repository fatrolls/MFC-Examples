// Declarations for pnpmon driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H

#include "ioctls.h"

#define DRIVERNAME "PNPMON"				// for use in messages

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct tagDEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDRIVER_OBJECT DriverObject;			// driver object (for PnP registrations)
	UNICODE_STRING devname;
	LIST_ENTRY registered;					// list of notifications
	LIST_ENTRY events;						// undelivered events
	KSPIN_LOCK eventlock;					// spin lock for guarding event list
	LONG handles;							// # open handles
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////

typedef struct _REG_RECORD {
	GUID Guid;
	PVOID InterfaceNotificationEntry;
	PVOID HandleNotificationEntry;
	PKEVENT Event;
	PDEVICE_EXTENSION DeviceExtension;
	LIST_ENTRY ListEntry;
	PFILE_OBJECT TargetFile;
	LONG WorkItemCount;
	WCHAR LinkName[256];
	BOOLEAN TargetFileReferenced;
	BOOLEAN DeferredRelease;
	} REG_RECORD, *PREG_RECORD;

typedef struct _EVENT_RECORD {
	GETEVENT_PARAMS params;
	LIST_ENTRY ListEntry;
	} EVENT_RECORD, *PEVENT_RECORD;

///////////////////////////////////////////////////////////////////////////////
// Global functions

VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info);

// I/O request handlers

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp);

extern BOOLEAN win98;
extern UNICODE_STRING servkey;

#endif // DRIVER_H
