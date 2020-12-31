///////////////////////////////////////////////////////////////////
//  Module   : WIZARD1.CPP
//
//  Purpose  : Implementation of a Windows 95 Wizard in MFC.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "wizard1.h"

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd();

   // Initialize the frame window
   pFrame->LoadFrame(IDR_MAINFRAME, 
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   // Show the frame window, centered
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
