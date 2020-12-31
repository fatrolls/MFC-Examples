#include "stdafx.h"
#include "Spw.h"
#include "SpwDoc.h"
#include "SpwView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSpwView, CView)

BEGIN_MESSAGE_MAP(CSpwView, CView)
	//{{AFX_MSG_MAP(CSpwView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CSpwView::CSpwView()
{
}

CSpwView::~CSpwView()
{
}

BOOL CSpwView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CSpwView::OnDraw(CDC* pDC)
{
	CSpwDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CSpwView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CSpwView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CSpwView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CSpwView::AssertValid() const
{
	CView::AssertValid();
}

void CSpwView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpwDoc* CSpwView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpwDoc)));
	return (CSpwDoc*)m_pDocument;
}
#endif
