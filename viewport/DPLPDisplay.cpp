// DPLPDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "DPLPDisplay.h"
#include "round.h"
#include "geometry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DECLARE_MESSAGE(UWM_MOUSEMOVE)
DECLARE_MESSAGE(UWM_MOUSEDRAG)
DECLARE_MESSAGE(UWM_MOUSEDRAGSTART)
DECLARE_MESSAGE(UWM_MOUSEDRAGEND)

/////////////////////////////////////////////////////////////////////////////
// CDPLPDisplay

CDPLPDisplay::CDPLPDisplay()
{
 dx = 50;
 dy = 50;
 Ldx = 50;
 Ldy = 50;
 WindowOrg = CPoint(0, 0);
 ViewportOrg = CPoint(0, 0);
 circles = FALSE;
 GridLineStyle = PS_DASH;
}

CDPLPDisplay::~CDPLPDisplay()
{
}


BEGIN_MESSAGE_MAP(CDPLPDisplay, CStatic)
        //{{AFX_MSG_MAP(CDPLPDisplay)
        ON_WM_MOUSEMOVE()
        ON_WM_PAINT()
        ON_WM_LBUTTONDOWN()
        ON_WM_LBUTTONUP()
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDPLPDisplay message handlers

void CDPLPDisplay::OnMouseMove(UINT nFlags, CPoint point) 
   {
    CPoint tp = point;
    DPtoLP(tp);

    if(GetCapture() != NULL)
       { /* has capture */
        GetParent()->SendMessage(UWM_MOUSEDRAG, (WPARAM)&point, (LPARAM)&tp);
       } /* has capture */
    GetParent()->SendMessage(UWM_MOUSEMOVE, (WPARAM)&point, (LPARAM)&tp);
        
    CStatic::OnMouseMove(nFlags, point);
   }

void CDPLPDisplay::OnPaint() 
   {
    CPaintDC dc(this); // device context for painting
    CRect r;
    GetClientRect(&r);
        

    dc.FillSolidRect(&r, RGB(255,255,255));
    CPen gray(PS_SOLID, 0, RGB(192, 192, 192));
    dc.SelectObject(&gray);
    for(int x = 0; x < r.right; x += dx)
       { /* scan x */
        dc.MoveTo(x, r.top);
        dc.LineTo(x, r.bottom);
       } /* scan x */

    for(int y = 0; y < r.bottom; y += dy)
       { /* scan y */
        dc.MoveTo(r.left, y);
        dc.LineTo(r.right, y);
       } /* scan y */
        
    CRgn rgn;
    VERIFY(rgn.CreateRectRgn(r.left, r.top, r.right, r.bottom));

    int result = dc.SelectClipRgn(&rgn, RGN_COPY);
    //ASSERT(result != NULLREGION);
    PrepareDC(dc);
    
    CPen logical(GridLineStyle, 0, RGB(255, 0, 0));
    dc.SetBkMode(TRANSPARENT);

    dc.SelectObject(&logical);
    
    CRect edge;
    GetClientRect(&edge);
    dc.DPtoLP(&edge);

    // Figure out the lowest limit
    // Compute the low and high values by computing the
    // values which contains the actual visible
    // rectangle

#define RANGE(v, start, end, delta) v = (start); (start) < (end) ? v < (end) : v > (end); (start) < (end) ? v += (delta) : v -= (delta)
    
    span(edge.left, edge.right, Ldx);
    span(edge.top, edge.bottom, Ldy);

    //********************************************************************************
    // DRAW GRID LINES
    //********************************************************************************
    if(gridlines)
       { /* grid lines */
        /*****************************************************************************
          |   |   |   |
          |   |   |   |
          |   |   |   |
        *****************************************************************************/
        for(RANGE(x, edge.left, edge.right, Ldx))
           { /* scan x */
            dc.MoveTo(x, edge.top);
            dc.LineTo(x, edge.bottom);
           } /* scan x */

        /*****************************************************************************
          ----------------------------

          ----------------------------

          ----------------------------
        *****************************************************************************/
        for(RANGE(y, edge.top, edge.bottom, Ldy))
           { /* scan y */
            dc.MoveTo(edge.left, y);
            dc.LineTo(edge.right, y);
           } /* scan y */
       } /* grid lines */

    //********************************************************************************
    // DRAW CIRCULAR LINES
    //********************************************************************************
    if(circles)
       { /* circles */
        // Make sure the circles appear on the window, no matter what the scaling
        // or displacement 
        // Compute the maximum diagonal from the origin to each corner of the
        // rectangle
        CRect r;
        GetClientRect(&r);
        DPtoLP(r);

        int length = 0;
        MaxDiagonal(length, CPoint(0, 0), CPoint(r.left, r.top));
        MaxDiagonal(length, CPoint(0, 0), CPoint(r.right, r.top));
        MaxDiagonal(length, CPoint(0, 0), CPoint(r.left, r.bottom));
        MaxDiagonal(length, CPoint(0, 0), CPoint(r.right, r.bottom));
        length = roundUp(length, Ldx);

        // Note that in some scalings, the gap between the circles will
        // be greater than the window size; in this case, we halve the gap
        // until we know that we can see some number of circles on the
        // window

        int dr = Ldx; // get logical delta
        while(dr > abs(r.Width()))
           dr /= 2;

        if(dr == 0)
           dr = 1; // make sure loop will terminate
        
        dc.SelectStockObject(HOLLOW_BRUSH);

        for(int radius = dr; radius < length; radius += dr)
           { /* circles */
            CRect circle(-radius, -radius, radius, radius);
            circle.NormalizeRect();
            dc.Ellipse(circle.left, circle.top, circle.right, circle.bottom);
#ifdef _DEBUG
            ::GdiFlush();
#endif
           } /* circles */
       } /* circles */

    //*****************************************************************************
    // DRAW ARROWS
    //*****************************************************************************
    CPen positivePen(PS_SOLID, 2, RGB(0, 0, 255));
    dc.SelectObject(&positivePen);

    /****************************************************************
                                         \
      +----------------------------------->
                                         /
    ****************************************************************/

    int head = positive / 20;
    if(head == 0)
       head = 2;

    dc.MoveTo(0, 0);
    dc.LineTo(positive, 0);

    dc.LineTo(positive - 2 * head, -head);
    dc.MoveTo(positive, 0);
    dc.LineTo(positive - 2 * head, head);
    
    dc.MoveTo(0, 0);
    dc.LineTo(0, positive);

    dc.LineTo(-head, positive - 2 * head);
    dc.MoveTo(0, positive);
    dc.LineTo(head, positive - 2 * head);

    // Do not call CStatic::OnPaint() for painting messages
   }

