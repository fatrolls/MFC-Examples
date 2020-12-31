#include "stdafx.h"
#include "Help.h"
#include "HelpDoc.h"
#include "HelpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CHelpView, CView)

BEGIN_MESSAGE_MAP(CHelpView, CView)
	//{{AFX_MSG_MAP(CHelpView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CHelpView::CHelpView()
{
}

CHelpView::~CHelpView()
{
}

BOOL CHelpView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CHelpView::OnDraw(CDC* pDC)
{
	CHelpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CHelpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHelpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CHelpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CHelpView::AssertValid() const
{
	CView::AssertValid();
}

void CHelpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHelpDoc* CHelpView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHelpDoc)));
	return (CHelpDoc*)m_pDocument;
}
#endif

