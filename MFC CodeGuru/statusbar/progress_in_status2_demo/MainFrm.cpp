// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ProgressDemo.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_BAR, OnTestBar)
	ON_COMMAND(ID_TEST_SMOOTHBAR, OnTestSmoothbar)
	ON_COMMAND(ID_TEST_STDBAR, OnTestStdbar)
	ON_COMMAND(ID_TEST_CHANGETEXT, OnTestChangetext)
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
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

BOOL PeekAndPump()
{
	static MSG msg;

	while (::PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)) {
		if (!AfxGetApp()->PumpMessage()) {
			::PostQuitMessage(0);
			return FALSE;
		}	
	}

	return TRUE;
}

#include "ProgressBar.h"
void CMainFrame::OnTestBar() 
{
	CProgressBar bar(_T("Progress"), 40, 5000, TRUE);

	for (int i = 0; i < 5000; i++) {
		bar.StepIt();
		PeekAndPump();
	}
}

void CMainFrame::OnTestSmoothbar() 
{
	CProgressBar bar(_T("Progress"), 40, 5000, TRUE);

	for (int i = 0; i < 5000; i++) {
		bar.StepIt();
		PeekAndPump();
	}
}

void CMainFrame::OnTestStdbar() 
{
	CProgressBar bar(_T("Progress"), 40, 5000);

	for (int i = 0; i < 5000; i++) {
		bar.StepIt();
		PeekAndPump();
	}	
}


void CMainFrame::OnTestChangetext() 
{
	CProgressBar bar(_T("Progress"), 40, 5000);

	for (int i = 0; i < 5000; i++) {

		CString str;
		str.Format("%d%% complete", i*100/5000);
		bar.SetText(str);

		bar.StepIt();
		PeekAndPump();
	}	
}
