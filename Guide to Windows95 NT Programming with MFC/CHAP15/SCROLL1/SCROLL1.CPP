///////////////////////////////////////////////////////////////////
//  Module   : SCROLL1.CPP
//
//  Purpose  : Implementation of an MFC program that demonstrates 
//             the use of scroll bar controls.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 03-28-96
///////////////////////////////////////////////////////////////////

#include "scroll1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_ERASEBKGND()
   ON_WM_HSCROLL()      
   ON_WM_SIZE()
   ON_WM_WININICHANGE()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   m_pScroll1 = 0; 
   m_pScroll2 = 0; 
   m_pScroll3 = 0; 
   m_pSizeBox = 0;
   m_pStatic1 = 0; 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
   if (m_pScroll1) delete m_pScroll1;
   if (m_pScroll2) delete m_pScroll2;
   if (m_pScroll3) delete m_pScroll3;
   if (m_pSizeBox) delete m_pSizeBox;
   if (m_pStatic1) delete m_pStatic1;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::CreateChildControls() 

void CMainWnd::CreateChildControls()
{  
   // Allocate new scroll bar objects
   m_pScroll1 = new CScrollBar; ASSERT_VALID(m_pScroll1);
   m_pScroll2 = new CScrollBar; ASSERT_VALID(m_pScroll2);
   m_pScroll3 = new CScrollBar; ASSERT_VALID(m_pScroll3);
   m_pSizeBox = new CScrollBar; ASSERT_VALID(m_pSizeBox);

   m_pStatic1 = new CStatic; ASSERT_VALID(m_pStatic1);
  
   // Initialize the scroll bar objects
   if (!m_pScroll1->Create(SBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SCROLL1))
      { TRACE0(_T("Failed to create Scroll Control 1.\n")); }

   if (!m_pScroll2->Create(SBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SCROLL2))
      { TRACE0(_T("Failed to create Scroll Control 2.\n")); }

   if (!m_pScroll3->Create(SBS_COLOR, 
      CRect(0, 0, 0, 0), this, IDC_SCROLL3))
      { TRACE0(_T("Failed to create Scroll Control 3.\n")); }

   if (!m_pStatic1->Create(_T("Loading application..."), SS_STATIC, 
      CRect(0, 0, 0, 0), this, IDC_STATIC1))
      { TRACE0(_T("Failed to create Static Control.\n")); }

   if (!m_pSizeBox->Create(SBS_SIZEBOX | WS_VISCHILD | WS_BORDER, 
      CRect(0, 0, 0, 0), this, IDC_SCROLL3))
      { TRACE0(_T("Failed to create Size Box.\n")); }

   // Set scroll ranges
   m_pScroll1->SetScrollRange(0, 255);
   m_pScroll2->SetScrollRange(0, 255);
   m_pScroll3->SetScrollRange(0, 255);

   // Set current positions
   m_pScroll1->SetScrollPos(128);
   m_pScroll2->SetScrollPos(128);
   m_pScroll3->SetScrollPos(128);

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

   // Draw the size box interior button colored
   CRect rc;
   m_pSizeBox->GetClientRect(&rc);
   CBrush br(GetSysColor(COLOR_BTNFACE));
   m_pSizeBox->GetDC()->FillRect(&rc, &br);

   return TRUE;
}    

///////////////////////////////////////////////////////////////////
// CMainWnd::OnHScroll() 

void CMainWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
   INT nMax;
   INT nMin;
   INT nCurPos;

   // Get current scroll position
   nCurPos = pScrollBar->GetScrollPos();
   
   // Get scroll range
   pScrollBar->GetScrollRange(&nMin, &nMax);
   
   // Determine which notification is being sent
   switch (nSBCode)
   {
      case SB_LINEDOWN:   
         nCurPos += 1;    // scroll arrow click - increment by 1
         break;

      case SB_LINEUP:   
         nCurPos -= 1;    // scroll arrow click - decrement by 1
         break;

      case SB_PAGEDOWN:     // scroll bar click - increment by 10
         nCurPos += 10;
         break;

      case SB_PAGEUP:     // scroll bar click - decrement by 10
        nCurPos -= 10;
        break;

      case SB_THUMBTRACK: // follow the thumb
         nCurPos = nPos;
         break;

      default:
         break;
   }
   // Set new thumb position
   pScrollBar->SetScrollPos(nCurPos);

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

   // Get the system scroll bar size
   int nVThumb = ::GetSystemMetrics(SM_CYVTHUMB);
   int cyTop = 10;

   // Resize the color scrollers
   m_pScroll1->SetWindowPos(0, 10, cyTop, cx - 20, nVThumb, SWP_SHOWWINDOW);
   cyTop += nVThumb * 2;

   m_pScroll2->SetWindowPos(0, 10, cyTop, cx - 20, nVThumb, SWP_SHOWWINDOW);
   cyTop += nVThumb * 2;

   m_pScroll3->SetWindowPos(0, 10, cyTop, cx - 20, nVThumb, SWP_SHOWWINDOW);
   cyTop += nVThumb * 2;

   // Resize the static control
   m_pStatic1->SetWindowPos(0, 10, cyTop, cx - 20, m_nTextHeight, SWP_SHOWWINDOW);

   // Set the size box position
   m_pSizeBox->SetWindowPos(0, cx - 25, cy - 25, cx, cy, SWP_SHOWWINDOW);

   // Repaint the window at the new size
   UpdateClientColor();

   // Update scroll positions to keep thumb alignment after sizing
   m_pScroll1->SetScrollPos(m_pScroll1->GetScrollPos());
   m_pScroll2->SetScrollPos(m_pScroll2->GetScrollPos());
   m_pScroll3->SetScrollPos(m_pScroll3->GetScrollPos());
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnWinIniChange() 

void CMainWnd::OnWinIniChange(LPCTSTR lpszSection)
{
   // If user has changed control panel settings, update the UI
   OnSize(0, GetClientWidth(), GetClientHeight());

   // Call inherited handler
   CMainFrame::OnWinIniChange(lpszSection);      
}

///////////////////////////////////////////////////////////////////
// CMainWnd::UpdateClientColor() 

void CMainWnd::UpdateClientColor()
{
   BYTE nRed, nGreen, nBlue;

   // Get the current scroll position
   nRed   = m_pScroll1->GetScrollPos();
   nGreen = m_pScroll2->GetScrollPos();
   nBlue  = m_pScroll3->GetScrollPos();
  
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
// CScrollBarApp::InitInstance - overrides CWinApp::InitInstance

BOOL CScrollBarApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, _T("Scroll Bar Color Fun"),
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
CScrollBarApp MyApp;

///////////////////////////////////////////////////////////////////
