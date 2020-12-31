
// =================================================================
//  Ultimate TCP/IP DNS client test program
//  File:  TEST.CPP
//
//  Purpose:
//
//      Demonstrates the CUT_DNSClient class
//     for domain name lookup.
//
// =================================================================
// Ultimate TCP/IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================

#include "stdafx.h"
#include "test.h"
#include "uh_ctrl.h"	//output-history control
#include "ut_clnt.h"	//Ultimate TCP/IP client class
#include "DNS_c.h"		//dns client class

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

// these do not exist in core VC6 
#if _MSC_VER < 1400
#if !defined ULONG_PTR
#define ULONG_PTR DWORD
#define LONG_PTR DWORD
#endif
#endif

// Return the Query type based on the passed index from the 
// ComboBox
int GetSelectedQuery(int index)
{
	int queryType  = 0;
	
	switch (index)
	{
	case 0:
		{
			queryType = CUT_DNS_A;			//address
			break;
		}
	case 1:
		{
			queryType = CUT_DNS_NS;			//name server
			break;
		}
	case 2:
		{
			queryType = CUT_DNS_MD;			//mail destination (obs)
			break;
		}
	case 3:
		{
			queryType = CUT_DNS_MF;			//mail forwarder (obs)
			break;
		}
	case 4:
		{
			queryType = CUT_DNS_CNAME;	//canonical name
			break;
		}
	case 5:
		{
			queryType = CUT_DNS_SOA;		//start of authority
			break;
		}
	case 6:
		{
			queryType = CUT_DNS_MB;			//mailbox domain
			break;
		}
	case 7:
		{
			queryType = CUT_DNS_MG;			//mail group
			break;
		}
	case 8:
		{
			queryType = CUT_DNS_MR;			//mail rename domain
			break;
		}
	case 9:
		{
			queryType = CUT_DNS_NULL;		//null 
			break;
		}
	case 10:
		{
			queryType = CUT_DNS_WKS;		//well known service description
			break;
		}
	case 11:
		{
			queryType = CUT_DNS_PTR;		//domain name pointer   
			break;
		}
	case 12:
		{
			queryType = CUT_DNS_HINFO;	//host info
			break;
		}
	case 13:
		{
			queryType = CUT_DNS_MINFO;	//mailbox or mail list info
			break;
		}
	case 14:
		{
			queryType = CUT_DNS_MX;			//mail server
			break;
			
		}
	case 15:
		{
			queryType = CUT_DNS_TXT;		//text strings
			break;
		}
	case 16:
		{
			queryType = CUT_DNS_ALL;
			break;
			
		}
	case 17:
		{
			queryType = CUT_DNS_AXFR;
			break;
		}
	case 18:
		{
			queryType = CUT_DNS_MAILA;
			break;
		}
	case 19:
		{
			queryType = CUT_DNS_MAILB;
			break;
		}
	default:
		queryType = CUT_DNS_ALL;
	}
	
	return queryType;
}


HINSTANCE hInst;

// Main function
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int)
{
	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);
	
	hInst = hInstance;
	
	//show the splash screen
	DialogBox(hInst, _T("IDD_SPLASH"), NULL, (DLGPROC )AboutProc);
	
	//create the DNS lookup dialog box
	DialogBox(hInst, _T("DIALOG_1"), NULL, (DLGPROC)DlgProc);
	return 0;
}


BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	// About box and Splash screen dialog procedure
	
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


