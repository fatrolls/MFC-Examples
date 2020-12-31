#include "stdafx.h"
#include "CDB.h"
#include "CDBDoc.h"
#include "CDBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CCDBView, CView)

BEGIN_MESSAGE_MAP(CCDBView, CView)
	//{{AFX_MSG_MAP(CCDBView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CCDBView::CCDBView()
{
}

CCDBView::~CCDBView()
{
}

BOOL CCDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CCDBView::OnDraw(CDC* pDC)
{
	CCDBDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CCDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CCDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CCDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CCDBView::AssertValid() const
{
	CView::AssertValid();
}

void CCDBView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCDBDoc* CCDBView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCDBDoc)));
	return (CCDBDoc*)m_pDocument;
}
#endif