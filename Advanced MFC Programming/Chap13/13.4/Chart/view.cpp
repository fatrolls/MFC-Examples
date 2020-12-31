#include "stdafx.h"
#include "Chart.h"
#include <math.h>
#include "ChartDoc.h"
#include "View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define pi		3.1415926535

IMPLEMENT_DYNCREATE(CChartView, CView)

BEGIN_MESSAGE_MAP(CChartView, CView)
	//{{AFX_MSG_MAP(CChartView)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

CChartView::CChartView()
{
}

CChartView::~CChartView()
{
}

BOOL CChartView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

void CChartView::OnDraw(CDC* pDC)
{
	int nA, nB, nC;
	CBrush brush;
	CBrush *pBrOld;
	CRect rect;
	CRect rectSub;

	CChartDoc *pDoc=GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->GetABC(nA, nB, nC);

	GetClientRect(rect);
	rect.left=rect.Width()/4;
	rect.right-=rect.left;
	rect.top=rect.Height()/4;
	rect.bottom-=rect.top;
	pDC->MoveTo(rect.TopLeft());
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.BottomRight());

	brush.CreateSolidBrush(RGB(255, 0, 0));
	pBrOld=pDC->SelectObject(&brush);
	rectSub=rect;
	rectSub.top=rect.Height()-nA*rect.Height()/100+rect.top;
	rectSub.right=rect.Width()/3+rect.left;
	pDC->Rectangle(rectSub);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();

	brush.CreateSolidBrush(RGB(0, 255, 0));
	pBrOld=pDC->SelectObject(&brush);
	rectSub=rect;
	rectSub.top=rect.Height()-nB*rect.Height()/100+rect.top;
	rectSub.right=rect.Width()/3+rect.left;
	rectSub.OffsetRect(rectSub.Width(), 0);
	pDC->Rectangle(rectSub);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();

	brush.CreateSolidBrush(RGB(255, 255, 0));
	pBrOld=pDC->SelectObject(&brush);
	rectSub=rect;
	rectSub.top=rect.Height()-nC*rect.Height()/100+rect.top;
	rectSub.right=rect.Width()/3+rect.left;
	rectSub.OffsetRect(rectSub.Width()*2, 0);
	pDC->Rectangle(rectSub);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();
}

BOOL CChartView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CChartView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CChartView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

#ifdef _DEBUG
void CChartView::AssertValid() const
{
	CView::AssertValid();
}

void CChartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChartDoc* CChartView::GetDocument()
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChartDoc)));
	return (CChartDoc*)m_pDocument;
}
#endif

IMPLEMENT_DYNCREATE(CPieView, CView)

CPieView::CPieView()
{
}

CPieView::~CPieView()
{
}


BEGIN_MESSAGE_MAP(CPieView, CView)
	//{{AFX_MSG_MAP(CPieView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPieView::OnDraw(CDC* pDC)
{
	int nA, nB, nC;
	CPoint ptStart;
	CPoint ptEnd;
	CBrush brush;
	CBrush *pBrOld;
	CRect rect;
	long r=100;

	CChartDoc *pDoc=(CChartDoc *)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->GetABC(nA, nB, nC);

	pDC->SetMapMode(MM_ISOTROPIC);
	GetClientRect(rect);
	
	pDC->SetWindowExt(100, 100);
	pDC->SetViewportExt
	(
		pDC->GetDeviceCaps(LOGPIXELSX),
		-pDC->GetDeviceCaps(LOGPIXELSY)
	);
	pDC->SetViewportOrg(rect.right/2, rect.bottom/2);
	rect=CRect(-100, 100, 100, -100);

	ptStart.x=rect.right;
	ptStart.y=0;
	ptEnd.x=(long)(r*cos(nA*2*pi/100));
	ptEnd.y=(long)(r*sin(nA*2*pi/100));
	brush.CreateSolidBrush(RGB(255, 0, 0));
	pBrOld=pDC->SelectObject(&brush);
	pDC->Pie(rect, ptStart, ptEnd);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();

	ptStart=ptEnd;
	ptEnd.x=(long)(r*cos((nA+nB)*2*pi/100));
	ptEnd.y=(long)(r*sin((nA+nB)*2*pi/100));
	brush.CreateSolidBrush(RGB(0, 255, 0));
	pBrOld=pDC->SelectObject(&brush);
	pDC->Pie(rect, ptStart, ptEnd);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();

	ptStart=ptEnd;
	ptEnd.x=(long)(r*cos((nA+nB+nC)*2*pi/100));
	ptEnd.y=(long)(r*sin((nA+nB+nC)*2*pi/100));
	brush.CreateSolidBrush(RGB(255, 255, 0));
	pBrOld=pDC->SelectObject(&brush);
	pDC->Pie(rect, ptStart, ptEnd);
	pDC->SelectObject(pBrOld);
	brush.DeleteObject();
}

