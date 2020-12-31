// ex11bView.cpp : implementation of the CEx11bView class
//

#include "stdafx.h"
#include "ex11b.h"

#include "ex11bDoc.h"
#include "ex11bView.h"
#include "ComputeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx11bView

IMPLEMENT_DYNCREATE(CEx11bView, CView)

BEGIN_MESSAGE_MAP(CEx11bView, CView)
	//{{AFX_MSG_MAP(CEx11bView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx11bView construction/destruction

CEx11bView::CEx11bView()
{
	// TODO: add construction code here

}

CEx11bView::~CEx11bView()
{
}

BOOL CEx11bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx11bView drawing

void CEx11bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx11bView diagnostics

#ifdef _DEBUG
void CEx11bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx11bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx11bDoc* CEx11bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx11bDoc)));
	return (CEx11bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx11bView message handlers

void CEx11bView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CComputeDlg dlg;
	dlg.DoModal();
}
