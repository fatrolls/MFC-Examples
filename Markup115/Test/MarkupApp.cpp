// MarkupApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MarkupApp.h"
#include "MarkupDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupApp

BEGIN_MESSAGE_MAP(CMarkupApp, CWinApp)
	//{{AFX_MSG_MAP(CMarkupApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupApp construction

CMarkupApp::CMarkupApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMarkupApp object

CMarkupApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMarkupApp initialization

class CCustomCommandLineInfo : public CCommandLineInfo
{
public:
	CCustomCommandLineInfo() { m_bAutoExit = FALSE; };
	virtual void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
	{
		if (bFlag && _tcsicmp(pszParam,_T("autoexit")) == 0 )
			m_bAutoExit = TRUE;
		else
			CCommandLineInfo::ParseParam(pszParam,bFlag,bLast);
	};
	int m_bAutoExit;
};

BOOL CMarkupApp::InitInstance()
{
	// Standard initialization

#if _MFC_VER < 0x0700
	// Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Parse command line
	CCustomCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("First Objective Software"));

	CMarkupDlg dlg;
	dlg.m_bAutoExit = cmdInfo.m_bAutoExit;
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
