// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "resource.h"
#include "DockProp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, COXMDIFrameWndSizeDock)

BEGIN_MESSAGE_MAP(CMainFrame, COXMDIFrameWndSizeDock)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// standard on/off control bar handlers for View menu. 
	ON_UPDATE_COMMAND_UI(ID_PROPERTYSHEETBAR, OnUpdateControlBarMenu)
	ON_COMMAND_EX(ID_PROPERTYSHEETBAR, OnBarCheck)
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
: m_wndMeasureBar()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COXMDIFrameWndSizeDock::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndMeasureBar.Create(this, CBRS_RIGHT, 
		WS_CHILD | WS_VISIBLE | TCS_TABS | TCS_SINGLELINE | TCS_RAGGEDRIGHT, 
		ID_PROPERTYSHEETBAR))
		{
		TRACE0("Failed to create Dialogbar\n");
		return -1;      // fail to create
		}

	EnableDocking(CBRS_ALIGN_ANY);
	// TODO: Delete these three lines if you don't want the measurebar to
	//  be dockable
	m_wndMeasureBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMeasureBar);
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COXMDIFrameWndSizeDock::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	COXMDIFrameWndSizeDock::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	COXMDIFrameWndSizeDock::Dump(dc);
}

#endif //_DEBUG

