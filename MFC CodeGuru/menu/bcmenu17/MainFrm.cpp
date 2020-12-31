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
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
	ON_COMMAND(ID_DEFAULT, OnDefault)
	ON_UPDATE_COMMAND_UI(ID_DEFAULT, OnUpdateDefault)
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_HOMEPAGE, OnHomepage)
	ON_COMMAND(ID_WINDOW_TILE, OnWindowTile)
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
  static UINT toolbars[]={
    IDR_MAINFRAME,
    IDR_TOOLBAR
  };

  // Load the menu from the resources
  m_menu.LoadMenu(IDR_MYMENUTYPE);

  // Use ModifyODMenu to add a bitmap to a menu options.The first parameter
  // is the menu option text string.If it's NULL, keep the current text
  // string.The second option is the ID of the menu option, or the menu
  // option text (use this for adding bitmaps to popup options) to change.
  // The third option is the resource ID of the bitmap.This can also be a
  // toolbar ID in which case the class searches the toolbar for the
  // appropriate bitmap.Only Bitmap and Toolbar resources are supported.
  m_menu.ModifyODMenu(NULL,ID_WINDOW_TILE,IDB_WINDOW_TILE);
  m_menu.ModifyODMenu(NULL,"&Rocscience on the Web",IDB_NET);

  // Another method for adding bitmaps to menu options is through the
  // LoadToolbars member function.This method allows you to add all
  // the bitmaps in a toolbar object to menu options (if they exist).
  // The first function parameter is an array of toolbar id's.
  // The second is the number of toolbar id's. There is also a
  // function called LoadToolbar that just takes an id.
  m_menu.LoadToolbars(toolbars,2);

  return(m_menu.Detach());
}

HMENU CMainFrame::NewDefaultMenu()
{
  m_default.LoadMenu(IDR_MAINFRAME);
  m_default.LoadToolbar(IDR_MAINFRAME);
  return(m_default.Detach());
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(Undocheck);
}


void CMainFrame::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
  BOOL setflag=FALSE;
  if(lpMeasureItemStruct->CtlType==ODT_MENU){
    if(IsMenu((HMENU)lpMeasureItemStruct->itemID)){
      CMenu* cmenu=CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
      if(m_menu.IsMenu(cmenu)||m_default.IsMenu(cmenu)){
        m_menu.MeasureItem(lpMeasureItemStruct);
        setflag=TRUE;
      }
    }
  }
	if(!setflag)CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}


LRESULT CMainFrame::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
  LRESULT lresult;
  if(m_menu.IsMenu(pMenu)||m_default.IsMenu(pMenu))
    lresult=BCMenu::FindKeyboardShortcut(nChar, nFlags, pMenu);
	else
    lresult=CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
  return(lresult);
}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnEditCut() 
{
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

void CMainFrame::OnDefault() 
{
  CMenu *menu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);
  if(::GetMenuDefaultItem(menu->m_hMenu,MF_BYPOSITION,0)==3)
    ::SetMenuDefaultItem(menu->m_hMenu,-1,MF_BYPOSITION);
  else
    ::SetMenuDefaultItem(menu->m_hMenu,3,MF_BYPOSITION);
}

void CMainFrame::OnUpdateDefault(CCmdUI* pCmdUI) 
{
  CMenu *menu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);
  if(::GetMenuDefaultItem(menu->m_hMenu,MF_BYPOSITION,0)==3){
    pCmdUI->SetRadio(TRUE);
    pCmdUI->SetText("Default ON");
  }
  else{
    pCmdUI->SetRadio(FALSE);
    pCmdUI->SetText("Default");
  }
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	
  if(!bSysMenu){
    if(m_menu.IsMenu(pPopupMenu)||m_default.IsMenu(pPopupMenu))
      BCMenu::UpdateMenu(pPopupMenu);
  }
}

void CMainFrame::OnHomepage() 
{
  ShellExecute(::GetDesktopWindow(),"open",
    "http://www.rocscience.com/~corkum/BCMenu.html",NULL,NULL,
    SW_MAXIMIZE);
}

void CMainFrame::OnWindowTile() 
{
	// TODO: Add your command handler code here
	
}
