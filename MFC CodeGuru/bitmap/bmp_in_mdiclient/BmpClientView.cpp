// BmpClientView.cpp : implementation of the CBmpClientView class
//

#include "stdafx.h"
#include "BmpClient.h"

#include "BmpClientDoc.h"
#include "BmpClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpClientView

IMPLEMENT_DYNCREATE(CBmpClientView, CView)

BEGIN_MESSAGE_MAP(CBmpClientView, CView)
	//{{AFX_MSG_MAP(CBmpClientView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpClientView construction/destruction

CBmpClientView::CBmpClientView()
{
}

CBmpClientView::~CBmpClientView()
{
}

BOOL CBmpClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpClientView drawing

void CBmpClientView::OnDraw(CDC* pDC)
{
	CBmpClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpClientView diagnostics

#ifdef _DEBUG
void CBmpClientView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpClientView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpClientDoc* CBmpClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpClientDoc)));
	return (CBmpClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpClientView message handlers
