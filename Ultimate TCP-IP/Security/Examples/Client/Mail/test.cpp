// ===================================================================
//	 Ultimate TCP-IP v4.2 
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================
//


// This sample consists of two major dialogs 
//
// 1) The first is the SMTP (simple mail transfer protocol) dialog
//
//		- using this dailog you can create a message 
//
//		- add attachment to a message. The attachments are created by going through the 
//      number of strings in the attachment combobox. The attachment encoding type is
//      defaulted to MIME version 1.0
//
//		- For simplicity we did not create this sample in a multithreaded app. You may 
//      want to modify this app to a multithreaded app to be able to control or interpert
//      the send process such as returning false from the virtual function 
//      BOOL testSMTP::OnSendMailProgress(long bytesSent,long totalBytes) of 
//      the derived class testSMTP
//
// 2) The second dialog is a POP3 (post office protocol revision 3) dialog
//		- enables you to connect to a POP3 server using your user name and password
//
//		- after a successful connnection the number of available messages will be shown
//
//		- after entering the message number you are intersted in you can see the top headers
//      of the specified messages in the Message Information list box
//
//		- When you click the retrieve button, the message will be read into a CUT_Msg 
//      object which will enable you to see the diffrent fields of the message
//
//		- if the message includes any attachments, the file names of each attachment will be 
//      inserted in the Attachment combo box. You will be able to decode the 
//      selected message to a filename of your choice by clicking the Save Attachment
//      button.
//


#include "stdafx.h"
#include "ut_clnt.h"
#include "pop3_c.h"
#include "smtp_c.h"
#include "UTMEssage.h"
#include "UTUUEncode.h"
#include "test.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


BOOL CALLBACK SMTPDlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK POP3DlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK ATTACHDlgProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK AboutProc(HWND,UINT,WPARAM,LPARAM);
int SaveAttachment(HWND hwnd, CUT_Msg& theMessage, int iIndex);

HINSTANCE g_hInstance;
HWND g_hwnd;
_TCHAR szFileAtt[_MAX_PATH];


// We want to see the progres of the message sent so we derive our own class
// and override OnSendMailProgress virtual function
//
class testSMTP : public CUT_SMTPClient
{
public :
	testSMTP ()
	{
#ifdef CUT_SECURE_SOCKET
		m_CertValidation = CERT_VERIFY_AND_ASK;
#endif


	}
protected:
	virtual BOOL OnSendMailProgress(long bytesSent, long totalBytes);
};




