// View2.cpp : implementation file
//

#include "stdafx.h"
#include "VarSplit.h"
#include "View2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView2

IMPLEMENT_DYNCREATE(CView2, CView)

CView2::CView2()
{
		TRACE0("COSTRUTTORE CView2\n");

}

CView2::~CView2()
{
		TRACE0("DISTRUTTORE CView2\n");

}


BEGIN_MESSAGE_MAP(CView2, CView)
	//{{AFX_MSG_MAP(CView2)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView2 drawing

void CView2::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	pDC->TextOut(0,0,"view2");
}

/////////////////////////////////////////////////////////////////////////////
// CView2 diagnostics

#ifdef _DEBUG
void CView2::AssertValid() const
{
	CView::AssertValid();
}

void CView2::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView2 message handlers

void CView2::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
			TRACE0("INITIAL UPDATE CView2\n");

}
