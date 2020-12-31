// CmDgTestView.cpp : implementation of the CCmDgTestView class
//

#include "stdafx.h"
#include "CmDgTest.h"

#include "CmDgTestDoc.h"
#include "CmDgTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView

IMPLEMENT_DYNCREATE(CCmDgTestView, CView)

BEGIN_MESSAGE_MAP(CCmDgTestView, CView)
	//{{AFX_MSG_MAP(CCmDgTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView construction/destruction

CCmDgTestView::CCmDgTestView()
{
	// TODO: add construction code here

}

CCmDgTestView::~CCmDgTestView()
{
}

BOOL CCmDgTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView drawing

void CCmDgTestView::OnDraw(CDC* pDC)
{
	CCmDgTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDC->TextOut(100, 100, "Select \'File|Open\' to see the sample file-open dialog.");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView printing

BOOL CCmDgTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCmDgTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCmDgTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView diagnostics

#ifdef _DEBUG
void CCmDgTestView::AssertValid() const
{
	CView::AssertValid();
}

void CCmDgTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCmDgTestDoc* CCmDgTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCmDgTestDoc)));
	return (CCmDgTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCmDgTestView message handlers
