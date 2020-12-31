// SDITestView.cpp : implementation of the CSDITestView class
//

#include "stdafx.h"
#include "SDITest.h"

#include "SDITestDoc.h"
#include "SDITestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDITestView

IMPLEMENT_DYNCREATE(CSDITestView, CView)

BEGIN_MESSAGE_MAP(CSDITestView, CView)
	//{{AFX_MSG_MAP(CSDITestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDITestView construction/destruction

CSDITestView::CSDITestView()
{
	// TODO: add construction code here

}

CSDITestView::~CSDITestView()
{
}

BOOL CSDITestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDITestView drawing

void CSDITestView::OnDraw(CDC* pDC)
{
	CSDITestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSDITestView printing

BOOL CSDITestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDITestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDITestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSDITestView diagnostics

#ifdef _DEBUG
void CSDITestView::AssertValid() const
{
	CView::AssertValid();
}

void CSDITestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDITestDoc* CSDITestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDITestDoc)));
	return (CSDITestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDITestView message handlers
