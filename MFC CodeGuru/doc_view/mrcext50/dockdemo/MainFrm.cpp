// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "dockdemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMRCMDIFrameWndSizeDock)

BEGIN_MESSAGE_MAP(CMainFrame, CMRCMDIFrameWndSizeDock)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()

    // following command handlers are for the View menu items for hiding/showing control bars 
    ON_UPDATE_COMMAND_UI(ID_VIEW_SIZEDIALOG, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_SIZEDIALOG, OnBarCheck)
    ON_UPDATE_COMMAND_UI(ID_VIEW_TREEBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_TREEBAR, OnBarCheck)
    ON_UPDATE_COMMAND_UI(ID_VIEW_CALENDARBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_VIEW_CALENDARBAR, OnBarCheck)
    
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
	if (CMRCMDIFrameWndSizeDock::OnCreate(lpCreateStruct) == -1)
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

    // DOCKDEMO: 
    // creation of a sizeable dialog bar
    m_wndSizeDialogBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS | SZBARF_DLGAUTOSIZE); 
	if (!m_wndSizeDialogBar.Create(this, IDD_SIZEDIALOGBAR,
		CBRS_TOP | CBRS_HIDE_INPLACE,
		ID_VIEW_SIZEDIALOG))
	{
		TRACE0("Failed to create dialog bar m_wndSizeDialogBar\n");
		return -1;		// fail to create
	}
    // and dock it
	m_wndSizeDialogBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndSizeDialogBar);
	

    // CREATION OF A CUSTOM control bar.
    CRect rect(0,0, 100, 200);	
    if (!m_wndTreeBar.Create( NULL, "Tree Bar", WS_VISIBLE | WS_CHILD | CBRS_LEFT,
							rect, this, ID_VIEW_TREEBAR, NULL))
    {
    }
    m_wndTreeBar.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndTreeBar);

    // A Dialog bar with an OCX Calendar control on it.
    m_wndCalendarBar.SetSizeDockStyle(SZBARF_STDMOUSECLICKS | SZBARF_DLGAUTOSIZE); 
	if (!m_wndCalendarBar.Create(this, IDD_CALENDARBAR,
		CBRS_TOP | CBRS_HIDE_INPLACE, ID_VIEW_CALENDARBAR))
	{
		AfxMessageBox("Failed to create Calendar Bar.\n\nThe most likely reason for this is that you\
 don't have the Calendar OCX installed");
	}
    else
    {
        m_wndCalendarBar.EnableDocking(CBRS_ALIGN_ANY);
        DockControlBarLeftOf(&m_wndCalendarBar, &m_wndSizeDialogBar);
    }
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMRCMDIFrameWndSizeDock::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMRCMDIFrameWndSizeDock::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMRCMDIFrameWndSizeDock::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
