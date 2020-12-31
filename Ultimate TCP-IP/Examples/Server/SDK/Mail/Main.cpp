// =================================================================
//  Ultimate TCP/IP E-mail server 
//  File:  TEST.CPP
//
//
// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================

#include "stdafx.h"
#include "uh_ctrl.h"
#include "UT_MailServer.h"
#include "fileman.h"
#include "main.h"
#include <commctrl.h>
#include "ut_strop.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

// local define to restrict connections but allow for client testing - comment out
// for normal operation
#define UT_CLIENT_TESTING_ONLY


CUH_Control			status;
CUH_Control			*ctrlHistory = &status;
CUT_MailServer		*MailServer;
HFONT				hFont	=	CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));
CUT_UserInfo		*g_pUserInfo;
HINSTANCE hInst;

#define	EMAIL_REGISTRY_FOLDER	_T("SOFTWARE\\Ultimate TCP/IP\\EMAIL_SV3")
#define EMAIL_ROOT_PATH			_T("D:\\MailRoot\\")
#define	SPLASH_BITMAP_CX		359	
#define	SPLASH_BITMAP_CY		250
int							g_CurrentEditSel = -1;

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
			KillTimer(hwndDlg, nSplashTimerID);
			nSplashTimerID = 0;
		}
		break;
	}
	
	return 0;
}


void EnableButton(HWND hwnd, long id) {
	HWND BtnWnd = GetDlgItem(hwnd,id);
    EnableWindow(BtnWnd, TRUE);
}

void DisableButton(HWND hwnd, long id) {
	HWND BtnWnd = GetDlgItem(hwnd,id);
    EnableWindow(BtnWnd, FALSE);
}

void ShutDown(void) {
	if(NULL != MailServer) {
		
		status.AddLine(_T("Server shutting down ..."));
		SetCursor(LoadCursor(NULL, IDC_WAIT));
		MailServer->GetSMTPServer()->StopAccept();
		MailServer->GetPOP3Server()->StopAccept();
		MailServer->GetSMTPServer()->SetShutDownFlag(TRUE);
		MailServer->GetPOP3Server()->SetShutDownFlag(TRUE);
		
		_TCHAR buf[80];
		
		// v4.2 TD interesting little bug - using CUT_Str::sntprintf, 
		// max connections not properly fmted. (First noticed in vc 6)
		//		CUT_Str::sntprintf(buf, 80,80,_T("Active POP3 connections: %d (max %d)"),
		_sntprintf(buf, 80,_T("Active POP3 connections: %d (max %d)"),
			MailServer->GetPOP3Server()->GetNumConnections(),
			MailServer->GetPOP3Server()->GetMaxConnections());
		status.AddLine(buf);
		
		//		CUT_Str::sntprintf(buf, 80,80,_T("Active SMTP connections: %d (max %d)"),
		_sntprintf(buf, 80,_T("Active SMTP connections: %d (max %d)"),
			MailServer->GetSMTPServer()->GetNumConnections(),
			MailServer->GetSMTPServer()->GetMaxConnections());
		status.AddLine(buf);
		
		SendMessage(status.m_hWnd, WM_PAINT, 0L, 0L);
		
		delete MailServer;
		MailServer = NULL;
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		status.AddLine(_T("Server stopped"));
		
	}
	
}

