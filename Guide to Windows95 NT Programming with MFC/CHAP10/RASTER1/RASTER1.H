///////////////////////////////////////////////////////////////////
//  Header   : RASTER1.CPP
//
//  Purpose  : Header for the RASTER1 application.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-01-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Derive an application class 
class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

// Derive a frame window class 
class CMainWnd : public CMainFrame
{ 
protected:
   int    m_nTextHeight;
   CRect  m_rcRop[18];
   CFont  m_fntTitle;

public: 
   CMainWnd();
   ~CMainWnd();
   
   void DisplayLabel(CPaintDC& dc, int nWhich, 
      COLORREF cr = crBlack);
   void DoRasterOps(CPaintDC& dc);
   void CombineRops(CPaintDC& dc, int nIndex, int nWidth, 
      int nHeight, CDC* pdcMem, DWORD dwRop);
   void FillRectArray();

   afx_msg int OnCreate(LPCREATESTRUCT lpcs);
   afx_msg void OnPaint();
   afx_msg void OnSize(UINT nType, int cx, int cy);

   DECLARE_MESSAGE_MAP();
};
