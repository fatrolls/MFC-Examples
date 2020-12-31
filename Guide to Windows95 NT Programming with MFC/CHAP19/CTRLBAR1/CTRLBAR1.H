///////////////////////////////////////////////////////////////////
//  Header  : CTRLBAR1.H
//
//  Purpose : Header for the CTRLBAR1 program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 06-08-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#define IDC_STATUS     100
#define IDC_TOOLBAR    101
#define IDC_TBBUTTON1  102
#define IDC_TBBUTTON2  103
#define IDC_TBBUTTON3  104
#define IDC_TBBUTTON4  105

#define NUM_TBBUTTONS  4  // Number of TBBUTTONs used in toolbar

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// CMainWnd - A frame window class derived from CMainFrame

class CMainWnd : public CMainFrame
{ 
protected:
   CToolBarCtrl    m_ctlToolBar;
   CToolTipCtrl    m_ctlToolTip;
   CStatusBarCtrl  m_ctlStatus;
  
   // Array of toolbar button structures
   TBBUTTON m_atbb[NUM_TBBUTTONS];

public: 
   CMainWnd();
   ~CMainWnd();

   // Message handlers
   afx_msg int OnCreate(LPCREATESTRUCT lpcs);
   afx_msg void OnMouseMove(UINT nFlags, CPoint point);
   afx_msg void OnSize(UINT nType, int cx, int cy);

   // Button command handlers
   afx_msg void OnButton1Click();
   afx_msg void OnButton2Click();
   afx_msg void OnButton3Click();
   afx_msg void OnButton4Click();
   
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   
   BOOL OnToolTipNotify(UINT id, NMHDR * pTTTStruct, 
      LRESULT* pResult);
 
   DECLARE_MESSAGE_MAP();
};

