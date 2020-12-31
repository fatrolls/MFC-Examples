// DSplitView.cpp : implementation of the CDSplitView class
//

#include "stdafx.h"
#include "DSplit.h"

#include "DSplitDoc.h"
#include "DSplitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSplitView

IMPLEMENT_DYNCREATE(CDSplitView, CView)

BEGIN_MESSAGE_MAP(CDSplitView, CView)
	//{{AFX_MSG_MAP(CDSplitView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSplitView construction/destruction

CDSplitView::CDSplitView()
{
	// TODO: add construction code here

}

CDSplitView::~CDSplitView()
{
}

BOOL CDSplitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSplitView drawing

void CDSplitView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->DrawText("View 1",&rect,DT_CENTER | DT_VCENTER |DT_SINGLELINE);
}

/////////////////////////////////////////////////////////////////////////////
// CDSplitView printing

BOOL CDSplitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDSplitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDSplitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDSplitView diagnostics

#ifdef _DEBUG
void CDSplitView::AssertValid() const
{
	CView::AssertValid();
}

void CDSplitView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSplitDoc* CDSplitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSplitDoc)));
	return (CDSplitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSplitView message handlers

BOOL CDSplitView::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);

	pDC->FillSolidRect(&rect,::GetSysColor(COLOR_WINDOW));
	
	return TRUE;
}
