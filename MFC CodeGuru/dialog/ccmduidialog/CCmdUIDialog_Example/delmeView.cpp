// delmeView.cpp : implementation of the CDelmeView class
//

#include "stdafx.h"
#include "delme.h"

#include "delmeDoc.h"
#include "delmeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDelmeView

IMPLEMENT_DYNCREATE(CDelmeView, CView)

BEGIN_MESSAGE_MAP(CDelmeView, CView)
	//{{AFX_MSG_MAP(CDelmeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDelmeView construction/destruction

CDelmeView::CDelmeView()
{
	// TODO: add construction code here

}

CDelmeView::~CDelmeView()
{
}

BOOL CDelmeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDelmeView drawing

void CDelmeView::OnDraw(CDC* pDC)
{
	CDelmeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDelmeView printing

BOOL CDelmeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDelmeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDelmeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDelmeView diagnostics

#ifdef _DEBUG
void CDelmeView::AssertValid() const
{
	CView::AssertValid();
}

void CDelmeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDelmeDoc* CDelmeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDelmeDoc)));
	return (CDelmeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDelmeView message handlers
