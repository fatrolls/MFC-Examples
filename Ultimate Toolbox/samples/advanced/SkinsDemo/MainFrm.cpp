// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "SkinsDemo.h"

#include "MainFrm.h"
#include "OXWorkspaceState.h"
#include "OXChildFrameState.h"

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
	ON_COMMAND(ID_CHECKED, OnChecked)
	ON_UPDATE_COMMAND_UI(ID_CHECKED, OnUpdateChecked)
	ON_COMMAND(ID_MAIL, OnMail)
	ON_COMMAND(ID_FILE_POPUP_ITEM1, OnFilePopupItem1)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_FOLDERS, OnViewFolders)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FOLDERS, OnUpdateViewFolders)
	ON_COMMAND(ID_VIEW_PROPERTIES, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTIES, OnUpdateViewProperties)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_BUTTON32773, ID_BUTTON32781, OnToolbar2)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON32773, ID_BUTTON32781, OnUpdateToolbar2)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropDown)
	ON_CBN_SELCHANGE(ID_CB_COMBO, OnSelChangeCombo)
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

// STEP 3 - Call the constructor of COXMenuBarFrame<CMDIFrameWnd, COXSizeDockBar> and
//		pass CBRS_ALIGN_ANY for the first parameter and
//		RUNTIME_CLASS(COXSizableMiniDockFrameWnd) for the second parameter
CMainFrame::CMainFrame() : 
	COXMenuBarFrame<CMDIFrameWnd,COXSizeDockBar>(CBRS_ALIGN_ANY,
	RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{
	// TODO: add member initialization code here
	m_bChecked = FALSE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create and initialize the main toolbar
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), AFX_IDW_TOOLBAR) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))

	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	InitToolBar();	

	// Create and initialize the second toolbar
	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, CRect(1, 1, 1, 1), 3344554) ||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBAR2))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	InitToolBar2();

	// Create the status bar
	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// Create the workspace bar
	if (!m_WorkspaceBar.Create(this, _T("Workspace"), IDR_WORKSPACEBAR,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_SIZE_DYNAMIC, CRect(0, 0, 150, 200)))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create the workspace bar.\n"));
		return -1;      
	}

	// Create the folders bar
	if (!m_FoldersBar.Create(this, _T("Folders"), IDR_FOLDERSBAR,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_SIZE_DYNAMIC,CRect(0, 0, 150, 200)))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create the folders bar.\n"));
		return -1;      
	}

	// Create the properties bar
	if (!m_PropertiesBar.Create(this, _T("Properties"), IDR_PROPERTIESBAR,
		WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_SIZE_DYNAMIC, CRect(0, 0, 220, 200)))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create the properties bar.\n"));
		return -1;      
	}

	// Enable docking and dock all control bars
	m_WorkspaceBar.EnableDocking(CBRS_ALIGN_ANY);
	m_FoldersBar.EnableDocking(CBRS_ALIGN_ANY);
	m_PropertiesBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBar2);
	DockControlBar(&m_WorkspaceBar, AFX_IDW_DOCKBAR_LEFT);
	DockControlBar(&m_FoldersBar, AFX_IDW_DOCKBAR_RIGHT);
	DockControlBar(&m_PropertiesBar, AFX_IDW_DOCKBAR_RIGHT);

	// Add the following 2 lines to tab all the windows docked to the right dock bar
	// and have the properties bar as the selected tab.
	COXSizeDockBar* pRightDockBar = (COXSizeDockBar*) m_PropertiesBar.m_pDockBar;
	pRightDockBar->TabAllDockedControlBars(&m_PropertiesBar);

	// STEP 5 (Cont'd) - Call COXBitmapMenuOrganizer::AttachFrameWnd(...) and then
	//					 COXBitmapMenuOrganizer::AttachFrameWnd(...)
	m_BMO.AttachFrameWnd(this);
	m_BMO.AutoSetMenuImage();

	// STEP 6 (Cont'd) - Call COXTabClientWnd::Attach(...)
	m_MTIClientWnd.Attach(this);

	// Enable the snapping and tear-off befavior for toolbars,
	// menu bars and docking windows
	EnableSnapping();

	// Uncomment the following lines if you don't want the user to be able to move
	// the menubar and the toolbars
	GetMenuBar().EnableFloating(FALSE);
	// m_wndToolBar.EnableFloating(FALSE);
	// m_wndToolBar2.EnableFloating(FALSE);

	return 0;
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


void CMainFrame::OnChecked() 
{
	m_bChecked = !m_bChecked;
}


void CMainFrame::OnUpdateChecked(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bChecked);	
}


void CMainFrame::OnToolbar2(UINT /*nID*/)
{

}

void CMainFrame::OnUpdateToolbar2(CCmdUI* /*pCmdUI*/)
{

}

