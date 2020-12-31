// mainfrm.cpp : implementation of the CMainFrame class
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "docktest.h"
#include "mainfrm.h"

#include "OXWorkspaceState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, MainFrameParent)

BEGIN_MESSAGE_MAP(CMainFrame, MainFrameParent)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_TILEDOCKBARS, OnViewTiledockbars)
	ON_COMMAND(ID_ArrangeBottomLeft, OnArrangeBottomLeft)
	ON_COMMAND(ID_ArrangeBottomRight, OnArrangeBottomRight)
	ON_COMMAND(ID_ArrangeTopLeft, OnArrangeTopLeft)
	ON_COMMAND(ID_ArrangeTopRight, OnArrangeTopRight)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP

	// standard on/off control bar handlers for View menu. 
	ON_UPDATE_COMMAND_UI(ID_SIZEDLGBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_SIZEDLGBAR, OnBarCheck)
	
	ON_UPDATE_COMMAND_UI(ID_FIXEDDLGBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_FIXEDDLGBAR, OnBarCheck)
	
	ON_UPDATE_COMMAND_UI(ID_LISTBOXBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_LISTBOXBAR, OnBarCheck)
	
	ON_UPDATE_COMMAND_UI(ID_TABVIEWBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_TABVIEWBAR, OnBarCheck)

	ON_UPDATE_COMMAND_UI(ID_LOGOBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_LOGOBAR, OnBarCheck)

	//************************************************************************************
	// This command handler is a example how to make your controls NOT TO BE DISABLED when
	// on a CDialogbar or COXSizeDlgBar
	ON_COMMAND(IDC_OXBUTTON, OnHandleButton)
	//
	//************************************************************************************

END_MESSAGE_MAP()

// This command handler is a example how to make your controls NOT TO BE DISABLED when
// on a CDialogbar or COXSizeDlgBar
void CMainFrame::OnHandleButton()
{
}

/////////////////////////////////////////////////////////////////////////////
// arrays of IDs used to initialize control bars
	
// toolbar buttons - IDs are command buttons
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE allbuttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction


CMainFrame::CMainFrame() : 
	COXMenuBarFrame<MainFrameParent,COXSizeDockBar>(CBRS_ALIGN_ANY,
		RUNTIME_CLASS(COXSizableMiniDockFrameWnd))
{
	m_BarCount = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
		{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	EnableDocking(CBRS_ALIGN_ANY);

	// This is a sizeable dialog bar.. that includes gadget resizing
	m_SizeDlgBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS | 
		SZBARF_DLGAUTOSIZE | SZBARF_ALLOW_MDI_FLOAT);
	if (!m_SizeDlgBar.Create(this, IDD_DIALOGBAR2, CBRS_RIGHT, ID_FIXEDDLGBAR))   
		{
		TRACE0("Failed to create dialog bar\n");
		return -1;      
		} 
	m_SizeDlgBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_SizeDlgBar);

	// This is a sizeable dialog bar...
	if (!m_DlgBar.Create(this, IDD_DIALOGBAR, CBRS_RIGHT, ID_SIZEDLGBAR))   
		{
		TRACE0("Failed to create dialog bar\n");
		return -1;      
		}	 
	m_DlgBar.EnableDocking(CBRS_ALIGN_ANY);
	
	// Following code will dock our sizeable control bar on the same row as
	// the sizeable control that hasn't gadget resizing - a lot of people have asked how to do this.
	CRect rcDlg1, rcDlg2;
	m_SizeDlgBar.GetWindowRect(&rcDlg1);
	m_DlgBar.GetWindowRect(&rcDlg2);
	rcDlg2.BottomRight() = rcDlg2.TopLeft() + rcDlg1.Size();
	rcDlg2.bottom -= 40;

	DockControlBar(&m_DlgBar, AFX_IDW_DOCKBAR_RIGHT, &rcDlg2);

	// This is a list box that is added dynamically. You can have almost any number of these...
	if (!m_SizeListBar.Create(this))
		{
		TRACE0("Failed to create list box bar\n");
		return -1;      
		} 
			
	m_SizeListBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_SizeListBar, AFX_IDW_DOCKBAR_BOTTOM);

	// This is a sizeable logo bar.. that includes gadget resizing
	// This is a TabView Bar that is added dynamically. You can have almost any 
	// number of these...
	if (!m_TabViewBar.Create(this))
		{
		TRACE0("Failed to create TabView Bar\n");
		return -1;      
		} 
			
	m_TabViewBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_TabViewBar, AFX_IDW_DOCKBAR_BOTTOM);

	RecalcLayout();

	TileDockedBars(CBRS_ALIGN_RIGHT);		// this makes the bars the same size

	m_bAutoMenuEnable=TRUE;
	
	VERIFY(m_MTIClientWnd.Attach(this));

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

void CMainFrame::OnViewTiledockbars() 
{
  	TileDockedBars();
	RecalcLayout();
}


void CMainFrame::OnArrangeBottomLeft() 
{
	ArrangeFloatingBars(CBRS_ARRANGE_BOTTOMLEFT);
}


void CMainFrame::OnArrangeBottomRight() 
{
	ArrangeFloatingBars(CBRS_ARRANGE_BOTTOMRIGHT);
}


void CMainFrame::OnArrangeTopLeft() 
{
	ArrangeFloatingBars(CBRS_ARRANGE_TOPLEFT);
}


void CMainFrame::OnArrangeTopRight() 
{
	ArrangeFloatingBars(CBRS_ARRANGE_TOPRIGHT);
}




void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	// DestroyDynamicBars();
	SaveSizeBarState(_T("DocktestBars"));
	COXWorkspaceState workspaceState;
	if (!workspaceState.StoreToRegistry())
	{
		TRACE0("CMainFrame::OnClose : Failed to save workspace to registry, continuing\n");
	}
	MainFrameParent::OnClose();
}