void StartUp(void) {
	// Start up the E-mail server 
	
	if(NULL == MailServer) {
		MailServer = new CUT_MailServer;
		
		MailServer->Sys_SetRootKey(EMAIL_REGISTRY_FOLDER);
		MailServer->Sys_SetRootPath(EMAIL_ROOT_PATH);
		MailServer->GetPOP3Server()->SetMaxConnections( 100 );
		MailServer->GetSMTPServer()->SetMaxConnections( 400 );
		
		status.AddLine(_T("Users:"));
		
		int	nResult = 0;
		if ((nResult = MailServer->Start()) != UTE_SUCCESS) {
			status.AddLine(_T("E-mail server failed to startup: "));
			status.AppendToLine(CUT_ERR::GetErrorString(nResult));
			if(nResult == UTE_USER_INFO_LOAD_FAILED || nResult == UTE_SYSTEM_INFO_LOAD_FAILED)
				status.AddLine(_T("Make sure you configured your server correctly."));
		}
		else {
			status.AddLine(_T("E-mail server started"));
		}
	}
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int)
{
	hInst = hInstance;
	
	
	// in this sample we will be using the new comon control IP Address
	// so we need toRegisters ICC_INTERNET_CLASSES common control classes from the common control dynamic-link library (DLL). 
	INITCOMMONCONTROLSEX		intSt;
	intSt.dwICC					= ICC_INTERNET_CLASSES ;
	intSt.dwSize				= (BYTE) sizeof(INITCOMMONCONTROLSEX); 
	InitCommonControlsEx(&intSt);
	
	
	// Initialize the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_SPLASH), NULL, Splash);
	
	// Create modal dialog box
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC )DlgProc);
	DeleteObject(hFont);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			
			status.AttachHistoryWindow(hwnd, IDC_STATUS);
			status.SetHistoryLength(500);
			status.SetFont(hFont);
			
			MailServer = NULL;
			StartUp();
			DisableButton(hwnd, IDC_STARTUP);

#if defined UT_CLIENT_TESTING_ONLY
			MailServer->GetPOP3Server()->SetMaxConnections(5);
			MailServer->GetSMTPServer()->SetMaxConnections(5);
			status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
			status.AddLine(_T("of Ultimate TCP-IP. Maximum number of simultaneous connections is 5."),RGB(255,0,0));
			status.AddLine(_T("________________________________________________________________"));
#endif
		}
		break;
		
	case WM_CLOSE:
		ShutDown();
		EndDialog(hwnd, 0);
		break;
		
	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case IDC_CONFIG:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CONFIG), hwnd, ConfigureProc);
				break;
			case IDC_EXIT:
				delete MailServer;
				EndDialog(hwnd, 0);
				break;
				
			case IDC_ABOUT:
				// Display about box
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
				break;
				
			case IDC_SHUTDOWN: {
				
				DisableButton(hwnd, IDC_CONFIG);
				
				ShutDown();
				
				DisableButton(hwnd, IDC_SHUTDOWN);
				EnableButton(hwnd, IDC_STARTUP);
				
							   }
				break;
				
			case IDC_STARTUP: {
				StartUp();
				EnableButton(hwnd, IDC_CONFIG);
				EnableButton(hwnd, IDC_SHUTDOWN);
				DisableButton(hwnd, IDC_STARTUP);
				
							  }
				break;
			}
		}
	case WM_SIZE: {
		
		RECT rect, clientRect;
		POINT pnt;
		
		HWND statWnd = GetDlgItem(hwnd,IDC_STATUS);
		
		GetWindowRect(statWnd, &rect);
		pnt.x = rect.left;
		pnt.y = rect.top;
		ScreenToClient(hwnd, &pnt);
		
		GetClientRect(hwnd, &clientRect);
		
		rect.top = pnt.y;
		rect.left = pnt.x;
		
		rect.right = clientRect.right - rect.left;
		rect.bottom = clientRect.bottom - rect.left;
		
		MoveWindow(statWnd, rect.left, rect.top, rect.right-rect.left,rect.bottom-rect.top,TRUE);
		
		return 1;
				  }
		break;
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

