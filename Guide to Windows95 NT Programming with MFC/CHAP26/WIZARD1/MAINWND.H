///////////////////////////////////////////////////////////////////
//  Header  : MAINWND.H
//
//  Purpose : Interface for the CMainWnd class.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 05-26-96
///////////////////////////////////////////////////////////////////

#ifndef __MAINWND_H__
#define __MAINWND_H__

#include "mainfram.h"   // Custom frame window base class
#include "wizdata.h"
#include "wizard.h"
#include "intropg.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
#include "page4.h"

///////////////////////////////////////////////////////////////////
// Frame window class 

class CMainWnd : public CMainFrame
{ 
   DECLARE_DYNCREATE(CMainWnd)

public:
   CMainWnd(); 
   virtual ~CMainWnd(); 

protected:
   CStatusBar   m_wndStatusBar;
   
   CWizard*      m_pwndWizard;
   CIntroPage*   m_pdlgIntro;
   CPage1*       m_pdlgPage1;
   CPage2*       m_pdlgPage2;
   CPage3*       m_pdlgPage3;
   CPage4*       m_pdlgPage4;
   
   COLORREF      m_crBackColor;

   // Message map methods
   afx_msg int OnCreate(LPCREATESTRUCT lpCS);
   afx_msg void OnFileExit();
   afx_msg void OnFileRunWizard();
   afx_msg void OnHelpAbout();

   DECLARE_MESSAGE_MAP()
};

///////////////////////////////////////////////////////////////////
// CAboutDlg dialog

class CAboutDlg : public CDialog
{
// Construction
public:
   CAboutDlg(CWnd* pParent = NULL);   // standard constructor
   enum { IDD = IDD_ABOUTBOX };
};

// Inline constructor
inline CAboutDlg::CAboutDlg(CWnd* pParent) : 
   CDialog(CAboutDlg::IDD, pParent) { }


#endif  // __MAINWND_H__

///////////////////////////////////////////////////////////////////