int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int)
{
	g_hInstance = hInstance;
	
	//create modal dialog box
	DialogBox(hInstance,MAKEINTRESOURCE(IDD_SMTP),NULL, (DLGPROC )SMTPDlgProc);
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




BOOL CALLBACK SMTPDlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	// Window procedure for SMTP dialog
	
	int rt;
	switch(message)
	{
		case WM_INITDIALOG:
		{

			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)));

			// Fill in the fields with some default text. 
			SetDlgItemText(hwnd,IDC_SMTPSERVER,_T("enter your Secure SMTP Server here"));
			SetDlgItemText(hwnd,IDC_TO,_T("enter the To Field here"));
			SetDlgItemText(hwnd,IDC_FROM,_T("enter the From Field here"));
			SetDlgItemText(hwnd,IDC_SUBJECT,_T("Secure Example"));
			SetDlgItemText(hwnd,IDC_MESSAGE,_T("This message was sent to you using a \r\nTLS enabled client of The Ultimate Toolbox"));
			g_hwnd = hwnd;
			return 1;
		}
		case WM_CLOSE:
		{
			EndDialog(hwnd,0);
			break;
		}
		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{

				case IDC_ABOUT:
					{
						// display about box
						DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ABOUT),NULL, (DLGPROC )AboutProc);

					}
					break;


				case IDC_SENDMAIL:
					{
						_TCHAR host[256];
						_TCHAR to[4096];
						_TCHAR from[256];
						_TCHAR subject[256];
						_TCHAR message[4096];
						_TCHAR FileAtt[_MAX_PATH];
						_TCHAR ErrorMessage[500];

						CUT_Msg		EncodedMsg2;

						// Get text fields from dialog
						GetDlgItemText(hwnd,IDC_SMTPSERVER,host,sizeof(host)/sizeof(_TCHAR));
						GetDlgItemText(hwnd,IDC_TO,to,sizeof(to)/sizeof(_TCHAR));
						GetDlgItemText(hwnd,IDC_FROM,from,sizeof(from)/sizeof(_TCHAR));
						GetDlgItemText(hwnd,IDC_SUBJECT,subject,sizeof(subject)/sizeof(_TCHAR));
						GetDlgItemText(hwnd,IDC_MESSAGE,message,sizeof(message)/sizeof(_TCHAR));
						
						// Initialize message object
						EncodedMsg2.AddHeaderField(to, UTM_TO);
						EncodedMsg2.AddHeaderField(from, UTM_FROM);
						EncodedMsg2.AddHeaderField(subject, UTM_SUBJECT);
						EncodedMsg2.SetMessageBody(message);

						// Read the attachments from the combo box and add them to the message object
						HWND hWndCombo = GetDlgItem(hwnd,IDC_COMBO1);
						WORD wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
						for (int loop = 0 ; loop < wCount; loop++)
						{
							SendMessage (hWndCombo,
							CB_GETLBTEXT,
							loop,
							(LONG)(ULONG_PTR)(LPSTR)FileAtt);
							if(_tcslen(FileAtt) > 0)
							{
								rt = EncodedMsg2.AddAttachment(FileAtt);
								if(rt != UTE_SUCCESS)
								{
									_sntprintf(ErrorMessage, sizeof(ErrorMessage),_T("%s \n %s "),FileAtt, CUT_ERR::GetErrorString(rt));
									MessageBox(NULL, ErrorMessage, _T("ERROR"), MB_OK);
								}		
							}
						}

						testSMTP  smtp;
						smtp.SetSecurityEnabled ();
						
						rt =  smtp.SMTPConnect(host,_T("localhost"));
						if (rt == CUT_SUCCESS)
						{
							
							
							
							rt = smtp.SendMail(EncodedMsg2);
							
							smtp.SMTPClose();
							
							// display status to user
							if (rt == CUT_SUCCESS)
							{
								SetDlgItemText(hwnd,IDC_STATUS,_T("Done"));
								MessageBox(hwnd,_T("Message Sent Successfully"),_T("Finished"),MB_OK);
								SetDlgItemText(hwnd,IDC_STATUS,_T("Ready"));
								SetDlgItemText(hwnd,IDC_PROGRESS,_T("Done"));
								smtp.SMTPClose ();
							}
							else
							{
								MessageBox(hwnd,CUT_ERR::GetErrorString (rt),_T("Warning"),MB_OK);	
								SetDlgItemText(hwnd,IDC_STATUS,_T("Ready"));
								SetDlgItemText(hwnd,IDC_PROGRESS,_T("Failed"));
								smtp.SMTPClose ();
							}
						}
						else
						{
							MessageBox(hwnd,CUT_ERR::GetErrorString (rt),_T("Warning"),MB_OK);
							SetDlgItemText(hwnd,IDC_STATUS,_T("Ready"));
							SetDlgItemText(hwnd,IDC_PROGRESS,_T("Failed"));
							smtp.SMTPClose ();
							
						}

						return 1;
					}

				case IDC_BROWSE:
					{
						// allow the user to `browse' for a file name
						DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ATTACH_DLG),hwnd, (DLGPROC)ATTACHDlgProc);
						if (_tcslen(szFileAtt))
						{
							HWND hWndCombo = GetDlgItem(hwnd,IDC_COMBO1);
							SendMessage (hWndCombo,
								CB_ADDSTRING,
								0,
								(LONG)(ULONG_PTR)(LPSTR) szFileAtt);
						}
						return 1;
					}

				case IDC_DEL: // reset the attachment list in the combo box
					{
						HWND hWndCombo = GetDlgItem(hwnd,IDC_COMBO1);
						SendMessage(hWndCombo,CB_RESETCONTENT, 0, 0L);
						return 1;
					}

				case IDC_POP3:
					{
						//create the POP3 dialog box
						DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_POP3), hwnd, (DLGPROC )POP3DlgProc);
						return 1;
					}

				case IDC_EXIT:
					{
						EndDialog(hwnd,0);
						return 1;
					}
			}
			return 0;
		}
	}
	return 0;
}


