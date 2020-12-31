// ex10dView.cpp : implementation of the CEx10dView class
//

#include "stdafx.h"
#include "ex10d.h"

#include "ex10dDoc.h"
#include "ex10dView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx10dView

IMPLEMENT_DYNCREATE(CEx10dView, CView)

BEGIN_MESSAGE_MAP(CEx10dView, CView)
	//{{AFX_MSG_MAP(CEx10dView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx10dView construction/destruction

CEx10dView::CEx10dView()
{
	// TODO: add construction code here

}

CEx10dView::~CEx10dView()
{
}

BOOL CEx10dView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx10dView drawing

void CEx10dView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Choose About from the Help menu.");
}

/////////////////////////////////////////////////////////////////////////////
// CEx10dView diagnostics

#ifdef _DEBUG
void CEx10dView::AssertValid() const
{
	CView::AssertValid();
}

void CEx10dView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx10dDoc* CEx10dView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx10dDoc)));
	return (CEx10dDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx10dView message handlers
