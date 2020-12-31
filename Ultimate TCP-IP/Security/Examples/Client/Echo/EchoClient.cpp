// =================================================================
//  Ultimate TCP/IP ECHO Server
//  File:  EchoClient.cpp
//
//
// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================

#include "stdafx.h"
#include "resource.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "..\..\..\..\Security\Include\UTSecureSocket.h"


//****************************************************************
//***	Helper variables
//****************************************************************

CUT_WSClient			ECHOClient; 
HINSTANCE				hInst = NULL;
CUH_Control				status;
HFONT					hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));

//****************************************************************
//***	Client options
//****************************************************************
int						m_nPortNumber = 777;
_TCHAR					szServerAddress[1024] = {_T("127.0.0.1")};

//****************************************************************
//***	Functions decloration
//****************************************************************

// Dialog procedure
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// About box dialog procedure
BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam);

//****************************************************************
//***	ECHO client entry function
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
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_ECHO_CLIENT), NULL, (DLGPROC )DlgProc);

	// Delete created font
	DeleteObject(hFont);

	return 0;
}

//****************************************************************
//***	ECHO client dialog procedure
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

			// Set server port number & address
			SetDlgItemInt(hwnd, IDC_EDIT_PORT, m_nPortNumber, FALSE);
			SetDlgItemText(hwnd, IDC_EDIT_ADDRESS, szServerAddress);

			return 1;
		}

		case WM_CLOSE:
		{
			// Close the dialog
			EndDialog(hwnd,0);
			break;
		}
	
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
				// Connect to the server
				case IDC_BUTTON_CONNECT:
				{
					char	szBuffer[1024];
					int		nError;

					// Disconnect first
					ECHOClient.CloseConnection();

					// Get the port number & address
					BOOL	bResult;
					m_nPortNumber = GetDlgItemInt(hwnd, IDC_EDIT_PORT, &bResult, FALSE);
					GetDlgItemText(hwnd, IDC_EDIT_ADDRESS, szServerAddress, sizeof(szServerAddress) - 1);

					// Connect to the server
					status.AddLine("Connecting to the server...");
					ECHOClient.SetSecurityEnabled();
					if((nError = ECHOClient.Connect(m_nPortNumber, szServerAddress)) == UTE_SUCCESS)
					{
						// Read greeting string
						nError = ECHOClient.ReceiveLine(szBuffer, sizeof(szBuffer) - 1);
						if(nError > 0)
							// Display received line in the history control
							status.AddLine(szBuffer);
						else
							status.AddLine("Server connection failed!");
					}
					else
						status.AddLine(CUT_ERR::GetErrorString(nError));

					break;
				}

				// Send command
				case IDC_BUTTON_SEND:
				{
					// Check connectio
					if(ECHOClient.IsConnected())
					{
						// Get command to send
						_TCHAR	szBuffer[1024];
						char    szBufferA[1024];
						GetDlgItemText(hwnd, IDC_EDIT_COMMAND, szBuffer, 1023);
						
						// Send command
						// v4.2 Using wide char send overload
						ECHOClient.Send(szBuffer);
						ECHOClient.Send("\r\n");
							
						// Read responce back
						int nResult = ECHOClient.ReceiveLine(szBufferA, sizeof(szBufferA) - 1);

						if(nResult > 0)
						{
							// Display received line in the history control
							status.AddLine("Text received from the server:");
							status.AddLine(szBuffer);
						}
						else
						{
							// Error
							status.AddLine("ERROR: Can't recive data from the server.");
						}
					}
					else
						status.AddLine("ERROR: You must connect to the server first.");

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

