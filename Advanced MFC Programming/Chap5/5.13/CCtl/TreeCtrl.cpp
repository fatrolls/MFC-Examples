#include "stdafx.h"
#include "CCtl.h"
#include "TreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

MCTreeCtrl::MCTreeCtrl():CTreeCtrl()
{
}

MCTreeCtrl::~MCTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(MCTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(MCTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MCTreeCtrl::OnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult) 
{
	TV_DISPINFO *pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	
	if(pTVDispInfo->item.pszText != NULL)
	{
		SetItemText
		(
			pTVDispInfo->item.hItem,
			pTVDispInfo->item.pszText
		);
	}
	*pResult=0;
}

void MCTreeCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT *pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if
	(
		pNMTreeView->action == TVE_EXPAND &&
		pNMTreeView->itemNew.iImage == 2
	)
	{
		SetItemImage(pNMTreeView->itemNew.hItem, 3, 3);
	}
	if
	(
		pNMTreeView->action == TVE_COLLAPSE &&
		pNMTreeView->itemNew.iImage == 3
	)
	{
		SetItemImage(pNMTreeView->itemNew.hItem, 2, 2);
	}
	*pResult = 0;
}
