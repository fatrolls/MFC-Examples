// TreeFilesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DIBManager.h"
#include "TreeFilesDlg.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "DIBManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeFilesDlg dialog


CTreeFilesDlg::CTreeFilesDlg(CWnd* pParent /*=NULL*/)
	: COXSizeDialogBar()
{
	UNREFERENCED_PARAMETER(pParent);
	//{{AFX_DATA_INIT(CTreeFilesDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// use imagelist to show TreeFilesDlg
	m_ilTypeFile.Create(IDB_IMAGELIST, 16, 0, RGB(255,0,255));
}


void CTreeFilesDlg::DoDataExchange(CDataExchange* pDX)
{
	COXSizeDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeFilesDlg)
	DDX_Control(pDX, IDC_TREE_FILES, m_TreeFiles);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTreeFilesDlg, COXSizeDialogBar)
	//{{AFX_MSG_MAP(CTreeFilesDlg)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_FILES, OnSelchangedTreeFiles)
	ON_NOTIFY(NM_CLICK, IDC_TREE_FILES, OnClickTreeFiles)
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeFilesDlg message handlers

BOOL CTreeFilesDlg::Create(CWnd* pParentWnd, UINT nIDTemplate,
						   UINT nStyle, UINT nID)
{
	if (!COXSizeDialogBar::Create(pParentWnd, MAKEINTRESOURCE(nIDTemplate), 
		nStyle, nID))
		return FALSE;

	UpdateData(FALSE);

	BOOL bSuccess=IniTreeFiles();
	if(!bSuccess)
	{
		AfxMessageBox(_T("Cannot create Tree Files Bar!"));
	}
	return bSuccess; 
}

BOOL CTreeFilesDlg::IniTreeFiles()
{
	// initialize info in TreeFilesDlg
	m_TreeFiles.SetImageList(&m_ilTypeFile,TVSIL_NORMAL);

	TV_ITEM item;
	TV_INSERTSTRUCT InsertStruct;

	// root - Bitmaps
	item.mask=TVIF_CHILDREN|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_STATE|TVIF_TEXT;
	item.cChildren=1;
	item.state=TVIS_BOLD|TVIS_EXPANDED;
	item.stateMask=TVIS_BOLD|TVIS_EXPANDED;
	item.pszText=_T("Opened Files");
	item.iImage=0;
	item.iSelectedImage=0;
	item.lParam=(DWORD)CDIBManagerDoc::TF_DIB;

	InsertStruct.hParent=NULL;
	InsertStruct.hInsertAfter=TVI_LAST;
	InsertStruct.item=item;

	if(m_TreeFiles.InsertItem(&InsertStruct)==NULL)
	{
		return FALSE;
	}

	return TRUE;
}

void CTreeFilesDlg::AddNewWindowToTree(CWnd* pWnd)
{
	ASSERT_VALID(pWnd);
	if(!pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return;

	if(FindWindowInTree(pWnd)!=NULL)
		return;

	CString sWindowText;
	pWnd->GetWindowText(sWindowText);

	TV_ITEM item;
	item.mask=TVIF_CHILDREN|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM|TVIF_TEXT;
	item.cChildren=0;
	item.pszText=(LPTSTR)(LPCTSTR)sWindowText;
	item.iImage=1;
	item.iSelectedImage=1;
	item.lParam=(DWORD)pWnd;

	TV_INSERTSTRUCT InsertStruct;
	InsertStruct.hParent=m_TreeFiles.GetRootItem();
	InsertStruct.hInsertAfter=TVI_SORT;
	InsertStruct.item=item;
	m_TreeFiles.InsertItem(&InsertStruct);

	m_TreeFiles.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_ERASE);
}

void CTreeFilesDlg::RemoveWindowFromTree(CWnd* pWnd)
{
	if(!pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return;

	HTREEITEM deleteItem=FindWindowInTree(pWnd);
	if(deleteItem!=NULL)
		m_TreeFiles.DeleteItem(deleteItem);

}

void CTreeFilesDlg::SetTextForWindowInTree(CWnd* pWnd, const CString& string)
{
	// rename the name of opened document
	if(!pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return;

	HTREEITEM setItem=FindWindowInTree(pWnd);
	if(setItem!=NULL)
	{
		m_TreeFiles.SetItemText(setItem,string);
		m_TreeFiles.SortChildren(m_TreeFiles.GetRootItem());
		m_TreeFiles.RedrawWindow(NULL,NULL,RDW_INVALIDATE | RDW_ERASE);
	}

}

void CTreeFilesDlg::SetActiveWindowInTree(CWnd* pWnd)
{
	if(!pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return;

	HTREEITEM setItem=FindWindowInTree(pWnd);
	if(setItem!=NULL)
	{
		HTREEITEM selectedItem=m_TreeFiles.GetSelectedItem();
		if(setItem!=selectedItem)
		{
			if(selectedItem!=NULL)
			{
				m_TreeFiles.SetItemState(selectedItem,TVIS_SELECTED,TVIS_SELECTED);
			}
			m_TreeFiles.EnsureVisible(setItem);
			m_TreeFiles.Select(setItem,TVGN_CARET);
		}
	}

}

HTREEITEM CTreeFilesDlg::FindWindowInTree(CWnd* pWnd)
{
	// find window with given pWnd
	HTREEITEM result=NULL;

	if(!pWnd->IsKindOf(RUNTIME_CLASS(CChildFrame)))
		return result;

	HTREEITEM childItem=m_TreeFiles.GetRootItem();
	while(childItem!=NULL)
	{
		DWORD itemData=m_TreeFiles.GetItemData(childItem);
		if(itemData==(DWORD)pWnd)
		{
			result=childItem;
			break;
		}
		childItem=m_TreeFiles.GetNextItem(childItem,TVGN_NEXTVISIBLE);
	}
	
	return result;
}


void CTreeFilesDlg::OnSelchangedTreeFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	// if we poke some element in TreeFilesDlg then 
	// activate corresponding window
	ActivateWindowInTree((DWORD)pNMTreeView->itemNew.lParam);

	*pResult = 0;
}


void CTreeFilesDlg::ActivateWindowInTree(DWORD itemData)
{
	if(itemData!=m_TreeFiles.GetItemData(m_TreeFiles.GetRootItem()))
	{
		CDIBManagerApp* pApp=(CDIBManagerApp*)AfxGetApp();
		CMainFrame* pMainFrame=(CMainFrame*)pApp->m_pMainWnd;

		pMainFrame->LockWindowUpdate();
		pMainFrame->MDIActivate((CWnd*)itemData);
		m_TreeFiles.SetActiveWindow();
		m_TreeFiles.SetFocus();
		pMainFrame->UnlockWindowUpdate();
	}
}
	

void CTreeFilesDlg::OnClickTreeFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UNREFERENCED_PARAMETER(pNMHDR);

	// if we poke some element in TreeFilesDlg then 
	// activate corresponding window
	HTREEITEM selectedItem=m_TreeFiles.GetSelectedItem();
	if(selectedItem!=NULL)
	{
		ActivateWindowInTree(m_TreeFiles.GetItemData(selectedItem));
	}

	*pResult = 0;
}

void CTreeFilesDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	COXSizeDialogBar::OnRButtonUp(nFlags, point);
}

BOOL CTreeFilesDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	cs.lpszClass = AfxRegisterWndClass(CS_DBLCLKS,NULL,NULL,NULL);
	ASSERT(cs.lpszClass);

	return COXSizeDialogBar::PreCreateWindow(cs);
}
