// Windows Management Instrumentation handlers for wmi42 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

#include <initguid.h>
#include <wdmguid.h>
#include "guids.h"

NTSTATUS DefaultWmiHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleQueryAllData(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleQueryInstance(IN PDEVICE_OBJECT fdo, IN PIRP Irp);
NTSTATUS HandleWmiReginfo(IN PDEVICE_OBJECT fdo, IN PIRP Irp);

class CRegInfo
{								// class CRegInfo
public:
	CRegInfo(PUCHAR base, ULONG size);

	void NewInfo(PCWSTR drivername, PCWSTR resname, ULONG size);
	void NewDataBlock(const GUID* guid, PDEVICE_OBJECT pdo);
	ULONG Data(PCWSTR s);
	ULONG Data(PVOID p);

	PUCHAR m_base;				// base address of buffer
	ULONG m_size;				// size of structure
	ULONG m_info;				// where next info field goes (increases)
	ULONG m_data;				// where next data field goes (decreases)
	PWMIREGINFO m_current;		// current WMIREGINFO header
	ULONG m_cursize;			// size of current WMIREGINFO (incl all data)
};								// class CRegInfo
									  
///////////////////////////////////////////////////////////////////////////////

NTSTATUS DispatchWmi(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DispatchWmi
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ASSERT(stack->MajorFunction == IRP_MJ_SYSTEM_CONTROL);

	static NTSTATUS (*fcntab[])(IN PDEVICE_OBJECT fdo, IN PIRP Irp) = {
		HandleQueryAllData,		// IRP_MN_QUERY_ALL_DATA
		HandleQueryInstance,	// IRP_MN_QUERY_SINGLE_INSTANCE
		DefaultWmiHandler,		// IRP_MN_CHANGE_SINGLE_INSTANCE
		DefaultWmiHandler,		// IRP_MN_CHANGE_SINGLE_ITEM
		DefaultWmiHandler,		// IRP_MN_ENABLE_EVENTS
		DefaultWmiHandler,		// IRP_MN_DISABLE_EVENTS
		DefaultWmiHandler,		// IRP_MN_ENABLE_COLLECTION
		DefaultWmiHandler,		// IRP_MN_DISABLE_COLLECTION
		HandleWmiReginfo,		// IRP_MN_REGINFO
		DefaultWmiHandler,		// IRP_MN_EXECUTE_METHOD
		};

	ULONG fcn = stack->MinorFunction;

#if DBG
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

	// If the provider id in the IRP doesn't match ours, pass the request along. (Device
	// drivers use the address of their device objects as provider IDs). Also pass
	// the IRP along if we don't know how to handle this minor function because it
	// was defined in a later DDK than we built with.

	if (fcn >= arraysize(fcntab) || fdo != (PDEVICE_OBJECT) stack->Parameters.WMI.ProviderId)
		{						// unknown function
		status = DefaultWmiHandler(fdo, Irp); // some function we don't know about
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return status;
		}						// unknown function

	status = (*fcntab[fcn])(fdo, Irp);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status;
	}							// DispatchWmi

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NTSTATUS DefaultWmiHandler(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// DefaultWmiHandler
	IoSkipCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// DefaultWmiHandler

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryAllData(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// HandleQueryAllData
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ASSERT(stack->MajorFunction == IRP_MJ_SYSTEM_CONTROL);
	ASSERT(stack->MinorFunction == IRP_MN_QUERY_ALL_DATA);
	ULONG bufsize = stack->Parameters.WMI.BufferSize;
	PWNODE_ALL_DATA buffer = (PWNODE_ALL_DATA) stack->Parameters.WMI.Buffer;

	// See if we're being asked about a data block we understand

	if (*(LPGUID) stack->Parameters.WMI.DataPath != GUID_WMI42_SCHEMA)
		return CompleteRequest(Irp, STATUS_WMI_GUID_NOT_FOUND, 0);

	ASSERT(buffer->WnodeHeader.Flags & WNODE_FLAG_STATIC_INSTANCE_NAMES);

	// Verify that the output buffer is large enough to hold the data we're going
	// to return

	ULONG need = FIELD_OFFSET(WNODE_ALL_DATA, OffsetInstanceNameOffsets); // size of basic structure
	need += sizeof(ULONG);		// size of FixedInstanceSize member
	need = (need + 7) & ~7;		// round up to quadword boundary
	ULONG dataoffset = need;	// this is where data will begin
	need += sizeof(ULONG);		// size of all the data blocks put together

	if (bufsize < need)
		return CompleteRequest(Irp, STATUS_BUFFER_TOO_SMALL, need);

	// Fill in the data buffer with the value of a single instance of a fixed-size
	// data block

	buffer->WnodeHeader.BufferSize = need;
	buffer->WnodeHeader.Flags |= WNODE_FLAG_FIXED_INSTANCE_SIZE;
	buffer->DataBlockOffset = dataoffset;
	buffer->InstanceCount = 1;
	buffer->OffsetInstanceNameOffsets = 0; // no instance names
	buffer->FixedInstanceSize = sizeof(ULONG);

	*(PULONG) ((PUCHAR) buffer + dataoffset) = 42;	// our data value

	return CompleteRequest(Irp, STATUS_SUCCESS, need);
	}							// HandleQueryAllData

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleQueryInstance(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// HandleQueryInstance
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ASSERT(stack->MajorFunction == IRP_MJ_SYSTEM_CONTROL);
	ASSERT(stack->MinorFunction == IRP_MN_QUERY_SINGLE_INSTANCE);
	ULONG bufsize = stack->Parameters.WMI.BufferSize;
	PWNODE_SINGLE_INSTANCE buffer = (PWNODE_SINGLE_INSTANCE) stack->Parameters.WMI.Buffer;

	// See if we're being asked about a data block we understand

	if (*(LPGUID) stack->Parameters.WMI.DataPath != GUID_WMI42_SCHEMA)
		return CompleteRequest(Irp, STATUS_WMI_GUID_NOT_FOUND, 0);

	ASSERT(buffer->WnodeHeader.Flags & WNODE_FLAG_STATIC_INSTANCE_NAMES);
	if (buffer->InstanceIndex != 0)
		return CompleteRequest(Irp, STATUS_WMI_INSTANCE_NOT_FOUND, 0);

	// Verify that the output buffer is large enough to hold the data we're going
	// to return

	ULONG need = buffer->DataBlockOffset + sizeof(ULONG);
	if (bufsize < need)
		return CompleteRequest(Irp, STATUS_BUFFER_TOO_SMALL, need);

	// Fill in the data block

	buffer->WnodeHeader.BufferSize = need;
	buffer->OffsetInstanceName = 0; // no instance name
	buffer->SizeDataBlock = sizeof(ULONG);

	*(PULONG) ((PUCHAR) buffer + buffer->DataBlockOffset) = pdx->TheAnswer;	// our data value

	return CompleteRequest(Irp, STATUS_SUCCESS, need);
	}							// HandleQueryInstance

///////////////////////////////////////////////////////////////////////////////

NTSTATUS HandleWmiReginfo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// HandleWmiReginfo
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ASSERT(stack->MajorFunction == IRP_MJ_SYSTEM_CONTROL);
	ASSERT(stack->MinorFunction == IRP_MN_REGINFO);
	ULONG bufsize = stack->Parameters.WMI.BufferSize;
	PUCHAR buffer = (PUCHAR) stack->Parameters.WMI.Buffer;

	if ((ULONG) stack->Parameters.WMI.DataPath != WMIREGISTER)
		return CompleteRequest(Irp, STATUS_SUCCESS, 0);

	// Calculate the size needed for our registration info
	
	ULONG need = sizeof(WMIREGINFO);	// base size of structure

	static WCHAR resname[] = L"MofResource"; // name of schema
	need += sizeof(resname) + sizeof(WCHAR); // name plus count
	need += servkey.Length + sizeof(WCHAR); // ditto
	need += sizeof(WMIREGGUID); // guid info

	// Make sure enough buffer space was provided.

	if (bufsize < need)
		{						// buffer too small
		ASSERT(bufsize >= sizeof(ULONG)); // must be at least this big!
		*(PULONG) buffer = need;
		return CompleteRequest(Irp, STATUS_BUFFER_TOO_SMALL, sizeof(ULONG));
		}						// buffer too small

	// Build the registration information structure

	CRegInfo r(buffer, need);
	r.NewInfo(servkey.Buffer, resname, need);
	r.NewDataBlock(&GUID_WMI42_SCHEMA, pdx->Pdo);
	
	return CompleteRequest(Irp, STATUS_SUCCESS, need);
	}							// HandleWmiReginfo

///////////////////////////////////////////////////////////////////////////////

void WmiInitialize(PDEVICE_OBJECT fdo)
	{							// WmiInitialize
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status = IoWMIRegistrationControl(fdo, WMIREG_ACTION_REGISTER);
	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - IoWMIRegistrationControl failed - %X\n", status));
	}							// WmiInitialize

///////////////////////////////////////////////////////////////////////////////

void WmiTerminate(PDEVICE_OBJECT fdo)
	{							// WmiTerminate
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	IoWMIRegistrationControl(fdo, WMIREG_ACTION_DEREGISTER);
	}							// WmiTerminate

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CRegInfo::CRegInfo(PUCHAR base, ULONG size)
	{							// CRegInfo::CRegInfo
	m_base = base;
	m_size = size;
	m_info = 0;
	m_data = 0;
	m_current = NULL;
	}							// CRegInfo::CRegInfo

///////////////////////////////////////////////////////////////////////////////

void CRegInfo::NewInfo(PCWSTR drivername, PCWSTR resname, ULONG size)
	{							// CRegInfo::NewInfo
	if (m_current)
		{						// we follow another info structure
		m_info = ((PUCHAR) m_current - m_base) + m_cursize;
		m_current->NextWmiRegInfo = m_info;
		}						// we follow another info structure

	ASSERT(m_info + size <= m_size);
	m_data = m_info + m_size;	// where data for this info structure will go
	
	PWMIREGINFO p = (PWMIREGINFO) (m_base + m_info);

	p->BufferSize = size;
	p->NextWmiRegInfo = 0;
	p->RegistryPath = Data(drivername);
	p->MofResourceName = Data(resname);
	p->GuidCount = 0;

	m_info += sizeof(WMIREGINFO);
	m_current = p;
	m_cursize = size;
	}							// CRegInfo::NewInfo

///////////////////////////////////////////////////////////////////////////////

void CRegInfo::NewDataBlock(const GUID* guid, PDEVICE_OBJECT pdo)
	{							// CRegInfo::NewDataBlock
	ASSERT(m_info + sizeof(WMIREGGUID) < m_data);
	ASSERT(m_current);
	PWMIREGGUID p = &m_current->WmiRegGuid[m_current->GuidCount++];
	m_info += sizeof(WMIREGGUID);

	p->Guid = *guid;
	p->Flags = WMIREG_FLAG_INSTANCE_PDO;
	p->InstanceCount = 1;
	p->Pdo = (ULONG_PTR) pdo;
	}							// CRegInfo::NewDataBlock

///////////////////////////////////////////////////////////////////////////////

ULONG CRegInfo::Data(PCWSTR s)
	{							// CRegInfo::Data
	ULONG len = wcslen(s);
	ASSERT(m_info + (len + 1) * sizeof(WCHAR) <= m_data);
	m_data -= (len + 1) * sizeof(WCHAR);
	PWSTR t = (PWSTR) (m_base + m_data);
	*t++ = (USHORT) (len + 1) * sizeof(WCHAR); // length is in bytes, includes the count
	RtlCopyBytes(t, s, len * sizeof(WCHAR));
	return m_data;
	}							// CRegInfo::Data

ULONG CRegInfo::Data(PVOID p)
	{							// CRegInfo::Data
	ULONG len = sizeof(p);
	ASSERT(m_info + len <= m_data);
	m_data -= len;
	*(PVOID*) (m_base + m_data) = p;
	return m_data;
	}							// CRegInfo::Data
