// SideBySideToolbarsView.cpp : implementation of the CSideBySideToolbarsView class
//

#include "stdafx.h"
#include "SideBySideToolbars.h"

#include "SideBySideToolbarsDoc.h"
#include "SideBySideToolbarsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView

IMPLEMENT_DYNCREATE(CSideBySideToolbarsView, CView)

BEGIN_MESSAGE_MAP(CSideBySideToolbarsView, CView)
	//{{AFX_MSG_MAP(CSideBySideToolbarsView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView construction/destruction

CSideBySideToolbarsView::CSideBySideToolbarsView()
{
	// TODO: add construction code here

}

CSideBySideToolbarsView::~CSideBySideToolbarsView()
{
}

BOOL CSideBySideToolbarsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView drawing

void CSideBySideToolbarsView::OnDraw(CDC* pDC)
{
	CSideBySideToolbarsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView printing

BOOL CSideBySideToolbarsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSideBySideToolbarsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSideBySideToolbarsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView diagnostics

#ifdef _DEBUG
void CSideBySideToolbarsView::AssertValid() const
{
	CView::AssertValid();
}

void CSideBySideToolbarsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSideBySideToolbarsDoc* CSideBySideToolbarsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSideBySideToolbarsDoc)));
	return (CSideBySideToolbarsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSideBySideToolbarsView message handlers