void CMainFrame::OnMail() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	// This function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	// Translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBar.GetItemRect(
		m_wndToolBar.CommandToIndex(pNMToolBar->iItem),&rect);
	rect.top=rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom,&rect.TopLeft());

	COXBitmapMenu menuPopup;
	VERIFY(menuPopup.CreatePopupMenu());

	switch(pNMToolBar->iItem)
	{
	case ID_MAIL:
		{
			menuPopup.AppendMenu(MF_STRING,ID_MAIL,_T("Read Mail"));
			menuPopup.AppendMenu(MF_STRING,ID_MAIL,_T("New Message..."));
			menuPopup.AppendMenu(MF_STRING,ID_MAIL,_T("Send a Link..."));
			menuPopup.AppendMenu(MF_STRING,ID_MAIL,_T("Send Page..."));
			menuPopup.AppendMenu(MF_SEPARATOR);
			menuPopup.AppendMenu(MF_STRING,ID_MAIL,_T("Read News"));
			break;
		}

	}

	menuPopup.TrackPopupMenu(&m_wndToolBar, AfxGetMainWnd());

	*pResult = TBDDRET_DEFAULT; 
}
void CMainFrame::OnFilePopupItem1() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::InitToolBar()
{
	m_wndToolBar.SetList(); // the text will appear to the right of the icon (Outlook style)

	// Make all the buttons as wide as their text needs to be
	for (int i = 0; i < m_wndToolBar.GetToolBarCtrl().GetButtonCount(); i++)
	{
		if (!(m_wndToolBar.GetButtonStyle(i) & TBSTYLE_SEP))
			m_wndToolBar.SetButtonStyle(i, m_wndToolBar.GetButtonStyle(i) | TBSTYLE_AUTOSIZE);
	}

	m_wndToolBar.SetButtonTextFromID();//COXCoolToolBar::TTID_PLAIN);
	m_wndToolBar.SetButtonsMinMaxWidth(0, 180);
	m_wndToolBar.UpdateSizes();

	// Set the drop down style
	m_wndToolBar.SetDropDownArrow(TRUE);
	int iIndex = m_wndToolBar.CommandToIndex(ID_MAIL);
	m_wndToolBar.SetButtonStyle(iIndex,
		m_wndToolBar.GetButtonStyle(iIndex) | TBSTYLE_DROPDOWN | TBBS_CHECKBOX);

	// Insert a separator
	TBBUTTON tbb;
	::memset(&tbb, 0, sizeof(tbb));
	tbb.fsStyle = TBSTYLE_SEP;
	CToolBarCtrl& ctrl = m_wndToolBar.GetToolBarCtrl();
	ctrl.InsertButton(ctrl.GetButtonCount(), &tbb);

	// Create the custom buttons objects
	//
	static CFont font;
	if(font.m_hObject == NULL)
		font.CreatePointFont(-80,_T("MS Sans Serif"));

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

	// Add the skinned edit control
	int iEdit = COXCoolToolBar::AddCustomButton(&m_Edit, ID_CB_EDIT, 100, 18);
	m_wndToolBar.InsertEditBox(m_wndToolBar.GetToolBarCtrl().GetButtonCount(), iEdit);
	m_Edit.SetFont(&font);

	m_wndToolBar.UpdateSizes();

	m_wndToolBar.SetFlat(TRUE);
	m_wndToolBar.SetGripper(TRUE);
	m_wndToolBar.SetWindowText(_T("Standard"));
}

void CMainFrame::InitToolBar2()
{
	// Set the normal image list
	m_ilToolBar2Normal.Create(24, 22, ILC_COLOR8 | ILC_MASK, 9, 0);
	CBitmap bmpImage;
	bmpImage.LoadBitmap(IDB_TOOLBAR2_NORMAL);
	m_ilToolBar2Normal.Add(&bmpImage, RGB(255, 0, 0));
	bmpImage.DeleteObject();
	m_wndToolBar2.GetToolBarCtrl().SetImageList(&m_ilToolBar2Normal);

	// Set the hot image list
	m_ilToolBar2Hot.Create(24, 22, ILC_COLOR8 | ILC_MASK, 9, 0);
	bmpImage.LoadBitmap(IDB_TOOLBAR2_HOT);
	m_ilToolBar2Hot.Add(&bmpImage, RGB(0, 0, 255));
	bmpImage.DeleteObject();
	m_wndToolBar2.GetToolBarCtrl().SetHotImageList(&m_ilToolBar2Hot);

	// Set the disabled image list
	m_ilToolBar2Disabled.Create(24, 22, ILC_COLOR8 | ILC_MASK, 9, 0);
	bmpImage.LoadBitmap(IDB_TOOLBAR2_DISABLED);
	m_ilToolBar2Disabled.Add(&bmpImage, RGB(255, 0, 0));
	bmpImage.DeleteObject();
	m_wndToolBar2.GetToolBarCtrl().SetDisabledImageList(&m_ilToolBar2Disabled);

	// Set the toolbar caption
	m_wndToolBar2.SetWindowText(_T("Navigation"));
}

void CMainFrame::OnSelChangeCombo() 
{
	// Beep when the combo box selection changes
	int iFrequency = (int) m_Combo.GetItemData(m_Combo.GetCurSel());
	Beep(iFrequency, 100);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default

	CMDIFrameWnd::OnClose();
}


BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CMDIFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnViewFolders() 
{
	// Toggle the folders window
	m_FoldersBar.ShowBar(!m_FoldersBar.IsShown());
}

void CMainFrame::OnUpdateViewFolders(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_FoldersBar.IsShown());
}

void CMainFrame::OnViewProperties() 
{
	// Toggle the properties window
	m_PropertiesBar.ShowBar(!m_PropertiesBar.IsShown());	
}

void CMainFrame::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_PropertiesBar.IsShown());	
}

void CMainFrame::OnViewWorkspace() 
{
	// Toggle the workspace window
	m_WorkspaceBar.ShowBar(!m_WorkspaceBar.IsShown());
}

void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_WorkspaceBar.IsShown());
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (COXBitmapMenu::HandleMDICommandMessage(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	
	return CMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


