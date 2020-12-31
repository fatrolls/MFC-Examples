#include "stdafx.h"
#include "Explorer.h"
#include "MainFrm.h"
#include "Doc.h"
#include "View.h"
#include "FormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame()
{
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
		return -1;
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient
(
	LPCREATESTRUCT lpcs,
	CCreateContext *pContext
)
{
	if
	(
		!m_wndSplitter.CreateStatic
		(
			this, 1, 2, WS_CHILD | WS_VISIBLE, AFX_IDW_PANE_FIRST
		)
	)
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	if
	(
		!m_wndSplitter.CreateView
		(
			0, 0, RUNTIME_CLASS(CDirFormView), CSize(100, 100), pContext
		)
	)
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if
	(
		!m_wndSplitter.CreateView
		(
			0, 1, RUNTIME_CLASS(CExplorerView), CSize(100, 100), pContext
		)
	)
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}
	
	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif
