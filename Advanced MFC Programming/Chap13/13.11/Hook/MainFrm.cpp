#define __DLLIMPORT__

#include "stdafx.h"
#include "..\HookLib\HookLib.h"
#include "Hook.h"

#include "MainFrm.h"

HINSTANCE hInstance;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT uMsgFinishJournal=0;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_HIDE_GO, OnHideGo)
	ON_COMMAND(ID_MACRO_PALYBACK, OnMacroPalyback)
	ON_COMMAND(ID_MACRO_RECORD, OnMacroRecord)
	ON_UPDATE_COMMAND_UI(ID_MACRO_PALYBACK, OnUpdateMacroPalyback)
	ON_UPDATE_COMMAND_UI(ID_MACRO_RECORD, OnUpdateMacroRecord)
	ON_UPDATE_COMMAND_UI(ID_HIDE_GO, OnUpdateHideGo)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(uMsgFinishJournal, OnFinishJournal)
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
	m_bEnableMenu=TRUE;
	m_bPlayAvailable=FALSE;
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

	uMsgFinishJournal=RegisterWindowMessage(WM_FINISHJOURNAL);
	hInstance=LoadLibrary("HookLib.Dll");
	RegisterMessage();
	ASSERT(hInstance);

	return 0;
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

void CMainFrame::OnClose() 
{
	FreeLibrary(hInstance);
	CFrameWnd::OnClose();
}

void CMainFrame::OnHideGo() 
{
	m_bEnableMenu=FALSE;
	SetKeyboardHook(GetSafeHwnd(), hInstance);
	ShowWindow(SW_HIDE);		
}

void CMainFrame::OnMacroPalyback() 
{
	m_bEnableMenu=FALSE;
	SetJournalPlaybackHook(GetSafeHwnd(), hInstance);
}

void CMainFrame::OnMacroRecord() 
{
	m_bEnableMenu=FALSE;
	SetJournalRecordHook(GetSafeHwnd(), hInstance);
}

LONG CMainFrame::OnFinishJournal(WPARAM wParam, LPARAM lParam)
{
	if((BOOL)wParam == FALSE)
	{
		AfxMessageBox("Recording Finished");
		m_bPlayAvailable=TRUE;
	}
	else 
	{
		m_bPlayAvailable=FALSE;
		AfxMessageBox("Playback Finished");
	}
	m_bEnableMenu=TRUE;

	return TRUE;
}

void CMainFrame::OnUpdateMacroPalyback(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEnableMenu && m_bPlayAvailable);
}

void CMainFrame::OnUpdateMacroRecord(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEnableMenu);
}

void CMainFrame::OnUpdateHideGo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEnableMenu);
}
