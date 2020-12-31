// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CPPTooltip_demo.h"
#include "CPPTooltip_demoDoc.h"
#include "CPPTooltip_demoView.h"
#include "CustomizeTooltip.h"

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
	ON_COMMAND(ID_DEMO_DIALOG, OnDemoDialog)
	ON_UPDATE_COMMAND_UI(ID_DEMO_DIALOG, OnUpdateDemoDialog)
	ON_WM_MENUSELECT()
	ON_WM_ENTERIDLE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_LEFT_MENUTIP, OnLeftMenutip)
	ON_UPDATE_COMMAND_UI(ID_LEFT_MENUTIP, OnUpdateLeftMenutip)
	ON_COMMAND(ID_CENTER_MENUTIP, OnCenterMenutip)
	ON_UPDATE_COMMAND_UI(ID_CENTER_MENUTIP, OnUpdateCenterMenutip)
	ON_COMMAND(ID_BOTTOM_MENUTIP, OnBottomMenutip)
	ON_UPDATE_COMMAND_UI(ID_BOTTOM_MENUTIP, OnUpdateBottomMenutip)
	ON_COMMAND(ID_RIGHT_MENUTIP, OnRightMenutip)
	ON_UPDATE_COMMAND_UI(ID_RIGHT_MENUTIP, OnUpdateRightMenutip)
	ON_COMMAND(ID_TOP_MENUTIP, OnTopMenutip)
	ON_UPDATE_COMMAND_UI(ID_TOP_MENUTIP, OnUpdateTopMenutip)
	ON_COMMAND(ID_VCENTER_MENUTIP, OnVcenterMenutip)
	ON_UPDATE_COMMAND_UI(ID_VCENTER_MENUTIP, OnUpdateVcenterMenutip)
	ON_COMMAND(ID_ANCHOR_BOTTOMEDGE_CENTER, OnAnchorBottomedgeCenter)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_BOTTOMEDGE_CENTER, OnUpdateAnchorBottomedgeCenter)
	ON_COMMAND(ID_ANCHOR_BOTTOMEDGE_LEFT, OnAnchorBottomedgeLeft)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_BOTTOMEDGE_LEFT, OnUpdateAnchorBottomedgeLeft)
	ON_COMMAND(ID_ANCHOR_BOTTOMEDGE_RIGHT, OnAnchorBottomedgeRight)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_BOTTOMEDGE_RIGHT, OnUpdateAnchorBottomedgeRight)
	ON_COMMAND(ID_ANCHOR_LEFTEDGE_BOTTOM, OnAnchorLeftedgeBottom)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_LEFTEDGE_BOTTOM, OnUpdateAnchorLeftedgeBottom)
	ON_COMMAND(ID_ANCHOR_LEFTEDGE_TOP, OnAnchorLeftedgeTop)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_LEFTEDGE_TOP, OnUpdateAnchorLeftedgeTop)
	ON_COMMAND(ID_ANCHOR_LEFTEDGE_VCENTER, OnAnchorLeftedgeVcenter)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_LEFTEDGE_VCENTER, OnUpdateAnchorLeftedgeVcenter)
	ON_COMMAND(ID_ANCHOR_RIGHTEDGE_BOTTOM, OnAnchorRightedgeBottom)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_RIGHTEDGE_BOTTOM, OnUpdateAnchorRightedgeBottom)
	ON_COMMAND(ID_ANCHOR_RIGHTEDGE_TOP, OnAnchorRightedgeTop)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_RIGHTEDGE_TOP, OnUpdateAnchorRightedgeTop)
	ON_COMMAND(ID_ANCHOR_RIGHTEDGE_VCENTER, OnAnchorRightedgeVcenter)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_RIGHTEDGE_VCENTER, OnUpdateAnchorRightedgeVcenter)
	ON_COMMAND(ID_ANCHOR_TOPEDGE_CENTER, OnAnchorTopedgeCenter)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_TOPEDGE_CENTER, OnUpdateAnchorTopedgeCenter)
	ON_COMMAND(ID_ANCHOR_TOPEDGE_LEFT, OnAnchorTopedgeLeft)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_TOPEDGE_LEFT, OnUpdateAnchorTopedgeLeft)
	ON_COMMAND(ID_ANCHOR_TOPEDGE_RIGHT, OnAnchorTopedgeRight)
	ON_UPDATE_COMMAND_UI(ID_ANCHOR_TOPEDGE_RIGHT, OnUpdateAnchorTopedgeRight)
	ON_COMMAND(ID_TOOLTIP_BALLOON, OnTooltipBalloon)
	ON_UPDATE_COMMAND_UI(ID_TOOLTIP_BALLOON, OnUpdateTooltipBalloon)
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
	m_bBalloonTooltip = TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar2.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_tooltip.Create(this, m_bBalloonTooltip))
	{
		TRACE0("Failed to create tooltip\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBar2);

	m_tooltip.AddToolBar(&m_wndToolBar);
	m_tooltip.AddToolBar(&m_wndToolBar2);
//	CString str;
//	str.Format(_T("0x%08X è 0x%08X"), m_wndToolBar.GetSafeHwnd(), m_wndToolBar2.GetSafeHwnd());
//	SetTitle(str);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnDemoDialog() 
{
	CCustomizeTooltip pDialog;

	pDialog.DoModal();
}

void CMainFrame::OnUpdateDemoDialog(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

/////////////////////////////////////////////////////
//Next two handlers (OnMenuSelect and OnEnterIdle)needed for work tooltip in menu
void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSubMenu)
{
	m_tooltip.OnMenuSelect(nItemID, nFlags, hSubMenu);
	CFrameWnd::OnMenuSelect(nItemID, nFlags, hSubMenu);
}

void CMainFrame::OnEnterIdle(UINT nWhy, CWnd* pWho)
{
	m_tooltip.OnEnterIdle(nWhy, pWho);
}

void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MAINFRAME));
	CMenu* pSubMenu = menu.GetSubMenu(4);

	// Make sure cursor pos is within client area.
	// If user invoked via Shift-F10, it may not be!
	ScreenToClient(&point);
	CRect rc;
	GetClientRect(&rc);
	if (!rc.PtInRect(point)) 
	{
		point = CPoint(rc.Width()/2, rc.Height()/2);
	}
	ClientToScreen(&point);

	// display popup menu
	pSubMenu->TrackPopupMenu(0, point.x, point.y, this);
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
/*
	if (WM_MOUSEMOVE == pMsg->message)
	{
		CString str;
		char buf[16];
		HWND hWnd = ::WindowFromPoint(pMsg->pt);
		GetClassName(hWnd,buf,sizeof(buf));
		str.Format(_T("x = %d, y = %d, hWnd = 0x%08X, classname = %s, toolbar = %s"), pMsg->pt.x, pMsg->pt.y, hWnd, buf, TOOLBARCLASSNAME);
		m_wndStatusBar.SetPaneText(0, str);
	}
*/
	m_tooltip.RelayEvent(pMsg);
	
	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnLeftMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_HMASK;
	dwAlign |= PPTOOLTIP_MENU_LEFT;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateLeftMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_HMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_LEFT) ? 1 : 0);
}

