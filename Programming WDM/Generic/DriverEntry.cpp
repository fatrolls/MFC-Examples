// Main program for Generic driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved
// @doc

#include "stddcls.h"
#include "driver.h"

#include <initguid.h>
DEFINE_GUID(GUID_AUTOLAUNCH_NOTIFY, 0xba4ec740, 0xda8b, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);
#include "GenericPower.h"

NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev);

BOOLEAN win98 = FALSE;
KSPIN_LOCK IoctlListLock;
BOOLEAN IoctlListLockInitialized = FALSE;

///////////////////////////////////////////////////////////////////////////////

#pragma INITCODE

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	return STATUS_SUCCESS;		// never entered, actually
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

// Overloaded variant that doesn't change IoStatus.Information -- use
// this for most PnP requests.

NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status)
	{							// CompleteRequest
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// CompleteRequest

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ForwardAndWait(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// ForwardAndWait
	PAGED_CODE();
	
	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	IoCallDriver(pdx->LowerDeviceObject, Irp);
	KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
	return Irp->IoStatus.Status;
	}							// ForwardAndWait

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Determine the size of the GENERIC.SYS device extension
// @rdesc Number of bytes needed by GENERIC.SYS in your device extension.
// @comm Call this function before creating your device object.
// @ex The following example illustrates how to specify the device extension size when you call IoCreateDevice |
//   ULONG dxsize = (sizeof(DEVICE_EXTENSION) + 7) & ~7;
//   ULONG xsize = dxsize + GetSizeofGenericExtension();
//   PDEVICE_OBJECT fdo;
//   NTSTATUS status = IoCreateDevice(DriverObject, xsize, ..., &fdo);
//   PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceObject;
//   PGENERIC_EXTENSION pgx = (PGENERIC_EXTENSION) ((PUCHAR) pdx + dxsize);
// @end

GENERICAPI ULONG GENERIC_EXPORT GetSizeofGenericExtension()
	{							// GetSizeofGenericExtension
	PAGED_CODE();
	ULONG size = (sizeof(GENERIC_EXTENSION) + 7) & ~7;
	return size;
	}							// GetSizeofGenericExtension

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Initialize GENERIC.SYS for a new device object
// @parm Address of queue object
// @parm Structure containing initialization parameters
// @rdesc Standard status code, such as:
// @flag STATUS_INVALID_PARAMETER | Invalid parameter in initialization structure
// @flag STATUS_SUCCESS | Normal result
// @comm Call this function from your AddDevice function to register to use GENERIC.SYS
// for handling standard WDM driver functions
// @ex The following example illustrates how to initialize your driver to use GENERIC.SYS: |
// NTSTATUS AddDevice(...)
//   {
//   ULONG dxsize = (sizeof(DEVICE_EXTENSION) + 7) & ~7;
//   ULONG xsize = dxsize + GetSizeofGenericExtension();
//   PDEVICE_OBJECT fdo;
//   NTSTATUS status = IoCreateDevice(DriverObject, xsize, ..., &fdo);
//   PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceObject;
//   PGENERIC_EXTENSION pgx = (PGENERIC_EXTENSION) ((PUCHAR) pdx + dxsize);
//   GENERIC_INIT_STRUCT gis = {sizeof(GENERIC_INIT_STRUCT)};
//   [initialize fields of "gis" structure]
//   status = InitializeGenericExtension(pgx, &gis);
//   }
// @end

GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION pdx, PGENERIC_INIT_STRUCT isp)
	{							// InitializeGenericExtension
	if (isp->Size < FIELD_OFFSET(GENERIC_INIT_STRUCT, Flags)
		|| !isp->DeviceObject
		|| !isp->Ldo
		|| !isp->Pdo
		|| !isp->StartDevice
		|| !isp->StopDevice
		|| !isp->RemoveDevice
		|| isp->DeviceQueue && !isp->StartIo)

		return STATUS_INVALID_PARAMETER;

	RtlZeroMemory(pdx, sizeof(GENERIC_EXTENSION));

	pdx->DeviceObject = isp->DeviceObject;
	pdx->LowerDeviceObject = isp->Ldo;
	pdx->Pdo = isp->Pdo;
	pdx->StartDevice = isp->StartDevice;
	pdx->StopDevice = isp->StopDevice;
	pdx->RemoveDevice = isp->RemoveDevice;

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, OkayToRemove) + sizeof(PQUERYFUNCTION))
		{						// set OkayToStop & OkayToRemove pointers
		pdx->OkayToStop = isp->OkayToStop;
		pdx->OkayToRemove = isp->OkayToRemove;
		}						// set OkayToStop & OkayToRemove pointers

	if ((pdx->dqReadWrite = isp->DeviceQueue))
		{						// queue reads & writes
		if (!isp->StartIo)
			return STATUS_INVALID_PARAMETER;
		InitializeQueue(pdx->dqReadWrite, isp->StartIo);
		}						// queue reads & writes

	if ((pdx->RemoveLock = isp->RemoveLock))
		IoInitializeRemoveLock(pdx->RemoveLock, 0, 0, 0);

	pdx->state = STOPPED;
	
	pdx->devpower = PowerDeviceD0;
	pdx->syspower = PowerSystemWorking;
	POWER_STATE state;
	state.DeviceState = PowerDeviceD0;
	PoSetPowerState(pdx->DeviceObject, DevicePowerState, state);

	// Capture the mini-driver name for messages. This needs to be in ANSI because
	// unicode conversions at or above DISPATCH_LEVEL are not allowed

	if (!isp->DebugName.Length)
		strcpy(pdx->DebugName, "GENERIC");
	else
		{						// convert debug name
		ANSI_STRING asname = {0, sizeof(pdx->DebugName) - 1, pdx->DebugName};
		RtlUnicodeStringToAnsiString(&asname, &isp->DebugName, FALSE);
		pdx->DebugName[asname.Length] = 0;
		}						// convert debug name

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, Flags) + sizeof(ULONG))
		pdx->Flags = isp->Flags & GENERIC_CLIENT_FLAGS;

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, RestoreDeviceContext) + sizeof(PCONTEXTFUNCTION))
		{						// get power helper functions
		pdx->QueryPower = isp->QueryPower;
		pdx->SaveDeviceContext = isp->SaveDeviceContext;
		pdx->RestoreDeviceContext = isp->RestoreDeviceContext;
		}						// get power helper functions

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, PerfBoundary) + sizeof(DEVICE_POWER_STATE))
		pdx->PerfBoundary = isp->PerfBoundary;
	else
		pdx->PerfBoundary = PowerDeviceUnspecified;

	if (pdx->PerfBoundary == PowerDeviceUnspecified)
		pdx->PerfBoundary = PowerDeviceMaximum; // inhibit POWER_SEQUENCE optimization

	// Initialize variables related to asynchrounous IOCTL management.

	if (pdx->Flags & GENERIC_PENDING_IOCTLS)
		{						// driver may cache asyncronous IOCTLs
		InitializeListHead(&pdx->PendingIoctlList);
		pdx->IoctlAbortStatus = 0;

		// We need to initialize our IOCTL spin lock sometime, but just once.
		// Acquiring the cancel spin lock to guard this operation is a bit of
		// a hack, I suppose, but note that a class driver like this one never
		// gets an actual chance to initialize, so it's not my fault...

		KIRQL oldirql;
		IoAcquireCancelSpinLock(&oldirql);	// any global spin lock would do
		if (!IoctlListLockInitialized)
			{					// initialize global lock
			IoctlListLockInitialized = TRUE;
			KeInitializeSpinLock(&IoctlListLock);
			}					// initialize global lock
		IoReleaseCancelSpinLock(oldirql);
		}						// driver may cache asynchronous IOCTLs

	// Initialize to manage registered device interfaces

	ExInitializeFastMutex(&pdx->iflock);
	InitializeListHead(&pdx->iflist);

	// Indicate we handle power IRPs at PASSIVE_LEVEL

	pdx->DeviceObject->Flags |= DO_POWER_PAGABLE;

	KdPrint(("GENERIC - Initializing for %s\n", pdx->DebugName));

	// If requested to do so, register an AutoLaunch interface

	if (pdx->Flags & GENERIC_AUTOLAUNCH)
		GenericRegisterInterface(pdx, &GUID_AUTOLAUNCH_NOTIFY);

	// Register a power management interface

	GenericRegisterInterface(pdx, &GUID_GENERIC_POWER);

#ifdef _X86_
	win98 = IsWin98();
#endif

	return STATUS_SUCCESS;
	}							// InitializeGenericExtension

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev)
	{							// OnRequestComplete
	KeSetEvent(pev, 0, FALSE);
	return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnRequestComplete

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Determine if we're running under Windows 98 or Windows 2000
// @rdesc TRUE if running under Windows 98, FALSE if under Windows 2000
// @comm This function calls IoIsWdmVersionAvailable to see if the OS
// supports WDM version 1.10. Win98 and Win98 2d ed support 1.00, whereas
// Win2K supports 1.10.

GENERICAPI BOOLEAN GENERIC_EXPORT IsWin98()
	{							// IsWin98
#ifdef _X86_
	return !IoIsWdmVersionAvailable(1, 0x10);
#else
	return FALSE;
#endif // _X86_
	}							// IsWin98


///////////////////////////////////////////////////////////////////////////////

#if DBG && defined(_X86_)
#pragma LOCKEDCODE

extern "C" void __declspec(naked) __cdecl _chkesp()
	{
	_asm je okay
	ASSERT(! DRIVERNAME " - Stack pointer mismatch!");
okay:
	_asm ret
	}

#endif // DBG
