#include "stdafx.h"
#include "StatusBar.h"

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
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_OVR, OnUpdateIndicatorOvr)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // Statusleistenanzeige
	ID_INDICATOR_COUNT,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_OVR,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()	{}
CMainFrame::~CMainFrame()	{}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // Fehler beim Erzeugen
	}

	//************************************************************************
	//************************************************************************
	//************************************************************************

	if (!m_wndStatusBar.CreateStatusBar(this, indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // Fehler beim Erzeugen
	}

	// COUNT, CAPS, NUM, OVR, SCROLL
	m_wndStatusBar.SetMode(1, XSB_TEXT | DT_CENTER);
	m_wndStatusBar.SetMode(2, XSB_TEXT | DT_CENTER);		// Fest (Caps)
	m_wndStatusBar.SetMode(3, XSB_TEXT | DT_CENTER);		// Num
	m_wndStatusBar.SetMode(4, XSB_BITMAP | XSB_REPEAT);
	m_wndStatusBar.SetMode(5, XSB_BITMAP | XSB_STRETCH);

	m_wndStatusBar.SetNumber(1, 0, 0);
	m_wndStatusBar.SetFgColor(2, RGB(  0,   0,   0), RGB(255, 255, 255));
	m_wndStatusBar.SetBkColor(2, RGB(  0, 255, 255), RGB(128,   0,   0));
	m_wndStatusBar.SetFont(3, "Arial", 80);
	m_wndStatusBar.SetBitmap(4, "SCBM1", "SCBM2");
	m_wndStatusBar.SetBitmap(5, "BM1", "BM2");

	//************************************************************************
	//************************************************************************
	//************************************************************************

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)	{ return CFrameWnd::PreCreateWindow(cs); }

#ifdef _DEBUG
void CMainFrame::AssertValid() const				{ CFrameWnd::AssertValid(); }
void CMainFrame::Dump(CDumpContext& dc) const		{ CFrameWnd::Dump(dc); }
#endif //_DEBUG

void CMainFrame::OnUpdateIndicatorOvr(CCmdUI* pCmdUI)
{
	m_wndStatusBar.SetPaneStyle(4, (::GetKeyState(VK_INSERT) & 1) ? 0 : SBPS_DISABLED);
}

void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	switch (m_wndStatusBar.GetPaneAtPosition(point))
	{
	case 0:	m_wndStatusBar.SavePane(0);
			m_wndStatusBar.SetMode(0, XSB_PROGRESS);
			m_wndStatusBar.SetRange(0, 0, 100);
			SetTimer(0, 10, NULL);
			break;
	case 1:	m_wndStatusBar.Increment(1, true);
			m_wndStatusBar.Increment(1, false);
			break;
	case 2:	if (m_wndStatusBar.GetMode(2) & XSB_HSCROLL)
				m_wndStatusBar.SetMode(2, m_wndStatusBar.GetMode(2) & ~XSB_HSCROLL);
			else
				m_wndStatusBar.SetMode(2, m_wndStatusBar.GetMode(2) |  XSB_HSCROLL);
			break;
	case 3:	if (m_wndStatusBar.GetFontSize(3) == 18)
				m_wndStatusBar.SetFontSize(3, 12);
			else
				m_wndStatusBar.SetFontSize(3, 18);
			break;
	case 4:	if (m_wndStatusBar.GetMode(4) & XSB_HSCROLL)
				m_wndStatusBar.SetMode(4, m_wndStatusBar.GetMode(4) & ~XSB_HSCROLL);
			else
				m_wndStatusBar.SetMode(4, m_wndStatusBar.GetMode(4) |  XSB_HSCROLL);
			break;
	case 5:	m_wndStatusBar.SavePane(5);
			m_wndStatusBar.SetMode(5, XSB_NUMBER | XSB_CENTER);
			m_wndStatusBar.SetFgColor(5, RGB(0, 0, 0), RGB(0, 0, 0));
			m_wndStatusBar.SetNumber(5, 0, 0);
			SetTimer(5, 10, NULL);
			break;
	}

	CFrameWnd::OnLButtonDblClk(nFlags, point);
}

void CMainFrame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	switch (m_wndStatusBar.GetPaneAtPosition(point))
	{
	case 0:	if (m_wndStatusBar.GetMode(0) & XSB_BITMAP)
			{
				m_wndStatusBar.SetMode(0, XSB_TEXT);
				m_wndStatusBar.SetText(0, "", "");
			}
			else
			{
				m_wndStatusBar.SetBitmap(0, "JR", "JR");
				m_wndStatusBar.SetMode(0, XSB_BITMAP | XSB_REPEAT);
			}
			break;
	case 1:	m_wndStatusBar.Decrement(1, true);
			m_wndStatusBar.Decrement(1, false);
			break;
	case 2:	if (m_wndStatusBar.GetMode(2) & XSB_VSCROLL)
				m_wndStatusBar.SetMode(2, m_wndStatusBar.GetMode(2) & ~XSB_VSCROLL);
			else
				m_wndStatusBar.SetMode(2, m_wndStatusBar.GetMode(2) |  XSB_VSCROLL);
			break;
	case 3:	if (m_wndStatusBar.GetFontName(3) == "Arial")
				m_wndStatusBar.SetFontName(3, "Courier New");
			else
				m_wndStatusBar.SetFontName(3, "Arial");
			break;
	case 4:	if (m_wndStatusBar.GetMode(4) & XSB_VSCROLL)
				m_wndStatusBar.SetMode(4, m_wndStatusBar.GetMode(4) & ~XSB_VSCROLL);
			else
				m_wndStatusBar.SetMode(4, m_wndStatusBar.GetMode(4) |  XSB_VSCROLL);
			break;
	case 5:	m_wndStatusBar.SavePane(5);
			m_wndStatusBar.SetMode(5, XSB_PROGRESS | XSB_SMOOTH);
			m_wndStatusBar.SetRange(5, 0, 100);
			SetTimer(9, 10, NULL);
			break;
	}

	CFrameWnd::OnRButtonDblClk(nFlags, point);
}

void CMainFrame::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
	case 0:	{	if (m_wndStatusBar.OffsetPos(0, 1) >= 100)
				{
					KillTimer(0);
					m_wndStatusBar.RestorePane(0);
				}
			} break;
	case 5:	{	m_wndStatusBar.Increment(5, true);
				if (m_wndStatusBar.Increment(5, false) >= 100)
				{
					KillTimer(5);
					m_wndStatusBar.RestorePane(5);
				}
			} break;
	case 9:	{	if (m_wndStatusBar.OffsetPos(5, 1) >= 100)
				{
					KillTimer(9);
					m_wndStatusBar.RestorePane(5);
				}
			} break;
	}
}
