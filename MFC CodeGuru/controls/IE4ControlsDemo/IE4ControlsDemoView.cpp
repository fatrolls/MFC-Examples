// IE4ControlsDemoView.cpp : implementation of the CIE4ControlsDemoView class
//

#include "stdafx.h"
#include "IE4ControlsDemo.h"

#include "IE4ControlsDemoDoc.h"
#include "IE4ControlsDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoView

IMPLEMENT_DYNCREATE(CIE4ControlsDemoView, CView)

BEGIN_MESSAGE_MAP(CIE4ControlsDemoView, CView)
	//{{AFX_MSG_MAP(CIE4ControlsDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoView construction/destruction

CIE4ControlsDemoView::CIE4ControlsDemoView()
{
	// TODO: add construction code here

}

CIE4ControlsDemoView::~CIE4ControlsDemoView()
{
}

BOOL CIE4ControlsDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoView drawing

void CIE4ControlsDemoView::OnDraw(CDC* pDC)
{
	CIE4ControlsDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoView diagnostics

#ifdef _DEBUG
void CIE4ControlsDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CIE4ControlsDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIE4ControlsDemoDoc* CIE4ControlsDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIE4ControlsDemoDoc)));
	return (CIE4ControlsDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIE4ControlsDemoView message handlers
