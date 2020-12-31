// SecureChatClient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SecureChatClient.h"
#include "SecureChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientApp

BEGIN_MESSAGE_MAP(CSecureChatClientApp, CWinApp)
	//{{AFX_MSG_MAP(CSecureChatClientApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientApp construction

CSecureChatClientApp::CSecureChatClientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSecureChatClientApp object

CSecureChatClientApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientApp initialization

BOOL CSecureChatClientApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//
// Load The accelerator 
//

	m_haccel=LoadAccelerators(AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDR_ACCELERATOR1));
	


	CSecureChatClientDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
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

BOOL CSecureChatClientApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	// If we have an accelerator and a key is pressed down let the dialog hanlde it. 
	if( m_haccel && (WM_KEYFIRST <= lpMsg->message && lpMsg->message<= WM_KEYLAST))
    {
        if (::TranslateAccelerator(m_pMainWnd->m_hWnd, m_haccel, lpMsg)) 
            return(TRUE);
    }	
	return CWinApp::ProcessMessageFilter(code, lpMsg);
}
