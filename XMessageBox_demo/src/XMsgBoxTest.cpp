// XMsgBoxTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "XMsgBoxTest.h"
#include "XMsgBoxTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXsgBoxTestApp

BEGIN_MESSAGE_MAP(CXsgBoxTestApp, CWinApp)
	//{{AFX_MSG_MAP(CXsgBoxTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXsgBoxTestApp construction

CXsgBoxTestApp::CXsgBoxTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CXsgBoxTestApp object

CXsgBoxTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CXsgBoxTestApp initialization

BOOL CXsgBoxTestApp::InitInstance()
{
	TRACE(_T("_MSC_VER=%d  _MFC_VER=0x%X  WINVER=0x%X  _WIN32_WINNT=0x%X  _WIN32_IE=0x%X\n"),
		_MSC_VER, _MFC_VER, WINVER, _WIN32_WINNT, _WIN32_IE);

#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CXMsgBoxTestDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}

void CXsgBoxTestApp::OnHelp()
{
	TRACE(_T("in CXsgBoxTestApp::OnHelp\n"));
	TRACE(_T("   m_dwPromptContext=%d\n"), m_dwPromptContext);
	CWinApp::OnHelp();
}
