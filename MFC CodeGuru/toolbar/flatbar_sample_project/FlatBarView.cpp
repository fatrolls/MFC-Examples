// FlatBarView.cpp : implementation of the CFlatBarView class
//

#include "stdafx.h"
#include "FlatBar.h"

#include "FlatBarDoc.h"
#include "FlatBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView

IMPLEMENT_DYNCREATE(CFlatBarView, CView)

BEGIN_MESSAGE_MAP(CFlatBarView, CView)
	//{{AFX_MSG_MAP(CFlatBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView construction/destruction

CFlatBarView::CFlatBarView()
{
	// TODO: add construction code here

}

CFlatBarView::~CFlatBarView()
{
}

BOOL CFlatBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView drawing

void CFlatBarView::OnDraw(CDC* pDC)
{
	CFlatBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView printing

BOOL CFlatBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFlatBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFlatBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView diagnostics

#ifdef _DEBUG
void CFlatBarView::AssertValid() const
{
	CView::AssertValid();
}

void CFlatBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlatBarDoc* CFlatBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlatBarDoc)));
	return (CFlatBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlatBarView message handlers
