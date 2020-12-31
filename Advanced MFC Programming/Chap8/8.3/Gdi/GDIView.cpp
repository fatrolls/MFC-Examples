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
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CGDIView::CGDIView()
{
	m_nCurrentPt=0;
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
	int nNumOfPts;
	int nMode;
	int i;
	CPen pen;
	CPen *ptrPenOld;
	CPoint pt[4];

	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	ptrPenOld=pDC->SelectObject(&pen);
	nMode=pDC->SetROP2(R2_COPYPEN);
	nNumOfPts=pDoc->GetNumOfPts();
	for(i=0; i<nNumOfPts/4; i++)
	{
		pt[0]=pDoc->GetOnePt(4*i);
		pt[1]=pDoc->GetOnePt(4*i+1);
		pt[2]=pDoc->GetOnePt(4*i+2);
		pt[3]=pDoc->GetOnePt(4*i+3);
		pDC->PolyBezier(pt, 4);
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

void CGDIView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	CGDIDoc *ptrDoc;
	int i;

	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	ptrPenOld=dc.SelectObject(&pen);
	nMode=dc.SetROP2(R2_XORPEN);
	if(m_nCurrentPt == 3)
	{
		m_ptCurve[3]=point;
		ptrDoc=(CGDIDoc *)GetDocument();
		VERIFY(ptrDoc != NULL);
		for(i=0; i<4; i++)ptrDoc->AddPoint(m_ptCurve[i]);
		m_nCurrentPt=0;
		m_bNeedErase=FALSE;
		if(m_bCapture == TRUE)::ReleaseCapture();
		Invalidate();
	}
	else
	{
		if(m_nCurrentPt != 0)
		{
			dc.PolyBezier(m_ptCurve, 4);
			m_ptCurve[m_nCurrentPt]=point;
			for(i=m_nCurrentPt+1; i<4; i++)
			{
				m_ptCurve[i]=m_ptCurve[m_nCurrentPt];
			}
			dc.PolyBezier(m_ptCurve, 4);
			m_nCurrentPt++;
		}
		else 
		{
			m_ptCurve[m_nCurrentPt++]=point;
			SetCapture();
			m_bCapture=TRUE;
		}
	}
	dc.SetROP2(nMode);
	dc.SelectObject(ptrPenOld);

	CView::OnLButtonUp(nFlags, point);
}

void CGDIView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	CPen pen;
	CPen *ptrPenOld;
	int nMode;
	int i;

	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	ptrPenOld=dc.SelectObject(&pen);
	nMode=dc.SetROP2(R2_XORPEN);
	if(m_bNeedErase == TRUE)
	{
		dc.PolyBezier(m_ptCurve, 4);
		m_ptCurve[m_nCurrentPt]=point;
		for(i=m_nCurrentPt+1; i<4; i++)
		{
			m_ptCurve[i]=m_ptCurve[m_nCurrentPt];
		}
		dc.PolyBezier(m_ptCurve, 4);
	}
	else
	{
		m_ptCurve[m_nCurrentPt]=point;
		for(i=m_nCurrentPt+1; i<4; i++)
		{
			m_ptCurve[i]=m_ptCurve[m_nCurrentPt];
		}
		m_bNeedErase=TRUE;
	}
	dc.SetROP2(nMode);
	dc.SelectObject(ptrPenOld);
	CView::OnMouseMove(nFlags, point);
}
