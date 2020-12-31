// XFolderDialogTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XFolderDialogTest.h"
#include "XFolderDialogTestDlg.h"
#include "XTrace.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXFolderDialogTestApp

BEGIN_MESSAGE_MAP(CXFolderDialogTestApp, CWinApp)
	//{{AFX_MSG_MAP(CXFolderDialogTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXFolderDialogTestApp construction

CXFolderDialogTestApp::CXFolderDialogTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXFolderDialogTestApp object

CXFolderDialogTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXFolderDialogTestApp initialization

BOOL CXFolderDialogTestApp::InitInstance()
{
	TRACE(_T("in CXFolderDialogTestApp::InitInstance\n"));

#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	SetRegistryKey(_T("CodeProject"));	// for folder history and view mode

	CXFolderDialogTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
