// dockdemoView.cpp : implementation of the CDockdemoView class
//

#include "stdafx.h"
#include "dockdemo.h"

#include "dockdemoDoc.h"
#include "dockdemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView

IMPLEMENT_DYNCREATE(CDockdemoView, CView)

BEGIN_MESSAGE_MAP(CDockdemoView, CView)
	//{{AFX_MSG_MAP(CDockdemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView construction/destruction

CDockdemoView::CDockdemoView()
{
	// TODO: add construction code here

}

CDockdemoView::~CDockdemoView()
{
}

BOOL CDockdemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView drawing

void CDockdemoView::OnDraw(CDC* pDC)
{
	CDockdemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView printing

BOOL CDockdemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDockdemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDockdemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView diagnostics

#ifdef _DEBUG
void CDockdemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDockdemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDockdemoDoc* CDockdemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDockdemoDoc)));
	return (CDockdemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockdemoView message handlers
