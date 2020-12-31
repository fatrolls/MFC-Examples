// ex04bView.cpp : implementation of the CEx04bView class
//

#include "stdafx.h"
#include "ex04b.h"

#include "ex04bDoc.h"
#include "ex04bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04bView

IMPLEMENT_DYNCREATE(CEx04bView, CView)

BEGIN_MESSAGE_MAP(CEx04bView, CView)
	//{{AFX_MSG_MAP(CEx04bView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04bView construction/destruction

CEx04bView::CEx04bView() : m_rectEllipse(0, 0, 4000, -4000)
{
	m_nColor = GRAY_BRUSH;

}

CEx04bView::~CEx04bView()
{
}

BOOL CEx04bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04bView drawing

void CEx04bView::OnDraw(CDC* pDC)
{
	pDC->SelectStockObject(m_nColor);
	pDC->Ellipse(m_rectEllipse);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04bView printing

BOOL CEx04bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx04bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx04bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx04bView diagnostics

#ifdef _DEBUG
void CEx04bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx04bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx04bDoc* CEx04bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04bDoc)));
	return (CEx04bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04bView message handlers

void CEx04bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	OnPrepareDC(&dc);
	CRect rectDevice = m_rectEllipse;
	dc.LPtoDP(rectDevice);
	if (rectDevice.PtInRect(point)) {
		if (m_nColor == GRAY_BRUSH) {
			m_nColor = WHITE_BRUSH;
		}
		else {
			m_nColor = GRAY_BRUSH;
		}
		InvalidateRect(rectDevice);
	}
}

void CEx04bView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	pDC->SetMapMode(MM_HIMETRIC);	
	CView::OnPrepareDC(pDC, pInfo);
}
