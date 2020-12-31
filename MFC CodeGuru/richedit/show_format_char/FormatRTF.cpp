// FormatRTF.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FormatRTF.h"
#include "LRTFCtrl.h"
#include "FormatRTFDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFApp

BEGIN_MESSAGE_MAP(CFormatRTFApp, CWinApp)
	//{{AFX_MSG_MAP(CFormatRTFApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFApp construction

CFormatRTFApp::CFormatRTFApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFormatRTFApp object

CFormatRTFApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFormatRTFApp initialization

BOOL CFormatRTFApp::InitInstance()
{
	// Standard initialization

	CFormatRTFDlg dlg;
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
