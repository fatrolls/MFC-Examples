// MinDialog.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MinDialog.h"
#include "MinDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMinDialogApp

BEGIN_MESSAGE_MAP(CMinDialogApp, CWinApp)
	//{{AFX_MSG_MAP(CMinDialogApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMinDialogApp construction

CMinDialogApp::CMinDialogApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMinDialogApp object

CMinDialogApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMinDialogApp initialization

BOOL CMinDialogApp::InitInstance()
{
#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CMinDialogDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
