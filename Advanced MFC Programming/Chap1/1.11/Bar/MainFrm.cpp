#include "stdafx.h"
#include "Bar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_COLORBAR, OnViewColorBar)
	ON_COMMAND(ID_VIEW_DIALOGBAR, OnViewDialogBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLORBAR, OnUpdateViewColorBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_DIALOGBAR, OnUpdateViewDialogBar)
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

	if (!m_wndColorButton.Create(this) ||
		!m_wndColorButton.LoadToolBar(IDR_COLOR_BUTTON))
	{													
		TRACE0("Failed to create toolbar\n");			
		return -1; 
	}			

	if			
	(								
		!m_wndDialogBar.Create		
		(							
			this,					
			IDD_DIALOG_BAR,			
			CBRS_BOTTOM | CBRS_TOOLTIPS | CBRS_FLYBY,
			IDD_DIALOG_BAR							
		)											
	)												
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
	m_wndColorButton.SetBarStyle(m_wndColorButton.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndColorButton.EnableDocking(CBRS_ALIGN_ANY);		
	m_wndDialogBar.EnableDocking(CBRS_ALIGN_ANY);		
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndColorButton);
	DockControlBar(&m_wndDialogBar);
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

void CMainFrame::OnViewColorBar()												//ATM 1.8
{																				//ATM 1.8
	BOOL bShow;																	//ATM 1.8
																				//ATM 1.8
	bShow=m_wndColorButton.IsWindowVisible() ? FALSE:TRUE;						//ATM 1.8
	ShowControlBar(&m_wndColorButton, bShow, FALSE);							//ATM 1.8
}																				//ATM 1.8

void CMainFrame::OnViewDialogBar()												//ATM 1.8
{																				//ATM 1.8
	BOOL bShow;																	//ATM 1.8
																				//ATM 1.8
	bShow=m_wndDialogBar.IsWindowVisible() ? FALSE:TRUE;						//ATM 1.8
	ShowControlBar(&m_wndDialogBar, bShow, FALSE);								//ATM 1.8
}																				//ATM 1.8

void CMainFrame::OnUpdateViewColorBar(CCmdUI* pCmdUI)							//ATM 1.8
{																				//ATM 1.8
	pCmdUI->SetCheck(m_wndColorButton.IsWindowVisible());						//ATM 1.8
}																				//ATM 1.8

void CMainFrame::OnUpdateViewDialogBar(CCmdUI* pCmdUI)							//ATM 1.8
{																				//ATM 1.8
	pCmdUI->SetCheck(m_wndDialogBar.IsWindowVisible());							//ATM 1.8
}																				//ATM 1.8
