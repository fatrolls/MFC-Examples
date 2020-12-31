// Plug and Play handlers for Generic driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved
// @doc

#include "stddcls.h"
#include "driver.h"
#include "GenericPower.h"

NTSTATUS DefaultPnpHandler(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleCancelRemove(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleCancelStop(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleQueryCapabilities(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleQueryRemove(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleQueryState(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleQueryStop(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleRemoveDevice(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleStartDevice(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleStopDevice(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleSurpriseRemoval(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS HandleUsageNotification(PGENERIC_EXTENSION pdx, PIRP Irp);
NTSTATUS OnNotificationComplete(PDEVICE_OBJECT fdo, PIRP Irp, PGENERIC_EXTENSION pdx);

VOID DeregisterInterface(PGENERIC_EXTENSION pdx, PINTERFACE_RECORD ifp);
VOID DeregisterAllInterfaces(PGENERIC_EXTENSION pdx);
VOID EnableAllInterfaces(PGENERIC_EXTENSION pdx, BOOLEAN enable);
PINTERFACE_RECORD FindInterfaceRecord(PGENERIC_EXTENSION pdx, const GUID* guid);

#if DBG
VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list);

static char* statenames[] = {
	"STOPPED",
	"WORKING",
	"PENDINGSTOP",
	"PENDINGREMOVE",
	"SURPRISEREMOVED",
	"REMOVED",
	};

#endif

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Handle IRP_MJ_PNP
// @parm Address of generic device extension
// @parm Plug and Play request
// @rdesc Standard completion code

GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPnp(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// GenericDispatchPnp
	PAGED_CODE();
	NTSTATUS status = STATUS_SUCCESS;
	if (pdx->RemoveLock && !NT_SUCCESS(status = IoAcquireRemoveLock(pdx->RemoveLock, Irp)))
		return CompleteRequest(Irp, status);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_PNP);

	static NTSTATUS (*fcntab[])(PGENERIC_EXTENSION pdx, PIRP Irp) = {
		HandleStartDevice,		// IRP_MN_START_DEVICE
		HandleQueryRemove,		// IRP_MN_QUERY_REMOVE_DEVICE
		HandleRemoveDevice,		// IRP_MN_REMOVE_DEVICE
		HandleCancelRemove,		// IRP_MN_CANCEL_REMOVE_DEVICE
		HandleStopDevice,		// IRP_MN_STOP_DEVICE
		HandleQueryStop,		// IRP_MN_QUERY_STOP_DEVICE
		HandleCancelStop,		// IRP_MN_CANCEL_STOP_DEVICE
		DefaultPnpHandler,		// IRP_MN_QUERY_DEVICE_RELATIONS
		DefaultPnpHandler,		// IRP_MN_QUERY_INTERFACE
		HandleQueryCapabilities,// IRP_MN_QUERY_CAPABILITIES
		DefaultPnpHandler,		// IRP_MN_QUERY_RESOURCES
		DefaultPnpHandler,		// IRP_MN_QUERY_RESOURCE_REQUIREMENTS
		DefaultPnpHandler,		// IRP_MN_QUERY_DEVICE_TEXT
		DefaultPnpHandler,		// IRP_MN_FILTER_RESOURCE_REQUIREMENTS
		DefaultPnpHandler,		// 
		DefaultPnpHandler,		// IRP_MN_READ_CONFIG
		DefaultPnpHandler,		// IRP_MN_WRITE_CONFIG
		DefaultPnpHandler,		// IRP_MN_EJECT
		DefaultPnpHandler,		// IRP_MN_SET_LOCK
		DefaultPnpHandler,		// IRP_MN_QUERY_ID
		HandleQueryState,		// IRP_MN_QUERY_PNP_DEVICE_STATE
		DefaultPnpHandler,		// IRP_MN_QUERY_BUS_INFORMATION
		HandleUsageNotification,// IRP_MN_DEVICE_USAGE_NOTIFICATION
		HandleSurpriseRemoval,	// IRP_MN_SURPRISE_REMOVAL
		};

	ULONG fcn = stack->MinorFunction;

	if (fcn >= arraysize(fcntab))
		{						// unknown function
		status = DefaultPnpHandler(pdx, Irp); // some function we don't know about
		if (pdx->RemoveLock)
			IoReleaseRemoveLock(pdx->RemoveLock, Irp);
		return status;
		}						// unknown function

#if DBG
	static char* fcnname[] = {
		"IRP_MN_START_DEVICE",
		"IRP_MN_QUERY_REMOVE_DEVICE",
		"IRP_MN_REMOVE_DEVICE",
		"IRP_MN_CANCEL_REMOVE_DEVICE",
		"IRP_MN_STOP_DEVICE",
		"IRP_MN_QUERY_STOP_DEVICE",
		"IRP_MN_CANCEL_STOP_DEVICE",
		"IRP_MN_QUERY_DEVICE_RELATIONS",
		"IRP_MN_QUERY_INTERFACE",
		"IRP_MN_QUERY_CAPABILITIES",
		"IRP_MN_QUERY_RESOURCES",
		"IRP_MN_QUERY_RESOURCE_REQUIREMENTS",
		"IRP_MN_QUERY_DEVICE_TEXT",
		"IRP_MN_FILTER_RESOURCE_REQUIREMENTS",
		"",
		"IRP_MN_READ_CONFIG",
		"IRP_MN_WRITE_CONFIG",
		"IRP_MN_EJECT",
		"IRP_MN_SET_LOCK",
		"IRP_MN_QUERY_ID",
		"IRP_MN_QUERY_PNP_DEVICE_STATE",
		"IRP_MN_QUERY_BUS_INFORMATION",
		"IRP_MN_DEVICE_USAGE_NOTIFICATION",
		"IRP_MN_SURPRISE_REMOVAL",
		};

	KdPrint(("%s - PNP Request (%s)\n", pdx->DebugName, fcnname[fcn]));
#endif // DBG

	status = (*fcntab[fcn])(pdx, Irp);
	if (fcn != IRP_MN_REMOVE_DEVICE && pdx->RemoveLock)
		IoReleaseRemoveLock(pdx->RemoveLock, Irp);
	return status;
	}							// GenericDispatchPnp

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Deregister a device interface
// @parm Address of generic device extension
// @parm Address of GUID for which an interface was previously registered
// @rdesc One of the following standard status codes:
// @flag STATUS_SUCCESS | Operation was performed
// @flag STATUS_INVALID_PARAMETER | No interface GUID by that name registered

GENERICAPI NTSTATUS GENERIC_EXPORT GenericDeregisterInterface(PGENERIC_EXTENSION pdx, const GUID* guid)
	{							// GenericDeregisterInterface
	PAGED_CODE();
	NTSTATUS status;
	
	ExAcquireFastMutex(&pdx->iflock);
	PINTERFACE_RECORD ifp = FindInterfaceRecord(pdx, guid);
	if (ifp)
		{
		DeregisterInterface(pdx, ifp);
		status = STATUS_SUCCESS;
		}
	else
		status = STATUS_INVALID_PARAMETER;

	ExReleaseFastMutex(&pdx->iflock);
	return status;
	}							// GenericDeregisterInterface

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Enable or disable a device interface
// @parm Address of generic device extension
// @parm Address of GUID for which an interface was previously registered
// by calling GenericRegisterInterface
// @parm TRUE if interface should be enabled, FALSE if should be disabled
// @rdesc One of the following standard status codes:
// @flag STATUS_SUCCESS | Operation was performed
// @flag STATUS_INVALID_PARAMETER | No interface GUID by that name registered

GENERICAPI NTSTATUS GENERIC_EXPORT GenericEnableInterface(PGENERIC_EXTENSION pdx, const GUID* guid, BOOLEAN enable)
	{							// GenericEnableInterface
	PAGED_CODE();
	NTSTATUS status;
	
	ExAcquireFastMutex(&pdx->iflock);
	PINTERFACE_RECORD ifp = FindInterfaceRecord(pdx, guid);
	if (ifp)
		{						// enable/disable this interface
		IoSetDeviceInterfaceState(&ifp->linkname, enable);
		status = STATUS_SUCCESS;
		}						// enable/disable this interface
	else
		status = STATUS_INVALID_PARAMETER;

	ExReleaseFastMutex(&pdx->iflock);
	return status;
	}							// GenericEnableInterface

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// @func Register a device interface
// @parm Address of generic device extension
// @parm Address of interface GUID
// @rdesc Standard status code, which may be one of these, among others:
// @flag STATUS_SUCCESS | Operation was performed
// @flag STATUS_INVALID_PARAMETER | An interface for this GUID has already been registered for this device.

GENERICAPI NTSTATUS GENERIC_EXPORT GenericRegisterInterface(PGENERIC_EXTENSION pdx, const GUID* guid)
	{							// GenericRegisterInterface
	PAGED_CODE();
	NTSTATUS status;
	
	ExAcquireFastMutex(&pdx->iflock);
	PINTERFACE_RECORD ifp = FindInterfaceRecord(pdx, guid);
	if (ifp)
		status = STATUS_INVALID_PARAMETER;
	else
		{						// register new interface
		ifp = (PINTERFACE_RECORD) ExAllocatePool(NonPagedPool, sizeof(INTERFACE_RECORD));
		if (ifp)
			{					// initialize new interface record
			status = IoRegisterDeviceInterface(pdx->Pdo, guid, NULL, &ifp->linkname);
			if (NT_SUCCESS(status))
				{				// interface registered
				ifp->guid = *guid;
				InsertHeadList(&pdx->iflist, &ifp->list);
				}				// interface registered
			else
				ExFreePool(ifp);
			}					// initialize new interface record
		else
			status = STATUS_INSUFFICIENT_RESOURCES;
		}						// register new interface

	ExReleaseFastMutex(&pdx->iflock);
	return status;
	}							// GenericRegisterInterface

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

// @func Report change in device status
// @parm Address of generic device extension
// @parm New PnP state flags (see doc for PNP_DEVICE_STATE)
// @comm The client driver must synchronize calls to this routine to prevent
// reentrance. The state that gets reported in the eventual IRP_MN_QUERY_PNP_DEVICE_STATE 
// includes just those flag bits that have changed since the last call to this routine.
// This fact allows you to set PNP_DEVICE_NOT_DISABLEABLE one time and clear it another.

GENERICAPI VOID GENERIC_EXPORT GenericSetDeviceState(PGENERIC_EXTENSION pdx, PNP_DEVICE_STATE pnpstate)
	{							// GenericSetDeviceState
	pdx->pnpstatemask = (pnpstate ^ pdx->pnpstate); // mask for things that changed
	pdx->pnpstate |= pnpstate;

	// Inform PnP manager that our state has changed.

	IoInvalidateDeviceState(pdx->Pdo);
	}							// GenericSetDeviceState

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID CallStopDevice(PGENERIC_EXTENSION pdx)
	{							// CallStopDevice
	GenericWakeupControl(pdx, CancelWaitWake);
	BOOLEAN oktouch = pdx->HardwareWorking;
	pdx->HardwareWorking = FALSE;
	(*pdx->StopDevice)(pdx->DeviceObject, oktouch);
	}							// CallStopDevice

///////////////////////////////////////////////////////////////////////////////

VOID CallRemoveDevice(PGENERIC_EXTENSION pdx)
	{							// CallRemoveDevice
	(*pdx->RemoveDevice)(pdx->DeviceObject);
	}							// CallRemoveDevice

///////////////////////////////////////////////////////////////////////////////

NTSTATUS DefaultPnpHandler(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// DefaultPnpHandler
	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// DefaultPnpHandler

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DeregisterAllInterfaces(PGENERIC_EXTENSION pdx)
	{							// DeregisterAllInterfaces
	PAGED_CODE();
	NTSTATUS status;
	
	ExAcquireFastMutex(&pdx->iflock);

	while (!IsListEmpty(&pdx->iflist))
		{						// for each interface
		PLIST_ENTRY list = RemoveHeadList(&pdx->iflist);
		PINTERFACE_RECORD ifp = CONTAINING_RECORD(list, INTERFACE_RECORD, list);
		DeregisterInterface(pdx, ifp);
		}						// for each interface

	ExReleaseFastMutex(&pdx->iflock);
	}							// DeregisterAllInterfaces

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DeregisterInterface(PGENERIC_EXTENSION pdx, PINTERFACE_RECORD ifp)
	{							// DeregisterInterface
	IoSetDeviceInterfaceState(&ifp->linkname, FALSE);
	RtlFreeUnicodeString(&ifp->linkname);
	RemoveEntryList(&ifp->list);
	ExFreePool(ifp);
	}							// DeregisterInterface

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID EnableAllInterfaces(PGENERIC_EXTENSION pdx, BOOLEAN enable)
	{							// EnableAllInterfaces
	for (PLIST_ENTRY list = pdx->iflist.Flink; list != &pdx->iflist; list = list->Flink)
		{						// search for specified interface record
		PINTERFACE_RECORD ifp = CONTAINING_RECORD(list, INTERFACE_RECORD, list);
		IoSetDeviceInterfaceState(&ifp->linkname, enable);
		}
	}							// EnableAllInterfaces

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

PINTERFACE_RECORD FindInterfaceRecord(PGENERIC_EXTENSION pdx, const GUID* guid)
	{							// FindInterfaceRecord
	PAGED_CODE();

	for (PLIST_ENTRY list = pdx->iflist.Flink; list != &pdx->iflist; list = list->Flink)
		{						// search for specified interface record
		PINTERFACE_RECORD ifp = CONTAINING_RECORD(list, INTERFACE_RECORD, list);
		if (ifp->guid == *guid)
			return ifp;
		}
	return NULL;
	}							// FindInterfaceRecord

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleCancelRemove(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleCancelRemove
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_CANCEL_REMOVE_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	if (pdx->state == PENDINGREMOVE)
		{						// we succeeded earlier query

		// Lower-level drivers are presumably in the pending-remove state as
		// well, so we need to tell them that the remove has been cancelled
		// before we start sending IRPs down to them.

		NTSTATUS status = ForwardAndWait(pdx, Irp); // wait for lower layers
		if (NT_SUCCESS(status))
			{					// completed successfully
			KdPrint(("%s - To %s from PENDINGREMOVE\n", pdx->DebugName, statenames[pdx->prevstate]));
			if ((pdx->state = pdx->prevstate) == WORKING)
				{				// back to working state
				if (pdx->dqReadWrite)
					RestartRequests(pdx->dqReadWrite, pdx->DeviceObject);
				}				// back to working state
			}					// completed successfully
		else
			KdPrint(("%s - Status %8.8lX returned by PDO for IRP_MN_CANCEL_REMOVE_DEVICE", pdx->DebugName, status));

		return CompleteRequest(Irp, status);
		}						// we succeeded earlier query
	
	return DefaultPnpHandler(pdx, Irp); // unexpected cancel
	}							// HandleCancelRemove

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleCancelStop(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleCancelStop
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_CANCEL_STOP_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	if (pdx->state == PENDINGSTOP)
		{						// we succeeded earlier query

		// Lower level drivers are presumably in the pending-stop state as
		// well, so we need to tell them that the stop has been cancelled
		// before we start sending IRPs down to them.

		NTSTATUS status = ForwardAndWait(pdx, Irp); // wait for lower layers
		if (NT_SUCCESS(status))
			{					// completed successfully
			KdPrint(("%s - To WORKING from PENDINGSTOP\n", pdx->DebugName));
			pdx->state = WORKING;
			if (pdx->dqReadWrite)
				RestartRequests(pdx->dqReadWrite, pdx->DeviceObject);
			}					// completed successfully
		else
			KdPrint(("ws - Status %8.8lX returned by PDO for IRP_MN_CANCEL_STOP_DEVICE", pdx->DebugName, status));
		
		return CompleteRequest(Irp, status);
		}						// we succeeded earlier query

	return DefaultPnpHandler(pdx, Irp); // unexpected cancel
	}							// HandleCancelStop

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryCapabilities(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleQueryCapabilities
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_QUERY_CAPABILITIES);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_CAPABILITIES pdc = stack->Parameters.DeviceCapabilities.Capabilities;

	// Check to be sure we know how to handle this version of the capabilities structure

	if (pdc->Version < 1)
		return DefaultPnpHandler(pdx, Irp);

	NTSTATUS status = ForwardAndWait(pdx, Irp);
	if (NT_SUCCESS(status))
		{						// IRP succeeded
		stack = IoGetCurrentIrpStackLocation(Irp);
		pdc = stack->Parameters.DeviceCapabilities.Capabilities;
		if (pdx->Flags & GENERIC_SURPRISE_REMOVAL_OK)
			pdc->SurpriseRemovalOK = TRUE;
		pdx->devcaps = *pdc;	// save capabilities for whoever needs to see them
		}						// IRP succeeded

	return CompleteRequest(Irp, status);
	}							// HandleQueryCapabilities

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryRemove(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleQueryRemove
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_QUERY_REMOVE_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	if (pdx->state == WORKING)
		{						// currently working

	#ifdef _X86_

		// Win98 doesn't check for open handles before allowing a remove to proceed,
		// and it may deadlock in IoReleaseRemoveLockAndWait if handles are still
		// open.

		if (win98 && pdx->DeviceObject->ReferenceCount)
			{
			KdPrint(("%s - Failing removal query due to open handles\n", pdx->DebugName));
			return CompleteRequest(Irp, STATUS_DEVICE_BUSY);
			}

	#endif

		// See if it's okay to remove this device. The test includes asking the client
		// driver. Then stall the queue for the duration of the query. The TOASTER sample
		// in the DDK drains the queue here instead of stalling it, by the way.

		if (!OkayToRemove(pdx))
			return CompleteRequest(Irp, STATUS_UNSUCCESSFUL); // can't remove because busy

		if (pdx->dqReadWrite)
			{					// stall request queue
			StallRequests(pdx->dqReadWrite);
			WaitForCurrentIrp(pdx->dqReadWrite);
			}					// stall request queue

		KdPrint(("%s - To PENDINGREMOVE from %s\n", pdx->DebugName, statenames[pdx->state]));
		}						// currently working

	// Save current state for restoration if the query gets cancelled.
	// (We can now be stopped or working)

	pdx->prevstate = pdx->state;
	pdx->state = PENDINGREMOVE;
	return DefaultPnpHandler(pdx, Irp);
	}							// HandleQueryRemove

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryState(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleQueryState
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_QUERY_PNP_DEVICE_STATE);

	// Note that you can't use sizeof in a #if expression, so it's not possible to use
	// conditional compilation to choose between 32- and 64-bit exchanges in the
	// following statement. If the size of a PNP_DEVICE_STATE changes to be bigger than
	// 32 bits, therefore, you have to change this by hand. The ASSERT will alert you to
	// the problem...

	PNP_DEVICE_STATE mask = InterlockedExchange((PLONG) &pdx->pnpstatemask, 0);
	ASSERT(sizeof(PNP_DEVICE_STATE) == sizeof(LONG));

	if (mask)
		{						// some status flags have changed
		Irp->IoStatus.Status = STATUS_SUCCESS; // indicate we've handled this IRP
		Irp->IoStatus.Information &= ~mask; // clear all changed flags
		Irp->IoStatus.Information |= pdx->pnpstate & mask; // set all flags that were changed to "1"
		}						// some status flags have changed

	// DDK doc says you handle this IRP on the way down, but TOASTER handles
	// it on the way up. It shouldn't matter, because you're not supposed to
	// overstore the result you find already in IoStatus.Information.

	return DefaultPnpHandler(pdx, Irp);
	}							// HandleQueryState

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryStop(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleQueryStop
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_QUERY_STOP_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP
	
	// Boot devices may get this query before they even start, so check to see
	// if we're in the WORKING state before doing anything.

	if (pdx->state != WORKING)
		return DefaultPnpHandler(pdx, Irp);

	// See if it will be okay to stop the device right now. This test includes
	// asking the client driver via a callback routine.

	if (!OkayToStop(pdx))
		return CompleteRequest(Irp, STATUS_UNSUCCESSFUL);

	// Stall the request queue and wait for the current IRP (if any) to finish

	if (pdx->dqReadWrite)
		{						// check request queue
		StallRequests(pdx->dqReadWrite);
		WaitForCurrentIrp(pdx->dqReadWrite);
		}						// check request queue
 	
	pdx->state = PENDINGSTOP;
	return DefaultPnpHandler(pdx, Irp);
	}							// HandleQueryStop

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleRemoveDevice(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleRemoveDevice
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_REMOVE_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	// Cancel any queued requests and start rejecting new ones

	if (pdx->dqReadWrite)
		AbortRequests(pdx->dqReadWrite, STATUS_DELETE_PENDING);
	AbortPendingIoctls(pdx, STATUS_DELETE_PENDING);

	// Disable all device interfaces that were registered through us. This
	// triggers PnP notifications that will allow apps to close their handles.

	DeregisterAllInterfaces(pdx);

	// Release I/O resources

	CallStopDevice(pdx);

	KdPrint(("%s - To REMOVED from %s\n", pdx->DebugName, statenames[pdx->state]));
	pdx->state = REMOVED;

	// Let lower-level drivers handle this request. Ignore whatever
	// result eventuates.

	NTSTATUS status = DefaultPnpHandler(pdx, Irp);

	// Wait for all claims against this device to vanish before removing
	// the device object
	
	if (pdx->RemoveLock)
		IoReleaseRemoveLockAndWait(pdx->RemoveLock, Irp);

	// Remove the device object

	CallRemoveDevice(pdx);

	return status;				// lower-level completed IoStatus already
	}							// HandleRemoveDevice

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleStartDevice(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleStartDevice
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_START_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	NTSTATUS status = ForwardAndWait(pdx, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	PCM_PARTIAL_RESOURCE_LIST raw;
	if (stack->Parameters.StartDevice.AllocatedResources)
		raw = &stack->Parameters.StartDevice.AllocatedResources->List[0].PartialResourceList;
	else
		raw = NULL;

	PCM_PARTIAL_RESOURCE_LIST translated;
	if (stack->Parameters.StartDevice.AllocatedResourcesTranslated)
		translated = &stack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList;
	else
		translated = NULL;

#if DBG
	if (raw)
		{
		KdPrint(("%s - Resources:\n", pdx->DebugName));
		ShowResources(raw);
		}
	if (translated)
		{
		KdPrint(("%s - Translated Resources:\n", pdx->DebugName));
		ShowResources(translated);
		}
#endif // DBG

	status = (*pdx->StartDevice)(pdx->DeviceObject, raw, translated); 

	if (NT_SUCCESS(status))
		{						// started okay
		KdPrint(("%s - To WORKING from %s\n", pdx->DebugName, statenames[pdx->state]));

		pdx->HardwareWorking = TRUE;

		// If idle detection constants were saved in the registry, register
		// this device for idle detection

		POWERINFO pi;
		if (NT_SUCCESS(GetPowerInfoFromRegistry(pdx, &pi)))
			ImplementPowerPolicy(pdx, &pi);

		// Enable all registered device interfaces

		EnableAllInterfaces(pdx, TRUE);

		// Release any stalled IRPs

		pdx->state = WORKING;
		if (pdx->dqReadWrite)
			{					// restart queue
			AllowRequests(pdx->dqReadWrite); // in case we got a bogus STOP
			RestartRequests(pdx->dqReadWrite, pdx->DeviceObject);
			}					// restart queue

		// If system wakeup is enabled, start a wait-wake IRP

		GenericWakeupControl(pdx, ManageWaitWake);
		}						// started okay

	return CompleteRequest(Irp, status);
	}							// HandleStartDevice

///////////////////////////////////////////////////////////////////////////////	

NTSTATUS HandleStopDevice(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleStopDevice
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_STOP_DEVICE);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	// We're supposed to always get a query before we're stopped, so
	// we should already be in the PENDINGSTOP state. There's a Win98 bug that
	// can sometimes cause us to get a STOP instead of a REMOVE, in which case
	// we should start rejecting IRPs

	if (pdx->state != PENDINGSTOP)
		{						// no previous query
		KdPrint(("%s - STOP with no previous QUERY_STOP!\n", pdx->DebugName));
		if (pdx->dqReadWrite)
			AbortRequests(pdx->dqReadWrite, STATUS_DELETE_PENDING);
		AbortPendingIoctls(pdx, STATUS_DELETE_PENDING);
		}						// no previous query

	CallStopDevice(pdx);
	KdPrint(("%s - To STOPPED from %s\n", pdx->DebugName, statenames[pdx->state]));
	pdx->state = STOPPED;
	return DefaultPnpHandler(pdx, Irp);
	}							// HandleStopDevice

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleSurpriseRemoval(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleSurpriseRemoval
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_SURPRISE_REMOVAL);
	Irp->IoStatus.Status = STATUS_SUCCESS;	// flag that we handled this IRP

	if (pdx->dqReadWrite)
		AbortRequests(pdx->dqReadWrite, STATUS_DELETE_PENDING);
	AbortPendingIoctls(pdx, STATUS_DELETE_PENDING);

	KdPrint(("%s - To SURPRISEREMOVED from %s\n", pdx->DebugName, statenames[pdx->state]));
	pdx->state = SURPRISEREMOVED;

	EnableAllInterfaces(pdx, FALSE);	// this triggers notifications so apps can close their handles
	CallStopDevice(pdx);
	return DefaultPnpHandler(pdx, Irp);
	}							// HandleSurpriseRemoval

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleUsageNotification(PGENERIC_EXTENSION pdx, PIRP Irp)
	{							// HandleUsageNotification
	ASSERT(IoGetCurrentIrpStackLocation(Irp)->MinorFunction == IRP_MN_DEVICE_USAGE_NOTIFICATION);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	DEVICE_USAGE_NOTIFICATION_TYPE type = stack->Parameters.UsageNotification.Type;
	BOOLEAN inpath = stack->Parameters.UsageNotification.InPath;

	switch (type)
		{						// switch on usage type

	case DeviceUsageTypeHibernation:
		if (!(pdx->Flags & GENERIC_USAGE_HIBERNATE))
			return CompleteRequest(Irp, STATUS_UNSUCCESSFUL);

		AdjustSpecialFileCounter(pdx, inpath, &pdx->nhibernatefiles);
		Irp->IoStatus.Status = STATUS_SUCCESS;
		break;

	case DeviceUsageTypePaging:
		{						// DeviceUsageTypePaging
		if (!(pdx->Flags & GENERIC_USAGE_PAGING))
			return CompleteRequest(Irp, STATUS_UNSUCCESSFUL);

		AdjustSpecialFileCounter(pdx, inpath, &pdx->npagefiles);

		// Adjust the power-pagable flag too. (Per AdrianO) we must be careful not to
		// have a non-paged power handler sitting on top of a paged handler, so we
		// only clear DO_POWER_PAGABLE in our completion routine.
		
		PDEVICE_OBJECT fdo = pdx->DeviceObject;
		if (pdx->npagefiles == 0)
			{					// resume paging
			if (!(fdo->Flags & DO_POWER_INRUSH))
				fdo->Flags |= DO_POWER_PAGABLE;
			}					// resume paging

		// TODO Deal with paging of Read, Write, Control requests in minidriver

		Irp->IoStatus.Status = STATUS_SUCCESS;
		break;
		}						// DeviceUsageTypePaging

	case DeviceUsageTypeDumpFile:
		if (!(pdx->Flags & GENERIC_USAGE_DUMP))
			return CompleteRequest(Irp, STATUS_UNSUCCESSFUL);

		AdjustSpecialFileCounter(pdx, inpath, &pdx->ndumpfiles);
		Irp->IoStatus.Status = STATUS_SUCCESS;
		break;
		}						// switch on usage type

	// Install completion routine so we can recover from a failure and so we can
	// clear DO_POWER_PAGABLE at the right time.
	
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnNotificationComplete, pdx, TRUE, TRUE, TRUE);
	IoCopyCurrentIrpStackLocationToNext(Irp);
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// HandleUsageNotification

///////////////////////////////////////////////////////////////////////////////	

NTSTATUS OnNotificationComplete(PDEVICE_OBJECT fdo, PIRP Irp, PGENERIC_EXTENSION pdx)
	{							// OnNotificationComplete

	if (Irp->PendingReturned)
		IoMarkIrpPending(Irp);

	// If the notification succeeded, and if we're on the path for paging files,
	// be sure we start getting power IRPs at DISPATCH_LEVEL.

	if (NT_SUCCESS(Irp->IoStatus.Status))
		{						// notification succeeded
		if (pdx->npagefiles)
			fdo->Flags &= ~DO_POWER_PAGABLE;
		return STATUS_SUCCESS;
		}						// notification succeeded

	// Somebody underneath us failed this usage notification, so undo the steps we
	// took in the dispatch routine. Notice how we reverse the sense of "inpath" in
	// the following calls to AdjustSpecialFileCounter.

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	DEVICE_USAGE_NOTIFICATION_TYPE type = stack->Parameters.UsageNotification.Type;
	BOOLEAN inpath = stack->Parameters.UsageNotification.InPath;

	switch (type)
		{						// switch on usage type

	case DeviceUsageTypeHibernation:
		AdjustSpecialFileCounter(pdx, !inpath, &pdx->nhibernatefiles);
		break;

	case DeviceUsageTypePaging:
		{						// DeviceUsageTypePaging
		AdjustSpecialFileCounter(pdx, !inpath, &pdx->npagefiles);
		if (pdx->npagefiles == 0)
			{					// resume paging
			if (!(fdo->Flags & DO_POWER_INRUSH))
				fdo->Flags |= DO_POWER_PAGABLE;
			}					// resume paging
		else
			fdo->Flags &= ~DO_POWER_PAGABLE;
		break;
		}						// DeviceUsageTypePaging

	case DeviceUsageTypeDumpFile:
		AdjustSpecialFileCounter(pdx, !inpath, &pdx->ndumpfiles);
		break;
		}						// switch on usage type

	return STATUS_SUCCESS;
	}							// OnNotificationComplete

///////////////////////////////////////////////////////////////////////////////	

#if DBG

VOID ShowResources(IN PCM_PARTIAL_RESOURCE_LIST list)
	{							// ShowResources
	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = list->PartialDescriptors;
	ULONG nres = list->Count;
	ULONG i;

	for (i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		ULONG type = resource->Type;

		static char* name[] = {
			"CmResourceTypeNull",
			"CmResourceTypePort",
			"CmResourceTypeInterrupt",
			"CmResourceTypeMemory",
			"CmResourceTypeDma",
			"CmResourceTypeDeviceSpecific",
			"CmResourceTypeBusNumber",
			"CmResourceTypeDevicePrivate",
			"CmResourceTypeAssignedResource",
			"CmResourceTypeSubAllocateFrom",
			};

		KdPrint(("    type %s", type < arraysize(name) ? name[type] : "unknown"));

		switch (type)
			{					// select on resource type
		case CmResourceTypePort:
		case CmResourceTypeMemory:
			KdPrint((" start %8X%8.8lX length %X\n",
				resource->u.Port.Start.HighPart, resource->u.Port.Start.LowPart,
				resource->u.Port.Length));
			break;
		
		case CmResourceTypeInterrupt:
			KdPrint(("  level %X, vector %X, affinity %X\n",
				resource->u.Interrupt.Level, resource->u.Interrupt.Vector,
				resource->u.Interrupt.Affinity));
			break;
	
		case CmResourceTypeDma:
			KdPrint(("  channel %d, port %X\n",
				resource->u.Dma.Channel, resource->u.Dma.Port));
			}					// select on resource type
		}						// for each resource
	}							// ShowResources

#endif // DBG

