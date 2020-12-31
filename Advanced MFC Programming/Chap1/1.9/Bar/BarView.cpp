#include "stdafx.h"
#include "Bar.h"
#include "BarDoc.h"
#include "BarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBarView, CView)

BEGIN_MESSAGE_MAP(CBarView, CView)
	//{{AFX_MSG_MAP(CBarView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CBarView::CBarView()
{
}

CBarView::~CBarView()
{
}

BOOL CBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CBarView::OnDraw(CDC* pDC)
{
	CBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CBarView::AssertValid() const
{
	CView::AssertValid();
}

void CBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBarDoc* CBarView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBarDoc)));
	return (CBarDoc*)m_pDocument;
}
#endif
