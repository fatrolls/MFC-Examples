// View1.cpp : implementation file
//

#include "stdafx.h"
#include "VarSplit.h"
#include "View1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CView1

IMPLEMENT_DYNCREATE(CView1, CView)

CView1::CView1()
{
		TRACE0("COSTRUTTORE CView1\n");

}

CView1::~CView1()
{
	TRACE0("DISTRUTTORE CView1\n");
}


BEGIN_MESSAGE_MAP(CView1, CView)
	//{{AFX_MSG_MAP(CView1)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CView1 drawing

void CView1::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
		pDC->TextOut(0,0,"view1");

}

/////////////////////////////////////////////////////////////////////////////
// CView1 diagnostics

#ifdef _DEBUG
void CView1::AssertValid() const
{
	CView::AssertValid();
}

void CView1::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CView1 message handlers

void CView1::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	TRACE0("INITIAL UPDATE VIEW1\n");
}
