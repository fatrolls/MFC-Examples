// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "DeviceList.h"
#include <winioctl.h>
#include <initguid.h>
#include "GenericPower.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
	{							// _tmain
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		{
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 1;
		}

	CDeviceList devices(GUID_GENERIC_POWER);
	int ndevices = devices.Initialize();
	if (ndevices == 0)
		{
		cout << _T("No devices to report about") << endl;
		return 0;
		}

	for (int i = 0; i < ndevices; ++i)
		{						// for each device
		CDeviceListEntry* dp = &devices.m_list[i];

		cout << _T("Properties of ") << (LPCTSTR) dp->GetProperty(FriendlyName) << _T(':') << endl;
		cout << _T("  Device Description ") << (LPCTSTR) dp->GetProperty(DeviceDescription) << endl;
		cout << _T("  Hardware Id        ") << (LPCTSTR) dp->GetProperty(HardwareId) << endl;
		cout << _T("  Compatible Ids     ") << (LPCTSTR) dp->GetProperty(CompatibleIds) << endl;
		cout << _T("  Service            ") << (LPCTSTR) dp->GetProperty(Service) << endl;
		cout << _T("  Class              ") << (LPCTSTR) dp->GetProperty(Class) << endl;
		cout << _T("  ClassGuid          ") << (LPCTSTR) dp->GetProperty(ClassGuid) << endl;
		cout << _T("  Driver             ") << (LPCTSTR) dp->GetProperty(Driver) << endl;
		cout << _T("  Manufacturer       ") << (LPCTSTR) dp->GetProperty(Manufacturer) << endl;
		cout << _T("  Enumerator         ") << (LPCTSTR) dp->GetProperty(Enumerator) << endl << endl;
		}						// for each device

	return 0;
	}							// _tmain


