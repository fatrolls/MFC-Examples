///////////////////////////////////////////////////////////////////
// Module   : CURVTHRD.CPP
//
// Purpose  : Implementation of the CCurveThread class
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 06-20-96
///////////////////////////////////////////////////////////////////

#include "curvthrd.h"
#include "random.h"
#include "curves.h"

extern CMutex  g_Mutex;

///////////////////////////////////////////////////////////////////
//  CCurveThread::CCurveThread() - constructor

CCurveThread::CCurveThread(HWND hwnd, UINT nMax)
{
   // Store the handle of the main app window
   m_hwnd = hwnd;
   
   CRand rand;

	for (int i = 0; i < MAXPOINTS; i++)
   {
      m_nVelocityX[i] = rand.MapRand(nMax) + 1;
      m_nVelocityY[i] = rand.MapRand(nMax) + 1;

      m_Point[i].x = m_Point[i].y = 0;
      
      m_Direction[i] = dirRightDown;
   }

   // Create some pens
   m_penRed.CreatePen(PS_SOLID, 1, crRed);
	m_penGreen.CreatePen(PS_SOLID, 1, crGreen);
	m_penBlue.CreatePen(PS_SOLID, 1, crBlue);
}

///////////////////////////////////////////////////////////////////
//  CCurveThread::~CCurveThread() - destructor

CCurveThread::~CCurveThread()
{
   // Delete pens
   DeleteObject(m_penRed);
   DeleteObject(m_penGreen);
   DeleteObject(m_penBlue);
}

///////////////////////////////////////////////////////////////////
//  CCurveThread::InitInstance() 

BOOL CCurveThread::InitInstance()
{
   CMainWnd wnd;
   CMainWnd* pWnd = (CMainWnd*) wnd.FromHandle(m_hwnd);

   // Create a single lock object using the global mutex
   CSingleLock SingleLock(&g_Mutex);

   // Loop for the life of the thread
   while (1)
   {
      // Lock the resource, in this case the device context used
      // by the DrawCurves() method...
      // We could also use the Win32 API function:
      //    ::WaitForSingleObject(g_Mutex, INFINITE);
      //
      SingleLock.Lock();
     
      // Draw the curves for this thread
      DrawCurves();
   
      // Unlock the shared resource...
      // We could also use the  Win32 API function:
      //    ::ReleaseMutex(g_Mutex);
      //
      SingleLock.Unlock();
   }
   // Kill the thread by returning zero
   return 0;
}

///////////////////////////////////////////////////////////////////
//  CCurveThread::UpdatePointPositions()

void CCurveThread::UpdatePointPositions()
{   
   // Get the client rectangle of the app's main window
   CRect rc;
   ::GetClientRect(m_hwnd, &rc);

   //
   // Move the control points of the beziers according to the 
   // random values preset in the constructor...
   //
   for (int i = 0; i < MAXPOINTS; i++)
   {
      // Right
      if ((m_Point[i].x >= rc.right) && (m_Direction[i] == dirRightUp))
         m_Direction[i] = dirLeftUp;

      if ((m_Point[i].x >= rc.right) && (m_Direction[i] == dirRightDown))
         m_Direction[i] = dirLeftDown;

      // Top
      if ((m_Point[i].y <= rc.top) && (m_Direction[i] == dirRightUp))
         m_Direction[i] = dirRightDown;
      
      if ((m_Point[i].y <= rc.top) && (m_Direction[i] == dirLeftUp))
         m_Direction[i] = dirLeftDown;
      
      // Left
      if ((m_Point[i].x <= rc.left) && (m_Direction[i] == dirLeftUp))
         m_Direction[i] = dirRightUp;
      
      if ((m_Point[i].x <= rc.left) && (m_Direction[i] == dirLeftDown))
         m_Direction[i] = dirRightDown;
      
      // Bottom
      if ((m_Point[i].y >= rc.bottom) && (m_Direction[i] == dirLeftDown))
         m_Direction[i] = dirLeftUp;
      
      if ((m_Point[i].y >= rc.bottom) && (m_Direction[i] == dirRightDown))
         m_Direction[i] = dirRightUp;
      
      switch (m_Direction[i])
      {
         case dirLeftUp:
           m_Point[i].x -= m_nVelocityX[i];
           m_Point[i].y -= m_nVelocityY[i];
           break;

         case dirLeftDown:
           m_Point[i].x -= m_nVelocityX[i];
           m_Point[i].y += m_nVelocityY[i];
           break;

         case dirRightUp:
           m_Point[i].x += m_nVelocityX[i];
           m_Point[i].y -= m_nVelocityY[i];
           break;

         case dirRightDown:
           m_Point[i].x += m_nVelocityX[i];
           m_Point[i].y += m_nVelocityY[i];
      }
   }
}

///////////////////////////////////////////////////////////////////
// CCurveThread::DrawCurves()

void CCurveThread::DrawCurves()
{   
   CClientDC* pDC = (CClientDC*) AfxGetMainWnd()->GetDC();

   // Set XOR drawing mode
   int nPrevDrawMode = pDC->SetROP2(R2_XORPEN);

   // Draw each curve in its current position (erases current)
   CPen* pPenOld;
   pPenOld = pDC->SelectObject(&m_penRed);
   pDC->PolyBezier(&m_Point[0], 4);

   pDC->SelectObject(&m_penGreen);
   pDC->PolyBezier(&m_Point[4], 4);

   pDC->SelectObject(&m_penBlue);
   pDC->PolyBezier(&m_Point[8], 4);

   // Move each point
   UpdatePointPositions();

   // Draw each curve in its new position
   pDC->SelectObject(&m_penRed);
   pDC->PolyBezier(&m_Point[0], 4);

	pDC->SelectObject(&m_penGreen);
   pDC->PolyBezier(&m_Point[4], 4);

	pDC->SelectObject(&m_penBlue);
   pDC->PolyBezier(&m_Point[8], 4);

   // Restore the device context to original state
   pDC->SelectObject(pPenOld);
   pDC->SetROP2(nPrevDrawMode);

   // Release the DC
   AfxGetMainWnd()->ReleaseDC(pDC);
}
