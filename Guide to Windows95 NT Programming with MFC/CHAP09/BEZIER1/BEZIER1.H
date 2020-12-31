///////////////////////////////////////////////////////////////////
//  Header  : BEZIER1.H
//
//  Purpose : Header for the BEZIER1 program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 05-01-96
///////////////////////////////////////////////////////////////////

#include <afxwin.h>  // MFC core classes
#include "colors.h"  // COLORREF definitions

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class 

class CMainWnd : public CFrameWnd
{ 
protected:
   POINT m_apt[10];
   int   m_inCurPoint;
   BOOL  m_bMoving;

   // Helper methods
   void DoBezier();
   void EraseClient(CDC* pDC);
   int GetCurPoint(CPoint pt);
   void ResetControlPoints();

public: 
   CMainWnd();

   // Message handlers
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
