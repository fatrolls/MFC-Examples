
// =================================================================
//  Ultimate TCP/IP MX Lookup client test program
//  File:  TEST.CPP
//
//  Purpose:
//
//      Demonstrates the CUT_MXLookup class
//     for domain Mail Echange server lookup.
//
// ===================================================================
// Ultimate TCP-IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================

#include "stdafx.h"
#include "test.h"
#include "uh_ctrl.h"	//output-history control
#include "ut_clnt.h"	//ultimate tcp/ip client class
#include "mxlookup.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

HINSTANCE hInst;

// Main function
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int)
{
	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);
	
	hInst = hInstance;
	
	//show the splash screen
	DialogBox(hInst, _T("IDD_SPLASH"), NULL, (DLGPROC) AboutProc);
	
	//create the DNS lookup dialog box
	DialogBox(hInst, _T("DIALOG_1"), NULL, (DLGPROC)DlgProc);
	return 0;
}


BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	// About box and Splash screen dialog procedure
	
	switch (message) {

		case WM_COMMAND:
			switch (LOWORD(wParam)) {

				case IDC_EXIT:
					EndDialog(hwndDlg, IDOK);
					break;
			}
			break;

			case WM_CLOSE:
				EndDialog(hwndDlg, IDOK);
				break;
	}

	return 0;
}


BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */){

	static CUH_Control control;
	static HFONT hFont;
	
	static CUT_MXLookup mxLookup;
					
	switch(message){

		case WM_INITDIALOG:{

			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDR_ICON)));

			//attach the history window to the control
			control.AttachHistoryWindow(hwnd,IDC_HISTORY);
			//set the maximum length of the buffer of this window
			control.SetHistoryLength(100);

			// set the font for the history window
			hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			control.SetFont(hFont);

			//setup the controls
			SetDlgItemText(hwnd, IDC_DNSSERVER,_T("A.ROOT-SERVERS.NET"));

			return 1;
		}
        // on final release reclaim the resources
		case WM_NCDESTROY:{
			DeleteObject((HGDIOBJ)hFont);

			return 0;
		}
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
			{
				case IDC_ABOUT:{
					DialogBox(hInst,_T("IDD_ABOUT"),hwnd,(DLGPROC)AboutProc);
					return 1;
				}
				case IDC_LOOKUPBTN:{
					
					UpdateWindow(hwnd);

					//get the name server and domain name to lookup
					_TCHAR nameServer[256];
					GetDlgItemText(hwnd,IDC_DNSSERVER,nameServer,256);
					_TCHAR lookUp[256];
					GetDlgItemText(hwnd,IDC_LOOKUP,lookUp,256);
						
					//clear the history window
					control.ClearHistory();


					//check the input strings
					if(nameServer[0] ==0){
						control.AddLine(_T("No Name Server Was Specified"));
						return 1;
					}
					if(lookUp[0] ==0){
						control.AddLine(_T("No Name Was Entered To Lookup"));
						return 1;
					}

					//set the cursor to an hourglass
					SetCursor(LoadCursor(NULL,IDC_WAIT));
					
					//perform the lookup
					if(mxLookup.LookupMX(nameServer,lookUp) == UTE_SUCCESS){

						_TCHAR buf[1000];
						_TCHAR szName[MAX_PATH];
						_TCHAR szAddress[MAX_PATH];
						long pref;

						int count = mxLookup.GetMXRecordCount();

						for(int loop = 0; loop < count ; loop++){
							mxLookup.GetMXRecord(szName,MAX_PATH,szAddress,MAX_PATH,&pref);
							_sntprintf(buf, 1000,_T("%16s %5.5d %s"),szAddress,pref,szName);
							control.AddLine(buf);
						}
					}
					else{
						control.AddLine(_T("N/A"));
					}

					//set the cursor back to the arrow
					SetCursor(LoadCursor(NULL,IDC_ARROW));
					return 1;
				}
			}
			return 0;
		}
		case WM_CLOSE:{
			EndDialog(hwnd,0);
			return 1;
		}
	}
	return 0;
}

#pragma warning ( pop )