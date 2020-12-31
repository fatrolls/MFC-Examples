// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"

#include "MainFrm.h"

#include "OXCoolComboBox.h"


#ifndef OX_CUSTOMIZE_WORKSPACE_STATE
#include "OXWorkspaceState.h"
#endif	//	OX_CUSTOMIZE_WORKSPACE_STATE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COXCustomTBButtonTemplate* CCustomTBExtendedEdit::CBCreateNewInstance() const
{
	return dynamic_cast<COXCustomTBButtonTemplate*>(new CCustomTBExtendedEdit);
}

void CCustomTBExtendedEdit::
CBCopyContents(COXCustomTBButtonTemplate* pCBTemplate) const
{
	ASSERT(::IsWindow(GetSafeHwnd()));

	COXCustomTBButtonWnd<COXEdit>::CBCopyContents(pCBTemplate);
	
	COXEdit* pNewEdit=(COXEdit*)pCBTemplate->CBGetWindow();
	pNewEdit->SetBkColor(GetBkColor(),FALSE);
	pNewEdit->SetHighlightOnSetFocus(GetHighlightOnSetFocus());
	pNewEdit->SetInsertMode(GetInsertMode());
	pNewEdit->SetMask(GetMask());
	pNewEdit->SetTextColor(GetTextColor(),FALSE);
	pNewEdit->SetToolTipText(GetToolTipText());
	pNewEdit->SetInputData(GetInputData());
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMainFrameWindow)

