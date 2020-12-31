// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FileExplorer.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "FileExplorerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int ID_MAXHISTORYITEMDISPLAYED=20;
const int ID_BACKWARD_BASE=18000;
const int ID_FORWARD_BASE=19000;

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, OnDropDown)
	ON_COMMAND(ID_VIEW_TYPE, OnViewType)
	ON_COMMAND(ID_VIEW_UP, OnViewUp)
	ON_COMMAND(ID_VIEW_BACKWARD, OnViewBackward)
	ON_COMMAND(ID_VIEW_FORWARD, OnViewForward)
	ON_UPDATE_COMMAND_UI(ID_VIEW_UP, OnUpdateViewUp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_BACKWARD, OnUpdateViewBackward)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FORWARD, OnUpdateViewForward)
	ON_COMMAND_RANGE(ID_BACKWARD_BASE, ID_BACKWARD_BASE+ID_MAXHISTORYITEMDISPLAYED, OnBackwardItem)
	ON_COMMAND_RANGE(ID_FORWARD_BASE, ID_FORWARD_BASE+ID_MAXHISTORYITEMDISPLAYED, OnForwardItem)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

static UINT buttons[] =
{
	ID_VIEW_BACKWARD,
	ID_VIEW_FORWARD,
	ID_VIEW_UP,
	ID_SEPARATOR,   
	ID_EDIT_CUT,
	ID_EDIT_COPY,
	ID_EDIT_PASTE,
	ID_EDIT_DELETE,
	ID_SEPARATOR,   
	ID_VIEW_PROPERTY,
	ID_VIEW_TYPE,
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
	
	if (!m_wndToolBar.Create(this,WS_CHILD|WS_VISIBLE|CBRS_TOP|CBRS_TOOLTIPS|
		CBRS_FLYBY|CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.SetButtons(buttons,sizeof(buttons)/sizeof(buttons[1])) ||
		m_wndToolBar.GetToolBarCtrl().
		AddBitmap(sizeof(buttons)/sizeof(buttons[1]),IDB_TB_FILE)==-1)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	/////////////
	// COXCoolToolBar specific functions
	m_wndToolBar.IniSizes(CSize(24,22));
	m_wndToolBar.SetButtonTextFromID(COXCoolToolBar::TTID_TOOLTIP);
	m_wndToolBar.SetMaxTextRows(1);
	m_wndToolBar.SetButtonsMinMaxWidth(0,80);
	m_wndToolBar.SetHotImageList(m_wndToolBar.AddImageList(IDB_TB_FILE_HOT,24,
		RGB(192,192,192),ILC_COLOR8|ILC_MASK));
//	m_wndToolBar.SetDisabledImageList(m_wndToolBar.AddImageList(IDB_TB_FILE_DISABLED,24,
//		RGB(255,0,255),ILC_COLOR8|ILC_MASK));
	m_wndToolBar.UpdateSizes();

	m_wndToolBar.SetButtonStyle(0,m_wndToolBar.GetButtonStyle(0)|TBSTYLE_DROPDOWN);
	m_wndToolBar.SetButtonStyle(1,m_wndToolBar.GetButtonStyle(1)|TBSTYLE_DROPDOWN);
	m_wndToolBar.SetButtonStyle(10,m_wndToolBar.GetButtonStyle(10)|TBSTYLE_DROPDOWN);
	m_wndToolBar.SetDropDownArrow(TRUE);
	////////////

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
								CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CLeftView),CSize(0,0),pContext) ||
		!m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CFileExplorerView),
		CSize(0,0),pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_wndSplitter.SetColumnInfo(0,200,0);
	m_wndSplitter.SetActivePane(0,0);

	return TRUE;
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

CFileExplorerView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CFileExplorerView* pView = DYNAMIC_DOWNCAST(CFileExplorerView, pWnd);
	return pView;
}

CLeftView* CMainFrame::GetLeftPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 0);
	CLeftView* pView = DYNAMIC_DOWNCAST(CLeftView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	CFileExplorerView* pView = GetRightPane(); 

	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->m_filesList.GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.
	CFileExplorerView* pView = GetRightPane();

	// if the right-hand pane has been created and is a CFileExplorerView,
	// process the menu commands...
	if (pView != NULL)
	{
		DWORD dwStyle=(DWORD)-1;

		switch (nCommandID)
		{
		case ID_VIEW_LINEUP:
			{
				// ask the list control to snap to grid
				pView->m_filesList.Arrange(LVA_SNAPTOGRID);
			}
			break;

		// other commands change the style on the list control
		case ID_VIEW_DETAILS:
			dwStyle = LVS_REPORT;
			break;

		case ID_VIEW_SMALLICON:
			dwStyle = LVS_SMALLICON;
			break;

		case ID_VIEW_LARGEICON:
			dwStyle = LVS_ICON;
			break;

		case ID_VIEW_LIST:
			dwStyle = LVS_LIST;
			break;
		}

		// change the style; window will repaint automatically
		if (dwStyle != -1)
			pView->m_filesList.ModifyStyle(LVS_TYPEMASK, dwStyle);
	}
}


