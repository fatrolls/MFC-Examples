///////////////////////////////////////////////////////////////////
//  Header  : SLIDER1.H
//
//  Purpose : Header for the SLIDER1 MFC program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-25-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define a slider control window style
#define TBS_COLOR (TBS_HORZ | TBS_AUTOTICKS | WS_VISCHILD | WS_TABSTOP)

// Static control style
#define SS_STATIC (WS_VISCHILD | SS_CENTER)

// Control IDs
#define IDC_SLIDER1   100
#define IDC_SLIDER2   101
#define IDC_SLIDER3   102
#define IDC_SLIDER4   103
#define IDC_STATIC1   104

///////////////////////////////////////////////////////////////////
// CSliderApp - Derived application class 

class CSliderApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// CMainWnd - Derived frame window class 

class CMainWnd : public CMainFrame
{ 
protected:
   // Three slider controls
   CSliderCtrl*  m_pSlider1;
   CSliderCtrl*  m_pSlider2;
   CSliderCtrl*  m_pSlider3;
   
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

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
                