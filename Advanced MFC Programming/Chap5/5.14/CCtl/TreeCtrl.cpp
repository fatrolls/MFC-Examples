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
	m_pilDrag=NULL;
	m_hTreeDragSrc=NULL;
	m_hTreeDragTgt=NULL;
	m_bIsDragging=FALSE;
}

MCTreeCtrl::~MCTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(MCTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(MCTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MCTreeCtrl::OnBegindrag(NMHDR *pNMHDR, LRESULT *pResult) 
{
	CPoint pt;
	UINT nFlags;

	NM_TREEVIEW *pNMTreeView=(NM_TREEVIEW *)pNMHDR;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);
	ASSERT(m_bIsDragging == FALSE);
	m_bIsDragging=TRUE;
	m_hTreeDragSrc=HitTest(pt, &nFlags);
	m_hTreeDragTgt=NULL;

	ASSERT(m_pilDrag == NULL);
	m_pilDrag=CreateDragImage(m_hTreeDragSrc);
	if(m_pilDrag != NULL)
	{
		m_pilDrag->DragShowNolock(TRUE);
		m_pilDrag->SetDragCursorImage(0, CPoint(0, 0));
		m_pilDrag->BeginDrag(0, CPoint(0,0));
		m_pilDrag->DragMove(pt);
		m_pilDrag->DragEnter(this, pt);
		SetCapture();
		*pResult=0;
	}
	else
	{
		m_bIsDragging=FALSE;
		*pResult=1;
	}
}

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
		pNMTreeView->itemNew. iImage == 2
	)
	{
		SetItemImage(pNMTreeView->itemNew.hItem, 3, 3);
	}
	if
	(
		pNMTreeView->action == TVE_COLLAPSE &&
		pNMTreeView->itemNew. iImage == 3
	)
	{
		SetItemImage(pNMTreeView->itemNew.hItem, 2, 2);
	}
	*pResult = 0;
}

void MCTreeCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	HTREEITEM			hitem;
	UINT				flags;
	
	if(m_bIsDragging)
	{
		ASSERT(m_pilDrag != NULL);
		m_pilDrag->DragMove(point);
		if((hitem=HitTest(point, &flags)) != NULL)
		{
			m_pilDrag->DragLeave(this);
			SelectDropTarget(hitem);
			m_hTreeDragTgt=hitem;
			m_pilDrag->DragEnter(this, point);
		}
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}

void MCTreeCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bIsDragging)
	{
		ASSERT(m_pilDrag != NULL);
		m_pilDrag->DragLeave(this);
		m_pilDrag->EndDrag();
		delete m_pilDrag;
		m_pilDrag=NULL;

		if
		(
			m_hTreeDragSrc != m_hTreeDragTgt &&
			GetChildItem(m_hTreeDragTgt) != NULL &&
			!IsDescendent(m_hTreeDragTgt, m_hTreeDragSrc)
		)
		{
			CopyItemTo(m_hTreeDragTgt, m_hTreeDragSrc);
//			DeleteItem(m_hTreeDragTgt);
		}
		else ::MessageBeep(0);

		::ReleaseCapture();
		m_bIsDragging=FALSE;
		SelectDropTarget(NULL);
	}	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

BOOL MCTreeCtrl::IsDescendent(HTREEITEM hTreeDescendent, HTREEITEM hTreeParent)
{
	while(TRUE)
	{
		if(hTreeDescendent == hTreeParent || hTreeDescendent == NULL)break;
		hTreeDescendent=GetParentItem(hTreeDescendent);
	}
	return hTreeDescendent != NULL;
}

void MCTreeCtrl::CopyItemTo(HTREEITEM hTreeDragTgt, HTREEITEM hTreeDragSrc)
{
	TV_INSERTSTRUCT tvInsertStruct;
	char szBuf[256];
	HTREEITEM hTreeItem;

	tvInsertStruct.item.mask=
	(
		TVIF_CHILDREN | 
		TVIF_HANDLE | 
		TVIF_IMAGE | 
		TVIF_SELECTEDIMAGE | 
		TVIF_TEXT |
		TVIF_STATE
	);
	tvInsertStruct.item.pszText=szBuf;
	tvInsertStruct.item.cchTextMax=sizeof(szBuf);
	tvInsertStruct.item.hItem=hTreeDragSrc;
	GetItem(&tvInsertStruct.item);
	tvInsertStruct.hParent=hTreeDragTgt;
	tvInsertStruct.hInsertAfter=TVI_LAST;
	hTreeItem=InsertItem(&tvInsertStruct);
	if(tvInsertStruct.item.cChildren != 0)
	{
		hTreeDragSrc=GetChildItem(hTreeDragSrc);
		while(TRUE)
		{
			if(hTreeDragSrc == NULL)break;
			CopyItemTo(hTreeItem, hTreeDragSrc);
			hTreeDragSrc=GetNextItem(hTreeDragSrc, TVGN_NEXT);
		}
	}
}