// =================================================================
//  File:  QuickMailer.cpp
//
//  Purpose:
//
//      Ultimate TCP/IP Quick Mailer ver 1.0
//      Allows to quickly prepare and send the e-mail messages.
//
// =================================================================
// Ultimate TCP/IP v4.2
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// =================================================================

#include "stdafx.h"
#include "QuickMailer.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#define	SPLASH_BITMAP_CX		359	
#define	SPLASH_BITMAP_CY		251

DWORD					nSplashTimerID;


BOOL CALLBACK Splash(HWND hwndDlg, UINT message, WPARAM /* wParam */, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            // If in splash mode - start timer & remove Ok button
			nSplashTimerID = (DWORD)SetTimer(hwndDlg, 1, 2000, NULL);

			// Recalculate window size
			RECT	rectNew;
			GetWindowRect(hwndDlg, &rectNew);
			rectNew.right = rectNew.left + SPLASH_BITMAP_CX;
			rectNew.bottom = rectNew.top + SPLASH_BITMAP_CY;
			MoveWindow(hwndDlg, rectNew.left, rectNew.top, rectNew.right-rectNew.left, rectNew.bottom-rectNew.top, TRUE);

            break;
        case WM_TIMER:
		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;

        case WM_DESTROY:
            // Destroy timer
            if(nSplashTimerID != 0) {
                KillTimer(hwndDlg, nTimerID);
                nTimerID = 0;
                }
            break;
	    }

	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
HANDLE      hNamedMutex     = NULL;     // Named mutex handle

    // Create named mutex
    hNamedMutex = CreateMutex(NULL, TRUE, _T("Ultimate TCP/IP Quick Mailer"));

    // Test if the programm is already running
    if(GetLastError() == ERROR_ALREADY_EXISTS) {
        MessageBox(NULL, _T("Ultimate TCP/IP Quick Mailer is already running!"), _T("Ultimate TCP/IP Quick Mailer"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

        // Close mutex handle
        CloseHandle(hNamedMutex);
        return 0;
        }

    // Save instance handle
    hInst = hInstance;

	// I will disable the splash window for now it is killing me GHAZI

//	DialogBox(hInstance, MAKEINTRESOURCE(IDD_SPLASH), NULL, Splash);
	// Show the about box 
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), NULL, AboutProc);

	// Show the main dilog box 
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, MainProc);

    // Close mutex handle
    CloseHandle(hNamedMutex);
	return 0;
}




/***************************************
AboutProc
    About dialog box procedure
****************************************/
BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            // If in splash mode - start timer & remove Ok button
            if(bAboutSplash) {
                nTimerID = (DWORD)SetTimer(hwndDlg, 2, 5000, NULL);
                MoveWindow(GetDlgItem(hwndDlg, IDOK), 0, 0, 0, 0, TRUE);
                }
            break;

        case WM_COMMAND:
            if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
    			EndDialog(hwndDlg, LOWORD(wParam));
	    		}
			break;

        case WM_TIMER:
		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;

        case WM_DESTROY:
            // Destroy timer
            if(nTimerID != 0) {
                KillTimer(hwndDlg, nTimerID);
                nTimerID = 0;
                }

            // Clear splash mode
            bAboutSplash = FALSE;
            break;
	    }

	return 0;
}

