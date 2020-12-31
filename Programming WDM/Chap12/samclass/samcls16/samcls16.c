// SAMCLS16.C -- 16-bit Property Page Provider DLL for WDM samples (Win98 version)
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include <windows.h>
#include <shellapi.h>
#include <commctrl.h>
#include <setupx.h>

#define EXPORT __export

#define Not_VxD   // to get ring-3 dcls
#include <vmm.h>
#define MIDL_PASS  // suppress 32-bit only #pragma pack(push)
#include <configmg.h>

#include "resource.h"

BOOL WINAPI EXPORT PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);

///////////////////////////////////////////////////////////////

BOOL WINAPI EXPORT EnumPropPages(LPDEVICE_INFO pdi,
    LPFNADDPROPSHEETPAGE AddPage, LPARAM lParam)
    {    // EnumPropPages
    PROPSHEETPAGE page; // status property page
    HPROPSHEETPAGE hpage;

    page.dwSize = sizeof(PROPSHEETPAGE);
    page.dwFlags = PSP_USETITLE;
    _asm mov page.hInstance, ds
    page.pszTemplate = MAKEINTRESOURCE(IDD_SAMPAGE);
    page.hIcon = NULL;
    page.pszTitle = "Sample Information";
    page.pfnDlgProc = PageDlgProc;
    page.lParam = (LPARAM) pdi->dnDevnode;
    page.pfnCallback = NULL;

    hpage = CreatePropertySheetPage(&page);
    if (!hpage)
    return TRUE;

    if (!AddPage(hpage, lParam))
        DestroyPropertySheetPage(hpage);
    return TRUE;
    }                           // EnumPropPages

///////////////////////////////////////////////////////////////

BOOL WINAPI EXPORT PageDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
    {                           // PageDlgProc
    switch (msg)
    	{						// process message
    	
    case WM_INITDIALOG:
    	{						// WM_INITDIALOG 
    	DEVNODE devnode = (DEVNODE) ((LPPROPSHEETPAGE) lParam)->lParam;
    	CONFIGRET cr;
    	char name[256];                                                                        
    	ULONG length = sizeof(name);
    	
    	// Determine the friendly name or description for this device
		    	                                                                        
    	cr = CM_Read_Registry_Value(devnode, NULL, "FriendlyName", REG_SZ, name, &length, CM_REGISTRY_HARDWARE);
    	if (cr != CR_SUCCESS)
			{
			length = sizeof(name);
    		cr = CM_Read_Registry_Value(devnode, NULL, "DeviceDesc", REG_SZ, name, &length, CM_REGISTRY_HARDWARE);
			}

    	if (cr != CR_SUCCESS)
    		name[0] = 0;
    	
    	SetDlgItemText(hdlg, IDC_SAMNAME, name);
    	
    	// Look for a SampleInfo entry in the registry
    	
    	length = sizeof(name);
    	cr = CM_Read_Registry_Value(devnode, NULL, "SampleInfo", REG_SZ, name, &length, CM_REGISTRY_HARDWARE);
    	if (cr == CR_SUCCESS)
    		{					// save SampleInfo
    		HGLOBAL hmem;
    		LPSTR infofile;
    		
    		DoEnvironmentSubst(name, sizeof(name));
    		hmem = GlobalAlloc(GMEM_MOVEABLE, lstrlen(name) + 1);
    		if (!hmem)
    			break;
    			
    		infofile = (LPSTR) GlobalLock(hmem);
    		if (!infofile)
    			{				// can't lock
    			GlobalFree(hmem);
    			break;
    			}				// can't lock
    			
    		lstrcpy(infofile, name);
    		GlobalUnlock(hmem);
    		SetWindowLong(hdlg, DWL_USER, (LONG) hmem);
    		}					// save SampleInfo
		else
			{					// no SampleInfo
			ShowWindow(GetDlgItem(hdlg, IDC_INFOLABEL), SW_HIDE);
			ShowWindow(GetDlgItem(hdlg, IDB_MOREINFO), SW_HIDE);
			}					// no SampleInfo
			    		
    	break;
    	}						// WM_INITDIALOG
    	
   	case WM_DESTROY:
   		{						// WM_DESTROY
   		HGLOBAL hmem = (HGLOBAL) GetWindowLong(hdlg, DWL_USER);
   		if (hmem)
   			GlobalFree(hmem);
   		break;
   		}						// WM_DESTROY
    	
    case WM_COMMAND:
    	switch (LOWORD(wParam))
    		{					// process command notification
    		
    	case IDB_MOREINFO:
    		{					// IDB_MOREINFO 
	   		HGLOBAL hmem = (HGLOBAL) GetWindowLong(hdlg, DWL_USER);
	   		LPCSTR infofile;
	   		
   			if (!hmem)
   				return TRUE;
    		infofile = (LPCSTR) GlobalLock(hmem);
    		if (!infofile)
    			return TRUE;
    			
    		ShellExecute(hdlg, NULL, infofile, NULL, NULL, SW_SHOWNORMAL);
    		GlobalUnlock(hmem);
    		return TRUE;
    		}					// IDB_MOREINFO
    		
    		}					// process command notification
    	
    	}						// process message
    	
    return FALSE;
    }                           // StatusDlgProc
    