//IDD_MODIFY_USERS_INFO Dialog Proc
BOOL CALLBACK ModifyUserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
		
	case WM_INITDIALOG:
		{
			// v4.2 unrefed var removed
			//HWND hwndLB = GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST);
			
			SetDlgItemText(hwnd, IDC_MODIFY_USER_NAME, g_pUserInfo->szUserName);
			SetDlgItemText(hwnd, IDC_MODIFY_NEW_NAME, g_pUserInfo->szUserName);
			EnableWindow(GetDlgItem(hwnd,IDC_MODIFY_USER_NAME),FALSE);
			SetDlgItemText(hwnd, IDC_MODIFY_PASSWORD, g_pUserInfo->szPassword );
			// loop through the available email aliases for this user and pouplate the list box	
			// v4.2 g_pUserInfo->listEmailAddresses now using CUT_TStringList
			_TCHAR szTemp[MAX_PATH];
			for (int counter= 0; counter < g_pUserInfo->listEmailAddresses.GetCount (); counter++) {
				_tcscpy(szTemp, g_pUserInfo->listEmailAddresses.GetString (counter));
				SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_ADDSTRING, 0, (LPARAM) szTemp );
			}
		}
		break;
		
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
			{
				EndDialog(hwnd, 0);
				break;
			}
		case IDOK:
			{
				// loop through the list and populate the string list from the listbox
				//LB_GETCOUNT 
				int count = 0;
				_TCHAR szOrigName[MAX_PATH];
				_TCHAR szAlias[MAX_PATH];
				_TCHAR newPassword[MAX_PATH];
				_TCHAR newName[MAX_PATH];
				
				CUT_TStringList newListAliases;
				
				
				count = (int)SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_GETCOUNT, 0, 0);
				if (count == LB_ERR )
					break;
				for (int loop = 0; loop < count; loop++)
				{
					SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_GETTEXT, loop, (LPARAM) (LPCSTR)szAlias);
					newListAliases.AddString (szAlias);
				}
				GetDlgItemText(hwnd, IDC_MODIFY_USER_NAME, szOrigName,MAX_PATH);
				GetDlgItemText(hwnd, IDC_MODIFY_NEW_NAME, newName,MAX_PATH);
				GetDlgItemText(hwnd, IDC_MODIFY_PASSWORD, newPassword,MAX_PATH );
				
				// call the modify user selection
				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				
				int retCode = pUserManager->User_Modify (szOrigName,newName,newPassword,&newListAliases);
				if (retCode != UTE_SUCCESS)
				{
					MessageBox (hwnd,CUT_ERR::GetErrorString (retCode),_T("Error Update Failed"),MB_OK);
					break;
				}
				else
					EndDialog(hwnd, 0);
				break;
			}
		case IDC_REMOVE_ALIASE:
			{
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_GETCURSEL, 0, 0);
				SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_DELETESTRING, nIndex, 0);
				break;
			}
			
		case IDC_ADD_ALIAS:
			{
				_TCHAR szAliase[MAX_PATH];
				
				GetDlgItemText(hwnd, IDC_NEW_EMAIL_ALIAS, szAliase, 127);
				
				SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_ADDSTRING, 0, (LPARAM) szAliase);
				SetDlgItemText(hwnd, IDC_NEW_EMAIL_ALIAS, _T(""));
				
				break;
			}		
// v4.2 unreachable code
//			return 0;
		}
	}
	return 0;
}


