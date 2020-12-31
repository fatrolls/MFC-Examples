///////////////////////////////////////////////////////////////////
// Module   : MOUSEKEY.CPP
//
// Purpose  : Implementation of an MFC program that uses mouse 
//            methods, mouse capture, and keyboard methods to 
//            demonstrate user input in MFC applications.
///////////////////////////////////////////////////////////////////

#include "mousekey.h"

///////////////////////////////////////////////////////////////////
// CMainWnd Message Map 

BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
   ON_WM_CREATE()
   ON_WM_SIZE()
   //
   // Mouse entries
   //
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_NCHITTEST()
   //
   // Keyboard entries
   //
   ON_WM_CHAR()
   ON_WM_SYSCHAR()
   ON_WM_KEYDOWN()
   ON_WM_KEYUP()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() -  Constructor

CMainWnd::CMainWnd()
{ 
   m_bLMouseDown = FALSE;
   m_cyPixels = 0;
   m_cyClient = 0;
   m_cxText   = 0;
   m_cyText   = 0;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() -  Destructor

CMainWnd::~CMainWnd()
{ 
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate() 

int CMainWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{ 
   // Get the height of the default font
   TEXTMETRIC tm;

   CDC* pDC = GetDC();
   pDC->GetTextMetrics(&tm);

   m_cxText = tm.tmAveCharWidth;
   m_cyText = tm.tmHeight;

   ReleaseDC(pDC);

   // Set tab stops
   int cx = 24;
   for (int i = 0; i < 7; i++)
   {
      m_anTabs[i] = m_cxText * cx + 15;
      cx += 6;
   }

   m_cyPixels = m_cyText;

   // Call inherited handler
   return CFrameWnd::OnCreate(lpCreateStruct);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSize() 

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   m_cyClient = cy; 

   // Call inherited handler
   CFrameWnd::OnSize(nType, cx, cy);
}

///////////////////
// Mouse Handlers
///////////////////

///////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonDown() 

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
   // Set the class member mouse down flag
   m_bLMouseDown = TRUE;

   // Capture the mouse
   SetCapture();

   // Show the current left mouse button state
   ShowLButtonState();

   // Activate the Start Menu
   //ActivateStartMenu();
         
   // call the inherited handler
   CFrameWnd::OnLButtonDown(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonUp() 

void CMainWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
   // Set the class member mouse down flag
   m_bLMouseDown = FALSE;

   // release the mouse capture
   ReleaseCapture();

   // Show the current left mouse button state
   ShowLButtonState();

   // call the inherited handler
   CFrameWnd::OnLButtonUp(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnMouseMove() 

void CMainWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
   // Show the current left mouse button state
   ShowLButtonState;

   // Call inherited handler
   CFrameWnd::OnMouseMove(nFlags, point);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::ShowLButtonState() 

void CMainWnd::ShowLButtonState() 
{
   CString strState = "MOUSEKEY - [Left Mouse Button State: ";
   
   // Show present state of the left mouse button in the title bar 
   if (m_bLMouseDown)
      strState += "DOWN]";
   else
      strState += "UP]";

   SetWindowText(strState);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnNcHitTest() 

UINT CMainWnd::OnNcHitTest(CPoint point) 
{
   // Get the current non-client area being hit
   UINT nWhere = CFrameWnd::OnNcHitTest(point);
   CString strNcHit = "MOUSEKEY - [NC ";

   switch (nWhere)
   {
      default:
         ShowLButtonState();
         return CFrameWnd::OnNcHitTest(point);

      case HTERROR:
         ShowLButtonState();
         return CFrameWnd::OnNcHitTest(point);

      case HTBORDER:
         strNcHit += "Border Hit]";
         break;

      case HTBOTTOM:	
         strNcHit += "Bottom Border Hit]";
         break;

      case HTBOTTOMLEFT:
         strNcHit += "Bottom Left Border Hit]";
         break;

      case HTBOTTOMRIGHT:
         strNcHit += "Border Bottom Right Border Hit]";
         break;

      case HTCAPTION:
         strNcHit += "Caption Hit]";
         break;

      case HTCLOSE:
         strNcHit += "Close Button Hit]";
         break;

      case HTLEFT:
         strNcHit += "Left Border Hit]";
         break;

      case HTMAXBUTTON:
         strNcHit += "Maximize Button Hit]";
         break;

      case HTMINBUTTON:
         strNcHit += "Minimize Button Hit]";
         break;

      case HTRIGHT:	
         strNcHit += "Right Border Hit]";
         break;

      case HTSYSMENU:
         strNcHit += "System Menu Hit]";
         break;

      case HTTOP:
         strNcHit += "Top Border Hit]";
         break;

      case HTTOPLEFT:
         strNcHit += "Top Left Border Hit]";
         break;

      case HTTOPRIGHT:
         strNcHit += "Top Right Border Hit]";
         break;
   }
   SetWindowText(strNcHit);
   return CFrameWnd::OnNcHitTest(point);
}

//////////////////////
// Keyboard Handlers
//////////////////////

///////////////////////////////////////////////////////////////////
// CMainWnd::OnChar() 

void CMainWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // Draw the character
   CString msg = "WM_CHAR";
   ShowKeyInfo(msg, nChar, nRepCnt, nFlags);

   // Call inherited handler
   CFrameWnd::OnChar(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnSysChar() 

void CMainWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // Draw the character
   CString msg = "WM_SYSCHAR";
   ShowKeyInfo(msg, nChar, nRepCnt, nFlags);
   
   // Call inherited handler
   CFrameWnd::OnSysChar(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnKeyDown() 

void CMainWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // Draw the character
   CString msg = "WM_KEYDOWN";
   ShowKeyInfo(msg, nChar, nRepCnt, nFlags);

   // Call inherited handler
   CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnKeyUp() 

void CMainWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
   // Draw the character
   CString msg = "WM_KEYUP";
   ShowKeyInfo(msg, nChar, nRepCnt, nFlags);

   // Call inherited handler
   CFrameWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::ShowKeyInfo() 

void CMainWnd::ShowKeyInfo(CString str, UINT nChar, 
                           UINT nRepCnt, UINT nFlags)
{
   // Create a header string
   CString strHeader = "Message\t Char\t Rep\t Scan\t Ext\t"
                       "Con\t Prev\t Trans";

   // Macro to extract the low-order bit from UINT nFlags
   #define LOBIT(b) ((b) & 0x01)
   
   // Create an output string
   CString strOut;
   strOut.Format("%s\t %c\t %u\t %u\t %u\t %u\t %u\t %u",
                 str, nChar, nRepCnt, LOBYTE(nFlags),
                 LOBIT(nFlags >> 8),
                 LOBIT(nFlags >> 13),
                 LOBIT(nFlags >> 14),
                 LOBIT(nFlags >> 15));

   // If at the bottom wrap back to the top and start over
   if (m_cyPixels >= m_cyClient - m_cyText)
   {
      Invalidate();
      m_cyPixels = 0;
   }

   // Draw the text 
   GetDC()->TabbedTextOut(5, 0, strHeader, 7, m_anTabs, 0);
   GetDC()->TabbedTextOut(5, m_cyPixels, strOut, 7, m_anTabs, 0);
   m_cyPixels += m_cyText;
}

///////////////////////////////////////////////////////////////////
// CInputApp::InitInstance - overrides CWinApp::InitInstance

BOOL CInputApp::InitInstance()
{
   // Allocate a new frame window object
   CMainWnd* pFrame = new CMainWnd;

   // Initialize the frame window
   pFrame->Create(0, "MOUSEKEY - [Left Mouse Button State: UP]", 
                  WS_OVERLAPPEDWINDOW, CRect(0, 0, 640, 480));

   // Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;
   return TRUE;
}

// Declare, create, and run the application
CInputApp MyApp;

///////////////////////////////////////////////////////////////////
