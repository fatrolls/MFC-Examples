// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Customize.h"

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
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CToolBarInfo CMainFrame::mainToolBar[] =
{
	{{0, ID_FILE_NEW  , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0}, "New"     },
	{{1, ID_FILE_OPEN , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 1}, "Open"    },
	{{2, ID_FILE_SAVE , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 2}, "Save"    },
	{{0, ID_SEPARATOR , TBSTATE_ENABLED, TBSTYLE_SEP   , 0, 3}, ""        },
	{{3, ID_EDIT_CUT  , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 4}, "Cut"     },
	{{4, ID_EDIT_COPY , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 5}, "Copy"    },
	{{5, ID_EDIT_PASTE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 6}, "Paste"   },
	{{0, ID_SEPARATOR , TBSTATE_ENABLED, TBSTYLE_SEP   , 0, 7}, ""        },
	{{6, ID_FILE_PRINT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 8}, "Print"   },
	{{7, ID_APP_ABOUT , TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 9}, "About..."}
};

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
		int		 success;		// indicates fail/success

	// if base class fails - indicate
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
	{
		success = -1;
	}

	// else we may continue with creation
	else
	{
		// if the toolbar can't be created - indicate	
		if (!m_wndToolBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP,
			AFX_IDW_TOOLBAR, mainToolBar,
			"Software\\Lockheed Martin\\BinaryAnalyst\\Settings\\Toolbar",
			"ToolBar Settings") || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME, TRUE))
		{
			TRACE0("Failed to create toolbar\n");
			success = -1;
		}

		// else we may continue creation
		else
		{
			// if we can't create the status bar - indicate
			if (!m_wndStatusBar.Create(this) ||
				!m_wndStatusBar.SetIndicators(indicators,
				  sizeof(indicators)/sizeof(UINT)))
			{
				TRACE0("Failed to create status bar\n");
				success = -1;
			}

			// else we may continue creation
			else
			{
				// TODO: Remove this if you don't want tool tips or a resizeable toolbar
				m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
					CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

				// TODO: Delete these three lines if you don't want the toolbar to
				//  be dockable
				m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
				EnableDocking(CBRS_ALIGN_ANY);
				DockControlBar(&m_wndToolBar);

				// toolbar and status bar have been created - restore it
				LoadBarState("ToolBar");
			}
		}
	}
	return success;
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

void CMainFrame::OnDestroy() 
{
	// save the toolbar information
	SaveBarState("ToolBar");

	// default processing
	CMDIFrameWnd::OnDestroy();
}