/***************************************
AddMailRecipientProc
     Add Mail Recipient dialog box procedure
****************************************/
BOOL CALLBACK AddMailRecipientProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_NAME), EM_LIMITTEXT, 99, 0);
            SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_ADDRESS), EM_LIMITTEXT, 1023, 0);

            // If edit mode
            if(bEditMode) {
                HWND            hwndList = GetDlgItem(hwndMainDlg, IDC_LIST_NAMES);
                int             item;

                *EditCancelData.szAddress = NULL;

                // Get selected data
                if((item = (DWORD)SendMessage(hwndList, LB_GETCURSEL, 0, 0)) != LB_ERR) {

                    // Find in the data list
                    SendMessage(hwndList, LB_GETTEXT, item, (LPARAM) (LPCTSTR) EditCancelData.szName);
                    RECIPIENTDATALIST::iterator i;
                    for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i)
                        if(_tcsicmp(EditCancelData.szName, i->szName) == 0) {
                            _tcscpy(EditCancelData.szAddress, i->szAddress);
                            break;
                            }

                    if(*EditCancelData.szAddress != NULL) {
                        // Display selected data
                        SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_NAME), EditCancelData.szName);
                        SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_ADDRESS), EditCancelData.szAddress);

                        SetWindowText(GetDlgItem(hwndDlg, IDOK), _T("Change"));
                        SetWindowText(hwndDlg, _T("Edit Mail Recipient"));
                        }
                    else
                        bEditMode = FALSE;
                    }
                else
                    bEditMode = FALSE;

                }

            break;
        case WM_COMMAND:
            if(HIWORD(wParam) == EN_CHANGE) {
                // Set the Ok button state
                if(GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT_NAME)) > 0 &&GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT_ADDRESS)) > 0 )
                    EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
                else
                    EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
 
                }  
            else if(LOWORD(wParam) == IDOK) {
                RecipientData   data;

                // Get data
                GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_NAME), data.szName, sizeof(data.szName)/sizeof(_TCHAR)-1);
                GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_ADDRESS), data.szAddress, sizeof(data.szAddress)/sizeof(_TCHAR)-1);

                // In edit mode remove current item
                if(bEditMode) {
                    RECIPIENTDATALIST::iterator i;
                    for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i)
                        if(_tcsicmp(EditCancelData.szName, i->szName) == 0) {
                            RecipientDataList.erase(i);
                            break;
                            }
                    }

                // Check if the name already exsists
                RECIPIENTDATALIST::iterator i;
                for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i)
                    if(_tcsicmp(data.szName, i->szName) == 0) {
                        MessageBox(hwndDlg, _T("This e-mail recipient name already exists."), _T("Ultimate TCP/IP Quick Mailer"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
                        EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
                        return 0;
                        }
    
                // Add new mail recipient to the data list
                RecipientDataList.push_back(data);

                // In edit mode remove current item
                if(bEditMode) {
                    int item;
                    if((item = (DWORD)SendMessage(GetDlgItem(hwndMainDlg, IDC_LIST_NAMES), LB_GETCURSEL, 0, 0)) != LB_ERR) 
                        SendMessage(GetDlgItem(hwndMainDlg, IDC_LIST_NAMES), LB_DELETESTRING , item, 0);
                    }

                // Add new mail recipient to the list control
                SendMessage(GetDlgItem(hwndMainDlg, IDC_LIST_NAMES), LB_ADDSTRING, 0, (LPARAM) (LPCTSTR) data.szName);

                // Clear fields
                SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_NAME), _T(""));
                SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_ADDRESS), _T(""));

                if(bEditMode) 
                    EndDialog(hwndDlg, IDOK);	    		
                else
                    SetFocus(GetDlgItem(hwndDlg, IDC_EDIT_NAME));
                }
            else if(LOWORD(wParam) == IDCANCEL) {
                EndDialog(hwndDlg, IDOK);
                }
			break;

        case EN_CHANGE:
            EndDialog(hwndDlg, IDCANCEL);
            break;

        case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;
	    }

	return 0;
}

/***************************************
PropertiesProc
     Properties dialog box procedure
****************************************/
BOOL CALLBACK PropertiesProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_FROM), EM_LIMITTEXT, 99, 0);
            SendMessage(GetDlgItem(hwndDlg, IDC_EDIT_SERVER), EM_LIMITTEXT, 99, 0);
            
            SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_FROM), szSendFrom);
            SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_SERVER), szHost);
            SendMessage(GetDlgItem(hwndDlg, IDC_CHECK_AUTO_RUN), BM_SETCHECK, dwRunAtStartUp, 0);

            if(*szSendFrom != NULL && *szHost != NULL)
                EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
            break;

        case WM_COMMAND:
            if(HIWORD(wParam) == EN_CHANGE) {

                // Get data
                if(GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT_FROM)) > 0)
                    EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);
                else
                    EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
                }  
            else if(LOWORD(wParam) == IDOK) {
                GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_FROM), szSendFrom, sizeof(szSendFrom)/sizeof(_TCHAR)-1);
                GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_SERVER), szHost, sizeof(szHost)/sizeof(_TCHAR)-1);
                dwRunAtStartUp = (DWORD)SendMessage(GetDlgItem(hwndDlg, IDC_CHECK_AUTO_RUN), BM_GETCHECK, 0, 0);

                // Set/Remove programm from the autorun folder
                // Open up the key 
                HKEY    m_hkey;
                if(RegOpenKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\"), &m_hkey) == ERROR_SUCCESS) {
                    if(dwRunAtStartUp != 0) {
                        LPTSTR  lpszPath = new _TCHAR[_tcslen(GetCommandLine())+1];
                        if(*GetCommandLine() == '\"')
                            _tcscpy(lpszPath, GetCommandLine()+1);
                        else
                            _tcscpy(lpszPath, GetCommandLine());
                        while(lpszPath[_tcslen(lpszPath)-1] == _T('\"') || lpszPath[_tcslen(lpszPath)-1] == _T(' '))
                            lpszPath[_tcslen(lpszPath)-1] = 0;
                        RegSetValueEx(m_hkey,_T("QuickMailer"),0,REG_SZ,(LPBYTE)lpszPath,(DWORD)_tcslen(lpszPath)+1);
                        delete [] lpszPath;
                        }
                    else {
                        RegDeleteValue(m_hkey, _T("QuickMailer"));
                        }

                    RegCloseKey(m_hkey);
                    }


    			EndDialog(hwndDlg, IDOK);
	    		}
            else if(LOWORD(wParam) == IDCANCEL) 
                EndDialog(hwndDlg, IDCANCEL);
			break;

		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;
	    }

	return 0;
}

