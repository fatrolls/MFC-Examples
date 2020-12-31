// =================================================================
//  Ultimate TCP/IP ECHO Server
//  File:  EchoServer.cpp
//
//
// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================

#include "stdafx.h"
#include "resource.h"
#include "uh_ctrl.h"
#include "Echo_s.h"
#include "..\..\..\..\Security\Include\UTCertifListDlg.h"
#include "..\..\..\..\Security\Include\UTCertifMan.h"

// local define to restrict connections but allow for client testing - comment out
// for normal operation
//#define UT_CLIENT_TESTING_ONLY


// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

//****************************************************************
//***	Helper variables
//****************************************************************
 
CUT_EchoServer			ECHOServer;
HINSTANCE				hInst = NULL;
CUH_Control				status;
HFONT					hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));
CUT_CertificateListDlg	dlg;
BOOL					bServerStarted = FALSE;

//****************************************************************
//***	Server options
//****************************************************************
unsigned short			m_nPortNumber = 777;
int						m_nProtocol = 0;
CUT_Certificate			m_Cert;
BOOL					m_bAuth = FALSE;
_TCHAR					m_szStoreName[MAX_PATH + 1];
DWORD					m_dwStoreLocation = 0;

//****************************************************************
//***	Function declarations
//****************************************************************

// Save server options
void SaveOptions(HWND hwnd);

// Read server options
void ReadOptions();

// Read server options from the dialog window
void GetOptionsFromDlg(HWND hwnd);

// Dialog procedure
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// About box dialog procedure
BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

//****************************************************************
//***	ECHO server entry function
//****************************************************************
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE /* hPrevInstance */,
                     LPSTR     /* lpCmdLine */,
                     int       /* nCmdShow */)
{
	hInst = hInstance;

	// Init the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);

	// Create modal dialog box
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ECHO_SERVER), NULL, (DLGPROC )DlgProc);

	// Delete created font
	DeleteObject(hFont);

	return 0;
}

//****************************************************************
//***	ECHO server dialog procedure
//****************************************************************
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch(message)
	{
		// Initialize dialog
		case WM_INITDIALOG:
		{	
			// Set the history control
			status.AttachHistoryWindow(hwnd,IDC_STATUS);
			status.SetFont(hFont);
			status.SetHistoryLength(50);

			// Fill the list of possible protocols
			SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("Default"));
			SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("PCT 1.0"));
			SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("SSL 2.0"));
			SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("SSL 3.0"));
			SendDlgItemMessage(hwnd, IDC_COMBO_PROTOCOL, CB_ADDSTRING, 0, (LPARAM)_T("TLS 1.0"));

			// Read settings from registry
			ReadOptions();

			// Select protocol
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

			// Set port number
			SetDlgItemInt(hwnd, IDC_EDIT_PORT, m_nPortNumber, FALSE);

			// Set authentication flag
			SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_SETCHECK, m_bAuth, 0L);

			// Display certificate subject
			SetDlgItemText(hwnd, IDC_EDIT_CERT, m_Cert.GetSubject());

			// Set history control pointer
			ECHOServer.ctrlHistory = &status;

#if defined UT_CLIENT_TESTING_ONLY
			ECHOServer.SetMaxConnections(5);
			status.AddLine(_T("This server is provided for testing the client side samples "),RGB(255,0,0));
			status.AddLine(_T("of Ultimate TCP-IP. Maximum number of simultaneous connections is 5."),RGB(255,0,0));
			status.AddLine(_T("________________________________________________________________"));
#endif
			return 1;
		}

		case WM_CLOSE:
		{
			// Save settings
			SaveOptions(hwnd);

			// Close the dialog
			EndDialog(hwnd,0);
			break;
		}
	
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				// Server Start/Stop button was clicked
				case IDC_BUTTON_START:
				{
					// Start server
					if(!bServerStarted)
					{
						// Check if certificate selected
						if(m_Cert.GetContext() == NULL)
						{
							MessageBox(hwnd, _T("You must select a valid certificate before strting the server!"), _T("Invalid Certificate"), MB_OK);
							break;
						}

						// Get server options
						GetOptionsFromDlg(hwnd);

						// start server
						if (ECHOServer.ConnectToPort(m_nPortNumber) == CUT_SUCCESS)
						{
							_TCHAR	szBuffer[100];
							_stprintf(szBuffer, _T("Connected to port %d"), m_nPortNumber);
							status.AddLine(szBuffer);

							// Start accepting calls
							ECHOServer.StartAccept();
							status.AddLine(_T("Waiting for connections"));
							bServerStarted = TRUE;
						}
						else
							status.AddLine(_T("Connection failed you might have an other server listening on the same port."));
					}

					// Stop server
					else
					{
						status.AddLine("Stopping server...");
						ECHOServer.StopAccept();
						bServerStarted = FALSE;
						status.AddLine("Server stopped");
					}

					// Change dialog items
					if(bServerStarted)
						SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Stop"));
					else
						SetDlgItemText(hwnd, IDC_BUTTON_START, _T("Start"));

					// Disable options editing
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT_PORT), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_BUTTON_CERT), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_COMBO_PROTOCOL), !bServerStarted);
					EnableWindow(GetDlgItem(hwnd, IDC_CHECK_AUTH), !bServerStarted);
					break;
				}

				// Browse certificate button was clicked
				case IDC_BUTTON_CERT:
				{
					// Select the certificate
					dlg.SetViewCertOnDblClk(FALSE);
					dlg.SetStoreNames(_T("MY"));
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
			
				// About button was clicked
				case IDC_ABOUT:
				{
					// Display about box
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					break;
				}
			}
		}
	}
	return 0;
}

