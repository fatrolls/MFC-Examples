// ex14aView.cpp : implementation of the CEx14aView class
//

#include "stdafx.h"
#include "ex14a.h"

#include "ex14aDoc.h"
#include "ex14aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx14aView

IMPLEMENT_DYNCREATE(CEx14aView, CView)

BEGIN_MESSAGE_MAP(CEx14aView, CView)
	//{{AFX_MSG_MAP(CEx14aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx14aView construction/destruction

CEx14aView::CEx14aView()
{
	// TODO: add construction code here

}

CEx14aView::~CEx14aView()
{
}

BOOL CEx14aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx14aView drawing

void CEx14aView::OnDraw(CDC* pDC)
{
	CEx14aDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx14aView diagnostics

#ifdef _DEBUG
void CEx14aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx14aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx14aDoc* CEx14aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx14aDoc)));
	return (CEx14aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx14aView message handlers