/***************************************
NameListProc
     Names list box procedure
****************************************/
BOOL CALLBACK NameListProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static UINT ID;

	switch (message) {
        case WM_KEYUP:
            if(wParam == VK_RETURN)
            PostMessage(hwndMainDlg, WM_COMMAND, ID_TASKBAR_SENDMAIL, 0);
            break;
        case WM_LBUTTONDBLCLK:
            PostMessage(hwndMainDlg, WM_COMMAND, ID_TASKBAR_SENDMAIL, 0);
            return 0;
        case WM_RBUTTONDOWN: 
            {
            // Run menu
            POINT   pt;
            pt.y  = HIWORD(lParam);
            pt.x  = LOWORD(lParam);
            ClientToScreen(hWnd, &pt);
            RunMenu(GetParent(hWnd), IDR_MENU_LIST, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y);
			break;
            }
            
	    }
    
	return (BOOL)CallWindowProc(lpPrevListFunc, hWnd, message, wParam, lParam);
}

/***************************************
SendProc
     Send dialog box procedure
****************************************/
BOOL CALLBACK SendProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            {
            _TCHAR     strTo[4096];		// arbitrary - hey, it's just a sample...
			*strTo = _T('\0');

            // Initialize Subject field
            SendMessage(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT), CB_LIMITTEXT , MAX_PATH, 0);
			// v4.2 change - loop index used below ...
			UINT index = 0;
            for(index = 0; index < nSubjCount; index++) {
                SendMessage(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT), CB_ADDSTRING, 0, (LPARAM) (LPCTSTR) szLastSubjects[index]);
                }

            if(nSubjCount > 0)
                SendMessage(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT), CB_SETCURSEL , 0, 0);
            else {
				_TCHAR  strSubject[MAX_PATH];
				_stprintf(strSubject, _T("Quick message from "), szSendFrom);
                SetWindowText(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT), strSubject);
                }
            

            // Initialize To field
            HWND    hwndList = GetDlgItem(hwndMainDlg, IDC_LIST_NAMES);

            int nItemsNumber = (int)SendMessage(hwndList, LB_GETCOUNT, 0, 0);
            int *nSelected = new int[nItemsNumber];
            nItemsNumber = (int)SendMessage(hwndList, LB_GETSELITEMS, nItemsNumber, (LPARAM) (LPINT)nSelected);

            if(nItemsNumber > 0) {
                for(int j = 0; j < nItemsNumber; j++) {
                    RECIPIENTDATALIST::iterator i;
                    RecipientData       data;

                    SendMessage(hwndList, LB_GETTEXT, nSelected[j], (LPARAM) (LPCTSTR) data.szName);
                    for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i, index++)
                        if(_tcscmp(data.szName, i->szName) == 0) {
                            if(j > 0)
                                _tcscat(strTo,_T("; "));
                            _tcscat(strTo, i->szAddress);
                            }
                    }
                }

            delete [] nSelected;

            SetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_SEND_TO), strTo);
            break;
            }

        case WM_COMMAND:
            if(LOWORD(wParam) == IDOK) {
                // Send mail 
                if(SendMail(hwndDlg) == UTE_SUCCESS)
        			EndDialog(hwndDlg, IDOK);
	    		}
            else if(LOWORD(wParam) == IDCANCEL) {
                EndDialog(hwndDlg, IDCANCEL);
                }
			break;

		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;

	    }
    
	return 0;
}

