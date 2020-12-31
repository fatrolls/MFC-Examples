// LayoutManagerView.cpp : implementation of the CLayoutManagerView class
//

#include "stdafx.h"
#include "LayoutManager.h"

#include "LayoutManagerDoc.h"
#include "LayoutManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerView

IMPLEMENT_DYNCREATE(CLayoutManagerView, CView)

BEGIN_MESSAGE_MAP(CLayoutManagerView, CView)
	//{{AFX_MSG_MAP(CLayoutManagerView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerView construction/destruction

CLayoutManagerView::CLayoutManagerView()
{
}

CLayoutManagerView::~CLayoutManagerView()
{
}

BOOL CLayoutManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerView drawing

void CLayoutManagerView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);
	CLayoutManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerView diagnostics

#ifdef _DEBUG
void CLayoutManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CLayoutManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLayoutManagerDoc* CLayoutManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLayoutManagerDoc)));
	return (CLayoutManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerView message handlers

void CLayoutManagerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	m_dlgDemo.ShowWindow(SW_SHOW);
	m_LayoutManager.Attach(this);
	m_LayoutManager.SetConstraint(&m_dlgDemo, OX_LMS_ANY, OX_LMT_SAME);
	m_LayoutManager.RedrawLayout();
}

BOOL CLayoutManagerView::OnEraseBkgnd(CDC* pDC) 
{
	UNREFERENCED_PARAMETER(pDC);
	return 0;
}

int CLayoutManagerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_dlgDemo.Create(IDD_DEMO, this);
	m_dlgDemo.SetDlgCtrlID(IDD_DEMO);
	
	return 0;
}
