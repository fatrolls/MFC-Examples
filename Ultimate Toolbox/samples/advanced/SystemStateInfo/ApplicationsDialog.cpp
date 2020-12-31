// ApplicationsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "systemstateinfo.h"
#include "ApplicationsDialog.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define APPLICATIONREF_FLAG			0xffee0000
#define WINDOWREF_FLAG				0xffdd0000
#define PROCESSREF_FLAG				0xffcc0000

/////////////////////////////////////////////////////////////////////////////
// CApplicationsDialog dialog


CApplicationsDialog::CApplicationsDialog() : CPageDialog()
{
	//{{AFX_DATA_INIT(CApplicationsDialog)
	m_nExpandLevel = 0;
	m_nExpandType = 1;
	//}}AFX_DATA_INIT
	m_nCurrentIndex=-1;
}


void CApplicationsDialog::DoDataExchange(CDataExchange* pDX)
{
	CPageDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CApplicationsDialog)
	DDX_Control(pDX, IDC_SPIN_EXPANDLEVEL, m_spinExpandLevel);
	DDX_Control(pDX, IDC_EDIT_EXPANDLEVEL, m_editExpandLevel);
	DDX_Control(pDX, IDC_TREE_APPLICATIONS, m_tree);
	DDX_Text(pDX, IDC_EDIT_EXPANDLEVEL, m_nExpandLevel);
	DDX_Radio(pDX, IDC_RADIO_EXPANDLEVEL, m_nExpandType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CApplicationsDialog, CPageDialog)
	//{{AFX_MSG_MAP(CApplicationsDialog)
	ON_BN_CLICKED(IDC_RADIO_EXPANDALL, OnRadioExpandall)
	ON_BN_CLICKED(IDC_RADIO_EXPANDLEVEL, OnRadioExpandlevel)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_APPLICATIONS, OnDblclkTreeServices)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_APPLICATIONS, OnRclickTreeApplications)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_APP_SWITCHTO, OnAppWndSwitchTo)
	ON_COMMAND(IDM_APP_BRINGTOFRONT, OnAppWndBringToFront)
	ON_COMMAND(IDM_APP_MINIMIZE, OnAppWndMinimize)
	ON_COMMAND(IDM_APP_MAXIMIZE, OnAppWndMaximize)
	ON_COMMAND(IDM_APP_RESTORE, OnAppWndRestore)
	ON_COMMAND(IDM_APP_CLOSE, OnAppWndClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CApplicationsDialog message handlers
void CApplicationsDialog::OnInitDialog() 
{
	CPageDialog::OnInitDialog();

	// TODO: Add your specialized creation code here

	m_ilTree.Create(::GetSystemMetrics(SM_CXSMICON),
		::GetSystemMetrics(SM_CYSMICON),ILC_COLOR8|ILC_MASK,0,0);
	m_tree.SetImageList(&m_ilTree,TVSIL_NORMAL);

	LV_COLUMN lvc={ sizeof(lvc) };
	lvc.fmt=LVCFMT_LEFT;
	lvc.cx=237;
	lvc.pszText=_T("Item");
	lvc.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT;
	m_tree.SetColumn(0,&lvc);
	m_tree.InsertColumn(1,_T("Value"),LVCFMT_LEFT,200,1);

	// set COXTreeCtrl styles
	m_tree.ModifyExStyle(0,TVOXS_PICKANYWHERE|TVOXS_ROWSEL);
	m_tree.ModifyStyle(0,TVS_SHOWSELALWAYS|TVS_HASBUTTONS|
		TVS_HASLINES|TVS_LINESATROOT);


	// spin control
	m_spinExpandLevel.SetRange(0,3);
	m_spinExpandLevel.SetPos(0);
	
	// layout manager 
	//
	m_LayoutManager.Attach(this);
	
	// tree control
	m_LayoutManager.TieChild(IDC_TREE_APPLICATIONS,OX_LMS_ANY,OX_LMT_SAME);
	//////////////////

	// radio buttons and expand level edit control
	m_LayoutManager.TieChild(IDC_RADIO_EXPANDALL,
		OX_LMS_LEFT|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_RADIO_EXPANDLEVEL,
		OX_LMS_LEFT|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_EDIT_EXPANDLEVEL,OX_LMS_LEFT,
		OX_LMT_OPPOSITE,IDC_RADIO_EXPANDLEVEL);
	m_LayoutManager.TieChild(IDC_EDIT_EXPANDLEVEL,OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_SPIN_EXPANDLEVEL,OX_LMS_LEFT,
		OX_LMT_OPPOSITE,IDC_EDIT_EXPANDLEVEL);
	m_LayoutManager.TieChild(IDC_SPIN_EXPANDLEVEL,OX_LMS_BOTTOM,OX_LMT_SAME);
	//////////////////

	//////////////////////////////////////

	PopulateTree();

	ShowControls();
}

void CApplicationsDialog::Refresh() 
{
	PopulateTree();
}

void CApplicationsDialog::PopulateTree()
{
	if(!UpdateData())
		return;

	CWaitCursor waitCursor;

	m_tree.SetRedraw(FALSE);
	// kill and close all threads
	CleanThreads();
	// remove all items
	m_tree.DeleteAllItems();
	COXTreeHeader* pHeader=(COXTreeHeader*)m_tree.GetDlgItem(0);
	ASSERT(pHeader);
	pHeader->SortColumn(-1,0);
	// clean up image list
	for(int nIndex=0; nIndex<m_ilTree.GetImageCount(); nIndex++)
		VERIFY(m_ilTree.Remove(0));

	// create fonts to customize tree items appearance
	LOGFONT lf;
	CFont fontRoot;
	CFont fontSubRoot;
	CFont* pFontRoot=GetFont();
	if(pFontRoot->GetLogFont(&lf))
	{
		lf.lfHeight=-14;
		UTBStr::tcsncpy(lf.lfFaceName, LF_FACESIZE,_T("Arial"),LF_FACESIZE);
		fontRoot.CreateFontIndirect(&lf);

		lf.lfHeight=-12;
		lf.lfWeight=FW_BOLD;
		UTBStr::tcsncpy(lf.lfFaceName,LF_FACESIZE,_T("Times New Roman"),LF_FACESIZE);
		fontSubRoot.CreateFontIndirect(&lf);
	}
	pFontRoot=((HFONT)fontRoot!=NULL) ? &fontRoot : NULL;
//	CFont* pFontSubRoot=((HFONT)fontSubRoot!=NULL) ? &fontSubRoot : NULL;

	CString sValue;
	HTREEITEM htiRoot=NULL;
	HTREEITEM htiSelectItem=NULL;
	HTREEITEM htiItem=NULL;

	COLORREF clrTopic=RGB(0,0,255);
	COLORREF clrValue=RGB(0,128,0);

	m_arrAppInfo.RemoveAll();
	if(::EnumWindows(&EnumMainWindows,(LPARAM)&m_arrAppInfo))
	{
		for(int nIndex=0; nIndex<m_arrAppInfo.GetSize(); nIndex++)
		{
			CWnd* pAppWnd=CWnd::FromHandle(m_arrAppInfo[nIndex].hMainWnd);
			if(pAppWnd!=NULL && ::IsWindow(pAppWnd->GetSafeHwnd()))
			{
				// main window text
				CString sWindowText;
				pAppWnd->GetWindowText(sWindowText);
				///////////////////

				// work out icon...
				int nIconIndex=-1;
				HICON hIcon=(HICON)(DWORD_PTR)::GetClassLongPtr(pAppWnd->m_hWnd,GCL_HICONSM);
				if(hIcon==NULL)
					hIcon=(HICON)(DWORD_PTR)::GetClassLongPtr(pAppWnd->m_hWnd,GCL_HICON);
				if(hIcon==NULL && m_arrAppInfo[nIndex].bGotRespond)
				{
					if(!::SendMessageTimeout(m_arrAppInfo[nIndex].hMainWnd,
						WM_GETICON,ICON_SMALL,0,SMTO_ABORTIFHUNG,
						1000,(LPDWORD)&hIcon) || hIcon==NULL)
					{
						::SendMessageTimeout(m_arrAppInfo[nIndex].hMainWnd,
							WM_GETICON,ICON_BIG,0,SMTO_ABORTIFHUNG,
							1000,(LPDWORD)&hIcon);
					}
				}
				if(hIcon!=NULL)
					// add icon
					nIconIndex=m_ilTree.Add(hIcon);
				///////////////////

				htiRoot=InsertItem(sWindowText,NULL,nIconIndex,
					pFontRoot,clrTopic);
				VERIFY(m_tree.SetSubItem(htiRoot,1,OX_SUBITEM_TEXT|
					OX_SUBITEM_COLOR,(m_arrAppInfo[nIndex].bGotRespond ? 
					_T("Running") : _T("Not reponding")),0,NULL,clrValue));
				VERIFY(m_tree.SetItemData(htiRoot,APPLICATIONREF_FLAG+nIndex));
				if(htiSelectItem==NULL)
					htiSelectItem=htiRoot;
				///////////////////

				// Executable
				if(m_process.GetProcessImageFileName(
					m_arrAppInfo[nIndex].dwProcessID,sValue))
				{
					htiItem=InsertItem(_T("Executable"),htiRoot);
					VERIFY(m_tree.SetSubItem(htiItem,1,
						OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
						sValue,0,NULL,clrValue));
					VERIFY(m_tree.
						SetItemDrawEllipsis(htiItem,DT_PATH_ELLIPSIS,1));
				}
				///////////////////

				// Process ID
				htiItem=InsertItem(_T("Process ID"),htiRoot);
				sValue.Format(_T("0x%x"),m_arrAppInfo[nIndex].dwProcessID);
				VERIFY(m_tree.SetSubItem(htiItem,1,
					OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
				VERIFY(m_tree.SetItemData(htiItem,PROCESSREF_FLAG+nIndex));
				///////////////////

				// Main Window
				htiItem=InsertItem(_T("Main window handle"),htiRoot);
				sValue.Format(_T("0x%x"),m_arrAppInfo[nIndex].hMainWnd);
				VERIFY(m_tree.SetSubItem(htiItem,1,
					OX_SUBITEM_TEXT|OX_SUBITEM_COLOR,
					sValue,0,NULL,clrValue));
				VERIFY(m_tree.SetItemData(htiItem,WINDOWREF_FLAG+nIndex));
				///////////////////

			}
		}
	}

	ExpandTree((m_nExpandType==0 ? m_nExpandLevel : -1));

	m_tree.SetFocus();
	m_tree.SelectItem(htiSelectItem);

	m_tree.SetRedraw(TRUE);
}


void CApplicationsDialog::ExpandTree(int nExpandLevel/*=-1*/,
									 HTREEITEM htiParent/*=NULL*/)
{
	if(nExpandLevel==0)
		return;

	if(htiParent==NULL)
	{
		htiParent=m_tree.GetRootItem();
		ASSERT(htiParent!=NULL);
	}

	HTREEITEM hti=m_tree.GetNextItem(htiParent,TVGN_CHILD);
	while(hti!=NULL)
	{
		m_tree.Expand(hti,TVE_EXPAND);

		COXTreeItem* xti=m_tree.GetXItem(hti);
		ASSERT(xti!=NULL);
		if(xti->ItemHasChildren())
			ExpandTree((nExpandLevel==-1 ? -1 : nExpandLevel-1),hti);

		hti=m_tree.GetNextItem(hti,TVGN_NEXT);
	}
}

HTREEITEM CApplicationsDialog::InsertItem(CString sItem, 
										  HTREEITEM htiParent/*=NULL*/, 
										  int nImage/*=-1*/, 
										  CFont* pFont/*=NULL*/, 
										  COLORREF clr/*=CLR_NONE*/)
{
	HTREEITEM hti=m_tree.InsertItem(sItem,htiParent);
	ASSERT(hti!=NULL);

	// associate new font
	if(pFont!=NULL)
		VERIFY(m_tree.SetItemFont(hti,pFont));
	// and new color
	if(clr!=CLR_NONE)
		VERIFY(m_tree.SetItemColor(hti,clr));

	m_tree.SetItemImage(hti,nImage,nImage);

	return hti;
}

void CApplicationsDialog::ShowControls()
{
	if(UpdateData())
	{
		CWnd* pDlgItem=GetDlgItem(IDC_EDIT_EXPANDLEVEL);
		ASSERT(pDlgItem!=NULL);
		pDlgItem->EnableWindow((m_nExpandType==0));
		pDlgItem=GetDlgItem(IDC_SPIN_EXPANDLEVEL);
		ASSERT(pDlgItem!=NULL);
		pDlgItem->EnableWindow((m_nExpandType==0));
	}
}

void CApplicationsDialog::OnRadioExpandall() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CApplicationsDialog::OnRadioExpandlevel() 
{
	// TODO: Add your control notification handler code here
	
	ShowControls();
}

void CApplicationsDialog::OnDblclkTreeServices(NMHDR* pNMHDR, 
											   LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UNREFERENCED_PARAMETER(pNMHDR);

	CPoint point;
	if(::GetCursorPos(&point))
	{
		m_tree.ScreenToClient(&point);
		UINT nFlags;
		int nItem=m_tree.HitTest(point,&nFlags);
		if(nItem!=-1)
		{
			HTREEITEM hti=m_tree.GetItemFromIndex(nItem);
			ASSERT(hti!=NULL);
			if(m_tree.GetItemIndent(hti)<point.x && 
				(nFlags&TVHT_ONITEM)==TVHT_ONITEM)
			{
				DWORD dwData=m_tree.GetItemData(hti);
				if((dwData&WINDOWREF_FLAG)==WINDOWREF_FLAG)
				{
					int nIndex=dwData&0x0000ffff;
					ASSERT(nIndex>=0 && nIndex<m_arrAppInfo.GetSize());
					if(m_arrAppInfo[nIndex].bGotRespond)
					{
						m_nCurrentIndex=nIndex;
						PostMessage(WM_COMMAND,IDM_APP_SWITCHTO);
					}
				}
			}
		}
	}

	*pResult = 0;
}


void CApplicationsDialog::OnRclickTreeApplications(NMHDR* pNMHDR, 
												   LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UNREFERENCED_PARAMETER(pNMHDR);
	
	CPoint point;
	if(::GetCursorPos(&point))
	{
		m_tree.ScreenToClient(&point);
		UINT nFlags;
		int nItem=m_tree.HitTest(point,&nFlags);
		if(nItem!=-1)
		{
			HTREEITEM hti=m_tree.GetItemFromIndex(nItem);
			ASSERT(hti!=NULL);
			if(m_tree.GetItemIndent(hti)<point.x && 
				(nFlags&TVHT_ONITEM)==TVHT_ONITEM)
			{
				DWORD dwData=m_tree.GetItemData(hti);
//				if((dwData&WINDOWREF_FLAG)==WINDOWREF_FLAG || 
//					(dwData&APPLICATIONREF_FLAG)==APPLICATIONREF_FLAG)
				{
					int nIndex=dwData&0x0000ffff;
					ASSERT(nIndex>=0 && nIndex<m_arrAppInfo.GetSize());
					m_nCurrentIndex=nIndex;

					CMenu popMenu;
					VERIFY(popMenu.LoadMenu(IDR_APPLICATION_POPUPMENU));

					MENUITEMINFO itemInfo={ sizeof(MENUITEMINFO) };
					itemInfo.fMask=MIIM_STATE;
					if(m_arrAppInfo[nIndex].bGotRespond)
					{
						if(m_arrAppInfo[nIndex].dwProcessID!=m_process.GetProcessID())
						{
							// set default item
							itemInfo.fState=MFS_DEFAULT;
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_SWITCHTO,FALSE,&itemInfo);
						}
						else
						{
							// disable items
							itemInfo.fState=MFS_DISABLED;
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_SWITCHTO,FALSE,&itemInfo);
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_BRINGTOFRONT,FALSE,&itemInfo);
						}

						DWORD dwStyle=::GetWindowLong(
							m_arrAppInfo[m_nCurrentIndex].hMainWnd,GWL_STYLE);
						BOOL bSysMenu=(dwStyle&WS_SYSMENU)!=0;
						BOOL bMaximizeBtn=bSysMenu & 
							((dwStyle&WS_MAXIMIZEBOX)!=0);
						BOOL bCanMaximize=bMaximizeBtn & 
							((dwStyle&WS_MAXIMIZE)==0);
						BOOL bMinimizeBtn=bSysMenu & 
							((dwStyle&WS_MINIMIZEBOX)!=0);
						BOOL bCanMinimize=bMinimizeBtn & 
							((dwStyle&WS_MINIMIZE)==0);

						itemInfo.fState=MFS_DISABLED;
						if(!bCanMaximize)
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_MAXIMIZE,FALSE,&itemInfo);
						if(!bCanMinimize)
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_MINIMIZE,FALSE,&itemInfo);
						if((bCanMaximize && bCanMinimize) ||
							(!bMaximizeBtn && bCanMinimize) || !bSysMenu)
							::SetMenuItemInfo(popMenu.m_hMenu,
								IDM_APP_RESTORE,FALSE,&itemInfo);
					}
					else
					{
						// disable items
						itemInfo.fState=MFS_DISABLED;
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_SWITCHTO,FALSE,&itemInfo);
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_BRINGTOFRONT,FALSE,&itemInfo);
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_MINIMIZE,FALSE,&itemInfo);
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_MAXIMIZE,FALSE,&itemInfo);
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_RESTORE,FALSE,&itemInfo);
					}
	
					if(m_arrAppInfo[nIndex].dwProcessID==m_process.GetProcessID())
					{
						// disable items
						itemInfo.fState=MFS_DISABLED;
						::SetMenuItemInfo(popMenu.m_hMenu,
							IDM_APP_CLOSE,FALSE,&itemInfo);
					}
					// show menu
					m_tree.ClientToScreen(&point);
					popMenu.GetSubMenu(0)->
						TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,
						point.x, point.y,this);
				}
			}
		}
	}

	*pResult = 0;
}

