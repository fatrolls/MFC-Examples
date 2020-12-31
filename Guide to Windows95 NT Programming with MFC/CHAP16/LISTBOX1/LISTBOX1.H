///////////////////////////////////////////////////////////////////
// Module  : LISTBOX1.H
//
// Purpose : Header for CListBoxApp.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//       
// Date    : 03-05-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define two custom list box styles
#define LBS_SINGLE (LBS_STANDARD | WS_VISIBLE | WS_CHILD)
#define LBS_MULTI  (LBS_STANDARD | WS_VISIBLE | WS_CHILD | LBS_EXTENDEDSEL)

// Button styles
#define BS_COMMAND (WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON)

// Control IDs
#define IDC_LBSINGLE 100   // single-select list box
#define IDC_LBMULTI  101   // multi-select list box
#define IDC_BTNSEND  102   // send button
#define IDC_BTNCLEAR 103   // clear button

///////////////////////////////////////////////////////////////////
// Class   : CListBoxApp
//
// Purpose : An application class derived from CWinApp

class CListBoxApp : public CWinApp
{
public: 
   virtual BOOL InitInstance();   // overridden from CWnd
};

///////////////////////////////////////////////////////////////////
// Class   : CMainWnd
//
// Purpose : An custom frame window class derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   UINT m_cnSelected;                    // selected item counter

   // child controls
   CListBox* m_plbMulti;                 // multi-select member
   CListBox* m_plbSingle;                // single-select member
   CButton*  m_pbtnSend;                 // send button
   CButton*  m_pbtnClear;                // clear button
  
   // message handlers
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
   afx_msg void OnSListBoxDblClick();    // respond to double click
   afx_msg void OnMListBoxDblClick();    // respond to double click
   afx_msg void OnMListBoxClick();       // respond to click
   afx_msg void OnBtnSendClick();        // respond to send click
   afx_msg void OnBtnClearClick();       // respond to clear click
   
public:
   CMainWnd();
   virtual ~CMainWnd();

   // To allocate & initilize child controls
   virtual void CreateChildControls();
   
   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