/***************************************
MainProc
    Main dialog box procedure
****************************************/
BOOL CALLBACK MainProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT    rect;
    POINT   pt;

	switch (message) {
        case WM_INITDIALOG: {

            // Initialize dialog handle
            hwndMainDlg = hwndDlg;

            // Load data from the registry
            LoadData();
            
            // Add Task Bar icon
            TaskBarIcon(hwndDlg, NIM_ADD);

            // Hide window
            ShowMainDlg(FALSE);

            // Set new window procedure for the list control
            lpPrevListFunc = (WNDPROC)(ULONG_PTR)GetWindowLong(GetDlgItem(hwndDlg, IDC_LIST_NAMES), GWL_WNDPROC);
            SetWindowLong(GetDlgItem(hwndDlg, IDC_LIST_NAMES), GWL_WNDPROC, (LONG)(ULONG_PTR)NameListProc);
            break;
            }

        // Resize the list control 
        case WM_SIZE: {
            HWND    hwndList = GetDlgItem(hwndDlg, IDC_LIST_NAMES);

            // Get current list left & top coordinates
            GetWindowRect(hwndList, &rect);
            pt.x = rect.left;
            pt.y = rect.top;
            ScreenToClient(hwndDlg, &pt);

            // Move list window
            MoveWindow(hwndList, pt.x, pt.y, LOWORD(lParam) - pt.x, HIWORD(lParam) - pt.y, TRUE);
            break;
            }

        case WM_TASKBAR_ICON_NOTIFY:
            if(wParam == ID_TASKBAR_ICON_QUICK_MAILER) {
                switch(lParam) {
                    case(WM_RBUTTONDOWN): 
                        {
                        UINT        unFlags = TPM_LEFTALIGN | TPM_TOPALIGN;
                        POINT       pt;
                        GetCursorPos(&pt);

                        SetActiveWindow(hwndDlg);

                        // Run menu
                        RunMenu(hwndDlg, IDR_MENU_TASKBAR_ICON, unFlags, pt.x, pt.y);
                        SetActiveWindow(NULL);
                        break;
                        }
                    case(WM_LBUTTONDOWN):
                        // Show main dialog
                        ShowMainDlg(TRUE);
                        break;
                    }
                }
			break;

        case WM_COMMAND:

            switch(LOWORD(wParam)) {
                case(ID_TASKBAR_SENDMAIL):
                    // Send mail to the selected mail recipients
                    if(IsNameSelected())
	                    DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SEND), hwndDlg, SendProc);
                    break;
                case(ID_TASKBAR_DELETEMAILRECIPIENTS):
                    {
                    // Delete selected mail recipients
                    HWND    hwndList = GetDlgItem(hwndDlg, IDC_LIST_NAMES);

                    int nItemsNumber = (int)SendMessage(hwndList, LB_GETCOUNT, 0, 0);
                    int *nSelected = new int[nItemsNumber];
                    nItemsNumber = (int)SendMessage(hwndList, LB_GETSELITEMS, nItemsNumber, (LPARAM) (LPINT)nSelected);

                    // Confirm deletion
                    if(nItemsNumber > 0) {
                        if(MessageBox(hwndDlg, _T("Delete selected names from the list?"), _T("Ultimate TCP/IP Quick Mailer"), MB_YESNO | MB_ICONQUESTION | MB_SYSTEMMODAL) == IDYES) {
                            for(int j = nItemsNumber-1; j >= 0; j--) {
                                _TCHAR    buffer[100];

                                // Delete from data list
                                SendMessage(hwndList, LB_GETTEXT, nSelected[j], (LPARAM) (LPCTSTR) buffer);
                                RECIPIENTDATALIST::iterator i;
                                for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i)
                                    if(_tcsicmp(buffer, i->szName) == 0) {
                                        RecipientDataList.erase(i);
                                        break;
                                        }

                                // Delete from list control
                                SendMessage(hwndList, LB_DELETESTRING, nSelected[j], 0);
                                }
                            }
                        }
                    else
                        MessageBox(hwndDlg, _T("There is nothing to delete."), _T("Ultimate TCP/IP Quick Mailer"), MB_OK | MB_ICONINFORMATION | MB_SYSTEMMODAL);

                    delete [] nSelected;

                    break;
                    }
                    
                case(ID_TASKBAR_EDITMAILRECIPIENT):
                	// Show the AddMailRecipient dialog box 
                    bEditMode = TRUE;
	                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_ADDMAILRECIPIENT), hwndDlg, AddMailRecipientProc);
                    bEditMode = FALSE;
                    break;
                case(ID_TASKBAR_ADDMAILRECIPIENT):
                	// Show the AddMailRecipient dialog box 
	                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_ADDMAILRECIPIENT), hwndDlg, AddMailRecipientProc);
                    break;
                case(ID_TASKBAR_PROPERTIES):
                	// Show the properties dialog box 
	                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_PROPERTIES), hwndDlg, PropertiesProc);
                    break;

                case(ID_TASKBAR_HELP):
                	// Show the html help page
                    ShellExecute(NULL, NULL, _T("QuickMailerHelp.htm"),NULL, NULL, 0);
                    break;
                case(ID_TASKBAR_ABOUT):
                	// Show the about box 
	                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_ABOUT), NULL, AboutProc);
                    break;
                case(ID_TASKBAR_EXIT):
                    // Post Close message
                    EndDialog(hwndDlg, IDOK);
                    break;

	    		}			

            break;


		case WM_CLOSE:
            ShowMainDlg(FALSE);
			return 0;

        case WM_DESTROY:
            // Save data to the registry
            SaveData();

            // Delete task bar icon
            TaskBarIcon(hwndDlg, NIM_DELETE);
            break;
    	}

	return 0;
}