BOOL CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */){

	static CUH_Control control;
	static HFONT hFont;
	
	static BOOL bUseUDP = FALSE;
	static 	CUT_DNSClient dns;
	static HWND hWndCombo;
	static int queryType = CUT_DNS_ALL;
					
	switch(message){

		case WM_INITDIALOG:{

			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDR_ICON)));

			//attach the history window to the control
			control.AttachHistoryWindow(hwnd,IDC_HISTORY);
			//set the maximum length of the buffer of this window
			control.SetHistoryLength(100);

			// set the font for the history window
			hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			control.SetFont(hFont);

			//setup the controls
			SetDlgItemText(hwnd, IDC_DNSSERVER,_T("A.ROOT-SERVERS.NET"));
			hWndCombo = GetDlgItem(hwnd,IDC_RECORD_TYPE);
			
			// add a the query types as string to the combobox		
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_A (address)"));
			//address
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_NS (name server)"));
							//name server
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MD (mail destination (obs))"));
							//mail destination (obs)
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MF (mail forwarder (obs))"));
							//mail forwarder (obs)
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_CNAME (canonical name)"));
						//canonical name
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_SOA (start of authority)"));
						//start of authority
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MB (mailbox domain)"));
							//mailbox domain
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MG (mail group)"));
							//mail group
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MR (mail rename domain)"));
							//mail rename domain
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_NULL (NULL)"));
						//null 
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_WKS (well known service description)"));
						//well known service description
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_PTR (domain name pointer)"));
					//domain name pointer   
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_HINFO (host info)"));
						//host info
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MINFO (mailbox or mail list info)"));
						//mailbox or mail list info
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MX (mail exchange server)"));
							//mail server
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_TXT (text strings)"));
							//text strings
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_ALL (All records)"));
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_AXFR (Zone Transfer)"));
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MAILB"));
			SendMessage (hWndCombo,
							CB_ADDSTRING,
							0,
							(ULONG_PTR)(LPTSTR) _T("CUT_DNS_MAILA"));

			SendMessage (hWndCombo,
							CB_SETCURSEL,
							0,
							0);

			return 1;
		}
        // on final release reclaim the resources
		case WM_NCDESTROY:{
			DeleteObject((HGDIOBJ)hFont);

			return 0;
		}
		case WM_COMMAND:
			{
			switch(LOWORD(wParam))
			{
				case IDC_USE_UDP:
				{ 	// the user checked or unchecked the UseUDP check box
					if (bUseUDP)
						bUseUDP = FALSE;
					else
						bUseUDP = TRUE;
					return 1;
				}
				case IDC_AUTHLOOKUPBTN:
					{
					//get the name server and domain name to lookup
					_TCHAR nameServer[256];
					GetDlgItemText(hwnd,IDC_DNSSERVER,nameServer,256);
					_TCHAR lookUp[256];
					

					GetDlgItemText(hwnd,IDC_LOOKUP,lookUp,256);
					//clear the history window
					control.ClearHistory();

					//check the input strings
					if(nameServer[0] ==0){
						control.AddLine(_T("No Name Server Was Specified"));
						return 1;
					}
					if(lookUp[0] ==0){
						control.AddLine(_T("No Name Was Entered To Lookup"));
						return 1;
					}
					int wIndex = (WORD) SendMessage (hWndCombo, CB_GETCURSEL, 0, 0L);
                    // lets see what query is the user interested in
					queryType  = GetSelectedQuery(wIndex);
                  	//set the cursor to an hourglass
					SetCursor(LoadCursor(NULL,IDC_WAIT));
					dns.SetUseUDP (bUseUDP);
						if(dns.AuthoritativeLookup(nameServer,lookUp,queryType )== UTE_SUCCESS){
						dns.ResetEnumerations();
						CUT_DNSEntry entry;
						_TCHAR buf[1000];
						_TCHAR buf1[256], buf2[256], buf3[256];

						_stprintf(buf1,_T("%5s  %25.25s  %9.9s  %30.30s  %11s"),
							_T("ENTRY"),
							_T("HOST"), 
							_T("SHORTNAME"),
							_T("LONGNAME"),
							_T("TYPE"));
						_stprintf(buf2,_T("  %11s  %25.25s  %25.25s  %13s"),
							_T("TTL"),
							_T("DATA"),
							_T("DATA2"),
							_T("nMX_Preference"));
						_stprintf(buf3,_T("  %11s  %11s  %11s  %11s  %11s"),
							_T("SOA_SERIAL"),
							_T("SOA_REFRESH"),
							_T("SOA_RETRY"),
							_T("SOA_EXPIRE"),
							_T("SOA_MINIMUM"));
						_tcscpy(buf, buf1);
						_tcscat(buf, buf2);
						_tcscat(buf, buf3);
						control.SetTextColor(COLORREF(0x00FF0000));
						control.AddLine(buf);
						control.SetTextColor(COLORREF(0x00000000));
 
						//display the results
						int count = 0;
						while(dns.EnumDNSEntry(&entry) == CUT_SUCCESS){
						// v4.2 entry strings now _TCHAR
							_stprintf(buf1,_T("%5d  %25.25s  %9.9s  %30.30s  %11d"),
								count++,
								entry.szHost,
								dns.GetShortName(entry.nType),
								dns.GetLongName(entry.nType),
								entry.nType);
							wsprintf(buf2,_T("  %11lu  %25.25s  %25.25s  %13u"),
								entry.lTTL,
								entry.szData,
								entry.szData2,
								entry.nMX_Preference);
							wsprintf(buf3,_T("  %11lu  %11lu  %11lu  %11lu  %11lu"),
								entry.lSOA_Serial,
								entry.lSOA_Refresh,
								entry.lSOA_Retry,
								entry.lSOA_Expire,
								entry.lSOA_Minimum);
							_tcscpy(buf, buf1);
							_tcscat(buf, buf2);
							_tcscat(buf, buf3);
							control.AddLine(buf);
						}
					}
					else
						control.AddLine(_T("N/A"));

					//set the cursor back to the arrow
					SetCursor(LoadCursor(NULL,IDC_ARROW));
					return 1;
				}
				case IDC_ABOUT:{
					DialogBox(hInst,_T("IDD_ABOUT"),hwnd,(DLGPROC )AboutProc);
					return 1;
				}
				case IDC_LOOKUPBTN:{
					UpdateWindow(hwnd);
					//get the name server and domain name to lookup
					_TCHAR nameServer[256];
					GetDlgItemText(hwnd,IDC_DNSSERVER,nameServer,256);
					_TCHAR lookUp[256];
					GetDlgItemText(hwnd,IDC_LOOKUP,lookUp,256);
					
					//clear the history window
					control.ClearHistory();

					//check the input strings
					if(nameServer[0] ==0){
						control.AddLine(_T("No Name Server Was Specified"));
						return 1;
					}
					if(lookUp[0] ==0){
						control.AddLine(_T("No Name Was Entered To Lookup"));
						return 1;
					}

					//set the cursor to an hourglass
					SetCursor(LoadCursor(NULL,IDC_WAIT));
					dns.SetUseUDP (bUseUDP);
					int wIndex = (WORD) SendMessage (hWndCombo, CB_GETCURSEL, 0, 0L);
					// lets see what query is the user interested in
					queryType  = GetSelectedQuery(wIndex);

					// Issue the lookup call 
              		if(dns.LookupName(nameServer,lookUp,queryType )== UTE_SUCCESS){
						// lets start from the begining
						dns.ResetEnumerations();
						CUT_DNSEntry entry;
						_TCHAR buf[1000];
						_TCHAR buf1[256], buf2[256], buf3[256];
						_stprintf(buf1,_T("%5s  %35.25s  %9.9s  %30.30s  %11s"),
							_T("ENTRY"),
							_T("HOST"), 
							_T("SHORTNAME"),
							_T("LONGNAME"),
							_T("TYPE"));
						_stprintf(buf2,_T("  %11s  %s  %s  %13s"),
							_T("TTL"),
							_T("DATA"),
							_T("DATA2"),
							_T("nMX_Preference"));
						_stprintf(buf3,_T("  %11s  %11s  %11s  %11s  %11s"),
							_T("SOA_SERIAL"),
							_T("SOA_REFRESH"),
							_T("SOA_RETRY"),
							_T("SOA_EXPIRE"),
							_T("SOA_MINIMUM"));
						_tcscpy(buf, buf1);
						_tcscat(buf, buf2);
						_tcscat(buf, buf3);
						// change the Column headers colors to blue
						control.SetTextColor(COLORREF(0x00FF0000));
						control.AddLine(buf);
						control.SetTextColor(COLORREF(0x00000000));
						int count = 0;
						//display the results
						//enumerate the entries and display their memebers 
						while(dns.EnumDNSEntry(&entry) == CUT_SUCCESS){
						// v4.2 entry strings now _TCHAR
							_stprintf(buf1,_T("%5d  %25.25s  %9.9s  %30.30s  %11d"),
								count++,
								entry.szHost, // host name of the corresponding record
								dns.GetShortName(entry.nType), // the type of the record
								dns.GetLongName(entry.nType),
								entry.nType);
							_stprintf(buf2,_T("  %11lu  %35.35s  %35.35s  %13u"),
								entry.lTTL, // time to live 
								entry.szData, // data field 1
								entry.szData2, // data field 2
								entry.nMX_Preference); // mail exchange prefrence
							_stprintf(buf3,_T("  %11lu  %11lu  %11lu  %11lu  %11lu"),
								entry.lSOA_Serial, // Start of authority serial
								entry.lSOA_Refresh, // the time interval before the zone should be refreshed.
								entry.lSOA_Retry,
								entry.lSOA_Expire,
								entry.lSOA_Minimum);
							_tcscpy(buf, buf1);
							_tcscat(buf, buf2);
							_tcscat(buf, buf3);
							control.AddLine(buf);
						}
					}
					else
						control.AddLine(_T("N/A"));

					//set the cursor back to the arrow
					SetCursor(LoadCursor(NULL,IDC_ARROW));
					return 1;
				}
			}
			return 0;
		}
		case WM_CLOSE:{
			EndDialog(hwnd,0);
			return 1;
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
		
		rect.right = clientRect.right - rect.left;
		rect.bottom = clientRect.bottom - rect.left;
		
		MoveWindow(statWnd, rect.left, rect.top, rect.right-rect.left,rect.bottom-rect.top,TRUE);
		
		return 1;
				  }

	}
	return 0;
}

#pragma warning ( pop )