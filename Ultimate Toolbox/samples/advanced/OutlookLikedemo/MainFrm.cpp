// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Outlook.h"

#include "MainFrm.h"

#include "OutlookView.h"
#include "OutlookFormView.h"
#include "OutlookTreeView.h"
#include "OutlookListView.h"

#include "OXSzMiniDockFrmWnd.h"
#include "OXBitmapMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_NOTIFY(TBN_DROPDOWN, ID_VIEW_TOOLBAR, OnDropDown)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
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

CMainFrame::CMainFrame() :
	COXMenuBarFrame<CFrameWnd,COXSizeDockBar>(CBRS_ALIGN_ANY,
		RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER,
		CRect(2, 2, 2, 2), ID_VIEW_TOOLBAR) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.IniSizes(CSize(16,16));
	m_wndToolBar.SetWindowText(_T("Toolbar"));
	m_wndToolBar.SetDropDownArrow(TRUE);
	
	m_wndToolBar.SetButtonStyle(0, m_wndToolBar.GetButtonStyle(0) | TBSTYLE_DROPDOWN);
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

	{
		// Create the combo box
		//m_wndToolBar.SetButtonInfo(18, IDC_COMBO, TBBS_SEPARATOR, 200);
		m_iCombo = COXCoolToolBar::AddCustomButton(&m_Combo, IDC_COMBO, 100, 100);
		m_wndToolBar.InsertComboBox(18,m_iCombo);

		// add some stuff
		m_Combo.AddString(_T("Messages"));
		m_Combo.AddString(_T("Messages with AutoPreview"));
		m_Combo.AddString(_T("By Message Flag"));
		m_Combo.AddString(_T("Last Seven Days"));
		m_Combo.AddString(_T("Flagged For Next Seven Days"));
		m_Combo.AddString(_T("By Conversation Topic"));
		m_Combo.AddString(_T("By Sender"));
		m_Combo.AddString(_T("Unread Messages"));
		m_Combo.AddString(_T("Sent To"));
		m_Combo.AddString(_T("Message Timeline"));

		m_wndToolBar.m_font.CreatePointFont(85, _T("Arial"));
		m_Combo.SetFont(&m_wndToolBar.m_font);
	}

	m_wndToolBar.UpdateSizes();
	
	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	m_menuOrganizer.AttachFrameWnd(this);
	m_menuOrganizer.AutoSetMenuImage();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~FWS_ADDTOTITLE;

	return CFrameWnd::PreCreateWindow(cs);
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

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	UNREFERENCED_PARAMETER(lpcs);

	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(COutlookView), CSize(0, 0), pContext))
		return FALSE;

	if (!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 1, 2, WS_CHILD | WS_VISIBLE, m_wndSplitter1.IdFromRowCol(0, 1)))
		return FALSE;

	if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(COutlookTreeView), CSize(0, 0), pContext))
		return FALSE;

	if (!m_wndSplitter2.CreateView(0, 1, RUNTIME_CLASS(COutlookListView), CSize(0, 0), pContext))
		return FALSE;

	m_wndSplitter1.SetColumnInfo(0, 150, 0);
	m_wndSplitter2.SetColumnInfo(0, 150, 0);

	return TRUE;
}

void CMainFrame::OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*) pNotifyStruct;
	CRect rect;

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBar.GetItemRect(m_wndToolBar.CommandToIndex(pNMToolBar->iItem), &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());

	if (pNMToolBar->iItem == ID_NEW_MESSAGE)
	{
		CMenu menu;
		CMenu* pPopup;

		menu.LoadMenu(IDR_POPUP_MENU);
		pPopup = menu.GetSubMenu(0);
		COXBitmapMenu menuPopup;
		menuPopup.Attach(pPopup->Detach());
		menuPopup.TrackPopupMenu(&m_wndToolBar, AfxGetMainWnd());
	}
	*pResult = TBDDRET_DEFAULT; 
}
