// -----------------------------------------------------------------------------
// AudioDialog.cpp : Defines the class behaviors for the application.
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "AudioDialog.h"
#include "AudioDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// -----------------------------------------------------------------------------
// CAudioDialogApp

BEGIN_MESSAGE_MAP(CAudioDialogApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
// CAudioDialogApp construction
CAudioDialogApp::CAudioDialogApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// -----------------------------------------------------------------------------
// The one and only CAudioDialogApp object

CAudioDialogApp theApp;


// -----------------------------------------------------------------------------
// CAudioDialogApp initialization
BOOL CAudioDialogApp::InitInstance()
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
	SetRegistryKey(_T("Peter C. Studt"));

	CAudioDialogDlg dlg;
	//CMixerDialog dlg;
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

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
// -----------------------------------------------------------------------------
