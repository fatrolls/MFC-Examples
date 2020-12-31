// ButtonView.cpp : implementation of the CButtonView class
//

#include "stdafx.h"
#include "Button.h"

#include "ButtonDoc.h"
#include "ButtonView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonView

IMPLEMENT_DYNCREATE(CButtonView, CView)

BEGIN_MESSAGE_MAP(CButtonView, CView)
	//{{AFX_MSG_MAP(CButtonView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonView construction/destruction

CButtonView::CButtonView()
{
	// TODO: add construction code here

}

CButtonView::~CButtonView()
{
}

BOOL CButtonView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CButtonView drawing

void CButtonView::OnDraw(CDC* pDC)
{
	CButtonDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CButtonView printing

BOOL CButtonView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CButtonView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CButtonView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CButtonView diagnostics

#ifdef _DEBUG
void CButtonView::AssertValid() const
{
	CView::AssertValid();
}

void CButtonView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CButtonDoc* CButtonView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CButtonDoc)));
	return (CButtonDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CButtonView message handlers
