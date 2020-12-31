// OutLookStyleView.cpp : implementation of the COutLookStyleView class
//

#include "stdafx.h"
#include "OutLookStyle.h"

#include "OutLookStyleDoc.h"
#include "OutLookStyleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView

IMPLEMENT_DYNCREATE(COutLookStyleView, CView)

BEGIN_MESSAGE_MAP(COutLookStyleView, CView)
	//{{AFX_MSG_MAP(COutLookStyleView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView construction/destruction

COutLookStyleView::COutLookStyleView()
{
	// TODO: add construction code here

}

COutLookStyleView::~COutLookStyleView()
{
}

BOOL COutLookStyleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView drawing

void COutLookStyleView::OnDraw(CDC* pDC)
{
	COutLookStyleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView printing

BOOL COutLookStyleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COutLookStyleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutLookStyleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView diagnostics

#ifdef _DEBUG
void COutLookStyleView::AssertValid() const
{
	CView::AssertValid();
}

void COutLookStyleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutLookStyleDoc* COutLookStyleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutLookStyleDoc)));
	return (COutLookStyleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutLookStyleView message handlers
