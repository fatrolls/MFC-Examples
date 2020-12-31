// =================================================================
//  Ultimate TCP/IP Finger server 
//  File:  TEST.CPP
//
//
// =================================================================
// Ultimate TCP/IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================


#include "stdafx.h"
#include <shlobj.h>
#include "uh_ctrl.h"
#include "finger_s.h"
#include "test.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
//#define UT_CLIENT_TESTING_ONLY


HINSTANCE hInst = NULL;
HFONT hFont = NULL;
CUT_FingerServer* wsc = NULL;
CUH_Control status;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	hInst = hInstance;

	// init the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);
	
	// create modal dialog box
	hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));
	DialogBox(hInstance, _T("DIALOG_1"), NULL, (DLGPROC )DlgProc);
	DeleteObject(hFont);
	return 0;
}


BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	// About box dialog procedure
	
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





BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch(message)
	{
		case WM_INITDIALOG:
			{

				// set the window icon
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM) LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
				
				// setup the histroy control
				status.AttachHistoryWindow(hwnd,IDC_STATUS);
				status.SetFont(hFont);
				status.SetHistoryLength(200);

				// create an instance of the socket class
				wsc = new CUT_FingerServer;

			
				// start the connection
				wsc->ConnectToPort(79);
				status.AddLine(_T("Connected to Port 79"));
				wsc->StartAccept();			// start accepting calls
				status.AddLine(_T("Waiting for connections"));
				
				// set up the path where the server works from
				_TCHAR buffer[MAX_PATH + 1], *p;
				GetModuleFileName(NULL, buffer, MAX_PATH);

				p = buffer + _tcslen(buffer);
				while (p >= buffer && *p != '\\') p--;
				*p = 0;
				
				status.AddLine(_T("Working Dir: "));
				status.AppendToLine(buffer);

				wsc->SetPath(buffer);
				SetDlgItemText(hwnd, IDC_EDIT1, buffer);
				
#ifdef  UT_DISPLAYSTATUS
				// since this examples uses the history control where
				// other applications you will be developing may not need the functionality of the history 
				// control window  this statement was left in a define
				// to enable it from the project setting define  UT_DISPLAYSTATUS as a preeprocessor defenition 
				// in the preprocessor category of the C++ tab (that if you are using VC5 <g>)
				wsc->ctrlHistory = &status;
#if defined UT_CLIENT_TESTING_ONLY
				wsc->SetMaxConnections(5);
				status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
				status.AddLine(_T("of Ultimate TCP-IP. Maximum number of simultaneous connections is 5."),RGB(255,0,0));
				status.AddLine(_T("________________________________________________________________"));
#endif
#endif
				// Display about box
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);

				return 1;
			}
		case WM_DESTROY:
			{
				// We don't have to check if `wsc' is NULL since C++ allows deletetion
				// of NULL pointers -- the instruction is simply ignored

				delete wsc; 
				return 1;
			}
		case WM_CLOSE:
			{
				EndDialog(hwnd,0);
				return 1;
			}
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
				case IDC_BROWSE:
					{
						BROWSEINFO bi;
						TCHAR szDisplayName[MAX_PATH]; 
						LPITEMIDLIST pidl;
						LPMALLOC pMalloc = NULL; 
						
						ZeroMemory(&bi, sizeof(bi));
						
						bi.hwndOwner = hwnd; 
						bi.pszDisplayName = szDisplayName;
						bi.lpszTitle = TEXT("Select a folder containg the file named \"default\" and all users plan files:"); 
						bi.ulFlags = BIF_RETURNONLYFSDIRS;
						pidl = SHBrowseForFolder(&bi);
						
						if (pidl) 
						{
							HWND hwndEdit = GetDlgItem(hwnd, IDC_EDIT1);

							SHGetPathFromIDList(pidl, szDisplayName); // set the directory name. 
							
							// set focus and selection to the edit control
							SetWindowText(hwndEdit, szDisplayName);
							SetFocus(hwndEdit);
							SendMessage(hwndEdit, EM_SETSEL, 0, -1);
						} 
						
						// free the pidl using the shell's task allocator. 
						if (SHGetMalloc(&pMalloc) == NOERROR)
						{
							// free it. 
							pMalloc->Free((void *)pidl);
						}
					}
					break;
				case IDC_ABOUT:
					{
						// Display about box
						DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					}
					break;
				case IDC_SET_PATH:
					{
						_TCHAR buffer[MAX_PATH + 1];
						GetDlgItemText(hwnd, IDC_EDIT1, buffer, MAX_PATH);
						
						wsc->SetPath(buffer);
						status.AddLine(_T("Working Dir: "));
						status.AppendToLine(buffer);
						return 1;
					}
				case IDC_EXIT:
					{
						EndDialog(hwnd,0);
						return 1;
					}
				}
			}
	}
	return 0;
}

