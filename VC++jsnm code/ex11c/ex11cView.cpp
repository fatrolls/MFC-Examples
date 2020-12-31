// ex11cView.cpp : implementation of the CEx11cView class
//

#include "stdafx.h"
#include "ex11c.h"

#include "ex11cDoc.h"
#include "ex11cView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11cView

IMPLEMENT_DYNCREATE(CEx11cView, CView)

BEGIN_MESSAGE_MAP(CEx11cView, CView)
	//{{AFX_MSG_MAP(CEx11cView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11cView construction/destruction

CEx11cView::CEx11cView()
{
	// TODO: add construction code here

}

CEx11cView::~CEx11cView()
{
}

BOOL CEx11cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11cView drawing

void CEx11cView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx11cView diagnostics

#ifdef _DEBUG
void CEx11cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx11cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx11cDoc* CEx11cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11cDoc)));
	return (CEx11cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11cView message handlers

void CEx11cView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CComputeDlg dlg;
	dlg.DoModal();
}