CPoint CPieView::GetPoint(CRect rect, int nAngle)
{
	CPoint pt;

	if(nAngle == 0)
	{
		pt.x=rect.right;
		pt.y=(LONG)((rect.top+rect.bottom)/2);
	}
	if(nAngle >0 && nAngle < 45)
	{
		pt.x=rect.right;
		pt.y=(LONG)((rect.top+rect.bottom)/2-rect.Width()/2*tan(2*pi*nAngle/360));
	}
	if(nAngle == 45)pt=CPoint(rect.right, rect.top);
	if(nAngle > 45 && nAngle < 90)
	{
		pt.y=rect.top;
		pt.x=(LONG)((rect.left+rect.right)/2+rect.Height()/2/tan(2*pi*nAngle/360));
	}
	if(nAngle == 90)
	{
		pt.x=(rect.left+rect.right)/2;
		pt.y=rect.top;
	}
	if(nAngle > 90 && nAngle < 135)
	{
		pt.y=rect.top;
		pt.x=(LONG)((rect.left+rect.right)/2+rect.Height()/2/tan(2*pi*nAngle/360));
	}
	if(nAngle == 135)pt=CPoint(rect.left, rect.top);
	if(nAngle > 135 && nAngle < 180)
	{
		pt.x=rect.left;
		pt.y=(LONG)((rect.top+rect.bottom)/2+rect.Width()/2*tan(2*pi*nAngle/360));
	}
	if(nAngle == 180)
	{
		pt.x=rect.left;
		pt.y=(rect.top+rect.bottom)/2;
	}
	if(nAngle > 180 && nAngle < 225)
	{
		pt.x=rect.left;
		pt.y=(LONG)((rect.top+rect.bottom)/2+rect.Width()/2*tan(2*pi*nAngle/360));
	}
	if(nAngle == 225)pt=CPoint(rect.left, rect.bottom);
	if(nAngle > 225 && nAngle < 270)
	{
		pt.y=rect.bottom;
		pt.x=(LONG)((rect.left+rect.right)/2-rect.Height()/2/tan(2*pi*nAngle/360));
	}
	if(nAngle == 270)
	{
		pt.x=(rect.left+rect.right)/2;
		pt.y=rect.bottom;
	}
	if(nAngle > 270 && nAngle < 315)
	{
		pt.y=rect.bottom;
		pt.x=(LONG)((rect.left+rect.right)/2-rect.Height()/2/tan(2*pi*nAngle/360));
	}
	if(nAngle == 315)pt=CPoint(rect.right, rect.bottom);
	if(nAngle > 315 && nAngle <= 360)
	{
		pt.x=rect.right;
		pt.y=(LONG)((rect.top+rect.bottom)/2-rect.Width()/2*tan(2*pi*nAngle/360));
	}
	return pt;
}

#ifdef _DEBUG
void CPieView::AssertValid() const
{
	CView::AssertValid();
}

void CPieView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
