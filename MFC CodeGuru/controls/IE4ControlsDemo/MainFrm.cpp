// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "IE4ControlsDemo.h"

#include "MainFrm.h"

#include "ToolBarCtrlEx.h"
#include "ReBarCtrl.h"

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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
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
	CImageList il;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndReBar.Create(this))
	{
		TRACE0("Failed to create rebar\n");
		return -1;		// fail to create
	}

	if (!m_wndToolBar.CreateEx(this) || !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT | TBSTYLE_TRANSPARENT);

	// create the combo box
	if (!m_wndCombo.Create(CBS_DROPDOWN | WS_CHILD, CRect(0, 0, 200, 200), this, AFX_IDW_TOOLBAR + 1))
	{
		TRACE0("Failed to create combobox\n");
		return -1;		// fail to create
	}

	// fill the combo box with something
	il.Create(IDB_IMAGES, 16, 0, RGB(255, 0, 255));
	m_wndCombo.SetImageList(&il);
	il.Detach();

	COMBOBOXEXITEM cbItem;

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem = 0;
	cbItem.pszText = "Item 1";
	cbItem.iImage = cbItem.iSelectedImage = 0;
	cbItem.iIndent = 0;
	m_wndCombo.InsertItem(&cbItem);

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem = 1;
	cbItem.pszText = "Sub-item 1";
	cbItem.iImage = cbItem.iSelectedImage = 1;
	cbItem.iIndent = 1;
	m_wndCombo.InsertItem(&cbItem);

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem = 2;
	cbItem.pszText = "Sub-sub-item 1";
	cbItem.iImage = cbItem.iSelectedImage = 2;
	cbItem.iIndent = 2;
	m_wndCombo.InsertItem(&cbItem);

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem = 3;
	cbItem.pszText = "Sub-item 2";
	cbItem.iImage = cbItem.iSelectedImage = 1;
	cbItem.iIndent = 1;
	m_wndCombo.InsertItem(&cbItem);

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem = 4;
	cbItem.pszText = "Item 2";
	cbItem.iImage = cbItem.iSelectedImage = 0;
	cbItem.iIndent = 0;
	m_wndCombo.InsertItem(&cbItem);

	cbItem.mask = CBEIF_TEXT | CBEIF_IMAGE | CBEIF_SELECTEDIMAGE | CBEIF_INDENT;
	cbItem.iItem =5;
	cbItem.pszText = "Sub-item 1";
	cbItem.iImage = cbItem.iSelectedImage = 1;
	cbItem.iIndent = 1;
	m_wndCombo.InsertItem(&cbItem);

	m_wndCombo.SetCurSel(0);

	// create the date picker
	if (!m_wndDatePick.Create(WS_CHILD | WS_VISIBLE | DTS_SHORTDATEFORMAT, CRect(0, 0, 200, 25), this, AFX_IDW_TOOLBAR + 2))
	{
		TRACE0("Failed to create date picker\n");
		return -1;		// fail to create
	}

	// add the toolbar, combo box and date picker to the rebar
	m_wndReBar.AddBar(&m_wndToolBar);
	m_wndReBar.AddBar(&m_wndCombo, "Combo Box");
	m_wndReBar.AddBar(&m_wndDatePick, "Date Pick");

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// setup min/max sizes and ideal sizes for pieces of the rebar
	REBARBANDINFO rbbi;

	CRect rcToolBar;

	m_wndToolBar.GetWindowRect(&rcToolBar);

	rbbi.cbSize = sizeof(rbbi);
	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_SIZE;
	rbbi.cxMinChild = rcToolBar.Width();
	rbbi.cyMinChild = rcToolBar.Height();
	rbbi.cx = rbbi.cxIdeal = rcToolBar.Width() * 10;
	m_wndReBar.GetReBarCtrl().SetBandInfo(0, &rbbi);
	rbbi.cxMinChild = 0;

	CRect rcCombo;

	rbbi.fMask = RBBIM_CHILDSIZE | RBBIM_IDEALSIZE;
	m_wndCombo.GetEditCtrl()->GetWindowRect(&rcCombo);
	rbbi.cyMinChild = rcCombo.Height() + 10;
	rbbi.cxIdeal = 200;
	m_wndReBar.GetReBarCtrl().SetBandInfo(1, &rbbi);
	m_wndReBar.GetReBarCtrl().SetBandInfo(2, &rbbi);

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

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
