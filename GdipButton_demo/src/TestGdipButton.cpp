// TestGdipButton.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TestGdipButton.h"
#include "TestGdipButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonApp

BEGIN_MESSAGE_MAP(CTestGdipButtonApp, CWinApp)
	//{{AFX_MSG_MAP(CTestGdipButtonApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonApp construction

CTestGdipButtonApp::CTestGdipButtonApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTestGdipButtonApp object

CTestGdipButtonApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonApp initialization

BOOL CTestGdipButtonApp::InitInstance()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

#if _MFC_VER < 0x700
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	CTestGdipButtonDlg dlg;
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

int CTestGdipButtonApp::ExitInstance() 
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	
	return CWinApp::ExitInstance();
}
