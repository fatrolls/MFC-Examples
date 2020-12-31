///////////////////////////////////////////////////////////////////
// Header  : BUTTONS.H
//
// Purpose : Header for CButtonApp.
//
// Author  : Rob McGregor, rob_mcgregor@compuserve.com
//       
// Date    : 03-10-96
///////////////////////////////////////////////////////////////////
                                                                    
// Custom frame window base class
#include "..\..\chap12\mainfram\mainfram.cpp"   

#include "resource.h"

// Define some button styles
#define BS_CHECK      (BS_CHECKBOX | WS_VISCHILD)
#define BS_AUTOCHECK  (BS_AUTOCHECKBOX | WS_VISCHILD)
#define BS_3          (BS_3STATE | WS_VISCHILD)
#define BS_AUTO3      (BS_AUTO3STATE | WS_VISCHILD)
#define BS_PUSH       (BS_PUSHBUTTON | WS_VISCHILD)
#define BS_DEFPUSH    (BS_DEFPUSHBUTTON | WS_VISCHILD)
#define BS_RADIO      (BS_RADIOBUTTON | WS_VISCHILD)
#define BS_AUTORADIO  (BS_AUTORADIOBUTTON | WS_VISCHILD)
#define BS_GROUP      (BS_GROUPBOX | WS_VISCHILD)
                     
// Control IDs 
#define IDC_BTNABOUT         100    // default standard push button    
#define IDC_BTNEXIT          101    // standard push button            
                                                                       
#define IDC_BTNCHECK         102    // standard check box              
#define IDC_BTNCHECKLEFT     103    // left-captioned check box        
#define IDC_BTNAUTOCHECK1    104    // auto-check box 1                
#define IDC_BTNAUTOCHECK2    105    // standard check box 2            
                                                                       
#define IDC_BTN3STATE        106    // 3-state button                 
#define IDC_BTNAUTO3STATE1   107    // auto 3-state button 1          
#define IDC_BTNAUTO3STATE2   108    // auto 3-state button 2          
                                                                       
#define IDC_BTNRADIO         109    // radio button                    
#define IDC_BTNRADIOLEFT     110    // left-captioned radio button     
#define IDC_BTNAUTORADIO1    111    // auto-radio 1                    
#define IDC_BTNAUTORADIO2    112    // auto-radio 2                    
                                                                       
#define IDC_BITBTN1          113    // bitmap button 1                 
#define IDC_BITBTN2          114    // bitmap button 2                 
#define IDC_BITBTN3          115    // bitmap button 3  
                                                                       
#define IDC_BTNGROUP1        116    // group box 1                     
#define IDC_BTNGROUP2        117    // group box 2                     
#define IDC_BTNGROUP3        118    // group box 3                     
#define IDC_BTNGROUP4        119    // group box 4                     

///////////////////////////////////////////////////////////////////
// Class   : CButtonApp
//
// Purpose : An application class derived from CWinApp

class CButtonApp : public CWinApp
{
public: 
   virtual BOOL InitInstance();     // overridden from CWnd
};

///////////////////////////////////////////////////////////////////
// Class   : CMainWnd
//
// Purpose : A frame window class derived from CMainFrame

class CMainWnd : public CMainFrame
{
protected:
   // Child window button controls 
   CButton*  m_pBtnAbout;         // default standard push button
   CButton*  m_pBtnExit;          // standard push button
   
   CButton*  m_pBtnCheck;         // standard check box 
   CButton*  m_pBtnCheckLeft;     // left-captioned check box 
   CButton*  m_pBtnAutoCheck1;    // auto-check box 1
   CButton*  m_pBtnAutoCheck2;    // standard check box 2
   
   CButton*  m_pBtn3State;       // 3-state button
   CButton*  m_pBtnAuto3State1;  // auto 3-state button 1
   CButton*  m_pBtnAuto3State2;  // auto 3-state button 2
   
   CButton*  m_pBtnRadio;         // radio button
   CButton*  m_pBtnRadioLeft;     // left-captioned radio button
   CButton*  m_pBtnAutoRadio1;    // auto-radio 1
   CButton*  m_pBtnAutoRadio2;    // auto-radio 2
   
   CBitmapButton* m_pBitBtn1;     // bitmap button 1
   CBitmapButton* m_pBitBtn2;     // bitmap button 2
   CBitmapButton* m_pBitBtn3;     // bitmap button 3

   CButton*  m_pBtnGroup1;        // group box 1
   CButton*  m_pBtnGroup2;        // group box 2
   CButton*  m_pBtnGroup3;        // group box 3
   CButton*  m_pBtnGroup4;        // group box 4

   // Message Handlers
   afx_msg void OnBtnAboutClick();  
   afx_msg void OnBtnExitClick();    
   afx_msg void OnAutoRadio1Click();    
   afx_msg void OnAutoRadio2Click();    
   afx_msg void OnBitBtn1Click();    
   afx_msg void OnBitBtn2Click();    
   afx_msg void OnBitBtn3Click();    

public:
   CMainWnd();
   ~CMainWnd();
   virtual void CreateChildControls(); 

   DECLARE_MESSAGE_MAP();
};

///////////////////////////////////////////////////////////////////
