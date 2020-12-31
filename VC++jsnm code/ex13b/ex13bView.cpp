// ex13bView.cpp : implementation of the CEx13bView class
//

#include "stdafx.h"
#include "ex13b.h"

#include "ex13bDoc.h"
#include "ex13bView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx13bView

IMPLEMENT_DYNCREATE(CEx13bView, CView)

BEGIN_MESSAGE_MAP(CEx13bView, CView)
	//{{AFX_MSG_MAP(CEx13bView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx13bView construction/destruction

CEx13bView::CEx13bView()
{
	// TODO: add construction code here

}

CEx13bView::~CEx13bView()
{
}

BOOL CEx13bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx13bView drawing

void CEx13bView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0,
		"Watch the status bar while you move and click the mouse.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx13bView diagnostics

#ifdef _DEBUG
void CEx13bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx13bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx13bDoc* CEx13bView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx13bDoc)));
	return (CEx13bDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx13bView message handlers

void CEx13bView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CString str;
	CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	CStatusBar* pStatus = &pFrame->m_wndStatusBar;
	if (pStatus) {
		str.Format("x = %d", point.x);
		pStatus->SetPaneText(0, str);
		str.Format("y = %d", point.y);
		pStatus->SetPaneText(1, str);
	}
}
