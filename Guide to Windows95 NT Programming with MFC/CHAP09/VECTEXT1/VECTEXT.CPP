///////////////////////////////////////////////////////////////////
//  Module   : VECTEXT.CPP
//
//  Purpose  : Implementation of an MFC program using vector 
//             graphics and fonts.
//
//  Author   : Rob McGregor, rob_mcgregor@compuserve.com
//        
//  Date     : 04-29-96
///////////////////////////////////////////////////////////////////

#include "vectext.h"

// Message map for CMainWnd
BEGIN_MESSAGE_MAP(CMainWnd, CFrameWnd)
   ON_WM_LBUTTONDOWN()
   ON_WM_RBUTTONDOWN()
   ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////
// CMainWnd::CMainWnd() - Constructor

CMainWnd::CMainWnd()
{
   m_nCurScreen = 0;
   
   // Define an array of points
   m_apt[0].x = 200;  m_apt[0].y = 420;
   m_apt[1].x = 200;  m_apt[1].y = 200;
   m_apt[2].x = 375;  m_apt[2].y = 300;
   m_apt[3].x = 480;  m_apt[3].y = 310;
   m_apt[4].x = 590;  m_apt[4].y = 350;
   m_apt[5].x = 465;  m_apt[5].y = 200;
   m_apt[6].x = 320;  m_apt[6].y = 150;
   m_apt[7].x = 205;  m_apt[7].y = 100;
   m_apt[8].x = 115;  m_apt[8].y = 150;
   m_apt[9].x = 100;  m_apt[9].y = 175;

   // Seed random number generator with current time
   SeedRand();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::OnLButtonDown()

void CMainWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
   Invalidate();
   ProcessMouseClick(TRUE);
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnRButtonDown()

void CMainWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
   Invalidate();
   ProcessMouseClick(TRUE);
} 

///////////////////////////////////////////////////////////////////
// CMainWnd::OnEraseBkgnd()

BOOL CMainWnd::OnEraseBkgnd(CDC* pDC)
{
   // Call inherited handler
   CFrameWnd::OnEraseBkgnd(pDC);

   // Erase the client area 
   CRect rc;
   GetClientRect(&rc);

   CBrush br(crWhite);
   pDC->FillRect(&rc, &br);
   ProcessMouseClick(FALSE);

   return TRUE;
}

///////////////////////////////////////////////////////////////////
// CMainWnd::ProcessMouseClick()

void CMainWnd::ProcessMouseClick(BOOL bAdvance)
{
   // Create a client DC to draw on
   CClientDC dc(this);

   switch (m_nCurScreen)
   {
      case DO_PIXELS:
         if (!bAdvance) DoPixels(&dc);
         break;
                                         
      case DO_POINTS:                              
         if (!bAdvance) DoPoints(&dc);                       
         break;                            
                                              
      case DO_LINES:                     
         if (!bAdvance) DoLines(&dc);                      
         break;                                
                                                  
      case DO_ELLIPSES:                                    
         if (!bAdvance) DoEllipses(&dc);
         break;

      case DO_RECTS:
         if (!bAdvance) DoRects(&dc);
         break;
           
      case DO_ROUNDRECTS:
         if (!bAdvance) DoRoundRects(&dc);
         break;
           
      case DO_REGIONS:
         if (!bAdvance) DoRegions(&dc);
         break;
      
      case DO_REGIONSUNION:
         if (!bAdvance) DoRegionsUnion(&dc);
         break;
      
      case DO_REGIONSDIFFERENCE:
         if (!bAdvance) DoRegionsDifference(&dc);
         break;
      
      case DO_REGIONSINTERSECT:
         if (!bAdvance) DoRegionsIntersect(&dc);
         break;
      
      case DO_BEZIER:
         if (!bAdvance) DoBezier(&dc);
         break;
           
      case DO_POLYGON:
         if (!bAdvance) DoPolygon(&dc);
         break;
     
      case DO_POLYLINE:
         if (!bAdvance) DoPolyLine(&dc);
         break;

      case DO_METAFILE:
         if (!bAdvance) DoMetafile(&dc);
         break;

      case DO_TEXTARIAL:
         if (!bAdvance) DoTextArial(&dc);
         break;

      case DO_TEXTROMAN:
         if (!bAdvance) DoTextRoman(&dc);
         break;

      case DO_TEXTSYSTEM:
         if (!bAdvance) DoTextSystem(&dc);
         break;
   }

   if (bAdvance)
   {
      // Roll over to zero on max
      if (m_nCurScreen > MAXCLICKS - 1)
         m_nCurScreen = 0;
      else
         m_nCurScreen += 1;
   }
}

