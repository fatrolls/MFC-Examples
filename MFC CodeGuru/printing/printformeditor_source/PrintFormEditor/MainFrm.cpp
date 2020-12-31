// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PrintFormEditor.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, SECWorkbook)

BEGIN_MESSAGE_MAP(CMainFrame, SECWorkbook)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(IDC_PROPERTY, OnProperty)
	ON_UPDATE_COMMAND_UI(IDC_PROPERTY, OnUpdateProperty)
	ON_COMMAND(ID_SHOW_PAGEBAR, OnShowPagebar)
	ON_UPDATE_COMMAND_UI(ID_SHOW_PAGEBAR, OnUpdateShowPagebar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


static UINT BASED_CODE fileButtons[] =
{
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
	ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
};

static UINT BASED_CODE toolButtons[] =
{
	IDC_TOOL_ARROW,
	ID_SEPARATOR,
	IDC_TOOL_STATIC,
	IDC_TOOL_EDIT,
	IDC_TOOL_BORDER,
	IDC_TOOL_RADIO,
	IDC_TOOL_CHECK,
	IDC_TOOL_IMAGE,
	IDC_TOOL_LINE,
	IDC_TOOL_RECT,
	IDC_TOOL_VLINE,
	IDC_TOOL_HLINE,
	ID_SEPARATOR,
	IDC_TOOL_SOTTOREPORT,
};


static UINT BASED_CODE alignButtons[] =
{
	ID_ALIGN_LEFT,
	ID_ALIGN_RIGHT,
	ID_ALIGN_TOP,
	ID_ALIGN_BOTTOM,
	ID_SEPARATOR,
	ID_SIZE_VERT,
	ID_SIZE_HORZ,
	ID_SIZE_ALL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
//	Cooltoolbar initialization
	m_pControlBarManager = new SECToolBarManager(this);
	GetManager()->m_pToolBarClass = RUNTIME_CLASS(SECExtBar);

	m_pMenuBar           = new SECMDIMenuBar;
	m_pMenuBar->m_cyTopBorder = m_pMenuBar->m_cyBottomBorder = 1;
	EnableBmpMenus();


	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
// OT Coolbar cleanup
	if (m_pControlBarManager) delete m_pControlBarManager;
	if (m_pMenuBar) delete m_pMenuBar;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (SECWorkbook::OnCreate(lpCreateStruct) == -1) return -1;

	if (!m_wndStatusBar.Create(this) || !m_wndStatusBar.SetIndicators(indicators,  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	SECToolBarManager* pToolBarMgr= GetManager();
	VERIFY(pToolBarMgr->LoadToolBarResource(MAKEINTRESOURCE(IDR_MAINFRAME), NULL));
	VERIFY(pToolBarMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_TOOL_BAR), NULL));
	VERIFY(pToolBarMgr->AddToolBarResource(MAKEINTRESOURCE(IDR_ALIGN_BAR), NULL));

	pToolBarMgr->SetMenuInfo(2, IDR_MAINFRAME, IDR_PRINTFTYPE);

	pToolBarMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR,_T("Principale"),
							NUMELEMENTS(fileButtons),fileButtons,
							CBRS_ALIGN_ANY,AFX_IDW_DOCKBAR_TOP);
	pToolBarMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 5, _T("Strumenti"),
								NUMELEMENTS(toolButtons),toolButtons,
								CBRS_ALIGN_ANY,AFX_IDW_DOCKBAR_TOP,AFX_IDW_TOOLBAR);

	pToolBarMgr->DefineDefaultToolBar(AFX_IDW_TOOLBAR + 6, _T("Align"),
								NUMELEMENTS(alignButtons),alignButtons,
								CBRS_ALIGN_ANY,AFX_IDW_DOCKBAR_TOP,AFX_IDW_TOOLBAR+5);



	pToolBarMgr->EnableCoolLook(TRUE);
	EnableDocking(CBRS_ALIGN_ANY);
	pToolBarMgr->SetDefaultDockState();

	if (!paperBar.Create(this, _T("Macro"), CBRS_BOTTOM | WS_VISIBLE | CBRS_SIZE_DYNAMIC, CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_COOL, 1010)) 
	{
		TRACE(_T("Failed to create paperBar bar\n"));
		return -1;      
	} 
	paperBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBarEx(&paperBar, AFX_IDW_DOCKBAR_BOTTOM, 0, 0, (float)0.24, 80);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	return SECWorkbook::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	SECWorkbook::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	SECWorkbook::Dump(dc);
}

#endif //_DEBUG




void CMainFrame::DoTrackMenu(const int menuId, const int iPopPos, CWnd * pSendTo, CPoint pt)
{
	CMenu popup;
	popup.LoadMenu(menuId);
	CMenu * pops = popup.GetSubMenu(iPopPos);
	pops->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, pt.x, pt.y, pSendTo);
}



/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
CPropDlg * GfxGetProp()
{
	CMainFrame * mf = (CMainFrame *) AfxGetMainWnd();
	if (!mf->propDlg.GetSafeHwnd()) mf->propDlg.Create(CPropDlg::IDD, mf);
	if (!mf->propDlg.IsWindowVisible()) mf->propDlg.ShowWindow(SW_SHOW);
	return &(mf->propDlg);
}

bool GfxIsProp()
{
	CMainFrame * mf = (CMainFrame *) AfxGetMainWnd();
	return mf->propDlg.GetSafeHwnd() && mf->propDlg.IsWindowVisible();
}

CGfxProperty * GfxGetProp2()
{
	CMainFrame * mf = (CMainFrame *) AfxGetMainWnd();
	if (!mf->gfxProp.GetSafeHwnd()) mf->gfxProp.Create(CGfxProperty::IDD, mf);
	if (!mf->gfxProp.IsWindowVisible()) mf->gfxProp.ShowWindow(SW_SHOWNOACTIVATE);
	return &(mf->gfxProp);
}

bool GfxIsProp2()
{
	CMainFrame * mf = (CMainFrame *) AfxGetMainWnd();
	return mf->gfxProp.GetSafeHwnd() && mf->gfxProp.IsWindowVisible();
}

CPapersBar * GfxGetPaperList()
{
	CMainFrame * mf = (CMainFrame *) AfxGetMainWnd();
	ASSERT(mf);
	return &(mf->paperBar);
}

void CMainFrame::OnProperty() 
{
//	if (!propDlg.GetSafeHwnd()) propDlg.Create(CPropDlg::IDD, this);
//	if (!propDlg.IsWindowVisible()) propDlg.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateProperty(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(propDlg.GetSafeHwnd() && propDlg.IsWindowVisible());
}

void CMainFrame::OnShowPagebar() 
{
	ShowControlBar(&paperBar, !paperBar.IsVisible(), TRUE);
}

void CMainFrame::OnUpdateShowPagebar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(paperBar.IsVisible());
}
