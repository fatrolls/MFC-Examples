///////////////////////////////////////////////////////////////////
//  Header  : DIALOG2.H
//
//  Purpose : Header for the DIALOG2 program.
//
//  Author  : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date    : 05-22-96
///////////////////////////////////////////////////////////////////

#include "mainfram.h"   // Custom frame window base class
#include "resource.h"

///////////////////////////////////////////////////////////////////
// Application class 

class CMyApp : public CWinApp
{ 
public: 
   virtual BOOL InitInstance();
};

///////////////////////////////////////////////////////////////////
// Frame window class 

class CMainWnd : public CMainFrame
{ 
   DECLARE_DYNCREATE(CMainWnd)

public:
   CMainWnd(); 
   virtual ~CMainWnd(); 

protected:
   COLORREF    m_crBackColor;
   CStatusBar  m_wndStatusBar;
   CDialogBar  m_dlgBar;

   // Message map methods
   afx_msg int OnCreate(LPCREATESTRUCT lpCS);
   afx_msg void OnFileExit();
   afx_msg void OnDialogWndSize();
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

///////////////////////////////////////////////////////////////////
