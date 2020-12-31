// MainFrm.cpp : implementation of the CMainFrame class
//
// 1998 Kirk Stowell ( kstowel@sprynet.com )
// www.geocities.com/SiliconValley/Haven/8230/index.html
//
// You are free to use, modify and distribute this source, as long as
// there is no charge, and this HEADER stays intact. This source is
// supplied "AS-IS", and without WARRANTY OF ANY KIND, and the user
// holds the author blameless for any or all problems that may arise
// from the use of this code.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "demo_toolbar.h"

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
	ON_COMMAND(ID_BACK, OnBack)
	ON_COMMAND(ID_FORWARD, OnForward)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_REFRESH, OnRefresh)
	ON_COMMAND(ID_HOME, OnHome)
	//}}AFX_MSG_MAP

	// will have to define some message handlers for our controls.
	ON_CBN_SELENDOK( IDC_COMBO, OnSelEndOk )
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnToolbarDropDown)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static CString comboText[] =
{
	"Page Width",
	" 50%",
	"100%",
	"200%",
	"300%",
	"400%",
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

	if (!m_winToolBar.Create(this) ||
		!m_winToolBar.LoadToolBar(IDR_WINDOW))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_hotToolBar.Create(this) ||
		!m_hotToolBar.LoadToolBar(IDR_HOTBAR))
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
	m_winToolBar.SetBarStyle(m_winToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_hotToolBar.SetBarStyle(m_hotToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_winToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_hotToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBarLeftOf(&m_winToolBar,&m_wndToolBar);
	DockControlBar(&m_hotToolBar);

	LPSTR lpText[] = {"Back","Forward","Stop","Refresh","Home"};

	// Create and initialize image list used for child toolbar
	CBitmap bmp;
	bmp.LoadBitmap( IDB_COLOR_IMAGELIST );
	m_pImageColor.Create( 21,20,ILC_COLORDDB|ILC_MASK,5,1);
	m_pImageColor.Add( &bmp, RGB(191,191,191) );

	// Create and initialize hot image list used for child toolbar
	CBitmap hotBmp;
	hotBmp.LoadBitmap( IDB_GRAY_IMAGELIST );
	m_pImageNoColor.Create( 21,20,ILC_COLORDDB|ILC_MASK,5,1);
	m_pImageNoColor.Add( &hotBmp, RGB(191,191,191) );

	// Set toolbar image lists
	m_hotToolBar.SetImageList( &m_pImageNoColor, TB_SETIMAGELIST );
	m_hotToolBar.SetImageList( &m_pImageColor,   TB_SETHOTIMAGELIST );

	// Add text to toolbar buttons.
	for( int i = ID_BACK, x = 0; i <= ID_HOME; i++, x++ )
	{
		m_hotToolBar.SetButtonText(
			m_hotToolBar.CommandToIndex( i ), lpText[x] );
	}

	// set button to dropdown list
	m_wndToolBar.SetButtonDropDown( ID_FILE_OPEN );
	m_hotToolBar.SetButtonDropDown( ID_BACK );
	m_hotToolBar.SetButtonDropDown( ID_FORWARD );

	// Insert the CEdit control
	m_edit = (CEdit*)m_wndToolBar.InsertControl(
		RUNTIME_CLASS(CEdit), _T(""), CRect(-35,-22,0,0), IDC_EDIT,
		ES_AUTOHSCROLL | WS_BORDER | WS_TABSTOP );

	// Insert the CComboBox control
	m_combo = (CComboBox*)m_wndToolBar.InsertControl(
		RUNTIME_CLASS(CComboBox), _T(""), CRect(-100,-200,0,0), IDC_COMBO,
		WS_CHILD | CBS_DROPDOWNLIST | CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS );

	// Add strings to combo box
	for( i = 0; i < 5; i++ ) {
		m_combo->AddString( comboText[i] );
	}
	
	// Select first index.
	m_combo->SetCurSel(0);

	// Install cool menus.
	m_menuManager.Install((CFrameWnd*)this);
	m_menuManager.LoadToolbar(IDR_MAINFRAME);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.lpszClass = AfxRegisterWndClass(
      CS_DBLCLKS,                       // if you need double-clicks
      NULL,                             // no cursor (use default)
      NULL,                             // no background brush
      AfxGetApp()->LoadIcon(IDR_MAINFRAME)); // app icon
   ASSERT(cs.lpszClass);
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

void CMainFrame::OnSelEndOk()
{
	SetComboIndex( m_combo->GetCurSel());
	MessageBox( "Combo box selection made!",
		"CCoolbar Message", MB_ICONINFORMATION );
}

void CMainFrame::OnToolbarDropDown(NMTOOLBAR* pnmtb, LRESULT *plr)
{
	CWnd *pWnd;
	UINT nID;

	if( pnmtb->iItem == ID_FILE_OPEN ) {
		pWnd = &m_wndToolBar;
		nID = IDR_POPUP;
	}
	
	else if( pnmtb->iItem == ID_BACK ) {
		pWnd = &m_hotToolBar;
		nID = IDR_POPUP;
	}

	else if( pnmtb->iItem == ID_FORWARD ) {
		pWnd = &m_hotToolBar;
		nID = IDR_POPUP;
	}

	else {
		return;
	}

	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);

	CRect rc;
	pWnd->SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	pWnd->ClientToScreen(&rc);

	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
}

void CMainFrame::DockControlBarLeftOf(CToolBar* Bar, CToolBar* LeftOf)
{
	CRect rect;
	DWORD dw;
	UINT n;
	
	// get MFC to adjust the dimensions of all docked ToolBars
	// so that GetWindowRect will be accurate
	RecalcLayout(TRUE);
	
	LeftOf->GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	dw=LeftOf->GetBarStyle();
	n = 0;
	n = (dw&CBRS_ALIGN_TOP)				 ? AFX_IDW_DOCKBAR_TOP		: n;
	n = (dw&CBRS_ALIGN_BOTTOM	&& n==0) ? AFX_IDW_DOCKBAR_BOTTOM	: n;
	n = (dw&CBRS_ALIGN_LEFT		&& n==0) ? AFX_IDW_DOCKBAR_LEFT		: n;
	n = (dw&CBRS_ALIGN_RIGHT	&& n==0) ? AFX_IDW_DOCKBAR_RIGHT	: n;
	
	// When we take the default parameters on rect, DockControlBar will dock
	// each Toolbar on a seperate line. By calculating a rectangle, we in effect
	// are simulating a Toolbar being dragged to that location and docked.
	DockControlBar(Bar,n,&rect);
}


void CMainFrame::OnBack() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnForward() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnStop() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnRefresh() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnHome() 
{
	// TODO: Add your command handler code here
	
}