BOOL CALLBACK POP3DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	static CUT_POP3Client pop;
	static HWND hWndCombo;
	static CUT_Msg theMessage;
	
	switch(message)
	{
		
	case WM_INITDIALOG:
		{
			// set the window icon
			SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1)));

			hWndCombo = GetDlgItem(hwnd,IDC_POP3_COMBO);
			HWND hWnndsaveBtn = GetDlgItem(hwnd,IDC_SAVE_ATTACH);
			// disable the SaveAttachment button
			EnableWindow(
				hWnndsaveBtn,     // handle to window
				FALSE   // flag for enabling or disabling input
				);
			HWND hWnndBtn = GetDlgItem(hwnd,IDC_DELETE);
			// disable the retrieve button if we don't have messages 
			EnableWindow(
				hWnndBtn,     // handle to window
				FALSE   // flag for enabling or disabling input
				);
			hWnndBtn = GetDlgItem(hwnd,IDC_TOP);
			// disable the retrieve button if we don't have messages 
			EnableWindow(
				hWnndBtn,     // handle to window
				FALSE   // flag for enabling or disabling input
				);
			hWnndBtn = GetDlgItem(hwnd,IDC_RETRIEVE);
			// disable the retrieve button if we don't have messages 
			EnableWindow(
				hWnndBtn,     // handle to window
				FALSE   // flag for enabling or disabling input
				);
		
			return 1;
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
			case IDC_CONNECT:
				{
					_TCHAR host[256];
					_TCHAR user[256];
					_TCHAR pass[256];
					_TCHAR buf[256];
					
					GetDlgItemText(hwnd,IDC_HOST,host,sizeof(host));
					GetDlgItemText(hwnd,IDC_USER,user,sizeof(user));
					GetDlgItemText(hwnd,IDC_PASS,pass,sizeof(pass));

					// connect using TLS
					pop.SetSecurityEnabled ();
					if(pop.POP3Connect(host,user,pass) != CUT_SUCCESS)
					{
						MessageBox(hwnd,_T("Connection Failed"),_T("Warning"),MB_OK);
						return 1;
					}
					int number;
					pop.GetNumMsgs(&number);
					if (number < 1){
						HWND hWnndBtn = GetDlgItem(hwnd,IDC_DELETE);
						// disable the retrieve button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							FALSE   // flag for enabling or disabling input
							);
						hWnndBtn = GetDlgItem(hwnd,IDC_TOP);
						// disable the retrieve button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							FALSE   // flag for enabling or disabling input
							);
						hWnndBtn = GetDlgItem(hwnd,IDC_RETRIEVE);
						// disable the retrieve button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							FALSE   // flag for enabling or disabling input
							);
					}
					else
					{
						HWND hWnndBtn = GetDlgItem(hwnd,IDC_DELETE);
						// enable the Delete button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							TRUE   // flag for enabling or disabling input
							);
						hWnndBtn = GetDlgItem(hwnd,IDC_TOP);
						// enable the top button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							TRUE   // flag for enabling or disabling input
							);
						hWnndBtn = GetDlgItem(hwnd,IDC_RETRIEVE);
						// enable the retrieve button if we don't have messages 
						EnableWindow(
							hWnndBtn,     // handle to window
							TRUE   // flag for enabling or disabling input
							);
					}

					_sntprintf(buf, sizeof(buf),_T("%d"),number);
					SetDlgItemText(hwnd,IDC_NUMMSGS,buf);
					
					SetDlgItemText(hwnd,IDC_STATUS,_T("Connection Successful"));
					
					return 1;
				}
			case IDC_DISCONNECT:
				{
					// clear the message object
					theMessage.EmptyAttachmentList();
					theMessage.ClearHeader();
					
					pop.POP3Close();
					SetDlgItemText(hwnd,IDC_STATUS,_T("Not Connected"));
					HWND hWnndsaveBtn = GetDlgItem(hwnd,IDC_SAVE_ATTACH);
					// disable the SaveAttachment button
					EnableWindow(
						hWnndsaveBtn,     // handle to window
						FALSE   // flag for enabling or disabling input
						);
					HWND hWnndBtn = GetDlgItem(hwnd,IDC_DELETE);
					// disable the retrieve button if we don't have messages 
					EnableWindow(
						hWnndBtn,     // handle to window
						FALSE   // flag for enabling or disabling input
						);
					hWnndBtn = GetDlgItem(hwnd,IDC_TOP);
					// disable the retrieve button if we don't have messages 
					EnableWindow(
						hWnndBtn,     // handle to window
						FALSE   // flag for enabling or disabling input
						);
					hWnndBtn = GetDlgItem(hwnd,IDC_RETRIEVE);
					// disable the retrieve button if we don't have messages 
					EnableWindow(
						hWnndBtn,     // handle to window
						FALSE   // flag for enabling or disabling input
						);
					
					return 1;
				}
				
			case IDC_EXIT:
				{
					EndDialog(hwnd,0);
					return 1;
				}
			case IDC_TOP:
				{
					// top will not tell us the number of attachments so lets just display 0 for now
					SetDlgItemInt(hwnd,IDC_NUM_ATTACH,0,FALSE);
					// we will add the top headers to the list box
					HWND hwndList = GetDlgItem(hwnd,IDC_MSGLIST);
					_TCHAR buf[2048];
					// which message is the user interested in
					GetDlgItemText(hwnd,IDC_MSGNUM,buf,sizeof(buf)/sizeof(TCHAR));
					pop.CloseTop(); //lets make sure that all previous tops are closed
					if(pop.OpenTop(_ttoi(buf),0) != CUT_SUCCESS)
					{
						MessageBox(hwnd,_T("Top Failed to open a message"),_T("Warning"),MB_OK);
					}
					else
					{
						int rt;
						int pos = 0;
						SendMessage(hwndList,LB_RESETCONTENT ,0,0);   // Clear the list
						// v4.2 changed - was while(1)			
						for(;;)
						{
							rt = pop.ReadTopLine(buf,1023);
							if(rt <=0)
								break;
							pos += rt;
							SendMessage(hwndList,LB_ADDSTRING ,0,(LPARAM)buf);   // address of string to add 
						}
						pop.CloseTop();
						pop.CloseMsg();
						//buf[pos] =0;
					}
					return 1;
				}
			case IDC_RETRIEVE:
				{
					// retrive the messag from the server into
					// a message object
					_TCHAR buf[4096];
					_TCHAR type[MAX_PATH];
					int rt;
					WORD wCount = 0;
					// clear the attachment combo box
					wCount = (WORD) SendMessage (hWndCombo, CB_GETCOUNT, 0, 0L);
					if (wCount)
					{
						SendMessage (hWndCombo,CB_RESETCONTENT, 0, 0L);
					}
					// clear all edit boxes
					SetDlgItemText(hwnd,IDC_POP3_FROM,_T(""));
					SetDlgItemText(hwnd,IDC_POP3_TO,_T(""));
					SetDlgItemText(hwnd,IDC_POP3_SUBJECT,_T(""));
					SetDlgItemText(hwnd,IDC_POP3_CC,_T(""));
					SetDlgItemText(hwnd,IDC_MESSAGE,_T(""));
					
					// reset the message object
					theMessage.EmptyAttachmentList();
					theMessage.ClearHeader();
					
					
					LoadCursor(g_hInstance, IDC_WAIT);
					GetDlgItemText(hwnd,IDC_MSGNUM,buf,sizeof(buf)/sizeof(_TCHAR));
					
					// lets save the message to a dummy file 
					long lMsgSize;
					pop.GetMsgSize(_ttoi(buf), &lMsgSize);
					CUT_MapFileDataSource	ds(0, lMsgSize,NULL);
					if ((rt = pop.SaveMsg(_ttoi(buf),ds)) == CUT_SUCCESS)
					{
						if ((rt = theMessage.LoadMessage(ds))== CUT_SUCCESS)
						{
							// lets parse the mail headers
							// FROM
							theMessage.GetHeaderByType (UTM_FROM,buf,sizeof(buf)/sizeof(_TCHAR)-1);
							SetDlgItemText(hwnd,IDC_POP3_FROM,buf);
							// TO
							theMessage.GetHeaderByType (UTM_TO,buf,sizeof(buf)/sizeof(_TCHAR)-1);
							SetDlgItemText(hwnd,IDC_POP3_TO,buf);
							// SUBJECT
							theMessage.GetHeaderByType (UTM_SUBJECT,buf,sizeof(buf)/sizeof(_TCHAR)-1);
							SetDlgItemText(hwnd,IDC_POP3_SUBJECT,buf);
							//Carbon Copy
							theMessage.GetHeaderByType (UTM_CC,buf,sizeof(buf)/sizeof(_TCHAR)-1);
							SetDlgItemText(hwnd,IDC_POP3_CC,buf);
							
							// Message Body
							_TCHAR *szBody = new _TCHAR[MAX_PATH];
							size_t size;
							int result = theMessage.GetMessageBody(szBody, MAX_PATH, &size);
							if(result == UTE_SUCCESS) {
								SetDlgItemText(hwnd,IDC_MESSAGE,szBody);
							}
							else {
								if(result == UTE_BUFFER_TOO_SHORT) {
									delete [] szBody;
									szBody = new _TCHAR[size];
									theMessage.GetMessageBody(szBody, size, &size);
									SetDlgItemText(hwnd,IDC_MESSAGE,szBody);
								}
							}
							delete [] szBody;
							
							// Show Attachment information 
							SetDlgItemInt(hwnd,IDC_NUM_ATTACH,theMessage.GetAttachmentNumber (),FALSE);
							// if we do have attachments lets add them to the combobox so the user
							// can select them and save each if he/she wishes to a disk file
							HWND hWnndsaveBtn = GetDlgItem(hwnd,IDC_SAVE_ATTACH);
							if (theMessage.GetAttachmentNumber () > 0)
							{								
								for (int loop = 0 ; loop < theMessage.GetAttachmentNumber ();loop ++)
								{
									// 
									theMessage.GetAttachmentInfo (loop,buf,sizeof(buf)/sizeof(_TCHAR)-1, type,sizeof(type)-1);
                                    if(_tcslen(buf) == 0)
                                        _tcscpy(buf, _T("Attachment without name"));
									SendMessage (hWndCombo,CB_ADDSTRING, 0,(LONG)(ULONG_PTR)(LPSTR) buf);
								}
								//enable the save attachment button
								EnableWindow(  hWnndsaveBtn,     // handle to window
									TRUE   // flag for enabling or disabling input
									);
								
							}
							else
							{
								// disable the SaveAttachment button
								EnableWindow(  hWnndsaveBtn,     // handle to window
									FALSE   // flag for enabling or disabling input
									);
								
							}
						}
						else{
							MessageBox(NULL, CUT_ERR::GetErrorString(rt), _T("ERROR"), MB_OK);
						}
					}
					else
					{
						MessageBox(NULL, CUT_ERR::GetErrorString(rt), _T("ERROR"), MB_OK);
					}

					pop.CloseMsg();
					LoadCursor(NULL, IDC_ARROW);
					return 1;
				}
			case IDC_DELETE:
				{
					_TCHAR buf[32];
					GetDlgItemText(hwnd,IDC_MSGNUM,buf,sizeof(buf)/sizeof(_TCHAR));
					if(_tcslen(buf) <1)
						MessageBox(hwnd,_T("Invalid Message Number"),_T("Warning"),MB_OK);
					if(pop.DeleteMsg(_ttoi(buf)) != CUT_SUCCESS)
					{
						MessageBox(hwnd,_T("Invalid Message Number"),_T("Warning"),MB_OK);
					}
					else
						MessageBox(hwnd,_T("Message Deleted"),_T("Finished"),MB_OK);
					return 1;
				}
				// The user clicks on the attachment combo box
			case IDC_SAVE_ATTACH:
				{
					WORD wIndex = 0;
					wIndex = (WORD) SendMessage (hWndCombo, CB_GETCURSEL, 0, 0L);
					if (wIndex == CB_ERR)
						MessageBox(hwnd, _T("No Selection. Please select an item in the drop down combo then press this button again."), NULL, MB_OK);
					else{
						
						// Save the attachment (the currently selected item in the combo)
						// to the disk.
						
						SaveAttachment(hwnd, theMessage, wIndex);
					}
					return 1;
				}
			}
		}
		return 1;
	}
	return 0;
}

