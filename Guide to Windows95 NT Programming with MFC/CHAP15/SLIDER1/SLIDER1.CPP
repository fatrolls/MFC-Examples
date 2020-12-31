///////////////////////////////////////////////////////////////////
//  Module   : SLIDER1.CPP
//
//  Purpose  : Implementation of an MFC program that demonstrates 
//             the use of slider controls.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 03-30-96
///////////////////////////////////////////////////////////////////

#include "slider1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_ERASEBKGND()
   ON_WM_HSCROLL()      
   ON_WM_SIZE()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   m_pSlider1 = 0; 
   m_pSlider2 = 0; 
   m_pSlider3 = 0; 

   m_pStatic1 = 0; 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
   if (m_pSlider1) delete m_pSlider1;
   if (m_pSlider2) delete m_pSlider2;
   if (m_pSlider3) delete m_pSlider3;

   if (m_pStatic1) delete m_pStatic1;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() 

void CMainWnd::CreateChildControls()
{  
   // Allocate new slider objects
   m_pSlider1 = new CSliderCtrl; ASSERT_VALID(m_pSlider1);
   m_pSlider2 = new CSliderCtrl; ASSERT_VALID(m_pSlider2);
   m_pSlider3 = new CSliderCtrl; ASSERT_VALID(m_pSlider3);

   m_pStatic1 = new CStatic; ASSERT_VALID(m_pStatic1);
  
   // Initialize the slider objects 
   if (!m_pSlider1->Create(TBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SLIDER1))
      { TRACE0(_T("Failed to create Slider Control 1\n")); }

   if (!m_pSlider2->Create(TBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SLIDER1))
      { TRACE0(_T("Failed to create Slider Control 2\n")); }

   if (!m_pSlider3->Create(TBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SLIDER1))
      { TRACE0(_T("Failed to create Slider Control 3\n")); }

   if (!m_pStatic1->Create(_T("Loading application..."), SS_STATIC, 
      CRect(0, 0, 0, 0), this, IDC_STATIC1))
      { TRACE0(_T("Failed to create Static Control\n")); }

   // Set slider ranges
   m_pSlider1->SetRange(0, 255);
   m_pSlider2->SetRange(0, 255);
   m_pSlider3->SetRange(0, 255);

   // Set current positions
   m_pSlider1->SetPos(128);
   m_pSlider2->SetPos(128);
   m_pSlider3->SetPos(128);

   // Set tick frequency
   m_pSlider1->SetTicFreq(8);
   m_pSlider2->SetTicFreq(8);
   m_pSlider3->SetTicFreq(8);

   // Set page size
   m_pSlider1->SetPageSize(8);
   m_pSlider2->SetPageSize(8);
   m_pSlider3->SetPageSize(8);

   // Set line size
   m_pSlider1->SetLineSize(1);
   m_pSlider2->SetLineSize(1);
   m_pSlider3->SetLineSize(1);

   // Set a new font for the static control
   SetWndFont(m_pStatic1, _T("MS Sans Serif"), 10);

   // Store the height of the static control's font
   TEXTMETRIC tm;
   m_pStatic1->GetDC()->GetTextMetrics(&tm);
   m_nTextHeight = tm.tmHeight + tm.tmExternalLeading;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   // call the inherited handler
   CMainFrame::OnEraseBkgnd(pDC);

   // paint the client area as needed
   UpdateClientColor();

   return TRUE;
}    

///////////////////////////////////////////////////////////////////
// CMainWnd::OnHScroll() 

void CMainWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   // *Much* simpler than a scroll bar!
      
   // Change to the new color
   UpdateClientColor();
   
   // call inherited handler
   CMainFrame::OnHScroll(nSBCode, nPos, pScrollBar);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize() 

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   // Call inherited method
   CWnd::OnSize(nType, cx, cy);

   // set some initial positions 
   int nHeight = 20;
   int cyTop   = 10;

   // Resize the color sliders
   m_pSlider1->SetWindowPos(0, 10, cyTop, cx - 20, nHeight, SWP_SHOWWINDOW);
   cyTop += nHeight * 2;

   m_pSlider2->SetWindowPos(0, 10, cyTop, cx - 20, nHeight, SWP_SHOWWINDOW);
   cyTop += nHeight * 2;

   m_pSlider3->SetWindowPos(0, 10, cyTop, cx - 20, nHeight, SWP_SHOWWINDOW);
   cyTop += nHeight * 2;

   // Resize the static control
   m_pStatic1->SetWindowPos(0, 10, cyTop, cx - 20, m_nTextHeight, SWP_SHOWWINDOW);

   // Repaint the window at the new size
   UpdateClientColor();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::UpdateClientColor() 

void CMainWnd::UpdateClientColor()
{
   BYTE nRed, nGreen, nBlue;

   // Get the current scroll position
   nRed   = m_pSlider1->GetPos();
   nGreen = m_pSlider2->GetPos();
   nBlue  = m_pSlider3->GetPos();
  
   // Display current RGB color as a text string
   CString szText = _T("RGB(");
   szText += IntToString(nRed) + ", " + 
             IntToString(nGreen) + ", " + 
             IntToString(nBlue) + ")";
   m_pStatic1->SetWindowText(szText); 

   // Set brush to desired background color
   CBrush br(RGB(nRed, nGreen, nBlue));

   // Save old brush
   CDC* pDC = GetDC();
   CBrush* pbrOld = pDC->SelectObject(&br);

   CRect rc;
   pDC->GetClipBox(&rc);  // Erase only the area needed
   pDC->PatBlt(rc.left, rc.top, rc.Width(), rc.Height(), PATCOPY);
   pDC->SelectObject(pbrOld);
}

///////////////////////////////////////////////////////////////////
// CSliderCtrlApp::InitInstance - overrides CWinApp::InitInstance

BOOL CSliderApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Slider Control Color Fun"),
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN),
                  CRect(0, 0, 640, 480);

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
CSliderApp MyApp;

///////////////////////////////////////////////////////////////////