/****************************************************************************
*                        CDPLPDisplay::SetViewportExt
* Inputs:
*       int x:
*       int y:
* Result: void
*       
* Effect: 
*       Sets the viewport ext
****************************************************************************/

void CDPLPDisplay::SetViewportExt(int x, int y)
    {
     if(x == 0 || y == 0)
        return; // ignore same size
     TRACE2("CDPLPDisplay::SetViewportExt(%d, %d)\n", x, y);
     ViewportExt = CSize(x, y);
     Invalidate();
    } // CDPLPDisplay::SetViewportExt

/****************************************************************************
*                        CDPLPDisplay::SetViewportOrg
* Inputs:
*       int x:
*       int y:
* Result: void
*       
* Effect: 
*       Sets the viewport org
****************************************************************************/

void CDPLPDisplay::SetViewportOrg(int x, int y)
    {
     TRACE2("CDPLPDisplay::SetViewportOrg(%d, %d)\n", x, y);
     ViewportOrg = CPoint(x, y);
     Invalidate();
    } // CDPLPDisplay::SetViewportOrg

/****************************************************************************
*                         CDPLPDisplay::SetWindowExt
* Inputs:
*       int x:
*       int y:
* Result: void
*       
* Effect: 
*       Sets the window ext
****************************************************************************/

void CDPLPDisplay::SetWindowExt(int x, int y)
    {
     if(x == 0 || y == 0)
         return; // ignore empty request
     TRACE2("CDPLPDisplay::SetWindowExt(%d, %d)\n", x, y);
     WindowExt = CSize(x, y);
     Invalidate();
    } // CDPLPDisplay::SetWindowExt

/****************************************************************************
*                         CDPLPDisplay::SetWindowOrg
* Inputs:
*       int x:
*       int y:
* Result: void
*       
* Effect: 
*       Sets the window org
****************************************************************************/

void CDPLPDisplay::SetWindowOrg(int x, int y)
    {
     TRACE2("CDPLPDisplay::SetWindowOrg(%d, %d)\n", x, y);
     WindowOrg = CPoint(x, y);
     Invalidate();
    } // CDPLPDisplay::SetWindowOrg

/****************************************************************************
*                          CDPLPDisplay::SetMapMode
* Inputs:
*       UINT mode: Mode to use
* Result: void
*       
* Effect: 
*       Sets the map mode
****************************************************************************/

