// =================================================================
//  Ultimate TCP/IP E-mail server 
//  File:  TEST.CPP
//
//
// =================================================================
// Ultimate TCP/IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================

#include "stdafx.h"
#include "uh_ctrl.h"
#include "UT_MailServer.h"
#include "fileman.h"
#include "main.h"
#include "..\..\..\..\Security\Include\UTCertifListDlg.h"
#include "..\..\..\..\Security\Include\UTCertifMan.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
// #define UT_CLIENT_TESTING_ONLY

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#define	EMAIL_REGISTRY_FOLDER	_T("SOFTWARE\\Ultimate TCP/IP\\EMAIL_SV3")
#define	SPLASH_BITMAP_CX		359	
#define	SPLASH_BITMAP_CY		250


CUH_Control			status;
CUH_Control			*ctrlHistory = &status;
CUT_MailServer		*MailServer;
HFONT				hFont	=	CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));
CUT_UserInfo		*g_pUserInfo;
HINSTANCE			hInst;
unsigned short		m_nSMTPPortNumber = 25;
unsigned short		m_nPOP3PortNumber = 110;
int					m_nProtocol = 0;
CUT_Certificate		m_Cert;
BOOL				m_bAuth = FALSE;
BOOL				m_bImmedNeg = FALSE;
CUT_CertificateListDlg	dlg;
_TCHAR				m_szStoreName[MAX_PATH + 1];
DWORD				m_dwStoreLocation = 0;

DWORD					nSplashTimerID;
BOOL					bServerRunning = FALSE;

void SaveOptions(HWND hwnd);
void ReadOptions();
void GetOptionsFromDlg(HWND hwnd);
BOOL CALLBACK UserOptionsProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */);

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

void ShutDown(HWND hwnd) 
{
	DisableButton(hwnd, IDC_BUTTON_START);

	status.AddLine(_T("Server shutting down ..."));
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	MailServer->GetSMTPServer()->StopAccept();
	MailServer->GetPOP3Server()->StopAccept();
	MailServer->GetSMTPServer()->SetShutDownFlag(TRUE);
	MailServer->GetPOP3Server()->SetShutDownFlag(TRUE);
	
	_TCHAR buf[80];
	wsprintf(buf, _T("Active POP3 connections: %d (max %d)"),
		MailServer->GetPOP3Server()->GetNumConnections(),
		MailServer->GetPOP3Server()->GetMaxConnections());
	status.AddLine(buf);

	wsprintf(buf, _T("Active SMTP connections: %d (max %d)"),
		MailServer->GetSMTPServer()->GetNumConnections(),
		MailServer->GetSMTPServer()->GetMaxConnections());
	status.AddLine(buf);

	SendMessage(status.m_hWnd, WM_PAINT, 0L, 0L);

	SetCursor(LoadCursor(NULL, IDC_ARROW));
	status.AddLine(_T("Server stopped"));
	bServerRunning = FALSE;
	SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Start"));
	EnableButton(hwnd, IDC_BUTTON_START);
}

