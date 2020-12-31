// SingleDemoView.cpp : implementation of the CSingleDemoView class
//

#include "stdafx.h"
#include "SingleDemo.h"

#include "SingleDemoDoc.h"
#include "SingleDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoView

IMPLEMENT_DYNCREATE(CSingleDemoView, CView)

BEGIN_MESSAGE_MAP(CSingleDemoView, CView)
	//{{AFX_MSG_MAP(CSingleDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoView construction/destruction

CSingleDemoView::CSingleDemoView()
{
	// TODO: add construction code here

}

CSingleDemoView::~CSingleDemoView()
{
}

BOOL CSingleDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoView drawing

void CSingleDemoView::OnDraw(CDC* pDC)
{
	CSingleDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoView diagnostics

#ifdef _DEBUG
void CSingleDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CSingleDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDemoDoc* CSingleDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDemoDoc)));
	return (CSingleDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSingleDemoView message handlers
