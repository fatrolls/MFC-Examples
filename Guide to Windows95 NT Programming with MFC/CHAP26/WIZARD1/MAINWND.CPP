///////////////////////////////////////////////////////////////////
//  Module   : MAINWND.CPP
//
//  Purpose  : Implementation of the CMainWnd class.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-25-96
///////////////////////////////////////////////////////////////////

#include "mainwnd.h"

IMPLEMENT_DYNCREATE(CMainWnd, CFrameWnd)

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_COMMAND(ID_FILE_EXIT, OnFileExit)
   ON_COMMAND(ID_HELP_ABOUT, OnHelpAbout)
   ON_COMMAND(ID_FILE_RUNWIZARD, OnFileRunWizard)
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
   m_pwndWizard = 0;
   m_pdlgIntro  = 0;
   m_pdlgPage1  = 0;
   m_pdlgPage2  = 0;
   m_pdlgPage3  = 0;
   m_pdlgPage4  = 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
   if (m_pwndWizard) 
      delete m_pwndWizard;
   
   if (m_pdlgIntro) 
      delete m_pdlgIntro;
   
   if (m_pdlgPage1) 
      delete m_pdlgPage1;
   
   if (m_pdlgPage2) 
      delete m_pdlgPage2;
   
   if (m_pdlgPage3) 
      delete m_pdlgPage3;

   if (m_pdlgPage4) 
      delete m_pdlgPage4;
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
   return 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnFileRunWizard()

void CMainWnd::OnFileRunWizard()
{
   // Create the wizard
   m_pwndWizard = new CWizard("Sample Wizard", this);
   ASSERT_VALID(m_pwndWizard);

   // Construct the property pages
   m_pdlgIntro = new CIntroPage;
   ASSERT_VALID(m_pdlgIntro);
   m_pdlgIntro->Construct(IDD_INTRO, 0);

   m_pdlgPage1 = new CPage1;
   ASSERT_VALID(m_pdlgPage1);
   m_pdlgPage1->Construct(IDD_PAGE1, 0);

   m_pdlgPage2 = new CPage2;
   ASSERT_VALID(m_pdlgPage2);
   m_pdlgPage2->Construct(IDD_PAGE2, 0);

   m_pdlgPage3 = new CPage3;
   ASSERT_VALID(m_pdlgPage3);
   m_pdlgPage3->Construct(IDD_PAGE3, 0);

   m_pdlgPage4 = new CPage4;
   ASSERT_VALID(m_pdlgPage4);
   m_pdlgPage4->Construct(IDD_PAGE4, 0);

   // Add the property pages to the property sheet
   m_pwndWizard->AddPage(m_pdlgIntro);
   m_pwndWizard->AddPage(m_pdlgPage1);   
   m_pwndWizard->AddPage(m_pdlgPage2);
   m_pwndWizard->AddPage(m_pdlgPage3);
   m_pwndWizard->AddPage(m_pdlgPage4);

   // Make the property sheet a Wizard
   m_pwndWizard->SetWizardMode();   

   // Display the Wizard
   m_pwndWizard->DoModal();
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

