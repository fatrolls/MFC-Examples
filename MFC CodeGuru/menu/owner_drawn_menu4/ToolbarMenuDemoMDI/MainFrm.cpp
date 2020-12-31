// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CSpawnMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CSpawnMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
// COOLMENU SUPPORT
	cSpawn.LoadToolBarResource(IDR_MAINFRAME);
	cSpawn.AddToolBarResource(IDR_SYSTEMBAR);

// Someone asked for different font support; now you can specify a LOGFONT
// for the font you want in the menus. If you uncomment the lines below, a BIG
// tahoma will be used (be sure to have Tahoma in your system, or change facename!)

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lstrcpy(lf.lfFaceName, "Tahoma");
	lf.lfHeight = 14;
//	lf.lfWeight = 700;

//	cSpawn.SetFont(&lf);

//	cSpawn.SetTextColor(RGB(0,0,255), RGB(255,0,0));

//	cSpawn.SetBackBitmap(IDB_BACK4, RGB(255,255,255));

// END COOLMENU SUPPORT
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CSpawnMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CSpawnMDIFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CSpawnMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CSpawnMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

// COOLMENU WITH STINGRAY SOFTWARE OBJECTIVE TOOLKIT PRO SUPPORT

//	If you wish to use the coolmenu along with Stingray Software Objective Toolkit 
//	and their SECMenuBar, thus obtaining a very look and feel with Office97 menu "buttons" 
//	style, you will to need to uncomment the lines below; this to avoid general protection
//	errors or similar. If you are using different base class from SECWorkbook, change it 
//	to yours base class

LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
//	if (message != WM_MEASUREITEM) return SECWorkbook::WindowProc(message, wParam, lParam);
//	else return CMDIFrameWnd::WindowProc( message, wParam, lParam );	
	
	return CMDIFrameWnd::WindowProc(message, wParam, lParam);
}
// END COOLMENU WITH STINGRAY SOFTWARE OBJECTIVE TOOLKIT PRO SUPPORT

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return CSpawnMDIFrameWnd::OnCreateClient(lpcs, pContext);
/*	{
		CMenu * pMenu = GetMenu();
		ASSERT(pMenu);
		cSpawn.RemapMenu(pMenu);
		SetMenu(pMenu);
		VERIFY(::DrawMenuBar(GetSafeHwnd()));
		return TRUE;
	}
	return FALSE;	*/
}
