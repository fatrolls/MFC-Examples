// CreditsTestView.cpp : implementation of the CCreditsTestView class
//

#include "stdafx.h"
#include "CreditsTest.h"

#include "CreditsTestDoc.h"
#include "CreditsTestView.h"
#include "CreditDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView

IMPLEMENT_DYNCREATE(CCreditsTestView, CView)

BEGIN_MESSAGE_MAP(CCreditsTestView, CView)
	//{{AFX_MSG_MAP(CCreditsTestView)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView construction/destruction

CCreditsTestView::CCreditsTestView()
{
}

CCreditsTestView::~CCreditsTestView()
{
}

BOOL CCreditsTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView drawing

void CCreditsTestView::OnDraw(CDC* pDC)
{
	CCreditsTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView printing

BOOL CCreditsTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCreditsTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCreditsTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView diagnostics

#ifdef _DEBUG
void CCreditsTestView::AssertValid() const
{
	CView::AssertValid();
}

void CCreditsTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCreditsTestDoc* CCreditsTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCreditsTestDoc)));
	return (CCreditsTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCreditsTestView message handlers

void CCreditsTestView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CCreditDialog dlg;

	dlg.DoModal();
	
	CView::OnLButtonDblClk(nFlags, point);
}