//****************************************************************
//***	About box dialog procedure
//****************************************************************
BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	switch (message) 
	{
		case WM_COMMAND:
			if(LOWORD(wParam) == IDC_EXIT)
				EndDialog(hwndDlg, IDOK);
			break;
		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;
	}
	return 0;
}

//****************************************************************
//***	Read server options from the registry
//****************************************************************
void ReadOptions()
{
	DWORD   size;
	HKEY    key;

	// Open up the key for the email config info
	if(RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\The Ultimate Toolbox\\TCPIP40\\ECHOServer"), &key) != ERROR_SUCCESS)
		return;

	// Get the port number to listen on
	size = sizeof(int);
	if(RegQueryValueEx(key, _T("Port"), NULL, NULL, (LPBYTE)&m_nPortNumber, &size) != ERROR_SUCCESS) 
		m_nPortNumber = 777;

	// Get secure protocol
	size = sizeof(int);
	if(RegQueryValueEx(key, _T("Protocol"), NULL, NULL, (LPBYTE)&m_nProtocol, &size) != ERROR_SUCCESS) 
		m_nProtocol = 0;

	// Get client authentication flag
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

//****************************************************************
//***	Save server options into the registry
//****************************************************************
void SaveOptions(HWND hwnd)
{
	HKEY    key;

	// get options from dialog controls
	GetOptionsFromDlg(hwnd);

	// Open up the key for the email config info
	if(RegCreateKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\The Ultimate Toolbox\\TCPIP40\\ECHOServer"), &key) != ERROR_SUCCESS)
		return;

	// Set the port number to listen on
	RegSetValueEx(key, _T("Port"), NULL, REG_DWORD, (LPBYTE)&m_nPortNumber, sizeof(int));

	// Set secure protocol
	RegSetValueEx(key, _T("Protocol"), NULL, REG_DWORD, (LPBYTE)&m_nProtocol, sizeof(int));

	// Set client authentication flag
	RegSetValueEx(key, _T("ClientAuth"), NULL, REG_DWORD, (LPBYTE)&m_bAuth, sizeof(BOOL));

	if(m_Cert.GetContext() != NULL)
	{
		RegSetValueEx(key, _T("CertSerial"), NULL, REG_SZ, (LPBYTE)m_Cert.GetSerialNumber(), (DWORD)_tcslen(m_Cert.GetSerialNumber()));
		RegSetValueEx(key, _T("CertIssuer"), NULL, REG_SZ, (LPBYTE)m_Cert.GetIssuer(), (DWORD)_tcslen(m_Cert.GetIssuer()));
		RegSetValueEx(key, _T("StoreLocation"), NULL, REG_DWORD, (LPBYTE)&m_dwStoreLocation, sizeof(int));
		RegSetValueEx(key, _T("StoreName"), NULL, REG_SZ, (LPBYTE)&m_szStoreName, (DWORD)_tcslen(m_szStoreName));
	}

	// Close registry key
	RegCloseKey(key);
}

//****************************************************************
//***	Get server options from the dialog
//****************************************************************
void GetOptionsFromDlg(HWND hwnd)
{
	BOOL bResult;

	// Get port number
	m_nPortNumber = (unsigned short) GetDlgItemInt(hwnd, IDC_EDIT_PORT, &bResult, FALSE);

	// Get client authentication flag
	m_bAuth = (BOOL)SendDlgItemMessage(hwnd, IDC_CHECK_AUTH, BM_GETCHECK, 0, 0L);

	// Get protocol
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

	// Set options
	ECHOServer.SetSecurityEnabled(TRUE); 
	ECHOServer.SetCertificate(m_Cert);
	ECHOServer.SetSecurityProtocol(m_nProtocol);
	ECHOServer.SetClientAuth(m_bAuth);
	ECHOServer.SetPort(m_nPortNumber);
}

#pragma warning ( pop )