BOOL CALLBACK UserConfigureProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
		
	case WM_INITDIALOG:
		{
			
			HWND hwndLB = GetDlgItem(hwnd, IDC_USER_LIST);
			CUT_UserInfo* pUserInfo;
			
			CUT_UserManager* pUserManager = MailServer->GetUserManager();
			for (int i = 0; i < pUserManager->User_GetCount(); i++) {
				
				pUserInfo = pUserManager->User_GetUser(i);
				if (pUserInfo != NULL) {
				// v4.2 userinfo now holds _TCHARs
					_TCHAR szTemp[MAX_PATH];
					_tcscpy(szTemp, pUserInfo->szUserName);
					SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM) szTemp);
					//						SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM) pUserInfo->szUserName);
				}
			}
			g_pUserInfo = NULL;
		}
		break;
		
	case WM_COMMAND:
		
		switch (HIWORD(wParam)) {
		case LBN_SELCHANGE:
			{
				
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
				//int nRequiredLength = SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETTEXTLEN, nIndex, 0);
				
				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				CUT_UserInfo* pUserInfo = pUserManager->User_GetUser(nIndex);
				
				if (pUserInfo != NULL)
				{
					
					SetDlgItemText(hwnd, IDC_USER_NAME, pUserInfo->szUserName);
					SetDlgItemText(hwnd, IDC_USER_PASSWORD, pUserInfo->szPassword);
					SetDlgItemText(hwnd, IDC_USER_MAIL, pUserInfo->listEmailAddresses.GetString(0L));
				}
				break;
			}
		case LBN_DBLCLK :
			{
				// call the modify user selection
				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
				g_pUserInfo = pUserManager->User_GetUser(nIndex);
				
				if (g_pUserInfo != NULL)
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY_USERS_INFO), hwnd, (DLGPROC )ModifyUserProc);
				}
				break;
			}
			
		}
		switch (LOWORD(wParam)) 
		{
		case IDCANCEL:
		case IDOK:
			EndDialog(hwnd, 0);
			break;
			
		case IDC_BUTTON_USER_INFO:
			{
				// call the modify user selection
				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
				g_pUserInfo = pUserManager->User_GetUser(nIndex);
				
				if (g_pUserInfo != NULL)
					DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY_USERS_INFO), hwnd, (DLGPROC )ModifyUserProc);
			}
			break;
		case IDC_ADD_USER:
			_TCHAR szUserName[128], szPassword[128], szMailAddress[128];
			szUserName[0] = szPassword[0] = szMailAddress[0] = 0;
			
			GetDlgItemText(hwnd, IDC_USER_NAME, szUserName, 127);
			GetDlgItemText(hwnd, IDC_USER_PASSWORD, szPassword, 127);
			GetDlgItemText(hwnd, IDC_USER_MAIL, szMailAddress, 127);
			
			if (SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_FINDSTRING, (WPARAM)-1, (LPARAM) szUserName) != LB_ERR) {
				
				MessageBox(hwnd, _T("A user with that name already exists. Choose another user name."), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			else if (_tcslen(szUserName) && _tcslen(szPassword) && _tcslen(szMailAddress)) {
				
				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				pUserManager->User_Add(szUserName,szPassword, szMailAddress);
				
				SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_ADDSTRING, 0, (LPARAM) szUserName);
			}
			else {
				
				MessageBox(hwnd, _T("Please specify a user name, password and address"), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			break;
			
		case IDC_REMOVE_USER:
			
			int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
			int nRequiredLength = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETTEXTLEN, nIndex, 0);
			_TCHAR* pszUserName = new _TCHAR[nRequiredLength + 1];
			
			// Remove the selected item from the list box and clear the text
			// in the edit controls.
			SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETTEXT, nIndex, (LPARAM) pszUserName);
			SendMessage(GetDlgItem(hwnd, IDC_USER_NAME), EM_REPLACESEL, 0, (LPARAM) _T(""));
			SendMessage(GetDlgItem(hwnd, IDC_USER_PASSWORD), EM_REPLACESEL, 0, (LPARAM) _T(""));
			SendMessage(GetDlgItem(hwnd, IDC_USER_MAIL), EM_REPLACESEL, 0, (LPARAM) _T(""));
			SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_DELETESTRING, nIndex, 0);
			CUT_UserManager* pUserManager = MailServer->GetUserManager();
			pUserManager->User_Delete(pszUserName);
			delete [] pszUserName;
			break;
		}
	}
	
	return 0;
}

