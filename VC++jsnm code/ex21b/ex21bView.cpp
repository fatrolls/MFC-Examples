// ex21bView.cpp : implementation of the CEx21bView class
//

#include "stdafx.h"
#include "ex21b.h"

#include "ex21bDoc.h"
#include "ex21bView.h"

#include "Test21cDialog.h"
#include "Test21dDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx21bView

IMPLEMENT_DYNCREATE(CEx21bView, CView)

BEGIN_MESSAGE_MAP(CEx21bView, CView)
	//{{AFX_MSG_MAP(CEx21bView)
	ON_COMMAND(ID_TEST_EX21CDLL, OnTestEx21cdll)
	ON_COMMAND(ID_TEST_EX21DDLL, OnTestEx21ddll)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx21bView construction/destruction

CEx21bView::CEx21bView()
{
	// TODO: add construction code here

}

CEx21bView::~CEx21bView()
{
}

BOOL CEx21bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx21bView drawing

void CEx21bView::OnDraw(CDC* pDC)
{
	CEx21bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx21bView printing

BOOL CEx21bView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx21bView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx21bView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx21bView diagnostics

#ifdef _DEBUG
void CEx21bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx21bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx21bDoc* CEx21bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx21bDoc)));
	return (CEx21bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx21bView message handlers

void CEx21bView::OnTestEx21cdll() 
{
	CTest21cDialog dlg;
	dlg.DoModal();
}

void CEx21bView::OnTestEx21ddll() 
{
	CTest21dDialog dlg;
	dlg.DoModal();
}
