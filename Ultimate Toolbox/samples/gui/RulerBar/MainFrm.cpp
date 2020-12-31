// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RulerBar.h"

#include "MainFrm.h"
#include "CustomizeRulersDlg.h"

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
	ON_COMMAND(ID_VIEW_CUSTOMIZE_RULERS, OnViewCustomizeRulers)
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
	
	m_bShowHorz=TRUE;
	m_bShowVert=TRUE;
	m_nUnit=0;
	m_nSize=18;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this,
		WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC) || 
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

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
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


void CMainFrame::OnViewCustomizeRulers() 
{
	// TODO: Add your command handler code here

	CCustomizeRulersDlg customizeDlg;
	customizeDlg.m_bShowHorz=m_bShowHorz;
	customizeDlg.m_bShowVert=m_bShowVert;
	customizeDlg.m_nUnit=m_nUnit;
	customizeDlg.m_nSize=m_nSize;
	if(customizeDlg.DoModal()==IDOK)
	{
		m_bShowHorz=customizeDlg.m_bShowHorz;
		m_bShowVert=customizeDlg.m_bShowVert;
		m_nUnit=customizeDlg.m_nUnit;
		m_nSize=customizeDlg.m_nSize;

		// update all views
		CRulerBarApp* pApp=(CRulerBarApp*)AfxGetApp();
		POSITION posTemplate=pApp->GetFirstDocTemplatePosition();
		while(posTemplate!=NULL)
		{
			CDocTemplate* pTemplate=pApp->GetNextDocTemplate(posTemplate);
			POSITION posDoc=pTemplate->GetFirstDocPosition();
			while(posDoc!=NULL)
			{
				CDocument* pDoc=pTemplate->GetNextDoc(posDoc);
				pDoc->UpdateAllViews(NULL);
			}
		}
	}
}