/***************************************************************
  To show the progress of a message you simply over ride the 
  On send mail progress.
  As demonstrated below

  To cancel the send you simply return FALSE
***************************************************************/
BOOL testSMTP::OnSendMailProgress(long bytesSent,long totalBytes)
{
	HBRUSH	hBlueBrush;
	HWND		hwnd;
	HWND		hwndStatus;
	HDC			hdc;
	RECT		rect;
	
	float		fPercentComplete;
	// Since this example was designed to be compiler independent 
	// we are not going to use a progress control such as the CProgressCtrl  
	// provided with MFC 
	// So lets make the static control look like a progress bar ;-)
	
	hwnd = GetDlgItem(g_hwnd,IDC_PROGRESS);
	hwndStatus = GetDlgItem(g_hwnd,IDC_STATUS);
	
	hdc = GetDC(hwnd);
	GetClientRect(hwnd,&rect);
	
	// the calculation here may not be perfect 
	fPercentComplete = (float)bytesSent / (float)totalBytes;
	
	int right = rect.left + (int)((float)(rect.right - rect.left)* fPercentComplete);
    if(right < rect.right)
        rect.right = right;
	
	hBlueBrush = CreateSolidBrush(RGB(0,0,255));
	FillRect(hdc,&rect, hBlueBrush);
	SetWindowText(hwndStatus,_T("Sending"));
	
	DeleteObject(hBlueBrush);
	ReleaseDC(hwnd,hdc);
	
	return TRUE;  // if you want to cancel the mail send command simply return FALSE
}

