#include "stdafx.h"
#include "Hook.h"
#include "HookDoc.h"
#include "HookView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CHookView, CView)

BEGIN_MESSAGE_MAP(CHookView, CView)
	//{{AFX_MSG_MAP(CHookView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CHookView::CHookView()
{
}

CHookView::~CHookView()
{
}

BOOL CHookView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CHookView::OnDraw(CDC* pDC)
{
	CHookDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CHookView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHookView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CHookView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CHookView::AssertValid() const
{
	CView::AssertValid();
}

void CHookView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHookDoc* CHookView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHookDoc)));
	return (CHookDoc*)m_pDocument;
}
#endif
