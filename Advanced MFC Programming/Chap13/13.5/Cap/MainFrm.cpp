#include "stdafx.h"
#include "Cap.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_NCACTIVATE()
	ON_WM_NCPAINT()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif

BOOL CMainFrame::OnNcActivate(BOOL bActive) 
{
	if(bActive == FALSE)
	{
		CFrameWnd::OnNcActivate(bActive);
		DrawCaption(RGB(0, 255, 255));
		return TRUE;
	}
	return CFrameWnd::OnNcActivate(bActive);
}

void CMainFrame::OnNcPaint() 
{
	CFrameWnd::OnNcPaint();
	DrawCaption(RGB(255, 255, 0));
}

void CMainFrame::DrawCaption(COLORREF color)
{
	CWindowDC dc(this);
	CRect rect;
	CRect rectDraw;
	int nBorderX;
	int nCapButtonX;
	int nFrameX;
	int nFrameY;
	int nBkMode;
	CString szCaption;

	nCapButtonX=::GetSystemMetrics(SM_CXSIZE);
	nBorderX=::GetSystemMetrics(SM_CXBORDER);
	nFrameX=::GetSystemMetrics(SM_CXFRAME);
	nFrameY=::GetSystemMetrics(SM_CYFRAME);
	szCaption.LoadString(AFX_IDS_APP_TITLE);
	szCaption=GetActiveDocument()->GetTitle()+" - "+szCaption;
	GetWindowRect(rect);
	rectDraw.left=nCapButtonX+nBorderX+nFrameX;
	rectDraw.top=nFrameY;
	rectDraw.right=rect.Width()-3*nCapButtonX-nFrameX-nBorderX;
	rectDraw.bottom=rectDraw.top+::GetSystemMetrics(SM_CYSIZE);
	dc.FillSolidRect(rectDraw, color);
	nBkMode=dc.SetBkMode(OPAQUE);
	dc.DrawText(szCaption, rectDraw, DT_CENTER);
	dc.SetBkMode(nBkMode);
}

LONG CMainFrame::OnSetText(WPARAM wParam, LPARAM lParam)
{
	SendMessage(WM_NCPAINT, 0, 0);
	return (LRESULT)TRUE;
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CFrameWnd::OnSysCommand(nID, lParam);
	if(::IsWindow(GetSafeHwnd()))SendMessage(WM_NCPAINT, 0, 0);
}
