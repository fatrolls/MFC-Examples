///////////////////////////////////////////////////////////////////
//  Module   : BEZIER1.CPP
//
//  Purpose  : Implementation of an MFC program using interactive 
//             Bezier curves.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-01-96
///////////////////////////////////////////////////////////////////

#include "bezier1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_RBUTTONDOWN()
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - Constructor

CMainWnd::CMainWnd()
{
   ResetControlPoints();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonDown()

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
   // See if the cursor is in any of the points
   SetCapture();
   m_inCurPoint = GetCurPoint(point);
   if (m_inCurPoint >= 0)
      m_bMoving = TRUE;
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::GetCurPoint()

int CMainWnd::GetCurPoint(CPoint pt)
{
   for (int i = 0; i < 10; i++)
   {
      //  Create an 8 x 8 pixel bounding box for each point
      CRect rc;
      rc.left   = m_apt[i].x - 4;
      rc.top    = m_apt[i].y - 4;
      rc.right  = m_apt[i].x + 4;
      rc.bottom = m_apt[i].y + 4;

      // See if cursor is in there
      if (rc.PtInRect(pt))  // found one!
         return i; 
   }
   return -1;                // didn't find any :(
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonUp()

void CMainWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
   m_bMoving    = FALSE;
   m_inCurPoint = -1;

   // Release the mouse and draw the Bezier curve
   ::ReleaseCapture();
   DoBezier();
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMouseMove()

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point)
{
   if ((m_bMoving != 0) && (m_inCurPoint >= 0))
   {
      m_apt[m_inCurPoint] = point;

      CClientDC dc(this);
      
      EraseClient(&dc);
      DoBezier();
   }
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnRButtonDown()

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
   // Reset to initial Bezier config
   Invalidate();
   ResetControlPoints();
   DoBezier();
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::ResetControlPoints()

void CMainWnd::ResetControlPoints()
{
   m_bMoving    = FALSE;
   m_inCurPoint = -1;

   m_apt[0].x = 100;  m_apt[0].y = 100;
   m_apt[1].x = 150;  m_apt[1].y = 135;
   m_apt[2].x = 200;  m_apt[2].y = 165;
   m_apt[3].x = 250;  m_apt[3].y = 225;
   m_apt[4].x = 300;  m_apt[4].y = 265;
   m_apt[5].x = 350;  m_apt[5].y = 300;
   m_apt[6].x = 375;  m_apt[6].y = 335;
   m_apt[7].x = 400;  m_apt[7].y = 350;
   m_apt[8].x = 450;  m_apt[8].y = 375;
   m_apt[9].x = 500;  m_apt[9].y = 400;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   // Call inherited handler
   CFrameWnd::OnEraseBkgnd(pDC);

   EraseClient(pDC);
   DoBezier();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::EraseClient()

void CMainWnd::EraseClient(CDC* pDC)
{
   // Erase the client area 
   CRect rc;
   GetClientRect(&rc);

   CBrush br(crWhite);
   pDC->FillRect(&rc, &br);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoBezier() 

void CMainWnd::DoBezier()
{
   // Create a client DC to draw on
   CClientDC dc(this);

   // Draw points
   for (int i = 0; i < 10; i++)
      dc.Ellipse(m_apt[i].x - 4, m_apt[i].y - 4, 
                 m_apt[i].x + 4, m_apt[i].y + 4);

   // Create new pens
   CPen penBlue;
   CPen penRed;

   penBlue.CreatePen(PS_DOT, 1, crBlue);
   penRed.CreatePen(PS_SOLID, 1, crRed);
   
   // Select a new pen into the device context, and save 
   // the old pen to restore on clean up...
   CPen* ppenOld;
   ppenOld = dc.SelectObject(&penBlue);

   // Draw lines with blue pen to connect control points 
   dc.Polyline(m_apt, 10);
   
   // Draw Bezier curve with red pen
   dc.SelectObject(&penRed);
   dc.PolyBezier(m_apt, 10);

   // Leave things as we found them (clean up)
   dc.SelectObject(ppenOld);

}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->Create(0, 
      "Interactive MFC Bezier Curve",
      WS_POPUPWINDOW | WS_DLGFRAME,
      CRect(0, 0, 640, 480));

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

	// Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

// Declare, create, and run the application
CMyApp MyApp;

///////////////////////////////////////////////////////////////////