BOOL CALLBACK DNSServersConfigureProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
		
	case WM_INITDIALOG:
		{
			// Set title
			SetDlgItemText(hwnd, IDC_STATIC_TITLE, _T(" DNS Servers: "));
			
			// Fill the list
			HWND hwndLB = GetDlgItem(hwnd, IDC_USER_LIST);
			for (unsigned int i = 0; i < MailServer->Sys_GetDNSNamesCount(); i++) {
				SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM) MailServer->Sys_GetDNSName(i));
			}
		}
		break;
		
	case WM_COMMAND:
		
		switch (HIWORD(wParam)) 
		{
		case LBN_SELCHANGE:
			{
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
				SetDlgItemText(hwnd, IDC_USER_NAME, MailServer->Sys_GetDNSName(nIndex));
				break;
			}
		}
		switch (LOWORD(wParam)) 
		{
		case IDCANCEL:
		case IDOK:
			EndDialog(hwnd, 0);
			break;
			
		case IDC_ADD_USER:
			_TCHAR szBuffer[1024];
			
			GetDlgItemText(hwnd, IDC_USER_NAME, szBuffer, 1024);
			
			if (SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_FINDSTRING, (WPARAM)-1, (LPARAM) szBuffer) != LB_ERR) 
			{
				MessageBox(hwnd, _T("This DNS Server name is already in the list."), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			else if (_tcslen(szBuffer)) 
			{
				MailServer->Sys_AddDNSName(szBuffer);
				SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_ADDSTRING, 0, (LPARAM) szBuffer);
				SetDlgItemText(hwnd, IDC_USER_NAME, _T(""));
			}
			else 
			{
				MessageBox(hwnd, _T("Please specify a DNS Server name"), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			break;
			
		case IDC_REMOVE_USER:
			
			int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
			
			MailServer->Sys_DeleteDNSName(nIndex);
			
			// Remove the selected item from the list box and clear the text
			// in the edit controls.
			SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_DELETESTRING, nIndex, 0);
			SetDlgItemText(hwnd, IDC_USER_NAME, _T(""));
			break;
		}
	}
	
	return 0;
}

BOOL CALLBACK DomainConfigureProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {
		
	case WM_INITDIALOG:
		{
			// Set title
			SetDlgItemText(hwnd, IDC_STATIC_TITLE, _T(" Domain Names: "));
			
			// Fill the list
			HWND hwndLB = GetDlgItem(hwnd, IDC_USER_LIST);
			for (unsigned int i = 0; i < MailServer->Sys_GetLocalNamesCount(); i++) {
				SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM) MailServer->Sys_GetLocalName(i));
			}
		}
		break;
		
	case WM_COMMAND:
		
		switch (HIWORD(wParam)) 
		{
		case LBN_SELCHANGE:
			{
				int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
				SetDlgItemText(hwnd, IDC_USER_NAME, MailServer->Sys_GetLocalName(nIndex));
				break;
			}
		}
		switch (LOWORD(wParam)) 
		{
		case IDCANCEL:
		case IDOK:
			EndDialog(hwnd, 0);
			break;
			
		case IDC_ADD_USER:
			_TCHAR szBuffer[1024];
			
			GetDlgItemText(hwnd, IDC_USER_NAME, szBuffer, 1024);
			
			if (SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_FINDSTRING, (WPARAM)-1, (LPARAM) szBuffer) != LB_ERR) 
			{
				MessageBox(hwnd, _T("This DNS Server name is already in the list."), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			else if (_tcslen(szBuffer)) 
			{
				MailServer->Sys_AddLocalName(szBuffer);
				SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_ADDSTRING, 0, (LPARAM) szBuffer);
				SetDlgItemText(hwnd, IDC_USER_NAME, _T(""));
			}
			else 
			{
				MessageBox(hwnd, _T("Please specify a DNS Server name"), _T("Error"), MB_OK|MB_ICONINFORMATION);
			}
			break;
			
		case IDC_REMOVE_USER:
			
			int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);
			
			MailServer->Sys_DeleteLocalName(nIndex);
			
			// Remove the selected item from the list box and clear the text
			// in the edit controls.
			SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_DELETESTRING, nIndex, 0);
			SetDlgItemText(hwnd, IDC_USER_NAME, _T(""));
			break;
		}
	}
	
	return 0;
}

