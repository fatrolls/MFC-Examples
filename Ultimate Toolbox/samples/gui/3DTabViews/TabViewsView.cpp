// TabViewsView.cpp : implementation of the CTabViewsView class
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView

IMPLEMENT_DYNCREATE(CTabViewsView, CEditView)

BEGIN_MESSAGE_MAP(CTabViewsView, CEditView)
	//{{AFX_MSG_MAP(CTabViewsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView construction/destruction

CTabViewsView::CTabViewsView()
{
	// TODO: add construction code here

}

CTabViewsView::~CTabViewsView()
{
}

BOOL CTabViewsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CEditView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView drawing

void CTabViewsView::OnDraw(CDC* pDC)
{
	CTabViewsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	UNREFERENCED_PARAMETER(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView printing

BOOL CTabViewsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTabViewsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTabViewsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView diagnostics

#ifdef _DEBUG
void CTabViewsView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTabViewsView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTabViewsDoc* CTabViewsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTabViewsDoc)));
	return (CTabViewsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabViewsView message handlers
