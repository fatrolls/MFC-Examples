// Declarations for Generic driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DRIVER_H
#define DRIVER_H

#define GENERIC_INTERNAL
#include "Generic.h"

#define DRIVERNAME "GENERIC"				// for use in messages

///////////////////////////////////////////////////////////////////////////////
// Device extension structure

enum DEVSTATE {
	STOPPED,								// device stopped
	WORKING,								// started and working
	PENDINGSTOP,							// stop pending
	PENDINGREMOVE,							// remove pending
	SURPRISEREMOVED,						// removed by surprise
	REMOVED,								// removed
	};

typedef struct _GENERIC_EXTENSION {
	PDEVICE_OBJECT DeviceObject;			// device object this extension belongs to
	PDEVICE_OBJECT LowerDeviceObject;		// next lower driver in same stack
	PDEVICE_OBJECT Pdo;						// the PDO
	PGENERIC_REMOVE_LOCK RemoveLock;		// removal control locking structure
	DEVSTATE state;							// current state of device
	DEVSTATE prevstate;						// state prior to removal query
	DEVICE_POWER_STATE devpower;			// current device power state
	SYSTEM_POWER_STATE syspower;			// current system power state
	PULONG idlecount;						// address of idle counter from idle detection registration
	ULONG cto;								// conservation timeout
	ULONG pto;								// performance timeout
	DEVICE_POWER_STATE idlestate;			// idle state requested by minidriver
	DEVICE_CAPABILITIES devcaps;			// copy of most recent device capabilities
	PDEVQUEUE dqReadWrite;					// queue for reads and writes
	PSTART_DEVICE StartDevice;				// routine to initialize device configuration
	PSTOP_DEVICE StopDevice;				// routine to release device configuration
	PREMOVE_DEVICE RemoveDevice;			// routine to remove device object
	PQUERYFUNCTION OkayToStop;				// okay to stop device now?
	PQUERYFUNCTION OkayToRemove;			// okay to remove device now?
	CHAR DebugName[64];						// name for debugging messages
	ULONG Flags;							// flags from initialization call
	LONG npagefiles;						// # page files about which we've been notified
	LONG ndumpfiles;						// # dump ditto
	LONG nhibernatefiles;					// # hibernate ditto
	LIST_ENTRY PendingIoctlList;			// list of asynchronous IOCTLs
	NTSTATUS IoctlAbortStatus;				// abort incoming IOCTLs if nonzero
	PQUERYPOWERFUNCTION QueryPower;			// okay to change device power?
	PCONTEXTFUNCTION SaveDeviceContext;		// routine to save device context
	PCONTEXTFUNCTION RestoreDeviceContext;	// routine to restore device context
	PNP_DEVICE_STATE pnpstate;				// new PnP state bits
	PNP_DEVICE_STATE pnpstatemask;			// mask of changed state bits
	DEVICE_POWER_STATE PerfBoundary;		// context restore very expensive from >= this power state
	PIRP WaitWakeIrp;						// outstanding WAIT_WAKE request (if any)
	LONG wwcancelled;						// non-zero when WAIT_WAKE has been cancelled
	LONG wwoutstanding;						// non-zero between PoRequestPowerIrp and WaitWaitCallback
	POWER_SEQUENCE oldseq;					// old power sequence numbers
	FAST_MUTEX iflock;						// for interlocking use of interface list
	LIST_ENTRY iflist;						// list of registered device interfaces
	BOOLEAN HardwareWorking;				// we should touch hardware at stop-device time
	BOOLEAN WakeupEnabled;					// device wakeup feature is enabled
	BOOLEAN StalledForPower;				// power management has stalled IRP queue
	} GENERIC_EXTENSION;

///////////////////////////////////////////////////////////////////////////////

typedef struct _PENDINGIOCTL {
	LIST_ENTRY ListEntry;					// linking field
	PIRP Irp;								// the IRP in question
	PIRP* pIrp;								// minidriver's one pointer to the IRP
	} PENDINGIOCTL, *PPENDINGIOCTL;

///////////////////////////////////////////////////////////////////////////////

typedef struct _INTERFACE_RECORD {
	LIST_ENTRY list;						// linking fields
	GUID guid;								// guid for registered interface
	UNICODE_STRING linkname;				// symbolic link name
	} INTERFACE_RECORD, *PINTERFACE_RECORD;

///////////////////////////////////////////////////////////////////////////////
// Global functions

struct _POWERINFO;

VOID AbortPendingIoctls(PGENERIC_EXTENSION pdx, NTSTATUS status);
VOID AdjustSpecialFileCounter(PGENERIC_EXTENSION pdx, BOOLEAN inpath, PLONG counter);
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info);
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status);
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS GetPowerInfoFromRegistry(PGENERIC_EXTENSION pdx, _POWERINFO* pip);
NTSTATUS ImplementPowerPolicy(PGENERIC_EXTENSION pdx, _POWERINFO* pip);
BOOLEAN OkayToRemove(PGENERIC_EXTENSION pdx);
BOOLEAN OkayToStop(PGENERIC_EXTENSION pdx);
NTSTATUS SendDeviceSetPower(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
NTSTATUS WritePowerInfoToRegistry(PGENERIC_EXTENSION pdx, _POWERINFO* pip);

extern BOOLEAN win98;						// true if running under Win98

extern KSPIN_LOCK IoctlListLock;			// spin lock for asynchronous IOCTLs

#endif // DRIVER_H
