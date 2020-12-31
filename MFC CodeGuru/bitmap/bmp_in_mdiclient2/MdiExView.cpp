// MdiExView.cpp : implementation of the CMdiExView class
//

#include "stdafx.h"
#include "MdiEx.h"

#include "MdiExDoc.h"
#include "MdiExView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdiExView

IMPLEMENT_DYNCREATE(CMdiExView, CView)

BEGIN_MESSAGE_MAP(CMdiExView, CView)
	//{{AFX_MSG_MAP(CMdiExView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdiExView construction/destruction

CMdiExView::CMdiExView()
{
	// TODO: add construction code here

}

CMdiExView::~CMdiExView()
{
}

BOOL CMdiExView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMdiExView drawing

void CMdiExView::OnDraw(CDC* pDC)
{
	CMdiExDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMdiExView diagnostics

#ifdef _DEBUG
void CMdiExView::AssertValid() const
{
	CView::AssertValid();
}

void CMdiExView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMdiExDoc* CMdiExView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdiExDoc)));
	return (CMdiExDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdiExView message handlers
