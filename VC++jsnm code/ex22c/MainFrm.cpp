// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex22c.h"

#include "MainFrm.h"
#include "ChildFrm.h"

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
	ON_WM_CLOSE()
	ON_WM_QUERYENDSESSION()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseall)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_CLOSEALL, OnUpdateWindowCloseall)
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
	m_nChild = 1;
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

void CMainFrame::CreateInitialChild()
{
	OnFileNew(); // Call it here because it's protected
}

BOOL CMainFrame::CloseAllChildWindows()
{
	// returns TRUE if all child windows permit closure
	CChildFrame* pChild;
	CChildFrame* pPrevChild = NULL;
	while ((pChild = (CChildFrame*) MDIGetActive()) != NULL) {
		if (pChild == pPrevChild) {
			return FALSE; // closure not permitted
		}
		pPrevChild = pChild;
		pChild->SendMessage(WM_CLOSE);
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnClose() 
{
	if (CloseAllChildWindows()) {
		CMDIFrameWnd::OnClose();
	}
}

BOOL CMainFrame::OnQueryEndSession() 
{
	return CloseAllChildWindows();
}

void CMainFrame::OnFileNew() 
{
	BOOL bMaximized = FALSE;
	// creates a new child window, maximized if active child is maximized
	CChildFrame* pActiveChild = (CChildFrame*) MDIGetActive(&bMaximized);
	CChildFrame* pChild = new CChildFrame();
	pChild->LoadFrame(IDR_EX22CTYPE,
		WS_CHILD | WS_VISIBLE | WS_OVERLAPPEDWINDOW |
		(bMaximized ? WS_MAXIMIZE : 0), this);

	CString strTitle;
	strTitle.Format("Child Window %d", m_nChild++);
	pChild->SetWindowText(strTitle);
}

void CMainFrame::OnWindowCloseall() 
{
	CloseAllChildWindows();
}

void CMainFrame::OnUpdateWindowCloseall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(MDIGetActive() != NULL);
}

