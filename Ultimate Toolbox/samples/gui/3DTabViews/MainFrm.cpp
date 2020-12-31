// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TabViews.h"

#include "TabViewsDoc.h"
#include "TabViewsView.h"
#include "HexView.h"
#include "StatisticsView.h"
#include "Customize.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CMainFrameWindow)

BEGIN_MESSAGE_MAP(CMainFrame, CMainFrameWindow)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_SHOW_CUSTOMIZE_DLG, OnViewShowCustomizeDlg)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SHOW_CUSTOMIZE_DLG, OnUpdateViewShowCustomizeDlg)
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
	m_dwOffsetExt=5;
	m_dwOffsetInt=0;
	m_dwStyle=DEFAULT_3DTABCTRLSTYLE;
	m_bOpenCustomizeDlg=TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMainFrameWindow::OnCreate(lpCreateStruct) == -1)
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

	// Let the menu organizer fix our menus
	Organizer.AttachFrameWnd(this);
	// use button from toolbars with corresponding items in menu
	Organizer.AutoSetMenuImage();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMainFrameWindow::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMainFrameWindow::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMainFrameWindow::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
#ifndef _MDI_INTERFACE
	UNREFERENCED_PARAMETER(lpcs);

	if(m_bOpenCustomizeDlg)
	{
		CCustomizeDlg dlgCustomize(this);
		dlgCustomize.m_dwOffsetExt=m_dwOffsetExt;
		dlgCustomize.m_dwOffsetInt=m_dwOffsetInt;
		dlgCustomize.m_dwStyle=m_dwStyle;
		dlgCustomize.m_bOpenCustomizeDlg=m_bOpenCustomizeDlg;

		if(dlgCustomize.DoModal()==IDOK)
		{
			m_dwOffsetExt=dlgCustomize.m_dwOffsetExt;
			m_dwOffsetInt=dlgCustomize.m_dwOffsetInt;
			m_dwStyle=dlgCustomize.m_dwStyle;
			m_bOpenCustomizeDlg=dlgCustomize.m_bOpenCustomizeDlg;
		}
	}

	if(!m_TabViewContainer.Create(this,CRect(0,0,0,0),m_dwStyle))
		return FALSE;

	m_TabViewContainer.SetOffsetExternal(m_dwOffsetExt);
	m_TabViewContainer.SetOffsetInternal(m_dwOffsetInt);

	VERIFY(m_ilContainer.Create(IDB_IL_TABVIEWS,16,0,RGB(255,0,255)));
	m_TabViewContainer.SetImageList(&m_ilContainer);

	if(!m_TabViewContainer.AddPage(pContext->m_pNewViewClass,
		pContext,_T("Editor"),0))
		return FALSE;
	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CHexView),
		pContext,_T("HexView"),1))
		return FALSE;

	if(!m_TabViewContainer.AddPage(RUNTIME_CLASS(CStatisticsView),
		pContext,_T("Statistics"),2))
		return FALSE;

	m_TabViewContainer.SetActivePageIndex(0);
	
	return TRUE;
#else
	return COXMenuBarFrame<CMainFrameWindow,CDockBar>::
		OnCreateClient(lpcs, pContext);
#endif
}


void CMainFrame::OnViewShowCustomizeDlg() 
{
	// TODO: Add your command handler code here
	m_bOpenCustomizeDlg=!m_bOpenCustomizeDlg;
}

void CMainFrame::OnUpdateViewShowCustomizeDlg(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_bOpenCustomizeDlg);
}
