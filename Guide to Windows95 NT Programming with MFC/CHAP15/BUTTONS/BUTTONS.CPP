///////////////////////////////////////////////////////////////////
// Module   : BUTTONS.CPP
//
// Purpose  : Implementation of program that uses all predefined 
//            button styles for CButton and CBitmapButton classes
//            in a frame window.
//
// Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
// Date     : 03-20-96
///////////////////////////////////////////////////////////////////

#include "buttons.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_COMMAND(IDC_BTNABOUT, OnBtnAboutClick)      
   ON_COMMAND(IDC_BTNEXIT, OnBtnExitClick)      
   ON_COMMAND(IDC_BTNAUTORADIO1, OnAutoRadio1Click)
   ON_COMMAND(IDC_BTNAUTORADIO2, OnAutoRadio2Click)
   ON_COMMAND(IDC_BITBTN1, OnBitBtn1Click)      
   ON_COMMAND(IDC_BITBTN2, OnBitBtn2Click)      
   ON_COMMAND(IDC_BITBTN3, OnBitBtn3Click)      
END_MESSAGE_MAP()

//
// CMainWnd Methods
//

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{
   // Initialize the child control pointers to NULL...
   m_pBtnAbout = 0;  
   m_pBtnExit  = 0;
   
   m_pBtnCheck      = 0;
   m_pBtnCheckLeft  = 0;
   m_pBtnAutoCheck1 = 0;
   m_pBtnAutoCheck2 = 0;
   
   m_pBtn3State      = 0;
   m_pBtnAuto3State1 = 0;
   m_pBtnAuto3State2 = 0;
   
   m_pBtnRadio      = 0;
   m_pBtnRadioLeft  = 0;
   m_pBtnAutoRadio1 = 0;
   m_pBtnAutoRadio2 = 0;
   
   m_pBtnGroup1 = 0;
   m_pBtnGroup2 = 0;
   m_pBtnGroup3 = 0;
   m_pBtnGroup4 = 0;

   m_pBitBtn1 = 0;
   m_pBitBtn2 = 0;
   m_pBitBtn3 = 0;
}  
                
///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor (overrides default)

