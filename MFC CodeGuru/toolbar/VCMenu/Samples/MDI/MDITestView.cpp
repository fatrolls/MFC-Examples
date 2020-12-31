// MDITestView.cpp : implementation of the CMDITestView class
//

#include "stdafx.h"
#include "MDITest.h"

#include "MDITestDoc.h"
#include "MDITestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDITestView

IMPLEMENT_DYNCREATE(CMDITestView, CView)

BEGIN_MESSAGE_MAP(CMDITestView, CView)
	//{{AFX_MSG_MAP(CMDITestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDITestView construction/destruction

CMDITestView::CMDITestView()
{
	// TODO: add construction code here

}

CMDITestView::~CMDITestView()
{
}

BOOL CMDITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMDITestView drawing

void CMDITestView::OnDraw(CDC* pDC)
{
	CMDITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMDITestView printing

BOOL CMDITestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMDITestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMDITestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMDITestView diagnostics

#ifdef _DEBUG
void CMDITestView::AssertValid() const
{
	CView::AssertValid();
}

void CMDITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMDITestDoc* CMDITestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMDITestDoc)));
	return (CMDITestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDITestView message handlers