BEGIN_MESSAGE_MAP(CMainFrame, CMainFrameWindow)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_WORKSPACE, OnBarCheck)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_OUTPUT, OnBarCheck)
	ON_COMMAND_RANGE(AFX_IDW_TOOLBAR,AFX_IDW_TOOLBAR+100,OnShowControlBars)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CB_EDIT, ID_CB_HOTKEY, OnUpdateCustomButton)
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
	COXMenuBarFrame<CMainFrameWindow,COXSizeDockBar>(CBRS_ALIGN_ANY,
		RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{
		// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)
public:
	CMyEdit() {};

protected:
	BOOL b;

protected:
	virtual void Control() {};
	DECLARE_MESSAGE_MAP()
};

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
END_MESSAGE_MAP()


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
#ifdef OX_CUSTOMIZE_INSTANCE_MANAGER
	if(m_customizeManager.CheckMaxAllowedInstances())
	{
		TRACE(_T("CMainFrame::OnCreate: the maximum allowed number of instances has been reached. The application won't be loaded\n"));
		return -1;
	}
#endif	//	OX_CUSTOMIZE_INSTANCE_MANAGER

#ifdef OX_CUSTOMIZE_SPLASHWINDOW
	VERIFY(m_customizeManager.InitializeSplashWindow(IDB_SPLASHWINDOW));
#endif	//	OX_CUSTOMIZE_INSTANCE_MANAGER

	if (CMainFrameWindow::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_bAutoMenuEnable=FALSE;

	if (!m_wndToolBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC,
		AFX_IDW_TOOLBAR) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.IniSizes(CSize(ID_OXCUSTOMIZE_TBIMAGE_WIDTH,
		ID_OXCUSTOMIZE_TBIMAGE_HEIGHT));
	m_wndToolBar.UpdateSizes();
	m_wndToolBar.SetWindowText(_T("Toolbar"));


	static CFont font;
	if((HFONT)font!=NULL)
		font.DeleteObject();
	font.CreatePointFont(-80,_T("MS Sans Serif"));

	// create custom buttons objects
	//
	static COXCustomTBSubclassedComboBox<CComboBox, CListBox, COXNumericEdit> m_combo;
	int nCBIndexCombo=
		COXCoolToolBar::AddCustomButton(&m_combo,ID_CB_COMBO,100,200,OXCBD_SHOWANY,0);
	ASSERT(nCBIndexCombo!=-1);

	static CCustomTBExtendedEdit m_edit;
	int nCBIndexEdit=
		COXCoolToolBar::AddCustomButton(&m_edit,ID_CB_EDIT,100,18,OXCBD_SHOWANY,0);
	ASSERT(nCBIndexEdit!=-1);

	static COXCustomTBButtonWnd<CSliderCtrl> m_slider;
	int nCBIndexSlider=
		m_wndToolBarWindow.AddCustomButton(&m_slider,ID_CB_SLIDER,90,21,OXCBD_SHOWANY,0);
	ASSERT(nCBIndexSlider!=-1);

#if _MFC_VER>0x0421
	///////////////////////////////////////////////////////////////////////////
	static COXCustomTBButtonWnd<CDateTimeCtrl> m_datetime;
	int nCBIndexDTP=
		m_wndToolBarWindow.AddCustomButton(&m_datetime,ID_CB_DTP,80,21,OXCBD_SHOWANY,0);
	ASSERT(nCBIndexDTP!=-1);


	///////////////////////////////////////////////////////////////////////////
#endif
	static COXCustomTBComboBox<CComboBox> m_comboEx;
	int nCBIndexComboEx=
		m_wndToolBarWindow.AddCustomButton(&m_comboEx,ID_CB_COMBOEX,120,200,OXCBD_SHOWANY,0);
	ASSERT(nCBIndexComboEx!=-1);

	VERIFY(m_wndToolBar.InsertComboBox(10,nCBIndexCombo));
	m_combo.SetFont(&font);
	m_combo.AddString(_T("32.34"));
	m_combo.AddString(_T("Only digits!"));
	m_combo.AddString(_T("10,200.356"));
	m_combo.AddString(_T("1.0"));

	VERIFY(m_wndToolBar.InsertEditBox(12,nCBIndexEdit,_T("EditBox")));
	m_edit.SetFont(&font);
	m_edit.SetTextColor(RGB(0,0,255));


	if (!m_wndToolBarWindow.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC,
		AFX_IDW_TOOLBAR+10) || !m_wndToolBarWindow.LoadToolBar(IDR_TB_WINDOW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBarWindow.IniSizes(CSize(ID_OXCUSTOMIZE_TBIMAGE_WIDTH,
		ID_OXCUSTOMIZE_TBIMAGE_HEIGHT));
	m_wndToolBarWindow.UpdateSizes();
	m_wndToolBarWindow.SetWindowText(_T("Window"));

	VERIFY(m_wndToolBarWindow.InsertSlider(1,nCBIndexSlider));

#if _MFC_VER>0x0421
	///////////////////////////////////////////////////////////////////////////
	VERIFY(m_wndToolBarWindow.InsertDateTimePicker(2,nCBIndexDTP,
		COleDateTime(1999,9,19,0,0,0)));
	///////////////////////////////////////////////////////////////////////////
#endif
	VERIFY(m_wndToolBarWindow.InsertComboBox(2,nCBIndexComboEx, WS_CHILD|WS_VISIBLE|CBS_DROPDOWNLIST));
	static CFont fontEx;
	if((HFONT)fontEx!=NULL)
		font.DeleteObject();
	fontEx.CreatePointFont(100,_T("Courier"));
	
	m_comboEx.SetFont(&fontEx);
	m_comboEx.AddString(_T("Release"));
	m_comboEx.AddString(_T("Debug"));
	m_comboEx.SetCurSel(0);
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_wndToolBarWindow.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBarWindow);

	// This is a TabView Bar that is added dynamically. You can have almost any 
	// number of these...
	if(!m_tabViewBar.Create(this))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create TabView Bar\n"));
		return -1;      
	} 
	m_tabViewBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_tabViewBar,AFX_IDW_DOCKBAR_BOTTOM);

	// This is a 3DTabView Bar that is added dynamically. You can have almost any 
	// number of these...
	if(!m_3DTabViewBar.Create(this))
	{
		TRACE(_T("CMainFrame::OnCreate: failed to create 3DTabView Bar\n"));
		return -1;      
	} 
	m_3DTabViewBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_3DTabViewBar,AFX_IDW_DOCKBAR_LEFT);

