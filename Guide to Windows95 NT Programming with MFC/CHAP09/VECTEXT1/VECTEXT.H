///////////////////////////////////////////////////////////////////
//  Header  : VECTEXT.H
//
//  Purpose : Header for the VECTEXT program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 04-29-96
///////////////////////////////////////////////////////////////////

#include <afxwin.h>  // MFC core classes
#include <afxext.h>  // MFC extension classes
#include "colors.h"  // COLORREF definitions

// Macro for seeding random number generator
#define SeedRand() srand((UINT)::GetTickCount())

//
// Values for the various graphics methods defined in VECTEXT.CPP
// These values determine in which order the methods are called...
//
#define DO_PIXELS             0
#define DO_POINTS             1
#define DO_LINES              2 
#define DO_ELLIPSES           3
#define DO_RECTS              4
#define DO_ROUNDRECTS         5
#define DO_REGIONS            6
#define DO_REGIONSDIFFERENCE  7
#define DO_REGIONSINTERSECT   8
#define DO_REGIONSUNION       9
#define DO_POLYLINE           10
#define DO_POLYGON            11
#define DO_BEZIER             12
#define DO_METAFILE           13
#define DO_TEXTSYSTEM         14
#define DO_TEXTARIAL          15
#define DO_TEXTROMAN          16

#define MAXCLICKS             16

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
   int     m_nCurScreen;  // Current "screen" for graphic displays
   CPoint  m_apt[10];     // An array of 10 points

   // Helper methods
   COLORREF GetRandomColor();
   void ProcessMouseClick(BOOL bAdvance);
   UINT MapRand(UINT nMax);
   void DisplayLogFont(CClientDC* pDC, CString sFont);
   
   // Graphics methods
   void DoBezier(CClientDC* pDC);
   void DoEllipses(CClientDC* pDC);
   void DoLines(CClientDC* pDC);
   void DoMetafile(CClientDC* pDC);
   void DoPixels(CClientDC* pDC);
   void DoPoints(CClientDC* pDC);
   void DoPolygon(CClientDC* pDC);
   void DoPolyLine(CClientDC* pDC);
   void DoRects(CClientDC* pDC);
   void DoRegions(CClientDC* pDC);
   void DoRegionsUnion(CClientDC* pDC);
   void DoRegionsDifference(CClientDC* pDC);
   void DoRegionsIntersect(CClientDC* pDC);
   void DoRoundRects(CClientDC* pDC);
   void DoTextArial(CClientDC* pDC);
   void DoTextRoman(CClientDC* pDC);
   void DoTextSystem(CClientDC* pDC);

public: 
   CMainWnd();

   // Message handlers
   afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
   afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
