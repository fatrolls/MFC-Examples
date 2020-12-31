// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BackgroundPainter.h"

#include "MainFrm.h"
#include "TestDlg.h"
#include "LogoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TESTDIALOG, OnViewTestdialog)
	ON_COMMAND(ID_VIEW_LOGODLG, OnViewLogodlg)
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
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
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | 
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// set transparent style in order to make toolbar to delegate all rights
	// for drawing the background to COXBackgroundPainterOrganizer object
	// that will hook the toolbar later in the code of this function
	m_wndToolBar.ModifyStyle(NULL,TBSTYLE_TRANSPARENT);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbars with corresponding items in menu
	Organizer.AutoSetMenuImage();


	// hook toolbar after it was created and initialized
	m_backPainterOrganizer.Attach(&m_wndToolBar,IDB_WALLPAPER,Tile,
		CLR_DEFAULT,this);

	// hook the frame window in order to display tab control in client area
	VERIFY(m_MTIClientWnd.Attach(this));

	CWnd* pMDIClient=CWnd::FromHandle(m_hWndMDIClient);
	// hook MDIClient window
	m_backPainterOrganizer.Attach(pMDIClient,IDB_WALLPAPER,Tile,
		CLR_DEFAULT,this);

	// hook tab control in MTI interface
	m_backPainterOrganizer.Attach(m_MTIClientWnd.GetTabCtrl(),IDB_WALLPAPER,Tile,
		CLR_DEFAULT,this);

	return 0;
}

void CMainFrame::EnableDocking(DWORD dwDockStyle)
{
	COXMenuBarFrame<CMDIFrameWnd,CDockBar>::EnableDocking(dwDockStyle);

	if(GetControlBar(AFX_IDW_DOCKBAR_TOP)!=NULL &&
		!m_backPainterOrganizer.IsAttached(GetControlBar(AFX_IDW_DOCKBAR_TOP)))
	{
		m_backPainterOrganizer.Attach(GetControlBar(AFX_IDW_DOCKBAR_TOP),
			IDB_WALLPAPER,Tile,CLR_DEFAULT,this);
	}
	if(GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)!=NULL &&
		!m_backPainterOrganizer.IsAttached(GetControlBar(AFX_IDW_DOCKBAR_BOTTOM)))
	{
		m_backPainterOrganizer.Attach(GetControlBar(AFX_IDW_DOCKBAR_BOTTOM),
			IDB_WALLPAPER,Tile,CLR_DEFAULT,this);
	}
	if(GetControlBar(AFX_IDW_DOCKBAR_LEFT)!=NULL &&
		!m_backPainterOrganizer.IsAttached(GetControlBar(AFX_IDW_DOCKBAR_LEFT)))
	{
		m_backPainterOrganizer.Attach(GetControlBar(AFX_IDW_DOCKBAR_LEFT),
			IDB_WALLPAPER,Tile,CLR_DEFAULT,this);
	}
	if(GetControlBar(AFX_IDW_DOCKBAR_RIGHT)!=NULL &&
		!m_backPainterOrganizer.IsAttached(GetControlBar(AFX_IDW_DOCKBAR_RIGHT)))
	{
		m_backPainterOrganizer.Attach(GetControlBar(AFX_IDW_DOCKBAR_RIGHT),
			IDB_WALLPAPER,Tile,CLR_DEFAULT,this);
	}
}

BOOL CMainFrame::OnCreateMenuBar(HMENU hMenu, CFrameWnd* pFrameWnd, 
								 DWORD dwStyle, UINT nID)
{
	if(!COXMenuBarFrame<CMDIFrameWnd,CDockBar>::
		OnCreateMenuBar(hMenu,pFrameWnd,dwStyle,nID))
	{
		return FALSE;
	}

	m_backPainterOrganizer.Attach(&GetMenuBar(),IDB_WALLPAPER,Tile,
		CLR_DEFAULT,this);

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewTestdialog() 
{
	// TODO: Add your command handler code here
	
	CTestDlg dlgTest;
	dlgTest.DoModal();
}

void CMainFrame::OnViewLogodlg() 
{
	// TODO: Add your command handler code here
	
	CLogoDlg dlgLogo;
	dlgLogo.DoModal();
}

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
	CMDIFrameWnd::OnPaletteChanged(pFocusWnd);
	
	// TODO: Add your message handler code here
	SendMessageToDescendants(WM_PALETTECHANGED,(WPARAM)((HWND)*pFocusWnd),NULL);
}

BOOL CMainFrame::OnQueryNewPalette() 
{
	// TODO: Add your message handler code here and/or call default
	
	SendMessageToDescendants(WM_QUERYNEWPALETTE,NULL,NULL);
	return CMDIFrameWnd::OnQueryNewPalette();
}