///////////////////////////////////////////////////////////////////
//  H e l p e r    M e t h o d s
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CMainWnd::DisplayLogFont() 

void CMainWnd::DisplayLogFont(CClientDC* pDC, CString sFont)
{
   // Draw various sizes of fonts
   UINT uSize      = 2;   // Starting point size
   int  cyDrawHere = 30;  // Start vertical drawing text here
   CFont* pfntOld  = 0;

   // 16 lines of text, font sizes from 2 to 32 points
   for (int i = 0; i < 16; i++)
   {
      // Create a new font and init a LOGFONT structure
      CFont      fnt;          
      LOGFONT    lf;          
      TEXTMETRIC tm;

      memset(&lf, 0, sizeof(LOGFONT));

      // Set initial font typeface name and font size
      lstrcpy(lf.lfFaceName, sFont);

      int cyPixels = pDC->GetDeviceCaps(LOGPIXELSY);
      lf.lfHeight  = -MulDiv(uSize, cyPixels, 72); 

      // Create the new font
      fnt.CreateFontIndirect(&lf);
      
      // Get the text metrics
      pDC->GetTextMetrics(&tm);
      cyDrawHere += abs(lf.lfHeight) + tm.tmExternalLeading;

      // Make the new font current in the DC
      pfntOld = pDC->SelectObject(&fnt);

      // Draw a line of text
      CString str;
      str.Format("Font name: %s, size: %d points", 
                 lf.lfFaceName, uSize);
      pDC->TextOut(5, cyDrawHere, str);

      uSize += 2;
   }
   // Restore the previous font to the DC
   pDC->SelectObject(pfntOld);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::GetRandomColor() 

COLORREF CMainWnd::GetRandomColor()
{
   return RGB(MapRand(255), MapRand(255), MapRand(255));
}
   
///////////////////////////////////////////////////////////////////
// CMainWnd::MapRand() - Maps random number to nMax

UINT CMainWnd::MapRand(UINT nMax)
{
   // Assumes the random number generator was seeded with 
   // SeedRand() in the constructor!
   
   // Map a random number to nMax
   int   nRand   = rand();
   float fMap    = (float) nMax / RAND_MAX;
   float fRetVal = (float) nRand * fMap + 0.5F;

   return (UINT)fRetVal;
}

///////////////////////////////////////////////////////////////////
// G r a p h i c s    M e t h o d s
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CMainWnd::DoBezier() 

void CMainWnd::DoBezier(CClientDC* pDC)
{
   // Create a label 
   CString str = "Bezier with ten control points:";
   pDC->TextOut(5, 5, str);

   // Draw points
   for (int i = 0; i < 10; i++)
      pDC->Ellipse(m_apt[i].x - 4, m_apt[i].y - 4, 
                   m_apt[i].x + 4, m_apt[i].y + 4);

   // Create new pens
   CPen penBlue;
   CPen penRed;

   penBlue.CreatePen(PS_DOT, 1, crBlue);
   penRed.CreatePen(PS_SOLID, 1, crRed);
   
   // Select a new pen into the device context, and save 
   // the old pen to restore on clean up...
   CPen* ppenOld;
   ppenOld = pDC->SelectObject(&penBlue);

   // Draw lines with blue pen to connect control points 
   pDC->Polyline(m_apt, 10);
   
   // Draw Bezier curve with red pen
   pDC->SelectObject(&penRed);
   pDC->PolyBezier(m_apt, 10);

   // Leave things as we found them (clean up)
   pDC->SelectObject(ppenOld);

}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoEllipses() 

void CMainWnd::DoEllipses(CClientDC* pDC)
{
   // Create a label 
   CString str = "Ellipses filled with hatch brushes:";
   pDC->TextOut(5, 5, str);

   // Subdivide the display into 6 sections
   CRect  rc;
   CRect  arcSection[4][3];

   GetClientRect(&rc);
   int cx = rc.right / 3;
   int cy = (rc.bottom - 25) / 2;

   int nHeight = cy;

   for (int x = 0; x < 2; x++)
   {
      int nWidth = cx;
      for (int y = 0; y < 3; y++)
      {
         arcSection[x][y].left   = nWidth - cx;
         arcSection[x][y].top    = nHeight - cy + 25;
         arcSection[x][y].right  = arcSection[x][y].left + cx;
         arcSection[x][y].bottom = arcSection[x][y].top + cy;
         
         nWidth += cx;
      }
      nHeight += cy;
   }

   // Six different hatch brush styles
   cy = 25;
   int nHatchStyle = 0;

   for (x = 0; x < 2; x++)
   {
      for (int y = 0; y < 3; y++)
      {
         /*==================================================
            From WINGDI.H:

            // Hatch Styles 
            #define HS_HORIZONTAL    0    // -----
            #define HS_VERTICAL      1    // |||||
            #define HS_FDIAGONAL     2    // \\\\\
            #define HS_BDIAGONAL     3    // /////
            #define HS_CROSS         4    // +++++
            #define HS_DIAGCROSS     5    // xxxxx
         ===================================================*/

         // Create a hatch brush
         CBrush br(nHatchStyle, crRed);   

         // Select the new brush into the device context, and save 
         // the old brush to restore on clean up...
         CBrush* pbrOld;
         pbrOld = pDC->SelectObject(&br);

         // Draw an ellipse on the DC
         pDC->Ellipse(arcSection[x][y]);
         nHatchStyle++;

         // Leave things as we found them (clean up)
         pDC->SelectObject(pbrOld);
      }
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoLines() -  Draws all line styles

void CMainWnd::DoLines(CClientDC* pDC)
{
   // Create a label 
   CString str = "Pen Line Styles:";
   pDC->TextOut(5, 5, str);
   
   const int nLineLength = 600;

   // Six different pen styles
   int cy = 25;
   for (int nLineStyle = 0; nLineStyle < 6; nLineStyle++)
   {
      /*===========================================
         From WINGDI.H:

         #define PS_SOLID        0
         #define PS_DASH         1     // -------  
         #define PS_DOT          2     // .......  
         #define PS_DASHDOT      3     // _._._._  
         #define PS_DASHDOTDOT   4     // _.._.._  
         #define PS_NULL         5
      =============================================*/

      // Create a new pen
      CPen penBlue;

      // Pick the current pen style
      penBlue.CreatePen(nLineStyle, 1, crBlue);      

      // Select the new pen into the device context, and save 
      // the old pen to restore on clean up...
      CPen* ppenOld;
      ppenOld = pDC->SelectObject(&penBlue);

      // Draw on the DC
      pDC->MoveTo(10, cy);
      pDC->LineTo(10 + nLineLength, cy);
      cy += 20; 

      // Leave things as we found them (clean up)
      pDC->SelectObject(ppenOld);
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoPixels() - Draws random colored pixels

void CMainWnd::DoPixels(CClientDC* pDC)
{
   // Get the client area rectangle
   CRect rc;
   GetClientRect(&rc);

   // Display 500 points as pixels in the rect 
   // w/random positions and colors
   //
   for (int i = 0; i < 500; i++)
   {
      // Position
      int cx = MapRand(rc.Width());
      int cy = MapRand(rc.Height());

      // Display the pixel
      pDC->SetPixel(cx, cy, GetRandomColor());
   }

   // Create a label 
   int nPrev = pDC->SetBkMode(TRANSPARENT);   

   CString str = "Points as Pixels:";
   pDC->TextOut(5, 5, str);   
   pDC->SetBkMode(nPrev);   
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoPoints() - Draws random colored points as ellipses

void CMainWnd::DoPoints(CClientDC* pDC)
{
   // Get the client area rectangle
   CRect rc;
   GetClientRect(&rc);

   // Display 500 points as ellipses in the rect 
   // w/random positions and colors
   //
   for (int i = 0; i < 500; i++)
   {
      // Position
      int cx = MapRand(rc.Width());
      int cy = MapRand(rc.Height());

      // Create a new pen and set the current pen style
      CPen pen;
      pen.CreatePen(PS_SOLID, 1, GetRandomColor());      

      // Select the new pen into the device context, and save 
      // the old pen to restore on clean up...
      CPen* ppenOld;
      ppenOld = pDC->SelectObject(&pen);

      // Display the point as a 4 x 4 pixel ellipse
      pDC->Ellipse(cx - 2, cy - 2, cx + 2, cy + 2);
      
      // Leave things as we found them (clean up)
      pDC->SelectObject(ppenOld);   
   }

   // Create a label 
   int nPrev = pDC->SetBkMode(TRANSPARENT);   

   CString str = "Points as ellipses:";
   pDC->TextOut(5, 5, str);   
   pDC->SetBkMode(nPrev);   
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoPolygon() 

void CMainWnd::DoPolygon(CClientDC* pDC)
{
   // Create a label 
   CString str = "A polygon with ten vertices:";
   pDC->TextOut(5, 5, str);

   // Create a new pen and brush
   CPen penBlue;
   penBlue.CreatePen(PS_SOLID, 1, crBlue);
   
   CBrush br(crGray);
   
   // Select a new pen & brush into the device context, and save 
   // the old objects to restore on clean up...
   CPen* ppenOld;
   ppenOld = pDC->SelectObject(&penBlue);

   CBrush* pbrOld;
   pbrOld = pDC->SelectObject(&br);

   // Draw lines with blue pen to connect control points 
   pDC->Polygon(m_apt, 10);
   
   // Leave things as we found them (clean up)
   pDC->SelectObject(ppenOld);
   pDC->SelectObject(pbrOld);

   // Draw points
   for (int i = 0; i < 10; i++)
      pDC->Ellipse(m_apt[i].x - 4, m_apt[i].y - 4, 
                   m_apt[i].x + 4, m_apt[i].y + 4);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoPolyLine() 

void CMainWnd::DoPolyLine(CClientDC* pDC)
{
   // Create a label 
   CString str = "A polyline with 10 vertices:";
   pDC->TextOut(5, 5, str);

   // Draw points
   for (int i = 0; i < 10; i++)
      pDC->Ellipse(m_apt[i].x - 4, m_apt[i].y - 4, 
                   m_apt[i].x + 4, m_apt[i].y + 4);

   // Create a new pen
   CPen penRed;
   penRed.CreatePen(PS_SOLID, 1, crRed);
   
   // Select a new pen into the device context, and save 
   // the old pen to restore on clean up...
   CPen* ppenOld;
   ppenOld = pDC->SelectObject(&penRed);

   // Draw lines with red pen to connect vertex points 
   pDC->Polyline(m_apt, 10);
   
   // Leave things as we found them (clean up)
   pDC->SelectObject(ppenOld);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRects() 

void CMainWnd::DoRects(CClientDC* pDC)
{
   // Create a label 
   CString str = "Rectangles filled with hatch brushes:";
   pDC->TextOut(5, 5, str);

   // Subdivide the display into 6 sections
   CRect  rc;
   CRect  arcSection[4][3];

   GetClientRect(&rc);
   int cx = rc.right / 3;
   int cy = (rc.bottom - 25) / 2;

   int nHeight = cy;

   for (int x = 0; x < 2; x++)
   {
      int nWidth = cx;
      for (int y = 0; y < 3; y++)
      {
         arcSection[x][y].left   = nWidth - cx;
         arcSection[x][y].top    = nHeight - cy + 25;
         arcSection[x][y].right  = arcSection[x][y].left + cx;
         arcSection[x][y].bottom = arcSection[x][y].top + cy;
         
         nWidth += cx;
      }
      nHeight += cy;
   }

   // Six different hatch brush styles
   cy = 25;
   int nHatchStyle = 0;

   for (x = 0; x < 2; x++)
   {
      for (int y = 0; y < 3; y++)
      {
         /*==================================================
            From WINGDI.H:

            // Hatch Styles 
            #define HS_HORIZONTAL    0    // -----
            #define HS_VERTICAL      1    // |||||
            #define HS_FDIAGONAL     2    // \\\\\
            #define HS_BDIAGONAL     3    // /////
            #define HS_CROSS         4    // +++++
            #define HS_DIAGCROSS     5    // xxxxx
         ===================================================*/

         // Create a hatch brush
         CBrush br(nHatchStyle, crRed);   

         // Select the new brush into the device context, and save 
         // the old brush to restore on clean up...
         CBrush* pbrOld;
         pbrOld = pDC->SelectObject(&br);

         // Draw an ellipse on the DC
         pDC->Rectangle(arcSection[x][y]);
         nHatchStyle++;

         // Leave things as we found them (clean up)
         pDC->SelectObject(pbrOld);
      }
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRegions() 

void CMainWnd::DoRegions(CClientDC* pDC)
{
   // Create a label 
   CString str = "Two regions: red and blue";
   pDC->TextOut(5, 5, str);

   // Create a region composed of an ellipse and a rectangle
   CRgn rgn1;
   CRgn rgn2;
   CRgn rgn3;

   rgn1.CreateEllipticRgn(25, 25, 100, 200);
   rgn2.CreateRectRgn(60, 125, 175, 250);

   // Create new brushes
   CBrush br1(crRed);   
   CBrush br2(crBlue);   

   // Draw the regions
   pDC->FillRgn(&rgn1, &br1);
   pDC->FillRgn(&rgn2, &br2);

   // Clean up
   rgn1.DeleteObject();
   rgn2.DeleteObject();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRegionsDifference() 

void CMainWnd::DoRegionsDifference(CClientDC* pDC)
{
   // Create a label 
   CString str = "Regions: Difference (red - blue)";
   pDC->TextOut(5, 5, str);

   // Create a region composed of an ellipse and a rectangle
   CRgn rgn1;
   CRgn rgn2;
   CRgn rgn3;

   rgn1.CreateEllipticRgn(25, 25, 100, 200);
   rgn2.CreateRectRgn(60, 125, 175, 250);

   // Default 3rd region
   CRect rc(0, 0, 0, 0);
   rgn3.CreateRectRgnIndirect(&rc);

   // Combine the regions as a union
   if (rgn3.CombineRgn(&rgn1, &rgn2, RGN_DIFF) == ERROR) 
      return;

   // Create a new brush
   CBrush br(crRed);   

   // Draw the new region
   pDC->FillRgn(&rgn3, &br);
   
   // Clean up
   rgn1.DeleteObject();
   rgn2.DeleteObject();
   rgn3.DeleteObject();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRegionsIntersect() 

void CMainWnd::DoRegionsIntersect(CClientDC* pDC)
{
   // Create a label 
   CString str = "Regions: Intersection";
   pDC->TextOut(5, 5, str);

   // Create a region composed of an ellipse and a rectangle
   CRgn rgn1;
   CRgn rgn2;
   CRgn rgn3;

   rgn1.CreateEllipticRgn(25, 25, 100, 200);
   rgn2.CreateRectRgn(60, 125, 175, 250);

   // Default 3rd region
   CRect rc(0, 0, 0, 0);
   rgn3.CreateRectRgnIndirect(&rc);

   // Combine the regions as a union
   if (rgn3.CombineRgn(&rgn1, &rgn2, RGN_AND) == ERROR) 
      return;

   // Create a new brush
   CBrush br(crMagenta);   

   // Draw the new region
   pDC->FillRgn(&rgn3, &br);
   
   // Clean up
   rgn1.DeleteObject();
   rgn2.DeleteObject();
   rgn3.DeleteObject();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRegionsUnion() 

void CMainWnd::DoRegionsUnion(CClientDC* pDC)
{
   // Create a label 
   CString str = "Regions: Union (red + blue)";
   pDC->TextOut(5, 5, str);

   // Create a region composed of an ellipse and a rectangle
   CRgn rgn1;
   CRgn rgn2;
   CRgn rgn3;

   rgn1.CreateEllipticRgn(25, 25, 100, 200);
   rgn2.CreateRectRgn(60, 125, 175, 250);

   // Default 3rd region
   CRect rc(0, 0, 0, 0);
   rgn3.CreateRectRgnIndirect(&rc);

   // Combine the regions as a union
   if (rgn3.CombineRgn(&rgn1, &rgn2, RGN_OR) == ERROR) 
      return;

   // Create a new brush
   CBrush br(crMagenta);   

   // Draw the new region
   pDC->FillRgn(&rgn3, &br);
   
   // Clean up
   rgn1.DeleteObject();
   rgn2.DeleteObject();
   rgn3.DeleteObject();
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoRoundRects() 

void CMainWnd::DoRoundRects(CClientDC* pDC)
{
   // Create a label 
   CString str = "Rounded rectangles filled with colored brushes:";
   pDC->TextOut(5, 5, str);

   // Subdivide the display into 6 sections
   CRect  rc;
   CRect  arcSection[4][3];

   GetClientRect(&rc);
   int cx = rc.right / 3;
   int cy = (rc.bottom - 25) / 2;

   int nHeight = cy;

   for (int x = 0; x < 2; x++)
   {
      int nWidth = cx;
      for (int y = 0; y < 3; y++)
      {
         arcSection[x][y].left   = nWidth - cx;
         arcSection[x][y].top    = nHeight - cy + 25;
         arcSection[x][y].right  = arcSection[x][y].left + cx;
         arcSection[x][y].bottom = arcSection[x][y].top + cy;
         
         nWidth += cx;
      }
      nHeight += cy;
   }

   // Six different, randomly colored brushes
   cy = 25;

   for (x = 0; x < 2; x++)
   {
      for (int y = 0; y < 3; y++)
      {
         // Create a new randomly colored brush
         CBrush br(GetRandomColor());

         // Select the new brush into the device context, and save 
         // the old brush to restore on clean up...
         CBrush* pbrOld;
         pbrOld = pDC->SelectObject(&br);

         // Draw a rounded rect on the DC
         pDC->RoundRect(arcSection[x][y], CPoint(50, 50));

         // Leave things as we found them (clean up)
         pDC->SelectObject(pbrOld);
      }
   }
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoTextArial() 

void CMainWnd::DoTextArial(CClientDC* pDC)
{
   // Create a label 
   CString str = "Text output using the Arial font (TTF):";
   pDC->TextOut(5, 5, str);

   DisplayLogFont(pDC, "Arial");
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoTextRoman() 

void CMainWnd::DoTextRoman(CClientDC* pDC)
{
   // Create a label 
   CString str = "Text output using the Time New Roman font (TTF):";
   pDC->TextOut(5, 5, str);

   DisplayLogFont(pDC, "Times New Roman");
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoTextSystem() 

void CMainWnd::DoTextSystem(CClientDC* pDC)
{
   // Create a label 
   CString strLbl = "Generic text information on the system font:";
   pDC->TextOut(5, 5, strLbl);

   // Select the system font into the DC
   HFONT hFont = (HFONT)::GetStockObject(SYSTEM_FONT);
   CFont fnt;
   CFont* pFont = fnt.FromHandle(hFont);
   CFont* pfntOld = pDC->SelectObject(pFont);

   // Get some info about the current font
   TEXTMETRIC tm;
   pDC->GetTextMetrics(&tm);

   UINT nCurLineHeight = 40;

   // Create an array of strings to display the TEXTMETRIC data
   // Label strings
   CString str[42];
   
   str[0] = "Height";    
   str[1] = "Ascent";           
   str[2] = "Descent";          
   str[3] = "InternalLeading";  
   str[4] = "ExternalLeading";  
   str[5] = "AveCharWidth";     
   str[6] = "MaxCharWidth";     
   str[7] = "Weight";           
   str[8] = "Overhang";         
   str[9] = "DigitizedAspectX"; 
   str[10] = "DigitizedAspectY";
   str[11] = "FirstChar";       
   str[12] = "LastChar";        
   str[13] = "DefaultChar";     
   str[14] = "BreakChar";       
   str[15] = "Italic";          
   str[16] = "Underlined";      
   str[17] = "StruckOut";       
   str[18] = "Pitch";           
   str[19] = "Family";          
   str[20] = "CharSet";         
   
   // Data strings
   str[21].Format(" = %d", tm.tmHeight);          
   str[22].Format(" = %d", tm.tmAscent);          
   str[23].Format(" = %d", tm.tmDescent);         
   str[24].Format(" = %d", tm.tmInternalLeading); 
   str[25].Format(" = %d", tm.tmExternalLeading); 
   str[26].Format(" = %d", tm.tmAveCharWidth);    
   str[27].Format(" = %d", tm.tmMaxCharWidth);    
   str[28].Format(" = %d", tm.tmWeight);          
   str[29].Format(" = %d", tm.tmOverhang);        
   str[30].Format(" = %d", tm.tmDigitizedAspectX);
   str[31].Format(" = %d", tm.tmDigitizedAspectY);
   str[32].Format(" = '%c'", tm.tmFirstChar);       
   str[33].Format(" = '%c'", tm.tmLastChar);        
   str[34].Format(" = '%c'", tm.tmDefaultChar);     
   str[35].Format(" = '%c'", tm.tmBreakChar);       
   str[36].Format(" = %d", tm.tmItalic);          
   str[37].Format(" = %d", tm.tmUnderlined);      
   str[38].Format(" = %d", tm.tmStruckOut);       
   str[39].Format(" = %d", tm.tmPitchAndFamily & TMPF_FIXED_PITCH);  
   str[40].Format(" = %d", tm.tmPitchAndFamily & 0xF0);  
   str[41].Format(" = %d", tm.tmCharSet);

   // Display strings 0-20
   for (int i = 0; i < 21; i++)
   {
      pDC->TextOut(20, nCurLineHeight, str[i]);
      nCurLineHeight += tm.tmHeight;
   }

   // Reset line height
   nCurLineHeight = 40;

   //
   // Now we need to determine the distance that the data strings 
   // should move to the right to align the data evenly. 
   //
   // str[9] is the longest string, so we calculate the width + 5 
   // to space the = signs nicely.
   //

   UINT nLeft = 20 + tm.tmAveCharWidth * (str[9].GetLength() + 2);
   
   // Display strings 21-41
   for (i = 21; i < 42; i++)
   {
      pDC->TextOut(nLeft, nCurLineHeight, str[i]);
      nCurLineHeight += tm.tmHeight;
   }
   if (pfntOld)
      pDC->SelectObject(pfntOld);
}

///////////////////////////////////////////////////////////////////
// CMainWnd::DoMetafile() 

void CMainWnd::DoMetafile(CClientDC* pDC)
{
   // Get the client size
   CRect rc;
   GetClientRect(&rc);
 
   // Create and initialize an enhanced metafile
   CMetaFileDC dc;

   BOOL bCreated = 
   dc.CreateEnhanced(
      pDC,              // use the client area DC for reference
      "metatest.emf\0", // file name
      0,                // the bounding rect for the image (HIMETRIC)

      "VECTEXT1 Application\0Example enhanced metafile.\0\0"
   );

  if (!bCreated) return;
      
   // Set the initial drawing position
   dc.MoveTo(0, 0);

   // Draw a random number of lines into the metafile
   UINT nCount = MapRand(100);
   for (UINT i = 0; i < nCount; i++)
   {
      // Create a pen w/random color and width
      CPen pen;
      pen.CreatePen(PS_SOLID, MapRand(9) + 1, GetRandomColor());
      
      // Select the new pen into the device context, and save 
      // the old pen to restore on clean up...
      CPen* ppenOld = dc.SelectObject(&pen);

      // Draw a random line
      dc.LineTo(MapRand(1000), MapRand(1000));
      
      // Restore the old brush
      dc.SelectObject(ppenOld);   
   }

   // Close the enhanced metafile and get the handle. This also 
   // creates the disk file METATEST.EMF...
   HENHMETAFILE hemf = dc.CloseEnhanced();

   // Save the current state of the client DC
   pDC->SaveDC();
   
   // Set mapping mode to MM_ANISOTROPIC to allow the image to 
   // stretch to fit the client area
   pDC->SetMapMode(MM_ANISOTROPIC);
   
   // Set the logical window size
   pDC->SetWindowExt(rc.Width(), rc.Height());

   // Set the physical window size
   pDC->SetViewportExt(rc.Width(), rc.Height());

   // Play the metafile back into the client DC
   pDC->PlayMetaFile(hemf, &rc);

   // Restore the saved client DC state
   pDC->RestoreDC(-1);

   // Typically you would store the metafile handle for use with 
   // other application methods, but we don't need it anymore for 
   // this demo, so...
   
   // Destroy the metafile
   if (hemf)
      ::DeleteEnhMetaFile(hemf);

   // Create a label 
   CString str = "Metafile TESTMETA.EMF:";
   pDC->TextOut(5, 5, str);

}

///////////////////////////////////////////////////////////////////
//  C M y A p p    M e t h o d s
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// CMyApp::InitInstance - overrides CWinApp::InitInstance

BOOL CMyApp::InitInstance()
{
	// Allocate a new frame window object
	CMainWnd* pFrame = new CMainWnd;

	// Initialize the frame window
   pFrame->Create(0, 
      "Vector Graphics Demo - Click the Mouse Buttons",
      WS_POPUPWINDOW | WS_DLGFRAME,
      CRect(0, 0, 640, 480));

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
