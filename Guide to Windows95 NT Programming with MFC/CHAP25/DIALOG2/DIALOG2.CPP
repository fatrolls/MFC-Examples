///////////////////////////////////////////////////////////////////
//  Module   : DIALOG2.CPP
//
//  Purpose  : Implementation of an MFC program using custom 
//             dialogs.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-22-96
///////////////////////////////////////////////////////////////////

#include "dialog2.h"
#include "sizedlg.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(CMainWnd, CFrameWnd)

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(ID_FILE_EXIT, OnFileExit)
   ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
   ON_COMMAND(ID_DIALOG_WNDSIZE, OnDialogWndSize)
END_MESSAGE_MAP()

// Status bar array
static UINT auIndicators[] =
{
   ID_SEPARATOR,           // status line indicator
   ID_INDICATOR_CAPS,
   ID_INDICATOR_NUM,
   ID_INDICATOR_SCRL,
};

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpCS)
{
   // Create a status bar
   if (!m_wndStatusBar.Create(this))
   {
      TRACE0("Failed to create status bar\n");
      return -1;    
   }

   if (!m_wndStatusBar.SetIndicators(auIndicators,
       sizeof(auIndicators) / sizeof(UINT)))
   {
      TRACE0("Failed to set status bar indicators\n");
      return -1;    
   }
   
   // Create the dialog bar
   if (!m_dlgBar.Create(this, IDD_DLGBAR, WS_CHILD | CBRS_TOP, 
      IDD_DLGBAR))
   {
      TRACE0("Failed to create dialog bar\n");
      return -1;    
   }

   m_dlgBar.ShowWindow(SW_SHOWNORMAL);
   
   // Set the dialog bar's edit control text
   CEdit* pEdit = (CEdit*) m_dlgBar.GetDlgItem(IDC_EDIT1);
   if (!pEdit) 
      return -1;
   
   pEdit->SetWindowText("Some text...");

   return 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnDialogWndSize()

void CMainWnd::OnDialogWndSize()
{
   CWndSizeDlg dlgSizer;
   dlgSizer.DoModal();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileExit()

void CMainWnd::OnFileExit() 
{
   DestroyWindow();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnHelpAbout()

void CMainWnd::OnHelpAbout() 
{
   CAboutDlg dlgAbout;
   dlgAbout.DoModal();
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd();

   // Initialize the frame window
   pFrame->LoadFrame(IDR_MAINFRAME, 
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;
   pFrame->SetClientBackColor(COLOR_APPWORKSPACE);
   pFrame->CreateChildControls();

   // Show the frame window, centered
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
