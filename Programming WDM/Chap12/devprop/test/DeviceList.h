// DeviceList.h - Interface to CDeviceList class
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef DEVICELIST_H
#define DEVICELIST_H

///////////////////////////////////////////////////////////////////////////////

enum DEVPROP {
	DeviceDescription,
	HardwareId,
	CompatibleIds,
	Service,
	Class,
	ClassGuid,
	Driver,
	Manufacturer,
	FriendlyName,
	Enumerator,
	};

class CDeviceListEntry
{								// class CDeviceListEntry
public:
	CDeviceListEntry(LPCTSTR linkname, LPCTSTR friendlyname);
	CDeviceListEntry(){}

	CString		m_linkname;
	CString		m_friendlyname;

	CString	GetProperty(enum DEVPROP prop);
};								// class CDeviceListEntry

///////////////////////////////////////////////////////////////////////////////

class CDeviceList
{								// class CDeviceList
public:
	CDeviceList(const GUID& guid);
	~CDeviceList();

	GUID	m_guid;				// the interface GUID for this list
	CArray<CDeviceListEntry, CDeviceListEntry&> m_list;	// list of devices

	int		Initialize();
};								// class CDeviceList

#endif