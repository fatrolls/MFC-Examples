// OtherView.cpp : implementation of the COtherView class
//

#include "stdafx.h"
#include "Scribble.h"

#include "OtherDoc.h"
#include "OtherView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtherView

IMPLEMENT_DYNCREATE(COtherView, CView)

BEGIN_MESSAGE_MAP(COtherView, CView)
	//{{AFX_MSG_MAP(COtherView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtherView construction/destruction

COtherView::COtherView()
{
	// TODO: add construction code here

}

COtherView::~COtherView()
{
}

BOOL COtherView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COtherView drawing

void COtherView::OnDraw(CDC* pDC)
{
	COtherDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COtherView printing

BOOL COtherView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COtherView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COtherView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COtherView diagnostics

#ifdef _DEBUG
void COtherView::AssertValid() const
{
	CView::AssertValid();
}

void COtherView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COtherDoc* COtherView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COtherDoc)));
	return (COtherDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COtherView message handlers
