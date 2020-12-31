//=================================================================
//  main file
//  File:  test.cpp
//
//  Purpose:
//
//  HTTPS Client Class
//  Implementation of Hypertext Transfer Protocol -- HTTP/1.0
//
//  See also RFC  1945
//      
//=================================================================
// Ultimate TCP-IP v4.2
// Copyright © The Ultimate Toolbox 1995-2007, all rights reserverd
//=================================================================


#include "stdafx.h"
#include "test.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "HTTP_c.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


HINSTANCE	g_hInstance;
_TCHAR		g_szHeader[MAX_PATH];
CUH_Control control;
CUT_HTTPClient client;
HFONT		hFont;
BOOL bPutFromFile = FALSE;
int			tagPos;

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	g_hInstance = hInstance;

	// register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);

	// create modal dialog box
	DialogBox(hInstance, _T("DIALOG_1"), NULL, (DLGPROC )DlgProc);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)));

			SetDlgItemInt(hwnd, IDC_PORT, 443, FALSE);

			// attach the history window to the control
			control.AttachHistoryWindow(hwnd,IDC_HISTORY);
			control.SetHistoryLength(1000);
			hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			control.SetFont(hFont);
			client.SetCertValidation (CERT_VERIFY_AND_ASK);

			// enable security
			client.SetSecurityEnabled(TRUE);
			return 1;
		}
	case WM_NCDESTROY:
		{
			DeleteObject(hFont);
			return 0;
		}
	case WM_COMMAND:
		{

			switch(LOWORD(wParam))
			{

			case IDC_ABOUT:
				{
					DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					return 1;
				}
			case IDC_EXIT:
				{
					EndDialog(hwnd,0);
					return 1;
				}
				// set the put source to be treated as a file or Data
			case IDC_PUT_FROM_FILE:
				{
					if (bPutFromFile)
						bPutFromFile = FALSE;
					else
						bPutFromFile = TRUE;
					return 1;
				}
			case IDC_GET:
				{

					int nResult = 0;
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					_TCHAR szBuffer[256];
					_TCHAR szErrorMessage[MAX_PATH];

					// clear the history control
					control.ClearHistory();
					tagPos = 0;
					// clear the send header tags so we for the next request
					client.ClearSendHeaderTags();
					// read the list of headers to be added for the next request
					// from the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					WORD  wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					for (int loop = 0 ; loop < wCount; loop++)
					{
						SendMessage (hWndCombo,	CB_GETLBTEXT,loop,(LONG)(ULONG_PTR)(LPSTR)szBuffer);
						if (_tcslen(szBuffer) > 4)
							nResult = client.AddSendHeaderTag (szBuffer);						
					}

					// Setup proxy 
					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);


					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));


					// get the information to retrieve
					GetDlgItemText(hwnd, IDC_EDIT, szBuffer, 256);

					// execute the GET statement
					nResult = client.GET(szBuffer);
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					if (nResult == UTE_SUCCESS){
						LPCSTR line;
						long count = client.GetHeaderLineCount();
						long loop = 0;

						control.SetTextColor(RGB(0,0,250));
						for(loop =0;loop <count;loop++){
							line = client.GetHeaderLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}

						control.AddLine ("__________END_OF_HEADER______");
						control.SetTextColor(RGB(0,0,0));
						// display the body of the HTTP message 
						count = client.GetBodyLineCount();
						for(loop =0;loop <count;loop++){
							line = client.GetBodyLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}					
					}
					else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}

					return 1;
				}
			case IDC_DELETE_BTN:
				{
					int nResult = 0;
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					_TCHAR szBuffer[256];
					_TCHAR szErrorMessage[MAX_PATH];
					// clear the history control
					control.ClearHistory();
					tagPos = 0;
					// clear the send header tags so we for the next request
					client.ClearSendHeaderTags ();
					// read the list of headers to be added for the next request
					// from the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					WORD  wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					for ( int loop = 0 ; loop < wCount; loop++)
					{
						SendMessage (hWndCombo,	CB_GETLBTEXT,loop,(LONG)(ULONG_PTR)(LPSTR)szBuffer);
						if (lstrlen(szBuffer) > 4){
							nResult = client.AddSendHeaderTag (szBuffer);						
						}
					}
					// get the information to retrieve
					GetDlgItemText(hwnd, IDC_EDIT,szBuffer,256);


					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);



					//Set up the port 

					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));

					// perform  the get statement
					nResult = client.DeleteFile(szBuffer);
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					if( nResult == UTE_SUCCESS){
						LPCSTR line;
						long count = client.GetHeaderLineCount();
						long loop = 0;
						control.SetTextColor(RGB(0,0,250));

						control.SetTextColor(RGB(0,0,0));
						// display the body of the HTTP message 
						count = client.GetBodyLineCount();
						for(loop =0;loop <count;loop++){
							line = client.GetBodyLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
					}else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}


					return 1;

				}
			case IDC_SEND_CUSTOM:
				{
					// Send a server specific command or a command that CUT_HTTPClient does not 
					// implement. This method enables the client reuest to be modified for use in 
					// a format that is specific for your own company server.
					// On the other hand you may be intersted in seeing the replies for each 
					// HTTP command
					int nResult = 0;
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					_TCHAR url[256];
					_TCHAR command[MAX_PATH];
					_TCHAR szBuffer[MAX_PATH];
					_TCHAR data[MAX_PATH];
					data[0] = NULL;
					_TCHAR szErrorMessage[MAX_PATH];
					//clear the history control
					control.ClearHistory();
					tagPos = 0;
					// clear the send header tags so we for the next request
					client.ClearSendHeaderTags ();
					//read the list of headers to be added for the next request
					// from the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					WORD  wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					for ( int loop = 0 ; loop < wCount; loop++)
					{
						SendMessage (hWndCombo,	CB_GETLBTEXT,loop,(LONG)(ULONG_PTR)(LPSTR)szBuffer);
						if (_tcslen(szBuffer) > 4){
							nResult = client.AddSendHeaderTag (szBuffer);						
						}
					}
					// get the information to retrieve
					GetDlgItemText(hwnd, IDC_EDIT,url,256);
					GetDlgItemText(hwnd, IDC_COMMAND,command,256);
					GetDlgItemText(hwnd, IDC_DATA,data,256);
					// if there is data then lets add the content length of the data as a header
					if ((nResult = lstrlen(data)) > 0)
					{
						_sntprintf(szBuffer, sizeof(szBuffer),_T("Content-Length: %d"),nResult);
						client.AddSendHeaderTag (szBuffer);
					}
					else
						data[0] = NULL;

					//Set up the port 
					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));

					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);



					// Send The custom command such as OPTIONS, POST  and so on
					nResult = client.CommandLine (command,url, data);
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					if( nResult == UTE_SUCCESS){
						LPCSTR line;
						// display the headers
						// if any 
						long count = client.GetHeaderLineCount();
						long loop = 0;
						control.SetTextColor(RGB(0,0,250));
						for(loop =0;loop <count;loop++){
							line = client.GetHeaderLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
						control.SetTextColor(RGB(0,0,0));
						// display the body of the HTTP message 
						count = client.GetBodyLineCount();
						for(loop =0;loop <count;loop++){
							line = client.GetBodyLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
					}
					else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}

					return 1;

				}
			case IDC_ADD_HEADER:
				{
					// adds header tag string to the combobox where we will read from 
					// each time we attempt to send an HTTP commands
					// SAMPLE OF HEADER TAGS follow:
					// "Connection: Keep-Alive"
					// "Referer: http://www.gwDomain.com/form1.htm"
					//	"Cookie: ASPSESSIONIDQQGGGGCU=PKAAEDNACCEHEDDIOHJCAGFI"
					//	"Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, *"
					g_szHeader[0] = NULL;
					// display the input dialog
					DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_DIALOG2),NULL,(DLGPROC)AddHeaderBox);
					if (_tcslen(g_szHeader) > 4 ) // well, 4 =  a header name a : and a space then the data 
					{
						// add the header to the combo box
						HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
						SendMessage (hWndCombo,	CB_ADDSTRING,0,	(LONG)(ULONG_PTR)(LPSTR) g_szHeader);

					}

					return 1;
				}
			case IDC_POST:
				{
					// put the file or data specified by the data edit box on the server resource
					// and name it the name given in the URL edit box
					// the PUT command requires that youhave a write access to 
					// the directory you are trying to access
					int nResult = 0;
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					_TCHAR url[256];
					_TCHAR szBuffer[MAX_PATH];
					_TCHAR data[MAX_PATH];
					data[0] = NULL;
					_TCHAR szErrorMessage[MAX_PATH];

					//clear the history control
					control.ClearHistory();
					tagPos = 0;

					// clear the send header tags so we for the next request
					client.ClearSendHeaderTags ();

					//read the list of headers to be added for the next request
					// from the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					WORD  wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					for ( int loop = 0 ; loop < wCount; loop++)
					{
						SendMessage (hWndCombo,	CB_GETLBTEXT,loop,(LONG)(ULONG_PTR)(LPSTR)szBuffer);
						if (_tcslen(szBuffer) > 4){
							nResult = client.AddSendHeaderTag (szBuffer);
						}
					}
					// get the information to retrieve
					GetDlgItemText(hwnd, IDC_EDIT,url,256);
					GetDlgItemText(hwnd, IDC_DATA,data,256);

					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);

					//Set up the port 
					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));

					// Send The custom command such as OPTIONS, POST  and so on
					if (bPutFromFile) {
						nResult = client.POST (url, data);
					}
					else {
// v4.2 VC8 doesn't like this constuct - changed to create ds before call - also, note use of AC
//						nResult = client.POST (url, CUT_BufferDataSource(data, strlen(data)));
						CUT_BufferDataSource ds(AC(data), _tcslen(data));
						nResult = client.POST (url, ds);
					}

					SetCursor(LoadCursor(NULL, IDC_ARROW));
					if( nResult == UTE_SUCCESS){
						LPCSTR line;
						long count = client.GetHeaderLineCount();
						long loop = 0;
						control.SetTextColor(RGB(0,0,250));
						for(loop =0;loop <count;loop++){
							line = client.GetHeaderLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
						control.SetTextColor(RGB(0,0,0));
						// display the body of the HTTP message 
						count = client.GetBodyLineCount();
						for(loop =0;loop <count;loop++){
							line = client.GetBodyLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
					}
					else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}

					return 1;

				}
			case IDC_PUT_CMD:
				{
					// put the file or data specified by the data edit box on the server resource
					// and name it the name given in the URL edit box
					// the PUT command requires that youhave a write access to 
					// the directory you are trying to access
					int nResult = 0;
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					_TCHAR url[256];
					_TCHAR szBuffer[MAX_PATH];
					_TCHAR data[MAX_PATH];
					data[0] = NULL;
					_TCHAR szErrorMessage[MAX_PATH];
					//clear the history control
					control.ClearHistory();
					tagPos = 0;
					// clear the send header tags so we for the next request
					client.ClearSendHeaderTags ();
					//read the list of headers to be added for the next request
					// from the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					WORD  wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					for ( int loop = 0 ; loop < wCount; loop++)
					{
						SendMessage (hWndCombo,	CB_GETLBTEXT,loop,(LONG)(ULONG_PTR)(LPSTR)szBuffer);
						if (lstrlen(szBuffer) > 4){
							nResult = client.AddSendHeaderTag (szBuffer);
						}
					}
					// get the information to retrieve
					GetDlgItemText(hwnd, IDC_EDIT,url,256);
					GetDlgItemText(hwnd, IDC_DATA,data,256);

					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);


					//Set up the port 
					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));

					// Send The custom command such as OPTIONS, POST  and so on
					// v4.2 note use of AC() macro...
					if (bPutFromFile) {
						nResult = client.PUT (url, data);
					}
					else {
						CUT_BufferDataSource	ds(AC(data), _tcslen(data)); 
 						nResult = client.PUT (url, ds);
					}

					SetCursor(LoadCursor(NULL, IDC_ARROW));
					if( nResult == UTE_SUCCESS){
						LPCSTR line;
						long count = client.GetHeaderLineCount();
						long loop = 0;
						control.SetTextColor(RGB(0,0,250));
						for(loop =0;loop <count;loop++){
							line = client.GetHeaderLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
						control.SetTextColor(RGB(0,0,0));
						// display the body of the HTTP message 
						count = client.GetBodyLineCount();
						for(loop =0;loop <count;loop++){
							line = client.GetBodyLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
					}
					else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}

					return 1;

				}
			case IDC_DEL: // delete the headers from the combo box
				{
					//clear the content of the combo box
					HWND hWndCombo = GetDlgItem(hwnd,IDC_HEADER_CB);
					// Remove all headers from the list until error
					while (SendMessage (hWndCombo, CB_DELETESTRING, 0, 0L) != CB_ERR)
						;
					return 1;
				}
			case IDC_HEAD:
				{

					SetCursor(LoadCursor(NULL, IDC_WAIT));

					_TCHAR szBuffer[256];
					_TCHAR szErrorMessage[MAX_PATH];
					int nResult = 0;

					//clear the history control
					control.ClearHistory();
					tagPos = 0;


					//Set up the port 
					BOOL bConnectThroughProxy = IsDlgButtonChecked(hwnd, IDC_PROXY) == BST_CHECKED;
					BOOL bTunneling = IsDlgButtonChecked(hwnd, IDC_ENABLE_TUNNELLING) == BST_CHECKED; 
					GetDlgItemText(hwnd, IDC_PROXY_ADDRESS, szBuffer, 256);					
					client.SetProxy(szBuffer);
					client.UseProxyServer(bConnectThroughProxy);
					client.EnableTunneling (bTunneling);

					client.SetPort(GetDlgItemInt(hwnd, IDC_PORT, NULL, FALSE));
					GetDlgItemText(hwnd, IDC_EDIT,szBuffer,256);

					nResult = client.HEAD(szBuffer);

					//perform  the get statement
					if( nResult == UTE_SUCCESS){
						LPCSTR line;
						long loop = 0;
						long count = client.GetHeaderLineCount ();
						control.SetTextColor(RGB(0,0,250));
						for(loop =0;loop <count;loop++){
							line = client.GetHeaderLine(loop);
							if(line != NULL)
								control.AddLine(line);
						}
					}
					else
					{
						_sntprintf(szErrorMessage, sizeof(szErrorMessage),_T("ERROR  \n %s "), CUT_ERR::GetErrorString(nResult));
						MessageBox(NULL, szErrorMessage, _T("ERROR"), MB_OK);
					}
					control.SetTextColor(RGB(0,0,0));

					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
			case IDC_GETTAGCOUNT:
				{
					// Retrieve the number of hyper link refrences on the given page 
					char szBuffer[256];
					int count = client.GetLinkTagCount();
					_snprintf(szBuffer, sizeof(szBuffer),"Tag Count: %d",count);
					control.AddLine(szBuffer);
					return 1;
				}
			case IDC_GETTAGSTRING:
				{
					// Retrive the  next string of hyper link refrences 
					char szBuffer[256];
					if(client.GetLinkTag(tagPos,szBuffer,sizeof(szBuffer)) == UTE_SUCCESS){
						tagPos++;
						control.AddLine(szBuffer);
					}
					else
						control.AddLine("End of Tag List");
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

/*******************************************
Invok the input dialog box to add the request 
header to the combo box
An example of suche headers can be :
"Connection: Keep-Alive"

********************************************/
BOOL CALLBACK AddHeaderBox(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	switch(message)
	{

	case WM_INITDIALOG:
		{
			// reinitialize the Header name to null
			SetDlgItemText(hwnd,IDC_HEADER,g_szHeader);			
			return 1;
		}
	case WM_NCDESTROY:
		{
			return 0;
		}
	case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			return 1;
		}
	case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case ID_ADD:
				{
					GetDlgItemText(hwnd,IDC_HEADER,g_szHeader,sizeof(g_szHeader)-1);
					EndDialog(hwnd,0);
					return 1;
				}
			case IDCANCEL:
				{
					g_szHeader[0] = NULL;
					EndDialog(hwnd,0);
					return 1;
				}
			}return 1;
		}
	}
	return 0;
}

#pragma warning ( pop )