void CMainFrame::OnCenterMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_HMASK;
	dwAlign |= PPTOOLTIP_MENU_CENTER;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateCenterMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_HMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_CENTER) ? 1 : 0);
}

void CMainFrame::OnBottomMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_VMASK;
	dwAlign |= PPTOOLTIP_MENU_BOTTOM;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateBottomMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_VMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_BOTTOM) ? 1 : 0);
}

void CMainFrame::OnRightMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_HMASK;
	dwAlign |= PPTOOLTIP_MENU_RIGHT;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateRightMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_HMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_RIGHT) ? 1 : 0);
}

void CMainFrame::OnTopMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_VMASK;
	dwAlign |= PPTOOLTIP_MENU_TOP;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateTopMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_VMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_TOP) ? 1 : 0);
}

void CMainFrame::OnVcenterMenutip() 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= ~PPTOOLTIP_MENU_VMASK;
	dwAlign |= PPTOOLTIP_MENU_VCENTER;
	m_tooltip.MenuToolPosition(dwAlign);
}

void CMainFrame::OnUpdateVcenterMenutip(CCmdUI* pCmdUI) 
{
	DWORD dwAlign = m_tooltip.GetMenuToolPosition();
	dwAlign &= PPTOOLTIP_MENU_VMASK;
	pCmdUI->SetCheck((dwAlign == PPTOOLTIP_MENU_VCENTER) ? 1 : 0);
}


