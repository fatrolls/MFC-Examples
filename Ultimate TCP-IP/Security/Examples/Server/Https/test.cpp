// =================================================================
//  Ultimate TCP/IP HTTP Server
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
#include "HTTP_s.h"
#include "test.h"

#include "..\..\..\..\Security\Include\UTCertifListDlg.h"
#include "..\..\..\..\Security\Include\UTCertifMan.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
//#define UT_CLIENT_TESTING_ONLY


// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


HINSTANCE hInst = NULL;
CUT_HTTPServer HTTPs;
CUH_Control status;
HFONT hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));
CUT_CertificateListDlg	dlg;
BOOL	bServerStarted = FALSE;

// Server options
unsigned short	m_nPortNumber = 443;
int				m_nProtocol = 0;
CUT_Certificate	m_Cert;
BOOL			m_bAuth = FALSE;
_TCHAR			m_szRootPath[MAX_PATH + 1];
_TCHAR			m_szStoreName[MAX_PATH + 1];
DWORD			m_dwStoreLocation = 0;

void SaveOptions(HWND hwnd);
void ReadOptions();
void GetOptionsFromDlg(HWND hwnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	hInst = hInstance;

	// init the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);

	// set up the path where the server works from
	GetModuleFileName(NULL, m_szRootPath, MAX_PATH);
	while(*(m_szRootPath + _tcslen(m_szRootPath) - 1) != _T('\\'))
		*(m_szRootPath + _tcslen(m_szRootPath) - 1) = 0;

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
			SetDlgItemInt(hwnd, IDC_EDIT_PORT, m_nPortNumber, FALSE);

			// set authentication flag
			SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_SETCHECK, m_bAuth, 0L);

			// set root path
			SetDlgItemText(hwnd, IDC_EDIT_PATH, m_szRootPath);

			// display certificate subject
			SetDlgItemText(hwnd, IDC_EDIT_CERT, m_Cert.GetSubject());

			// set security options
			HTTPs.SetSecurityEnabled(TRUE); 
			HTTPs.SetCertificate(m_Cert);
			HTTPs.SetPort(m_nPortNumber);
			HTTPs.SetPath(m_szRootPath); // copy the path the the winsock class
			HTTPs.ctrlHistory = &status; // copy the history control pointer

#if defined UT_CLIENT_TESTING_ONLY
			HTTPs.SetMaxConnections(5);
			status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
			status.AddLine(_T("of Ultimate TCP-IP. The number of simultaneous connections is 5."),RGB(255,0,0));
			status.AddLine(_T("________________________________________________________________"));
#endif
			return 1;
		}
	case WM_CLOSE:
		{
			// save settings
			SaveOptions(hwnd);

			EndDialog(hwnd,0);
			break;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case IDC_BUTTON_START:
				{
					// start server
					if(!bServerStarted)
					{
						// check if certificate selected
						if(m_Cert.GetContext() == NULL)
						{
							MessageBox(hwnd, _T("You must select a valid certificate before starting the server!"), _T("Invalid Certificate"), MB_OK);
							break;
						}

						// get server options
						GetOptionsFromDlg(hwnd);

						// set server options
						HTTPs.SetCertificate(m_Cert);
						HTTPs.SetPort(m_nPortNumber);
						HTTPs.SetPath(m_szRootPath);
						HTTPs.SetSecurityProtocol(m_nProtocol);

						// start server
						if (HTTPs.ConnectToPort(m_nPortNumber) == CUT_SUCCESS)
						{
							char	szBuffer[100];
							sprintf(szBuffer, "Connected to port %d", m_nPortNumber);
							status.AddLine(szBuffer);
							HTTPs.StartAccept();			// start accepting calls
							status.AddLine("Waiting for connections");

							bServerStarted = TRUE;
						}
						else
							status.AddLine("Connection failed you might have an other server listening on the same port.");
					}

					// stop server
					else
					{
						status.AddLine("Stopping server...");
						HTTPs.StopAccept();
						bServerStarted = FALSE;
						status.AddLine(_T("Server stopped"));
					}

					// change dialog items
					if(bServerStarted)
					{
						SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Stop"));
						SetDlgItemText(hwnd, IDC_STATIC_MSG, _T("Server is running..."));
					}
					else
					{
						SetDlgItemText(hwnd, IDC_STATIC_MSG, _T("Press Start to run the server"));
						SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Start"));
					}

					// disable options editing
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT_PORT), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_CERT), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_COMBO_PROTOCOL), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_CHECK_AUTH), !bServerStarted);
					break;
				}
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

					ZeroMemory(buffer, sizeof(buffer));

					GetDlgItemText(hwnd, IDC_EDIT, buffer, MAX_PATH);
					HTTPs.SetPath(buffer);
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

// Read options
void ReadOptions()
{
	DWORD   size;
	HKEY    key;

	// Open up the key for the email config info
	if(RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\The Ultimate Toolbox\\TCPIP40\\HTTPServer"), &key) != ERROR_SUCCESS)
		return;

	size = MAX_PATH;
	RegQueryValueEx(key, _T("RootPath"), NULL, NULL, (LPBYTE)&m_szRootPath, &size);

	size = sizeof(int);
	if(RegQueryValueEx(key, _T("Port"), NULL, NULL, (LPBYTE)&m_nPortNumber, &size) != ERROR_SUCCESS) 
		m_nPortNumber = 443;

	size = sizeof(int);
	if(RegQueryValueEx(key, _T("Protocol"), NULL, NULL, (LPBYTE)&m_nProtocol, &size) != ERROR_SUCCESS) 
		m_nProtocol = 0;

	size = sizeof(BOOL);
	if(RegQueryValueEx(key, _T("ClientAuth"), NULL, NULL, (LPBYTE)&m_bAuth, &size) != ERROR_SUCCESS) 
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
	if(RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\The Ultimate Toolbox\\TCPIP40\\HTTPServer"), &key) != ERROR_SUCCESS)
		return;

	RegSetValueEx(key, _T("RootPath"), NULL, REG_SZ, (LPBYTE)&m_szRootPath, (DWORD)_tcslen(m_szRootPath)*sizeof(_TCHAR));

	RegSetValueEx(key, _T("Port"), NULL, REG_DWORD, (LPBYTE)&m_nPortNumber, sizeof(int));

	RegSetValueEx(key, _T("Protocol"), NULL, REG_DWORD, (LPBYTE)&m_nProtocol, sizeof(int));

	RegSetValueEx(key, _T("ClientAuth"), NULL, REG_DWORD, (LPBYTE)&m_bAuth, sizeof(BOOL));

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
	GetDlgItemText(hwnd, IDC_EDIT_PATH, m_szRootPath, MAX_PATH);

	m_nPortNumber = (unsigned short)GetDlgItemInt(hwnd, IDC_EDIT_PORT, &bResult, FALSE);

	m_bAuth = (BOOL)SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_GETCHECK, 0, 0L);

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

#pragma warning ( pop )