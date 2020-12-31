// XHtmlTreeTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XHtmlTreeTest.h"
#include "MainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXHtmlTreeTest

BEGIN_MESSAGE_MAP(CXHtmlTreeTest, CWinApp)
	//{{AFX_MSG_MAP(CXHtmlTreeTest)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXHtmlTreeTest construction

CXHtmlTreeTest::CXHtmlTreeTest()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXHtmlTreeTest object

CXHtmlTreeTest theApp;

/////////////////////////////////////////////////////////////////////////////
// CXHtmlTreeTest initialization

BOOL CXHtmlTreeTest::InitInstance()
{
#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CMainDialog dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
