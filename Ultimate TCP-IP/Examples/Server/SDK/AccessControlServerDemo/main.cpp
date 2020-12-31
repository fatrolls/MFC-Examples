// =================================================================
//  Ultimate TCP/IP Access Control Server Test
//  File:  main.CPP
//
//
// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 2000-2001, all rights reserverd
// =================================================================
#include "stdafx.h"
#include <shlobj.h> 
#include "uh_ctrl.h"
#include "resource.h"
#include "SampleSvr.h"
#include "AccessSampleThread.h"
#include <commctrl.h>

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


#define AS_PORT 9013	// accept connections on this port

							// Server Object
CUT_AccessServer			g_Srvr;
							// The current Display list Access Type 
enumAccessType				g_enAccessType = ACCESS_BLOCKED;

							// Prototype of dialog proc
BOOL CALLBACK				DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK				DlgConfig(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK				DlgAddIP(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgAbout(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

							// this application instance
HINSTANCE					hInst = NULL;

							// status history control of the server
CUH_Control					status;
							// font to be used with the statu
HFONT						hFont = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, VARIABLE_PITCH | FF_SWISS, _T(""));

long						g_CurrentEditSel = -1;
							// main window proc
int WINAPI					WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	// this global object will be used in the comunication between dialogs 
	hInst = hInstance;
	
	// in this sample we will be using the new comon control IP Address
	// so we need toRegisters ICC_INTERNET_CLASSES common control classes from the common control dynamic-link library (DLL). 
	INITCOMMONCONTROLSEX		intSt;
	intSt.dwICC					= ICC_INTERNET_CLASSES ;
	intSt.dwSize				= (BYTE) sizeof(INITCOMMONCONTROLSEX); 
	InitCommonControlsEx(&intSt);
	

	// init the history/logging control
	CUH_Control::RegisterWindowClass(hInstance);
	
	// create modal dialog box and display it 
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC )DlgProc);

	// reclaim resources
	DeleteObject(hFont);
	return 0;
}
// Main window Proc
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	// connected flag
	static BOOL bConnected = FALSE;
	
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
		case WM_INITDIALOG:
		{
			// set the window icon
			//SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));			
			status.AttachHistoryWindow(hwnd,IDC_HISTORY);
			status.SetFont(hFont);
			status.SetHistoryLength(50);
			// assign the history control to the server's
			g_Srvr.m_status = &status;
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
		
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
				case IDC_EXIT:
				{
					// exit window
					g_Srvr.StopAccept ();
					EndDialog(hwnd,0);
					break;
				}
				// The start button was clicked
				case IDC_START:
				{
					// are we already connected
					if (!bConnected)
					{
						// connect to the port number 
						if (g_Srvr.ConnectToPort (AS_PORT) == UTE_SUCCESS)
						{
							// start accepting incoming connections
							g_Srvr.StartAccept();
							// display message on history control
							_TCHAR buf[80];
							_stprintf(buf, _T("Waiting for Connection on port %d"),AS_PORT);
							status.AddLine(buf);
							
							// change the caption of the button
							SetDlgItemText(hwnd,IDC_START,_T("Stop"));
							// we are cionnected
							bConnected = TRUE;
						}
						else // we failed to connect
							status.AddLine ("Listening failed , you must be running other server on the same port");
					}
					else // we are already connected
					{  // stop accepting new connections
						g_Srvr.StopAccept ();
						// not connected anymore
						bConnected = FALSE;
						// display message
						status.AddLine ("Stopped Accepting");
						// change the caption on the button
						SetDlgItemText(hwnd,IDC_START,_T("Start"));
					}
					break;
				}
				
				// the user need to controll access to specific IP addresses
			case IDC_CONTROL_ACCESS:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ACCESS_CONTROL_CONFIG), hwnd, (DLGPROC )DlgConfig);
					break;					
				}
			case IDC_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )DlgAbout);
					break;					

				}
				
			}
			break;
		}
	}
	return 0;
}

