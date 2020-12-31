// SquaresView.cpp : implementation of the CSquaresView class
//

#include "stdafx.h"
#include "MdiSquares.h"

#include "SquaresDoc.h"
#include "SquaresView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSquaresView

IMPLEMENT_DYNCREATE(CSquaresView, CView)

BEGIN_MESSAGE_MAP(CSquaresView, CView)
	//{{AFX_MSG_MAP(CSquaresView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSquaresView construction/destruction

CSquaresView::CSquaresView()
{
}

CSquaresView::~CSquaresView()
{
}

BOOL CSquaresView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSquaresView drawing

void CSquaresView::OnDraw(CDC* pDC)
{
	CSquaresDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//
	// Set the mapping mode to MM_LOENGLISH.
	//
	pDC->SetMapMode (MM_LOENGLISH);

	//
	// Draw the 16 squares.
	//
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			COLORREF color = pDoc->GetSquare (i, j);
			CBrush brush (color);
			int x1 = (j * 70) + 35;
			int y1 = (i * -70) - 35;
			int x2 = x1 + 70;
			int y2 = y1 - 70;
			CRect rect (x1, y1, x2, y2);
			pDC->FillRect (rect, &brush);
		}
	}

	//
	// Then draw the grid lines surrounding them.
	//
	for (int x=35; x<=315; x+=70) {
		pDC->MoveTo (x, -35);
		pDC->LineTo (x, -315);
	}

	for (int y=-35; y>=-315; y-=70) {
		pDC->MoveTo (35, y);
		pDC->LineTo (315, y);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSquaresView diagnostics

#ifdef _DEBUG
void CSquaresView::AssertValid() const
{
	CView::AssertValid();
}

void CSquaresView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSquaresDoc* CSquaresView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSquaresDoc)));
	return (CSquaresDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSquaresView message handlers

void CSquaresView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

	//
	// Convert click coordinates to MM_LOENGLISH units.
	//
	CClientDC dc (this);
	dc.SetMapMode (MM_LOENGLISH);
	CPoint pos = point;
	dc.DPtoLP (&pos);

	//
	// If a square was clicked, set its color to the current color.
	//
	if (pos.x >= 35 && pos.x <= 315 && pos.y <= -35 && pos.y >= -315) {
		int i = (-pos.y - 35) / 70;
		int j = (pos.x - 35) / 70;
		CSquaresDoc* pDoc = GetDocument ();
		COLORREF clrCurrentColor = pDoc->GetCurrentColor ();
		pDoc->SetSquare (i, j, clrCurrentColor);
	}
}
