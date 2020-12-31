#include "stdafx.h"
#include "DB.h"
#include "DBDoc.h"
#include "DBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CDBView, CView)

BEGIN_MESSAGE_MAP(CDBView, CView)
	//{{AFX_MSG_MAP(CDBView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CDBView::CDBView()
{
}

CDBView::~CDBView()
{
}

BOOL CDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CDBView::OnDraw(CDC* pDC)
{
	CDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CDBView::AssertValid() const
{
	CView::AssertValid();
}

void CDBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDBDoc* CDBView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBDoc)));
	return (CDBDoc*)m_pDocument;
}
#endif