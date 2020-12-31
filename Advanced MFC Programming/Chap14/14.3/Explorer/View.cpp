#include "stdafx.h"
#include "Explorer.h"
#include "Doc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CExplorerView, CListView)

BEGIN_MESSAGE_MAP(CExplorerView, CListView)
	//{{AFX_MSG_MAP(CExplorerView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

CExplorerView::CExplorerView()
{
}

CExplorerView::~CExplorerView()
{
}

BOOL CExplorerView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListView::PreCreateWindow(cs);
}

void CExplorerView::OnDraw(CDC* pDC)
{
	CExplorerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CExplorerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CExplorerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CExplorerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CExplorerView::AssertValid() const
{
	CListView::AssertValid();
}

void CExplorerView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CExplorerDoc* CExplorerView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExplorerDoc)));
	return (CExplorerDoc*)m_pDocument;
}
#endif
