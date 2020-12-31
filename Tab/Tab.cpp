// Tab.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Tab.h"
#include "TabDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma data_seg("NUM")
HANDLE g_hMutex = NULL; 
int g_array[10] = {0};
int g_num = 0;
#pragma data_seg()
#pragma comment(linker, "/Section:NUM,RWS")

// CTabApp

BEGIN_MESSAGE_MAP(CTabApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTabApp construction

CTabApp::CTabApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CTabApp object

CTabApp theApp;


// CTabApp initialization

BOOL CTabApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	
	if (g_hMutex == NULL)
		g_hMutex = CreateMutex(NULL, FALSE, "numMutex");

    // Request ownership of mutex.
 
	if (g_num >= 9)
		return FALSE;
	g_num++;
	g_array[g_num] = g_num;
	
	CString str,str2="";
	for (int i = 0; i < g_num; i++)
	{
		str.Format("%d ", g_array[i]);
		str2 += str;
	}
	//AfxMessageBox(str2);

	CTabDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	g_num--;
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