int StartUp(HWND hwnd) 
{
	// Start up the E-mail server 
	int	nResult = UTE_ERROR;

	// get options from dialog controls
	GetOptionsFromDlg(hwnd);

	// check if certificate selected
	if(m_Cert.GetContext() == NULL)
	{
		MessageBox(hwnd, _T("You must select a valid certificate before starting the server!"), _T("Invalid Certificate"), MB_OK);
		status.AddLine(_T("Select the certificate first\r\n"));
		status.AppendToLine(CUT_ERR::GetErrorString(nResult));
		SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Start"));
		return nResult;
	}

	if(MailServer != NULL) 
	{
		delete MailServer;
	}

	MailServer = new CUT_MailServer;

	MailServer->Sys_SetRootKey(EMAIL_REGISTRY_FOLDER);

	status.AddLine(_T("Users:"));

	// Enable security
	CUT_POP3Server *serverPOP3 = MailServer->GetPOP3Server();
	serverPOP3->SetSecurityEnabled(TRUE);
	serverPOP3->SetCertificate(m_Cert);
	serverPOP3->SetSecurityProtocol(m_nProtocol);
	serverPOP3->SetPort(m_nPOP3PortNumber);
	serverPOP3->SetImmediateNegotiation(m_bImmedNeg);
	CUT_SMTPServer *serverSMTP = MailServer->GetSMTPServer();
	serverSMTP->SetSecurityEnabled(TRUE);
	serverSMTP->SetCertificate(m_Cert);
	serverSMTP->SetSecurityProtocol(m_nProtocol);
	serverSMTP->SetPort(m_nSMTPPortNumber);

	if ((nResult = MailServer->Start()) != UTE_SUCCESS) 
	{
		status.AddLine(_T("E-mail server failed to startup: "));
		status.AppendToLine(CUT_ERR::GetErrorString(nResult));
		SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Start"));
	}
	else 
	{
		status.AddLine(_T("E-mail server started"));
		bServerRunning = TRUE;
		SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Stop"));
	}

	return nResult;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	hInst = hInstance;
	
	// Initialize the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_SPLASH), NULL, Splash);

	// Create server object
	MailServer = new CUT_MailServer;
	MailServer->Sys_SetRootKey(EMAIL_REGISTRY_FOLDER);
	MailServer->LoadSystemInfo(EMAIL_REGISTRY_FOLDER);
	MailServer->GetUserManager()->LoadUserInfo(EMAIL_REGISTRY_FOLDER);

	// Create modal dialog box
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC )DlgProc);
	DeleteObject(hFont);

	// Delete server object 
	delete MailServer;
	MailServer = NULL;

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


				// fill list of possible protocols
				SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("Default"));
				SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("PCT 1.0"));
				SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("SSL 2.0"));
				SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("SSL 3.0"));
				SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("TLS 1.0"));

				// read settings from registry
				ReadOptions();

				// select protocol
				if(m_nProtocol == SP_PROT_PCT1)
					SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_SETCURSEL, 1, 0L);
				else if(m_nProtocol == SP_PROT_SSL2)
					SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_SETCURSEL, 2, 0L);
				else if(m_nProtocol == SP_PROT_SSL3)
					SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_SETCURSEL, 3, 0L);
				else if(m_nProtocol == SP_PROT_TLS1)
					SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_SETCURSEL, 4, 0L);
				else 
					SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_SETCURSEL, 0, 0L);

				// set port number
				SetDlgItemInt(hwnd, IDC_EDIT_PORT, m_nSMTPPortNumber, FALSE);
				SetDlgItemInt(hwnd, IDC_EDIT_PORT_POP3, m_nPOP3PortNumber, FALSE);

				// set authentication flag
				SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_SETCHECK, m_bAuth, 0L);
				SendDlgItemMessage(hwnd, IDC_CHECK_IMMEDIATE_NEG, BM_SETCHECK, m_bImmedNeg, 0L);

				// display certificate subject
				SetDlgItemText(hwnd, IDC_EDIT_CERT, m_Cert.GetSubject());

				StartUp(hwnd);

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
			// save settings
			SaveOptions(hwnd);

			ShutDown(hwnd);
			EndDialog(hwnd, 0);
			break;

		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON_CERT:
					{
						// select the certificate
						dlg.SetViewCertOnDblClk(FALSE);
						dlg.SetStoreNames(_T("MY"));
						// dlg.SetCertUsageFilter(CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE | CERT_KEY_AGREEMENT_KEY_USAGE);
						if(dlg.OpenDlg(hwnd) == IDOK && 
							dlg.GetSelectedCertificate() != NULL &&
							dlg.GetSelectedCertificate()->GetContext() != NULL )
						{
							m_Cert = *dlg.GetSelectedCertificate();
							SetDlgItemText(hwnd, IDC_EDIT_CERT, m_Cert.GetSubject());
							CUT_CertificateStore *store = dlg.GetSelectedStore();
							if(store)
							{
								m_dwStoreLocation = store->GetStoreLocation();
								_tcscpy(m_szStoreName, store->GetStoreName());
							}
						}

						break;
					}
				case IDC_CONFIG:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CONFIG), hwnd, ConfigureProc);
					break;
				case IDC_EXIT:
					EndDialog(hwnd, 0);
					break;

				case IDC_ABOUT:
					// Display about box
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					break;

				case IDC_BUTTON_START: 
				{
				
					if(bServerRunning)
						ShutDown(hwnd);	
					else
						StartUp(hwnd);
					break;
				}
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

