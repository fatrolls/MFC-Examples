// XEditPromptTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XEditPromptTest.h"
#include "XEditPromptTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestApp

BEGIN_MESSAGE_MAP(CXEditPromptTestApp, CWinApp)
	//{{AFX_MSG_MAP(CXEditPromptTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestApp construction

CXEditPromptTestApp::CXEditPromptTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXEditPromptTestApp object

CXEditPromptTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestApp initialization

BOOL CXEditPromptTestApp::InitInstance()
{
#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CXEditPromptTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
