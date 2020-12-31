
// =================================================================
//  Ultimate TCP/IP Finger server Demo
//  File:  TEST.CPP
//
//
// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================
 

#include "stdafx.h"
#include <shlobj.h>
#include "uh_ctrl.h"
#include "ftp_s.h"
#include "test.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
//#define UT_CLIENT_TESTING_ONLY



HINSTANCE hInst = NULL;
CUT_FTPServer FTPs;
CUH_Control status;
HFONT hFont = NULL;
BOOL Accepting = TRUE;

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



BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
		
			status.AttachHistoryWindow(hwnd,IDC_STATUS);
			status.SetFont(hFont);


			//start the connection
			if(FTPs.ConnectToPort(21) != CUT_SUCCESS)
			{
				status.AddLine("Connection failed on port 21");
				return 1;
			}
			else
				status.AddLine("Connected to port 21");

			FTPs.StartAccept();			//start accepting calls
			status.AddLine("Waiting for connections...");
			
			// set up the path where the server works from
			_TCHAR buffer[MAX_PATH + 1], *p;
			GetModuleFileName(NULL, buffer, MAX_PATH);

			p = buffer + _tcslen(buffer);
			while (p >= buffer && *p != _T('\\')) p--;
			*p = 0;
			
			SetDlgItemText(hwnd, IDC_EDIT1, buffer);
			
			status.AddLine("Working Dir: ");
			status.AppendToLine(buffer);
			
			//copy the path the the winsock class
			FTPs.SetPath(buffer);
			FTPs.SetMaxTimeOut(0);
			
			//copy the history control pointer
			FTPs.ctrlHistory = &status;
			
#if defined UT_CLIENT_TESTING_ONLY
			FTPs.SetMaxConnections(5);
			status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
			status.AddLine(_T("of Ultimate TCP-IP. Maximum number of simultaneous connections is 5."),RGB(255,0,0));
			status.AddLine(_T("________________________________________________________________"));
#endif
			return 1;
		}
	case WM_CLOSE:
		{
            FTPs.StopAccept();
			EndDialog(hwnd,0);
			return 1;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
            case IDC_STOPACC:
                if(Accepting){                
                    FTPs.StopAccept();
			        status.AddLine("Not accepting connections...");
                    SetDlgItemText(hwnd, IDC_STOPACC, _T("&Start Accept"));
                    Accepting = FALSE;
                }
                else
                {
			        //start the connection
			        if(FTPs.ConnectToPort(21) != CUT_SUCCESS)
			        {
				        status.AddLine("Connection failed on port 21");
				        return 1;
			        }
			        else
				        status.AddLine("Connected to port 21");

			        FTPs.StartAccept();			//start accepting calls
			        status.AddLine(_T("Waiting for connections..."));
                    SetDlgItemText(hwnd, IDC_STOPACC, _T("&Stop Accept"));
                    Accepting = TRUE;
                }
                return 1;

			case IDC_BROWSE:
				{
					BROWSEINFO bi;
					TCHAR szDisplayName[MAX_PATH]; 
					LPITEMIDLIST pidl;
					LPMALLOC pMalloc = NULL; 
					
					ZeroMemory(&bi, sizeof(bi));
					
					bi.hwndOwner = hwnd; 
					bi.pszDisplayName = szDisplayName;
					bi.lpszTitle = TEXT("Select a folder to act as the root path for the server:"); 
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
			case IDC_SETROOTPATH:
				{
					_TCHAR buf[MAX_PATH + 1];
					GetDlgItemText(hwnd,IDC_EDIT1,buf,MAX_PATH);
					FTPs.SetPath(buf);
					status.AddLine("Working Dir: ");
					status.AppendToLine(buf);
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