BOOL CALLBACK ConfigureProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) 
	{
	case WM_INITDIALOG:
		{
			// Set data folder
			SetDlgItemText(hwnd, IDC_EDIT_ROOT_PATH, MailServer->Sys_GetRootPath());
			
			// Set sending/receiving options
			SetDlgItemInt(hwnd, IDC_EDIT_MAX_RETRIES, MailServer->Sys_GetMaxRetries(), FALSE);
			SetDlgItemInt(hwnd, IDC_EDIT_RETRY_INTERVAL, MailServer->Sys_GetRetryInterval(), FALSE);
			SetDlgItemInt(hwnd, IDC_EDIT_MAX_THREAD, MailServer->Sys_GetMaxOut(), FALSE);
		}
		break;
		
	case WM_COMMAND:
		switch (LOWORD(wParam)) 
		{
		case IDCANCEL:
		case IDOK:
			{
				BOOL	bResult;
				_TCHAR	szBuffer[2*MAX_PATH];
				
				// Set data folder
				GetDlgItemText(hwnd, IDC_EDIT_ROOT_PATH, szBuffer, sizeof(szBuffer)/sizeof(_TCHAR));
				MailServer->Sys_SetRootPath(szBuffer);
				
				// Set sending/receiving options
				MailServer->Sys_SetMaxRetries(GetDlgItemInt(hwnd, IDC_EDIT_MAX_RETRIES, &bResult, FALSE));
				MailServer->Sys_SetRetryInterval(GetDlgItemInt(hwnd, IDC_EDIT_RETRY_INTERVAL, &bResult, FALSE));
				MailServer->Sys_SetMaxOut(GetDlgItemInt(hwnd, IDC_EDIT_MAX_THREAD, &bResult, FALSE));
				
				// Save settings into the registry
				MailServer->GetUserManager()->SaveUserInfo(EMAIL_REGISTRY_FOLDER);
				MailServer->SaveSystemInfo(EMAIL_REGISTRY_FOLDER);
				
				EndDialog(hwnd, wParam);
				break;
			}
		case IDC_BUTTON_USERS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, UserConfigureProc);
			break;
		case IDC_BUTTON_DNS_NAMES:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_LIST), hwnd, DNSServersConfigureProc);
			break;
		case IDC_BUTTON_DOMAIN_NAMES:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_LIST), hwnd, DomainConfigureProc);
			break;
		case IDC_BUTTON_RELAY_IP:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_RELAY_CONFIG), hwnd, DlgIPConfig);
			break;
			
			
			
		}
	}
	
	return 0;
}

