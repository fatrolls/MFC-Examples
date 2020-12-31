// msdi.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "msdi.h"

#include "mainfrm.h"
#include "msdidoc.h"
#include "msdiview.h"
#include "grafview.h"
#include "outview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsdiApp

BEGIN_MESSAGE_MAP(CMsdiApp, CMSDIWinApp)
  //{{AFX_MSG_MAP(CMsdiApp)
  ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
    // NOTE - the ClassWizard will add and remove mapping macros here.
    //    DO NOT EDIT what you see in these blocks of generated code!
  //}}AFX_MSG_MAP
  // Standard print setup command
  ON_COMMAND(ID_FILE_PRINT_SETUP, CMSDIWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdiApp construction

CMsdiApp::CMsdiApp()
{
  // TODO: add construction code here,
  // Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMsdiApp object

CMsdiApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsdiApp initialization

BOOL CMsdiApp::InitInstance()
{
  // Standard initialization
  // If you are not using these features and wish to reduce the size
  //  of your final executable, you should remove from the following
  //  the specific initialization routines you do not need.

  SetDialogBkColor();    // Set dialog background color to gray
  LoadStdProfileSettings();  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  //  serve as the connection between documents, frame windows and views.

  CMultiDocTemplate* pMsdiDocTemplate = new CMultiDocTemplate(
    IDR_MSDITYPE,
    RUNTIME_CLASS(CMsdiDoc),
    RUNTIME_CLASS(CMSDIFrame),  // main MSDI first child frame
    RUNTIME_CLASS(CMsdiView));  // the main view
  AddDocTemplate(pMsdiDocTemplate);

  CMultiDocTemplate* pGrafDocTemplate = new CMultiDocTemplate(
    IDR_GRAFTYPE,
    RUNTIME_CLASS(CMsdiDoc),
    RUNTIME_CLASS(CViewFrame),  // standard MSDI second child frame
    RUNTIME_CLASS(CGrafView));  // the graf view
  AddDocTemplate(pGrafDocTemplate);

  CMultiDocTemplate* pOutDocTemplate = new CMultiDocTemplate(
    IDR_OUTTYPE,
#ifdef WIN32
    NULL,     // view is not dependent from document
#else
    RUNTIME_CLASS(CMsdiDoc), // to avoid an ASSERT
#endif
    RUNTIME_CLASS(CViewFrame),// standard MSDI second child frame
    RUNTIME_CLASS(COutView)); // the output view
  AddDocTemplate(pOutDocTemplate);

  // create main MDI Frame window
  CMainFrame* pMainFrame = new CMainFrame;
  if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
    return FALSE;
  m_pMainWnd = pMainFrame;

  // enable file manager drag/drop and DDE Execute open
  EnableShellOpen();
  RegisterShellFileTypes();

  // simple command line parsing
  if (m_lpCmdLine[0] == '\0')
  {
    // create a new (empty) document
    OnFileNew();
  }
  else
  {
    // open an existing document
    OpenDocumentFile(m_lpCmdLine);
  }

  m_pMainWnd->DragAcceptFiles();
  // The main window has been initialized, so show and update it.
  pMainFrame->ShowWindow(m_nCmdShow);
  pMainFrame->UpdateWindow();

  return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
  //{{AFX_DATA(CAboutDlg)
  enum { IDD = IDD_ABOUTBOX };
  //}}AFX_DATA

// Implementation
protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //{{AFX_MSG(CAboutDlg)
    // No message handlers
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
  //{{AFX_DATA_INIT(CAboutDlg)
  //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAboutDlg)
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
  //{{AFX_MSG_MAP(CAboutDlg)
    // No message handlers
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMsdiApp::OnAppAbout()
{
  CAboutDlg aboutDlg;
  aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMsdiApp commands
