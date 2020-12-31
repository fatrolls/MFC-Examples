// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MyWord.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
    ON_COMMAND_EX (IDW_STYLE_BAR, OnBarCheck)
    ON_UPDATE_COMMAND_UI (IDW_STYLE_BAR, OnUpdateControlBarMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

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
	
	//
	// Tell the frame window to permit docking.
	//
    EnableDocking (CBRS_ALIGN_ANY);

	//
	// Create the toolbar, style bar, and status bar.
	//
    if (!CreateToolBar () ||
        !CreateStyleBar () ||
        !CreateStatusBar ())
        return -1;

	//
	// Load the saved bar state (if any).
	//
	LoadBarState (_T ("MainBarState"));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
{
	SaveBarState (_T ("MainBarState"));
	CFrameWnd::OnClose();
}

BOOL CMainFrame::CreateToolBar()
{
    if (!m_wndToolBar.Create (this) ||
        !m_wndToolBar.LoadToolBar (IDR_MAINFRAME))
        return FALSE;

    m_wndToolBar.SetBarStyle (m_wndToolBar.GetBarStyle () |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

    m_wndToolBar.SetWindowText (_T ("Main"));
    m_wndToolBar.EnableDocking (CBRS_ALIGN_ANY);
    DockControlBar (&m_wndToolBar);
    return TRUE;
}

BOOL CMainFrame::CreateStyleBar()
{
    if (!m_wndStyleBar.Create (this, WS_CHILD | WS_VISIBLE | CBRS_TOP |
        CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDW_STYLE_BAR))
        return FALSE;

    m_wndStyleBar.SetWindowText (_T ("Styles"));
    m_wndStyleBar.EnableDocking (CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
    DockControlBar (&m_wndStyleBar);
    return TRUE;
}

BOOL CMainFrame::CreateStatusBar()
{
    static UINT nIndicators[] = {
        ID_SEPARATOR,
        ID_INDICATOR_LINE,
        ID_INDICATOR_CAPS,
        ID_INDICATOR_NUM
    };

    if (!m_wndStatusBar.Create (this))
        return FALSE;

    m_wndStatusBar.SetIndicators (nIndicators, 4);
    return TRUE;
}