//
// in this dialog proc we will handle the display of 
// the currently list of IP that we are attempting to control the 
// access of our server
BOOL CALLBACK DlgConfig(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{
	
	// temporary general use IP address variables
	in_addr ipStart, ipEnd;
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
	case WM_INITDIALOG:
		{

			// Set the default checked button				
			switch (g_enAccessType)
			{
			case ACCESS_ALLOWED:
				{
					// group the check boxes and set the default one based on the global 
					// last accessed list
					CheckRadioButton(hwnd,IDC_BLOCKED,IDC_TEMP_BLOCKED,IDC_ALLOWED);
					break;
					
				}
			case ACCESS_BLOCKED:
				{
					// group the check boxes and set the default one based on the global 
					// last accessed list
					CheckRadioButton(hwnd,IDC_BLOCKED,IDC_TEMP_BLOCKED,IDC_BLOCKED);
					break;
					
				}	
			case ACCESS_TEMP_BLOCKED:
				{
					// group the check boxes and set the default one based on the global 
					// last accessed list
					CheckRadioButton(hwnd,IDC_BLOCKED,IDC_TEMP_BLOCKED,IDC_TEMP_BLOCKED);
					break;
					
				}	
			}
			// disable the delete and edit buttons
			EnableWindow(GetDlgItem(hwnd, IDC_DELETE),FALSE);			
			EnableWindow(GetDlgItem(hwnd, IDC_EDIT),FALSE);			
			// call the refresh button to display a fresh list of the selected 
			// list
			SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);
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
					LRESULT count = SendMessage(GetDlgItem(hwnd, IDC_IP_LIST) ,LB_GETCOUNT ,0,0);
					// if we have any elements
					if (count > 0)
					{
						// we can delete so enable it						
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE),TRUE);
						// we don't want to enable the edit in the case of temporary block
						if (g_enAccessType != ACCESS_TEMP_BLOCKED)
							EnableWindow(GetDlgItem(hwnd, IDC_EDIT),TRUE);
						
					}
					else
					{
						// we don't have anything to delete
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE),FALSE);			
						// // we don't have anything to Edit
						EnableWindow(GetDlgItem(hwnd, IDC_EDIT),FALSE);			
					}
					break;

				}
				case LBN_SELCANCEL:
				{
					// we lost focus so disable them
					EnableWindow(GetDlgItem(hwnd, IDC_DELETE),FALSE);	
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT),FALSE);			
					break;
				}
				case LBN_DBLCLK:
					{
						// we don't want to enable the edit on temporary block , for demo 
						// so we either delete or add
						if (g_enAccessType != ACCESS_TEMP_BLOCKED )			
							SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_EDIT,0);
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
			case IDC_ADD:
				{
						// show the dialog box
					g_CurrentEditSel= -1;
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_IP_DLG), hwnd, (DLGPROC )DlgAddIP);
					// refresh the current display
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);				
					break;
					
				}
			case IDC_DELETE:// delete the selected ip address
				{
					LRESULT count = SendMessage(GetDlgItem(hwnd, IDC_IP_LIST) ,LB_GETCOUNT ,0,0);
					if (count > 0) // the list has elemenets ?
					{
					int nAnswer =  MessageBox(NULL, _T("Are you sure you want to remove the selected IP Address ?"),_T("Confirm") ,  MB_YESNO);
					if (nAnswer == IDYES)
					{
						// get the current selecteion
						LRESULT nIndex = SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_GETCURSEL, 0, 0);
						// then remove it from the blocked list
						g_Srvr.m_aclObj.DeleteAddress (g_enAccessType,(long)nIndex);
						// send A message with delete command 						
						SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_DELETESTRING, nIndex, 0);
						// refresh the display 
						SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);	
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE),FALSE);			
			
					}
					}
					break;
				}
			case IDC_EDIT:
				{
				if (g_enAccessType != ACCESS_TEMP_BLOCKED )
					{
						// get the current selection and pass it as a user defined data 
						// 
						g_CurrentEditSel = (long)SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_GETCURSEL, 0, 0);
						// Set the Edit Flag on and call the same dialog as the 
						// add so we can show it
						DialogBox(hInst, MAKEINTRESOURCE(IDD_ADD_IP_DLG), hwnd, (DLGPROC )DlgAddIP);
					}
					// refresh the current display
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);
			
				}
			case IDC_REFRESH:
				{
					
					// refresh the current display in the 
					// list box based on the selected access type
					HWND hwndList = GetDlgItem(hwnd, IDC_IP_LIST);  
					_TCHAR szBuffer[MAX_PATH];
					
					// first clear the existing list
					SendMessage( 
						(HWND) hwndList,              // handle to destination window 
						LB_RESETCONTENT,          // message to send
						(WPARAM) 0,         // not used; must be zero
						(LPARAM) 0          // not used; must be zero
						);
					
					// Add a list of selected type IP addresses 
					if (g_enAccessType != ACCESS_TEMP_BLOCKED )
					{
						// loop through the list of available IP addresses
						for (int counter= 0; counter < g_Srvr.m_aclObj.GetAddressListSize(g_enAccessType) ; counter++)
						{
							// get the range of addresses
							g_Srvr.m_aclObj.GetAddress (g_enAccessType,counter,ipStart,ipEnd);
							_sntprintf(szBuffer, MAX_PATH,_T("[%s] to ["), g_Srvr.m_aclObj.IPToString (ipStart));
							_TCHAR szTemp[32];
							size_t size = 0;
							g_Srvr.m_aclObj.IPToString (szTemp, 32, ipEnd, &size); 
							_tcscat (szBuffer, szTemp);
							_tcscat (szBuffer,_T("]"));
							SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_ADDSTRING, 0, (LPARAM)szBuffer);
						}
					}
					else
					{
						 int nListSize =  g_Srvr.m_aclObj.GetAddressListSize (g_enAccessType);
							long lBlockCounter = 0 ;
							time_t tExpiryTime ;
							_TCHAR szBuf[MAX_PATH];
							in_addr ipAddrTemp;
							_TCHAR szIpAddresszIp[32];

				 		  for (int counter = 0; counter < nListSize; counter++)
						  {
							   g_Srvr.m_aclObj.GetTempBlockedAddress (counter,ipAddrTemp,lBlockCounter,tExpiryTime);
							   _TCHAR szTemp[32];
						    	size_t size = 0;
								g_Srvr.m_aclObj.IPToString (szTemp, 32, ipEnd, &size); 
							   _tcscpy(szIpAddresszIp, szTemp); 
							   _sntprintf(szBuf, MAX_PATH,_T("(%s), Expires:%s"), szIpAddresszIp,_tasctime( localtime( &tExpiryTime) ) );
							   SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_ADDSTRING, 0, (LPARAM)szBuf);							  
						  }
						 
				
					}

					LRESULT count = SendMessage(GetDlgItem(hwnd, IDC_IP_LIST) ,LB_GETCOUNT ,0,0);
					if (count > 0)
					{
						LRESULT nIndex = SendMessage(GetDlgItem(hwnd, IDC_IP_LIST), LB_GETCURSEL, 0, 0);
						if (LB_ERR != nIndex)
						{
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE),TRUE);
						if (g_enAccessType != ACCESS_TEMP_BLOCKED)
							EnableWindow(GetDlgItem(hwnd, IDC_EDIT),TRUE);
						}
						
					}
					else
					{
						EnableWindow(GetDlgItem(hwnd, IDC_DELETE),FALSE);
						EnableWindow(GetDlgItem(hwnd, IDC_EDIT),FALSE);

					}

					break;
				}
				// The user selected on of the radio buttons
			case IDC_BLOCKED:
				{
					// change the current display type to the 
					// selected type and send a refreshe Message toe display it
					g_enAccessType = ACCESS_BLOCKED ;
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);
					break;
				}
				
			case IDC_ALLOWED:
				{
					// change the current display type to the 
					// selected type and send a refreshe Message toe display it
					g_enAccessType = ACCESS_ALLOWED	;
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);
					break;
				}
			case IDC_TEMP_BLOCKED:
				{
					// change the current display type to the 
					// selected type and send a refreshe Message toe display it
					g_enAccessType =	ACCESS_TEMP_BLOCKED;
					EnableWindow(GetDlgItem(hwnd, IDC_EDIT),FALSE);
					SendMessage(hwnd, WM_COMMAND, (WPARAM)IDC_REFRESH,0);
					break;
				}
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
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
	case WM_INITDIALOG:
		{
			// get the user selection 
			// if it is not -1 then the user is editing the entry
			bRangeCliecked = FALSE;
		
			if (g_CurrentEditSel != -1 )
			{
				// set up the IP Addess controls to hold the passwed ip address range
				in_addr		ipEnd;
				in_addr		ipStart;
				DWORD dwAddr;
				if (g_enAccessType != ACCESS_TEMP_BLOCKED )
				{
					// get the start and end of the IP addresses
					g_Srvr.m_aclObj.GetAddress (g_enAccessType,g_CurrentEditSel,ipStart,ipEnd);
					// reverse the words for display
					dwAddr = (DWORD)htonl(ipStart.S_un.S_addr ) ;
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_SETADDRESS,0,(LPARAM)dwAddr);
					// reverse the words for display
					dwAddr = (DWORD)htonl(ipEnd.S_un.S_addr );
					SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS2),IPM_SETADDRESS,0,(LPARAM)dwAddr);

					EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),TRUE);			
				}
				else
					{
						long lBlockCounter;
						time_t tExpiryTime;

						g_Srvr.m_aclObj.GetTempBlockedAddress (g_CurrentEditSel,ipStart,lBlockCounter,tExpiryTime);
						

						dwAddr = (DWORD)ipStart.S_un.S_addr  ;

						SendMessage(GetDlgItem(hwnd,IDC_IPADDRESS1),IPM_SETADDRESS,0,(LPARAM)(DWORD)dwAddr);
						EnableWindow(GetDlgItem(hwnd,IDC_RANGE),FALSE);
						EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),FALSE);	
				}					
			}else
			{	
				EnableWindow(GetDlgItem(hwnd,IDC_IPADDRESS2),bRangeCliecked);
				
			}
			if (g_enAccessType == ACCESS_TEMP_BLOCKED )
				{
					EnableWindow(GetDlgItem(hwnd,IDC_RANGE),FALSE);
				}
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
					
					
					// ok so the IP Address control returns the address back word
					// oh well we will carve it then byte by byte
					// Start Address
					adStart.S_un.S_un_b.s_b1  = (unsigned char)FIRST_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b2  =(unsigned char)SECOND_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b3  =(unsigned char)THIRD_IPADDRESS((LPARAM )dwStartAddr);
					adStart.S_un.S_un_b.s_b4  =(unsigned char)FOURTH_IPADDRESS((LPARAM )dwStartAddr);

					// // End Address
					adEnd.S_un.S_un_b.s_b1  =(unsigned char)FIRST_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b2  =(unsigned char)SECOND_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b3  =(unsigned char)THIRD_IPADDRESS((LPARAM )dwEndAddr);
					adEnd.S_un.S_un_b.s_b4  =(unsigned char)FOURTH_IPADDRESS((LPARAM )dwEndAddr);

					if(g_enAccessType != ACCESS_TEMP_BLOCKED )
					{
						// if we are editing , then delete the selection before we add the modified one
						if (g_CurrentEditSel != -1)
						{
							g_Srvr.m_aclObj.DeleteAddress (g_enAccessType,g_CurrentEditSel);
							g_Srvr.m_aclObj.AddAddress (g_enAccessType,adStart,&adEnd);	
						}
						else
						{
							if (bRangeCliecked)					
								g_Srvr.m_aclObj.AddAddress (g_enAccessType,adStart,&adEnd);	
							else
								g_Srvr.m_aclObj.AddAddress (g_enAccessType,adStart);	
						}

					}
					else // if we are adding to the temp delete lets call the proper function
						g_Srvr.m_aclObj.AddTempBlockedAddress (adStart);	
					
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

//
// Display the about box
BOOL CALLBACK DlgAbout(HWND hwnd, UINT message, WPARAM wParam, LPARAM /* lParam */)
{	
	
	
	// dispatch tyhe window messages
	switch(message)
	{
		// dialog initialization command
	case WM_INITDIALOG:
		{
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
			case IDOK:
				{
					EndDialog(hwnd,0);
					break;
				}
			}
			break;
		}
	}
	return 0;
}

#pragma warning ( pop )