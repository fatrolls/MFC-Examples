// ProgressDemoView.cpp : implementation of the CProgressDemoView class
//

#include "stdafx.h"
#include "ProgressDemo.h"

#include "ProgressDemoDoc.h"
#include "ProgressDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoView

IMPLEMENT_DYNCREATE(CProgressDemoView, CView)

BEGIN_MESSAGE_MAP(CProgressDemoView, CView)
	//{{AFX_MSG_MAP(CProgressDemoView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoView construction/destruction

CProgressDemoView::CProgressDemoView()
{
}

CProgressDemoView::~CProgressDemoView()
{
}

BOOL CProgressDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoView drawing

void CProgressDemoView::OnDraw(CDC* pDC)
{
	CProgressDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoView diagnostics

#ifdef _DEBUG
void CProgressDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CProgressDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProgressDemoDoc* CProgressDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProgressDemoDoc)));
	return (CProgressDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProgressDemoView message handlers
