// NoFlickerView.cpp : implementation of the CNoFlickerView class
//

#include "stdafx.h"
#include "NoFlicker.h"

#include "NoFlickerDoc.h"
#include "NoFlickerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView

IMPLEMENT_DYNCREATE(CNoFlickerView, CView)

BEGIN_MESSAGE_MAP(CNoFlickerView, CView)
	//{{AFX_MSG_MAP(CNoFlickerView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView construction/destruction

CNoFlickerView::CNoFlickerView()
{
	// TODO: add construction code here

}

CNoFlickerView::~CNoFlickerView()
{
}

BOOL CNoFlickerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView drawing

void CNoFlickerView::OnDraw(CDC* dc)
{
	CRect	rcBounds;
	GetClientRect(&rcBounds);
	CMemDC	pDC(dc, rcBounds);

	pDC->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pDC->Ellipse(rcBounds);
}

BOOL CNoFlickerView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView printing

BOOL CNoFlickerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNoFlickerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNoFlickerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView diagnostics

#ifdef _DEBUG
void CNoFlickerView::AssertValid() const
{
	CView::AssertValid();
}

void CNoFlickerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNoFlickerDoc* CNoFlickerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNoFlickerDoc)));
	return (CNoFlickerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNoFlickerView message handlers

