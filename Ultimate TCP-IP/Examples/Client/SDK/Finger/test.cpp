// =================================================================
//  Ultimate TCP/IP Finger Test Program
//  File:  test.cpp
//  
// ===================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================


#include "stdafx.h"
#include "test.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "finger_c.h"

HINSTANCE hInst = NULL;

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE, LPSTR, int)
{
	hInst = hInstance;
	
	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);

	//create modal dialog box
	DialogBox(hInstance,_T("DIALOG_1"),NULL, (DLGPROC )DlgProc);

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

BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	static CUH_Control control;
	static int align = TA_LEFT;
	static int textColor = RGB(0,0,0);
	static int backColor = RGB(255,255,255);
	static HFONT hFont;

	_TCHAR buf[256];
	

	switch(message){

		case WM_INITDIALOG:{

			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));

			// Set some default text 
			SetDlgItemText(hwnd, IDC_EDIT, _T("name@mit.edu"));

			//attach the history window to the control
			control.AttachHistoryWindow(hwnd,IDC_HISTORY);
			control.SetHistoryLength(50);

			hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			control.SetFont(hFont);

			return 1;
		}
		case WM_NCDESTROY:{
			DeleteObject(hFont);
			return 0;
		}
		case WM_COMMAND:{

			switch(LOWORD(wParam)){

				case IDC_ABOUT:{
					DialogBox(hInst,_T("IDD_ABOUT"),hwnd,(DLGPROC )AboutProc);
					return 1;
				}
				case IDC_FINGER:{

					//set the cursor to an hourglass	
					SetCursor(LoadCursor(NULL,IDC_WAIT));

					//clear the history control
					control.ClearHistory();
					//get the information to finger
					GetDlgItemText(hwnd, IDC_EDIT,buf,256);

					if (_tcsstr(buf, _T("@")) == NULL) {

						// Oops, forgot the @ symbol
						MessageBox(hwnd, _T("The finger address must contain the @ symbol."), 
							NULL, MB_OK | MB_ICONINFORMATION);
					}
					else {

						//perform the finger
						CUT_FingerClient fc;
						if(fc.Finger(buf) != UTE_SUCCESS){
							//if finger failed then show fail message
							control.AddLine(_T("Finger Failed"));
						}
						else{
							//show the results
							int numLines = fc.GetNumberReturnLines();
							for(int index =0;index <numLines;index++){
								control.AddLine(fc.GetReturnLine(index));
							}
						}
						
						//set the cursor back to the arrow
						SetCursor(LoadCursor(NULL,IDC_ARROW));
					}

					return 1;
				}
				case IDC_EXIT:{
					EndDialog(hwnd,0);
					return 1;
				}
			}
			return 0;
		}
		case WM_SIZE: {

			RECT rect, clientRect;
			POINT pnt;
			
			HWND statWnd = GetDlgItem(hwnd,IDC_HISTORY);
			
			GetWindowRect(statWnd, &rect);
			pnt.x = rect.left;
			pnt.y = rect.top;
			ScreenToClient(hwnd, &pnt);
			
			GetClientRect(hwnd, &clientRect);
			
			rect.top = pnt.y;
			rect.left = pnt.x;
			
			rect.right = clientRect.right - rect.left + 1;
			rect.bottom = clientRect.bottom - rect.left + 1;
			
			MoveWindow(statWnd, rect.left, rect.top, rect.right-rect.left,rect.bottom-rect.top,TRUE);
			
			return 1;
		}
		case WM_CLOSE:{
			EndDialog(hwnd,0);
			return 1;
		}
	}
	return 0;
}
