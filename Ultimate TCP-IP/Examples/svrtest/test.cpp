/*******************************************
Ultimate History/Logger Test Program
********************************************/

//MFC Users - include the following
#include "stdafx.h"
//OWL Users - include the following
//#include <owl\owlpch.h>
//SDK Users - include the following

#include "test.h"
#include "resource.h"

#include "uh_ctrl.h"
#include "ut_clnt.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)


_TCHAR g_address[32] = _T("");
long g_interval = 100;

int  g_port = 0;
_TCHAR g_send[512];

int  g_threadStop;

long g_count;
long g_badcount;


/*******************************************
********************************************/
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int){

	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);

	//create modal dialog box
	DialogBox(hInstance,_T("DIALOG_1"),NULL,(DLGPROC)DlgProc);

	return 0;
}
/*******************************************
********************************************/
long CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM /* lParam */){

	static CUH_Control control;
	static HFONT hFont;
	

	switch(message){

		case WM_INITDIALOG:{

			//attach the history window to the control
			control.AttachHistoryWindow(hwnd,IDC_HISTORY);
			control.SetHistoryLength(50);

			hFont = CreateFont(12,0,0,0,500,0,0,0,0,0,0,0,0,_T("Courier New"));
			control.SetFont(hFont);

			//setup the dlg items
			SetDlgItemText(hwnd,IDC_ADDRESS,_T("127.0.0.1"));
			SetDlgItemText(hwnd,IDC_PORT,_T("80"));
			SetDlgItemText(hwnd,IDC_INTERVAL,_T("500"));

			return 1;
		}
		case WM_NCDESTROY:{
			DeleteObject(hFont);
			return 0;
		}
		case WM_COMMAND:{

			switch(LOWORD(wParam)){

				case IDC_START:{		
					_TCHAR buf[MAX_PATH];

					GetDlgItemText(hwnd,IDC_SEND,g_send,sizeof(g_send)/sizeof(TCHAR));
					
					GetDlgItemText(hwnd,IDC_ADDRESS,buf,MAX_PATH);
					CUT_WSClient wsc;
					if(wsc.IsIPAddress(buf) == FALSE){					
						if( wsc.GetAddressFromName(buf,g_address,sizeof(g_address)/sizeof(_TCHAR)) != CUT_SUCCESS){
							MessageBox(hwnd,_T("Could not resolve the given address"),_T("Error"),MB_OK);
							return 1;
						}
					}
					else
						CUT_Str::tcscpy(g_address,sizeof(g_address)/sizeof(_TCHAR), buf);

					GetDlgItemText(hwnd,IDC_INTERVAL,buf,MAX_PATH);
					g_interval = _ttol(buf);
					GetDlgItemText(hwnd,IDC_PORT,buf,MAX_PATH);
					g_port = _ttoi(buf);

					g_threadStop = FALSE;
					if(_beginthread(LoopThread,0,(VOID *)&control) == (DWORD)-1){
						MessageBox(hwnd,_T("Thread Start Error"),_T("Error"),MB_OK);
					}
					return 1;
				}
				case IDC_STOP:{		
					g_threadStop = TRUE;
					return 1;
				}
				case IDC_EXIT:{
					EndDialog(hwnd,0);
					return 1;
				}
			}
			return 0;
		}
		case WM_CLOSE:{
			EndDialog(hwnd,0);
			return 1;
		}
	}
	return 0;
}
void LoopThread(void * _this){
	
	CUH_Control *control = (CUH_Control*)_this;
	_TCHAR buf[64];

    while(g_threadStop == FALSE){

		if(_beginthread(ConnectThread,0,(VOID *)control) == (DWORD)-1){
			control->AddLine(_T("New Thread Failed"));
 			g_badcount++;
		}
		else{
			_sntprintf(buf, 64,_T("Connect Number: %ld"),g_count);
			control->AddLine(buf);
		}
		g_count++;
		if(g_interval <1000){
			Sleep(g_interval);
		}
		else{
			long secs = g_interval / 1000;
			long mSecs = g_interval % 1000;
			for(long loop = 0; loop <secs;loop++){
				Sleep(1000);
				if(g_threadStop == FALSE)
					break;
			}
			Sleep(mSecs);
		}
	}

	_endthread();
}

void ConnectThread(void * _this){

	CUH_Control *control = (CUH_Control*)_this;
	CUT_WSClient wsc; 
	char buf[256];

	//connect
	if(wsc.Connect(g_port,g_address) != CUT_SUCCESS){
		control->AddLine("Connect Failed");
	}
	else{
		// v4.2 Using AC() here - should consider overload
		wsc.Send(AC(g_send));
	}
	while(wsc.Receive(buf,sizeof(buf)/sizeof(char)) >0){
	}
	wsc.CloseConnection();

	
	_endthread();
}

#pragma warning ( pop )