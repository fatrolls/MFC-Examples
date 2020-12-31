#include "stdafx.h"
#include "Ini.h"
#include "MainFrm.h"
#include "IniDoc.h"
#include "EditView.h"
#include "IniView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
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
	CString szStr;
	CIniApp *pApp;

	pApp=(CIniApp *)AfxGetApp();

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.Create(this, WS_CHILD | CBRS_TOP | WS_VISIBLE) ||
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

	m_wndToolBar.SetBarStyle
	(
		m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC
	);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	LoadBarState(TOOL_BAR);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext)
{
	int nSizeCy;
	CRect rect;
	CString szStr;
	CIniApp *pApp;

	pApp=(CIniApp *)AfxGetApp();
	if
	(
		!m_wndSplitter.CreateStatic
		(
			this, 2, 1, WS_CHILD | WS_VISIBLE, AFX_IDW_PANE_FIRST
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
			0, 0, RUNTIME_CLASS(CIniView), CSize(100, 100), pContext
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
			1, 0, RUNTIME_CLASS(CIniEditView), CSize(100, 100), pContext
		)
	)
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	szStr=pApp->GetProfileString(FRAME_WINDOW, WINDOW_POSITION);
	if(!szStr.IsEmpty())
	{
		sscanf
		(
			szStr,
			"%d,%d,%d,%d",
			&rect.left,
			&rect.top,
			&rect.right,
			&rect.bottom
		);
		MoveWindow(rect);
	}
	nSizeCy=pApp->GetProfileInt(FRAME_WINDOW, SPLITTER_SIZE, 0);
	if(nSizeCy != 0)m_wndSplitter.SetRowInfo(0, nSizeCy, 0);
	else
	{
		GetClientRect(rect);
		m_wndSplitter.SetRowInfo(0, rect.Height()/2, 0);
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

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if(nID == SC_CLOSE)
	{
	}
	CFrameWnd::OnSysCommand(nID, lParam);
}

void CMainFrame::OnClose() 
{
	CRect rect;
	CWinApp* pApp=AfxGetApp();
	CString szStr;
	int cySize;
	int cyMinSize;

	ASSERT(pApp);
	GetWindowRect(rect);
	szStr.Format("%d,%d,%d,%d", rect.left, rect.top, rect.right, rect.bottom);

	if(IsIconic() == TRUE)
	{
		pApp->WriteProfileInt
		(
			FRAME_WINDOW,
			WINDOW_STATUS,
			WINDOW_STATUS_ICONIC
		);
	}
	else
	{
		if(IsZoomed() == TRUE)
		{
			pApp->WriteProfileInt
			(
				FRAME_WINDOW,
				WINDOW_STATUS,
				WINDOW_STATUS_ZOOMED
			);
		}
		else
		{
			pApp->WriteProfileInt
			(
				FRAME_WINDOW,
				WINDOW_STATUS,
				WINDOW_STATUS_NORMAL
			);
			pApp->WriteProfileString(FRAME_WINDOW, WINDOW_POSITION, szStr);
		}
		m_wndSplitter.GetRowInfo(0, cySize, cyMinSize);
		pApp->WriteProfileInt(FRAME_WINDOW, SPLITTER_SIZE, cySize);
	}

	SaveBarState(TOOL_BAR);

	CFrameWnd::OnClose();
}
