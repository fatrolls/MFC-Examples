// WMI.CPP -- Windows Management Instrumentation handlers for wmiextra driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

#include <initguid.h>
#include <wdmguid.h>
#include "guids.h"

NTSTATUS QueryRegInfo(PDEVICE_OBJECT fdo, PULONG flags, PUNICODE_STRING instname, PUNICODE_STRING* regpath, PUNICODE_STRING resname, PDEVICE_OBJECT* pdo);
NTSTATUS QueryDataBlock(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG instcount, PULONG instlength, ULONG bufsize, PUCHAR buffer);
NTSTATUS SetDataBlock(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG bufsize, PUCHAR buffer);
NTSTATUS SetDataItem(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG id, ULONG bufsize, PUCHAR buffer);
NTSTATUS ExecuteMethod(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG id, ULONG cbInbuf, ULONG cbOutbuf, PUCHAR buffer);
NTSTATUS FunctionControl(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, WMIENABLEDISABLECONTROL fcn, BOOLEAN enable);

WMIGUIDREGINFO guidlist[] = {
	{&GUID_WMIEXTRA_EVENT, 1, WMIREG_FLAG_EVENT_ONLY_GUID},
	{&GUID_WMIEXTRA_EXPENSIVE, 1, WMIREG_FLAG_EXPENSIVE},
	{&GUID_WMIEXTRA_METHOD, 1, 0},
	{&GUID_POWER_DEVICE_ENABLE, 1, 0},
	{&GUID_POWER_DEVICE_TIMEOUTS, 1, 0},
	{&GUID_POWER_DEVICE_WAKE_ENABLE, 1, 0},
	};

#define INDEX_WMIEXTRA_EVENT		0
#define INDEX_WMIEXTRA_EXPENSIVE	1
#define INDEX_WMIEXTRA_METHOD		2
#define INDEX_POWER_ENABLE			3
#define INDEX_POWER_TIMEOUTS		4
#define INDEX_POWER_WAKE_ENABLE		5

WMILIB_CONTEXT libinfo = {
	arraysize(guidlist),		// GuidCount
	guidlist,					// GuidList
	QueryRegInfo,
	QueryDataBlock,
	SetDataBlock,
	SetDataItem,
	ExecuteMethod,
	FunctionControl,
	};
									  
///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchWmi(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DispatchWmi
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

#if DBG
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG fcn = stack->MinorFunction;

	static char* fcnname[] = {
		"IRP_MN_QUERY_ALL_DATA",
		"IRP_MN_QUERY_SINGLE_INSTANCE",
		"IRP_MN_CHANGE_SINGLE_INSTANCE",
		"IRP_MN_CHANGE_SINGLE_ITEM",
		"IRP_MN_ENABLE_EVENTS",
		"IRP_MN_DISABLE_EVENTS",
		"IRP_MN_ENABLE_COLLECTION",
		"IRP_MN_DISABLE_COLLECTION",
		"IRP_MN_REGINFO",
		"IRP_MN_EXECUTE_METHOD",
		};

	KdPrint((DRIVERNAME " - WMI Request (%s)\n", fcnname[fcn]));
#endif // DBG

	// Delegate processing to the WMILIB helper library

	SYSCTL_IRP_DISPOSITION disposition;
	status = WmiSystemControl(&libinfo, fdo, Irp, &disposition);

	switch (disposition)
		{						// finish handling IRP

	case IrpProcessed:
		break;

	case IrpNotCompleted:
		IoCompleteRequest(Irp, IO_NO_INCREMENT); // WMILIB already filled in IoStatus fields
		break;

	default:
	case IrpNotWmi:
		ASSERT(FALSE);

	case IrpForward:
		IoSkipCurrentIrpStackLocation(Irp);
		status = IoCallDriver(pdx->LowerDeviceObject, Irp);
		break;
		}						// finish handling IRP

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchWmi

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

void WmiInitialize(PDEVICE_OBJECT fdo)
	{							// WmiInitialize
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoWMIRegistrationControl(fdo, WMIREG_ACTION_REGISTER);
	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - IoWMIRegistrationControl failed - %X\n", status));
	}							// WmiInitialize

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

