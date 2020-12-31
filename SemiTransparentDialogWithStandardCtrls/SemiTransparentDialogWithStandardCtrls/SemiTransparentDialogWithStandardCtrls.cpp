
// SemiTransparentDialogWithStandardCtrls.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SemiTransparentDialogWithStandardCtrls.h"
#include "SemiTransparentDialogWithStandardCtrlsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSemiTransparentDialogWithStandardCtrlsApp

BEGIN_MESSAGE_MAP(CSemiTransparentDialogWithStandardCtrlsApp, CWinApp)
END_MESSAGE_MAP()


// CSemiTransparentDialogWithStandardCtrlsApp construction

CSemiTransparentDialogWithStandardCtrlsApp::CSemiTransparentDialogWithStandardCtrlsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CSemiTransparentDialogWithStandardCtrlsApp object

CSemiTransparentDialogWithStandardCtrlsApp theApp;


// CSemiTransparentDialogWithStandardCtrlsApp initialization

BOOL CSemiTransparentDialogWithStandardCtrlsApp::InitInstance()
{
	::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,TRUE,NULL,0);

	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	CSemiTransparentDialogWithStandardCtrlsDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
