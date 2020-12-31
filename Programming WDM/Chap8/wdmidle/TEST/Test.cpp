// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "SelectDlg.h"

#include <initguid.h>
#include "..\sys\guids.h"

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

	// initialize MFC and print and error on failure

	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
		{						// can't initializa MFC
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 1;
		}						// can't initialize MFC

	CDeviceList devices(GUID_WDMIDLE);
	if (devices.Initialize() == 0)
		{						// no devices
		cerr << _T("No WDMIDLE devices to test") << endl;
		return 0;
		}						// no devices
	
	CSelectDlg dlg;
	dlg.m_list = &devices;
	if (dlg.DoModal() != IDOK)
		return 1;

	HANDLE hDevice = CreateFile(devices.m_list[dlg.m_devicelist].m_linkname, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		{						// can't open
		cerr << _T("Unable to open ") << devices.m_list[dlg.m_devicelist].m_friendlyname << endl;
		return 1;
		}						// can't open

	char buffer[15];
	DWORD junk;
	if (ReadFile(hDevice, buffer, sizeof(buffer), &junk, NULL))
		cout << _T("Read ") << junk << _T(" bytes: '") << buffer << _T("'") << endl;
	
	CloseHandle(hDevice);
	return 0;
	}							// _tmain