//
// in this dialog proc we will handle the display of 
// the currently list of IP that we are attempting to control the 
// access of our server
BOOL CALLBACK DlgIPConfig(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
	case WM_INITDIALOG:
		{
			// disable the delete and edit buttons
			EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),FALSE);			
			EnableWindow(GetDlgItem(hwnd, IDC_EDIT_IP),FALSE);
			// call the refresh button to display a fresh list of the selected 
			// list
			SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH_IP,0);
			
			
			
			
			
			
			return 1;
		}
		// close window message
	case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			break;
		}
		// Handle the window command buttons
	case WM_COMMAND:
		{
			switch (HIWORD(wParam) )
			{
			case LBN_SELCHANGE:
				{
					// get number of elements in th elist
					int count = (int)SendMessage(GetDlgItem(hwnd, IDC_IP_LIST) ,LB_GETCOUNT ,0,0);
					// if we have any elements
					if (count > 0)
					{
						// we can delete so enable it						
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),TRUE);
						// we don't want to enable the edit in the case of temporary block
						//	if (g_enAccessType != ACCESS_TEMP_BLOCKED)
						EnableWindow(GetDlgItem(hwnd, IDC_EDIT_IP),TRUE);
						
					}
					else
					{
						// disable the delete and edit buttons
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),FALSE);			
						EnableWindow(GetDlgItem(hwnd, IDC_EDIT_IP),FALSE);
						
					}
					break;
					
				}
			case LBN_SELCANCEL:
				{
					// we lost focus so disable them
					// disable the delete and edit buttons
					EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),FALSE);			
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT_IP),FALSE);
					
					break;
				}
			case LBN_DBLCLK:
				{
					// SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_EDIT_IP,0);
				}
				
				
				
			}
			// what control issued the message
			switch(LOWORD(wParam))
			{
				// exit button was clicked
			case IDCANCEL:
				{
					EndDialog(hwnd,0);
					break;
				}
				// the user clicked on the Add button so lets 
				// lets allow him to enter a new IP address
			case IDC_ADD_IP:
				{
					// show the dialog box
					g_CurrentEditSel= -1;
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_IP_DLG), hwnd, (DLGPROC )DlgAddIP);
					// refresh the current display
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH_IP,0);				
					break;
					
				}
			case IDC_DELETE_IP:// delete the selected ip address
				{
					int count = (int)SendMessage(GetDlgItem(hwnd, IDC_IP_LIST) ,LB_GETCOUNT ,0,0);
					if (count > 0) // the list has elemenets ?
					{
						int nAnswer =  MessageBox(NULL, _T("Are you sure you want to remove the selected IP Address ?"),_T("Confirm") ,  MB_YESNO);
						if (nAnswer == IDYES)
						{
							// get the current selecteion
							int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_GETCURSEL, 0, 0);
							// then remove it from the blocked list
							//	g_Srvr.m_aclObj.DeleteAddress (g_enAccessType,nIndex);
							// send A message with delete command 
							MailServer->Sys_DeleteRelayAddress (nIndex);
							
							SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_DELETESTRING, nIndex, 0);
							// refresh the display 
							SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH_IP,0);
							
							EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),FALSE);		
							
						}
					}
					break;
				}
			case IDC_EDIT_IP:
				{
					// refresh the current display
					g_CurrentEditSel =  (int)SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_GETCURSEL, 0, 0);
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_IP_DLG), hwnd, (DLGPROC )DlgAddIP);
					
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH_IP,0);
					
				}
			case IDC_REFRESH_IP:
				{
					// get the number of aii addresses and display them on list box
					// refresh the current display in the 
					// list box based on the selected access type
					HWND hwndList = GetDlgItem(hwnd, IDC_IP_LIST);  
					
					// first clear the existing list
					SendMessage( 
						(HWND) hwndList,              // handle to destination window 
						LB_RESETCONTENT,          // message to send
						(WPARAM) 0,         // not used; must be zero
						(LPARAM) 0          // not used; must be zero
						);
					int counter = MailServer->Sys_GetRelayAddressCount ();
					
					for (int index = 0; index < counter; index++)
					{
						SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_ADDSTRING, 0, (LPARAM)MailServer->Sys_GetRelayAddress (index));
					}
					
					
					// disable the delete and edit buttons
					EnableWindow(GetDlgItem(hwnd, IDC_DELETE_IP),FALSE);			
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT_IP),FALSE);
					break;
				}
				// The user selected on of the radio buttons
				
			}
			break;
		}
		}
		return 0;
}


