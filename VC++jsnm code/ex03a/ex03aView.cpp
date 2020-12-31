// ex03aView.cpp : implementation of the CEx03aView class
//

#include "stdafx.h"
#include "ex03a.h"

#include "ex03aDoc.h"
#include "ex03aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx03aView

IMPLEMENT_DYNCREATE(CEx03aView, CView)

BEGIN_MESSAGE_MAP(CEx03aView, CView)
	//{{AFX_MSG_MAP(CEx03aView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx03aView construction/destruction

CEx03aView::CEx03aView()
{
	// TODO: add construction code here

}

CEx03aView::~CEx03aView()
{
}

BOOL CEx03aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx03aView drawing

void CEx03aView::OnDraw(CDC* pDC)
{
	pDC->TextOut(0, 0, "Hello, world!");  // prints in default font
	                                      //  & size, top left corner
	pDC->SelectStockObject(GRAY_BRUSH);   // selects a brush for the
	                                      //  circle interior
	pDC->Ellipse(CRect(0, 20, 100, 120)); // draws a gray circle
	                                      //  100 units in diameter
}

/////////////////////////////////////////////////////////////////////////////
// CEx03aView printing

BOOL CEx03aView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx03aView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx03aView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CEx03aView diagnostics

#ifdef _DEBUG
void CEx03aView::AssertValid() const
{
	CView::AssertValid();
}

void CEx03aView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx03aDoc* CEx03aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx03aDoc)));
	return (CEx03aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx03aView message handlers
