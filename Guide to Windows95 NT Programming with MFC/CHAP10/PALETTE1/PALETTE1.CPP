///////////////////////////////////////////////////////////////////
//  Module   : PALETTE1.CPP
//
//  Purpose  : Implementation of a minimal MFC palette program.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 05-29-96
///////////////////////////////////////////////////////////////////

#include "palette1.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CMainFrame)
   ON_WM_PAINT()
   ON_WM_QUERYNEWPALETTE()
   ON_WM_PALETTECHANGED()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - constructor

CMainWnd::CMainWnd()
{ 
   // Define the 256-color logical palette
   m_pLP = (LPLOGPALETTE) new char[sizeof(LOGPALETTE) +
      256 * sizeof(PALETTEENTRY)];
  
   Fill4WayPalette();
   
   // Create the palette
   m_pal.CreatePalette(m_pLP);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::~CMainWnd() - destructor

CMainWnd::~CMainWnd()
{ 
   if (m_pLP) 
      delete (m_pLP);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnPaint()

void CMainWnd::OnPaint()
{ 
	CPaintDC dc(this); // device context for painting
   
   // Call inherited handler
   CFrameWnd::OnPaint();

   // Display the 4 color washes 
   Display4WayPalette(&dc, m_pal);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnQueryNewPalette()

BOOL CMainWnd::OnQueryNewPalette()
{
   // Set the background palette
   CClientDC dc(this);

   CPalette* ppalOld = dc.SelectPalette(&m_pal, FALSE);
   int nColorsChanged = dc.RealizePalette();
   dc.SelectPalette(ppalOld, FALSE);
   
   // Redraw the window if any colors were changed
   if (nColorsChanged)
   {
      Invalidate();
      UpdateWindow();
   }
   return CFrameWnd::OnQueryNewPalette();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnPaletteChanged()

void CMainWnd::OnPaletteChanged(CWnd* pFocusWnd)
{
   if (this == pFocusWnd)
      return;
   
   // Set the background palette
   CClientDC dc(this);

   CPalette* ppalOld = dc.SelectPalette(&m_pal, FALSE);
   int nColorsChanged = dc.RealizePalette();
   
   // Redraw the window if any colors were changed
   if (nColorsChanged)
   {
      Invalidate();
      UpdateWindow();
   }
   dc.SelectPalette(ppalOld, FALSE);    
}

///////////////////////////////////////////////////////////////////
// CMainWnd::Display4WayPalette()

void CMainWnd::Display4WayPalette(CPaintDC* pDC, CPalette& pal)
{
   // Get client width and height for drawing purposes
   int nClientWidth  = GetClientWidth();
   int nClientHeight = GetClientHeight();

   // Set mapping mode to MM_ANISOTROPIC
   pDC->SaveDC();
   pDC->SetMapMode(MM_ANISOTROPIC);
   
   // Set the logical window size
   UINT uLogSize = 1024;
   pDC->SetWindowExt(uLogSize, uLogSize);

   // Set the physical window size
   pDC->SetViewportExt(nClientWidth, nClientHeight);

   // Size of 4 screen-areas
   int nRectWidth  = uLogSize / 2;  // half of the logical window
   int nRectHeight = uLogSize / 2;  // half of the logical window

   // Divide into 64 sub screen-areas
   int cx = nRectWidth / 8;   // 1/64 of the logical window
   int cy = nRectHeight / 8;  // 1/64 of the logical window

   
   // Display the 4 color washes
   int iColorIndex = 0;

   for (int nArea = 0; nArea < 4; nArea++)
   {
      // Determine which of the 4 areas to paint
      CRect rc;
      switch (nArea)
      {
         case 0:
            rc.SetRect(0, 0, nRectWidth, nRectHeight);
            break;

         case 1:
            rc.SetRect(nRectWidth, 0, uLogSize, nRectHeight);
            break;                                  

         case 2:
            rc.SetRect(0, nRectHeight, uLogSize, uLogSize);
            break;

         case 3:
            rc.SetRect(nRectWidth, nRectHeight, uLogSize, uLogSize);
            break;
      }

      // Get the palette colors
      PALETTEENTRY pe[256];
      int nColors = pal.GetPaletteEntries(0, 256, pe);

      int nCurRight  = rc.left;
      int nCurBottom = rc.top + cy;
      pDC->Rectangle(&rc);

      // Create palette wash on the client area
      for (int i = 0; i < 8; i ++)
      {
         for (int j = 0; j < 8; j ++)
         {
            nCurRight += cx;
            CRect rc(j * cx + rc.left, i * cy + rc.top, 
               nCurRight, nCurBottom);

            // Create a brush of the color in the current palette index
            CBrush br(
               RGB(pe[iColorIndex].peRed, 
                   pe[iColorIndex].peGreen, 
                   pe[iColorIndex].peBlue));

            pDC->FillRect(&rc, &br);

            iColorIndex++;
         }
         nCurRight = rc.left;
         nCurBottom += cy;
      }
   }
   pDC->RestoreDC(-1);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::Fill4WayPalette()

void CMainWnd::Fill4WayPalette()
{
   m_pLP->palVersion    = 0x300; 
   m_pLP->palNumEntries = 256; 
 
   // Four color washes
   UINT iColorIndex = 0;
   for (int nColor = 0; nColor < 4; nColor++)
   {
      // Generate the palette colors
      for (UINT i = iColorIndex; i < iColorIndex + 64; i++)
      {
         switch (nColor)
         {
            case 0:
               m_pLP->palPalEntry[i].peRed   = (BYTE)i * 4;    
               m_pLP->palPalEntry[i].peGreen = 0;    
               m_pLP->palPalEntry[i].peBlue  = 0;    
               m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
               break;

            case 1:
               m_pLP->palPalEntry[i].peRed   = 0;    
               m_pLP->palPalEntry[i].peGreen = (BYTE)i * 4;    
               m_pLP->palPalEntry[i].peBlue  = 0;    
               m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
               break;

            case 2:
               m_pLP->palPalEntry[i].peRed   = 0;    
               m_pLP->palPalEntry[i].peGreen = 0;    
               m_pLP->palPalEntry[i].peBlue  = (BYTE)i * 4;    
               m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
               break;

            case 3:
               m_pLP->palPalEntry[i].peRed   = 0;    
               m_pLP->palPalEntry[i].peGreen = (BYTE)i * 4;    
               m_pLP->palPalEntry[i].peBlue  = (BYTE)i * 4;    
               m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
               break;
         }
      }
      iColorIndex += 64;
   }
}                   

///////////////////////////////////////////////////////////////////
// CPaletteApp::InitInstance - overrides CWinApp::InitInstance

BOOL CPaletteApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->Create(0, _T("A Basic MFC Palette Program"),
                  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN);

	// Assign the frame window as the app's main frame window
   this->m_pMainWnd = pFrame;

   // Center and decorate
   pFrame->CenterWindow();
   pFrame->SetClientBackColor(COLOR_APPWORKSPACE);

	// Show the frame window
   pFrame->ShowWindow(m_nCmdShow);
   pFrame->UpdateWindow();

   return TRUE;
}

// Declare, create, and run the application
CPaletteApp MyApp;

///////////////////////////////////////////////////////////////////
