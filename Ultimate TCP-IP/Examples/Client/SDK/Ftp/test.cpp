/*******************************************
Ultimate TCP/IP FTP Client Test Program
Copyright 1995 - 1997 The Ultimate Toolbox.

********************************************/


#include "stdafx.h"
#include "test.h"
#include "uh_ctrl.h"
#include "ut_clnt.h"
#include "ftp_c.h"

HINSTANCE g_hInstance;

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

// v4.2 added this...
#define HISTORY_ENTRY_SIZE MAX_PATH + 80

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int)
{
	g_hInstance = hInstance;
	
	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);
	
	//create modal dialog box
	DialogBox(hInstance,_T("DIALOG_1"),NULL,(DLGPROC )DlgProc);
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
	static CUT_FTPClient ftpClient;
	static CUH_Control history;
	static int align = TA_LEFT;
	static int textColor = RGB(0,0,0);
	static int backColor = RGB(255,255,255);
	static HFONT hFont;
	HWND	hwndCheck1;
	int		state;
	
	
	switch(message)
	{
		
	case WM_INITDIALOG:
		{
			
			
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)));
			
			
			
			//attach the history window to the control
			history.AttachHistoryWindow(hwnd,IDC_HISTORY);
			//setup the history window
			history.SetHistoryLength(50);
			hFont = CreateFont(14,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			history.SetFont(hFont);
			SetDlgItemText(hwnd,IDC_EDIT,_T("localhost"));
			SetDlgItemText(hwnd,IDC_EDIT2,_T("anonymous"));// User
			SetDlgItemText(hwnd,IDC_EDIT3,_T("user@host.com")); // Password
			SetDlgItemText(hwnd,IDC_EDIT4,_T("")); // account
			SetDlgItemText(hwnd,IDC_QUOTE_DATA,_T("HELP"));
			
			// The default file transfer structure is file 
			CheckRadioButton(hwnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO1);
			
			return 1;
		}
		
	case WM_NCDESTROY:
		{
			//delete the font
			DeleteObject(hFont);
			return 0;
		}
		
	case WM_COMMAND:
		{
			
			switch(LOWORD(wParam))
			{
				
				//connect to an FTP site
			case IDC_CONNECT:
				{	
					
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					_TCHAR addr[256];
					_TCHAR user [256];
					_TCHAR pass [256];
					_TCHAR account[256];
					int retcode = 11;
					GetDlgItemText(hwnd, IDC_EDIT,addr,256);
					GetDlgItemText(hwnd, IDC_EDIT2,user,256);
					GetDlgItemText(hwnd, IDC_EDIT3,pass,256);
					GetDlgItemText(hwnd, IDC_EDIT4,account,256);
					
					if (_tcslen(addr) > 0)
					{
						retcode = ftpClient.FTPConnect(addr,user,pass,account);
						if( retcode == UTE_SUCCESS){			
							history.AddLine(_T("Connect Success"));
							int index = 0;
							// v4.2 GetMultiLineResponse refactored
							size_t size = 0;
							_TCHAR	pBuf[MAX_PATH+1];
							*pBuf = 0;
							while(ftpClient.GetMultiLineResponse(pBuf, MAX_PATH, index, &size) == UTE_SUCCESS) {
								index++;
								history.AddLine(pBuf);
							}							
						}
						else{	
							// ***************** Change to alarm color ************
							history.SetTextColor(RGB(255,0,0));
							history.AddLine(ftpClient.GetLastResponse ());
							history.AddLine(CUT_ERR::GetErrorString (retcode));
							history.SetTextColor(RGB(0,0,0));
							// change back to black text color
						}
					}
					
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					
					return 1;
				}
				
				//disconnect from an FTP site
			case IDC_DISCONNECT:
				{
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					if(ftpClient.Close() == UTE_SUCCESS)
						history.AddLine(_T("Disconnect Successful"));
					else{
						history.SetTextColor(RGB(255,0,0));
						history.AddLine(_T("Disconnect Failed"));
						history.SetTextColor(RGB(0,0,0));
					}
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
			case IDC_QUOTE:
				{
					_TCHAR quote[MAX_PATH];
					int retcode = 0;
					GetDlgItemText(hwnd, IDC_QUOTE_DATA,quote,MAX_PATH-1);
					if ((retcode = ftpClient.Quote(quote)) == UTE_SUCCESS)
					{
						int index = 0;
						// v4.2 GetMultiLineResponse refactored
						size_t size = 0;
						_TCHAR	pBuf[MAX_PATH+1];
						*pBuf = 0;
						while(ftpClient.GetMultiLineResponse(pBuf, MAX_PATH, index, &size) == UTE_SUCCESS) {
							index++;
							history.AddLine(pBuf);
						}
						
					}else{
						history.AddLine(ftpClient.GetLastResponse ());
						history.AddLine(CUT_ERR::GetErrorString (retcode));
					}
					return 1;
				}
				
				
				// Send a file to the remote host
			case IDC_SENDFILE:
				{	
					
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					int		retCode;
					_TCHAR  filetosend[256];
					_TCHAR  fileToSave[256];
					
					GetDlgItemText(hwnd, IDC_FILENAME,filetosend,256);
					GetDlgItemText(hwnd, IDC_SAVEAS,fileToSave,256);
					
					retCode = ftpClient.SendFile(filetosend, fileToSave);
					
					if (retCode == UTE_SUCCESS)
						history.AddLine(_T("Send File Successful"));
					else{
						history.SetTextColor(RGB(255,0,0));
						history.AddLine(_T("Send File Failed!"));
						history.SetTextColor(RGB(0,0,0));
					}
					
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
			case IDC_TEST_REST:
				{
					_TCHAR	filetoget[MAX_PATH];
					_TCHAR  filetosave[MAX_PATH];
					
					
					GetDlgItemText(hwnd, IDC_FILENAME,filetoget,MAX_PATH);
					GetDlgItemText(hwnd, IDC_SAVEAS,filetosave,MAX_PATH);
					
					int retCode = ftpClient.ResumeReceiveFile(filetoget,filetosave);
					if (retCode == UTE_SUCCESS)
						history.AddLine(_T("Receive file"));
					else{
						history.SetTextColor(RGB(255,0,0));
						history.AddLine( CUT_ERR::GetErrorString (retCode));
						history.SetTextColor(RGB(0,0,0));
					}
					return 1;
				}
				// Get file from the remote host
			case IDC_RETRFILE:
				{	
					
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					int		retCode;
					_TCHAR	filetoget[MAX_PATH];
					_TCHAR  filetosave[MAX_PATH];
					_TCHAR	buf[MAX_PATH+80];	// allow for text w/filename
					
					GetDlgItemText(hwnd, IDC_FILENAME,filetoget,MAX_PATH);
					GetDlgItemText(hwnd, IDC_SAVEAS,filetosave,MAX_PATH);
					
					if(*filetoget == _T('\0')) {
						history.AddLine(_T("No file name entered"));
						return 1;
					}
					
					if(*filetosave == _T('\0')) {
						_tcscpy(filetosave, filetoget);
					}
					
					retCode = ftpClient.ReceiveFile(filetoget, filetosave);
					
					if (retCode == UTE_SUCCESS)
					{	
						history.AddLine(_T("Receive File Successful"));
						_sntprintf(buf, sizeof(buf)/sizeof(_TCHAR), _T("File was saved to %s"),filetosave);
						history.AddLine(buf );
					}
					
					else
					{
						history.SetTextColor(RGB(255,0,0));
						history.AddLine(CUT_ERR::GetErrorString (retCode));
						history.SetTextColor(RGB(0,0,0));
					}
					
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
				
				// the FILE transfer structure was selected
			case IDC_RADIO1:
				CheckRadioButton(hwnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO1);
				ftpClient.SetTransferStructure(0);
				break;
				
				// The RECORD transfer structure was selected
			case IDC_RADIO2:
				CheckRadioButton(hwnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
				ftpClient.SetTransferStructure(1);
				break;
				
			case IDC_RADIO3:
				// The PAGE transfer structure was selected
				CheckRadioButton(hwnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO3);
				ftpClient.SetTransferStructure(2);
				break;
				
				// Setting the fire wall mode on or of from when set PASV command will be sent each time we need to call 
				// LIST command 
				// Not all servers support the firewall mode
			case IDC_FIREWALL:
				hwndCheck1 = GetDlgItem(hwnd,IDC_FIREWALL);
				state = (int)SendMessage(hwndCheck1,BM_GETSTATE,0,0l);
				if(state&BST_CHECKED)
					ftpClient.SetFireWallMode(TRUE);
				else
					ftpClient.SetFireWallMode(FALSE);
				break;
				
				// Select either Image or ASCII for file Transfer type
				
			case IDC_TRANSFER_TYPE:
				hwndCheck1 = GetDlgItem(hwnd,IDC_TRANSFER_MODE);
				state = (int)SendMessage(hwndCheck1,BM_GETSTATE,0,0l);
				if(state&BST_CHECKED)
					ftpClient.SetTransferType(1);  // if checked then it is 1 = Image 
				else
					ftpClient.SetTransferType(0); // if not Selected then it is 0 = ASCII
				break;
				
				// GEt the directory information
			case IDC_LIST:
				{	
					
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					
					CUT_DIRINFO di;
					_TCHAR entry[HISTORY_ENTRY_SIZE];
					int RetCode = 0;	
					
					RetCode = ftpClient.GetDirInfo();
					
					
					if (RetCode == UTE_SUCCESS)
					{
						int count = ftpClient.GetDirInfoCount();
						history.AddLine(_T("Current Dir:"));
						for(int t=0;t<count;t++){
							ftpClient.GetDirEntry(t,&di);
							// v4.2 - changed dir info now has _TCHAR
							_sntprintf(entry, sizeof(entry)/sizeof(_TCHAR), _T("%s  %ld %2.2d/%2.2d/%2.2d %2.2d:%2.2d"),
							di.fileName,di.fileSize,di.year,di.month,
							di.day,di.hour,di.minute);
							
							history.AddLine(entry);
						}
						
					}
					else
					{	history.SetTextColor(RGB(255,0,0));
					history.AddLine(CUT_ERR::GetErrorString (RetCode));
					history.SetTextColor(RGB(0,0,0));
					}
					
					
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
				
				// Call the ChDir command  to change the directory 
			case 	IDC_CHANGEDIR:
				{	
					
					SetCursor(LoadCursor(NULL, IDC_WAIT));
					
					history.SetTextColor(RGB(0,0,255));
					history.AddLine(_T("============================================"));
					history.SetTextColor(RGB(0,0,0));
					
					CUT_DIRINFO di;
					_TCHAR entry[HISTORY_ENTRY_SIZE];
					_TCHAR dir[MAX_PATH];
					int valRet;
					GetDlgItemText(hwnd, IDC_DIRCHANGE,dir,256);
					if (_tcslen(dir)> 0)
					{
						valRet = ftpClient.ChDir(dir);
						if (valRet  != UTE_SUCCESS){
							history.SetTextColor(RGB(255,0,0));
							history.AddLine(CUT_ERR::GetErrorString (valRet));
							history.SetTextColor(RGB(0,0,0));
						}
						else {
							ftpClient.GetDirInfo();
							int count = ftpClient.GetDirInfoCount();
							for(int t=0;t<count;t++){
								ftpClient.GetDirEntry(t,&di);
								// v4.2 dir info now has _TCHAR
								_sntprintf(entry, sizeof(entry)/sizeof(_TCHAR), _T("%s  %ld %2.2d/%2.2d/%2.2d %2.2d:%2.2d"),
									di.fileName,di.fileSize,di.year,di.month,
									di.day,di.hour,di.minute);
								history.AddLine(entry);
							}
						}
						
					}	// User did not  enter any string in the edit box
					else 
					{	
						_sntprintf(entry, sizeof(entry)/sizeof(_TCHAR), _T(" Please Enter a directory Name"));
						history.SetTextColor(RGB(255,0,0));
						history.AddLine(entry);
						history.SetTextColor(RGB(0,0,0));
					}
					SetCursor(LoadCursor(NULL, IDC_ARROW));
					return 1;
				}
				
			case IDC_ABOUT:
				{
					DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC )AboutProc);
					return 1;
				}
				
				//exit the program
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