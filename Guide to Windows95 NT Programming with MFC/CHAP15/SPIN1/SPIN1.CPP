///////////////////////////////////////////////////////////////////
//  Module   : SPIN1.CPP
//
//  Purpose  : Implementation of an MFC program that demonstrates 
//             the use of spin controls.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 03-23-96
///////////////////////////////////////////////////////////////////

#include "spin1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_SIZE()
   ON_EN_UPDATE(IDC_BUDDY1, OnBuddyUpdate)      
   ON_EN_UPDATE(IDC_BUDDY2, OnBuddyUpdate)      
   ON_EN_UPDATE(IDC_BUDDY3, OnBuddyUpdate)      
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   m_pSpin1  = 0; 
   m_pSpin2  = 0; 
   m_pSpin3  = 0; 

   m_pBuddy1 = 0; 
   m_pBuddy2 = 0; 
   m_pBuddy3 = 0; 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
   if (m_pSpin1) delete m_pSpin1;
   if (m_pSpin2) delete m_pSpin2;
   if (m_pSpin3) delete m_pSpin3;

   if (m_pBuddy1) delete m_pBuddy1;
   if (m_pBuddy2) delete m_pBuddy2;
   if (m_pBuddy3) delete m_pBuddy3;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() 

void CMainWnd::CreateChildControls()
{  
   // Allocate new spin button objects
   m_pSpin1 = new CSpinButtonCtrl; ASSERT_VALID(m_pSpin1);
   m_pSpin2 = new CSpinButtonCtrl; ASSERT_VALID(m_pSpin2);
   m_pSpin3 = new CSpinButtonCtrl; ASSERT_VALID(m_pSpin3);

   // Allocate new buddy edit controls
   m_pBuddy1 = new CEdit; ASSERT_VALID(m_pBuddy1);
   m_pBuddy2 = new CEdit; ASSERT_VALID(m_pBuddy2);
   m_pBuddy3 = new CEdit; ASSERT_VALID(m_pBuddy3);

   // Initialize the spin button objects
   int y1 = 10; 
   int y2 = 40;

   if (!m_pSpin1->Create(SBS_LEFT, CRect(10, y1, 27, y2), this, IDC_SPIN1))
      { TRACE0(_T("Failed to create Spin Control 1\n")); }

   if (!m_pSpin2->Create(SBS_RIGHT, CRect(10, y1+=40, 27, y2+=40), this, IDC_SPIN2))
      { TRACE0(_T("Failed to create Spin Control 2\n")); }

   if (!m_pSpin3->Create(SBS_RIGHT, CRect(10, y1+=40, 27, y2+=40), this, IDC_SPIN3))
      { TRACE0(_T("Failed to create Spin Control 3\n")); }

   // Initialize the buddy edit controls
   y1 = 10; 
   y2 = 40;

   if (!m_pBuddy1->Create(ES_SINGLE, CRect(10, y1, 55, y2), this, IDC_BUDDY1))
      { TRACE0(_T("Failed to create Buddy Control 1\n")); }

   if (!m_pBuddy2->Create(ES_SINGLE, CRect(10, y1+=40, 55, y2+=40), this, IDC_BUDDY2))
      { TRACE0(_T("Failed to create Buddy Control 2\n")); }

   if (!m_pBuddy3->Create(ES_SINGLE, CRect(10, y1+=40, 55, y2+=40), this, IDC_BUDDY3))
      { TRACE0(_T("Failed to create Buddy Control 3\n")); }

   // Set buddies
   m_pSpin1->SetBuddy(m_pBuddy1);
   m_pSpin2->SetBuddy(m_pBuddy2);
   m_pSpin3->SetBuddy(m_pBuddy3);

   // Set scroll ranges
   m_pSpin1->SetRange(0, 255);
   m_pSpin2->SetRange(0, 255);
   m_pSpin3->SetRange(0, 255);

   // Set current position
   m_pSpin1->SetPos(128);
   m_pSpin2->SetPos(128);
   m_pSpin3->SetPos(128);

}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize() 

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   // Call inherited method
   CWnd::OnSize(nType, cx, cy);

   // Repaint the window at the new size
   UpdateClientColor();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::UpdateClientColor() 

void CMainWnd::UpdateClientColor()
{
   CString szBuddy1Text;
   CString szBuddy2Text;
   CString szBuddy3Text;

   m_pBuddy1->GetWindowText(szBuddy1Text);
   m_pBuddy2->GetWindowText(szBuddy2Text);
   m_pBuddy3->GetWindowText(szBuddy3Text);

   INT nBuddy1 = StringToInt(&szBuddy1Text);
   INT nBuddy2 = StringToInt(&szBuddy2Text);
   INT nBuddy3 = StringToInt(&szBuddy3Text);
   
   if( nBuddy1 > 255)
      nBuddy1 = 255;
   else if (nBuddy1 < 0)          
      nBuddy1 = 0;

   if (nBuddy2 > 255)
      nBuddy2 = 255;
   else if (nBuddy2 < 0)
      nBuddy2 = 0;
                                
   if (nBuddy3 > 255)
      nBuddy3 = 255;
   else if (nBuddy3 < 0)
      nBuddy3 = 0;

   CRect rcClient;
   GetClientRect(&rcClient);

   CBrush br(RGB(nBuddy1, nBuddy2, nBuddy3));
   GetDC()->FillRect(&rcClient, &br);
}

///////////////////////////////////////////////////////////////////
// CSpinApp::InitInstance - overrides CWinApp::InitInstance

BOOL CSpinApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Spin Controls And Their Buddies"),
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                  CRect(0, 0, 640, 480));

   // Create the child windows
   pFrame->CreateChildControls();

   // Set the new frame window back brush
   pFrame->SetClientBackColor(COLOR_BTNFACE);

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   // Show the frame window centered
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

// Declare, create, and run the application
CSpinApp MyApp;

///////////////////////////////////////////////////////////////////
