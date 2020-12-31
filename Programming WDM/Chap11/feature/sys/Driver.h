// Declarations for feature driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H
#include <generic.h>

#define DRIVERNAME "FEATURE"				// for use in messages
#define LDRIVERNAME L"FEATURE"

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
	USB_DEVICE_DESCRIPTOR dd;				// device descriptor
	USBD_CONFIGURATION_HANDLE hconfig;		// selected configuration handle
	PUSB_CONFIGURATION_DESCRIPTOR pcd;		// configuration descriptor
	LANGID langid;							// default language id for strings
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////
// Global functions

VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info);
NTSTATUS SendAwaitUrb(PDEVICE_OBJECT fdo, PURB urb);
VOID AbortPipe(PDEVICE_OBJECT fdo, USBD_PIPE_HANDLE hpipe);
NTSTATUS ResetPipe(PDEVICE_OBJECT fdo, USBD_PIPE_HANDLE hpipe);
VOID ResetDevice(PDEVICE_OBJECT fdo);
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);
VOID StopDevice(PDEVICE_OBJECT fdo, BOOLEAN oktouch = FALSE);

// I/O request handlers

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchInternalControl(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp);

extern BOOLEAN win98;
extern UNICODE_STRING servkey;

#define FEATURE_LED_DISPLAY 42

#endif // DRIVER_H
