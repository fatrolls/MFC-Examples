// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "afxpriv.h"
#include "CustToolBarTest.h"
#include "BCGToolbarButton.h"
#include "BCGToolbarComboBoxButton.h"
#include "BCGToolbarMenuButton.h"
#include "CBCGToolbarCustomize.h"

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
	ON_COMMAND(ID_VIEW_USER_TOOBAR, OnViewUserToobar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_USER_TOOBAR, OnUpdateViewUserToobar)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_WM_CLOSE()
	ON_COMMAND(ID_USER_CONFIGURATION, OnUserConfiguration)
	ON_COMMAND(ID_POPUP_ONE, OnPopupOne)
	ON_COMMAND(ID_POPUP_TWO, OnPopupTwo)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZETOOLBAR, OnToolbarCustomize)
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

	m_bIsTlbCustMode = FALSE;

	//---------------------------------------------------------------
	// Load toolbar images (both resource (standard) and disk (user)):
	//---------------------------------------------------------------
	if (!m_StandardImages.Load (IDR_MAINFRAME))
	{
		TRACE0("Failed to load standard images\n");
		return -1;      // fail to create
	}
	
	if (!m_UserImages.Load (_T("..\\User Buttons.bmp")) &&
		!m_UserImages.Load (_T("User Buttons.bmp")))
	{
		MessageBox ("Can't find 'User Buttons.bmp' file");

		TRACE0("Failed to load user images\n");
		return -1;      // fail to create
	}

	//---------------------------
	// Load the standard toolbar:
	//---------------------------
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.SetImages (&m_StandardImages, &m_UserImages) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetWindowText (_T("Standard"));

	//----------------------------------------
	// Add a combobox to the standard toolbar:
	//----------------------------------------

	CBCGToolbarComboBoxButton comboButton (ID_USER_CONFIGURATION, 3);
	comboButton.AddItem ("Win32 Debug");
	comboButton.AddItem ("Win32 Release");
	comboButton.AddItem ("Win32 Unicode Debug");
	comboButton.AddItem ("Win32 Unicode Release");

	m_wndToolBar.RemoveButton (m_wndToolBar.CommandToIndex (ID_USER_CONFIGURATION));
	m_wndToolBar.InsertButton (comboButton, 4);

	//-------------------------
	// Load the "user" toolbar:
	//-------------------------
	if (!m_wndUserToolBar.Create(this) ||
		!m_wndUserToolBar.SetImages (&m_StandardImages, &m_UserImages))
	{
		TRACE0("Failed to create user toolbar\n");
		return -1;      // fail to create
	}

	m_wndUserToolBar.SetWindowText (_T("User"));

	m_wndUserToolBar.InsertButton (CBCGToolbarMenuButton 
		(0, IDR_BUTTON_MENU, 0, "Select", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL1, 1, "User Tool 1", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL2, 2, "User Tool 2", TRUE));
	m_wndUserToolBar.InsertButton (CBCGToolbarButton 
		(ID_USER_TOOL3, 3, "User Tool 3", TRUE));


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndUserToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndUserToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndUserToolBar, AFX_IDW_DOCKBAR_BOTTOM);

	// Load toolbars states:
	m_wndToolBar.LoadState ("ControlBars", 1);
	m_wndUserToolBar.LoadState ("ControlBars", 2);

	LoadBarState ("ControlBars");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnViewUserToobar() 
{
	ShowControlBar (&m_wndUserToolBar,
					!(m_wndUserToolBar.GetStyle () & WS_VISIBLE),
					FALSE);
}

void CMainFrame::OnUpdateViewUserToobar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndUserToolBar.GetStyle () & WS_VISIBLE);
}

void CMainFrame::OnViewCustomize() 
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGToolbarCustomize* pDlgCust = new 
		CBCGToolbarCustomize (this, &m_StandardImages);

	//--------------------------
	// Add commands by category:
	//--------------------------
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_FILE_NEW, 0));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_FILE_OPEN, 1));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_FILE_SAVE, 2));
	pDlgCust->AddButton ("Main", CBCGToolbarComboBoxButton (ID_USER_CONFIGURATION, 3));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_EDIT_CUT, 4));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_EDIT_COPY, 5));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_EDIT_PASTE, 6));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_FILE_PRINT, 7));
	pDlgCust->AddButton ("Main", CBCGToolbarButton (ID_APP_ABOUT, 8));

	pDlgCust->AddButton ("User",
		CBCGToolbarMenuButton (0, IDR_BUTTON_MENU, 0, "Select", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL1, 1, "User Tool 1", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL2, 2, "User Tool 2", TRUE));
	pDlgCust->AddButton ("User", 
		CBCGToolbarButton (ID_USER_TOOL3, 3, "User Tool 3", TRUE));

	pDlgCust->SetUserCategory ("User");
	pDlgCust->Create ();
}

//////////////////////////////////////////////
// Toobar message handlers

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (LOWORD (lp), HIWORD(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	return 0;
}

LRESULT CMainFrame::OnToolbarCustomize(WPARAM wp,LPARAM)
{
	BOOL bCustMode = (BOOL) wp;
	if (m_bIsTlbCustMode == bCustMode)
	{
		return FALSE;
	}

	m_bIsTlbCustMode = bCustMode;

	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if (!m_bIsTlbCustMode)
	{
		return CMDIFrameWnd::OnCommand(wParam, lParam);
	}

	// If toolbar customization mode - disable all commands!
	MessageBeep (-1);
	return FALSE;
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_RBUTTONUP)
	{
		CWnd* pWnd = CWnd::FromHandlePermanent(pMsg->hwnd);
		CDockBar* pBar = DYNAMIC_DOWNCAST(CDockBar, pWnd);

		if (pBar != NULL)
		{
			CMenu Menu;
			CPoint pt;

			pt.x = LOWORD(pMsg->lParam);
			pt.y = HIWORD(pMsg->lParam);
			pBar->ClientToScreen(&pt);

			if (Menu.LoadMenu(IDR_POPUP_TOOLBAR))
			{
				CMenu* pSubMenu = Menu.GetSubMenu(0);

				if (pSubMenu!=NULL)
				{
					pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
				}
			}
		}
	}
	
	return CMDIFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnClose() 
{
	m_UserImages.Save ();

	m_wndToolBar.SaveState ("ControlBars", 1);
	m_wndUserToolBar.SaveState ("ControlBars", 2);

	SaveBarState ("ControlBars");

	CMDIFrameWnd::OnClose();
}

//--------------------
// Command examples:
//--------------------
void CMainFrame::OnUserConfiguration() 
{
	CObList listButtons;
	if (CBCGToolBar::GetCommandButtons (ID_USER_CONFIGURATION, listButtons) == 0)
	{
		return;
	}

	CBCGToolbarComboBoxButton* pCombo = 
		DYNAMIC_DOWNCAST (CBCGToolbarComboBoxButton, listButtons.GetHead ());
	if (pCombo == NULL)
	{
		return;
	}

	LPCSTR lpszSelItem = pCombo->GetItem ();
	CString strSelItem = (lpszSelItem == NULL) ? _T("") : lpszSelItem;

	MessageBox (strSelItem);
}

void CMainFrame::OnPopupOne() 
{
	MessageBox ("Say One!");
}

void CMainFrame::OnPopupTwo() 
{
	MessageBox ("Say Two!");
}
