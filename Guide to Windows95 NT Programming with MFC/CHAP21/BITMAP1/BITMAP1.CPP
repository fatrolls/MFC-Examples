///////////////////////////////////////////////////////////////////
// Module  : BITMAP1.CPP
//
// Purpose : Shows how to use bitmap resources in an MFC program.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date    : 03-26-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"  // Resource header - contains resource IDs

///////////////////////////////////////////////////////////////////
// Class CMainWnd - derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   HBITMAP   m_hbmpBack;     // bitmap handle
   HBITMAP   m_hbmpBtn1;     // bitmap handle
   HBITMAP   m_hbmpBtn1Lit;  // bitmap handle
   HBITMAP   m_hbmpBtn2;     // bitmap handle
   HBITMAP   m_hbmpBtn2Lit;  // bitmap handle
   
   CRect m_rcTop;     // rect for blitting
   CRect m_rcBtm;     // rect for blitting
   CRect m_rcClient;  // rect for blitting

   void BlitBitmap(CRect& rc, HBITMAP hbm);
   void ShowBitmaps();

public:
   // Helper method called by MFC
   virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

   void PositionRects();

   // Message handler
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
// Class CBitmapApp - Application class derived from CWinApp

class CBitmapApp : public CWinApp
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
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::PreCreateWindow()

BOOL CMainWnd::PreCreateWindow(CREATESTRUCT& cs)
{
   // Get the bitmap handles from the resource data
   m_hbmpBack = (HBITMAP)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_BMPBACKGROUND), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);  // actual size
   
   m_hbmpBtn1 = (HBITMAP)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_BMPBTN1), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);  // actual size
   
   m_hbmpBtn1Lit = (HBITMAP)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_BMPBTN1LIT), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);  // actual size
   
   m_hbmpBtn2 = (HBITMAP)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_BMPBTN2), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);  // actual size
   
   m_hbmpBtn2Lit = (HBITMAP)::LoadImage(cs.hInstance, 
      MAKEINTRESOURCE(IDR_BMPBTN2LIT), IMAGE_BITMAP, 
      0, 0, LR_DEFAULTCOLOR);  // actual size

   // Call inherited method
   return CMainFrame::PreCreateWindow(cs);
}   

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   CMainFrame::OnEraseBkgnd(pDC);   // call inherited method
   
   PositionRects();
   BlitBitmap(m_rcClient, m_hbmpBack);
   
   // "Blit" the unlit versions to the screen
   BlitBitmap(m_rcTop, m_hbmpBtn1);
   BlitBitmap(m_rcBtm, m_hbmpBtn2);

   return TRUE;
}
   
///////////////////////////////////////////////////////////////////
// CMainWnd::PositionRects()

void CMainWnd::PositionRects()
{
   // Set the rect positions
   CRect rc;
   GetClientRect(&rc);
   m_rcClient = rc;
   
   m_rcTop.left  = 523; m_rcTop.top    = 70; 
   m_rcTop.right = 598; m_rcTop.bottom = 145; 
   
   m_rcBtm.left  = 523; m_rcBtm.top    = 168; 
   m_rcBtm.right = 598; m_rcBtm.bottom = 243; 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::BlitBitmap()

void CMainWnd::BlitBitmap(CRect& rc, HBITMAP hbm)
{
   CClientDC dc(this);
   CDC       dcMem;
   HBITMAP   hbmpOld;
   
   // Get a compatible memory DC
   dcMem.CreateCompatibleDC(&dc);

   // Select the bitmap into the DC
   hbmpOld = (HBITMAP)::SelectObject(dcMem, hbm);

   // "Blit" the bitmap to the screen
   //
   GetDC()->BitBlt(rc.left, rc.top, rc.right, rc.bottom, 
                   &dcMem, 0, 0, SRCCOPY); 

   ::SelectObject(dcMem, hbmpOld);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMouseMove()

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
   // check to see if the pointer is over a bitmap area
   //
   if (m_rcTop.PtInRect(point))  
      BlitBitmap(m_rcTop, m_hbmpBtn1Lit); // "light" the top image

   else if (m_rcBtm.PtInRect(point))
      BlitBitmap(m_rcBtm, m_hbmpBtn2Lit); // "light" the bottom image

   else  // turn the lights off
   {
      // "Blit" the unlit versions to the screen
      BlitBitmap(m_rcTop, m_hbmpBtn1);
      BlitBitmap(m_rcBtm, m_hbmpBtn2);
   }

   // Call the inherited method
   CMainFrame::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CBitmapApp::InitInstance - overrides CWinApp::InitInstance

BOOL CBitmapApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Bitmap Resource Demo Program"),
                  WS_SYSMENU | WS_BORDER | WS_VISIBLE | WS_CAPTION, 
                  CRect(0, 0, 640, 480));

   // Center the frame window
   pFrame->CenterWindow();

   // Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   return TRUE;
}

// Declare, create, and run the application
CBitmapApp MyBitmapApp;

///////////////////////////////////////////////////////////////////
