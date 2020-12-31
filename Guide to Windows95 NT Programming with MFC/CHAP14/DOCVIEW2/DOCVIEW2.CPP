///////////////////////////////////////////////////////////////////
// Header  : DOCVIEW2.CPP
//
// Purpose : Defines the class behaviors for the application.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"      // Standard include
#include "DocView2.h"    // Application
#include "MainFrm.h"     // Frame Window
#include "DV_Doc.h"      // Document
#include "DV_View.h"     // View

///////////////////////////////////////////////////////////////////
// CDocView2App initialization

BOOL CDocView2App::InitInstance()
{
	//
   // Register the application's document template
	//
   CSingleDocTemplate* pDocTemplate;
	
   pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDocView2Doc),
		RUNTIME_CLASS(CMainFrame),      // main SDI frame window
		RUNTIME_CLASS(CDocView2View));

	AddDocTemplate(pDocTemplate);
                           
	// Parse command line (this is required by doc/view)
   CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

   // Make the frame window 640 x 480 pixels
   ASSERT_VALID(this->m_pMainWnd);
   this->m_pMainWnd->SetWindowPos(0, 0, 0, 640, 480, SWP_SHOWWINDOW);

	return TRUE;
}

///////////////////////////////////////////////////////////////////
// CDocView2App construction/destruction

CDocView2App::CDocView2App()
{
}

CDocView2App::~CDocView2App()
{
} 

///////////////////////////////////////////////////////////////////
// Declare and initialize the sole CDocView2App object

CDocView2App MyApp;
