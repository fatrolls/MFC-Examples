// Helper.cpp -- Implementation of CHelper class
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winsvc.h>
#include "Helper.h"

#include <winioctl.h>
#include "..\sys\ioctls.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CHelper theHelper;				// the one and only CHelper object

///////////////////////////////////////////////////////////////////////////////

CHelper::CHelper()
	{							// CHelper::CHelper
	m_hservice = NULL;
	m_hdriver = INVALID_HANDLE_VALUE;
	}							// CHelper::CHelper

CHelper::~CHelper()
	{							// CHelper::~CHelper
	if (m_hdriver != INVALID_HANDLE_VALUE)
		{						// close handle to driver
		CloseHandle(m_hdriver);
		m_hdriver = INVALID_HANDLE_VALUE;
		}						// close handle to driver

	if (m_hservice)
		{						// halt and delete service
		SERVICE_STATUS status;
		ControlService(m_hservice, SERVICE_CONTROL_STOP, &status);
		DeleteService(m_hservice);
		CloseServiceHandle(m_hservice);
		m_hservice = NULL;
		}						// halt and delete service
	}							// CHelper::~CHelper

///////////////////////////////////////////////////////////////////////////////

BOOL CHelper::Initialize(LPCTSTR name)
	{							// CHelper::Initialize
	TCHAR devname[_MAX_PATH];
	_tcscpy(devname, _T("\\\\.\\"));
	_tcscat(devname, name);
	
	SC_HANDLE hsc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (hsc)
		{						// start service

		// Construct the name of the helper driver

		TCHAR pathname[MAX_PATH];
//		GetWindowsDirectory(pathname, arraysize(pathname));
//		_tcscat(pathname, _T("\\system32\\drivers\\"));
		_tcscpy(pathname, _T("system32\\drivers\\"));
		_tcscat(pathname, name);
		_tcscat(pathname, _T(".sys"));

		m_hservice = CreateService(hsc, name, _T("Helper Driver"),
			SERVICE_ALL_ACCESS, SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
			pathname, NULL, NULL, NULL, NULL, NULL);
		if (!m_hservice && GetLastError() == ERROR_SERVICE_EXISTS)
			m_hservice = OpenService(hsc, name, SERVICE_ALL_ACCESS);
		if (m_hservice)
			{						// start service
			if (!StartService(m_hservice, 0, NULL))
				{
				TRACE(_T("StartService failed - %d\n"), GetLastError());
				return FALSE;
				}
			}						// start service
		else
			TRACE(_T("CreateService/OpenService failed - %d\n"), GetLastError());

		CloseServiceHandle(hsc);
		}						// start service

	m_hdriver = CreateFile(devname, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);

	if (m_hdriver == INVALID_HANDLE_VALUE && !hsc)
		{						// try to dynamically load VxD
		_tcscat(devname, _T(".vxd"));
		m_hdriver = CreateFile(devname, 0, 0, NULL, 0, FILE_FLAG_DELETE_ON_CLOSE, NULL);
		}						// try to dynamically load VxD

	if (m_hdriver == INVALID_HANDLE_VALUE)
		{
		TRACE(_T("CreateFile failed - %d\n"), GetLastError());
		return FALSE;
		}

	return TRUE;
	}							// CHelper::Initialize

///////////////////////////////////////////////////////////////////////////////

BOOL CHelper::GetEvent(GUID& guid, GUID& event, CString& linkname, DWORD& datasize, LONG& textoffset, PBYTE data)
	{							// CHelper::GetEvent
	GETEVENT_PARAMS params;
	DWORD junk;
	if (!DeviceIoControl(m_hdriver, IOCTL_GETEVENT, NULL, 0, &params, sizeof(params), &junk, NULL))
		return FALSE;

	guid = params.guid;
	event = params.event;
	linkname = params.linkname;
	datasize = params.datasize;
	textoffset = params.textoffset;
	memcpy(data, params.data, params.datasize);
	
	return TRUE;
	}							// CHelper::GetEvent

///////////////////////////////////////////////////////////////////////////////

BOOL CHelper::Register(const GUID* guid, HANDLE hevent)
	{							// CHelper::Register
	REGISTER_PARAMS params;
	params.guid = *guid;
	params.hevent = hevent;
	DWORD junk;
	return DeviceIoControl(m_hdriver, IOCTL_REGISTER, &params, sizeof(params), NULL, 0, &junk, NULL);
	}							// CHelper::Register

///////////////////////////////////////////////////////////////////////////////

VOID CHelper::Unregister(const GUID* guid)
	{							// CHelper::Unregister
	UNREGISTER_PARAMS params;
	params.guid = *guid;
	DWORD junk;
	DeviceIoControl(m_hdriver, IOCTL_DEREGISTER, &params, sizeof(params), NULL, 0, &junk, NULL);
	}							// CHelper::Unregister
