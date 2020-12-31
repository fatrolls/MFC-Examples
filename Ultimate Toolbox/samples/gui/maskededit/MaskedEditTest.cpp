// MaskedEditTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MaskedEditTest.h"     // CMaskedEditTestApp
#include "MaskedEditTestDlg.h"  // CMaskedEditTestDlg

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestApp

BEGIN_MESSAGE_MAP(CMaskedEditTestApp, CWinApp)
	//{{AFX_MSG_MAP(CMaskedEditTestApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestApp construction

CMaskedEditTestApp::CMaskedEditTestApp()
	{
	}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMaskedEditTestApp object

CMaskedEditTestApp theApp ;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestApp initialization

BOOL CMaskedEditTestApp::InitInstance()
	{
	// Standard initialization
	
	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}


	CMaskedEditTestDlg dlg ;
	/*int nResponse = */dlg.DoModal() ;
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE ;
	}

int CMaskedEditTestApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
