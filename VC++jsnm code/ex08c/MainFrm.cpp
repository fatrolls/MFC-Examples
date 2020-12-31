// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex08c.h"

#include "MainFrm.h"
#include "ex08cDoc.h"
#include "ex08cView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

const char CMainFrame::s_profileSplit[] = "Split";

IMPLEMENT_DYNCREATE(CMainFrame, CPersistentFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CPersistentFrame)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status text
	ID_SEPARATOR,           // URL
	ID_INDICATOR_BUSY,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPersistentFrame::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,
//	if (!m_wndStatusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,
//		ID_MY_STATUS_BAR) || !m_wndStatusBar.SetIndicators(indicators,
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

	return 0;
}

BOOL CMainFrame::OnCreateClient( LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	TRACE("CMainFrame::OnCreateClient\n");
	VERIFY(m_wndSplitter.CreateStatic( this, 1, 2));
	VERIFY(m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CEx08cView),
					CSize(0, 1000), pContext));
	VERIFY(m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CEx08cView),
					CSize(1000, 1000), pContext));
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CPersistentFrame::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CPersistentFrame::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CPersistentFrame::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::ActivateFrame(int nCmdShow) 
{
	CPersistentFrame::ActivateFrame(nCmdShow);
    m_nSplit = AfxGetApp()->GetProfileInt(s_profileHeading,
                                             s_profileSplit, 320);
	m_wndSplitter.SetColumnInfo(0, m_nSplit, 0);
	m_wndSplitter.RecalcLayout();
}

void CMainFrame::OnDestroy() 
{
	CPersistentFrame::OnDestroy();
	int nMin;
	m_wndSplitter.GetColumnInfo(0, m_nSplit, nMin);
    AfxGetApp()->WriteProfileInt(s_profileHeading,
                                 s_profileSplit, m_nSplit);
}
