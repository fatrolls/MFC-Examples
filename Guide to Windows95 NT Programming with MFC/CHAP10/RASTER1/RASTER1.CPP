///////////////////////////////////////////////////////////////////
//  Module   : RASTER1.CPP
//
//  Purpose  : Program to show all predefined Windows raster 
//             operations (ROPs).
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 06-01-96
///////////////////////////////////////////////////////////////////

#include "raster1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_CREATE()
   ON_WM_PAINT()
   ON_WM_SIZE()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
}

//////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{  
}

//////////////////////////////////////////////////////////////////
// CMainWnd::OnCreate()

int CMainWnd::OnCreate(LPCREATESTRUCT lpcs)
{ 
   CClientDC dc(this);

   m_fntTitle.CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE,
      0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
      DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");

   TEXTMETRIC tm;
   dc.GetTextMetrics(&tm);
   m_nTextHeight = tm.tmHeight + tm.tmExternalLeading * 2;

   MoveWindow(0, 0, 600, m_nTextHeight * 3 + 300, FALSE);
   CenterWindow();
   FillRectArray();

   return CFrameWnd::OnCreate(lpcs);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::OnSize()

void CMainWnd::OnSize(UINT nType, int cx, int cy)
{
   // Call inherited method
   CFrameWnd::OnSize(nType, cx, cy);

   // Update everything for display at new size
   FillRectArray();
   Invalidate();
   UpdateWindow();
}

//////////////////////////////////////////////////////////////////
// CMainWnd::DisplayLabel()

void CMainWnd::DisplayLabel(CPaintDC& dc, int nWhich, COLORREF cr)
{
   int nLeft = m_rcRop[nWhich].left;
   int nTop  = m_rcRop[nWhich].top;
   
   CString str;
   dc.SelectObject(m_fntTitle);
   
   switch (nWhich)
   {
      case 0: str = " Source: Red"; break;
      case 1: str = " Source: Blue"; break;
      case 2: str = " BLACKNESS"; break;
      case 3: str = " DSTINVERT"; break;       
      case 4: str = " MERGECOPY"; break;
      case 5: str = " MERGEPAINT"; break;
      case 6: str = " NOTSRCCOPY"; break;
      case 7: str = " NOTSRCERASE"; break;
      case 8: str = " PATCOPY"; break;
      case 9: str = " PATINVERT"; break;
      case 10: str = " PATPAINT"; break;
      case 11: str = " SRCAND"; break;
      case 12: str = " SRCCOPY"; break;
      case 13: str = " SRCERASE"; break;
      case 14: str = " SRCINVERT"; break;
      case 15: str = " SRCPAINT"; break;
      case 16: str = " WHITENESS";
   }
   dc.SetTextColor(cr);
   dc.SetBkMode(TRANSPARENT);
   dc.TextOut(nLeft, nTop, str);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::DoRasterOps()

void CMainWnd::DoRasterOps(CPaintDC& dc)
{  
   int nWidth  = m_rcRop[0].Width();
   int nHeight = m_rcRop[0].Height();

   // Prepare 2 memory DCs for holding memory bitmaps
   CDC dcMem[2];
   dcMem[0].CreateCompatibleDC(&dc);
   dcMem[1].CreateCompatibleDC(&dc);
   
   // Prepare the 2 memory bitmaps
   CBitmap bmp[2];
   bmp[0].CreateCompatibleBitmap(&dc, nWidth, nHeight);
   bmp[1].CreateCompatibleBitmap(&dc, nWidth, nHeight);

   dc.SaveDC();

   // Get a bitmap of the red ellipse
   dcMem[0].SelectObject(&bmp[0]);

   dcMem[0].BitBlt(m_rcRop[0].left, m_rcRop[0].top, 
      nWidth, nHeight, &dc, 0, 0, SRCCOPY);

   // Get a bitmap of the blue ellipse
   dcMem[1].SelectObject(&bmp[1]);

   dcMem[1].BitBlt(0, 0, nWidth, nHeight, &dc, 
      m_rcRop[1].left, m_rcRop[1].top, SRCCOPY);

   //
   // Display a BitBlt ROP for each rect in the array
   //

   // BitBlt the red ellipse to new locations
   for (int i = 2; i < 17; i++)
      dc.BitBlt(m_rcRop[i].left, m_rcRop[i].top, 
         nWidth, nHeight, &dcMem[0], 0, 0, SRCCOPY);
   
   DisplayLabel(dc, 0);
   DisplayLabel(dc, 1);

   // Display the raster operations
   CombineRops(dc, 2, nWidth, nHeight, &dcMem[1], BLACKNESS);
   CombineRops(dc, 3, nWidth, nHeight, &dcMem[1], DSTINVERT);
   CombineRops(dc, 4, nWidth, nHeight, &dcMem[1], MERGECOPY);
   CombineRops(dc, 5, nWidth, nHeight, &dcMem[1], MERGEPAINT);
   CombineRops(dc, 6, nWidth, nHeight, &dcMem[1], NOTSRCCOPY);
   CombineRops(dc, 7, nWidth, nHeight, &dcMem[1], NOTSRCERASE);
   CombineRops(dc, 8, nWidth, nHeight, &dcMem[1], PATCOPY);
   CombineRops(dc, 9, nWidth, nHeight, &dcMem[1], PATINVERT);
   CombineRops(dc, 10, nWidth, nHeight, &dcMem[1], PATPAINT);
   CombineRops(dc, 11, nWidth, nHeight, &dcMem[1], SRCAND);
   CombineRops(dc, 12, nWidth, nHeight, &dcMem[1], SRCCOPY);
   CombineRops(dc, 13, nWidth, nHeight, &dcMem[1], SRCERASE);
   CombineRops(dc, 14, nWidth, nHeight, &dcMem[1], SRCINVERT);
   CombineRops(dc, 15, nWidth, nHeight, &dcMem[1], SRCPAINT);   
   CombineRops(dc, 16, nWidth, nHeight, &dcMem[1], WHITENESS);  

   dc.RestoreDC(-1);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::OnPaint()

void CMainWnd::CombineRops(CPaintDC& dc, int nIndex, int nWidth, 
                           int nHeight, CDC* pdcMem, DWORD dwRop)
{
   dc.BitBlt(m_rcRop[nIndex].left, 
      m_rcRop[nIndex].top + m_nTextHeight, 
      nWidth, nHeight - m_nTextHeight, pdcMem, 0, 0, dwRop);

   COLORREF cr;
   (dwRop == BLACKNESS) ? cr = crWhite : cr = crBlack;
   DisplayLabel(dc, nIndex, cr);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::OnPaint()

void CMainWnd::OnPaint()
{
   CPaintDC dc(this);

   // Draw source images
   int nWidth  = m_rcRop[0].Width() / 3;
   int nHeight = m_rcRop[0].bottom - m_nTextHeight;
   int nLeft   = m_rcRop[0].left + nWidth;
   int nTop    = m_rcRop[0].top + m_nTextHeight;
   
   dc.SaveDC();

   CBrush br0(crRed);
   dc.SelectObject(&br0);
   dc.Ellipse(nLeft, nTop, nLeft + nWidth, nTop + nHeight);
   
   nLeft   = m_rcRop[1].left;
   nHeight = m_rcRop[1].Height() / 3;
   nTop    = m_rcRop[1].top + nHeight;
   nWidth  = m_rcRop[1].Width();

   CBrush br1(crBlue);
   dc.SelectObject(&br1);
   dc.Ellipse(nLeft, nTop, nLeft + nWidth, nTop + nHeight);

   dc.RestoreDC(-1);

   // Display the result of all 15 named ternary raster ops
   DoRasterOps(dc);

   // Draw rects
   CBrush br(crGray);
   for (int i = 0; i < 17; i++)
      dc.FrameRect(m_rcRop[i], &br);
}

//////////////////////////////////////////////////////////////////
// CMainWnd::FillRectArray()

void CMainWnd::FillRectArray()
{  
   CRect rcClient;
   GetClientRect(&rcClient);

   int i        = 0;
   int nCurLeft = 0;
   int nCurTop  = 0;
   int nWidth   = rcClient.Width() / 6;
   int nHeight  = rcClient.Height() / 3;

   // Divide the client area into 18 rects
   for (int cy = 0; cy < 3; cy++)
   {
      for (int cx = 0; cx < 6; cx++)
      {
         CRect rc(nCurLeft, nCurTop, nWidth + nCurLeft, 
            nHeight + nCurTop);
         m_rcRop[i].CopyRect(&rc);
         nCurLeft += nWidth;
         i++;
      }
      nCurLeft = 0;
      nCurTop += nHeight;
   }
}

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   
   pFrame->Create(0, "Windows Raster Operations",
      WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);
   
   // Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

	// Show the frame window maximized
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// Declare, create, and run the application

CMyApp MyApp;

///////////////////////////////////////////////////////////////////
