// PNPMON.CPP -- VxD version of PNPMON.SYS for Win98
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdvxd.h"
#include "..\sys\ioctls.h"

///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:4035)

BOOL _VWIN32_SetWin32Event(PVOID hEvent)
	{
	_asm mov eax, hEvent
	VMMCall(_VWIN32_SetWin32Event)
	}

#pragma warning(default:4035)

///////////////////////////////////////////////////////////////////////////////

typedef struct _REG_RECORD {
	GUID Guid;
	PVOID NotificationEntry;
	PVOID Event;
	} REG_RECORD, *PREG_RECORD;

typedef struct _EVENT_RECORD {
	GETEVENT_PARAMS params;
	} EVENT_RECORD, *PEVENT_RECORD;

///////////////////////////////////////////////////////////////////////////////

DWORD Register(PREGISTER_PARAMS p);
DWORD Deregister(PUNREGISTER_PARAMS p);
VOID DeregisterAll();
NTSTATUS OnPnpNotify(PDEVICE_INTERFACE_CHANGE_NOTIFICATION p, PREG_RECORD reg);
DWORD GetEvent(PGETEVENT_PARAMS p);

VMMLIST RegRecordList = NULL;
VMMLIST EventList = NULL;

///////////////////////////////////////////////////////////////////////////////

SYSCTL BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	RegRecordList = List_Create(0, sizeof(REG_RECORD));
	EventList = List_Create(LF_ASYNC, sizeof(EVENT_RECORD));
	return TRUE;
	}							// OnSysDynamicDeviceInit

///////////////////////////////////////////////////////////////////////////////

SYSCTL BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	DeregisterAll();
	List_Destroy(EventList);
	List_Destroy(RegRecordList);
	return TRUE;
	}							// OnSysDynamicDeviceExit

///////////////////////////////////////////////////////////////////////////////

SYSCTL DWORD OnW32DeviceIoControl(PDIOCPARAMETERS p)
	{							// OnW32DeviceIoControl
	DWORD status = 0;
	DWORD info = 0;

	DWORD cbin = p->cbInBuffer;
	DWORD cbout = p->cbOutBuffer;
	DWORD code = p->dwIoControlCode;

	switch (code)
		{						// process control operation
	case DIOC_OPEN:
	case DIOC_CLOSEHANDLE:
		break;

	case IOCTL_REGISTER:
		if (cbin < sizeof(REGISTER_PARAMS))
			{
			status = ERROR_INVALID_PARAMETER;
			break;
			}
		status = Register((PREGISTER_PARAMS) p->lpvInBuffer);
		break;

	case IOCTL_DEREGISTER:
		if (cbin < sizeof(UNREGISTER_PARAMS))
			{
			status = ERROR_INVALID_PARAMETER;
			break;
			}
		status = Deregister((PUNREGISTER_PARAMS) p->lpvInBuffer);
		break;

	case IOCTL_GETEVENT:
		if (cbout < sizeof(GETEVENT_PARAMS))
			{
			status = ERROR_INVALID_PARAMETER;
			break;
			}
		status = GetEvent((PGETEVENT_PARAMS) p->lpvOutBuffer);
		break;

	default:
		ASSERT(FALSE);
		status = ERROR_INVALID_FUNCTION;
		}						// process control operation

	if (p->lpcbBytesReturned)
		*(PDWORD) p->lpcbBytesReturned = info;
	return status;
	}							// OnW32DeviceIoControl

///////////////////////////////////////////////////////////////////////////////

