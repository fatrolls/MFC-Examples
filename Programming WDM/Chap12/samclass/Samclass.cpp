// samclass.cpp -- Property page provider for the SAMPLE class of devices
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "resource.h"

HINSTANCE hInst;
BOOL WINAPI PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
UINT CALLBACK PageCallbackProc(HWND junk, UINT msg, LPPROPSHEETPAGE p);

struct SETUPSTUFF {
	HDEVINFO info;
	PSP_DEVINFO_DATA did;
	};

///////////////////////////////////////////////////////////////////////////////

BOOL APIENTRY DllMain(HANDLE hModule, DWORD reason, LPVOID lpReserved)
	{							// DllMain
	hInst = (HINSTANCE) hModule;
    return TRUE;
	}							// DllMain

///////////////////////////////////////////////////////////////////////////////

extern "C" BOOL __declspec(dllexport) CALLBACK EnumPropPages(PSP_PROPSHEETPAGE_REQUEST p,
	LPFNADDPROPSHEETPAGE AddPage, LPARAM lParam)
	{							// EnumPropPages
	PROPSHEETPAGE page;
	HPROPSHEETPAGE hpage;

	memset(&page, 0, sizeof(page));
	page.dwSize = sizeof(PROPSHEETPAGE);
	page.hInstance = hInst;
	page.pszTemplate = MAKEINTRESOURCE(IDD_SAMPAGE);
	page.pfnDlgProc = PageDlgProc;

	// Create an auxiliary data structure to pass important information
	// to our WM_INITDIALOG handler. Arrange for a callback when the page
	// is destroyed (the only event we actually care about) to delete this
	// structure

	SETUPSTUFF* stuff = new SETUPSTUFF;
	stuff->info = p->DeviceInfoSet;
	stuff->did = p->DeviceInfoData;
	page.lParam = (LPARAM) stuff;
	page.pfnCallback = PageCallbackProc;
	page.dwFlags = PSP_USECALLBACK;

	// Create a property page and add it to the device manager's property sheet

	hpage = CreatePropertySheetPage(&page);

	if (!(*AddPage)(hpage, lParam))
		DestroyPropertySheetPage(hpage);

	return TRUE;
	}							// EnumPropPages

///////////////////////////////////////////////////////////////////////////////

BOOL WINAPI PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
	{							// PageDlgProc
	switch (msg)
		{						// process message

	case WM_INITDIALOG:
		{						// WM_INITDIALOG
		SETUPSTUFF* stuff = (SETUPSTUFF*) ((LPPROPSHEETPAGE) lParam)->lParam;
		BOOL okay = FALSE;

		// Determine the friendly name or description of the device

		TCHAR name[256];
		if (!SetupDiGetDeviceRegistryProperty(stuff->info, stuff->did, SPDRP_FRIENDLYNAME, NULL, (PBYTE) name, sizeof(name), NULL)
			&& !SetupDiGetDeviceRegistryProperty(stuff->info, stuff->did, SPDRP_DEVICEDESC, NULL, (PBYTE) name, sizeof(name), NULL))
			name[0] = 0;

		SetDlgItemText(hdlg, IDC_SAMNAME, name);

		// Determine the URL for the sample information file by interrogating the non-standard
		// device property SampleInfo. The user may click the More Information button on this
		// page to view this file in a web browser.

		HKEY hkey = SetupDiOpenDevRegKey(stuff->info, stuff->did, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ);
		DWORD length = sizeof(name);
		if (hkey && RegQueryValueEx(hkey, "SampleInfo", NULL, NULL, (LPBYTE) name, &length) == 0)
			{				// get sample info URL
    		LPSTR infofile;
    		
    		DoEnvironmentSubst(name, sizeof(name));
    		infofile = (LPSTR) GlobalAlloc(GMEM_FIXED, strlen(name) + 1);
    		if (infofile)
				{				// copy string
	    		strcpy(infofile, name);
				SetWindowLong(hdlg, DWL_USER, (LONG) infofile);
				}				// copy string

			okay = TRUE;

			RegCloseKey(hkey);
			}				// get sample info URL

		if (!okay)
			{					// no SampleInfo
			ShowWindow(GetDlgItem(hdlg, IDC_INFOLABEL), SW_HIDE);
			ShowWindow(GetDlgItem(hdlg, IDB_MOREINFO), SW_HIDE);
			}					// no SampleInfo
			    		
    	break;
    	}						// WM_INITDIALOG
    	
   	case WM_DESTROY:
   		{						// WM_DESTROY
   		LPSTR infofile = (LPSTR) GetWindowLong(hdlg, DWL_USER);
   		if (infofile)
   			GlobalFree((HGLOBAL) infofile);
   		break;
   		}						// WM_DESTROY
    	
    case WM_COMMAND:
    	switch (LOWORD(wParam))
    		{					// process command notification
    		
    	case IDB_MOREINFO:
    		{					// IDB_MOREINFO 
	   		LPSTR infofile = (LPSTR) GetWindowLong(hdlg, DWL_USER);
    		if (infofile)
	    		ShellExecute(hdlg, NULL, infofile, NULL, NULL, SW_SHOWNORMAL);
    		return TRUE;
    		}					// IDB_MOREINFO
    		
    		}					// process command notification
		break;

		}						// process message

	return FALSE;
	}							// PageDlgProc

///////////////////////////////////////////////////////////////////////////////

UINT CALLBACK PageCallbackProc(HWND junk, UINT msg, LPPROPSHEETPAGE p)
	{							// PageCallbackProc
	if (msg == PSPCB_RELEASE && p->lParam)
		delete (SETUPSTUFF*) p->lParam;
	return TRUE;				// matters only for PSPCB_CREATE
	}							// PageCallbackProc
