#include "stdafx.h"
#include "GDI.h"
#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	//{{AFX_MSG_MAP(CGDIView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CGDIView::OnDraw(CDC* pDC)
{
	CFont *ptrFt;
	CFont *ptrFtOld;
	CRect rect;
	LOGFONT logFont;

	CGDIDoc* pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	ptrFt=pDoc->GetCurrentFont();
	ASSERT(ptrFt != NULL);
	if(ptrFt->GetSafeHandle() != NULL)
	{
		ptrFt->GetLogFont(&logFont);
		ptrFtOld=pDC->SelectObject(ptrFt);
		pDC->SetTextColor(pDoc->GetFontColor());
		pDC->SetBkMode(pDoc->GetBgdStyle() ? TRANSPARENT:OPAQUE);
		pDC->SetBkColor((~pDoc->GetFontColor())&0x00FFFFFF);
	}
	GetClientRect(rect);
	pDC->TextOut(rect.Width()/4, rect.Height()/4, logFont.lfFaceName);
	if(ptrFt->GetSafeHandle() != NULL)pDC->SelectObject(ptrFtOld);
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
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif
