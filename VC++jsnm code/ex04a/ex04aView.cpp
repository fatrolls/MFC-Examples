// ex04aView.cpp : implementation of the CEx04aView class
//

#include "stdafx.h"
#include "ex04a.h"

#include "ex04aDoc.h"
#include "ex04aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx04aView

IMPLEMENT_DYNCREATE(CEx04aView, CView)

BEGIN_MESSAGE_MAP(CEx04aView, CView)
	//{{AFX_MSG_MAP(CEx04aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx04aView construction/destruction

CEx04aView::CEx04aView() : m_rectEllipse(0, 0, 200, 200)
{
	m_nColor = GRAY_BRUSH;
}

CEx04aView::~CEx04aView()
{
}

BOOL CEx04aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04aView drawing

void CEx04aView::OnDraw(CDC* pDC)
{
	pDC->SelectStockObject(m_nColor);
	pDC->Ellipse(m_rectEllipse);
}

/////////////////////////////////////////////////////////////////////////////
// CEx04aView printing

BOOL CEx04aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx04aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx04aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx04aView diagnostics

#ifdef _DEBUG
void CEx04aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx04aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx04aDoc* CEx04aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx04aDoc)));
	return (CEx04aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx04aView message handlers

void CEx04aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_rectEllipse.PtInRect(point)) {
		if (m_nColor == GRAY_BRUSH) {
			m_nColor = WHITE_BRUSH;
		}
		else {
			m_nColor = GRAY_BRUSH;
		}
		InvalidateRect(m_rectEllipse);
	}
}