void CDPLPDisplay::SetMapMode(UINT mode)
    {
     MapMode = mode;
     Invalidate();
    } // CDPLPDisplay::SetMapMode

/****************************************************************************
*                         CDPLPDisplay::SetDeviceGrid
* Inputs:
*       int n: Grid spacing
* Result: void
*       
* Effect: 
*       Sets grid spacing
****************************************************************************/

void CDPLPDisplay::SetDeviceGrid(int n)
    {
     if(n <= 0)
        return;
     dx = dy = n;
     Invalidate();
    } // CDPLPDisplay::SetDeviceGrid

/****************************************************************************
*                        CDPLPDisplay::SetLogicalGrid
* Inputs:
*       int n: Value to set
* Result: void
*       
* Effect: 
*       Sets the logical grid spacing
****************************************************************************/

void CDPLPDisplay::SetLogicalGrid(int n)
    {
     if(n <= 0)
        return;
     Ldx = Ldy = n;
     Invalidate();
    } // CDPLPDisplay::SetLogicalGrid

/****************************************************************************
*                           CDPLPDisplay::PrepareDC
* Inputs:
*       CDC & dc: DC to set up
* Result: void
*       
* Effect: 
*       Sets the mapping modes and other parameters
****************************************************************************/

void CDPLPDisplay::PrepareDC(CDC & dc)
    {
     dc.SetMapMode(MapMode);

     dc.SetWindowOrg(WindowOrg);
     TRACE2("CDPLPDisplay::PrepareDC!SetWindowOrg(%d, %d)\n", WindowOrg.x, WindowOrg.y);

     dc.SetViewportOrg(ViewportOrg);
     TRACE2("CDPLPDisplay::PrepareDC!SetViewportOrg(%d, %d)\n", ViewportOrg.x, ViewportOrg.y);

     dc.SetWindowExt(WindowExt);
     TRACE2("CDPLPDisplay::PrepareDC!SetWindowExt(%d, %d)\n", WindowExt.cx, WindowExt.cy);

     dc.SetViewportExt(ViewportExt);
     TRACE2("CDPLPDisplay::PrepareDC!SetViewportExt(%d, %d)\n", ViewportExt.cx, ViewportExt.cy);
    } // CDPLPDisplay::PrepareDC

/****************************************************************************
*                       CDPLPDisplay::PreSubclassWindow
* Result: void
*       
* Effect: 
*       Initializes the viewport and window extents
****************************************************************************/

void CDPLPDisplay::PreSubclassWindow() 
   {
    CStatic::PreSubclassWindow();
    CRect r;

    //-----------------------
    // Make sure it is square
    //-----------------------
    GetWindowRect(&r);
    int w = min(r.Width(), r.Height());
    SetWindowPos(NULL, 0, 0, w, w, SWP_NOMOVE | SWP_NOZORDER);
    
    GetClientRect(&r);
    ViewportExt = CSize(r.Width(), r.Height());
    WindowExt = CSize(r.Width(), r.Height());
   }

/****************************************************************************
*                          CDPLPDisplay::SetPositive
* Inputs:
*       int n: Value of length of positive line
* Result: void
*       
* Effect: 
*       Sets the length of the positive-pointing arrows
****************************************************************************/

void CDPLPDisplay::SetPositive(int n)
    {
     if(n < 0)
        return;
     positive = n;
     Invalidate();
    } // CDPLPDisplay::SetPositive

/****************************************************************************
*                         CDPLPDisplay::OnLButtonDown
* Inputs:
*       UINT nFlags:
*       CPoint point:
* Result: void
*       
* Effect: 
*       Initiates a drag operation by notifying the parent and setting
*       mouse capture
****************************************************************************/

void CDPLPDisplay::OnLButtonDown(UINT nFlags, CPoint point) 
   {
    SetCapture();
    anchor = point;
    CPoint tp = point;
    DPtoLP(tp);
    GetParent()->SendMessage(UWM_MOUSEDRAGSTART, (WPARAM)&anchor, (LPARAM)&tp);
    CStatic::OnLButtonDown(nFlags, point);
   }

/****************************************************************************
*                          CDPLPDisplay::OnLButtonUp
* Inputs:
*       UINT nFlags:
*       CPoint point: Current point (client coordinates)
* Result: void
*       
* Effect: 
*       If capture had been made, releases it
****************************************************************************/