#ifdef OX_CUSTOMIZE_COMMANDS
	COXBitmapMenuOrganizer* pBMOrganizer=m_customizeManager.GetBMOrganizer();
	ASSERT(pBMOrganizer!=NULL);
	pBMOrganizer->ExcludeFromRecentlyUsed(ID_FILE_PRINT_SETUP);
	pBMOrganizer->ExcludeFromRecentlyUsed(ID_FILE_OPEN);
	pBMOrganizer->ExcludeFromRecentlyUsed(AFX_ID_PREVIEW_ZOOMOUT);
	pBMOrganizer->ExcludeFromRecentlyUsed(AFX_ID_PREVIEW_NEXT);
#endif	//	OX_CUSTOMIZE_COMMANDS

#ifdef OX_CUSTOMIZE_INSTANCE_MANAGER
	VERIFY(m_customizeManager.InitializeInstanceManager());
#endif	//	OX_CUSTOMIZE_INSTANCE_MANAGER
#ifdef OX_CUSTOMIZE_TOOLBARS
	VERIFY(m_customizeManager.InitializeToolbars());
#endif	//	OX_CUSTOMIZE_TOOLBARS
#ifdef OX_CUSTOMIZE_COMMANDS
	VERIFY(m_customizeManager.InitializeCommands());
#endif	//	OX_CUSTOMIZE_COMMANDS
#ifdef OX_CUSTOMIZE_COOLCONTROLS
	VERIFY(m_customizeManager.InitializeCoolControls());
#endif	//	OX_CUSTOMIZE_COOLCONTROLS
#ifdef OX_CUSTOMIZE_TRAYICON
	VERIFY(m_customizeManager.InitializeTrayIcon(IDR_MAINFRAME,
		IDR_MAINFRAME,_T("Tooltip")));
#endif	//	OX_CUSTOMIZE_TRAYICON

#ifdef OX_CUSTOMIZE_INTELLIMOUSE
	VERIFY(m_customizeManager.InitializeIntelliMouse());
#endif // OX_CUSTOMIZE_INTELLIMOUSE

#ifdef OX_CUSTOMIZE_COOLCONTROLS
	m_customizeManager.InitializeCoolControls();
#endif // OX_CUSTOMIZE_COOLCONTROLS
	 
#ifndef _MDI_INTERFACE
	LoadWorkspace();
#endif

	m_tabViewBar.RedrawWindow();
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMainFrameWindow::PreCreateWindow(cs) )
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
	CMainFrameWindow::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameWindow::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::SaveWorkspace() 
{
	m_tabViewBar.m_TabViewContainer.SaveState(_T("OutputWindow"));
	m_customizeManager.SaveWorkspaceState();
#ifndef OX_CUSTOMIZE_WORKSPACE_STATE
	SaveSizeBarState(_T("SizeBarState"));
	// common procedure to save workspace
	COXWorkspaceState workspaceState;
	workspaceState.IncludeBarProperty(FALSE);
	if(!workspaceState.StoreToRegistry())
	{
		TRACE(_T("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n)"));
	}
#endif	//	OX_CUSTOMIZE_WORKSPACE_STATE
}

