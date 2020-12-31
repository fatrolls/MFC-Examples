///////////////////////////////////////////////////////////////////
//  Header  : SPIN1.H
//
//  Purpose : Header for the SPIN1 MFC program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 03-23-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

// Define some spin windows styles
#define SBS_LEFT  (WS_VISCHILD | UDS_ALIGNLEFT | UDS_SETBUDDYINT)
#define SBS_RIGHT (WS_VISCHILD | UDS_ALIGNRIGHT | UDS_SETBUDDYINT)

// Buddy control style
#define ES_SINGLE (WS_VISCHILD | ES_LEFT | WS_BORDER)

// Control IDs
#define IDC_SPIN1   100
#define IDC_SPIN2   101
#define IDC_SPIN3   102

#define IDC_BUDDY1  104
#define IDC_BUDDY2  105
#define IDC_BUDDY3  106

///////////////////////////////////////////////////////////////////
// Derive an application class 

class CSpinApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Derive a frame window class 

class CMainWnd : public CMainFrame
{ 
protected:
   CSpinButtonCtrl*  m_pSpin1;
   CSpinButtonCtrl*  m_pSpin2;
   CSpinButtonCtrl*  m_pSpin3;

   CEdit*            m_pBuddy1;
   CEdit*            m_pBuddy2;
   CEdit*            m_pBuddy3;

   void UpdateClientColor();

public: 
   CMainWnd();
   ~CMainWnd();
   virtual void CreateChildControls();

   // Message handlers
   afx_msg void OnSize(UINT nType, int cx, int cy);
   afx_msg void OnBuddyUpdate();  

   DECLARE_MESSAGE_MAP();
};

//
// CMainWnd Inline methods
//
inline void CMainWnd::OnBuddyUpdate()
   { UpdateClientColor(); }

///////////////////////////////////////////////////////////////////