/*******************************************
********************************************/
BOOL CALLBACK ATTACHDlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */)
{
	switch(message)
	{
	case WM_INITDIALOG:
		{
			// reinitialize the file name to null
			szFileAtt[0] = 0;
			return 1;
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
					// add the new file name to the field 
					GetDlgItemText(hwnd, IDC_ATTACH_ADD, szFileAtt, sizeof(szFileAtt));
					EndDialog(hwnd,0);
					return 1;
				}
			case IDC_ADD_BROWSE:
				{
					OPENFILENAME ofn;
					
					_TCHAR szFileName[MAX_PATH + 1] = _T(" ");
					_TCHAR szFileTitle[MAX_PATH + 1] = _T(" ");

					ofn.lStructSize       = sizeof(OPENFILENAME); 
					ofn.hwndOwner         = hwnd; 
					ofn.hInstance         = GetModuleHandle(NULL); 
					ofn.lpstrFilter       = _T("All Files (*.*)\0*.*\0\0"); 
					ofn.lpstrCustomFilter = (LPTSTR) NULL; 
					ofn.nMaxCustFilter    = 0L; 
					ofn.nFilterIndex      = 1L; 
					ofn.lpstrFile         = szFileName; 
					ofn.nMaxFile          = sizeof(szFileName); 
					ofn.lpstrFileTitle    = szFileTitle; 
					ofn.nMaxFileTitle     = MAX_PATH; 
					ofn.lpstrInitialDir   = NULL; 
					ofn.lpstrTitle        = __T("Select a file to attach..."); 
					ofn.nFileOffset       = 0;
					ofn.nFileExtension    = 0; 
					ofn.lpstrDefExt       = NULL;
					ofn.lCustData         = 0;  
					ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | 
						OFN_EXPLORER | OFN_LONGNAMES;  

					if (GetOpenFileName(&ofn)) {
				
						// set the file name and move the focus to the "Add"
						// button
						SetDlgItemText(hwnd, IDC_ATTACH_ADD, szFileName);
						SetFocus(GetDlgItem(hwnd, ID_ADD));
					}
				}
				break;
			case IDCANCEL:
				{
					szFileAtt[0] = NULL;
					EndDialog(hwnd,0);
					return 1;
				}
			}return 1;
		}
	}
	return 0;
}


