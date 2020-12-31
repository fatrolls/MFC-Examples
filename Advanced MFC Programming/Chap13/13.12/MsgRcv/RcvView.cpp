#include "stdafx.h"
#include "MsgRcv.h"

#include "RcvDoc.h"
#include "RcvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMsgRcvView, CEditView)

BEGIN_MESSAGE_MAP(CMsgRcvView, CEditView)
	//{{AFX_MSG_MAP(CMsgRcvView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

CMsgRcvView::CMsgRcvView()
{
}

CMsgRcvView::~CMsgRcvView()
{
}

BOOL CMsgRcvView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CEditView::PreCreateWindow(cs);
}

void CMsgRcvView::OnDraw(CDC* pDC)
{
	CMsgRcvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

void CMsgRcvView::OnInitialUpdate()
{
	CEditView::OnInitialUpdate();
}

BOOL CMsgRcvView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CMsgRcvView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CMsgRcvView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CMsgRcvView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMsgRcvView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMsgRcvDoc* CMsgRcvView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMsgRcvDoc)));
	return (CMsgRcvDoc*)m_pDocument;
}
#endif
