// MdLessPpshView.cpp : implementation of the CMdLessPpshView class
//

#include "stdafx.h"
#include "MdLessPpsh.h"

#include "MdLessPpshDoc.h"
#include "MdLessPpshView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView

IMPLEMENT_DYNCREATE(CMdLessPpshView, CView)

BEGIN_MESSAGE_MAP(CMdLessPpshView, CView)
	//{{AFX_MSG_MAP(CMdLessPpshView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView construction/destruction

CMdLessPpshView::CMdLessPpshView()
{
	// TODO: add construction code here

}

CMdLessPpshView::~CMdLessPpshView()
{
}

BOOL CMdLessPpshView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView drawing

void CMdLessPpshView::OnDraw(CDC* pDC)
{
	CMdLessPpshDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView printing

BOOL CMdLessPpshView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMdLessPpshView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMdLessPpshView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView diagnostics

#ifdef _DEBUG
void CMdLessPpshView::AssertValid() const
{
	CView::AssertValid();
}

void CMdLessPpshView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMdLessPpshDoc* CMdLessPpshView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMdLessPpshDoc)));
	return (CMdLessPpshDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMdLessPpshView message handlers
