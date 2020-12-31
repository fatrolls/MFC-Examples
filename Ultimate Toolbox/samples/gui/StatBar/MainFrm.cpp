// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Statusbar.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP

	ON_MESSAGE(WM_STAT_DBLCLICK, OnClickStatusBar)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_XFER,
	ID_INDICATOR_MAIL,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_CT,
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

    UINT nID, nStyle;
	int cxWidth;
	m_wndStatusBar.GetPaneInfo( 1, nID, nStyle, cxWidth);
	nStyle |= SBPS_PERCENT;
	m_wndStatusBar.SetPaneInfo( 1, nID, nStyle, 100);

	ShowWindow(SW_SHOW);
	if (!m_wndStatusBar.SetUpBar(1, TRUE, TRUE))
	{
		return -1;
	}

	if (SetTimer(1, 1000, NULL) == 0)
		{         
		TRACE(_T("*** ERROR not able to set Timer in OnCreate\n"));
		return -1;
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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnTimer(UINT nIDEvent) 
	{
	if(nIDEvent == 1)
		{
	  	TCHAR buffer[30];
        
    	time_t lTime;
		struct tm datetime; 
		
    	time(&lTime);

#if _MSC_VER >=1400
		localtime_s(&datetime, &lTime);
#else
		datetime = *localtime(&lTime);
#endif
		wsprintf(buffer, _T("%02.2d:%02.2d:%02.2d"), 
			datetime.tm_hour, datetime.tm_min, datetime.tm_sec);

    	if (datetime.tm_sec == 0 || datetime.tm_sec == 30)
		{
			m_wndStatusBar.ResetBar(1);
			m_wndStatusBar.SetBarProgress(1, TRUE, 30, 0);
		}
		else
		{
			m_wndStatusBar.SetBarProgress(1, TRUE, 31, datetime.tm_sec % 30);
		}

		if((datetime.tm_sec % 2) == 0)
			m_wndStatusBar.SetPaneText( 5, (LPCTSTR)buffer, RGB(255,0,0), TRUE);
		else
			m_wndStatusBar.SetPaneText( 5, (LPCTSTR)buffer);
		
		}
		
	CMDIFrameWnd::OnTimer(nIDEvent);
	}

void CMainFrame::OnClose() 
{
	KillTimer(1);
	
	CMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnClickStatusBar(WPARAM wParam, LPARAM lParam)
	{
	UNREFERENCED_PARAMETER(lParam);
	if (wParam != NULL)
		{
		switch(wParam)
			{
			case ID_INDICATOR_MAIL:
//				if(time(0)%2)
//					m_wndStatusBar.SetPaneBitmap(2, IDB_NEWMAIL, EO_CenterFit, RGB(0,128,128));
					m_wndStatusBar.SetPaneBitmap(2, IDB_GREEN_LIGHT, EO_CenterFit, RGB(0,128,128));
//				else
//					m_wndStatusBar.SetPaneBitmap(2, IDB_RED_LIGHT, EO_CenterFit, RGB(0,128,128));
				break;
			default:
				break;
			}
		}
	
	return 0L;
	}
