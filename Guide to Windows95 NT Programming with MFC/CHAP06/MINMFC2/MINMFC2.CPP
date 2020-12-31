/////////////////////////////////////////////////////////////////////////////
// Module   : MINMFC2.CPP
//
// Purpose  : Implementation of a minimal MFC program.
//
// Comments : This program shows the use of a basic message map.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 04-18-96
/////////////////////////////////////////////////////////////////////////////

#include <afxwin.h>  // MFC core and standard components

/////////////////////////////////////////////////////////////////////////////
// Derive an application class 

class CMinApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance(); 
};

/////////////////////////////////////////////////////////////////////////////
// Derive a frame window class

class CMainWnd : public CFrameWnd
{
protected:
   // Message handlers
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);  
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point); 

   DECLARE_MESSAGE_MAP();
};

/////////////////////////////////////////////////////////////////////////////
// CMainWnd Message Map 

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonDown() 

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
   CString szAboutLeft = "This is a minimal Windows MFC program.\n" 
                         "You've pressed the left mouse button!";

   ::MessageBeep(MB_ICONINFORMATION);
   ::MessageBox(GetSafeHwnd(), szAboutLeft, "About", 
                MB_OK | MB_ICONINFORMATION);
	

   // call the inherited handler
   CFrameWnd::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CMainWnd::OnRButtonDown() 

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
   CString szAboutRight = "This is a minimal Windows MFC program.\n" 
                          "You've pressed the right mouse button!";

   ::MessageBeep(MB_ICONINFORMATION);
   ::MessageBox(GetSafeHwnd(), szAboutRight, "About", 
                MB_OK | MB_ICONINFORMATION);
	
	// call the inherited handler
   CFrameWnd::OnRButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
// CMinApp::InitInstance - overrides virtual CWinApp::InitInstance

BOOL CMinApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Another Minimal MFC Program"));

   // Show the frame window maximized
   pFrame->ShowWindow(SW_SHOWMAXIMIZED);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CMinApp MyApp;

/////////////////////////////////////////////////////////////////////////////
