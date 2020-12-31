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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_bNeedErase=FALSE;
	m_bCapture=FALSE;
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
	CPen pen;
	CPen *ptrPenOld;
	CBrush brush;
	CBrush *ptrBrushOld;
	CBitmap bmp;
	int nMode;
	int nNumOfRects;
	int i;
	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	bmp.LoadBitmap(IDB_BITMAP_BRUSH);
	pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	ptrPenOld=pDC->SelectObject(&pen);
	brush.CreatePatternBrush(&bmp);
	ptrBrushOld=pDC->SelectObject(&brush);
	nMode=pDC->SetROP2(R2_COPYPEN);
	nNumOfRects=pDoc->GetNumOfRects();
	for(i=0; i<nNumOfRects; i++)
	{
		pDC->Rectangle(pDoc->GetRect(i));
	}
	pDC->SetROP2(nMode);
	pDC->SelectObject(ptrBrushOld);
	pDC->SelectObject(ptrPenOld);
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

void CGDIView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_rectDraw.left=point.x;
	m_rectDraw.top=point.y;
	SetCapture();
	m_bCapture=TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CGDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	CBrush brush;
	CBrush *ptrBrushOld;
	int nMode;
	CGDIDoc *ptrDoc;

	ptrDoc=(CGDIDoc *)GetDocument();
	pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
	ptrPenOld=dc.SelectObject(&pen);
	brush.Attach(::GetStockObject(HOLLOW_BRUSH));
	ptrBrushOld=dc.SelectObject(&brush);
	nMode=dc.SetROP2(R2_XORPEN);
	dc.Rectangle(m_rectDraw);
	dc.SetROP2(nMode);
	dc.SelectObject(ptrBrushOld);
	dc.SelectObject(ptrPenOld);
	pen.DeleteObject();
	brush.Detach();

	m_bNeedErase=FALSE;
	m_rectDraw.right=point.x;
	m_rectDraw.bottom=point.y;
	ptrDoc->AddRect(m_rectDraw);
	if(m_bCapture == TRUE)
	{
		::ReleaseCapture();
		m_bCapture=FALSE;
	}
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void CGDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	CBrush brush;
	CBrush *ptrBrushOld;
	int nMode;

	if(nFlags & MK_LBUTTON)
	{
		pen.CreatePen(PS_DASH, 1, RGB(0, 0, 0));
		ptrPenOld=dc.SelectObject(&pen);
		brush.Attach(::GetStockObject(HOLLOW_BRUSH));
		ptrBrushOld=dc.SelectObject(&brush);
		nMode=dc.SetROP2(R2_XORPEN);
		if(m_bNeedErase == TRUE)
		{
			dc.Rectangle(m_rectDraw);
		}
		else m_bNeedErase=TRUE;
		m_rectDraw.right=point.x;
		m_rectDraw.bottom=point.y;
		dc.Rectangle(m_rectDraw);
		dc.SetROP2(nMode);
		dc.SelectObject(ptrBrushOld);
		brush.Detach();
		dc.SelectObject(ptrPenOld);
	}
	
	CView::OnMouseMove(nFlags, point);
}
