// ex06bView.cpp : implementation of the CEx06bView class
//

#include "stdafx.h"
#include "ex06b.h"

#include "ex06bDoc.h"
#include "ex06bView.h"
#include "ex06bDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx06bView

IMPLEMENT_DYNCREATE(CEx06bView, CView)

BEGIN_MESSAGE_MAP(CEx06bView, CView)
	//{{AFX_MSG_MAP(CEx06bView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx06bView construction/destruction

CEx06bView::CEx06bView()
{
	// TODO: add construction code here

}

CEx06bView::~CEx06bView()
{
}

BOOL CEx06bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx06bView drawing

void CEx06bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx06bView diagnostics

#ifdef _DEBUG
void CEx06bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx06bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx06bDoc* CEx06bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx06bDoc)));
	return (CEx06bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx06bView message handlers

void CEx06bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEx06bDialog dlg;

	dlg.m_nTrackbar1 = 20;
	dlg.m_nTrackbar2 = 2; // index for 8.0
	dlg.m_nProgress = 70; // write-only
	dlg.m_dSpin = 3.2;

	dlg.DoModal();
}
