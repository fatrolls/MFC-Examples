// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BitmapMenuDemo.h"

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
	ON_COMMAND(ID_TEST_ENABLED, OnTestEnabled)
	ON_COMMAND(ID_TEST_HELLO, OnTestHello)
	ON_COMMAND(ID_TEST_MARKEDPAGE, OnTestMarkedpage)
	ON_COMMAND(ID_TEST_PAGE, OnTestPage)
	ON_UPDATE_COMMAND_UI(ID_TEST_PAGE, OnUpdateTestPage)
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

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// Set images from toolbar to use with corresponding menu items
	Organizer.AutoSetMenuImage();
	// explicitly designate images to use with menu items
	Organizer.SetMenuBitmap(ID_TEST_PAGE, MAKEINTRESOURCE(IDB_PAGE));
	Organizer.SetMenuBitmap(ID_TEST_HELLO, MAKEINTRESOURCE(IDB_HELLO));
	Organizer.SetMenuBitmap(ID_TEST_MARKEDPAGE, MAKEINTRESOURCE(IDB_MARKEDPAGE));
	Organizer.SetMenuBitmap(ID_TEST_DISABLED, MAKEINTRESOURCE(IDB_EXPLORE));
	Organizer.SetMenuBitmap(ID_TEST_ENABLED, MAKEINTRESOURCE(IDB_EXPLORE));

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

////
// Dummy handlers
////
void CMainFrame::OnTestEnabled() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnTestHello() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnTestMarkedpage() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnTestPage() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnUpdateTestPage(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	UNREFERENCED_PARAMETER(pCmdUI);
	
    CMenu* pMenu = GetMenu();
    ASSERT (pMenu); 
	CTime time = CTime::GetCurrentTime();
	CString menuItem;
	if(time.GetSecond()%2)
	{
		menuItem=time.Format( "%A, %B %d, %Y %H %M %S" );
	}
	else
	{
		menuItem=_T("");
	}
    pMenu->ModifyMenu(ID_TEST_PAGE, MF_BYCOMMAND | MF_STRING,
                      ID_TEST_PAGE, menuItem); 
}
