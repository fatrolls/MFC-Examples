// ex05cView.cpp : implementation of the CEx05cView class
//

#include "stdafx.h"
#include "ex05c.h"

#include "ex05cDoc.h"
#include "ex05cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx05cView

IMPLEMENT_DYNCREATE(CEx05cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx05cView, CScrollView)
	//{{AFX_MSG_MAP(CEx05cView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx05cView construction/destruction

CEx05cView::CEx05cView() : m_sizeEllipse(100, -100),
                           m_pointTopLeft(0, 0),
						   m_sizeOffset(0, 0)
{
	m_bCaptured = FALSE;
}

CEx05cView::~CEx05cView()
{
}

BOOL CEx05cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05cView drawing

void CEx05cView::OnDraw(CDC* pDC)
{
	CBrush brushHatch(HS_DIAGCROSS, RGB(255, 0, 0));
	CPoint point(0, 0);                  // logical (0, 0)
	
	pDC->LPtoDP(&point);                 // In device coordinates,
	pDC->SetBrushOrg(point);             //  align the brush with
	                                     //  the window origin
	pDC->SelectObject(&brushHatch);
	pDC->Ellipse(CRect(m_pointTopLeft, m_sizeEllipse));
	pDC->SelectStockObject(BLACK_BRUSH); // Deselect brushHatch
	pDC->Rectangle(CRect(100, -100, 200, -200)); // Test invalid rect
}

void CEx05cView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal(800, 1050); // 8-by-10.5 inches
	CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
	CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
	SetScrollSizes(MM_LOENGLISH, sizeTotal, sizePage, sizeLine);
}

/////////////////////////////////////////////////////////////////////////////
// CEx05cView diagnostics

#ifdef _DEBUG
void CEx05cView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx05cView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx05cDoc* CEx05cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx05cDoc)));
	return (CEx05cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx05cView message handlers

void CEx05cView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rectEllipse(m_pointTopLeft, m_sizeEllipse); // still logical
	CRgn  circle;

	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(rectEllipse); // Now it's in device coordinates
	circle.CreateEllipticRgnIndirect(rectEllipse);
	if (circle.PtInRegion(point)) {
		// Capturing the mouse ensures subsequent LButtonUp message
		SetCapture();
		m_bCaptured = TRUE;
		CPoint pointTopLeft(m_pointTopLeft);
		dc.LPtoDP(&pointTopLeft);
		m_sizeOffset = point - pointTopLeft; // device coordinates
		// New mouse cursor is active while mouse is captured
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
	}
}

void CEx05cView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		::ReleaseCapture();
		m_bCaptured = FALSE;
	}
}

void CEx05cView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bCaptured) {
		CClientDC dc(this);
		OnPrepareDC(&dc);
		CRect rectOld(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectOld);
		InvalidateRect(rectOld, TRUE);
		m_pointTopLeft = point - m_sizeOffset;
		dc.DPtoLP(&m_pointTopLeft);
		CRect rectNew(m_pointTopLeft, m_sizeEllipse);
		dc.LPtoDP(rectNew);
		InvalidateRect(rectNew, TRUE);
	}
}
