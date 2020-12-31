// Setup.cpp -- Helper classes for setup programs
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "Setup.h"
#include <initguid.h>
#include <devguid.h>

DWORD GetField(PINFCONTEXT ic, DWORD index, CString& value);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CInf::CInf()
	{							// CInf::CInf
	m_hinf = INVALID_HANDLE_VALUE;
	}							// CInf::CInf

CInf::~CInf()
	{							// CInf::~CInf
	if (m_hinf)
		SetupCloseInfFile(m_hinf);
	}							// CInf::~CInf

///////////////////////////////////////////////////////////////////////////////

DWORD CInf::EnumDevices(const CString& modelname, PENUMDEVCALLBACK callback, PVOID context)
	{							// CInf::EnumDevices
	INFCONTEXT mod;
	DWORD code;

	if (!SetupFindFirstLine(m_hinf, modelname, NULL, &mod))
		return GetLastError();

	do	{						// for each model
		CString devname, instname, id;
		CStringArray idlist;

		if ((code = GetField(&mod, 0, devname)) != 0
			|| (code = GetField(&mod, 1, instname)) != 0)
			return code;

		int nfields = SetupGetFieldCount(&mod);

		for (int i = 2; i <= nfields; ++i)
			if (GetField(&mod, i, id) == 0)
				idlist.Add(id);
			else
				break;

		if (idlist.GetSize() == 0)
			idlist.Add(_T(""));

		if (!(*callback)(this, devname, instname, idlist, context, code))
			return code;
		}						// for each model
	while (SetupFindNextLine(&mod, &mod));

	return ERROR_NO_MORE_ITEMS;
	}							// CInf::EnumDevices

///////////////////////////////////////////////////////////////////////////////

DWORD CInf::EnumManufacturers(PENUMMFGCALLBACK callback, PVOID context)
	{							// CInf::EnumManufacturers
	INFCONTEXT mfg;				// context for manufacturer section scan
	DWORD code;

	if (!SetupFindFirstLine(m_hinf, _T("Manufacturer"), NULL, &mfg))
		return GetLastError();

	// Loop throught the manufacturer section, calling the specified callback
	// function for each one

	do	{						// for each manufacturer
		CString mfgname, modelname;
		if ((code = GetField(&mfg, 0, mfgname)) != 0
			|| (code = GetField(&mfg, 1, modelname)) != 0)
			return code;

		// Invoke callback function. It returns TRUE if we should continue
		// the enumeration or FALSE if we should stop.
		
		if (!(*callback)(this, mfgname, modelname, context, code))
			return code;
		}						// for each manufacturer
	while (SetupFindNextLine(&mfg, &mfg));

	return ERROR_NO_MORE_ITEMS;
	}							// CInf::EnumManufacturers

///////////////////////////////////////////////////////////////////////////////

DWORD CInf::Open(LPCTSTR name, BOOL defsearch /* = TRUE */)
	{							// CInf::Open

	CString infname(name);
	if (infname[0] == '"')
		infname = infname.Mid(2, infname.GetLength() - 2); // remove quotes from name

	// If we're not to use the default search path for INF files (namely, directories
	// named in HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\DevicePath [i.e.,
	// the INF directory], make sure we present a pathname rather than just a
	// name to setup functions

	if (!defsearch && _tcschr(infname, _T('\\')) == NULL)
		m_name = _T(".\\");
	m_name += infname;

	m_hinf = SetupOpenInfFile(m_name, NULL, INF_STYLE_WIN4, NULL);
	if (m_hinf == INVALID_HANDLE_VALUE)
		return GetLastError();

	// Determine the class name and GUID for this file

	TCHAR classname[64];
	if (!SetupDiGetINFClass(m_name, &m_guid, classname, arraysize(classname), NULL))
		return GetLastError();
	m_classname = classname;
	DWORD junk;
	if (m_guid == GUID_NULL)
		SetupDiClassGuidsFromName(classname, &m_guid, 1, &junk);

	return 0;
	}							// CInf::Open

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