void CDPLPDisplay::OnLButtonUp(UINT nFlags, CPoint point) 
   {
    if(GetCapture() != NULL)
       { /* has capture */
        CPoint tp = point;
        DPtoLP(point);
        ReleaseCapture();
        GetParent()->SendMessage(UWM_MOUSEDRAGEND, (WPARAM)&point, (LPARAM)&tp);
       } /* has capture */
        
    CStatic::OnLButtonUp(nFlags, point);
   }

/****************************************************************************
*                          CDPLPDisplay::SetCircles
* Inputs:
*       BOOL mode: Mode
* Result: void
*       
* Effect: 
*       Sets the circles mode
****************************************************************************/

void CDPLPDisplay::SetCircles(BOOL mode)
    {
     circles = mode;
     Invalidate();
    } // CDPLPDisplay::SetCircles

/****************************************************************************
*                         CDPLPDisplay::SetGridLines
* Inputs:
*       BOOL mode: Mode to use
* Result: void
*       
* Effect: 
*       Sets the gridlines flag
****************************************************************************/

void CDPLPDisplay::SetGridLines(BOOL mode)
    {
     gridlines = mode;
     Invalidate();
    } // CDPLPDisplay::SetGridLines

/****************************************************************************
*                         CDPLPDisplay::SetLineStyle
* Inputs:
*       UINT style: Line style
* Result: void
*       
* Effect: 
*       Changes the line style
****************************************************************************/

void CDPLPDisplay::SetLineStyle(UINT style)
    {
     GridLineStyle = style;
     Invalidate();
    } // CDPLPDisplay::SetLineStyle

/****************************************************************************
*                            CDPLPDisplay::DPtoLP
* Inputs:
*       CPoint & dp: Rectangle in device coordinates
* Result: void
*       
* Effect: 
*       Translates the rectangle to logical coordinates
****************************************************************************/

void CDPLPDisplay::DPtoLP(CPoint & dp)
    {
     CClientDC dc(this);
     PrepareDC(dc);
     dc.DPtoLP(&dp);    
    } // CDPLPDisplay::DPtoLP

/****************************************************************************
*                            CDPLPDisplay::DPtoLP
* Inputs:
*       CSize & dp: Rectangle in device coordinates
* Result: void
*       
* Effect: 
*       Translates the rectangle to logical coordinates
****************************************************************************/

void CDPLPDisplay::DPtoLP(CSize & dp)
   {
    CClientDC dc(this);
    PrepareDC(dc);
    dc.DPtoLP(&dp);    
   } // CDPLPDisplay::DPtoLP

/****************************************************************************
*                            CDPLPDisplay::DPtoLP
* Inputs:
*       CRect & r: Rectangle in device coordinates
* Result: void
*       
* Effect: 
*       Translates the rectangle to logical coordinates
****************************************************************************/

void CDPLPDisplay::DPtoLP(CRect & r)
    {
     CClientDC dc(this);
     PrepareDC(dc);
     dc.DPtoLP(&r);    
    } // CDPLPDisplay::DPtoLP

/****************************************************************************
*                            CDPLPDisplay::LPtoDP
* Inputs:
*       CPoint & dp: Rectangle in device coordinates
* Result: void
*       
* Effect: 
*       Translates the rectangle to logical coordinates
****************************************************************************/

void CDPLPDisplay::LPtoDP(CPoint & dp)
    {
     CClientDC dc(this);
     PrepareDC(dc);
     dc.LPtoDP(&dp);    
    } // CDPLPDisplay::LPtoDP

/****************************************************************************
*                            CDPLPDisplay::LPtoDP
* Inputs:
*       CRect & r: Rectangle in device coordinates
* Result: void
*       
* Effect: 
*       Translates the rectangle to logical coordinates
****************************************************************************/

void CDPLPDisplay::LPtoDP(CRect & r)
    {
     CClientDC dc(this);
     PrepareDC(dc);
     dc.LPtoDP(&r);    
    } // CDPLPDisplay::LPtoDP

/****************************************************************************
*                            CDPLPDisplay::GetSign
* Result: CSize
*       The coordinate sign multiplier
*       cx = -1 for x increasing left, 1 for x increasing right
*       cy = -1 for y increasing up, 1 for y increasing down
****************************************************************************/

CSize CDPLPDisplay::GetSign()
    {
     CSize result(1, 1);
     CRect r;
     GetClientRect(&r);
     DPtoLP(r);
     if(r.left > r.right)
        result.cx = -1;
     if(r.bottom < r.top)
        result.cy = -1;
     return result;
    } // CDPLPDisplay::GetSign
