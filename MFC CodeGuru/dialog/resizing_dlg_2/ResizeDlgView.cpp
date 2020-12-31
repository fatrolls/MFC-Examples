// ResizeDlgView.cpp : implementation of the CResizeDlgView class
//

#include "stdafx.h"
#include "ResizeDlg.h"

#include "ResizeDlgDoc.h"
#include "ResizeDlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView

IMPLEMENT_DYNCREATE(CResizeDlgView, CView)

BEGIN_MESSAGE_MAP(CResizeDlgView, CView)
	//{{AFX_MSG_MAP(CResizeDlgView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView construction/destruction

CResizeDlgView::CResizeDlgView()
{
	// TODO: add construction code here

}

CResizeDlgView::~CResizeDlgView()
{
}

BOOL CResizeDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView drawing

void CResizeDlgView::OnDraw(CDC* pDC)
{
	CResizeDlgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView printing

BOOL CResizeDlgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CResizeDlgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CResizeDlgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView diagnostics

#ifdef _DEBUG
void CResizeDlgView::AssertValid() const
{
	CView::AssertValid();
}

void CResizeDlgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CResizeDlgDoc* CResizeDlgView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CResizeDlgDoc)));
	return (CResizeDlgDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CResizeDlgView message handlers