DWORD Register(PREGISTER_PARAMS p)
	{							// Register
	PREG_RECORD reg = (PREG_RECORD) List_Allocate(RegRecordList);
	if (!reg)
		return ERROR_NOT_ENOUGH_MEMORY;
	memset(reg, 0, sizeof(REG_RECORD));

	reg->Event = VWIN32OpenVxDHandle((ULONG) p->hevent, OPENVXD_TYPE_EVENT);
	reg->Guid = p->guid;

	NTSTATUS status = IoRegisterPlugPlayNotification(EventCategoryDeviceInterfaceChange,
		PNPNOTIFY_DEVICE_INTERFACE_INCLUDE_EXISTING_INTERFACES,
		&p->guid, NULL, (PDRIVER_NOTIFICATION_CALLBACK_ROUTINE) OnPnpNotify, reg, &reg->NotificationEntry);

	if (!NT_SUCCESS(status))
		{
		Debug_Printf("PNPMON - IoRegisterPlugPlayNotification failed - %X\n", status);
		List_Deallocate(RegRecordList, reg);
		return ERROR_CRC;
		}

	List_Attach_Tail(RegRecordList, reg);
	return 0;
	}							// Register

///////////////////////////////////////////////////////////////////////////////

DWORD Deregister(PUNREGISTER_PARAMS p)
	{							// Deregister
	DWORD status = 0;
	PREG_RECORD reg;

	for (reg = (PREG_RECORD) List_Get_First(RegRecordList); reg; )
		{						// for each list element
		PREG_RECORD next = (PREG_RECORD) List_Get_Next(RegRecordList, reg);
		if (memcmp(&reg->Guid, &p->guid, sizeof(GUID)) == 0)
			{					// found a registration record
			List_Remove(RegRecordList, reg);
			IoUnregisterPlugPlayNotification(reg->NotificationEntry);
			List_Deallocate(RegRecordList, reg);
			}					// found a registration record
		reg = next;
		}						// for each list element
	return status;
	}							// Deregister

///////////////////////////////////////////////////////////////////////////////

VOID DeregisterAll()
	{							// DeregisterAll
	PREG_RECORD reg;
	while ((reg = (PREG_RECORD) List_Remove_First(RegRecordList)))
		{						// deregister all notifications
		IoUnregisterPlugPlayNotification(reg->NotificationEntry);
		List_Deallocate(RegRecordList, reg);
		}						// deregister all notifications
	}							// DeregisterAll

///////////////////////////////////////////////////////////////////////////////

VOID __declspec(naked) __cdecl EventProc()
	{							// EventProc
	_asm mov eax, edx
	VMMCall(_VWIN32_SetWin32Event)
	_asm ret
	}							// EventProc

NTSTATUS OnPnpNotify(PDEVICE_INTERFACE_CHANGE_NOTIFICATION p, PREG_RECORD reg)
	{							// OnPnpNotify

	_asm pushfd
	_asm cli
	PEVENT_RECORD evrec = (PEVENT_RECORD) List_Allocate(EventList);
	_asm popfd

	memset(evrec, 0, sizeof(EVENT_RECORD));

	evrec->params.guid = p->InterfaceClassGuid;
	evrec->params.event = p->Event;
	memcpy(evrec->params.linkname, p->SymbolicLinkName->Buffer, p->SymbolicLinkName->Length);
	evrec->params.linkname[p->SymbolicLinkName->Length/2] = 0;

	_asm pushfd
	_asm cli
	List_Attach_Tail(EventList, evrec);
	_asm popfd

	HVM hvmSystem = Get_Sys_VM_Handle();	
	if (Get_Cur_VM_Handle() == hvmSystem)
		_VWIN32_SetWin32Event(reg->Event);
	else
		Call_Restricted_Event(0, hvmSystem, 0, (ULONG) reg->Event, (VMM_EVENT_HANDLER) EventProc, 0);

	return STATUS_SUCCESS;
	}							// OnPnpNotify

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG

DWORD GetEvent(PGETEVENT_PARAMS p)
	{							// GetEvent
	PEVENT_RECORD evrec;
	_asm pushfd
	_asm cli
	evrec = (PEVENT_RECORD) List_Remove_First(EventList);
	_asm popfd

	if (!evrec)
		return ERROR_NO_MORE_ITEMS;

	*p = evrec->params;
	
	_asm pushfd
	_asm cli
	List_Deallocate(EventList, evrec);
	_asm popfd

	return 0;
	}							// GetEvent

