
// NCSkinDemoView.cpp : implementation of the CNCSkinDemoView class
//

#include "stdafx.h"
#include "NCSkinDemo.h"

#include "NCSkinDemoDoc.h"
#include "NCSkinDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNCSkinDemoView

IMPLEMENT_DYNCREATE(CNCSkinDemoView, CView)

BEGIN_MESSAGE_MAP(CNCSkinDemoView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CNCSkinDemoView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CNCSkinDemoView construction/destruction

CNCSkinDemoView::CNCSkinDemoView()
{
	// TODO: add construction code here

}

CNCSkinDemoView::~CNCSkinDemoView()
{
}

BOOL CNCSkinDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CNCSkinDemoView drawing

void CNCSkinDemoView::OnDraw(CDC* pDC)
{
	CNCSkinDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}


// CNCSkinDemoView printing


void CNCSkinDemoView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CNCSkinDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNCSkinDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNCSkinDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CNCSkinDemoView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CNCSkinDemoView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CNCSkinDemoView diagnostics

#ifdef _DEBUG
void CNCSkinDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CNCSkinDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CNCSkinDemoDoc* CNCSkinDemoView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNCSkinDemoDoc)));
	return (CNCSkinDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CNCSkinDemoView message handlers
