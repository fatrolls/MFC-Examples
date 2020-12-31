// gridlistView.cpp : implementation of the CGridlistView class
//

#include "stdafx.h"
#include "gridlist.h"
#include "TestDlg.h"

#include "gridlistDoc.h"
#include "gridlistView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGridlistView

IMPLEMENT_DYNCREATE(CGridlistView, CView)

BEGIN_MESSAGE_MAP(CGridlistView, CView)
	//{{AFX_MSG_MAP(CGridlistView)
	ON_COMMAND(ID_TEST_GRIDLIST, OnTestGridlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridlistView construction/destruction

CGridlistView::CGridlistView()
{
	// TODO: add construction code here

}

CGridlistView::~CGridlistView()
{
}

BOOL CGridlistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGridlistView drawing

void CGridlistView::OnDraw(CDC* pDC)
{
	CGridlistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CGridlistView diagnostics

#ifdef _DEBUG
void CGridlistView::AssertValid() const
{
	CView::AssertValid();
}

void CGridlistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGridlistDoc* CGridlistView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGridlistDoc)));
	return (CGridlistDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridlistView message handlers

void CGridlistView::OnTestGridlist() 
{
	// TODO: Add your command handler code here
  TestDlg dlg;
  
  dlg.DoModal();
}
