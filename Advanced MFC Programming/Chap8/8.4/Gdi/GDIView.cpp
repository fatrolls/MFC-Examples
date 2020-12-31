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

void CGDIView::OnDraw(CDC* pDC)
{
	CPen pen;
	CPen *ptrPenOld;
	CBrush brush;
	CBrush *ptrBrushOld;
	CPoint pts[6];
	CRect rect;

	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	brush.CreateHatchBrush(HS_DIAGCROSS, RGB(255, 255, 0));
	ptrPenOld=pDC->SelectObject(&pen);
	ptrBrushOld=pDC->SelectObject(&brush);
	pDC->TextOut
	(
		0, 0, 
		"pDC->Chord(CRect(5, 5, 60, 70), CPoint(0, 80), CPoint(100, 0));"
	);
	pDC->Chord(CRect(5, 5, 60, 70), CPoint(0, 80), CPoint(100, 0));
	pDC->TextOut
	(
		0, 75, 
		"pDC->DrawFocusRect(CRect(5, 95, 60, 150));"
	);
	pDC->DrawFocusRect(CRect(5, 95, 60, 150));
	pDC->TextOut
	(
		0, 155, 
		"pDC->Pie(CRect(5, 165, 60, 200), CPoint(5, 165), CPoint(60, 165));"
	);
	pDC->Pie(CRect(5, 165, 60, 200), CPoint(5, 165), CPoint(60, 165));
	pts[0]=CPoint(5, 225);
	pts[1]=CPoint(100, 255);
	pts[2]=CPoint(50, 360);
	pts[3]=CPoint(5, 360);
	pts[4]=CPoint(50, 310);
	pts[5]=CPoint(50, 260);
	pDC->TextOut
	(
		0, 210, 
		"pDC->Polygon(pts, 6);"
	);
	pDC->Polygon(pts, 6);
	pDC->TextOut
	(
		0, 370, 
		"pDC->RoundRect(rect, CPoint(20, 10));"
	);
	rect=CRect(5, 385, 100, 435);
	pDC->RoundRect(rect, CPoint(20, 10));
	rect=CRect(5, 460, 100, 510);
	pDC->TextOut
	(
		0, 445, 
		"pDC->Draw3dRect(rect, RGB(127, 127, 127), RGB(63, 63, 63));"
	);
	pDC->Draw3dRect(rect, RGB(255, 0, 0), RGB(0, 255, 255));
	pDC->SelectObject(ptrPenOld);
	pDC->SelectObject(ptrBrushOld);
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
	CScrollView::OnInitialUpdate();
	SetScrollSizes(MM_TEXT, CSize(800, 800));	
}
