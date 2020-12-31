// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "HyperbarDemo.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, COXHyperFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, COXHyperFrameWnd)
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
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar2.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CImageList	imageList;
	CBitmap bitmap;

	imageList.Create(90, 90, ILC_COLOR24|ILC_MASK, 8, 1);

	bitmap.LoadBitmap(IDB_BOOK);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_CODE);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_DISK);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_DOC);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_FOLDERS);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_PC);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_PLUG);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_POCKETPC);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_USER);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_TOOLS);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();
	bitmap.LoadBitmap(IDB_GLOBE);
	imageList.Add(&bitmap, RGB(255,0,255));
	bitmap.Detach();

	m_wndToolBar2.SendMessage(TB_SETIMAGELIST, 0, (LPARAM)imageList.m_hImageList);
	imageList.Detach();


	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar2.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBar2);

	if (m_config.Create(IDD_CONFIGDLG, this))
	{
		m_config.ShowWindow(SW_SHOW);
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

