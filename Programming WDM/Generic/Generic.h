// GENERIC.H -- Public interface to GENERIC.SYS
// Copyright (C) 1999 by Walter Oney
// All rights reserved
// @doc

#ifndef GENERIC_H
#define GENERIC_H

#ifdef __cplusplus
	#define GENERICAPI extern "C" 
#else
	#define GENERICAPI
#endif

#ifdef GENERIC_INTERNAL
	#define GENERIC_EXPORT __declspec(dllexport) __stdcall
#else
	#define GENERIC_EXPORT __declspec(dllimport) __stdcall
	#pragma comment(lib, "generic.lib")
#endif

///////////////////////////////////////////////////////////////////////////////

typedef VOID (__stdcall *PQNOTIFYFUNC)(PVOID);

typedef struct _DEVQUEUE {
	LIST_ENTRY head;
	KSPIN_LOCK lock;
	PDRIVER_STARTIO StartIo;
	LONG stallcount;
	PIRP CurrentIrp;
	KEVENT evStop;
	PQNOTIFYFUNC notify;
	PVOID notifycontext;
	NTSTATUS abortstatus;
	} DEVQUEUE, *PDEVQUEUE;

GENERICAPI VOID		GENERIC_EXPORT InitializeQueue(PDEVQUEUE pdq, PDRIVER_STARTIO StartIo);
GENERICAPI VOID		GENERIC_EXPORT StartPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo, PIRP Irp, PDRIVER_CANCEL cancel);
GENERICAPI PIRP		GENERIC_EXPORT StartNextPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo);
GENERICAPI VOID		GENERIC_EXPORT CancelRequest(PDEVQUEUE pdq, PIRP Irp);
GENERICAPI VOID		GENERIC_EXPORT CleanupRequests(PDEVQUEUE pdq, PFILE_OBJECT fop, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT StallRequests(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT RestartRequests(PDEVQUEUE pdq, PDEVICE_OBJECT fdo);
GENERICAPI PIRP		GENERIC_EXPORT GetCurrentIrp(PDEVQUEUE pdq);
GENERICAPI BOOLEAN	GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT WaitForCurrentIrp(PDEVQUEUE pdq);
GENERICAPI VOID		GENERIC_EXPORT AbortRequests(PDEVQUEUE pdq, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT AllowRequests(PDEVQUEUE pdq);
GENERICAPI NTSTATUS	GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE pdq);
GENERICAPI NTSTATUS GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE pdq, PQNOTIFYFUNC notify, PVOID context);

///////////////////////////////////////////////////////////////////////////////

// The support routines for remove locking were not originally declared in WDM.H because they
// weren't implemented in Win98 Gold. The following declarations provide equivalent
// functionality on all WDM platforms.

typedef struct _GENERIC_REMOVE_LOCK {
	LONG usage;					// reference count
	BOOLEAN removing;			// true if removal is pending
	KEVENT evRemove;			// event to wait on
	} GENERIC_REMOVE_LOCK, *PGENERIC_REMOVE_LOCK;

GENERICAPI VOID		GENERIC_EXPORT GenericInitializeRemoveLock(PGENERIC_REMOVE_LOCK lock, ULONG tag, ULONG minutes, ULONG maxcount);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericAcquireRemoveLock(PGENERIC_REMOVE_LOCK lock, PVOID tag);
GENERICAPI VOID		GENERIC_EXPORT GenericReleaseRemoveLock(PGENERIC_REMOVE_LOCK lock, PVOID tag);
GENERICAPI VOID		GENERIC_EXPORT GenericReleaseRemoveLockAndWait(PGENERIC_REMOVE_LOCK lock, PVOID tag);

// NTDDK.H and WDM.H declares the documented support functions as macros which
// we need to redefine.

#if !defined(_NTDDK_)
	#error You must include WDM.H or NTDDK.H before GENERIC.H
#endif

#undef IoInitializeRemoveLock
#define IoInitializeRemoveLock GenericInitializeRemoveLock

#undef IoAcquireRemoveLock
#define IoAcquireRemoveLock GenericAcquireRemoveLock

#undef IoReleaseRemoveLock
#define IoReleaseRemoveLock GenericReleaseRemoveLock

#undef IoReleaseRemoveLockAndWait
#define IoReleaseRemoveLockAndWait GenericReleaseRemoveLockAndWait

// NTDDK.H/WDM.H declares an IO_REMOVE_LOCK structure.

#define _IO_REMOVE_LOCK _GENERIC_REMOVE_LOCK
#define IO_REMOVE_LOCK GENERIC_REMOVE_LOCK
#define PIO_REMOVE_LOCK PGENERIC_REMOVE_LOCK

///////////////////////////////////////////////////////////////////////////////

struct _GENERIC_EXTENSION;		// opaque
typedef struct _GENERIC_EXTENSION* PGENERIC_EXTENSION;

// @func NTSTATUS | StartDevice | Configure device during IRP_MN_START_DEVICE.
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object.
// @parm PCM_PARTIAL_RESOURCE_LIST | raw | "Raw" (i.e., untranslated) resources assigned by the PnP Manager.
// @parm PCM_PARTIAL_RESOURCE_LIST | translated | Translated resources assigned by the PnP Manager.
// @rdesc Standard status code
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the StartDevice field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension..

typedef NTSTATUS (__stdcall *PSTART_DEVICE)(PDEVICE_OBJECT, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated);

// @func VOID | StopDevice | Deconfigure device during IRP_MN_STOP_DEVICE (and at other times).
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object.
// @parm BOOLEAN | OkTouch | TRUE if it will be okay to communicate with the hardware, FALSE otherwise.
// @comm In general, the operations of StopDevice should be the opposite of the operations performed in StartDevice.
// @devnote StopDevice can be called multiple times for a single call to StartDevice.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the StopDevice field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension..

typedef VOID (__stdcall *PSTOP_DEVICE)(PDEVICE_OBJECT, BOOLEAN);

// @func VOID | RemoveDevice | Destroy device object in response to IRP_MN_REMOVE_DEVICE
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object
// @comm In general, the operations of RemoveDevice should be the opposite of the operations performed in AddDevice.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the RemoveDevice field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension..

typedef VOID (__stdcall *PREMOVE_DEVICE)(PDEVICE_OBJECT);

// @func BOOLEAN | OkayToStop | Determine if it's okay to stop the device right now
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object.
// @rdesc TRUE if the device can be stopped immediately, FALSE otherwise.
// @comm GENERIC calls this function during the processing of IRP_MN_QUERY_STOP_DEVICE to determine if there's any reason
// why the device could not immediately be stopped. If your device can't be stopped because it's busy
// with a particular type of IRP, for example, you can return FALSE.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the OkayToStop field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension..

// @func BOOLEAN | OkayToRemove | Determine if it's okay to remove the device right now
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object.
// @rdesc TRUE if the device can be remove immediately, FALSE otherwise.
// @comm GENERIC calls this function during the processing of IRP_MN_QUERY_REMOVE_DEVICE to determine if there's any reason
// why the device could not immediately be removed.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the OkayToRemove field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension.

// @func VOID | StartIo | Start the next I/O operation
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object
// @parm PIRP | Irp | An IRP to be started
// @comm GENERIC passes IRPs one at a time to this routine when you call StartPacket or
// StartNextPacket. Your function looks like a regular StartIo function in the "Standard Model"
// for IRP processing, except that it contains no logic for dealing with a cancelled IRP.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the StartIo field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension.

typedef BOOLEAN (__stdcall *PQUERYFUNCTION)(PDEVICE_OBJECT);

// @func BOOLEAN | QueryPowerChange | Determine if a pending power change will be okay
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object
// @parm DEVICE_POWER_STATE | oldstate | The current power state for the device
// @parm DEVICE_POWER_STATE | newstate | The proposed new power state for the device
// @rdesc TRUE if the proposed power change is permissible, FALSE if not.
// @comm GENERIC calls this routine as part of handling an IRP_MN_QUERY_POWER involving a
// proposed change in the device power state. You should provide the answer without blocking
// the current thread.
// Your function must be in nonpaged memory unless you know that the underlying IRP can never
// be sent at DISPATCH_LEVEL.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the QueryPower field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension.

typedef BOOLEAN (__stdcall *PQUERYPOWERFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE);

// @func VOID | SaveDeviceContext | Save device context in preparation for powering down
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object
// @parm DEVICE_POWER_STATE | oldstate | Old device power state
// @parm DEVICE_POWER_STATE | newstate | New device power state
// @parm PVOID | context | Context parameter to use in eventual call to GenericSaveRestoreComplete
// @comm GENERIC calls this function to afford you an opportunity to save any device context
// information that will be lost when the device enters the specified new power state.
// You should initiate any required I/O operations without waiting for them to complete.
// When all operations finish, call GenericSaveRestoreComplete.
// Your function must be in nonpaged memory unless you know that the underlying IRP can never
// be sent at DISPATCH_LEVEL.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the SaveDeviceContext field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension.

// @func VOID | RestoreDeviceContext | Restore device context following power up
// @parm PDEVICE_OBJECT | DeviceObject | Address of the device object
// @parm DEVICE_POWER_STATE | oldstate | Old device power state
// @parm DEVICE_POWER_STATE | newstate | New device power state
// @parm PVOID | context | Context parameter to use in eventual call to GenericSaveRestoreComplete
// @comm GENERIC calls this function to afford you an opportunity to restore any device context
// information that should be restored after power is restored to your device.
// You should initiate any required I/O operations without waiting for them to complete.
// When all operations finish, call GenericSaveRestoreComplete.
// Your function must be in nonpaged memory unless you know that the underlying IRP can never
// be sent at DISPATCH_LEVEL.
// @comm The name of this function is a placeholder for a function you define in your driver. You
// initialize the SaveDeviceContext field in the GENERIC_INIT_STRUCT to point to your function
// before you call InitializeGenericExtension.

typedef VOID (__stdcall *PCONTEXTFUNCTION)(PDEVICE_OBJECT, DEVICE_POWER_STATE, DEVICE_POWER_STATE, PVOID);

// @struct GENERIC_INIT_STRUCT | Parameter structure for InitializeGenericExtension
// @comm You create an instance of this structure and pass its address as an argument when
// you call InitializeGenericExtension
// @ex The following example illustrates how you might initialize this structure: |
// GENERIC_INIT_STRUCT gis;
// gis.Size = sizeof(GENERIC_INIT_STRUCT);
// gis.DeviceObject = fdo;
// gis.Pdo = pdo;
// gis.Ldo = pdx->LowerDeviceObject;
// gis.RemoveLock = &pdx->RemoveLock;
// gis.DeviceQueue = &pdx->dqReadWrite;
// gis.StartIo = StartIo;
// gis.StartDevice = StartDevice;
// gis.StopDevice = StopDevice;
// gis.RemoveDevice = RemoveDevice;
// RtlInitUnicodeString(&gis, DebugName, L"MYDRIVER");
// gis.Flags = GENERIC_SURPRISE_REMOVAL_OK | GENERIC_IDLE_DETECT;
// gis.OkayToStop = OkayToStop;
// gis.OkayToRemove = OkayToRemove;
// @end

typedef struct _GENERIC_INIT_STRUCT {
	ULONG Size;						// @field Size of this structure. Initialize this to sizeof(GENERIC_INIT_STRUCT).
	PDEVICE_OBJECT DeviceObject;	// @field The device object being registered. This would generally be returned by IoCreateDevice.
	PDEVICE_OBJECT Pdo;				// @field The PDO below this device object. This would generally be the same as the 2d argument to AddDevice.
	PDEVICE_OBJECT Ldo;				// @field Immediately lower device object. Set this equal to the return value from IoAttachDeviceToDeviceStack.
	PGENERIC_REMOVE_LOCK RemoveLock;// @field Address of remove lock in containing device extension (optional). InitializeGenericExtension will initialize this object for you. Specify NULL if you're not using an IO_REMOVE_LOCK. 
	PDEVQUEUE DeviceQueue;			// @field Address of queue object for read/write IRPs (optional). InitializeGenericExtension will initialize this object for you. Specify NULL if you don't queue read/write IRPs.
	PDRIVER_STARTIO StartIo;		// @field Start I/O routine for reads & writes (required only if DeviceQueue non-NULL). See the entry for StartIo for an explanation of the calling sequence to this routine.
	PSTART_DEVICE StartDevice;		// @field Routine to initialize device configuration. See the entry for StartDevice for an explanation of the calling sequence to this routine.
	PSTOP_DEVICE StopDevice;		// @field Routine to release device configuration. See the entry for StopDevice for an explanation of the calling sequence to this routine.
	PREMOVE_DEVICE RemoveDevice;	// @field Routine to remove device object. See the entry for RemoveDevice for an explanation of the calling sequence to this routine.
	UNICODE_STRING DebugName;		// @field Name to use in debug messages.
	ULONG Flags;					// @field Option flags. Zero or more of the following values:
									// @flag GENERIC_AUTOLAUNCH | Register and enable a device interface so that the AutoLaunch service will launch an application when this device starts.
									// @flag GENERIC_USAGE_PAGING | This device supports the paging-file usage notification.
									// @flag GENERIC_USAGE_DUMP | This device supports the dump-file usage notification.
									// @flag GENERIC_USAGE_HIBERNATE | This device supports the hibernate-file usage notification.
									// @flag GENERIC_PENDING_IOCTLS | The driver may cache asynchronous DeviceIoControl operations.
									// @flag GENERIC_SURPRISE_REMOVAL_OK | Surprise removal of the device is okay.
									// @flag GENERIC_IDLE_DETECT | Device supports GENERIC's idle detection scheme.
	PQUERYFUNCTION OkayToStop;		// @field Routine to decide whether it's okay to stop device now (optional). See the entry for OkayToStop for an explanation of the calling sequence to this routine. If you specify NULL, GENERIC assumes it's always okay to stop your device.
	PQUERYFUNCTION OkayToRemove;	// @field Routine to decide whether it's okay to remove device now (optional). See the entry for OkayToRemove for an explanation of the calling sequence to this routine. If you specify NULL, GENERIC assumes it's always okay to remove your device.
	PQUERYPOWERFUNCTION QueryPower;	// @field Routine to decide whether a proposed device power change is okay (optional). See the entry for QueryPower for an explanation of the calling sequence to this routine. If you specify NULL, GENERIC assumes that all power changes are okay unless your device is in the path of a paging, dump, or hibernation file.
	PCONTEXTFUNCTION SaveDeviceContext;	// @field Routine to save device context before power down (optional). See the entry for SaveDeviceContext for an explanation of the calling sequence to this routine. If you specify NULL, GENERIC will power the device down without affording you a chance to save any context information.
	PCONTEXTFUNCTION RestoreDeviceContext;	// @field Routine to restore device context after power up (optional). See the entry for RestoreDeviceContext for an explanation of the calling sequence to this routine. If you specify NULL, GENERIC will restore power to the device without affording you a chance to restore any context information.
	DEVICE_POWER_STATE PerfBoundary;		// @field (Optional) Power state below which context restore inordinately expensive. Leave zero if context restore not ever a performance issue with this device.
	} GENERIC_INIT_STRUCT, *PGENERIC_INIT_STRUCT;

#define GENERIC_AUTOLAUNCH			0x00000001	// register for AutoLaunch
#define GENERIC_USAGE_PAGING		0x00000002	// device supports DeviceUsageTypePaging
#define GENERIC_USAGE_DUMP			0x00000004	// device supports DeviceUsageTypeDumpFile
#define GENERIC_USAGE_HIBERNATE		0x00000008	// device supports DeviceUsageTypeHibernation
#define GENERIC_PENDING_IOCTLS		0x00000010	// driver may cache asynchronous IOCTLs
#define GENERIC_SURPRISE_REMOVAL_OK	0x00000020	// surprise removal of device is okay
#define GENERIC_IDLE_DETECT			0x00000040	// device supports generic idle detection scheme

#define GENERIC_CLIENT_FLAGS		0x0000007F	// mask to select client-controllable flags

// Enumeration for "wf" argument to GenericWakeupControl:

enum WAKEFUNCTION {
	EnableWakeup,					// enable system wakeup
	DisableWakeup,					// disable system wakeup
	ManageWaitWake,					// request or cancel WAIT_WAKE IRP, as appropriate
	CancelWaitWake,					// unconditionally cancel WAIT_WAKE
	};

// Exported functions

GENERICAPI NTSTATUS	GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION pdx, PIRP Irp, PIRP* pIrp);
GENERICAPI VOID		GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDeregisterInterface(PGENERIC_EXTENSION pdx, const GUID* guid);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPnp(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPower(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericEnableInterface(PGENERIC_EXTENSION pdx, const GUID* guid, BOOLEAN enable);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericHandlePowerIoctl(PGENERIC_EXTENSION pdx, PIRP Irp);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericIdleDevice(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
GENERICAPI VOID		GENERIC_EXPORT GenericMarkDeviceBusy(PGENERIC_EXTENSION);
GENERICAPI VOID     GENERIC_EXPORT GenericRegisterForIdleDetection(PGENERIC_EXTENSION, ULONG ConservationTimeout, ULONG PerformanceTimeout, DEVICE_POWER_STATE State);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericRegisterInterface(PGENERIC_EXTENSION pdx, const GUID* guid);
GENERICAPI VOID		GENERIC_EXPORT GenericSaveRestoreComplete(PVOID context);
GENERICAPI VOID		GENERIC_EXPORT GenericSetDeviceState(PGENERIC_EXTENSION pdx, PNP_DEVICE_STATE pnpstate);
GENERICAPI PIRP		GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION pdx, PIRP* pIrp);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupControl(PGENERIC_EXTENSION pdx, enum WAKEFUNCTION wf);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupFromIdle(PGENERIC_EXTENSION pdx, BOOLEAN wait = FALSE);
GENERICAPI ULONG    GENERIC_EXPORT GetSizeofGenericExtension(VOID);
GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION, PGENERIC_INIT_STRUCT);
GENERICAPI BOOLEAN	GENERIC_EXPORT IsWin98();

#endif