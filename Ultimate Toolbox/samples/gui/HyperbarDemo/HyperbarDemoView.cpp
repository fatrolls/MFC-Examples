// HyperbarDemoView.cpp : implementation of the CHyperbarDemoView class
//

#include "stdafx.h"
#include "HyperbarDemo.h"

#include "HyperbarDemoDoc.h"
#include "HyperbarDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView

IMPLEMENT_DYNCREATE(CHyperbarDemoView, CView)

BEGIN_MESSAGE_MAP(CHyperbarDemoView, CView)
	//{{AFX_MSG_MAP(CHyperbarDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView construction/destruction

CHyperbarDemoView::CHyperbarDemoView()
{
	// TODO: add construction code here

}

CHyperbarDemoView::~CHyperbarDemoView()
{
}

BOOL CHyperbarDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView drawing

void CHyperbarDemoView::OnDraw(CDC* pDC)
{
	CHyperbarDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView printing

BOOL CHyperbarDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHyperbarDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHyperbarDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView diagnostics

#ifdef _DEBUG
void CHyperbarDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CHyperbarDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHyperbarDemoDoc* CHyperbarDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHyperbarDemoDoc)));
	return (CHyperbarDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoView message handlers
