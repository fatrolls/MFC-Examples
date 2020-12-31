///////////////////////////////////////////////////////////////////
//  Header  : PALETTE1.H
//
//  Purpose : Header for the PALETTE1 MFC program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 05-29-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Derive an application class 
class CPaletteApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

// Derive a frame window class 
class CMainWnd : public CMainFrame
{ 
protected:
   LPLOGPALETTE m_pLP;
   CPalette     m_pal;

public: 
   CMainWnd();
   ~CMainWnd();

   void Display4WayPalette(CPaintDC* pDC, CPalette& pal);
   void Fill4WayPalette();
   afx_msg void OnPaint();
   afx_msg BOOL OnQueryNewPalette();
   afx_msg void OnPaletteChanged(CWnd* pFocusWnd);

   DECLARE_MESSAGE_MAP();
};