void CApplicationsDialog::OnAppWndSwitchTo()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].dwProcessID!=m_process.GetProcessID());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].bGotRespond);
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		!m_arrAppInfo[m_nCurrentIndex].bGotRespond ||
		m_arrAppInfo[m_nCurrentIndex].dwProcessID==m_process.GetProcessID())
		return;

	::SetForegroundWindow(m_arrAppInfo[m_nCurrentIndex].hMainWnd);
	if((::GetWindowLong(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
		GWL_STYLE)&WS_MINIMIZE)==WS_MINIMIZE)
	{
		::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			WM_SYSCOMMAND,SC_RESTORE,
			(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
	}
}

void CApplicationsDialog::OnAppWndBringToFront()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].dwProcessID!=m_process.GetProcessID());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].bGotRespond);
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		!m_arrAppInfo[m_nCurrentIndex].bGotRespond ||
		m_arrAppInfo[m_nCurrentIndex].dwProcessID==m_process.GetProcessID())
		return;

	if(::GetWindowLong(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
		GWL_STYLE)&WS_MINIMIZE)
	{
		OnAppWndRestore();
		AfxGetMainWnd()->SetForegroundWindow();
	}
	else
	{
		::SetWindowPos(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			AfxGetMainWnd()->GetSafeHwnd(),0,0,0,0,
			SWP_SHOWWINDOW|SWP_ASYNCWINDOWPOS|SWP_NOACTIVATE|
			SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	}
}

