// Control.cpp -- IOCTL handlers for pnpmon driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include <initguid.h>
#include <wdmguid.h>
#include "driver.h"
#include "ioctls.h"

NTSTATUS Register(PDEVICE_EXTENSION pdx, PREGISTER_PARAMS p);
NTSTATUS Deregister(PDEVICE_EXTENSION pdx, PUNREGISTER_PARAMS p);
VOID DeregisterAll(PDEVICE_EXTENSION pdx);
NTSTATUS OnPnpNotify(PPLUGPLAY_NOTIFICATION_HEADER p, PREG_RECORD reg);
VOID KillRegRecord(PREG_RECORD reg);
void SubscribeForTargetNotifications(PDEVICE_INTERFACE_CHANGE_NOTIFICATION q, PREG_RECORD reg);

typedef struct _SUBSCRIBE_CALLBACK_CONTEXT {
	PIO_WORKITEM item;
	PREG_RECORD reg;
	WCHAR name[1];
	} SUBSCRIBE_CALLBACK_CONTEXT, *PSUBSCRIBE_CALLBACK_CONTEXT;

void SubscribeCallback(PDEVICE_OBJECT DeviceObject, PSUBSCRIBE_CALLBACK_CONTEXT context);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchControl
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = STATUS_SUCCESS;
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
		{						// process request

	case IOCTL_REGISTER:				// code == 0x800
		{						// IOCTL_REGISTER
		if (cbin < sizeof(REGISTER_PARAMS))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}
		status = Register(pdx, (REGISTER_PARAMS*) Irp->AssociatedIrp.SystemBuffer);
		break;
		}						// IOCTL_REGISTER

	case IOCTL_DEREGISTER:				// code == 0x801
		{						// IOCTL_DEREGISTER
		if (cbin < sizeof(UNREGISTER_PARAMS))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}
		status = Deregister(pdx, (UNREGISTER_PARAMS*) Irp->AssociatedIrp.SystemBuffer);
		break;
		}						// IOCTL_DEREGISTER

	case IOCTL_GETEVENT:				// code == 0x802
		{						// IOCTL_GETEVENT
		if (cbout < sizeof(GETEVENT_PARAMS))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		PLIST_ENTRY list = ExInterlockedRemoveHeadList(&pdx->events, &pdx->eventlock);
		if (!list)
			{
			status = STATUS_NO_MORE_ENTRIES;
			break;
			}

		PEVENT_RECORD evrec = CONTAINING_RECORD(list, EVENT_RECORD, ListEntry);
		*(PGETEVENT_PARAMS) Irp->AssociatedIrp.SystemBuffer = evrec->params;
		info = sizeof(GETEVENT_PARAMS);
		ExFreePool(evrec);
		break;
		}						// IOCTL_GETEVENT

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	return CompleteRequest(Irp, status, info);
	}							// DispatchControl

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCreate
	PAGED_CODE();
	KdPrint((DRIVERNAME " - "
		"IRP_MJ_CREATE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	
	NTSTATUS status = STATUS_SUCCESS;
	if (InterlockedIncrement(&pdx->handles) > 1)
		{						// too many opens
		InterlockedDecrement(&pdx->handles);
		status = STATUS_ACCESS_DENIED;
		}						// too many opens

	return CompleteRequest(Irp, status, 0);
	}							// DispatchCreate

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchClose
	PAGED_CODE();
	KdPrint((DRIVERNAME " - "
		"IRP_MJ_CLOSE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	DeregisterAll(pdx);
	InterlockedDecrement(&pdx->handles);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS Register(PDEVICE_EXTENSION pdx, PREGISTER_PARAMS p)
	{							// Register
	NTSTATUS status;

	// Get a pointer to the event object we will set when notifications about
	// the specified GUID occur
	
	PKEVENT event;
	status = ObReferenceObjectByHandle(p->hevent, EVENT_MODIFY_STATE, *ExEventObjectType,
		KernelMode, (PVOID*) &event, NULL);

	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - ObReferenceObjectByHandle failed - %X\n", status));
		return status;
		}

	// Create an event registration structure

	PREG_RECORD reg = (PREG_RECORD) ExAllocatePool(NonPagedPool, sizeof(REG_RECORD));

	if (!reg)
		{
		KdPrint((DRIVERNAME " - unable to allocate %d bytes for registration record\n", sizeof(REG_RECORD)));
		ObDereferenceObject(event);
		return STATUS_INSUFFICIENT_RESOURCES;
		}

	RtlZeroMemory(reg, sizeof(REG_RECORD));
	reg->Event = event;
	reg->Guid = p->guid;
	reg->DeviceExtension = pdx;

	// Register for PnP notifications

	status = IoRegisterPlugPlayNotification(EventCategoryDeviceInterfaceChange,
		PNPNOTIFY_DEVICE_INTERFACE_INCLUDE_EXISTING_INTERFACES,
		&p->guid, pdx->DriverObject,
		(PDRIVER_NOTIFICATION_CALLBACK_ROUTINE) OnPnpNotify, reg, &reg->InterfaceNotificationEntry);
	
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - IoRegisterPlugPlayNotification failed - %X\n", status));
		ObDereferenceObject(event);
		ExFreePool(reg);
		return status;
		}

	// Put the registration record onto our list

	InsertTailList(&pdx->registered, &reg->ListEntry);
	return STATUS_SUCCESS;
	}							// Register

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS Deregister(PDEVICE_EXTENSION pdx, PUNREGISTER_PARAMS p)
	{							// Deregister
	PLIST_ENTRY list;
	NTSTATUS status = STATUS_SUCCESS;

	for (list = pdx->registered.Flink; list != &pdx->registered; )
		{						// for each list element
		PLIST_ENTRY next = list->Flink;
		PREG_RECORD reg = CONTAINING_RECORD(list, REG_RECORD, ListEntry);
		if (reg->Guid == p->guid)
			{					// found a registration record
			RemoveEntryList(list);
			KillRegRecord(reg);
			break;
			}					// found a registration record
		list = next;
		}						// for each list element

	return status;
	}							// Deregister

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DeregisterAll(PDEVICE_EXTENSION pdx)
	{							// DeregisterAll
	while (!IsListEmpty(&pdx->registered))
		{						// deregister all notifications
		PLIST_ENTRY next = RemoveHeadList(&pdx->registered);
		PREG_RECORD reg = CONTAINING_RECORD(next, REG_RECORD, ListEntry);
		KillRegRecord(reg);
		}						// deregister all notifications
	}							// DeregisterAll

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID KillRegRecord(PREG_RECORD reg)
	{							// KillRegRecord
	if (reg->InterfaceNotificationEntry)
		IoUnregisterPlugPlayNotification(reg->InterfaceNotificationEntry);
	reg->InterfaceNotificationEntry = NULL;

	if (reg->HandleNotificationEntry)
		IoUnregisterPlugPlayNotification(reg->HandleNotificationEntry);
	reg->HandleNotificationEntry = NULL;

	if (reg->TargetFileReferenced)
		ObDereferenceObject(reg->TargetFile);
	reg->TargetFileReferenced = FALSE;

	if (reg->Event)
		ObDereferenceObject(reg->Event);
	reg->Event = NULL;

	// Make sure we don't release the registration structure while a
	// work item is outstanding.

	if (reg->WorkItemCount == 0)
		ExFreePool(reg);
	else
		reg->DeferredRelease = TRUE;
	}							// KillRegRecord

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS OnPnpNotify(PPLUGPLAY_NOTIFICATION_HEADER p, PREG_RECORD reg)
	{							// OnPnpNotify
	PAGED_CODE();
	NTSTATUS status;

	// Report the event

#if DBG

	char *msg;
	
	if (p->Event == GUID_DEVICE_INTERFACE_ARRIVAL)
		msg = "arrival";
	else if (p->Event == GUID_DEVICE_INTERFACE_REMOVAL)
		msg = "removal";
	else if (p->Event == GUID_TARGET_DEVICE_QUERY_REMOVE)
		msg = "target query remove";
	else if (p->Event == GUID_TARGET_DEVICE_REMOVE_CANCELLED)
		msg = "target remove cancelled";
	else if (p->Event == GUID_TARGET_DEVICE_REMOVE_COMPLETE)
		msg = "target remove complete";
	else 
		msg = "custom notification";

	KdPrint((DRIVERNAME " - PnP notification (%s event)\n", msg));

#endif // DBG

	// Create an event record for reporting back to the application

	PDEVICE_EXTENSION pdx = reg->DeviceExtension;
	
	PEVENT_RECORD evrec = (PEVENT_RECORD) ExAllocatePool(NonPagedPool, sizeof(EVENT_RECORD));
	if (!evrec)
		{
		KdPrint((DRIVERNAME " - can't allocate %d bytes for event record\n", sizeof(EVENT_RECORD)));
		return STATUS_SUCCESS;
		}
	RtlZeroMemory(evrec, sizeof(EVENT_RECORD));

	evrec->params.event = p->Event;

	if (p->Event == GUID_DEVICE_INTERFACE_ARRIVAL || p->Event == GUID_DEVICE_INTERFACE_REMOVAL)
		{						// interface notification
		PDEVICE_INTERFACE_CHANGE_NOTIFICATION q = (PDEVICE_INTERFACE_CHANGE_NOTIFICATION) p;
		evrec->params.guid = q->InterfaceClassGuid;

		// N.B.: Don't just rely on an ASSERT like the following one in a production
		// driver -- handle the case where the name is too long in the free build too!

		ASSERT(q->SymbolicLinkName->Length + 2 <= sizeof(reg->LinkName));
		memcpy(reg->LinkName, q->SymbolicLinkName->Buffer, q->SymbolicLinkName->Length);
		reg->LinkName[q->SymbolicLinkName->Length/2] = 0;
		wcscpy(evrec->params.linkname, reg->LinkName);

		// For an arrival notification, we want to register for target device change notifications. To
		// do this, we must get a pointer to a file object for the device. Doing *that* entails opening
		// the device, which might cause a deadlock if the target device performs blocking PnP operations.
		// Therefore, arrange to do the open in another thread by queuing a work item.

		if (p->Event == GUID_DEVICE_INTERFACE_ARRIVAL)
			SubscribeForTargetNotifications(q, reg);
		}						// interface notification

	else if (p->Event == GUID_TARGET_DEVICE_QUERY_REMOVE
		|| p->Event == GUID_TARGET_DEVICE_REMOVE_COMPLETE)
		{						// target device notification
		PTARGET_DEVICE_REMOVAL_NOTIFICATION q = (PTARGET_DEVICE_REMOVAL_NOTIFICATION) p;
		wcscpy(evrec->params.linkname, reg->LinkName);

		// You need to close the file object when the query arrives,
		// or else the removal will get cancelled. Makes the idea
		// of getting a remove complete seem kind of silly, eh?

		if (reg->TargetFileReferenced)
			{					// dereference target
			if (reg->HandleNotificationEntry)
				IoUnregisterPlugPlayNotification(reg->HandleNotificationEntry);
			reg->HandleNotificationEntry = NULL;
			ObDereferenceObject(reg->TargetFile);
			reg->TargetFile = NULL;
			reg->TargetFileReferenced = FALSE;
			}					// dereference target
		}						// target device notification

	else if (p->Event == GUID_TARGET_DEVICE_REMOVE_CANCELLED)
		{						// remove cancelled
		PTARGET_DEVICE_REMOVAL_NOTIFICATION q = (PTARGET_DEVICE_REMOVAL_NOTIFICATION) p;
		wcscpy(evrec->params.linkname, reg->LinkName);
		}						// remove cancelled

	else
		{						// custom notification
		PTARGET_DEVICE_CUSTOM_NOTIFICATION q = (PTARGET_DEVICE_CUSTOM_NOTIFICATION) p;
		ASSERT(q->FileObject == reg->TargetFile);
		wcscpy(evrec->params.linkname, reg->LinkName);
		evrec->params.guid = q->Event;
		ULONG datasize = q->Size - FIELD_OFFSET(TARGET_DEVICE_CUSTOM_NOTIFICATION, CustomDataBuffer);
		
		// Don't just rely on an ASSERT for a production driver -- make it work even
		// in the free build!

		ASSERT(datasize <= sizeof(evrec->params.data));
		memcpy(evrec->params.data, q->CustomDataBuffer, datasize);
		evrec->params.datasize = datasize;
		evrec->params.textoffset = q->NameBufferOffset;
		}						// custom notification

	ExInterlockedInsertTailList(&pdx->events, &evrec->ListEntry, &pdx->eventlock);

	KeSetEvent(reg->Event, IO_NO_INCREMENT, FALSE);

	return STATUS_SUCCESS;
	}							// OnPnpNotify

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

void SubscribeCallback(PDEVICE_OBJECT DeviceObject, PSUBSCRIBE_CALLBACK_CONTEXT context)
	{							// SubscribeCallback
	PREG_RECORD reg = context->reg;
	PDEVICE_EXTENSION pdx = reg->DeviceExtension;
	InterlockedDecrement(&reg->WorkItemCount);
	IoFreeWorkItem(context->item);

	if (reg->DeferredRelease)
		{						// no-one interested anymore
		KillRegRecord(reg);
		ExFreePool(context);
		return;
		}						// no-one interested anymore

	PDEVICE_OBJECT junk;
	UNICODE_STRING name;
	RtlInitUnicodeString(&name, context->name);
	NTSTATUS status = IoGetDeviceObjectPointer(&name, 0, &reg->TargetFile, &junk);
	if (NT_SUCCESS(status))
		{				// register for notifications
		reg->TargetFileReferenced = TRUE;
		status = IoRegisterPlugPlayNotification(EventCategoryTargetDeviceChange, 0,
			reg->TargetFile, pdx->DriverObject, (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE) OnPnpNotify,
			reg, &reg->HandleNotificationEntry);
		if (!NT_SUCCESS(status))
			{			// error registering
			KdPrint((DRIVERNAME " - IoRegisterPlugPlayNotification failed - %X\n", status));
			ObDereferenceObject(reg->TargetFile);
			reg->TargetFile = NULL;
			reg->TargetFileReferenced = FALSE;
			}			// error registering
		}				// register for notifications
	else
		KdPrint((DRIVERNAME " - IoGetDeviceObjectPointer failed - %X\n", status));

	ExFreePool(context);
	}							// SubscribeCallback

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

void SubscribeForTargetNotifications(PDEVICE_INTERFACE_CHANGE_NOTIFICATION q, PREG_RECORD reg)
	{							// SubscribeForTargetNotifications

	// Use IoAllocateWorkItem so our driver can't disappear from memory while
	// the work item is outstanding. Note that we don't have access to a remove lock
	// in this driver, so we can't just call IoAcquireRemoveLock.

	PIO_WORKITEM item = IoAllocateWorkItem(reg->DeviceExtension->DeviceObject);
	if (!item)
		return;

	ULONG size = sizeof(SUBSCRIBE_CALLBACK_CONTEXT) + q->SymbolicLinkName->Length;
	PSUBSCRIBE_CALLBACK_CONTEXT context = (PSUBSCRIBE_CALLBACK_CONTEXT) ExAllocatePool(NonPagedPool, size);
	if (!context)
		{
		IoFreeWorkItem(item);
		return;
		}

	RtlZeroMemory(context, size);

	context->reg = reg;
	context->item = item;
	RtlCopyMemory(context->name, q->SymbolicLinkName->Buffer, q->SymbolicLinkName->Length);

	InterlockedIncrement(&reg->WorkItemCount);

	IoQueueWorkItem(item, (PIO_WORKITEM_ROUTINE) SubscribeCallback, DelayedWorkQueue, context);
	}							// SubscribeForTargetNotifications


