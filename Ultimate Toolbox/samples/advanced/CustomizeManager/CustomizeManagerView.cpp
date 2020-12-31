// CustomizeManagerView.cpp : implementation of the CCustomizeManagerView class
//

#include "stdafx.h"
#include "CustomizeManager.h"

#include "CustomizeManagerDoc.h"
#include "CustomizeManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView

IMPLEMENT_DYNCREATE(CCustomizeManagerView, CView)

BEGIN_MESSAGE_MAP(CCustomizeManagerView, CView)
	//{{AFX_MSG_MAP(CCustomizeManagerView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView construction/destruction

CCustomizeManagerView::CCustomizeManagerView()
{
	// TODO: add construction code here

}

CCustomizeManagerView::~CCustomizeManagerView()
{
}

BOOL CCustomizeManagerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView drawing

void CCustomizeManagerView::OnDraw(CDC* /*pDC*/)
{
	CCustomizeManagerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView printing

BOOL CCustomizeManagerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCustomizeManagerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCustomizeManagerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView diagnostics

#ifdef _DEBUG
void CCustomizeManagerView::AssertValid() const
{
	CView::AssertValid();
}

void CCustomizeManagerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCustomizeManagerDoc* CCustomizeManagerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCustomizeManagerDoc)));
	return (CCustomizeManagerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCustomizeManagerView message handlers
