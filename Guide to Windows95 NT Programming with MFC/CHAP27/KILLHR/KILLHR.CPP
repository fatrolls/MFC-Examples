// KillHR.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "KillHR.h"
#include "KillHRDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKillHRApp

BEGIN_MESSAGE_MAP(CKillHRApp, CWinApp)
	//{{AFX_MSG_MAP(CKillHRApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKillHRApp construction

CKillHRApp::CKillHRApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CKillHRApp object

CKillHRApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CKillHRApp initialization

BOOL CKillHRApp::InitInstance()
{
	CKillHRDlg dlg;
	m_pMainWnd = &dlg;
	
   dlg.DoModal();
   
   return FALSE;
}