void CMainFrame::OnDropDown(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	// this function handles the dropdown menus from the toolbar
	NMTOOLBAR* pNMToolBar = (NMTOOLBAR*)pNotifyStruct;
	CRect rect;

	// translate the current toolbar item rectangle into screen coordinates
	// so that we'll know where to pop up the menu
	m_wndToolBar.GetItemRect(m_wndToolBar.CommandToIndex(pNMToolBar->iItem), &rect);
	rect.top = rect.bottom;
	::ClientToScreen(pNMToolBar->hdr.hwndFrom, &rect.TopLeft());
	switch(pNMToolBar->iItem)
	{
	case ID_VIEW_BACKWARD:
		{
			CWnd* pWnd=m_wndSplitter.GetPane(0,0);
			ASSERT(pWnd!=NULL);
			CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

			ASSERT(pTreeView->m_arrHistory.GetSize()>1 && 
				pTreeView->m_nCurrentItemInHistory!=0);

			CMenu menuPopup;
			VERIFY(menuPopup.CreatePopupMenu());
			int nMenuItemCount=0;
			int nHistoryItemIndex=pTreeView->m_nCurrentItemInHistory-1;
			while(nMenuItemCount<ID_MAXHISTORYITEMDISPLAYED &&
				nHistoryItemIndex>=0)
			{
				LPITEMIDLIST lpFullIDL=pTreeView->m_arrHistory.GetAt(nHistoryItemIndex);
				if(lpFullIDL==NULL)
				{
					menuPopup.AppendMenu(MF_STRING,ID_BACKWARD_BASE+nMenuItemCount,
						_T("Desktop"));
					nHistoryItemIndex--;
					nMenuItemCount++;
				}
				else
				{
					HTREEITEM hItem=pTreeView->m_folderTree.FindFolder(lpFullIDL);
					if(hItem==NULL)
					{
						pTreeView->m_arrHistory.RemoveAt(nHistoryItemIndex);
						pTreeView->m_nCurrentItemInHistory--;
						nHistoryItemIndex--;
					}
					else
					{
						CString sText=pTreeView->m_folderTree.GetItemText(hItem);
						menuPopup.AppendMenu(MF_STRING,ID_BACKWARD_BASE+nMenuItemCount,
							sText);
						nHistoryItemIndex--;
						nMenuItemCount++;
					}
				}

			}
			menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,rect.left, 
				rect.top+1,AfxGetMainWnd());
			break;
		}

	case ID_VIEW_FORWARD:
		{
			CWnd* pWnd=m_wndSplitter.GetPane(0,0);
			ASSERT(pWnd!=NULL);
			CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

			ASSERT((pTreeView->m_arrHistory.GetSize()-1)>
				pTreeView->m_nCurrentItemInHistory);

			CMenu menuPopup;
			VERIFY(menuPopup.CreatePopupMenu());
			int nMenuItemCount=0;
			int nHistoryItemIndex=pTreeView->m_nCurrentItemInHistory+1;
			while(nMenuItemCount<ID_MAXHISTORYITEMDISPLAYED &&
				nHistoryItemIndex<pTreeView->m_arrHistory.GetSize())
			{
				LPITEMIDLIST lpFullIDL=pTreeView->m_arrHistory.GetAt(nHistoryItemIndex);
				if(lpFullIDL==NULL)
				{
					menuPopup.AppendMenu(MF_STRING,ID_FORWARD_BASE+nMenuItemCount,
						_T("Desktop"));
					nHistoryItemIndex++;
					nMenuItemCount++;
				}
				else
				{
					HTREEITEM hItem=pTreeView->m_folderTree.FindFolder(lpFullIDL);
					if(hItem==NULL)
					{
						pTreeView->m_arrHistory.RemoveAt(nHistoryItemIndex);
					}
					else
					{
						CString sText=pTreeView->m_folderTree.GetItemText(hItem);
						menuPopup.AppendMenu(MF_STRING,ID_FORWARD_BASE+nMenuItemCount,
							sText);
						nHistoryItemIndex++;
						nMenuItemCount++;
					}
				}

			}
			menuPopup.TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,rect.left, 
				rect.top+1,AfxGetMainWnd());
			break;
		}
	
	case ID_VIEW_TYPE:
		{
			CMenu menu;
			CMenu* pPopup;
			menu.LoadMenu(IDR_VIEWTYPE);
			pPopup=menu.GetSubMenu(0);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,rect.left, 
				rect.top+1,AfxGetMainWnd());
			break;
		}
	}
	*pResult=TBDDRET_DEFAULT; 
}