void CMainFrame::OnAnchorBottomedgeCenter() 
{
	m_tooltip.SetDirection(PPTOOLTIP_BOTTOMEDGE_CENTER);
}

void CMainFrame::OnUpdateAnchorBottomedgeCenter(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_BOTTOMEDGE_CENTER) ? 1 : 0);
}

void CMainFrame::OnAnchorBottomedgeLeft() 
{
	m_tooltip.SetDirection(PPTOOLTIP_BOTTOMEDGE_LEFT);
}

void CMainFrame::OnUpdateAnchorBottomedgeLeft(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_BOTTOMEDGE_LEFT) ? 1 : 0);
}

void CMainFrame::OnAnchorBottomedgeRight() 
{
	m_tooltip.SetDirection(PPTOOLTIP_BOTTOMEDGE_RIGHT);
}

void CMainFrame::OnUpdateAnchorBottomedgeRight(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_BOTTOMEDGE_RIGHT) ? 1 : 0);
}

void CMainFrame::OnAnchorLeftedgeBottom() 
{
	m_tooltip.SetDirection(PPTOOLTIP_LEFTEDGE_BOTTOM);
}

void CMainFrame::OnUpdateAnchorLeftedgeBottom(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_LEFTEDGE_BOTTOM) ? 1 : 0);
}

void CMainFrame::OnAnchorLeftedgeTop() 
{
	m_tooltip.SetDirection(PPTOOLTIP_LEFTEDGE_TOP);
}

void CMainFrame::OnUpdateAnchorLeftedgeTop(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_LEFTEDGE_TOP) ? 1 : 0);
}

void CMainFrame::OnAnchorLeftedgeVcenter() 
{
	m_tooltip.SetDirection(PPTOOLTIP_LEFTEDGE_VCENTER);
}

void CMainFrame::OnUpdateAnchorLeftedgeVcenter(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_LEFTEDGE_VCENTER) ? 1 : 0);
}

void CMainFrame::OnAnchorRightedgeBottom() 
{
	m_tooltip.SetDirection(PPTOOLTIP_RIGHTEDGE_BOTTOM);
}

void CMainFrame::OnUpdateAnchorRightedgeBottom(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_RIGHTEDGE_BOTTOM) ? 1 : 0);
}

void CMainFrame::OnAnchorRightedgeTop() 
{
	m_tooltip.SetDirection(PPTOOLTIP_RIGHTEDGE_TOP);
}

void CMainFrame::OnUpdateAnchorRightedgeTop(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_RIGHTEDGE_TOP) ? 1 : 0);
}

void CMainFrame::OnAnchorRightedgeVcenter() 
{
	m_tooltip.SetDirection(PPTOOLTIP_RIGHTEDGE_VCENTER);
}

void CMainFrame::OnUpdateAnchorRightedgeVcenter(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_RIGHTEDGE_VCENTER) ? 1 : 0);
}

void CMainFrame::OnAnchorTopedgeCenter() 
{
	m_tooltip.SetDirection(PPTOOLTIP_TOPEDGE_CENTER);
}

void CMainFrame::OnUpdateAnchorTopedgeCenter(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_TOPEDGE_CENTER) ? 1 : 0);
}

void CMainFrame::OnAnchorTopedgeLeft() 
{
	m_tooltip.SetDirection(PPTOOLTIP_TOPEDGE_LEFT);
}

void CMainFrame::OnUpdateAnchorTopedgeLeft(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_TOPEDGE_LEFT) ? 1 : 0);
}

void CMainFrame::OnAnchorTopedgeRight() 
{
	m_tooltip.SetDirection(PPTOOLTIP_TOPEDGE_RIGHT);
}

void CMainFrame::OnUpdateAnchorTopedgeRight(CCmdUI* pCmdUI) 
{
	DWORD dwDirection = m_tooltip.GetDirection();
	pCmdUI->SetCheck((dwDirection == PPTOOLTIP_TOPEDGE_RIGHT) ? 1 : 0);
}

void CMainFrame::OnTooltipBalloon() 
{
	// TODO: Add your command handler code here
	m_bBalloonTooltip = m_bBalloonTooltip ? FALSE : TRUE;
	m_tooltip.SetDefaultSizes(m_bBalloonTooltip);
}

void CMainFrame::OnUpdateTooltipBalloon(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bBalloonTooltip ? 1 : 0);
}
