// Main program for pnpmon driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject);
VOID DriverUnload(IN PDRIVER_OBJECT fdo);

BOOLEAN IsWin98();
BOOLEAN win98 = FALSE;
UNICODE_STRING servkey;
PDRIVER_OBJECT theDriver;

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	KdPrint((DRIVERNAME " - Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	// Insist that OS support at least the WDM level of the DDK we built with

	if (!IoIsWdmVersionAvailable(1, 0))
		{
		KdPrint((DRIVERNAME " - Expected version of WDM (%d.%2.2d) not available\n", 1, 0));
		return STATUS_UNSUCCESSFUL;
		}

	// See if we're running under Win98 or NT:

	win98 = IsWin98();

#if DBG
	if (win98)
		KdPrint((DRIVERNAME " - Running under Windows 98\n"));
	else
		KdPrint((DRIVERNAME " - Running under NT\n"));
#endif

	// Save the name of the service key

	servkey.Buffer = (PWSTR) ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
	if (!servkey.Buffer)
		{
		KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of service key name\n", RegistryPath->Length + sizeof(WCHAR)));
		return STATUS_INSUFFICIENT_RESOURCES;
		}
	servkey.MaximumLength = RegistryPath->Length + sizeof(WCHAR);
	RtlCopyUnicodeString(&servkey, RegistryPath);

	theDriver = DriverObject;		// for unloading under Win98

	// Initialize function pointers

	DriverObject->DriverUnload = DriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;

	// Create a device object to allow an associated application to open a handle
	// in order to send us IOCTL requests

	NTSTATUS status = AddDevice(DriverObject);
	
	return status;
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
	{							// DriverUnload
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
	
	while (DriverObject->DeviceObject)
		RemoveDevice(DriverObject->DeviceObject);

	RtlFreeUnicodeString(&servkey);
	}							// DriverUnload

///////////////////////////////////////////////////////////////////////////////

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject)
	{							// AddDevice
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX\n", DriverObject));

	NTSTATUS status;

	// Create a functional device object to represent the hardware we're managing.

	PDEVICE_OBJECT fdo;
	
	UNICODE_STRING devname;
	RtlInitUnicodeString(&devname, L"\\DosDevices\\PNPMON");

	status = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), &devname,
		FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, TRUE, &fdo);	// note: exclusive device
	if (!NT_SUCCESS(status))
		{						// can't create device object
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
		}						// can't create device object
	
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// From this point forward, any error will have side effects that need to
	// be cleaned up. Using a try-finally block allows us to modify the program
	// easily without losing track of the side effects.

	__try
		{						// finish initialization
		pdx->DeviceObject = fdo;
		pdx->DriverObject = DriverObject;
		InitializeListHead(&pdx->registered);
		InitializeListHead(&pdx->events);
		KeInitializeSpinLock(&pdx->eventlock);

		// Make a copy of the device name

		pdx->devname.Buffer = (PWCHAR) ExAllocatePool(NonPagedPool, devname.MaximumLength);
		if (!pdx->devname.Buffer)
			{					// can't allocate buffer
			status = STATUS_INSUFFICIENT_RESOURCES;
			KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of name\n", devname.MaximumLength));
			__leave;
			}					// can't allocate buffer
		pdx->devname.MaximumLength = devname.MaximumLength;
		RtlCopyUnicodeString(&pdx->devname, &devname);
		}						// finish initialization
	__finally
		{						// cleanup side effects
		if (!NT_SUCCESS(status))
			{					// need to cleanup
			if (pdx->devname.Buffer)
				RtlFreeUnicodeString(&pdx->devname);
			IoDeleteDevice(fdo);
			}					// need to cleanup
		}						// cleanup side effects

	return status;
	}							// AddDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

///////////////////////////////////////////////////////////////////////////////

#ifdef _X86_

BOOLEAN IsWin98()
	{							// IsWin98
	return !IoIsWdmVersionAvailable(1, 0x10);
	}							// IsWin98

#endif // _X86_

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID RemoveDevice(IN PDEVICE_OBJECT fdo)
	{							// RemoveDevice
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	while (!IsListEmpty(&pdx->events))
		{						// purge unread event list
		PLIST_ENTRY list = RemoveHeadList(&pdx->events);
		RemoveEntryList(list);
		ExFreePool(CONTAINING_RECORD(list, EVENT_RECORD, ListEntry));
		}						// purge unread event list

	RtlFreeUnicodeString(&pdx->devname);

	IoDeleteDevice(fdo);
	}							// RemoveDevice

///////////////////////////////////////////////////////////////////////////////

#if DBG && defined(_X86_)
#pragma LOCKEDCODE

extern "C" void __declspec(naked) __cdecl _chkesp()
	{
	_asm je okay
	ASSERT(!DRIVERNAME " - Stack pointer mismatch!");
okay:
	_asm ret
	}

#endif // DBG
