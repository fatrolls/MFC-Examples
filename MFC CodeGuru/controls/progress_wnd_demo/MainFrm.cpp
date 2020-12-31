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

#define TEST_RANGE 10000

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_TEST_SMOOTHBAR, OnTestSmoothbar)
	ON_COMMAND(ID_TEST_STDBAR, OnTestStdbar)
	ON_COMMAND(ID_TEST_MODAL, OnTestModal)
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
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = 300; cs.cy = 200;
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

#include "ProgressWnd.h"

void CMainFrame::OnTestSmoothbar() 
{
	CProgressWnd wndProgress(this, "Progress", TRUE);

	wndProgress.SetRange(0,TEST_RANGE);
	wndProgress.SetText("This is a progress window...\n\n"
						"Try dragging it around or hitting Cancel.");

	for (int i = 0; i < TEST_RANGE; i++) {
		wndProgress.StepIt();
		wndProgress.PeekAndPump();

		if (wndProgress.Cancelled()) {
			MessageBox("Progress Cancelled");
			break;
		}
	}	
}

void CMainFrame::OnTestStdbar() 
{
	CProgressWnd wndProgress(this, "Progress");

	wndProgress.SetRange(0,TEST_RANGE);
	wndProgress.SetText("This is a progress window...\n\n"					 
						"Try dragging it around or hitting Cancel.");

	for (int i = 0; i < TEST_RANGE; i++) {
		wndProgress.StepIt();
		wndProgress.PeekAndPump();

		if (wndProgress.Cancelled()) {
			MessageBox("Progress Cancelled");
			break;
		}
	}	
}

void CMainFrame::OnTestModal() 
{
	CProgressWnd wndProgress(this, "Progress");

	wndProgress.SetRange(0,TEST_RANGE);
	wndProgress.SetText("This is a progress window...\n\n"					 
						"Try dragging it around, hitting Cancel or pressing ESC.");

	for (int i = 0; i < TEST_RANGE; i++) {
		wndProgress.StepIt();
		wndProgress.PeekAndPump(TRUE, TRUE);

		if (wndProgress.Cancelled()) {
			MessageBox("Progress Cancelled");
			break;
		}
	}	
}
