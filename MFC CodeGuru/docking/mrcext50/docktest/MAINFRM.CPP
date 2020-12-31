// mainfrm.cpp : implementation of the CMainFrame class
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:34  $

#include "stdafx.h"
#include "docktest.h"
#include "mainfrm.h"

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
	
	ON_UPDATE_COMMAND_UI(ID_SIZETOOLBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_SIZETOOLBAR, OnBarCheck)
END_MESSAGE_MAP()

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

CMainFrame::CMainFrame() 
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
	
	// 	Uncommenting the line below will result in the toolbar having configuration.
	// 	This function specifies the command ID's of the button images in the bitmap.
	// 	The following SetButtons() then specifies which buttons are actually present
	m_wndToolBar.SetBitmapIds(allbuttons, sizeof(allbuttons)/sizeof(UINT));
	m_wndToolBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS);


	// Note: there is very little difference to what you'd see from standard AppWizard code.
	// The toolbar is created in the same way...just that it's a CMRCSizeToolBar, instead of
	// a CToolBar
	if (!m_wndFixedToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS) ||
		!m_wndFixedToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndFixedToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	} 

	
	if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS, ID_SIZETOOLBAR) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	
	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	m_wndFixedToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndFixedToolBar);
	
	// This is a sizeable dialog bar...
	if (!m_DlgBar.Create(this, IDD_DIALOGBAR, CBRS_TOP, ID_SIZEDLGBAR))   
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      
	} 
	m_DlgBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_DlgBar);


	// This is a sizeable dialog bar.. that includes gadget resizing
	m_SizeDlgBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS | SZBARF_DLGAUTOSIZE);
	if (!m_SizeDlgBar.Create(this, IDD_DIALOGBAR2, CBRS_TOP, ID_FIXEDDLGBAR))   
	{
		TRACE0("Failed to create dialog bar\n");
		return -1;      
	} 
	m_SizeDlgBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_SizeDlgBar, AFX_IDW_DOCKBAR_BOTTOM);	// dock it on the bottom

	// This is a list box that is added dynamically. You can have almost any number of these...
	if (!m_SizeListBar.Create(this))
	{
		TRACE0("Failed to create list box bar\n");
		return -1;      
	} 
			
	m_SizeListBar.EnableDocking(CBRS_ALIGN_ANY);
	
	// Following code will dock our sizeable control bar on the same row as
	// the dialog bar - a lot of people have asked how to do this.
	CRect rcList, rcDlg;
	m_SizeDlgBar.GetWindowRect(&rcDlg);
	m_SizeListBar.GetWindowRect(&rcList);
	rcDlg.BottomRight() = rcDlg.TopLeft() + rcList.Size();
	DockControlBar(&m_SizeListBar, AFX_IDW_DOCKBAR_BOTTOM, &rcDlg);

	RecalcLayout();
	
	TileDockedBars(CBRS_ALIGN_BOTTOM);		// this makes the bars the same size

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
	SaveSizeBarState("DocktestBars");
	MainFrameParent::OnClose();
}
