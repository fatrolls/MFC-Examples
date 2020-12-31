// ex11aView.cpp : implementation of the CEx11aView class
//

#include "stdafx.h"
#include "ex11a.h"

#include "ex11aDoc.h"
#include "ex11aView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11aView

IMPLEMENT_DYNCREATE(CEx11aView, CView)

BEGIN_MESSAGE_MAP(CEx11aView, CView)
	//{{AFX_MSG_MAP(CEx11aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11aView construction/destruction

CEx11aView::CEx11aView()
{
	// TODO: add construction code here

}

CEx11aView::~CEx11aView()
{
}

BOOL CEx11aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView drawing

void CEx11aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx11aView diagnostics

#ifdef _DEBUG
void CEx11aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx11aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx11aDoc* CEx11aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11aDoc)));
	return (CEx11aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11aView message handlers

void CEx11aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CComputeDlg dlg;
	dlg.DoModal();
}
