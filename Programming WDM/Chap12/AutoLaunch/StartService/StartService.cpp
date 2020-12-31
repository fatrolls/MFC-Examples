// StartService.dll -- Use with RUNDLL32 to start a service
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
	{							// DllMain
    return TRUE;
	}							// DllMain

extern "C" void CALLBACK StartServiceRunning(HWND hwnd, HINSTANCE hInst, LPSTR lpCmdLine, int nShow)
	{							// StartServiceRunning

	if (!lpCmdLine || lstrlen(lpCmdLine) == 0)
		return;

	SC_HANDLE hsc = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (!hsc)
		return;

	SC_HANDLE hservice = OpenService(hsc, lpCmdLine, SERVICE_START);
	if (hservice)
		{
		StartService(hservice, 0, NULL);
		CloseServiceHandle(hservice);
		}

	CloseServiceHandle(hsc);
	}							// StartServiceRunning


