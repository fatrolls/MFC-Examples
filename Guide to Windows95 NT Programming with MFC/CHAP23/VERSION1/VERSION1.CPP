///////////////////////////////////////////////////////////////////
// Module   : VERSION1.CPP
//
// Purpose  : Implementation of a minimal MFC program with 
//            version info.
//
// Comments : This program does absolutely nothing useful...
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-23-96
///////////////////////////////////////////////////////////////////

#include <afxwin.h>    // MFC core and standard components
#include "resource.h"  // Resource IDs

// Derive an application class 
class CVersionApp : public CWinApp
{
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// CVersionApp::InitInstance - overrides  CWinApp::InitInstance

BOOL CVersionApp::InitInstance()
{
	// Allocate a new frame window object
	CFrameWnd* pFrame = new CFrameWnd;

	// Initialize the frame window
   pFrame->Create(0, _T("Version Resource Program"));

	// Show the frame window maximized
   pFrame->ShowWindow(SW_SHOWMAXIMIZED);
   pFrame->UpdateWindow();

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CVersionApp MyApp;

/////////////////////////////////////////////////////////////////////////////
