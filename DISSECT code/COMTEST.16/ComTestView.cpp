// ComTestView.cpp : implementation of the CComTestView class
//

#include "stdafx.h"
#include "ComTest.h"

#include "ComTestDoc.h"
#include "ComTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComTestView

IMPLEMENT_DYNCREATE(CComTestView, CView)

BEGIN_MESSAGE_MAP(CComTestView, CView)
	//{{AFX_MSG_MAP(CComTestView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComTestView construction/destruction

CComTestView::CComTestView()
{
	// TODO: add construction code here

}

CComTestView::~CComTestView()
{
}

BOOL CComTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CComTestView drawing

void CComTestView::OnDraw(CDC* pDC)
{
	CComTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CComTestView printing

BOOL CComTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CComTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CComTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CComTestView diagnostics

#ifdef _DEBUG
void CComTestView::AssertValid() const
{
	CView::AssertValid();
}

void CComTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CComTestDoc* CComTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CComTestDoc)));
	return (CComTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CComTestView message handlers
