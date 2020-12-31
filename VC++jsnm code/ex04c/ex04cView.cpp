// ex04cView.cpp : implementation of the CEx04cView class
//

#include "stdafx.h"
#include "ex04c.h"

#include "ex04cDoc.h"
#include "ex04cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04cView

IMPLEMENT_DYNCREATE(CEx04cView, CScrollView)

BEGIN_MESSAGE_MAP(CEx04cView, CScrollView)
	//{{AFX_MSG_MAP(CEx04cView)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04cView construction/destruction

CEx04cView::CEx04cView() : m_rectEllipse(0, 0, 4000, -4000)
{
	m_nColor = GRAY_BRUSH;
}

CEx04cView::~CEx04cView()
{
}

BOOL CEx04cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04cView drawing

void CEx04cView::OnDraw(CDC* pDC)
{
	pDC->SelectStockObject(m_nColor);
	pDC->Ellipse(m_rectEllipse);
}

void CEx04cView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(20000, 30000); // 20 by 30 cm
	CSize sizePage(sizeTotal.cx / 2, sizeTotal.cy / 2);
	CSize sizeLine(sizeTotal.cx / 50, sizeTotal.cy / 50);
	SetScrollSizes(MM_HIMETRIC, sizeTotal, sizePage, sizeLine);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04cView printing

BOOL CEx04cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx04cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx04cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx04cView diagnostics

#ifdef _DEBUG
void CEx04cView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CEx04cView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CEx04cDoc* CEx04cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04cDoc)));
	return (CEx04cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04cView message handlers

void CEx04cView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar) {
	case VK_HOME:
		OnVScroll(SB_TOP, 0, NULL);
		OnHScroll(SB_LEFT, 0, NULL);
		break;
	case VK_END:
		OnVScroll(SB_BOTTOM, 0, NULL);
		OnHScroll(SB_RIGHT, 0, NULL);
		break;
	case VK_UP:
		OnVScroll(SB_LINEUP, 0, NULL);
		break;
	case VK_DOWN:
		OnVScroll(SB_LINEDOWN, 0, NULL);
		break;
	case VK_PRIOR:
		OnVScroll(SB_PAGEUP, 0, NULL);
		break;
	case VK_NEXT:
		OnVScroll(SB_PAGEDOWN, 0, NULL);
		break;
	case VK_LEFT:
		OnHScroll(SB_LINELEFT, 0, NULL);
		break;
	case VK_RIGHT:
		OnHScroll(SB_LINERIGHT, 0, NULL);
		break;
	default:
		break;
	}
}

void CEx04cView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rectDevice = m_rectEllipse;
	dc.LPtoDP(rectDevice);
	if (rectDevice.PtInRect(point)) {
		if (m_nColor == GRAY_BRUSH) {
			m_nColor = WHITE_BRUSH;
		}
		else{
			m_nColor = GRAY_BRUSH;
		}
		InvalidateRect(rectDevice);
	}
}