void CMainFrame::OnBackwardItem(UINT nCommandID)
{
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	ASSERT(pTreeView->m_arrHistory.GetSize()>1 && pTreeView->m_nCurrentItemInHistory!=0);
	int nItemIndex=pTreeView->m_nCurrentItemInHistory-1-nCommandID+ID_BACKWARD_BASE;
	ASSERT(nItemIndex>=0);
	LPITEMIDLIST lpFullIDLPrev=pTreeView->m_arrHistory.GetAt(nItemIndex);
	HTREEITEM hPrevItem=NULL;
	if(lpFullIDLPrev!=NULL)
	{
		hPrevItem=pTreeView->m_folderTree.FindFolder(lpFullIDLPrev);
	}
	else
	{
		hPrevItem=pTreeView->m_folderTree.GetRootItem();
	}
	if(hPrevItem!=NULL)
	{
		pTreeView->m_nCurrentItemInHistory=nItemIndex;
		pTreeView->m_folderTree.SelectItem(hPrevItem);
	}
}


void CMainFrame::OnForwardItem(UINT nCommandID)
{
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	ASSERT((pTreeView->m_arrHistory.GetSize()-1)>pTreeView->m_nCurrentItemInHistory);
	int nItemIndex=pTreeView->m_nCurrentItemInHistory+1+nCommandID-ID_FORWARD_BASE;
	ASSERT(nItemIndex<pTreeView->m_arrHistory.GetSize());
	LPITEMIDLIST lpFullIDLNext=pTreeView->m_arrHistory.GetAt(nItemIndex);
	HTREEITEM hNextItem=NULL;
	if(lpFullIDLNext!=NULL)
	{
		hNextItem=pTreeView->m_folderTree.FindFolder(lpFullIDLNext);
	}
	else
	{
		hNextItem=pTreeView->m_folderTree.GetRootItem();
	}
	if(hNextItem!=NULL)
	{
		pTreeView->m_nCurrentItemInHistory=nItemIndex;
		pTreeView->m_folderTree.SelectItem(hNextItem);
	}
}


void CMainFrame::OnViewType() 
{
	// TODO: Add your command handler code here
	OnViewStyle(ID_VIEW_LARGEICON);
}

void CMainFrame::OnViewUp() 
{
	// TODO: Add your command handler code here
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);
	HTREEITEM hItem=pTreeView->m_folderTree.GetSelectedItem();
	ASSERT(hItem!=NULL);
	HTREEITEM hParentItem=pTreeView->m_folderTree.GetParentItem(hItem);
	ASSERT(hParentItem!=NULL);
	pTreeView->m_folderTree.SelectItem(hParentItem);
}

void CMainFrame::OnViewBackward() 
{
	// TODO: Add your command handler code here
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	ASSERT(pTreeView->m_arrHistory.GetSize()>1 && pTreeView->m_nCurrentItemInHistory!=0);
	LPITEMIDLIST lpFullIDLPrev=pTreeView->m_arrHistory.
		GetAt(pTreeView->m_nCurrentItemInHistory-1);
	HTREEITEM hPrevItem=NULL;
	if(lpFullIDLPrev!=NULL)
	{
		hPrevItem=pTreeView->m_folderTree.FindFolder(lpFullIDLPrev);
	}
	else
	{
		hPrevItem=pTreeView->m_folderTree.GetRootItem();
	}
	if(hPrevItem!=NULL)
	{
		pTreeView->m_nCurrentItemInHistory--;
		pTreeView->m_folderTree.SelectItem(hPrevItem);
	}
}

void CMainFrame::OnViewForward() 
{
	// TODO: Add your command handler code here
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	ASSERT((pTreeView->m_arrHistory.GetSize()-1)>pTreeView->m_nCurrentItemInHistory);
	LPITEMIDLIST lpFullIDLNext=pTreeView->m_arrHistory.
		GetAt(pTreeView->m_nCurrentItemInHistory+1);
	HTREEITEM hNextItem=NULL;
	if(lpFullIDLNext!=NULL)
	{
		hNextItem=pTreeView->m_folderTree.FindFolder(lpFullIDLNext);
	}
	else
	{
		hNextItem=pTreeView->m_folderTree.GetRootItem();
	}
	if(hNextItem!=NULL)
	{
		pTreeView->m_nCurrentItemInHistory++;
		pTreeView->m_folderTree.SelectItem(hNextItem);
	}
}

void CMainFrame::OnUpdateViewForward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	pCmdUI->Enable((pTreeView->m_arrHistory.GetSize()-1)>
		pTreeView->m_nCurrentItemInHistory);
}

void CMainFrame::OnUpdateViewBackward(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);

	pCmdUI->Enable(pTreeView->m_arrHistory.GetSize()>1 && 
		pTreeView->m_nCurrentItemInHistory!=0);
}

void CMainFrame::OnUpdateViewUp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL bEnabled=FALSE;
	CWnd* pWnd=m_wndSplitter.GetPane(0,0);
	ASSERT(pWnd!=NULL);
	CLeftView* pTreeView=DYNAMIC_DOWNCAST(CLeftView,pWnd);
	HTREEITEM hItem=pTreeView->m_folderTree.GetSelectedItem();
	if(hItem!=NULL)
	{
		HTREEITEM hParentItem=pTreeView->m_folderTree.GetParentItem(hItem);
		if(hParentItem!=NULL)
			bEnabled=TRUE;
	}

	pCmdUI->Enable(bEnabled);
}