BOOL CALLBACK ModifyUserProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) {

		case WM_INITDIALOG:
			{

				HWND hwndLB = GetDlgItem(hwnd, IDC_USER_LIST);
				CUT_UserInfo* pUserInfo;

				CUT_UserManager* pUserManager = MailServer->GetUserManager();
				for (int i = 0; i < pUserManager->User_GetCount(); i++) {

					pUserInfo = pUserManager->User_GetUser(i);
					if (pUserInfo != NULL){
						_TCHAR szTemp[MAX_PATH];
						_tcscpy(szTemp, pUserInfo->szUserName);
						SendMessage(hwndLB, LB_ADDSTRING, 0, (LPARAM) szTemp);
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
						DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY_USERS_INFO), hwnd, (DLGPROC )UserOptionsProc);
					}
					break;
					}
					
			}
			switch (LOWORD(wParam)) {
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
							DialogBox(hInst, MAKEINTRESOURCE(IDD_MODIFY_USERS_INFO), hwnd, (DLGPROC )UserOptionsProc);
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
						pUserManager->User_Add(szUserName, szPassword, szMailAddress);

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
					SendMessage(GetDlgItem(hwnd, IDC_USER_NAME), EM_REPLACESEL, 0, (LPARAM) "");
					SendMessage(GetDlgItem(hwnd, IDC_USER_PASSWORD), EM_REPLACESEL, 0, (LPARAM) "");
					SendMessage(GetDlgItem(hwnd, IDC_USER_MAIL), EM_REPLACESEL, 0, (LPARAM) "");
					SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_DELETESTRING, nIndex, 0);
					CUT_UserManager* pUserManager = MailServer->GetUserManager();
					pUserManager->User_Delete(pszUserName);
					delete [] pszUserName;
					break;
			}
	}

	return 0;
}

// Read options
void ReadOptions()
{
	DWORD   size;
	HKEY    key;

	// Open up the key for the email config info
	if(RegCreateKey(HKEY_LOCAL_MACHINE, EMAIL_REGISTRY_FOLDER, &key) != ERROR_SUCCESS)
		return;

	size = sizeof(int);
	if(RegQueryValueEx(key, _T("SMTPPort"), NULL, NULL, (LPBYTE)&m_nSMTPPortNumber, &size) != ERROR_SUCCESS) 
		m_nSMTPPortNumber = 25;

	size = sizeof(int);
	if(RegQueryValueEx(key, _T("POP3Port"), NULL, NULL, (LPBYTE)&m_nPOP3PortNumber, &size) != ERROR_SUCCESS) 
		m_nPOP3PortNumber = 110;

	size = sizeof(int);
	if(RegQueryValueEx(key, _T("Protocol"), NULL, NULL, (LPBYTE)&m_nProtocol, &size) != ERROR_SUCCESS) 
		m_nProtocol = 0;

	size = sizeof(BOOL);
	if(RegQueryValueEx(key, _T("ClientAuth"), NULL, NULL, (LPBYTE)&m_bAuth, &size) != ERROR_SUCCESS) 
		m_bAuth = FALSE;

	size = sizeof(BOOL);
	if(RegQueryValueEx(key, _T("ImmedNeg"), NULL, NULL, (LPBYTE)&m_bImmedNeg, &size) != ERROR_SUCCESS) 
		m_bAuth = FALSE;

	// Get certificate
	_TCHAR	szSerial[MAX_PATH + 1], szIssuer[MAX_PATH + 1];

	size = MAX_PATH;
	if(RegQueryValueEx(key, _T("CertSerial"), NULL, NULL, (LPBYTE)&szSerial, &size) != ERROR_SUCCESS) 
		*szSerial = NULL;
	size = MAX_PATH;
	if(RegQueryValueEx(key, _T("CertIssuer"), NULL, NULL, (LPBYTE)&szIssuer, &size) != ERROR_SUCCESS) 
		*szIssuer = NULL;
	size = sizeof(DWORD);
	if(RegQueryValueEx(key, _T("StoreLocation"), NULL, NULL, (LPBYTE)&m_dwStoreLocation, &size) != ERROR_SUCCESS) 
		m_dwStoreLocation = 0;
	size = MAX_PATH;
	if(RegQueryValueEx(key, _T("StoreName"), NULL, NULL, (LPBYTE)&m_szStoreName, &size) != ERROR_SUCCESS) 
		*m_szStoreName = NULL;

	// Try to find the certificate which match the specified serial number & issuer
	CUT_CertificateStore	store(m_szStoreName, m_dwStoreLocation);
	store.FindCertificate(m_Cert, szIssuer, szSerial);

	// Close registry key
	RegCloseKey(key);
}