/*****************************************
TaskBarIcon
	Executes task bar icon commands
Params
    dwCmd - command to execute. Can be one of:
                NIM_ADD
                NIM_DELETE
                NIM_MODIFY
Return
	none
******************************************/
void TaskBarIcon(HWND hwndWnd, DWORD dwCmd)
{
   
    NOTIFYICONDATA tnid;
    tnid.uFlags		        = NIF_MESSAGE|NIF_ICON|NIF_TIP;
    tnid.uCallbackMessage   = WM_TASKBAR_ICON_NOTIFY;
    tnid.hIcon		        = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON_QUICK_MAILER_SMALL));
    tnid.cbSize             = sizeof(NOTIFYICONDATA);
    tnid.hWnd               = hwndWnd;
    tnid.uID                = ID_TASKBAR_ICON_QUICK_MAILER;
    _tcscpy(tnid.szTip, _T("Ultimate TCP/IP Quick Mailer"));

    Shell_NotifyIcon(dwCmd, &tnid);
}

/*****************************************
RunMenu
	Runs the popup menu
Params
    hWnd    - parent window
    idMenu  - menu id
    uFlags  - screen-position and mouse-button flags
    rect    - menu position 
              NOTE!!! rect.right and rect.bottom are used
Return
	none
******************************************/
void RunMenu(HWND hWnd, UINT idMenu, UINT uFlags, int x, int y)
{
    HMENU   hMenu = LoadMenu(hInst, MAKEINTRESOURCE(idMenu));
    HMENU   hMenuTrackPopup = GetSubMenu (hMenu, 0);      

    if(hMenu != NULL) {
        // Disable some menu items
        if(!IsNameSelected()) {
            EnableMenuItem(hMenuTrackPopup, ID_TASKBAR_SENDMAIL, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
            EnableMenuItem(hMenuTrackPopup, ID_TASKBAR_DELETEMAILRECIPIENTS, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
            EnableMenuItem(hMenuTrackPopup, ID_TASKBAR_EDITMAILRECIPIENT, MF_GRAYED|MF_DISABLED|MF_BYCOMMAND);
            }
        // Run menu
        TrackPopupMenu(hMenuTrackPopup, uFlags, x, y, 0, hWnd, NULL);        
        DestroyMenu(hMenu);
        }
}

/*****************************************
IsNameSelected
	Checks if any name selected in the list
Params
    none
Return
	TRUE if yes
******************************************/
BOOL IsNameSelected()
{
    HWND    hwndList = GetDlgItem(hwndMainDlg, IDC_LIST_NAMES);
    int nItemsNumber = (int)SendMessage(hwndList, LB_GETCOUNT, 0, 0);
    int *nSelected = new int[nItemsNumber];
    nItemsNumber = (int)SendMessage(hwndList, LB_GETSELITEMS, nItemsNumber, (LPARAM) (LPINT)nSelected);
    delete [] nSelected;
    return (BOOL)nItemsNumber;
}

/*****************************************
SendMail
	Sends mail message
Params
    Send dialog box handle
Return
	none
******************************************/
int SendMail(HWND hwndDlg)
{
    CUT_SMTPClient  smtp;
    CUT_MXLookup    mxLookup;
    int             rt = UTE_SUCCESS;
    _TCHAR          szHostName[MAX_PATH];
    _TCHAR          *lpszMessage, *lpszTo, *lpszSubject;

    HCURSOR oldCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
    
	if(szHost != NULL )
		_tcscpy(szHostName, szHost);
	else
		*szHostName = _T('\0');

    // Get Data
    int nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT_SEND_TO));
    lpszTo = new _TCHAR[nLength + 2];
    GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_SEND_TO), lpszTo, nLength+1);
    
    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_EDIT_MESSAGE));
    lpszMessage = new _TCHAR[nLength + 2];
    GetWindowText(GetDlgItem(hwndDlg, IDC_EDIT_MESSAGE), lpszMessage, nLength+1);

    nLength = GetWindowTextLength(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT));
    lpszSubject = new _TCHAR[nLength + 2];
    GetWindowText(GetDlgItem(hwndDlg, IDC_COMBO_SUBJECT), lpszSubject, nLength+1);

    // Check for properties
    if(*szHostName == _T('\0')) {
        // If the host name is not set do the MX records lookup for each recipient
        _TCHAR            e_mail[MAX_PATH] = {_T("")};

// v4.2 TODO("This should be picking out each To address and using it - wrong stuff...")
// v4.2 TODO("Also see below - whole section should be reworked")
		
        CUT_StrMethods::ParseString(lpszTo, _T(";"), 0, e_mail, sizeof(e_mail)/sizeof(_TCHAR)-1);
        mxLookup.LookupMX(_T("A.ROOT-SERVERS.NET"), e_mail);
        if(mxLookup.GetMXRecordCount() > 0) {
            mxLookup.ResetEnum();
			// v4.2 using refactored GetMXRecord
			size_t size = 0;
			mxLookup.GetMXRecord(szHostName, MAX_PATH, &size);
            }
        else {
            SetCursor(oldCursor);
            MessageBox(hwndDlg, _T("Can't find the SMTP server!"), _T("Ultimate TCP/IP Quick Mailer"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
            return UTE_ERROR;
            }
        }

    // Send mail
    if((rt=smtp.SMTPConnect(szHostName)) == UTE_SUCCESS) {
        // Save new subjects
        AddSubject(lpszSubject);

        // Send
        rt=smtp.SendMail(lpszTo , szSendFrom, lpszSubject, lpszMessage);
        smtp.SMTPClose();
        }

    SetCursor(oldCursor);

    // Display error message
    if(rt != UTE_SUCCESS)
        MessageBox(hwndDlg, CUT_ERR::GetErrorString(rt), _T("Ultimate TCP/IP Quick Mailer"), MB_OK | MB_ICONEXCLAMATION | MB_SYSTEMMODAL);

    // Free memory
    delete [] lpszMessage;
    delete [] lpszTo;
    delete [] lpszSubject;

    return rt;
}

/*****************************************
LoadData
	Loads properties, names and other data
    from the registry
Params
    none
Return
	none
******************************************/
void LoadData()
{
    HKEY    key;
    DWORD   size, items = 0;
    _TCHAR    buf[1024];

    // Open up the key for the email config info
    if(RegCreateKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Ultimate TCP/IP\\QUICK_MAIL\\"), &key) != ERROR_SUCCESS)
        return; 

    // Get the host name
    size = sizeof(szHost)/sizeof(_TCHAR)-1;
    RegQueryValueEx(key, _T("SMTP_ServerName"), NULL,NULL,(LPBYTE)szHost, &size);
    
    // Get the from name
    size = sizeof(szSendFrom)/sizeof(_TCHAR)-1;
    RegQueryValueEx(key, _T("SendFrom"), NULL,NULL,(LPBYTE)szSendFrom, &size);

    // Get the run at start up flag
    size = sizeof(DWORD);
    RegQueryValueEx(key, _T("RunAtStartUp"), NULL,NULL,(LPBYTE)&dwRunAtStartUp, &size);

    // Get the number of names 
    size = sizeof(DWORD);
    RegQueryValueEx(key, _T("RecipientNumber"),NULL,NULL,(LPBYTE)&items, &size);

    // Read recipient data
	// v4.2 redeclared loop index i
	int i = 0;
	for(i=0; i<(int)items; i++) {
        RecipientData   data;

        // Get the name
        size = sizeof(data.szName)/sizeof(_TCHAR)-1;
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR),_T("Name%d"), i);
        *data.szName = NULL;
        RegQueryValueEx(key, buf, NULL,NULL,(LPBYTE)data.szName, &size);

        // Get the name
        size = sizeof(data.szAddress)/sizeof(_TCHAR)-1;
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR), _T("Address%d"), i);
        *data.szAddress = NULL;
        RegQueryValueEx(key, buf, NULL,NULL,(LPBYTE)data.szAddress, &size);

        // Add to the data list
        RecipientDataList.push_back(data);

        // Add to the names list control
        SendMessage(GetDlgItem(hwndMainDlg, IDC_LIST_NAMES), LB_ADDSTRING, 0, (LPARAM) (LPCTSTR) data.szName);
        }

    // Read last subjects
    nSubjCount = 0;
    for(i=0; i<10; i++) {
        // Get the name
        size = sizeof(szLastSubjects[nSubjCount])/sizeof(_TCHAR)-1;
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR),_T("Subject%d"), i);
        *szLastSubjects[nSubjCount] = NULL;
        if(RegQueryValueEx(key, buf, NULL,NULL,(LPBYTE)szLastSubjects[nSubjCount], &size) == ERROR_SUCCESS)
            if(_tcslen(szLastSubjects[nSubjCount]) > 0)
                ++nSubjCount;
        }

    // Read the main dialog window position
    size = sizeof(LONG);
    if(RegQueryValueEx(key, _T("WindowLeft"),NULL,NULL,(LPBYTE)&rectMainDlg.left, &size) != ERROR_SUCCESS)
        rectMainDlg.left = -1;
    if(RegQueryValueEx(key, _T("WindowRight"),NULL,NULL,(LPBYTE)&rectMainDlg.right, &size) != ERROR_SUCCESS)
        rectMainDlg.left = -1;
    if(RegQueryValueEx(key, _T("WindowTop"),NULL,NULL,(LPBYTE)&rectMainDlg.top, &size) != ERROR_SUCCESS)
        rectMainDlg.left = -1;
    if(RegQueryValueEx(key, _T("WindowBottom"),NULL,NULL,(LPBYTE)&rectMainDlg.bottom, &size) != ERROR_SUCCESS)
        rectMainDlg.left = -1;

}

