// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex19c.h"

#include "MainFrm.h"

#include "PoemDoc.h"
#include "StringView.h"
#include "HexView.h"

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
	ON_COMMAND(ID_VIEW_STRINGVIEW, OnViewStringView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_STRINGVIEW, OnUpdateViewStringView)
	ON_COMMAND(ID_VIEW_HEXVIEW, OnViewHexView)
	ON_UPDATE_COMMAND_UI(ID_VIEW_HEXVIEW, OnUpdateViewHexView)
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

void CMainFrame::OnViewStringView() 
{
	SwitchToView(STRING);
}

void CMainFrame::OnUpdateViewStringView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		!GetActiveView()->IsKindOf(RUNTIME_CLASS(CStringView)));	
}

void CMainFrame::OnViewHexView() 
{
	SwitchToView(HEX);	
}

void CMainFrame::OnUpdateViewHexView(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		!GetActiveView()->IsKindOf(RUNTIME_CLASS(CHexView)));	
}

void CMainFrame::SwitchToView(eView nView)
{
	CView* pOldActiveView = GetActiveView();
	CView* pNewActiveView = (CView*) GetDlgItem(nView);
	if (pNewActiveView == NULL) {
		switch (nView) {
		case STRING:
			pNewActiveView = (CView*) new CStringView;
			break;
		case HEX:
			pNewActiveView = (CView*) new CHexView;
			break;
		}
		CCreateContext context;
		context.m_pCurrentDoc = pOldActiveView->GetDocument();
		pNewActiveView->Create(NULL, NULL, WS_BORDER,
			CFrameWnd::rectDefault, this, nView, &context);
		pNewActiveView->OnInitialUpdate();
	}
	SetActiveView(pNewActiveView);
	pNewActiveView->ShowWindow(SW_SHOW);
	pOldActiveView->ShowWindow(SW_HIDE);
	pOldActiveView->SetDlgCtrlID(
		pOldActiveView->GetRuntimeClass() == 
		RUNTIME_CLASS(CStringView) ? STRING : HEX);
	pNewActiveView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	RecalcLayout();
}
