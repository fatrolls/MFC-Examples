// Saver.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "collect.h"
#include "DlgScrSaver.h"
#include "drawwnd.h"
#include "Saverdlg.h"
#include "saverwnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaverApp

BEGIN_MESSAGE_MAP(CSaverApp, CWinApp)
	//{{AFX_MSG_MAP(CSaverApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

TCHAR szConfig[]=_T("Config");

/////////////////////////////////////////////////////////////////////////////
// CSaverApp construction

CSaverApp::CSaverApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSaverApp object

CSaverApp theApp;

BOOL MatchOption(LPTSTR lpsz, LPTSTR lpszOption)
{
	if (lpsz[0] == '-' || lpsz[0] == '/')
		lpsz++;
	if (lstrcmpi(lpsz, lpszOption) == 0)
		return TRUE;
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CSaverApp initialization

BOOL CSaverApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	SetRegistryKey(_T("Andreas Jaeger"));

	if (__argc == 1 || MatchOption(__argv[1], _T("c")))
		DoConfig();
	else if (MatchOption(__argv[1], _T("p")))
	{
		CWnd* pParent = CWnd::FromHandle((HWND)atol(__argv[2]));
		ASSERT(pParent != NULL);
		CDrawWnd* pWnd = new CDrawWnd();
		CRect rect;
		pParent->GetClientRect(&rect);
		pWnd->Create(NULL, WS_VISIBLE|WS_CHILD, rect, pParent, NULL);
		m_pMainWnd = pWnd;
		return TRUE;
	}
	else if (MatchOption(__argv[1], _T("s")))
	{
		CSaverWnd* pWnd = new CSaverWnd;
		pWnd->Create();
		m_pMainWnd = pWnd;
		return TRUE;
	}
	return FALSE;
}

void CSaverApp::DoConfig()
{
	CSaverDlg dlg;
	dlg.BitmapPath = GetProfileString(szConfig, _T("BitmapPath"), "");
	dlg.m_nSpeed = GetProfileInt(szConfig, _T("Speed"), 100);
	m_pMainWnd = &dlg;
	if (dlg.DoModal() == IDOK)
	{
		WriteProfileString(szConfig, _T("BitmapPath"), dlg.BitmapPath);
		WriteProfileInt(szConfig, _T("Speed"), dlg.m_nSpeed);
	}
}
