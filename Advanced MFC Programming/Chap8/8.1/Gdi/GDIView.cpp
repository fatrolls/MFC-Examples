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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_bCapture=TRUE;
	m_bNeedErase=FALSE;
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
	int nMode;
	int nNumOfLines;
	int i;
	CRect *ptrRect;
	CGDIDoc *pDoc=GetDocument();

	ASSERT_VALID(pDoc);

	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	ptrPenOld=pDC->SelectObject(&pen);
	nMode=pDC->SetROP2(R2_COPYPEN);
	nNumOfLines=pDoc->GetNumOfLines();
	for(i=0; i<nNumOfLines; i++)
	{
		ptrRect=pDoc->GetLine(i);
		pDC->MoveTo(ptrRect->TopLeft());
		pDC->LineTo(ptrRect->BottomRight());
	}
	pDC->SetROP2(nMode);
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
	m_ptStart=point;
	SetCapture();
	m_bCapture=TRUE;
	CView::OnLButtonDown(nFlags, point);
}

void CGDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	
	if(nFlags & MK_LBUTTON)
	{
		pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
		ptrPenOld=dc.SelectObject(&pen);
		nMode=dc.SetROP2(R2_XORPEN);
		if(m_bNeedErase == TRUE)
		{
			dc.MoveTo(m_ptStart);
			dc.LineTo(m_ptEnd);
		}
		else
		{
			m_bNeedErase=TRUE;
		}
		m_ptEnd=point;
		dc.MoveTo(m_ptStart);
		dc.LineTo(m_ptEnd);
		dc.SetROP2(nMode);
		dc.SelectObject(ptrPenOld);
	}
	CView::OnMouseMove(nFlags, point);
}

void CGDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	CGDIDoc *ptrDoc;

	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	ptrPenOld=dc.SelectObject(&pen);
	nMode=dc.SetROP2(R2_XORPEN);
	dc.MoveTo(m_ptStart);
	dc.LineTo(m_ptEnd);
	dc.SetROP2(nMode);
	dc.SelectObject(ptrPenOld);
	pen.DeleteObject();

	ptrDoc=(CGDIDoc *)GetDocument();
	m_ptEnd=point;
	ptrDoc->AddLine(CRect(m_ptStart.x, m_ptStart.y, m_ptEnd.x, m_ptEnd.y));
	m_bNeedErase=FALSE;
	Invalidate();
	if(m_bCapture == TRUE)
	{
		::ReleaseCapture();
		m_bCapture=FALSE;
	}
	CView::OnLButtonUp(nFlags, point);
}