void CMainFrame::LoadWorkspace() 
{
#ifdef OX_CUSTOMIZE_SHORTKEYS
	VERIFY(m_customizeManager.InitializeShortkeys(this));
#endif	//	OX_CUSTOMIZE_SHORTKEYS
#ifdef OX_CUSTOMIZE_TABBEDMDI
	VERIFY(m_customizeManager.InitializeTabbedMDI());
#endif	//	OX_CUSTOMIZE_TABBEDMDI
#ifdef OX_CUSTOMIZE_INTELLIMOUSE
	VERIFY(m_customizeManager.
		InitializeIntelliMouse(TRUE,WM_LBUTTONDOWN,KEYPRESSED_SHIFT));
#endif	//	OX_CUSTOMIZE_INTELLIMOUSE
#ifdef OX_CUSTOMIZE_CAPTION
	VERIFY(m_customizeManager.InitializeCaptionPainter());
#endif	//	OX_CUSTOMIZE_CAPTION
#ifdef OX_CUSTOMIZE_BACKGROUND
	VERIFY(m_customizeManager.InitializeBackgroundPainter(TRUE,TRUE,IDB_BACKGROUND));
#endif	//	OX_CUSTOMIZE_BACKGROUND

#ifdef OX_CUSTOMIZE_WORKSPACE_STATE
	m_customizeManager.LoadWorkspaceState();
#else
	LoadSizeBarState(_T("SizeBarState"));
	// common procedure to load workspace
	COXWorkspaceState workspaceState;
	workspaceState.IncludeBarProperty(FALSE);
	if(!workspaceState.LoadFromRegistry())
	{
		TRACE(_T("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n)"));
	}
#endif	//	OX_CUSTOMIZE_WORKSPACE_STATE
	
	m_tabViewBar.m_TabViewContainer.LoadState(_T("OutputWindow"));

	m_wndToolBar.UpdateCustomButtons();
	m_wndToolBarWindow.UpdateCustomButtons();

#ifdef OX_CUSTOMIZE_SPLASHWINDOW
	m_customizeManager.GetSplashWindow()->Hide();
#endif	//	OX_CUSTOMIZE_SPLASHWINDOW
}


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	SaveWorkspace();

	CMainFrameWindow::OnClose();
}

void CMainFrame::OnViewCustomize() 
{
	// TODO: Add your command handler code here

//	m_customizeManager.DoModal();
	if(!::IsWindow(m_customizeManager.GetSafeHwnd()))
	{
		VERIFY(m_customizeManager.Create(COXCustomizeManager::IDD,this));
	}
	m_customizeManager.ActivatePage(CAPTION_PAINTER);
	m_customizeManager.SetActiveWindow();
	m_customizeManager.ShowWindow(SW_SHOW);
}



void CMainFrame::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	UNREFERENCED_PARAMETER(pWnd);

	CArray<CToolBar*,CToolBar*> arrToolbars;
	POSITION pos=m_listControlBars.GetHeadPosition();
	while(pos!=NULL)
	{
		CToolBar* pToolbar=DYNAMIC_DOWNCAST(CToolBar, 
			(CControlBar*)m_listControlBars.GetNext(pos));
		//If it is a CToolBar
		if(pToolbar!=NULL && !pToolbar->IsKindOf(RUNTIME_CLASS(COXMenuBar)))
		{
			arrToolbars.Add(pToolbar);
		}
	}

	int nToolbarCount=PtrToInt(arrToolbars.GetSize());
	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	for(int nIndex=0; nIndex<nToolbarCount; nIndex++)
	{
		CToolBar* pToolbar=arrToolbars[nIndex];
		CString sText;
		pToolbar->GetWindowText(sText);
		menu.AppendMenu(MF_STRING|(pToolbar->IsWindowVisible() ? 
			MF_CHECKED : MF_UNCHECKED),pToolbar->GetDlgCtrlID(),sText);
	}
	if(nToolbarCount>0)
		menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING,ID_VIEW_CUSTOMIZE,_T("Customize..."));

	menu.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON,
		point.x,point.y,this);
}


void CMainFrame::OnShowControlBars(UINT nID)
{
	POSITION pos=m_listControlBars.GetHeadPosition();
	while(pos!=NULL)
	{
		CControlBar* pControlBar=(CControlBar*)m_listControlBars.GetNext(pos);
		//If it is a pControlBar
		if(pControlBar!=NULL && pControlBar->GetDlgCtrlID()==(int)nID &&
			!pControlBar->IsKindOf(RUNTIME_CLASS(COXMenuBar)))
		{
			ShowControlBar(pControlBar,!pControlBar->IsWindowVisible(),FALSE);
			break;
		}
	}
}

void CMainFrame::OnUpdateCustomButton(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
}


