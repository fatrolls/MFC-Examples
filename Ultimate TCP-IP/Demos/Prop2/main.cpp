// =================================================================
// Ultimate TCP-IP v4.2
// Copyright (C) The Ultimate Toolbox 1995-2007, all rights reserverd
// =================================================================


#include "stdafx.h"
#include "commdlg.h"
#include "UCPropertySheet.h"
#include "UCVTable.h"
#include "UCWnd.h"
#include "UT_DNSPage.h"
#include "UT_Finger.h"
#include "UT_PingPage.h"
#include "About.h"
//#include "UT_VrfyEmail.h"
#include "UT_WhoIs.h"
#include "UT_TracePage.h"

// ==========================================
// Global section

HINSTANCE				g_hInstance;  // incase we need one latter


CUCPropertySheet		*sheet; // the mother sheet
CUT_DNSPage				*g_dns;		// a page to display the DNS demo
CUT_FingerPage			*g_finger;	// a page to display the Finger demo
CUT_PingPage			*g_Ping;	// a page to display the Ping demo
//CUT_VrfyEmail			*g_vrfyEmail;// a page to display the Verify Email demo
CUT_WhoIsPage			*g_WhoIs;
CUT_TracePage			*g_Trace;
About					*g_About;
DWORD					nTimerID;

// ==========================================
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL InitInstance(HINSTANCE hInstance, int /* nCmdShow */)
{

	// Register the history window
	//register the history control (if it is going to be used in a dialog)
	CUH_Control::RegisterWindowClass(hInstance);

	
	// Create the mother of all pages (sheet)
	// this will be based on the IDD_DIALOG1 from the resource
	sheet	=	new CUCPropertySheet(NULL,hInstance);
	// create each page 
	g_dns	=	new CUT_DNSPage(_T("DNS Lookup (Domain servers)"));
	g_finger=	new CUT_FingerPage(_T("Finger (Who is logged on?)"));
	g_Ping	=	new CUT_PingPage(_T("Ping (is it alive?)"));
	//g_vrfyEmail = new CUT_VrfyEmail (_T("VerifyEmail"));
	g_WhoIs		= new CUT_WhoIsPage (_T("Who Is? (Domain Contacts)"));
	g_About		= new About(_T("Contacting The Ultimate Toolbox"));

	g_Trace  = new CUT_TracePage (_T("Trace Route (Show network path)"));
	// Add each page to the sheet
	sheet->AddPage(g_dns);
	sheet->AddPage(g_WhoIs);
	sheet->AddPage(g_finger);
	sheet->AddPage(g_Ping);
	sheet->AddPage(g_Trace);
	sheet-> AddPage(g_About);
	//sheet->AddPage (g_vrfyEmail);

	return TRUE;
}
BOOL CALLBACK AboutProc(HWND hwndDlg, UINT message, WPARAM /* wParam */, LPARAM /* lParam */)
{
	switch (message) {
        case WM_INITDIALOG:
            // If in splash mode - start timer & remove Ok button
                nTimerID = (DWORD) SetTimer(hwndDlg, 1, 2000, NULL);
            break;
        case WM_TIMER:
		case WM_CLOSE:
			EndDialog(hwndDlg, IDOK);
			break;

        case WM_DESTROY:
            // Destroy timer
            if(nTimerID != 0) {
                KillTimer(hwndDlg, nTimerID);
                nTimerID = 0;
                }
            break;
	    }

	return 0;
}

// ==========================================
// The main routine for this application
int CALLBACK WinMain(
					 HINSTANCE hInstance,
					 HINSTANCE /* hPrevInstance */,
					 LPSTR /* lpCmdLine */,
					 int nCmdShow)
{
	// Perform initializations that apply to a specific instance 
	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);
	
	g_hInstance = hInstance ;  // in case we need one later

	// IDD_SPLASH
	//AboutProc 
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_SPLASH), NULL, AboutProc);
	// Create our sheet and display the dialog
	sheet->Create(_T("Ultimate TCP/IP 2005 Internet Tools Demo (The Ultimate Toolbox) "),NULL);
	delete g_dns;
	delete g_finger;
	//delete g_vrfyEmail;
	delete g_Ping;
	delete sheet;
	delete g_WhoIs;
	delete g_Trace;
	delete g_About;

	return 0;
}
