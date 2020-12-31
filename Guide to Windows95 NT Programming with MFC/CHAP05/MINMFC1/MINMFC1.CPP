/////////////////////////////////////////////////////////////////////////////
// Module   : MINMFC1.CPP
//
// Purpose  : Implementation of a minimal MFC program.
//
// Comments : This program does absolutely nothing useful...
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 02-23-96
/////////////////////////////////////////////////////////////////////////////

#include <afxwin.h>  // MFC core and standard components

// Derive an application class 
class CMinApp : public CWinApp
   { public: virtual BOOL InitInstance(); };

/////////////////////////////////////////////////////////////////////////////
// CMinApp::InitInstance - overrides virtual CWinApp::InitInstance

BOOL CMinApp::InitInstance()
{
   // Allocate a new frame window object
   CFrameWnd* pFrame = new CFrameWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("A Minimal MFC Program"));

   // Show the frame window maximized
   pFrame->ShowWindow(SW_SHOWMAXIMIZED);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   AfxGetApp()->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CMinApp MyApp;

/////////////////////////////////////////////////////////////////////////////
