// ArrowButton.cpp : implementation file
//

#include "stdafx.h"
#include "ArrowButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArrowButton

CArrowButton::CArrowButton()
   {
    direction = DrawArrow::ARROW_NONE;
   }

CArrowButton::~CArrowButton()
{
}


BEGIN_MESSAGE_MAP(CArrowButton, CButton)
        //{{AFX_MSG_MAP(CArrowButton)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArrowButton message handlers

/****************************************************************************
*                           CArrowButton::DrawItem
* Inputs:
*       LPDRAWITEMSTRUCT dis
* Result: void
*       
* Effect: 
*       Draws a button with an arrow inside
****************************************************************************/

void CArrowButton::DrawItem(LPDRAWITEMSTRUCT dis) 
   {
    CDC * dc = CDC::FromHandle(dis->hDC);
    int save = dc->SaveDC();
    CRect r;
    GetClientRect(&r);

    dc->FillSolidRect(&r, ::GetSysColor(COLOR_3DFACE));
    dc->SelectStockObject(WHITE_BRUSH);
    UINT edge;
    CPoint pt(0,0);
    if(dis->itemState & ODS_SELECTED)
       { /* up */
        edge = EDGE_SUNKEN;
        pt = CPoint(1, 1);
       } /* up */
    else
       { /* down */
        edge = EDGE_RAISED;
       } /* down */

    dc->DrawEdge(&r, edge, BF_ADJUST | BF_RECT);
    r.InflateRect(-2, -2);
    r += pt;
    DrawArrow::Draw(*dc, r, direction);
    dc->RestoreDC(save);
   }

/****************************************************************************
*                         CArrowButton::SetDirection
* Inputs:
*       DrawArrow::Direction dir: Direction to set
* Result: void
*       
* Effect: 
*       Sets the direction
****************************************************************************/

void CArrowButton::SetDirection(DrawArrow::Direction dir)
    {
     if(direction == dir)
        return; // ignore if already set
     direction = dir;
     if(GetSafeHwnd() != NULL)
        Invalidate();
    } // CArrowButton::SetDirection
