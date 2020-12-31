///////////////////////////////////////////////////////////////////
// Header   : WAVES1.H
//
// Purpose  : Header for WAVES1 program
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-26-96
///////////////////////////////////////////////////////////////////

// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"  // Resource header - contains resource IDs
#include <mmsystem.h>  // multimedia extensions

// Button IDs
#define IDC_BTN1  200
#define IDC_BTN2  201
#define IDC_BTN3  202
#define IDC_BTN4  203

// Button style
#define BS_PUSH (BS_PUSHBUTTON | WS_VISCHILD)
 
///////////////////////////////////////////////////////////////////
// Class CMainWnd - derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   HICON   m_hIcon;    // 32 x 32 pixel icon handle
 
   CButton* m_pBtn1;   // Button 1
   CButton* m_pBtn2;   // Button 2
   CButton* m_pBtn3;   // Button 3
   CButton* m_pBtn4;   // Button 4

   BOOL PlayWave(LPCTSTR lpszWave);

public:
   CMainWnd();   // constructor
   ~CMainWnd();  // destructor
   
   // Override inherited placeholder
   virtual void CreateChildControls();

   // Message handler
   afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
   afx_msg void OnBtn1Click();
   afx_msg void OnBtn2Click();
   afx_msg void OnBtn3Click();
   afx_msg void OnBtn4Click();

   DECLARE_MESSAGE_MAP();
};

//
// Inline methods
//
inline void CMainWnd::OnBtn1Click()
   { PlayWave(MAKEINTRESOURCE(IDR_WAVE1)); }

inline void CMainWnd::OnBtn2Click()
   { PlayWave(MAKEINTRESOURCE(IDR_WAVE2)); }

inline void CMainWnd::OnBtn3Click()
   { PlayWave(MAKEINTRESOURCE(IDR_WAVE3)); }

inline void CMainWnd::OnBtn4Click()
   { PlayWave(MAKEINTRESOURCE(IDR_WAVE4)); }

///////////////////////////////////////////////////////////////////
// Class CWaveApp - Application class derived from CWinApp

class CWaveApp : public CWinApp
{ 
protected:
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
