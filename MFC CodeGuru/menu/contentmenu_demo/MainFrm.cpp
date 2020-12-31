// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "LookMaSDI.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Menu Information for the Content Bar
static CONTENT_ITEMS    ContentInfo[] =
{
    {IDI_COMPOSE, "Main View"},
    {IDI_FINISHED,"Another View"},
    {IDI_FILED,   "Another View"},
    {IDI_CALENDAR,"Another View"},
};



/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_CONTENTMENU, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_CONTENTMENU, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST_CONTENTS, OnSelchangeListContents)
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
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

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "ContentMenu":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_CONTENTMENU
	//   5. Assign the item a Caption: ContentMenu

	// TODO: Change the value of CG_ID_VIEW_CONTENTMENU to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component
	{
		// Initialize dialog bar m_wndContentMenu
		if (!m_wndContentMenu.Create(this, CG_IDD_CONTENTMENU,
			CBRS_LEFT | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_CONTENTMENU))
		{
			TRACE0("Failed to create dialog bar m_wndContentMenu\n");
			return -1;		// fail to create
		}

		m_wndContentMenu.EnableDocking(CBRS_ALIGN_LEFT | CBRS_ALIGN_RIGHT);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndContentMenu);

	}

    m_ContentMenu.SubclassDlgItem(IDC_LIST_CONTENTS, &m_wndContentMenu);
    m_ContentMenu.SetItems(ContentInfo, sizeof(ContentInfo) / sizeof(CONTENT_ITEMS));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

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
void CMainFrame::OnSelchangeListContents() 
{
    switch  (m_ContentMenu.GetCurSel())
    {
    case 0:
        AfxMessageBox("You have selected First Item");
        break;
    case 1:
        AfxMessageBox("You have selected Second Item");
        break;

    case 2:
        AfxMessageBox("You have selected Third Item");
        break;

    case 3:
        AfxMessageBox("You have selected Fourth Item");
        break;

    }
	
}
