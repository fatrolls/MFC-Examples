// test.cpp : Defines the class behaviors for the application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "Helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestApp

BEGIN_MESSAGE_MAP(CTestApp, CWinApp)
	//{{AFX_MSG_MAP(CTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestApp construction

CTestApp::CTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestApp object

CTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestApp initialization

BOOL CTestApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if (!theHelper.Initialize(_T("PNPMON")))
		{
		OSVERSIONINFO vi = {sizeof(OSVERSIONINFO)};
		if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
			AfxMessageBox(_T("Unable to load the PNPMON.SYS helper driver.\nYou may need to copy this file to the Drivers directory by hand."));
		else
			AfxMessageBox(_T("Unable to load the PNPMON.VXD helper dirver.\nYou may need to copy this file to the System directory by hand."));
		return FALSE;
		}

	CTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
