// Main program for notify driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);
VOID DriverUnload(IN PDRIVER_OBJECT fdo);
NTSTATUS OnRequestComplete(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PKEVENT pev);

BOOLEAN IsWin98();
BOOLEAN win98 = FALSE;

UNICODE_STRING servkey;

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	KdPrint((DRIVERNAME " - Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	// Insist that OS support at least the WDM level of the DDK we use

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

	// Initialize function pointers

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->DriverExtension->AddDevice = AddDevice;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = DispatchCleanup;
	DriverObject->MajorFunction[IRP_MJ_POWER] = DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP] = DispatchPnp;
	
	return STATUS_SUCCESS;
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
	{							// DriverUnload
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
	RtlFreeUnicodeString(&servkey);
	}							// DriverUnload

///////////////////////////////////////////////////////////////////////////////

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo)
	{							// AddDevice
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	NTSTATUS status;

	// Create a functional device object to represent the hardware we're managing.

	UNICODE_STRING devname;
	RtlInitUnicodeString(&devname, L"\\DosDevices\\NOTIFY");
	PDEVICE_OBJECT fdo;
	#define xsize sizeof(DEVICE_EXTENSION)
	status = IoCreateDevice(DriverObject, xsize, &devname,
		FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &fdo);
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
		pdx->Pdo = pdo;
		IoInitializeRemoveLock(&pdx->RemoveLock, 0, 0, 0);
		pdx->state = STOPPED;		// device starts in the stopped state

		// Link our device object into the stack leading to the PDO
		
		pdx->LowerDeviceObject = IoAttachDeviceToDeviceStack(fdo, pdo);
		if (!pdx->LowerDeviceObject)
			{						// can't attach device
			KdPrint((DRIVERNAME " - IoAttachDeviceToDeviceStack failed\n"));
			status = STATUS_DEVICE_REMOVED;
			__leave;
			}						// can't attach device

		// Set power management flags in the device object

		fdo->Flags |= DO_POWER_PAGABLE;

		// Indicate that our initial power state is D0 (fully on). Also indicate that
		// we have a pagable power handler (otherwise, we'll never get idle shutdown
		// messages!)

		pdx->syspower = PowerSystemWorking;
		pdx->devpower = PowerDeviceD0;
		POWER_STATE state;
		state.DeviceState = PowerDeviceD0;
		PoSetPowerState(fdo, DevicePowerState, state);

		// Initialize list head and spin lock used to coordinate asynchronous
		// I/O Control operations

		InitializeListHead(&pdx->PendingIoctlList);
		KeInitializeSpinLock(&pdx->IoctlListLock);

		// Clear the "initializing" flag so that we can get IRPs

		fdo->Flags &= ~DO_DEVICE_INITIALIZING;
		}						// finish initialization
	__finally
		{						// cleanup side effects
		if (!NT_SUCCESS(status))
			{					// need to cleanup
			if (pdx->LowerDeviceObject)
				IoDetachDevice(pdx->LowerDeviceObject);
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

NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ForwardAndWait(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// ForwardAndWait
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	PAGED_CODE();
	
	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	IoCallDriver(pdx->LowerDeviceObject, Irp);
	KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
	return Irp->IoStatus.Status;
	}							// ForwardAndWait

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnRequestComplete(IN PDEVICE_OBJECT fdo, IN PIRP Irp, IN PKEVENT pev)
	{							// OnRequestComplete
	KeSetEvent(pev, 0, FALSE);
	return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnRequestComplete

///////////////////////////////////////////////////////////////////////////////

VOID EnableAllInterfaces(PDEVICE_EXTENSION pdx, BOOLEAN enable)
	{							// EnableAllInterfaces
	}							// EnableAllInterfaces

///////////////////////////////////////////////////////////////////////////////

VOID DeregisterAllInterfaces(PDEVICE_EXTENSION pdx)
	{							// DeregisterAllInterfaces
	}							// DeregisterAllInterfaces

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID RemoveDevice(IN PDEVICE_OBJECT fdo)
	{							// RemoveDevice
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	if (pdx->LowerDeviceObject)
		IoDetachDevice(pdx->LowerDeviceObject);

	IoDeleteDevice(fdo);
	}							// RemoveDevice

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

BOOLEAN IsWin98()
	{							// IsWin98
#ifdef _X86_

	// Windows 98 (including 2d ed) supports WDM version 1.0, whereas Win2K
	// supports 1.10.

	return !IoIsWdmVersionAvailable(1, 0x10);
#else // not _X86_
	return FALSE;
#endif // not _X86_
	}							// IsWin98

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
