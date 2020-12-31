// ex07aView.cpp : implementation of the CEx07aView class
//

#include "stdafx.h"
#include "ex07a.h"

#include "ex07aDoc.h"
#include "ex07aView.h"
#include "ex07aDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx07aView

IMPLEMENT_DYNCREATE(CEx07aView, CView)

BEGIN_MESSAGE_MAP(CEx07aView, CView)
	ON_MESSAGE(WM_GOODBYE, OnGoodbye)
	//{{AFX_MSG_MAP(CEx07aView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx07aView construction/destruction

CEx07aView::CEx07aView()
{
	m_pDlg = new CEx07aDialog(this);
}

CEx07aView::~CEx07aView()
{
	delete m_pDlg; // destroys window if not already destroyed
}

BOOL CEx07aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx07aView drawing

void CEx07aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Press the left mouse button here.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx07aView diagnostics

#ifdef _DEBUG
void CEx07aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx07aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx07aDoc* CEx07aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx07aDoc)));
	return (CEx07aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx07aView message handlers

void CEx07aView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// creates the dialog if not created already
	if (m_pDlg->GetSafeHwnd() == 0) {
		m_pDlg->Create(); // displays the dialog window
	}
}

void CEx07aView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	m_pDlg->DestroyWindow();
	// no problem if window was already destroyed
}

LRESULT CEx07aView::OnGoodbye(WPARAM wParam, LPARAM lParam)
{
	// message received in response to modeless dialog OK
	//  and Cancel buttons
	TRACE("CEx07aView::OnGoodbye %x, %lx\n", wParam, lParam);
	TRACE("Dialog edit1 contents = %s\n",
	      (const char*) m_pDlg->m_strEdit1);
	m_pDlg->DestroyWindow();
	return 0L;
}