//
// Add a new IP address to the selected list d
BOOL CALLBACK DlgAddIP(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	
	static BOOL		bRangeCliecked = FALSE; // has the user selecetd a range
	_TCHAR szRelayLine[MAX_PATH];
	_TCHAR szStartString[MAX_PATH];
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
	case WM_INITDIALOG:
		{
			// get the user selection 
			// if it is not -1 then the user is editing the entry
			bRangeCliecked = FALSE;
			in_addr		ipEnd;
			in_addr		ipStart;
			DWORD dwAddr;
			
			
			if (g_CurrentEditSel != -1 )
			{
				// set up the IP Addess controls to hold the passwed ip address range
				
				// Get  the selected items string from the list of Relay servers 
				_tcscpy(szRelayLine, MailServer->Sys_GetRelayAddress (g_CurrentEditSel));
				
				// parse the range for - charachter if any is avilable 
				CUT_StrMethods::RemoveSpaces (szRelayLine);
				if (CUT_StrMethods::GetParseStringPieces (szRelayLine, _T("-")) > 1)
				{
					// get the start and end of the IP addresses
					CUT_StrMethods::ParseString (szRelayLine,_T("-"),0,szStartString, MAX_PATH-1);
					// v.42 replaced inet_addr with StrMethods overload
					ipStart.S_un.S_addr = CUT_WSServer::Inet_Addr(szStartString);
					// reverse the words for display
					dwAddr = (DWORD)htonl(ipStart.S_un.S_addr ) ;
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_SETADDRESS,0,(LPARAM)dwAddr);
					// reverse the words for display
					// get the start and end of the IP addresses
					CUT_StrMethods::ParseString (szRelayLine,_T("-"),1,szStartString ,MAX_PATH-1);
					// v.42 replaced inet_addr with StrMethods overload
					ipEnd.S_un.S_addr = CUT_WSClient::Inet_Addr(szStartString);
					dwAddr = (DWORD)htonl(ipEnd.S_un.S_addr );
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS2),IPM_SETADDRESS,0,(LPARAM)dwAddr);
					EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),TRUE);			
					bRangeCliecked = TRUE;
				}
				else
				{
					// v.42 replaced inet_addr with StrMethods overload
					ipStart.S_un.S_addr = CUT_WSServer::Inet_Addr(szRelayLine);
					// reverse the words for display
					dwAddr = (DWORD)htonl(ipStart.S_un.S_addr ) ;
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_SETADDRESS,0,(LPARAM)dwAddr);
					
				}
				
			} // otherwise it is a new address
			else
			{
				dwAddr = INADDR_ANY; //(DWORD)ipStart.S_un.S_addr  ;
				
				SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_SETADDRESS,0,(LPARAM)(DWORD)dwAddr);
				SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS2),IPM_SETADDRESS,0,(LPARAM)(DWORD)dwAddr);
				
				EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),FALSE);	
			}					
			CheckDlgButton (hwnd,IDC_RANGE, bRangeCliecked?BST_CHECKED:BST_UNCHECKED);
			EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),bRangeCliecked);
			
			return 1;
		}
		// close window message
	case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			break;
		}
		// Handle the window command buttons
	case WM_COMMAND:
		{
			
			// what control issued the message
			switch(LOWORD(wParam))
			{
				// exit button was clicked
			case IDCANCEL:
				{
					EndDialog(hwnd,0);
					break;
				}
			case IDOK:
				{
					
					DWORD dwStartAddr ; 
					DWORD dwEndAddr ; 
					in_addr adStart;
					in_addr adEnd ; 
					
					// 
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_GETADDRESS,0, (LPARAM)&dwStartAddr);
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS2),IPM_GETADDRESS,0, (LPARAM)&dwEndAddr);
					
					
					// ok so the IP Address control returns the address backward
					// oh well we will carve it then byte by byte
					// Start Address
					adStart.S_un.S_un_b.s_b1  = (unsigned char)FIRST_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b2  =(unsigned char)SECOND_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b3  =(unsigned char)THIRD_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b4  =(unsigned char)FOURTH_IPADDRESS((LPARAM )dwStartAddr);
					// v4.2 shouldn't need cvtcpy here - revisit
					CUT_Str::cvtcpy(szStartString,MAX_PATH,inet_ntoa (adStart));
					
					// // End Address
					adEnd.S_un.S_un_b.s_b1  =(unsigned char)FIRST_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b2  =(unsigned char)SECOND_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b3  =(unsigned char)THIRD_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b4  =(unsigned char)FOURTH_IPADDRESS((LPARAM )dwEndAddr);
					// v4.2 shouldn't need cvtcpy here - revisit
					CUT_Str::cvtcpy(szRelayLine,MAX_PATH,inet_ntoa (adEnd));				
					
					
					_TCHAR buf[MAX_PATH];
					if (bRangeCliecked)	
						_sntprintf(buf, MAX_PATH,_T("%s-%s"),szStartString,szRelayLine );
					else
						_sntprintf(buf, MAX_PATH,_T("%s"),szStartString);
					
					// if we are editing , then delete the selection before we add the modified one
					if (g_CurrentEditSel != -1)
					{
						MailServer->Sys_DeleteRelayAddress (g_CurrentEditSel);
						MailServer->Sys_AddRelayAddress (buf);	
					}
					else
					{
						MailServer->Sys_AddRelayAddress (buf);							
					}
					
					EndDialog(hwnd,0);
					break;					
				}
				
			case IDC_RANGE:
				{
					bRangeCliecked = !bRangeCliecked;
					EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),bRangeCliecked);
				}
				
			}
			break;
		}
	}
	return 0;
}

#pragma warning ( pop )