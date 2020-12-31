// DialogGL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DialogGL.h"
#include "DialogGLDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogGLApp

BEGIN_MESSAGE_MAP(CDialogGLApp, CWinApp)
	//{{AFX_MSG_MAP(CDialogGLApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogGLApp construction

CDialogGLApp::CDialogGLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDialogGLApp object

CDialogGLApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDialogGLApp initialization

BOOL CDialogGLApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDialogGLDlg dlg;
	m_pMainWnd = &dlg;
	m_pMainWnd->DragAcceptFiles(TRUE);
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


BOOL CDialogGLApp::OnIdle(LONG lCount)
{
	// CG: The following code inserted by 'Idle Time Processing' component.

	// Note: Do not perform lengthy tasks during OnIdle because your
	// application cannot process user input until OnIdle returns.

	// call the base class
	BOOL bBaseIdle = CWinApp::OnIdle(lCount);

	BOOL bMoreIdle = TRUE;
	if (lCount == 0)
	{
	CDialogGLDlg *pDlg;
	pDlg = (CDialogGLDlg *)m_pMainWnd;
	pDlg->Rotate();
	}
	else if (lCount == 100)
	{
		// TODO: add code to perform less important tasks during idle
	}
	else if (lCount == 1000)
	{
		// TODO: add code to perform occasional tasks during idle
		bMoreIdle = bBaseIdle;
	}

	// return FALSE when there is no more idle processing to do
	return bMoreIdle;
}

CDocument* CDialogGLApp::OpenDocumentFile(LPCTSTR lpszFileName) 
{
	CDialogGLDlg *pDlg;
	pDlg = (CDialogGLDlg *)m_pMainWnd;
	pDlg->ReadTexture((char *)lpszFileName);
	return CWinApp::OpenDocumentFile(lpszFileName);
}
