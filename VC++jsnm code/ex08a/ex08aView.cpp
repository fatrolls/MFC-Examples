// ex08aView.cpp : implementation of the CEx08aView class
//

#include "stdafx.h"
#include "ex08a.h"

#include "ex08aDoc.h"
#include "ex08aView.h"
#include "ActiveXDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx08aView

IMPLEMENT_DYNCREATE(CEx08aView, CView)

BEGIN_MESSAGE_MAP(CEx08aView, CView)
	//{{AFX_MSG_MAP(CEx08aView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx08aView construction/destruction

CEx08aView::CEx08aView()
{
	// TODO: add construction code here

}

CEx08aView::~CEx08aView()
{
}

BOOL CEx08aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx08aView drawing

void CEx08aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Click the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx08aView diagnostics

#ifdef _DEBUG
void CEx08aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx08aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx08aDoc* CEx08aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx08aDoc)));
	return (CEx08aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx08aView message handlers

void CEx08aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CActiveXDialog dlg;
	dlg.m_BackColor = RGB(255, 251, 240); // light yellow
	COleDateTime today = COleDateTime::GetCurrentTime();
	dlg.m_varValue = COleDateTime(today.GetYear(), today.GetMonth(),
	                              today.GetDay(), 0, 0, 0);
	if (dlg.DoModal() == IDOK) {
		COleDateTime date(dlg.m_varValue);
		AfxMessageBox(date.Format("%B %d, %Y"));
	}
}
