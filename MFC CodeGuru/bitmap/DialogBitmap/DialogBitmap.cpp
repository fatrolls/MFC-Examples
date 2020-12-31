// DialogBitmap.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DialogBitmap.h"
#include "DialogBitmapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapApp

BEGIN_MESSAGE_MAP(CDialogBitmapApp, CWinApp)
	//{{AFX_MSG_MAP(CDialogBitmapApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapApp construction

CDialogBitmapApp::CDialogBitmapApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDialogBitmapApp object

CDialogBitmapApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDialogBitmapApp initialization

BOOL CDialogBitmapApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDialogBitmapDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
