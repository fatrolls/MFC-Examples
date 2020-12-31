// Declarations for pci42 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H
#include <generic.h>
#include "s5933.h"

#define DRIVERNAME "PCI42"				// for use in messages
#define LDRIVERNAME L"PCI42"				// for use in UNICODE string constants

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

typedef struct tagDEVICE_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	IO_REMOVE_LOCK RemoveLock;				// removal control locking structure
	UNICODE_STRING devname;
	PGENERIC_EXTENSION pgx;					// device extension for GENERIC.SYS
	DEVQUEUE dqReadWrite;					// queue for reads and writes
	LONG handles;							// # open handles
	PKINTERRUPT InterruptObject;			// address of interrupt object
	PUCHAR portbase;						// I/O port base address
	ULONG nports;							// number of assigned ports

	PUCHAR buffer;							// input data buffer
	ULONG nbytes;							// residual count
	ULONG numxfer;							// cumulative count

	BOOLEAN mappedport;						// true if we mapped port addr in StartDevice
	BOOLEAN busy;							// true while device busy with a request
	} DEVICE_EXTENSION, *PDEVICE_EXTENSION;

///////////////////////////////////////////////////////////////////////////////
// Global functions

VOID RemoveDevice(IN PDEVICE_OBJECT fdo);
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info);
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);
VOID StartIo(PDEVICE_OBJECT fdo, PIRP Irp);
VOID StopDevice(PDEVICE_OBJECT fdo, BOOLEAN oktouch = FALSE);
VOID DpcForIsr(PKDPC Dpc, PDEVICE_OBJECT fdo, PIRP junk, PDEVICE_EXTENSION pdx);

// I/O request handlers

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp);

extern BOOLEAN win98;
extern UNICODE_STRING servkey;

#endif // DRIVER_H