void CApplicationsDialog::OnAppWndMinimize()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].bGotRespond);
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		!m_arrAppInfo[m_nCurrentIndex].bGotRespond)
		return;

	::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
		WM_SYSCOMMAND,SC_MINIMIZE,
		(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
}

void CApplicationsDialog::OnAppWndMaximize()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].bGotRespond);
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		!m_arrAppInfo[m_nCurrentIndex].bGotRespond)
		return;

	if(::GetWindowLong(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
		GWL_STYLE)&WS_MINIMIZE)
	{
		::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			WM_SYSCOMMAND,SC_MAXIMIZE,
			(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
		AfxGetMainWnd()->SetForegroundWindow();
	}
	else
	{
		::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			WM_SYSCOMMAND,SC_MAXIMIZE,
			(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
	}
}

void CApplicationsDialog::OnAppWndRestore()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].bGotRespond);
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		!m_arrAppInfo[m_nCurrentIndex].bGotRespond)
		return;

	if(::GetWindowLong(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
		GWL_STYLE)&WS_MINIMIZE)
	{
		::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			WM_SYSCOMMAND,SC_RESTORE,
			(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
		AfxGetMainWnd()->SetForegroundWindow();
	}
	else
	{
		::SendMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,
			WM_SYSCOMMAND,SC_RESTORE,
			(LPARAM)m_arrAppInfo[m_nCurrentIndex].hMainWnd);
	}
}

