#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CScrollView)

BEGIN_MESSAGE_MAP(CGDIView, CScrollView)
	//{{AFX_MSG_MAP(CGDIView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CScrollView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC *pDC)
{
	CBitmap *pBmp;
	CBitmap *pBmpOld;
	CDC dcMemory;
	BITMAP bm;

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	dcMemory.CreateCompatibleDC(pDC);
	pBmp=pDoc->GetBitmap();
	pBmpOld=dcMemory.SelectObject(pBmp);
	pBmp->GetBitmap(&bm);
	pDC->StretchBlt
	(
		0,
		0,
		2*bm.bmWidth,
		2*bm.bmHeight,
		&dcMemory,
		0,
		0,
		bm.bmWidth,
		bm.bmHeight,
		SRCCOPY
	);
	dcMemory.SelectObject(pBmpOld);
}

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif

void CGDIView::OnInitialUpdate() 
{
	CGDIDoc *pDoc;
	CBitmap *pBmp;
	BITMAP bm;

	pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pBmp=pDoc->GetBitmap();
	pBmp->GetBitmap(&bm);
	SetScrollSizes(MM_TEXT, CSize(2*bm.bmWidth, 2*bm.bmHeight));

	CScrollView::OnInitialUpdate();
}
