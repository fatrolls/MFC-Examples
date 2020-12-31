// dockchil.cpp : implementation file
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "docktest.h"
#include "mysizeba.h"

#include "dockchil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockChildWnd

IMPLEMENT_DYNCREATE(CDockChildWnd, COXMDIChildWndSizeDock)

CDockChildWnd::CDockChildWnd()
{
	nListBarID=2222;
}

CDockChildWnd::~CDockChildWnd()
{
}


BEGIN_MESSAGE_MAP(CDockChildWnd, COXMDIChildWndSizeDock)
	//{{AFX_MSG_MAP(CDockChildWnd)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDockChildWnd message handlers
static UINT BASED_CODE buttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
		ID_SEPARATOR,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
		ID_SEPARATOR,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE allbuttons[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	ID_FILE_NEW,
	ID_FILE_OPEN,
	ID_FILE_SAVE,
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
	ID_FILE_PRINT,
	ID_APP_ABOUT,
};

static UINT BASED_CODE indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

int CDockChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COXMDIChildWndSizeDock::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndChildStatusBar.Create(this) ||
		!m_wndChildStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
		{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
		}

	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	} 

	m_wndToolBar.SetBitmapIds(allbuttons, sizeof(allbuttons)/sizeof(UINT));

	EnableDocking(CBRS_ALIGN_ANY);

	VERIFY(CreateListBar(&m_SizeListBar));
	VERIFY(CreateListBar(&m_SizeListBarAdd1));
	VERIFY(CreateListBar(&m_SizeListBarAdd2));
	VERIFY(CreateListBar(&m_SizeListBarAdd3));
	VERIFY(CreateListBar(&m_SizeListBarAdd4));

	LoadSizeBarState(_T("ChildDocktestBars"));

	return 0;
}



BOOL CDockChildWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	//cs.style&=~WS_SYSMENU;

	return COXMDIChildWndSizeDock::PreCreateWindow(cs);
}

BOOL CDockChildWnd::CreateListBar(CMyListBoxBar* pBar) 
{
	// This is a list box that is added dynamically. You can have almost any 
	// number of these...
	nListBarID++;
	if (!pBar->Create(this,_T("ListBar"),nListBarID))
	{
		TRACE(_T("Failed to create list box bar\n"));
		return FALSE;      
	} 
			
	pBar->SetBarStyle(pBar->GetBarStyle() |	
		SZBARF_STDMOUSECLICKS/* | SZBARF_ALLOW_MDI_FLOAT*/);		

	pBar->EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(pBar, AFX_IDW_DOCKBAR_BOTTOM);

	return TRUE;
}

void CDockChildWnd::ActivateFrame(int nCmdShow) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	COXMDIChildWndSizeDock::ActivateFrame(nCmdShow);

//	LoadSizeBarState(_T("ChildDocktestBars"));

}

void CDockChildWnd::OnDestroy() 
{
	SaveSizeBarState(_T("ChildDocktestBars"));

	COXMDIChildWndSizeDock::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
