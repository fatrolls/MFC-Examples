/*******************************************
Ultimate History/Logger Test Program
Copyright 1997-1999 The Ultimate Toolbox
********************************************/


#include "stdafx.h"
#include "uh_ctrl.h"
#include "test.h"
#include <time.h>

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996 )

HINSTANCE hInst = NULL;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	hInst = hInstance;

	// register the history control
	CUH_Control::RegisterWindowClass(hInstance);

	// create modal dialog box
	DialogBox(hInstance, _T("DIALOG_1"), NULL, (DLGPROC )DlgProc);
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
	
	_TCHAR buf[256];
	
	
	switch(message)
	{
		case WM_INITDIALOG:
			{
				// set the window icon
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
				
				//attach the history window to the control
				control.AttachHistoryWindow(hwnd,IDC_HISTORY);
				control.SetHistoryLength(50);
				
				//setup the controls
				SetDlgItemText(hwnd, IDC_EDIT, _T("Sample line of text"));
				SetDlgItemText(hwnd,IDC_TEXTCOLOR,_T("Black Text"));
				SetDlgItemText(hwnd,IDC_BACKCOLOR,_T("White Back"));

                control.AddLine(_T("Welcome !!!"), RGB(255,0,0));

                // Display current time
                time_t lTime;
                struct tm *tmTime;
                time(&lTime);
                tmTime = localtime(&lTime);
				_TCHAR buf[MAX_PATH];
				_stprintf(buf,_T("Current time is:  %02d:%02d"), tmTime->tm_hour, tmTime->tm_min);
                control.AddLine(buf, RGB(255,0,0));


				return 1;
			}
		case WM_COMMAND:
			{
				
				switch(LOWORD(wParam))
				{

				case IDC_ABOUT:
					{
						// Display about box
						DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					}
					break;

				case IDC_DATESTAMP:
					{
						GetDlgItemText(hwnd, IDC_EDIT,buf,256);
						control.AddStampedLine(buf, textColor, backColor);
						return 1;
					}
				case IDC_CLEAR:
					{
						control.ClearHistory();
						return 1;
					}
				case IDC_ADDLINE:
					{
						GetDlgItemText(hwnd, IDC_EDIT,buf,256);
						control.AddLine(buf, textColor, backColor);
						return 1;
					}
				case IDC_APPENDLINE:
					{
						GetDlgItemText(hwnd, IDC_EDIT,buf,256);
						control.AppendToLine(buf);
						return 1;
					}
				case IDC_TEXTCOLOR:
					{
						if(textColor == RGB(0,0,0))
						{
							SetDlgItemText(hwnd,IDC_TEXTCOLOR,_T("Red Text"));
							textColor = RGB(255,0,0);
						}
						else if(textColor == RGB(255,0,0))
						{
							SetDlgItemText(hwnd,IDC_TEXTCOLOR,_T("Blue Text"));
							textColor = RGB(0,0,255);
						}
						else if(textColor == RGB(0,0,255))
						{
							SetDlgItemText(hwnd,IDC_TEXTCOLOR,_T("Black Text"));
							textColor = RGB(0,0,0);
						}
						return 1;
					}
				case IDC_BACKCOLOR:
					{
						if(backColor == RGB(255,255,255))
						{
							SetDlgItemText(hwnd,IDC_BACKCOLOR,_T("Gray Back"));
							backColor = RGB(200,200,200);
						}
						else if(backColor == RGB(200,200,200))
						{
							SetDlgItemText(hwnd,IDC_BACKCOLOR,_T("Yellow Back"));
							backColor = RGB(255,255,0);
						}
						else if(backColor == RGB(255,255,0))
						{
							SetDlgItemText(hwnd,IDC_BACKCOLOR,_T("White Back"));
							backColor = RGB(255,255,255);
						}
						return 1;
					}
				case IDC_EXIT:
					{
						EndDialog(hwnd,0);
						return 1;
					}
				}
				return 0;
			}
		case WM_CLOSE:
			{
				EndDialog(hwnd,0);
				return 1;
			}
	}
	return 0;
}

#pragma warning ( pop )