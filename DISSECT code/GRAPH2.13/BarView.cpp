// BarView.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"

#include "GraphDoc.h"
#include "BarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBarView

IMPLEMENT_DYNCREATE(CBarView, CView)

CBarView::CBarView()
{
}

CBarView::~CBarView()
{
}


BEGIN_MESSAGE_MAP(CBarView, CView)
        //{{AFX_MSG_MAP(CBarView)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBarView drawing

void CBarView::OnDraw(CDC* pDC)
{
        CGraphDoc* pDoc = (CGraphDoc*)GetDocument();

        int          cxBar,cxBarSpacing, cxGraph,cyGraph, x,y, i;
        RECT         rc;

        CBrush brush(RGB(255, 0, 0));  // red brush
        CBrush* pOldBrush = pDC->SelectObject(&brush);
        CPen pen(PS_SOLID, 1, RGB(255, 0, 0)); // red pen
        CPen* pOldPen = pDC->SelectObject(&pen);

        cxGraph = 100;
        cyGraph = DATAMAX;  // defined in resource.h

        this->GetClientRect(&rc);
        pDC->SetMapMode(MM_ANISOTROPIC);
        pDC->SetWindowOrg(0, 0);
        pDC->SetViewportOrg(10, rc.bottom-10);
        pDC->SetWindowExt(cxGraph, cyGraph);
        pDC->SetViewportExt(rc.right-20, -(rc.bottom-20));

        // 長條圖的條狀物之間距離是條狀物寬度的 1/3。
        // 我們希望條狀物能夠填充視窗的整個可用空間。
        // 所以 (bar_spacing + bar_width) * num_bars = graph_width
        // 亦即  bar_width * 4/3  * num_bars = graph_width
        // 亦即  bar_width = graph_width / num_bars * 3/4

        cxBar = (3 * cxGraph) / (4 * DATANUM);
        cxBarSpacing = cxBar/3;
        if (cxBar<3)  cxBar=3;

        // 座標軸
        pDC->MoveTo(0, 0);
        pDC->LineTo(0, cyGraph);
        pDC->MoveTo(0, 0);
        pDC->LineTo(cxGraph, 0);

        // 長條圖
        for (x=0+cxBarSpacing,y=0,i=0; i< DATANUM; i++,x+=cxBar+cxBarSpacing)
            pDC->Rectangle(x, y, x+cxBar, y+pDoc->m_intArray[i]);

       pDC->SelectObject(pOldPen);
       pDC->SelectObject(pOldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CBarView diagnostics

#ifdef _DEBUG
void CBarView::AssertValid() const
{
        CView::AssertValid();
}

void CBarView::Dump(CDumpContext& dc) const
{
        CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBarView message handlers
