// =================================================================
//  Ultimate TCP/IP HTTP Server
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
#include "HTTP_s.h"
#include "test.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
// #define UT_CLIENT_TESTING_ONLY


HINSTANCE hInst = NULL;
CUT_HTTPServer * HTTPs;
CUH_Control status;
HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	hInst = hInstance;

	// init the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);

	// create modal dialog box
	DialogBox(hInstance, _T("DIALOG_1"), NULL, (DLGPROC )DlgProc);
	DeleteObject(hFont);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch(message)
	{
		
	case WM_INITDIALOG:
		{
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));			
			status.AttachHistoryWindow(hwnd,IDC_STATUS);
			status.SetFont(hFont);
			status.SetHistoryLength(50);

			HTTPs = new CUT_HTTPServer;
			
			// start the connection
			if (HTTPs->ConnectToPort(80) == CUT_SUCCESS)
			{
				status.AddLine(_T("Connected to port 80"));
				HTTPs->StartAccept();			// start accepting calls
				status.AddLine(_T("Waiting for connections"));
			}
			else
				status.AddLine(_T("Connection failed you might have an other server listening to port 80"));

			// set up the path where the server works from
			_TCHAR buffer[MAX_PATH + 1], *p;
			GetModuleFileName(NULL, buffer, MAX_PATH);

			p = buffer + _tcslen(buffer);
			while (p >= buffer && *p != _T('\\')) p--;
			*p = 0;
			
			status.AddLine(_T("Working Dir: "));
			status.AppendToLine(buffer);
			SetDlgItemText(hwnd, IDC_EDIT, buffer);
			
			HTTPs->SetPath(buffer); // copy the path the the winsock class
			HTTPs->ctrlHistory = &status; // copy the history control pointer

#if defined UT_CLIENT_TESTING_ONLY
			HTTPs->SetMaxConnections(5);
			status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
			status.AddLine(_T("of Ultimate TCP-IP. Maximum number of simultaneous connections is 5."),RGB(255,0,0));
			status.AddLine(_T("________________________________________________________________"));
#endif
			return 1;
		}
	case WM_CLOSE:
		{
			delete HTTPs;
			EndDialog(hwnd,0);
			break;
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
						HWND hwndEdit = GetDlgItem(hwnd, IDC_EDIT);
						
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
			case IDC_SETPATH:
				{
					_TCHAR buffer[MAX_PATH + 1];

					ZeroMemory(buffer, MAX_PATH+1);

					GetDlgItemText(hwnd, IDC_EDIT, buffer, MAX_PATH);
					HTTPs->SetPath(buffer);
					status.AddLine("Working Dir: ");
					status.AppendToLine(buffer);
					return 1;
				}
			}
		}
	}
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
