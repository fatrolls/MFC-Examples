// TreeMenuDemoView.cpp : implementation of the CTreeMenuDemoView class
//

#include "stdafx.h"
#include "TreeMenuDemo.h"

#include "TreeMenuDemoDoc.h"
#include "TreeMenuDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoView

IMPLEMENT_DYNCREATE(CTreeMenuDemoView, CView)

BEGIN_MESSAGE_MAP(CTreeMenuDemoView, CView)
	//{{AFX_MSG_MAP(CTreeMenuDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoView construction/destruction

CTreeMenuDemoView::CTreeMenuDemoView()
{
	// TODO: add construction code here

}

CTreeMenuDemoView::~CTreeMenuDemoView()
{
}

BOOL CTreeMenuDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoView drawing

void CTreeMenuDemoView::OnDraw(CDC* pDC)
{
	CTreeMenuDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoView diagnostics

#ifdef _DEBUG
void CTreeMenuDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTreeMenuDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTreeMenuDemoDoc* CTreeMenuDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeMenuDemoDoc)));
	return (CTreeMenuDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoView message handlers
