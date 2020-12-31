// RegExpressionView.cpp : implementation of the CRegExpressionView class
//

#include "stdafx.h"
#include "RegExpression.h"

#include "RegExpressionDoc.h"
#include "RegExpressionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionView

IMPLEMENT_DYNCREATE(CRegExpressionView, CEditView)

BEGIN_MESSAGE_MAP(CRegExpressionView, CEditView)
	//{{AFX_MSG_MAP(CRegExpressionView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionView construction/destruction

CRegExpressionView::CRegExpressionView()
{
	// TODO: add construction code here

}

CRegExpressionView::~CRegExpressionView()
{
}

BOOL CRegExpressionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionView drawing

void CRegExpressionView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	CRegExpressionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionView diagnostics

#ifdef _DEBUG
void CRegExpressionView::AssertValid() const
{
	CEditView::AssertValid();
}

void CRegExpressionView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CRegExpressionDoc* CRegExpressionView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRegExpressionDoc)));
	return (CRegExpressionDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionView message handlers
