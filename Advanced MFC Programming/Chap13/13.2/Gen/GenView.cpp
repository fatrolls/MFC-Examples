// GenView.cpp : implementation of the CGenView class
//

#include "stdafx.h"
#include "Gen.h"

#include "GenDoc.h"
#include "GenView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenView

IMPLEMENT_DYNCREATE(CGenView, CView)

BEGIN_MESSAGE_MAP(CGenView, CView)
	//{{AFX_MSG_MAP(CGenView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenView construction/destruction

CGenView::CGenView()
{
}

CGenView::~CGenView()
{
}

BOOL CGenView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGenView drawing

void CGenView::OnDraw(CDC* pDC)
{
	CGenDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CGenView printing

BOOL CGenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CGenView diagnostics

#ifdef _DEBUG
void CGenView::AssertValid() const
{
	CView::AssertValid();
}

void CGenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGenDoc* CGenView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGenDoc)));
	return (CGenDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenView message handlers
