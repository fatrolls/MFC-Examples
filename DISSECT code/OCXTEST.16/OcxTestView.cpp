// OcxTestView.cpp : implementation of the COcxTestView class
//

#include "stdafx.h"
#include "OcxTest.h"

#include "OcxTestDoc.h"
#include "OcxTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COcxTestView

IMPLEMENT_DYNCREATE(COcxTestView, CView)

BEGIN_MESSAGE_MAP(COcxTestView, CView)
	//{{AFX_MSG_MAP(COcxTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COcxTestView construction/destruction

COcxTestView::COcxTestView()
{
	// TODO: add construction code here

}

COcxTestView::~COcxTestView()
{
}

BOOL COcxTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COcxTestView drawing

void COcxTestView::OnDraw(CDC* pDC)
{
	COcxTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COcxTestView printing

BOOL COcxTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COcxTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COcxTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COcxTestView diagnostics

#ifdef _DEBUG
void COcxTestView::AssertValid() const
{
	CView::AssertValid();
}

void COcxTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COcxTestDoc* COcxTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COcxTestDoc)));
	return (COcxTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COcxTestView message handlers
