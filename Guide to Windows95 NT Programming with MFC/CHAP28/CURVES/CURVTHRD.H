///////////////////////////////////////////////////////////////////
//  Header  : CURVTHRD.H
//
//  Purpose : Header for the CCurveThread class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-19-96
///////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "colors.h"

#define MAXPOINTS 12

typedef enum 
{ 
   dirLeftUp,  
   dirLeftDown,
   dirRightUp, 
   dirRightDown 
}
Direction; 

///////////////////////////////////////////////////////////////////
// Derive a curve thread class 

class CCurveThread : public CWinThread
{ 
public: 
   CCurveThread(HWND hwnd, UINT nMax);
   ~CCurveThread();
   void DrawCurves();
   void UpdatePointPositions();

protected:
   UINT       m_nVelocityX[MAXPOINTS];
   UINT       m_nVelocityY[MAXPOINTS];
   CPoint     m_Point[MAXPOINTS];
   Direction  m_Direction[MAXPOINTS];

   CPen       m_penRed;
   CPen       m_penGreen;
   CPen       m_penBlue;

   HWND       m_hwnd;  // main app window handle

   virtual BOOL InitInstance();
};

