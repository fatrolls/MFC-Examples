// dockchil.cpp : implementation file
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:28  $

#include "stdafx.h"
#include "docktest.h"
#include "dockchil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockChildWnd

IMPLEMENT_DYNCREATE(CDockChildWnd, CMDIChildWnd)

CDockChildWnd::CDockChildWnd()
{
}

CDockChildWnd::~CDockChildWnd()
{
}


BEGIN_MESSAGE_MAP(CDockChildWnd, CMRCMDIChildWndSizeDock)
	//{{AFX_MSG_MAP(CDockChildWnd)
	ON_WM_CREATE()
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


int CDockChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMRCMDIChildWndSizeDock::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndToolBar.SetBitmapIds(allbuttons, sizeof(allbuttons)/sizeof(UINT));

	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadBitmap(IDR_MAINFRAME) ||
		!m_wndToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	} 

	EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	
	return 0;
}