void CApplicationsDialog::OnAppWndClose()
{
	ASSERT(m_nCurrentIndex>=0 && m_nCurrentIndex<m_arrAppInfo.GetSize());
	ASSERT(m_arrAppInfo[m_nCurrentIndex].dwProcessID!=m_process.GetProcessID());
	if(m_nCurrentIndex<0 || m_nCurrentIndex>=m_arrAppInfo.GetSize() ||
		m_arrAppInfo[m_nCurrentIndex].dwProcessID==m_process.GetProcessID())
		return;

	if(m_arrAppInfo[m_nCurrentIndex].bGotRespond)
	{
		::PostMessage(m_arrAppInfo[m_nCurrentIndex].hMainWnd,WM_QUIT,0,0);
		Refresh();
		return;
	}

	HANDLE hProcess=::OpenProcess(PROCESS_TERMINATE,FALSE,
		m_arrAppInfo[m_nCurrentIndex].dwProcessID);
	if(hProcess!=NULL)
	{
		::TerminateProcess(hProcess,FALSE);
		Refresh();
	}

}

void CApplicationsDialog::CleanThreads()
{
	// kill and close all threads
	for(int nIndex=0; nIndex<m_arrThreads.GetSize(); nIndex++)
	{
		HANDLE hThread=m_arrThreads[nIndex];
		DWORD dwExitCode;
		if(::GetExitCodeThread(hThread,&dwExitCode) && dwExitCode==STILL_ACTIVE)
			::TerminateThread(hThread,TRUE);
		::CloseHandle(hThread);
	}
	m_arrThreads.RemoveAll();
}



BOOL CALLBACK CApplicationsDialog::EnumMainWindows(HWND hWnd, LPARAM lParam)
{
	ASSERT(lParam!=NULL);
	CAppInfoArray* parrAppInfo=(CAppInfoArray*)lParam;

	// Window should be not-owned (to exclude dialogs) 
	if(::GetWindow(hWnd,GW_OWNER)==NULL &&
		(::GetWindowLong(hWnd,GWL_EXSTYLE)&WS_EX_TOOLWINDOW)==0 &&
		(::GetWindowLong(hWnd,GWL_STYLE)&WS_VISIBLE)==WS_VISIBLE)
	{
		APPLICATIONINFO appInfo;
		::GetWindowThreadProcessId(hWnd,&appInfo.dwProcessID);
		appInfo.hMainWnd=hWnd;

		// application status
		DWORD dwResult;
		appInfo.bGotRespond=PtrToInt(::SendMessageTimeout(hWnd,WM_NULL,0,0,
			SMTO_ABORTIFHUNG,5000,&dwResult));
		///////////////////

		parrAppInfo->Add(appInfo);
	}
	return TRUE;
}


