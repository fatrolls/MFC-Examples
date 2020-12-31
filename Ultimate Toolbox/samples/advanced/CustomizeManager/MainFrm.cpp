// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "CustomizeManager.h"

#include "MainFrm.h"

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
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_WM_CLOSE()
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

CMainFrame::CMainFrame() : COXMenuBarFrame<CMDIFrameWnd,COXSizeDockBar>(CBRS_ALIGN_ANY,
	RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
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

	// STEP 6f: Commands Page - You must use Create(...) instead of CreateEx(...),
	// otherwise the toolbar buttons will not be customizable.
	if (!m_wndToolBar.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		AFX_IDW_TOOLBAR) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	InitToolBar();

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
	
	// Comment out the next line if you don't want the snapping and tear-off behavior.
	EnableSnapping();

	// STEP 3: Before initializing the different pages of the Customize Manager you have
	// to set CWinApp::m_pMainWnd to point to your main frame.
	AfxGetApp()->m_pMainWnd = this;

	// STEP 4b: Tabbed MDI Page - Call InitializeTabbedMDI() in the WM_CREATE handler
	// of your main frame window. This call but be prior to calling InitializeBackgroundPainter(...).
	m_CM.InitializeTabbedMDI();

	// STEP 5b: Toolbars Page - Call InitializeToolbars() in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeToolbars();

	// STEP 6b: Commands Page - Call InitializeCommands() in the WM_CREATE handler of
	// your main frame window. Make sure that this function is called AFTER InitializeToolbars().
	m_CM.InitializeCommands();

	// STEP 6c: Recent Menus - If you want some menu items to be colapsed call
	// ExcludeFromRecentlyUsed(...) and pass the ID of the menu item.
	m_CM.GetBMOrganizer()->ExcludeFromRecentlyUsed(ID_FILE_OPEN);
	m_CM.GetBMOrganizer()->ExcludeFromRecentlyUsed(ID_FILE_PRINT_PREVIEW);
	m_CM.GetBMOrganizer()->ExcludeFromRecentlyUsed(ID_FILE_PRINT_SETUP);

	// STEP 7b: Cool Controls Page - Call InitializeCoolControls() in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeCoolControls();

	// STEP 8b: Instance Manager Page - Call InitializeInstanceManager() in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeInstanceManager();

	// STEP 9b: IntelliMouse Support Page - Call InitializeIntelliMouse() in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeIntelliMouse(TRUE, WM_LBUTTONDOWN, KEYPRESSED_SHIFT);

	// STEP 10b: Shortkeys Page - Call InitializeShortkeys(...) in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeShortkeys(this);

	// STEP 11b: Splash Window Page - Call InitializeSplashWindow(...) in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeSplashWindow(IDB_SPLASH, TRUE, 2000);

	// STEP 12b: Background Painter Page - Call InitializeBackgroundPainter(...) in the
	// WM_CREATE handler of your main frame window. This must be called after InitializeTabbedMDI().
	m_CM.InitializeBackgroundPainter(TRUE, TRUE, IDB_BACKGROUND);

	// STEP 13b: Tray Icon Page - Call InitializeTrayIcon(...) in the WM_CREATE handler
	// of your main frame window.
	m_CM.InitializeTrayIcon(IDR_MAINFRAME, IDR_MAINFRAME, _T("Tooltip"));

	return 0;
}

void CMainFrame::OnClose() 
{
	// STEP 14c: Workspace State Page - Call SaveWorkspaceState() in the WM_CLOSE handler
	// of your main frame window.	
//	m_CM.SaveWorkspaceState();

	CMDIFrameWnd::OnClose();
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

// STEP 2: Add a command and a handler for it which will display the Customize Manager window.
void CMainFrame::OnViewCustomize() 
{
	// If the Customize Manager window has not been created yet - create it.
	if (!::IsWindow(m_CM.GetSafeHwnd()))
	{
		VERIFY(m_CM.Create(COXCustomizeManager::IDD, this));
	}

	// Set the page you want to display first and show the window.
	m_CM.ActivatePage(BACKGROUND_PAINTER);
	m_CM.SetActiveWindow();
	m_CM.ShowWindow(SW_SHOW);	
}

void CMainFrame::InitToolBar()
{
	m_wndToolBar.SetWindowText(_T("Toolbar"));

	static CFont font;
	if(font.m_hObject == NULL)
		font.CreatePointFont(-80, _T("MS Sans Serif"));

	// Add the skinned combo box
	int iCombo = COXCoolToolBar::AddCustomButton(&m_Combo, ID_CB_COMBO, 100, 100);
	m_wndToolBar.InsertComboBox(m_wndToolBar.GetToolBarCtrl().GetButtonCount(), iCombo);
	m_Combo.SetFont(&font);

	m_Combo.AddString(_T("One"));
	m_Combo.SetItemData(0, 500);
	m_Combo.AddString(_T("Two"));
	m_Combo.SetItemData(1, 1000);
	m_Combo.AddString(_T("Three"));
	m_Combo.SetItemData(2, 1500);
	m_Combo.AddString(_T("Four"));
	m_Combo.SetItemData(3, 2000);
	m_Combo.AddString(_T("Five"));
	m_Combo.SetItemData(4, 2500);
}

// We override WindowProc since we want to get CBN_SELCHANGE along with
// the handle of the window that generated it.
LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// NOTE: Since the Customize Manager could have been used to place the combo box
	// in more than one place, there is no garantee that m_Combo is where this notification
	// originated. So we must get the pointer using the combo box handle.
	if (message == WM_COMMAND && HIWORD(wParam) == CBN_SELCHANGE)
	{
		COXCustomTBComboBox<COXSkinnedComboBox>* pCombo =
			(COXCustomTBComboBox<COXSkinnedComboBox>*) CWnd::FromHandlePermanent((HWND) lParam);
		
		if (pCombo)
		{
		// Beep with the appropriate frequency when the selection changes
		int iFrequency = (int) pCombo->GetItemData(pCombo->GetCurSel());
		Beep(iFrequency, 100);
	}
	}
	
	return COXMenuBarFrame<CMDIFrameWnd, COXSizeDockBar>::WindowProc(message, wParam, lParam);
}