// Save options
void SaveOptions(HWND hwnd)
{
	HKEY    key;

	// get options from dialog controls
	GetOptionsFromDlg(hwnd);

	// Open up the key for the email config info
	if(RegCreateKey(HKEY_LOCAL_MACHINE, EMAIL_REGISTRY_FOLDER, &key) != ERROR_SUCCESS)
		return;

	RegSetValueEx(key, _T("SMTPPort"), NULL, REG_DWORD, (LPBYTE)&m_nSMTPPortNumber, sizeof(unsigned short));
	RegSetValueEx(key, _T("POP3Port"), NULL, REG_DWORD, (LPBYTE)&m_nPOP3PortNumber, sizeof(unsigned short));

	RegSetValueEx(key, _T("Protocol"), NULL, REG_DWORD, (LPBYTE)&m_nProtocol, sizeof(int));

	RegSetValueEx(key, _T("ClientAuth"), NULL, REG_DWORD, (LPBYTE)&m_bAuth, sizeof(BOOL));

	RegSetValueEx(key, _T("ImmedNeg"), NULL, REG_DWORD, (LPBYTE)&m_bImmedNeg, sizeof(BOOL));

	if(m_Cert.GetContext() != NULL)
	{
		RegSetValueEx(key, _T("CertSerial"), NULL, REG_SZ, (LPBYTE)m_Cert.GetSerialNumber(), (DWORD)_tcslen(m_Cert.GetSerialNumber())*sizeof(_TCHAR));
		RegSetValueEx(key, _T("CertIssuer"), NULL, REG_SZ, (LPBYTE)m_Cert.GetIssuer(), (DWORD)_tcslen(m_Cert.GetIssuer())*sizeof(_TCHAR));
		RegSetValueEx(key, _T("StoreLocation"), NULL, REG_DWORD, (LPBYTE)&m_dwStoreLocation, sizeof(int));
		RegSetValueEx(key, _T("StoreName"), NULL, REG_SZ, (LPBYTE)&m_szStoreName, (DWORD)_tcslen(m_szStoreName)*sizeof(_TCHAR));
	}

	// Close registry key
	RegCloseKey(key);
}

void GetOptionsFromDlg(HWND hwnd)
{
	BOOL bResult;

	m_nSMTPPortNumber = (unsigned short)GetDlgItemInt(hwnd, IDC_EDIT_PORT, &bResult, FALSE);
	m_nPOP3PortNumber = (unsigned short)GetDlgItemInt(hwnd, IDC_EDIT_PORT_POP3, &bResult, FALSE);

	m_bAuth = (BOOL)SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_GETCHECK, 0, 0L);

	m_bImmedNeg = (BOOL)SendDlgItemMessage(hwnd, IDC_CHECK_IMMEDIATE_NEG, BM_GETCHECK, 0, 0L);

	switch(SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_GETCURSEL, 0, 0L))
	{
		case(1):
			m_nProtocol = SP_PROT_PCT1;
			break;
		case(2):
			m_nProtocol = SP_PROT_SSL2;
			break;
		case(3):
			m_nProtocol = SP_PROT_SSL3;
			break;
		case(4):
			m_nProtocol = SP_PROT_TLS1;
			break;
		default:
			m_nProtocol = 0;
			break;
	}


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

					GetDlgItemText(hwnd, IDC_USER_NAME, szBuffer, sizeof(szBuffer)/sizeof(_TCHAR));

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

					GetDlgItemText(hwnd, IDC_USER_NAME, szBuffer, sizeof(szBuffer)/sizeof(TCHAR));

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
					{

					int nIndex = (int)SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_GETCURSEL, 0, 0);

					MailServer->Sys_DeleteLocalName(nIndex);

					// Remove the selected item from the list box and clear the text
					// in the edit controls.
					SendMessage(GetDlgItem(hwnd, IDC_USER_LIST), LB_DELETESTRING, nIndex, 0);
					SetDlgItemText(hwnd, IDC_USER_NAME, _T(""));
					break;
					}
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
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, ModifyUserProc);
					break;
				case IDC_BUTTON_DNS_NAMES:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_LIST), hwnd, DNSServersConfigureProc);
					break;
				case IDC_BUTTON_DOMAIN_NAMES:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_LIST), hwnd, DomainConfigureProc);
					break;

			}
	}

	return 0;
}


BOOL CALLBACK UserOptionsProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
		switch (message) {

		case WM_INITDIALOG:
			{
// v4.2 removed - local var not referenced
//				HWND hwndLB = GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST);
				SetDlgItemText(hwnd, IDC_MODIFY_USER_NAME, g_pUserInfo->szUserName);
				SetDlgItemText(hwnd, IDC_MODIFY_NEW_NAME, g_pUserInfo->szUserName);
				EnableWindow(GetDlgItem(hwnd,IDC_MODIFY_USER_NAME),FALSE);
				SetDlgItemText(hwnd, IDC_MODIFY_PASSWORD, g_pUserInfo->szPassword);
		 			// loop through the available email aliases for this user and pouplate the list box				
				 for (int counter= 0; counter < g_pUserInfo->listEmailAddresses.GetCount (); counter++)
						SendMessage(GetDlgItem(hwnd, IDC_EMAIL_ALIASES_LIST), LB_ADDSTRING, 0, (LPARAM) g_pUserInfo->listEmailAddresses.GetString (counter) );
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
// v4.2 unreachable code?
//				return 0;
			}
		}
	return 0;
}

#pragma warning ( pop )