CMainWnd::~CMainWnd()
{
   if (m_pBtnAbout) delete m_pBtnAbout;
   if (m_pBtnExit)  delete m_pBtnExit;
   
   if (m_pBtnCheck)      delete m_pBtnCheck;
   if (m_pBtnCheckLeft)  delete m_pBtnCheckLeft;
   if (m_pBtnAutoCheck1) delete m_pBtnAutoCheck1;
   if (m_pBtnAutoCheck2) delete m_pBtnAutoCheck2;
   
   if (m_pBtn3State)      delete m_pBtn3State;
   if (m_pBtnAuto3State1) delete m_pBtnAuto3State1;
   if (m_pBtnAuto3State2) delete m_pBtnAuto3State2;
   
   if (m_pBtnRadio)      delete m_pBtnRadio;
   if (m_pBtnRadioLeft)  delete m_pBtnRadioLeft;
   if (m_pBtnAutoRadio1) delete m_pBtnAutoRadio1;
   if (m_pBtnAutoRadio2) delete m_pBtnAutoRadio2;
   
   if (m_pBtnGroup1) delete m_pBtnGroup1;
   if (m_pBtnGroup2) delete m_pBtnGroup2;
   if (m_pBtnGroup3) delete m_pBtnGroup3;
   if (m_pBtnGroup4) delete m_pBtnGroup4;

   if (m_pBitBtn1) delete m_pBitBtn1;
   if (m_pBitBtn2) delete m_pBitBtn2;
   if (m_pBitBtn3) delete m_pBitBtn3;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() 

void CMainWnd::CreateChildControls()
{
   // Allocate the child controls
   m_pBtnAbout = new CButton; ASSERT_VALID(m_pBtnAbout);
   m_pBtnExit  = new CButton; ASSERT_VALID(m_pBtnExit);
   
   m_pBtnGroup1     = new CButton; ASSERT_VALID(m_pBtnGroup1);
   m_pBtnCheck      = new CButton; ASSERT_VALID(m_pBtnCheck);
   m_pBtnCheckLeft  = new CButton; ASSERT_VALID(m_pBtnCheckLeft);
   m_pBtnAutoCheck1 = new CButton; ASSERT_VALID(m_pBtnAutoCheck1);
   m_pBtnAutoCheck2 = new CButton; ASSERT_VALID(m_pBtnAutoCheck2);
   
   m_pBtnGroup2      = new CButton; ASSERT_VALID(m_pBtnGroup2);
   m_pBtn3State      = new CButton; ASSERT_VALID(m_pBtn3State);
   m_pBtnAuto3State1 = new CButton; ASSERT_VALID(m_pBtnAuto3State1);
   m_pBtnAuto3State2 = new CButton; ASSERT_VALID(m_pBtnAuto3State2);
   
   m_pBtnGroup3     = new CButton; ASSERT_VALID(m_pBtnGroup3);
   m_pBtnRadio      = new CButton; ASSERT_VALID(m_pBtnRadio);
   m_pBtnRadioLeft  = new CButton; ASSERT_VALID(m_pBtnRadioLeft);
   m_pBtnAutoRadio1 = new CButton; ASSERT_VALID(m_pBtnAutoRadio1);
   m_pBtnAutoRadio2 = new CButton; ASSERT_VALID(m_pBtnAutoRadio2);
   
   m_pBtnGroup4 = new CButton; ASSERT_VALID(m_pBtnGroup1);
   m_pBitBtn1   = new CBitmapButton; ASSERT_VALID(m_pBitBtn1);
   m_pBitBtn2   = new CBitmapButton; ASSERT_VALID(m_pBitBtn2);
   m_pBitBtn3   = new CBitmapButton; ASSERT_VALID(m_pBitBtn3);

   // initialize the child buttons
   if (!m_pBtnExit->Create("Exit", BS_PUSH, 
      CRect(424, 8, 513, 33), this, IDC_BTNEXIT))
      { TRACE0("Failed to create Exit button\n"); }

   if (!m_pBtnAbout->Create("About", BS_DEFPUSH, 
      CRect(424, 40 , 513, 65), this, IDC_BTNABOUT))
      { TRACE0("Failed to create About button\n"); }

   //
   // Check Boxes
   //
   if (!m_pBtnGroup1->Create("Check Boxes", BS_GROUP, 
      CRect(8, 8, 209, 137), this, IDC_BTNGROUP1))
      { TRACE0("Failed to create Group Box 1\n"); }

   if (!m_pBtnCheck->Create("Standard Check Box", BS_CHECK, 
      CRect(24, 32, 193, 49), this, IDC_BTNCHECK))
      { TRACE0("Failed to create Check Box\n"); }

   if (!m_pBtnCheckLeft->Create("LeftText Check Box", 
      BS_CHECK | BS_LEFTTEXT, 
      CRect(24, 56, 193, 73), this, IDC_BTNCHECKLEFT))
      { TRACE0("Failed to create LeftText Check Box\n"); }
                                                         
   if (!m_pBtnAutoCheck1->Create("Auto Check Box 1", BS_AUTOCHECK, 
   CRect(24, 88, 193, 105), 
      this, IDC_BTNAUTOCHECK1))
      { TRACE0("Failed to create AutoCheck Box 1\n"); }

   if (!m_pBtnAutoCheck2->Create("Auto Check Box 2", BS_AUTOCHECK, 
   CRect(24, 112, 193, 129), 
      this, IDC_BTNAUTOCHECK2))
      { TRACE0("Failed to create AutoCheck Box 2\n"); }

   //
   // 3-State Check Boxes
   //

   if (!m_pBtnGroup2->Create("3-State", BS_GROUP, 
      CRect(8, 144, 209, 249), this, IDC_BTNGROUP2))
      { TRACE0("Failed to create Group Box 2\n"); }

   if (!m_pBtn3State->Create("3-State Check Box", BS_3, 
   CRect(24, 168, 193, 185), 
      this, IDC_BTN3STATE))
      { TRACE0("Failed to create 3-State button\n"); }

   if (!m_pBtnAuto3State1->Create("3-State Auto Check 1", BS_AUTO3, 
   CRect(24, 200, 193, 217), 
      this, IDC_BTNAUTO3STATE1))
      { TRACE0("Failed to create Auto 3-State button 1\n"); }

   if (!m_pBtnAuto3State2->Create("3-State Auto Check 2", BS_AUTO3, 
      CRect(24, 224, 193, 241), this, IDC_BTNAUTO3STATE2))
      { TRACE0("Failed to create Auto3State button 2\n"); }

   //
   // Radio Buttons
   //
   if (!m_pBtnGroup3->Create("Radio Buttons", BS_GROUP, 
      CRect(216, 8, 409, 137), this, IDC_BTNGROUP3))
      { TRACE0("Failed to create Group Box 3\n"); }

   if (!m_pBtnRadio->Create("Radio Button", BS_RADIO, 
      CRect(232, 32, 401, 49), this, IDC_BTNRADIO))  
      { TRACE0("Failed to create Radio button\n"); }

   if (!m_pBtnRadioLeft->Create("LeftText Radio Button", 
      BS_RADIO | BS_LEFTTEXT, 
      CRect(232, 56, 401, 73), this, IDC_BTNRADIOLEFT))
      { TRACE0("Failed to create LeftText Radio button\n"); }

   if (!m_pBtnAutoRadio1->Create("Auto Radio Button 1", 
      BS_AUTORADIO, CRect(232, 88, 401, 105), 
      this, IDC_BTNAUTORADIO1))
      { TRACE0("Failed to create AutoRadio button 1\n"); }

   if (!m_pBtnAutoRadio2->Create("Auto Radio Button 2", 
      BS_AUTORADIO, CRect(232, 112, 401, 129), 
      this, IDC_BTNAUTORADIO2))
      { TRACE0("Failed to create AutoRadio button 2\n"); }

   //
   // Bitmap Buttons
   //
   if (!m_pBtnGroup4->Create("Bitmap Buttons", BS_GROUP, 
      CRect(216, 144, 409, 249), this, IDC_BTNGROUP4))
      { TRACE0("Failed to create Group Box 4\n"); }

   // BitBtn1
   if (!m_pBitBtn1->Create("Test", BS_PUSH | BS_OWNERDRAW, 
      CRect(232, 184, 281, 233), this, IDC_BITBTN1))
      { TRACE0("Failed to create Bitmap button 1\n"); }
   
   if (!m_pBitBtn1->LoadBitmaps(IDR_BITMAP1UP, IDR_BITMAP1DOWN))
      { TRACE0("Failed to load bitmap for Bitmap button 1\n"); }

   // BitBtn2
   if (!m_pBitBtn2->Create("", BS_PUSH | BS_OWNERDRAW, 
      CRect(288, 184, 337, 233), this, IDC_BITBTN2))
      { TRACE0("Failed to create Bitmap button 2\n"); }

   if (!m_pBitBtn2->LoadBitmaps(IDR_BITMAP2UP, IDR_BITMAP2DOWN))
      { TRACE0("Failed to load bitmap for Bitmap button 2\n"); }

   // BitBtn3
   if (!m_pBitBtn3->Create("", BS_PUSH | BS_OWNERDRAW, 
      CRect(344, 184, 393, 233), this, IDC_BITBTN3))
      { TRACE0("Failed to create Bitmap button 3\n"); }

   if (!m_pBitBtn3->LoadBitmaps(IDR_BITMAP3UP, IDR_BITMAP3DOWN))
      { TRACE0("Failed to load bitmap for Bitmap button 3\n"); }

   // Set some button states
   m_pBtnAuto3State1->SetCheck(3); 
   m_pBtnAuto3State2->SetCheck(1); 
   m_pBtnRadio->SetCheck(1); 
   m_pBtnAutoCheck1->SetCheck(1);
}
  
///////////////////////////////////////////////////////////////////
// CMainWnd::OnAutoRadio1Click() 

void CMainWnd::OnAutoRadio1Click()
{
   // Set a new font for each control
   //
   if (m_pFont)
   {
      delete m_pFont;
      m_pFont = 0;
   }

   SetChildFonts(IDC_BTNABOUT, IDC_BTNGROUP4, 
                 _T("MS Sans Serif"), 8);
   Invalidate();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnAutoRadio2Click() 

void CMainWnd::OnAutoRadio2Click()
{
   // Set a new font for each control
   //
   if (m_pFont)
   {
      delete m_pFont;
      m_pFont = 0;
   }
   SetChildFonts(IDC_BTNABOUT, IDC_BTNGROUP4, 
                 _T("Times New Roman"), 11);
   Invalidate();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBtnExitClick() 

void CMainWnd::OnBtnExitClick()
{
   DestroyWindow();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBtnAboutClick() 

void CMainWnd::OnBtnAboutClick()
{
   ::MessageBeep(MB_ICONINFORMATION);
   MessageBox(_T("Look at all those MFC button styles!"),
              _T("About"), MB_OK | MB_ICONINFORMATION);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBitBtn1Click() 

void CMainWnd::OnBitBtn1Click()
{
   ::MessageBeep(MB_ICONINFORMATION);

   // Launch the Windows Paint applet...
   ::WinExec(_T("pbrush"), SW_SHOWNORMAL);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBitBtn2Click() 

void CMainWnd::OnBitBtn2Click()
{
   ::MessageBeep(MB_ICONINFORMATION);

   // Launch the Windows Notepad applet...
   ::WinExec(_T("notepad"), SW_SHOWNORMAL);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnBitBtn3Click() 

void CMainWnd::OnBitBtn3Click()
{
   ::MessageBeep(MB_ICONINFORMATION);

   // Launch the Windows Explorer...
   ::WinExec(_T("explorer"), SW_SHOWNORMAL);
}

//
// CButtonApp Methods
//

///////////////////////////////////////////////////////////////////
// CButtonApp::InitInstance 

BOOL CButtonApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window                                      
   pFrame->Create(0, _T("MFC Button Style Sampler"),
                  WS_POPUPWINDOW | WS_DLGFRAME,
                  CRect(0, 0, 530, 290));

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;
   pFrame->SetClientBackColor(COLOR_BTNFACE);
  
   // Create the child controls for the frame window
   pFrame->CreateChildControls();

   // Center and show the frame window
   pFrame->CenterWindow();
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}
                
///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CButtonApp MyEditApp;

///////////////////////////////////////////////////////////////////
