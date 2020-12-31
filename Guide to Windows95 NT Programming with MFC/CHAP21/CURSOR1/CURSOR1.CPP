///////////////////////////////////////////////////////////////////
// Module   : CURSOR1.CPP
//
// Purpose  : Shows how to use cursor resources in an MFC program.
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
   HCURSOR   m_hcurLeft;    // cursor handle
   HCURSOR   m_hcurRight;   // cursor handle
   HCURSOR   m_hcurUp;      // cursor handle
   HCURSOR   m_hcurDown;    // cursor handle
   
   HINSTANCE  m_hInst;      // instance handle

   CRect m_rcLeft;          // rect for drawing
   CRect m_rcRight;         // rect for drawing
   CRect m_rcUp;            // rect for drawing
   CRect m_rcDown;          // rect for drawing

public:
   HCURSOR   m_hcurDefault; // cursor handle

   // Helper method called by MFC
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   // Message handler
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// Class CCursorApp - Application class derived from CWinApp

class CCursorApp : public CWinApp
{ 
protected:
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_ERASEBKGND()
   ON_WM_MOUSEMOVE()
   ON_WM_CREATE()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::PreCreateWindow()

BOOL CMainWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   // Get the Cursor handles from the resource data
   m_hcurLeft = (HCURSOR)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_CURSORLEFT), IMAGE_CURSOR, 
      32, 32, LR_DEFAULTCOLOR);
   
   m_hcurRight = (HCURSOR)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_CURSORRIGHT), IMAGE_CURSOR, 
      32, 32, LR_DEFAULTCOLOR);
   
   m_hcurUp = (HCURSOR)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_CURSORUP), IMAGE_CURSOR, 
      32, 32, LR_DEFAULTCOLOR);
   
   m_hcurDown = (HCURSOR)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_CURSORDOWN), IMAGE_CURSOR, 
      32, 32, LR_DEFAULTCOLOR);
   
   return CMainFrame::PreCreateWindow(cs);
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
   // Store a handle to the original (arrow) cursor
   m_hcurDefault = (HCURSOR)::GetClassLong(GetSafeHwnd(), 
                                           GCL_HCURSOR);

   return CMainFrame::OnCreate(lpCreateStruct);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   CMainFrame::OnEraseBkgnd(pDC);    // call inherited method
   
   // Get the client area rect
   CRect rcClient;
   GetClientRect(&rcClient);
   
   // Define some rectangles
   m_rcLeft.left   = 0; 
   m_rcLeft.top    = rcClient.bottom / 3;
   m_rcLeft.right  = rcClient.right / 3;
   m_rcLeft.bottom = m_rcLeft.top * 2; 

   m_rcRight.left   = m_rcLeft.right * 2; 
   m_rcRight.top    = m_rcLeft.top;
   m_rcRight.right  = rcClient.right;
   m_rcRight.bottom = m_rcLeft.bottom; 

   m_rcUp.left   = m_rcLeft.right; 
   m_rcUp.top    = 0;
   m_rcUp.right  = m_rcRight.left;
   m_rcUp.bottom = m_rcLeft.top; 

   m_rcDown.left   = m_rcUp.left; 
   m_rcDown.top    = m_rcLeft.bottom;
   m_rcDown.right  = m_rcUp.right;
   m_rcDown.bottom = rcClient.bottom; 

   // Create some brushes
   CBrush brLeft(RGB(0, 0, 255));    // blue
   CBrush brRight(RGB(255, 0, 0));   // red
   CBrush brUp(RGB(0, 255, 0));      // green
   CBrush brDown(RGB(0, 255, 255));  // cyan

   // Draw the rectangles
   pDC->FillRect(&m_rcLeft, &brLeft);
   pDC->FillRect(&m_rcRight, &brRight);
   pDC->FillRect(&m_rcUp, &brUp);
   pDC->FillRect(&m_rcDown, &brDown);

   return TRUE;
}
   
///////////////////////////////////////////////////////////////////
// CMainWnd::OnMouseMove()

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
   // Set the current class cursor to NULL
   ::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, NULL);
   
   // check to see if the pointer is in any colored rectangle
   if (m_rcLeft.PtInRect(point))
      SetCursor(m_hcurLeft);

   else if (m_rcRight.PtInRect(point))
      SetCursor(m_hcurRight);
   
   else if (m_rcUp.PtInRect(point))
      SetCursor(m_hcurUp);
   
   else if (m_rcDown.PtInRect(point))
      SetCursor(m_hcurDown);
   
   else  // set back to default
      ::SetClassLong(GetSafeHwnd(), GCL_HCURSOR, 
                     (LONG)m_hcurDefault);

   CMainFrame::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CCursorApp::InitInstance - overrides CWinApp::InitInstance

BOOL CCursorApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Sample MFC Cursor Program"));

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
CCursorApp MyCursorApp;

///////////////////////////////////////////////////////////////////