CDevInfoSet::CDevInfoSet()
	{							// CDevInfoSet::CDevInfoSet
	m_hinfo = INVALID_HANDLE_VALUE;
	memset(&m_devinfo, 0, sizeof(m_devinfo));
	m_devinfo.cbSize = sizeof(m_devinfo);
	}							// CDevInfoSet::CDevInfoSet

CDevInfoSet::~CDevInfoSet()
	{							// CDevInfoSet::~CDevInfoSet
	UnregisterDevice();
	if (m_hinfo != INVALID_HANDLE_VALUE)
		SetupDiDestroyDeviceInfoList(m_hinfo);
	}							// CDevInfoSet::~CDevInfoSet

///////////////////////////////////////////////////////////////////////////////

DWORD CDevInfoSet::Create(CInf* inf, HWND hwnd)
	{							// CDevInfoSet::Create
	m_inf = inf;
	m_hwnd = hwnd;
	m_hinfo = SetupDiCreateDeviceInfoList(&m_inf->m_guid, hwnd);
	if (m_hinfo == INVALID_HANDLE_VALUE)
		return GetLastError();
	
	return 0;
	}							// CDevInfoSet::Create

///////////////////////////////////////////////////////////////////////////////

DWORD CDevInfoSet::CreateDeviceInfo(const CString& devid)
	{							// CDevInfoSet::CreateDeviceInfo
	if (!SetupDiCreateDeviceInfo(m_hinfo, m_inf->m_classname, &m_inf->m_guid,
		NULL, m_hwnd, DICD_GENERATE_ID, &m_devinfo))
		return GetLastError();

	m_devid = devid;
	DWORD size = (devid.GetLength() + 2) * sizeof(TCHAR);
	PBYTE hwid = new BYTE[size];
	memset(hwid, 0, size);
	memcpy(hwid, (LPCTSTR) devid, size - 2 * sizeof(TCHAR));

	BOOL okay = SetupDiSetDeviceRegistryProperty(m_hinfo, &m_devinfo, SPDRP_HARDWAREID,
		hwid, size);

	delete[] hwid;

	if (okay)
		return 0;

	return GetLastError();
	}							// CDevInfoSet::CreateDeviceInfo

///////////////////////////////////////////////////////////////////////////////

DWORD CDevInfoSet::RegisterDevice()
	{							// CDevInfoSet::RegisterDevice
	if (!SetupDiCallClassInstaller(DIF_REGISTERDEVICE, m_hinfo, &m_devinfo))
		return GetLastError();
	m_registered = TRUE;
	return 0;
	}							// CDevInfoSet::RegisterDevice

///////////////////////////////////////////////////////////////////////////////

DWORD CDevInfoSet::UnregisterDevice()
	{							// CDevInfoSet::UnregisterDevice
	if (m_registered)
		if (!SetupDiCallClassInstaller(DIF_REMOVE, m_hinfo, &m_devinfo))
			return GetLastError();
	return 0;
	}							// CDevInfoSet::UnregisterDevice

///////////////////////////////////////////////////////////////////////////////

DWORD CDevInfoSet::UpdateDriver()
	{							// CDevInfoSet::UpdateDriver
	BOOL reboot = FALSE;
	if (!UpdateDriverForPlugAndPlayDevices(m_hwnd, m_devid, m_inf->m_name,
		INSTALLFLAG_FORCE, &reboot))
		return GetLastError();

	m_registered = FALSE;		// prevent unregistration when done
	return 0;
	}							// CDevInfoSet::UpdateDriver

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

DWORD GetField(PINFCONTEXT ic, DWORD index, CString& value)
	{							// GetField
	DWORD need;
	DWORD code;

	if (!SetupGetStringField(ic, index, NULL, 0, &need))
		return GetLastError();

	LPTSTR buffer = value.GetBuffer(need);
	if (SetupGetStringField(ic, index, buffer, need, NULL))
		code = 0;
	else
		{
		code = GetLastError();
		buffer[0] = 0;
		}

	value.ReleaseBuffer();
	return code;
	}							// GetField