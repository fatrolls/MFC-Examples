// TextView.cpp : implementation file
//

#include "stdafx.h"
#include "Graph.h"
#include "GraphDoc.h"
#include "TextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CView)

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CView)
        //{{AFX_MSG_MAP(CTextView)
                // NOTE - the ClassWizard will add and remove mapping macros here.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnDraw(CDC* pDC)
{
        CGraphDoc* pDoc = (CGraphDoc*)GetDocument();

        TEXTMETRIC   tm;
        int          x,y, cy, i;
        char         sz[20];
        pDC->GetTextMetrics(&tm);
        cy = tm.tmHeight;
        pDC->SetTextColor(RGB(255, 0, 0));  // red text
        for (x=5,y=5,i=0; i<DATANUM; i++,y+=cy)
        {
            wsprintf (sz, "%d", pDoc->m_intArray[i]);
            pDC->TextOut (x,y, sz, lstrlen(sz));
        }
}

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
        CView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
        CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers
