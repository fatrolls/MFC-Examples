//*******************************************************************************************************/
//* FileName:		demoView.cpp
//*
//* Contents:		demo implementation of clPlot.
//*
//* Note:			Most of the stuff in this file is standard MFC implementation stuff not related to 
//*					the plot.
//*
//*					The implementation of the plot in the demo are done as following:
//*
//*					1.	OnInitialUpdate creates the plot and initialize it. It also activates a timer.
//*
//*					2.	OnTimer	adds data points to the plot every second.
//*
//*					3.	OnSize re-sizes the plot to fit the entire view as needed.
//*
//*					4.	OnEraseBkgnd is overrided to do nothing. This is needed for flicker free drawing.
//*
//* Author:			Jan Vidar Berger
//*******************************************************************************************************/

#include "stdafx.h"
#include "Demo.h"

#include "DemoDoc.h"
#include "DemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoView

IMPLEMENT_DYNCREATE(CDemoView, CView)

BEGIN_MESSAGE_MAP(CDemoView, CView)
	//{{AFX_MSG_MAP(CDemoView)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoView construction/destruction

CDemoView::CDemoView()
{
	// TODO: add construction code here
canSize=FALSE;
}

CDemoView::~CDemoView()
{
}

BOOL CDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView drawing

void CDemoView::OnDraw(CDC* pDC)
{
	CDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView printing

BOOL CDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDemoView diagnostics

#ifdef _DEBUG
void CDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDemoDoc* CDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDemoDoc)));
	return (CDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDemoView message handlers

void CDemoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	CRect Rect;
	GetClientRect(Rect);
	m_Plot.Create(WS_CHILD|WS_VISIBLE,Rect,this,12000);

	m_Plot.SetSerie(0, PS_SOLID, RGB(255,0,0), 0.0, 2000.0, "Pressure");
	m_Plot.SetSerie(1, PS_DOT, RGB(0,255,0), 0.0, 2000.0, "Pressure");
	m_Plot.SetSerie(2, PS_DASH, RGB(0,0,255), 0.0, 2000.0, "Pressure");
	m_Plot.SetSerie(3, PS_SOLID, RGB(255,255,0), 0.0, 2000.0, "Pressure");

	m_Plot.SetLegend(0, PS_SOLID, RGB(255,0,0), "Temperature");
	m_Plot.SetLegend(1, PS_DOT, RGB(0,255,0), "Pressure");
	m_Plot.SetLegend(2, PS_DASH, RGB(0,0,255), "Pressure");
	m_Plot.SetLegend(3, PS_SOLID, RGB(255,255,0), "Pressure");

	m_Plot.m_bAutoScrollX=TRUE;

	SetTimer(1,1000,NULL);
	canSize=TRUE;
}

void CDemoView::OnTimer(UINT nIDEvent) 
{
	static BOOL pros={FALSE};
	if(!pros){
		pros=TRUE;
		{
		double y =(double)(abs(rand())%2000);
		m_Plot.AddPoint(0,  CTime::GetCurrentTime(), y);
		}
		{
		double y =(double)(abs(rand())%2000);
		m_Plot.AddPoint(1,  CTime::GetCurrentTime(), y);
		}
		{
		double y =(double)(abs(rand())%2000);
		m_Plot.AddPoint(2,  CTime::GetCurrentTime(), y);
		}
		{
		//double y =(double)(abs(rand())%2000);
			double y=500.0;
		m_Plot.AddPoint(3,  CTime::GetCurrentTime(), y);
		}
		Invalidate();
		pros=FALSE;
	}
	CView::OnTimer(nIDEvent);
}

void CDemoView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if(canSize){
		CRect Rect;
		GetClientRect(Rect);
		m_Plot.MoveWindow(Rect);
	}
}

BOOL CDemoView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return FALSE;
}
