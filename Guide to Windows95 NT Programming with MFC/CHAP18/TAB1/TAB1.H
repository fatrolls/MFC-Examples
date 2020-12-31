///////////////////////////////////////////////////////////////////
// Header   : TAB1.H
//
// Purpose  : Header for the TAB1 program.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 06-15-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CTestApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance(); 
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class

#define IDC_TABCTRL      125
#define IDC_ANIMCTRL     126
#define IDC_RICHEDITCTRL 127

class CMainWnd : public CMainFrame
{
public:
   CMainWnd();
   virtual ~CMainWnd();
   
   void SetStyleHeading1(CHARFORMAT& cf);
   void SetStyleHeading2(CHARFORMAT& cf);
   void SetStyleNormal(CHARFORMAT& cf);

protected:
   CTabCtrl       m_ctlTab;
   CAnimateCtrl   m_ctlAnim;
   CRichEditCtrl  m_ctlRichEdit;
 
   void GenerateRichText();

   // Message handlers
   afx_msg int OnCreate(LPCREATESTRUCT lpcs);
   afx_msg void OnClickTabCtrl(NMHDR* pNotifyStruct, 
      LRESULT* pResult);
   afx_msg void OnSize(UINT nType, int cx, int cy);

   DECLARE_MESSAGE_MAP();
};

//////////////////////////////////////////////////////////////////