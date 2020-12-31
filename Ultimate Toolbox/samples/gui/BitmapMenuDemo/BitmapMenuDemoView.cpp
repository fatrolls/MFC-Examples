// BitmapMenuDemoView.cpp : implementation of the CBitmapMenuDemoView class
//

#include "stdafx.h"
#include "BitmapMenuDemo.h"

#include "BitmapMenuDemoDoc.h"
#include "BitmapMenuDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoView

IMPLEMENT_DYNCREATE(CBitmapMenuDemoView, CView)

BEGIN_MESSAGE_MAP(CBitmapMenuDemoView, CView)
	//{{AFX_MSG_MAP(CBitmapMenuDemoView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoView construction/destruction

CBitmapMenuDemoView::CBitmapMenuDemoView()
{
	// TODO: add construction code here

}

CBitmapMenuDemoView::~CBitmapMenuDemoView()
{
}

BOOL CBitmapMenuDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoView drawing

void CBitmapMenuDemoView::OnDraw(CDC* pDC)
{
	CBitmapMenuDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	pDC->TextOut(20,20,CString(_T("Check out menu!")));
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoView diagnostics

#ifdef _DEBUG
void CBitmapMenuDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBitmapMenuDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitmapMenuDemoDoc* CBitmapMenuDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitmapMenuDemoDoc)));
	return (CBitmapMenuDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBitmapMenuDemoView message handlers

