///////////////////////////////////////////////////////////////////
// Module  : DOCVIEW1.CPP
//
// Purpose : Defines the class behaviors for the application.
//
// Author  : Rob McGregor - rob_mcgregor@compuserve.com
//
// Date    : 05-12-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"      // Standard include
#include "DocView1.h"    // Application
#include "MainFrm.h"     // Frame Window
#include "DV_Doc.h"      // Document
#include "DV_View.h"     // View

///////////////////////////////////////////////////////////////////
// CDocView1App construction/destruction

CDocView1App::CDocView1App()
{
}

CDocView1App::~CDocView1App()
{
} 

///////////////////////////////////////////////////////////////////
// CDocView1App initialization

BOOL CDocView1App::InitInstance()
{
	//
   // Register the application's document template
	//
   CSingleDocTemplate* pDocTemplate;
	
   pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDocView1Doc),
		RUNTIME_CLASS(CMainFrame),      // main SDI frame window
		RUNTIME_CLASS(CDocView1View));

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
// Declare and initialize the sole CDocView1App object

CDocView1App MyApp;
