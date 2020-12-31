#include "stdafx.h"
#include "Once.h"
#include "OnceDoc.h"
#include "OnceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(COnceView, CView)

BEGIN_MESSAGE_MAP(COnceView, CView)
	//{{AFX_MSG_MAP(COnceView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

COnceView::COnceView()
{
}

COnceView::~COnceView()
{
}

BOOL COnceView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void COnceView::OnDraw(CDC* pDC)
{
	COnceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL COnceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void COnceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void COnceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void COnceView::AssertValid() const
{
	CView::AssertValid();
}

void COnceView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COnceDoc* COnceView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COnceDoc)));
	return (COnceDoc*)m_pDocument;
}
#endif