int SaveAttachment(HWND hwnd, CUT_Msg& theMessage, int iIndex)
{
	OPENFILENAME ofn;
	
	_TCHAR szAttachmentName[MAX_PATH + 1];
	_TCHAR szAttachmentType[MAX_PATH + 1];
	_TCHAR szFileTitle[MAX_PATH + 1];
	
	theMessage.GetAttachmentInfo(iIndex, szAttachmentName, MAX_PATH, 
		szAttachmentType, MAX_PATH, NULL);
	
	ofn.lStructSize       = sizeof(OPENFILENAME); 
	ofn.hwndOwner         = hwnd; 
	ofn.hInstance         = GetModuleHandle(NULL); 
	ofn.lpstrFilter       = _T("All Files (*.*)\0*.*\0\0"); 
	ofn.lpstrCustomFilter = (LPTSTR) NULL; 
	ofn.nMaxCustFilter    = 0L; 
	ofn.nFilterIndex      = 1L; 
	ofn.lpstrFile         = szAttachmentName; 
	ofn.nMaxFile          = sizeof(szAttachmentName); 
	ofn.lpstrFileTitle    = szFileTitle; 
	ofn.nMaxFileTitle     = MAX_PATH; 
	ofn.lpstrInitialDir   = NULL; 
	ofn.lpstrTitle        = __T("Save attachment as..."); 
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0; 
	ofn.lpstrDefExt       = NULL;
	ofn.lCustData         = 0;  
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | 
		OFN_EXPLORER | OFN_LONGNAMES;  
	
	int result = GetSaveFileName(&ofn);
	if (result == IDOK) {
		
		theMessage.Decode(iIndex, szAttachmentName);
	}
	
	return result;

}

#pragma warning ( pop )