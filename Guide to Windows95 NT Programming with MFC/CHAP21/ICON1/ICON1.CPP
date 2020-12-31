///////////////////////////////////////////////////////////////////
// Module   : ICON1.CPP
//
// Purpose  : Shows how to use icon resources in an MFC program.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-25-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"  // Resource header - contains resource IDs

///////////////////////////////////////////////////////////////////
// Class CMainWnd - derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   HICON      m_hIcon;  // 32 x 32 pixel icon handle
   HINSTANCE  m_hInst;  // instance handle

public:
   // Helper method called by MFC
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
   // Message handler
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// Class CIconApp - Application class derived from CWinApp

class CIconApp : public CWinApp
{ 
protected:
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_ERASEBKGND()
   ON_WM_CREATE()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::PreCreateWindow()

BOOL CMainWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   // Get the icon handle from the resource data
   m_hIcon = (HICON)::LoadImage(cs.hInstance, 
                                MAKEINTRESOURCE(IDR_ICON1),
                                IMAGE_ICON, 32, 32, 
                                LR_DEFAULTCOLOR);
   // Could also do this:
   // m_hIcon = ::LoadIcon(AfxGetApp()->m_hInstance, 
   //                      MAKEINTRESOURCE(IDR_ICON1));

   return CMainFrame::PreCreateWindow(cs);
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // make the resource icon the default for the frame window
   if (m_hIcon) 
   {
      SetIcon(m_hIcon, TRUE);   // 32 x 32 icon
      SetIcon(m_hIcon, FALSE);  // 16 x 16 icon

      // Could also do this:
      // ::SetClassLong(GetSafeHwnd(), GCL_HICON, (LONG)m_hIcon);
   }

   return 0;
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   CMainFrame::OnEraseBkgnd(pDC);
   
   CRect rc;
   GetClientRect(&rc);

   // Fill the client area with icons!
   for (int cx = 0; cx < rc.right; cx += 32)
      for (int cy = 0; cy < rc.bottom; cy += 32)
         pDC->DrawIcon(cx, cy, m_hIcon);
   
   return TRUE;
}
   
///////////////////////////////////////////////////////////////////
// CIconApp::InitInstance - overrides CWinApp::InitInstance

BOOL CIconApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Sample MFC Icon Program"));

   // Center the frame window and set the client color
   pFrame->CenterWindow();
   pFrame->SetClientBackColor(COLOR_BTNFACE);

   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CIconApp MyIconApp;

///////////////////////////////////////////////////////////////////
