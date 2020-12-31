///////////////////////////////////////////////////////////////////
//  Header  : SCROLL1.H
//
//  Purpose : Header for the SCROLL1 MFC program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-25-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define a scroll bar window style
#define SBS_COLOR (SBS_HORZ | WS_VISCHILD | WS_TABSTOP)

// Static control style
#define SS_STATIC (WS_VISCHILD | SS_CENTER)

// Control IDs
#define IDC_SCROLL1   100
#define IDC_SCROLL2   101
#define IDC_SCROLL3   102
#define IDC_SCROLL4   103
#define IDC_STATIC1   104

///////////////////////////////////////////////////////////////////
// CScrollBarApp - Derived application class 

class CScrollBarApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// CMainWnd - Derived frame window class 

class CMainWnd : public CMainFrame
{ 
protected:
   // Three scroll bars
   CScrollBar*  m_pScroll1;
   CScrollBar*  m_pScroll2;
   CScrollBar*  m_pScroll3;
   CScrollBar*  m_pSizeBox;
   
   // One static control
   CStatic*  m_pStatic1;

   // Text height
   INT m_nTextHeight;   
   
   // Helper methods
   void UpdateClientColor();

public: 
   CMainWnd();
   ~CMainWnd();
   virtual void CreateChildControls();

   // Message handlers
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnWinIniChange(LPCTSTR lpszSection);

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
                