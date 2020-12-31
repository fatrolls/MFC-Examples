// MenuView.cpp : implementation of the CMenuView class
//

#include "stdafx.h"
#include "Menu.h"

#include "MenuDoc.h"
#include "MenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMenuView

IMPLEMENT_DYNCREATE(CMenuView, CView)

BEGIN_MESSAGE_MAP(CMenuView, CView)
	//{{AFX_MSG_MAP(CMenuView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMenuView construction/destruction

CMenuView::CMenuView()
{
	// TODO: add construction code here

}

CMenuView::~CMenuView()
{
}

BOOL CMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMenuView drawing

void CMenuView::OnDraw(CDC* pDC)
{
	CMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMenuView diagnostics

#ifdef _DEBUG
void CMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMenuDoc* CMenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMenuDoc)));
	return (CMenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMenuView message handlers