void WmiTerminate(PDEVICE_OBJECT fdo)
	{							// WmiTerminate
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	IoWMIRegistrationControl(fdo, WMIREG_ACTION_DEREGISTER);
	}							// WmiTerminate

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS QueryRegInfo(PDEVICE_OBJECT fdo, PULONG flags, PUNICODE_STRING instname, 
	PUNICODE_STRING* regpath, PUNICODE_STRING resname, PDEVICE_OBJECT* pdo)
	{							// QueryRegInfo
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	*flags = WMIREG_FLAG_INSTANCE_BASENAME;
	*regpath = &servkey;
	RtlInitUnicodeString(resname, L"MofResource");
	static WCHAR basename[] = L"WMIEXTRA";
	instname->Buffer = (PWCHAR) ExAllocatePool(PagedPool, sizeof(basename));
	if (!instname->Buffer)
		return STATUS_INSUFFICIENT_RESOURCES;
	instname->MaximumLength = sizeof(basename);
	instname->Length = sizeof(basename) - 2;
	RtlCopyMemory(instname->Buffer, basename, sizeof(basename));
	return STATUS_SUCCESS;
	}							// QueryRegInfo

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS QueryDataBlock(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, 
	ULONG instindex, ULONG instcount, PULONG instlength, ULONG bufavail, PUCHAR buffer)
	{							// QueryDataBlock
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ULONG bufsize = 0;
	NTSTATUS status = STATUS_SUCCESS;

	switch (guidindex)
		{						// provide indicated data

	case INDEX_WMIEXTRA_EXPENSIVE:
		{						// GUID_WMIEXTRA_EXPENSIVE
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}

		ASSERT(instcount == 1);
		ASSERT(pdx->expenable);

		bufsize = sizeof(ULONG);
		if (!instlength || bufavail < bufsize)
			status = STATUS_BUFFER_TOO_SMALL;
		else
			*(PULONG) buffer = 42;
		break;
		}						// GUID_WMIEXTRA_EXPENSIVE

	// We will be called to deliver the value of the method object even though it
	// doesn't really have a value

	case INDEX_WMIEXTRA_EVENT:
	case INDEX_WMIEXTRA_METHOD:
		bufsize = 0;
		break;

	// Standard power controls:

	case INDEX_POWER_ENABLE:
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}
		bufsize = sizeof(ULONG);
		if (!instlength || bufavail < bufsize)
			status = STATUS_BUFFER_TOO_SMALL;
		else
			*(PULONG) buffer = pdx->powerenable;
		break;

	case INDEX_POWER_WAKE_ENABLE:
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}
		bufsize = sizeof(ULONG);
		if (!instlength || bufavail < bufsize)
			status = STATUS_BUFFER_TOO_SMALL;
		else
			*(PULONG) buffer = pdx->wakeenable;
		break;

	default:
		status = STATUS_WMI_GUID_NOT_FOUND;
		}						// provide indicated data

	return WmiCompleteRequest(fdo, Irp, status, bufsize, IO_NO_INCREMENT);
	}							// QueryDataBlock

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS SetDataBlock(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG bufavail, PUCHAR buffer)
	{							// SetDataBlock
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;
	ULONG info = 0;

	switch (guidindex)
		{						// select data block

	case INDEX_POWER_ENABLE:
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}
		if (bufavail != sizeof(ULONG))
			{
			status = STATUS_INFO_LENGTH_MISMATCH;
			break;
			}
		pdx->powerenable = (BOOLEAN) *(PULONG) buffer;
		KdPrint((DRIVERNAME " - GUID_POWER_DEVICE_ENABLE = %c\n", pdx->powerenable));
		status = STATUS_SUCCESS;
		info = sizeof(ULONG);
		break;

	case INDEX_POWER_WAKE_ENABLE:
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}
		if (bufavail != sizeof(ULONG))
			{
			status = STATUS_INFO_LENGTH_MISMATCH;
			break;
			}
		pdx->wakeenable = (BOOLEAN) *(PULONG) buffer;
		KdPrint((DRIVERNAME " - GUID_POWER_DEVICE_WAKE_ENABLE = %c\n", pdx->wakeenable));
		status = STATUS_SUCCESS;
		info = sizeof(ULONG);
		break;

	default:
		status = STATUS_WMI_GUID_NOT_FOUND;
		break;
		}						// select data block

	return WmiCompleteRequest(fdo, Irp, status, info, IO_NO_INCREMENT);
	}							// SetDataBlock

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS SetDataItem(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG id, ULONG bufavail, PUCHAR buffer)
	{							// SetDataItem
	return WmiCompleteRequest(fdo, Irp, STATUS_INVALID_DEVICE_REQUEST, 0, IO_NO_INCREMENT);
	}							// SetDataItem

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ExecuteMethod(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, ULONG instindex, ULONG id, ULONG cbInbuf, ULONG cbOutbuf, PUCHAR buffer)
	{							// ExecuteMethod
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = STATUS_SUCCESS;
	ULONG bufused = 0;

	switch (guidindex)
		{						// process method call
	case 2:
		if (instindex != 0)
			{
			status = STATUS_WMI_INSTANCE_NOT_FOUND;
			break;
			}

		if (id != 1)
			{
			status = STATUS_WMI_ITEMID_NOT_FOUND;
			break;
			}
		
		bufused = sizeof(ULONG);
		if (cbOutbuf < bufused)
			{
			status = STATUS_BUFFER_TOO_SMALL;
			break;
			}

		(*(PULONG) buffer)++;	// return input value + 1
		break;

	default:
		status = STATUS_WMI_GUID_NOT_FOUND;
		break;
		}						// process method call

	return WmiCompleteRequest(fdo, Irp, status, bufused, IO_NO_INCREMENT);
	}							// ExecuteMethod

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS FunctionControl(PDEVICE_OBJECT fdo, PIRP Irp, ULONG guidindex, WMIENABLEDISABLECONTROL fcn, BOOLEAN enable)
	{							// FunctionControl
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = STATUS_SUCCESS;

	switch (guidindex)
		{						// process control operation
	case 0:
		if (fcn == WmiEventControl)
			pdx->evenable = enable;
		else
			status = STATUS_WMI_NOT_SUPPORTED;
		break;

	case 1:
		if (fcn == WmiDataBlockControl)
			pdx->expenable = enable;
		else
			status = STATUS_WMI_NOT_SUPPORTED;
		break;

	default:
		status = STATUS_WMI_GUID_NOT_FOUND;
		break;
		}						// process control operation

	return WmiCompleteRequest(fdo, Irp, status, 0, IO_NO_INCREMENT);
	}							// FunctionControl
