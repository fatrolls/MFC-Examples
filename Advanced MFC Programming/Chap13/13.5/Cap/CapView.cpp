#include "stdafx.h"
#include "Cap.h"
#include "CapDoc.h"
#include "CapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCapView, CView)

BEGIN_MESSAGE_MAP(CCapView, CView)
	//{{AFX_MSG_MAP(CCapView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CCapView::CCapView()
{
}

CCapView::~CCapView()
{
}

BOOL CCapView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CCapView::OnDraw(CDC* pDC)
{
	CCapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CCapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CCapView::AssertValid() const
{
	CView::AssertValid();
}

void CCapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCapDoc* CCapView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCapDoc)));
	return (CCapDoc*)m_pDocument;
}
#endif

