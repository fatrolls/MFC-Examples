// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "mymenu.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int Undocheck=0;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateWindowNew)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
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
	zoomcheck=TRUE;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
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

  CMenu *pSystemMenu=GetSystemMenu(FALSE);
  pSystemMenu->AppendMenu(MF_SEPARATOR);
  pSystemMenu->AppendMenu(MF_STRING,IDM_SYSMENU_ABOUT,"&About MyApp");

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CMDIFrameWnd::PreCreateWindow(cs);
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

void CMainFrame::OnZoom() 
{
	zoomcheck=!zoomcheck;
}

void CMainFrame::OnEditUndo() 
{
Undocheck=!Undocheck;	
}

HMENU CMainFrame::NewMenu()
{
  // Load the bitmaps representing the check marks. The first bitmap represents
  // the unselected state and the second the selected state.
  // This call must be done before LoadMenu.
  m_menubar.LoadCheckmarkBitmap(IDB_CHECKU,IDB_CHECKS);

  // Load the menu from the resources
  m_menubar.LoadMenu(IDR_MYMENUTYPE);

  // Set bitmap background color, this color becomes transparent
  // I've set it to the default so this call really isn't necessary.
  // This RGB setting represents the light gray background windows likes to use.
  m_menubar.SetBitmapBackground(RGB(192,192,192));

  // Use ModifyODMenu to add a bitmap to a menu options.The first parameter
  // is the menu option text string.If it's NULL, keep the current text
  // string.The second option is the ID of the menu option, or the menu
  // option text (use this for adding bitmaps to popup options) to change.
  // The third option is the resource ID of the bitmap.This can also be a
  // toolbar ID in which case the class searches the toolbar for the
  // appropriate bitmap.Only Bitmap and Toolbar resources are supported.
  m_menubar.ModifyODMenu(NULL,ID_WINDOW_NEW,IDB_WINDOW_NEW);
  m_menubar.ModifyODMenu(NULL,ID_WINDOW_NEW2,IDB_WINDOW_NEW);
  m_menubar.ModifyODMenu(NULL,ID_WINDOW_TILE,IDB_WINDOW_TILE);
  m_menubar.ModifyODMenu(NULL,"&Popup",IDB_NET);
  m_menubar.ModifyODMenu(NULL,ID_ZOOM,IDB_ZOOM);

  // Another method for adding bitmaps to menu options is through the
  // AddFromToolBar member function.This method allows you to add all
  // the bitmaps in a toolbar object to menu options (if they exist).
  // The first function parameter is the pointer to a toolbar object
  // while the second parameter is the toolbar id.
  m_menubar.AddFromToolBar(&m_wndToolBar, IDR_MAINFRAME);

  return(m_menubar.Detach());
}

HMENU CMainFrame::NewDefaultMenu()
{

  m_defaultmenubar.LoadCheckmarkBitmap(IDB_CHECKU,IDB_CHECKS);
  m_defaultmenubar.LoadMenu(IDR_MAINFRAME);
  m_defaultmenubar.ModifyODMenu(NULL,ID_FILE_NEW,IDR_MAINFRAME);
  m_defaultmenubar.ModifyODMenu(NULL,ID_FILE_OPEN,IDR_MAINFRAME);
  m_defaultmenubar.ModifyODMenu(NULL,ID_APP_ABOUT,IDR_MAINFRAME);
  return(m_defaultmenubar.Detach());

}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(Undocheck);
}


void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  if(lpMeasureItemStruct->CtlType==ODT_MENU)m_menubar.MeasureItem(lpMeasureItemStruct);
	else CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{

  LRESULT lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
  if(lresult)return(lresult);
	else return CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}
void CMainFrame::OnUpdateWindowNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
  CMDIFrameWnd::OnUpdateMDIWindowCmd(pCmdUI);
	BCMenu::UpdateMenu(pCmdUI->m_pMenu);
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditCut() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditPaste() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateZoom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(zoomcheck);
}
