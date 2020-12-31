// DeviceList.cpp - Implemementation of CDeviceList class
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <setupapi.h>
#include <regstr.h>
#include "DeviceList.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CDeviceList::CDeviceList(const GUID& guid)
	{							// CDeviceList::CDeviceList
	m_guid = guid;
	}							// CDeviceList::CDeviceList

CDeviceList::~CDeviceList()
	{							// CDeviceList::~CDeviceList
	}							// CDeviceList::~CDeviceList

///////////////////////////////////////////////////////////////////////////////

int CDeviceList::Initialize()
	{							// CDeviceList::Initialize

	// Open an enumeration handle so we can locate all devices of our
	// own class

	HDEVINFO info = SetupDiGetClassDevs(&m_guid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
	if (info == INVALID_HANDLE_VALUE)
		return 0;

	// Enumerate all devices of our class. For each one, create a
	// CDeviceEntryList object. Then determine the friendly name of the
	// device by reading the registry.

	SP_DEVICE_INTERFACE_DATA ifdata;
	ifdata.cbSize = sizeof(ifdata);
	DWORD devindex;
	for (devindex = 0; SetupDiEnumDeviceInterfaces(info, NULL, &m_guid, devindex, &ifdata); ++devindex)
		{						// for each device

		// Determine the symbolic link name for this device instance. Since
		// this is variable in length, make an initial call to determine
		// the required length.

		DWORD needed;
		SetupDiGetDeviceInterfaceDetail(info, &ifdata, NULL, 0, &needed, NULL);

		PSP_INTERFACE_DEVICE_DETAIL_DATA detail = (PSP_INTERFACE_DEVICE_DETAIL_DATA) malloc(needed);
		SP_DEVINFO_DATA did = {sizeof(SP_DEVINFO_DATA)};
		detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
		if (!SetupDiGetDeviceInterfaceDetail(info, &ifdata, detail, needed, NULL, &did))
			{						// can't get detail info
			free((PVOID) detail);
			continue;
			}						// can't get detail info

		// Determine the device's friendly name

		TCHAR fname[256];
		if (!SetupDiGetDeviceRegistryProperty(info, &did, SPDRP_FRIENDLYNAME, NULL, (PBYTE) fname, sizeof(fname), NULL)
			&& !SetupDiGetDeviceRegistryProperty(info, &did, SPDRP_DEVICEDESC, NULL, (PBYTE) fname, sizeof(fname), NULL))
			_tcsncpy(fname, detail->DevicePath, 256);

		CDeviceListEntry e(detail->DevicePath, fname);
		free((PVOID) detail);

		m_list.Add(e);
		}						// for each device

	SetupDiDestroyDeviceInfoList(info);

	// Return the number of entries in the list

	return m_list.GetSize();
	}							// CDeviceList::Initialize

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CDeviceListEntry::CDeviceListEntry(LPCTSTR linkname, LPCTSTR friendlyname)
	{							// CDeviceListEntry::CDeviceListEntry
	m_linkname = linkname;
	m_friendlyname = friendlyname;
	}							// CDeviceListEntry::CDeviceListEntry
