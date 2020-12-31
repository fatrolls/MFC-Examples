// ===================================================================
// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
// ===================================================================
// ==============
// ABOUT This sample:
//	1 - In this sample program we first set the CallBack functions
//		SetCallBacks()
//		The Service Control Handler function ServiceCtrlHandler() (Internal to the class)
//		will dispatch each request comming to the service
//		from the SCM to the default or 	user defined
//		functions set by this function for the the following 
//		notifications
//				SERVICE_CONTROL_STOP
//				SERVICE_CONTROL_PAUSE
//				SERVICE_CONTROL_CONTINUE
//		There are several cases in which you may want to provide
//		your own implementation of these function. One of these cases is 
//		writing to your service's custom log to inform you of who started,
//		paused or stoped the service.
//	2 - check for the Command argument parameters
//		(m) will start the service manually
//		(i) will install the service in the SCM 
//				Creates a service object and adds it to 
//				the service control manager database
//		(u) will uninstall the service form the the SCM database
//				Opens up the SCM database and locate the requested 
//				service then Marks the specified service for deletion
//				from the service control manager database
// =========
// * RUNNING this sample with  the NET command utility
// -To start this program as a service copy the test.exe to the winnt\system32 directory
//  then from the command line excute the following command
//		D:\WINNT\system32>test i
//		D:\WINNT\system32>net start CUS_Test
// By now you should be able to hear the computer Beeping
// -To stop the service issue the foolowing command
//		D:\WINNT\system32>net stop CUS_Test
// you will be nswered with the following 
//	The CUS_Test service is stopping.
//	The CUS_Test service was stopped successfully.
// -To remove the service from the SCM dtatabase issue the following command
// D:\WINNT\system32>test u
// 
// ===========
// * You also can start and stop a service by using the service applet from the CONTROL PANEL

// ====================================================================================
#include <windows.h>
#include <tchar.h>

#include "test.h"
#include "resource.h"
#include "c_servic.h"

// Suppress warnings for non-safe str fns. Transitional, for VC6 support.
#pragma warning (push)
#pragma warning (disable : 4996)

//global variables - which make communicating between
// the service class and the main pargram easier
HINSTANCE	g_hInst;
HWND		g_hwnd = NULL;

/******************************************************
*******************************************************/
int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE ,LPSTR ,int ){

	CUService	service;
	int			startAsService = TRUE;
	int 		loop  = 0;
	_TCHAR 		param = 0;
	_TCHAR		path[256];

	g_hInst = 	hInstance;


	//setup the service class callback functions
	service.SetCallBacks(NULL,NULL,StopFunction);

	//get the program path
	_tcscpy(path,GetCommandLine());
	
	//get the command line param
	while(path[loop] != 0){
		if(path[loop] == ' '){
			path[loop] = 0;
			param = path[loop+1];
			break;
		}
		loop++;
	}

	//manual program launch - do not try and start as a service
	if(param==_T('m') || param==_T('M')){
		startAsService = FALSE;
	}

	//service installation
	else if(param==_T('i') || param==_T('I')){
		if( service.InstallService(_T("CUS_Test"),_T("CUS_Test"),path) != 0)
			MessageBox(NULL,_T("Service Failed To Install"),_T("Error"),MB_OK);
		return 1;
	}

	//service un-install
	else if(param==_T('u') || param==_T('U')){
		if( service.RemoveService(_T("CUS_Test")) != 0)
			MessageBox(NULL,_T("Service Failed To Install"),_T("Error"),MB_OK);
		return 1;
	}

	//init the service with the SCM, if the program is to be started as
	//a service
	if(startAsService){
		if(service.InitService(_T("CUS_Test"),EntryFunction)!= TRUE){
			//if the service control manager failed then try and
			//start the program manually
			MessageBox(NULL,_T("Program Starting In Interactive Mode"),_T("Startup Message"),MB_OK);
			EntryFunction(NULL);
		}
	}

	//just call the programs main entry point, if it is not to start as
	//a service
	else{
			EntryFunction(NULL);
	}

	return 0;
}
/******************************************************
*******************************************************/
void EntryFunction(void *){

	//create modal dialog box
	DialogBox(g_hInst,MAKEINTRESOURCE(IDD_DIALOG1),NULL,(DLGPROC) DlgProc);
	// v4.2 changed - was -1.
	MessageBeep(0xFFFFFFFF);
	MessageBeep(0xFFFFFFFF);
	MessageBeep(0xFFFFFFFF);
	MessageBeep(0xFFFFFFFF);
	MessageBeep(0xFFFFFFFF);
}

/******************************************************
*******************************************************/
void StopFunction(void *){

	SendMessage(g_hwnd,WM_CLOSE,0,0);
}

/******************************************************
*******************************************************/
long CALLBACK DlgProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM){

	switch(message){

		case WM_INITDIALOG:{
			g_hwnd = hwnd;

			SetTimer(hwnd,123,500,NULL);

			return 1;
		}
		case WM_DESTROY:{
			g_hwnd = NULL;
			KillTimer(hwnd,123);

			return 1;
		}
		case WM_CLOSE:{
			EndDialog(hwnd,0);
			return 1;
		}
		case WM_TIMER:{
			// v4.2 changed this from -1
			MessageBeep(0xFFFFFFFF);
			return 0;
		}
		case WM_COMMAND:{
			switch(LOWORD(wParam)){
				case ID_OK:{
					EndDialog(hwnd,0);
				}
			}
		}
	}
	return 0;
}

#pragma warning (pop)