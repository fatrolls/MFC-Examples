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
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
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
	CString szText;
	CFont *ptrFontOld;

	CGDIDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	szText=pDoc->GetText();
	ptrFontOld=pDC->SelectObject(pDoc->GetFont());
	pDC->TextOut(0, 0, szText);
	pDC->SelectObject(ptrFontOld);
}

void CGDIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal;
	sizeTotal.cx=sizeTotal.cy=100;
	SetScrollSizes(MM_TEXT, sizeTotal);
	CreateNewCaret(FALSE);
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

void CGDIView::OnDestroy() 
{
	HideCaret();
	::DestroyCaret();
	CScrollView::OnDestroy();
}

void CGDIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	CGDIDoc *ptrDoc;

	ptrDoc=(CGDIDoc *)GetDocument();
	ASSERT(ptrDoc);
	switch(nChar)
	{
		case VK_LEFT:
		{
			ptrDoc->BackwardCaret();
			break;
		}
		case VK_RIGHT:
		{
			ptrDoc->ForwardCaret();
			break;
		}

	}
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGDIView::RedrawCaret()
{
	CGDIDoc *ptrDoc;

	ptrDoc=(CGDIDoc *)GetDocument();
	HideCaret();
	SetCaretPos(ptrDoc->GetCaretPosition());
	ShowCaret();
}

void CGDIView::CreateNewCaret(BOOL bDestroy)
{
	CGDIDoc *ptrDoc;

	if(bDestroy == TRUE)::DestroyCaret();
	ptrDoc=(CGDIDoc *)GetDocument();
	CreateSolidCaret(0, ptrDoc->GetCaretVerSize());
	SetCaretPos(ptrDoc->GetCaretPosition());
	ShowCaret();
}