/*****************************************
SaveData
	Saves properties, names and other data
    to the registry
Params
    none
Return
	none
******************************************/
void SaveData()
{
    HKEY    key;
    DWORD   items = 0;
    _TCHAR  buf[1024];

    // Open up the key for the email config info
    if(RegCreateKey(HKEY_CURRENT_USER, _T("SOFTWARE\\Ultimate TCP/IP\\QUICK_MAIL\\"), &key) != ERROR_SUCCESS)
        return; 

    // Put the host name
    RegSetValueEx(key, _T("SMTP_ServerName"), NULL, REG_SZ,(LPBYTE)szHost, (DWORD)_tcslen(szHost)*sizeof(_TCHAR));
    
    // Put the from name
    RegSetValueEx(key, _T("SendFrom"), NULL, REG_SZ,(LPBYTE)szSendFrom, (DWORD)_tcslen(szSendFrom)*sizeof(_TCHAR));

    // Put the run at start up flag
    RegSetValueEx(key, _T("RunAtStartUp"),NULL,REG_DWORD,(LPBYTE)&dwRunAtStartUp, sizeof(DWORD));

    // Put recipient data
    RECIPIENTDATALIST::iterator i;
    for (i = RecipientDataList.begin(); i != RecipientDataList.end(); ++i) {
        // Put the name
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR),_T("Name%d"), items);
        RegSetValueEx(key, buf, NULL, REG_SZ,(LPBYTE)i->szName, (DWORD)_tcslen(i->szName)*sizeof(_TCHAR));

        // Get the name
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR),_T("Address%d"), items);
        RegSetValueEx(key, buf, NULL, REG_SZ,(LPBYTE)i->szAddress, (DWORD)_tcslen(i->szAddress)*sizeof(_TCHAR));

        ++items;
        }

    // Put the number of names 
    RegSetValueEx(key, _T("RecipientNumber"),NULL,REG_DWORD,(LPBYTE)&items, sizeof(DWORD));

    // Write last subjects
    for(UINT j=0; j<10; j++) {
        _sntprintf(buf, sizeof(buf)/sizeof(_TCHAR),_T("Subject%d"), j);
        if(j < nSubjCount) {
            RegSetValueEx(key, buf, NULL, REG_SZ,(LPBYTE)szLastSubjects[j], (DWORD)_tcslen(szLastSubjects[j])*sizeof(_TCHAR));
            }
        else {
            RegSetValueEx(key, buf, NULL, REG_SZ,(LPBYTE)"", 0);
            }
       
        }

    // Put the main dialog window position
    GetWindowRect(hwndMainDlg, &rectMainDlg);
    RegSetValueEx(key, _T("WindowLeft"),NULL,REG_DWORD,(LPBYTE)&rectMainDlg.left, sizeof(LONG));
    RegSetValueEx(key, _T("WindowRight"),NULL,REG_DWORD,(LPBYTE)&rectMainDlg.right, sizeof(LONG));
    RegSetValueEx(key, _T("WindowTop"),NULL,REG_DWORD,(LPBYTE)&rectMainDlg.top, sizeof(LONG));
    RegSetValueEx(key, _T("WindowBottom"),NULL,REG_DWORD,(LPBYTE)&rectMainDlg.bottom, sizeof(LONG));
}


/*****************************************
AddSubject
	Adds new subject field to the list.
Params
    lpszSubject - subject to add
Return
	none
******************************************/
void AddSubject(LPCTSTR lpszSubject)
{
    int nShiftTo = nSubjCount;

    // Look for the same subject in the list
	// v4.2 redeclared loop index i
	unsigned int i = 0;
    for( i=0; i<nSubjCount; i++)
        if(_tcscmp(szLastSubjects[i], lpszSubject) == 0) {
            nShiftTo = i;
            break;
            }

    // Shift the list
    for(i=nShiftTo; i>=1; i--)
        _tcscpy(szLastSubjects[i], szLastSubjects[i-1]);

    // Copy new subject
    _tcscpy(szLastSubjects[0], lpszSubject);

    // Increase the counter
    if(nSubjCount < 10 && nShiftTo == (int)nSubjCount)
        ++nSubjCount;
}

/*****************************************
ShowMainDlg
	Shows main dialog window. When called for
    the first time - initialize window position
Params
    none
Return
	none
******************************************/
void ShowMainDlg(BOOL bState)
{
    RECT    rect;

    GetWindowRect(hwndMainDlg, &rect);

    // Hiding
    if(!bState && !bIsHidden) {
        // Hide window
        MoveWindow(hwndMainDlg, rect.left, rect.top + 2000, rect.right-rect.left, rect.bottom-rect.top, TRUE);
        bIsHidden = TRUE;

        SetActiveWindow(NULL);
        }

    else if(bState && bIsHidden) {

        SetActiveWindow(hwndMainDlg);

        // Move window
        if(bMoved) {
            RECT        rect;
			POINT       pt = {0,0};

            bMoved = FALSE;
            SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, NULL);

            if(rectMainDlg.left != -1 && rectMainDlg.left < rect.right && rectMainDlg.top < rect.bottom) {
                MoveWindow(hwndMainDlg, rectMainDlg.left, rectMainDlg.top, rectMainDlg.right-rectMainDlg.left, rectMainDlg.bottom-rectMainDlg.top, TRUE);
                }
            else {
                APPBARDATA  data;
                int     nWidth = 200, nHeight = 200;

                // Get task bar positon
                data.cbSize = sizeof(APPBARDATA);
                data.hWnd = FindWindow(_T("Shell_TrayWnd"), NULL);

                if(data.hWnd != NULL) {
                    SHAppBarMessage(ABM_GETTASKBARPOS, &data);
                    UINT uEdge = GetTaskBarEdge(data.rc);

                    switch(uEdge) {
                        case ABE_LEFT:
                            pt.x = data.rc.right;
                            pt.y = rect.bottom - nHeight;
                            break;
                        case ABE_RIGHT:
                            pt.x = data.rc.left - nWidth;
                            pt.y = rect.bottom - nHeight;
                            break;
                        case ABE_TOP:
                            pt.x = rect.right - nWidth;
                            pt.y = data.rc.bottom;
                            break;
                        case ABE_BOTTOM:
                        default:
                            pt.x = rect.right - nWidth;
                            pt.y = data.rc.top - nHeight;
                            break;
                        }
                    }

                // Set initial window position
                MoveWindow(hwndMainDlg, pt.x, pt.y, nWidth, nHeight, TRUE);
                }
            }
        else
            MoveWindow(hwndMainDlg, rect.left, rect.top - 2000, rect.right-rect.left, rect.bottom-rect.top, TRUE);

        // Make top most
        SetWindowPos(hwndMainDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);

        SetFocus(hwndMainDlg);

        bIsHidden = FALSE;
        }   
}

/*****************************************
GetTaskBarEdge
	Gets the position of the task bar.
Params
    rc  - task bar rect
Return
    ABE_LEFT
    ABE_TOP
    ABE_BOTTOM
    ABE_RIGHT
    or -1 if error
******************************************/
UINT GetTaskBarEdge(RECT rc)
{
    UINT uEdge = 0xFFFFFFFF;

    if (rc.top == rc.left && rc.bottom > rc.right)
      uEdge = ABE_LEFT;
    else if (rc.top == rc.left && rc.bottom < rc.right)
      uEdge = ABE_TOP;
    else if (rc.top > rc.left )
      uEdge = ABE_BOTTOM;
    else
      uEdge = ABE_RIGHT;

    return uEdge;
}

#pragma warning ( pop )