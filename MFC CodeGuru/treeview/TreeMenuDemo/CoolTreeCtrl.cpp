//************************************************************************
//
// Filename	:	CoolTreeCtrl.cpp
// Author	:	Rainer Pfitzner	
// Date		:	11.10.1997
// Purpose	:	Wrapper-Classes for New IE4.0 commctrl.dll: 
//			
// Copyright (c) 1998 raip systems. All rights reserved
//
//************************************************************************

#include "StdAfx.h"
#include "CoolTreeCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CCoolTreeCtrl, CWnd)

BEGIN_MESSAGE_MAP(CCoolTreeCtrl, CWnd)
	//{{AFX_MSG_MAP(CCoolTreeCtrl)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CCoolTreeCtrl::CCoolTreeCtrl()
{
}

CCoolTreeCtrl::~CCoolTreeCtrl()
{
	DestroyWindow();
}

//////////////////////////
// Create the CCoolTreeCtrl
//
BOOL CCoolTreeCtrl::Create(DWORD dwStyle, CRect rc, CWnd* pParentWnd, UINT nID)
{
	ASSERT_VALID(pParentWnd);   // must have a parent
	CWnd* pWnd = this;

	// Initialize cool common controls
	static BOOL bInit = FALSE;
	if (!bInit) {
		INITCOMMONCONTROLSEX sex;
		sex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		sex.dwICC = ICC_TREEVIEW_CLASSES;
		InitCommonControlsEx(&sex);
		bInit = TRUE;
	}

	// Create the ListCtrl using style and parent.
	pWnd->CreateEx(NULL, WC_TREEVIEW, NULL, dwStyle, rc, 
					pParentWnd, nID);

	ASSERT(pWnd != NULL);

	return TRUE;
}


CString CCoolTreeCtrl::GetItemText(HTREEITEM hItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_TEXT;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		item.pszText = str.GetBufferSetLength(nLen);
		item.cchTextMax = nLen;
		::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item);
		nRes = lstrlen(item.pszText);
	} while (nRes == nLen-1);
	str.ReleaseBuffer();
	return str;
}

BOOL CCoolTreeCtrl::GetItemImage(HTREEITEM hItem, int& nImage, int& nSelectedImage) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	BOOL bRes = (BOOL)::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item);
	if (bRes)
	{
		nImage = item.iImage;
		nSelectedImage = item.iSelectedImage;
	}
	return bRes;
}

UINT CCoolTreeCtrl::GetItemState(HTREEITEM hItem, UINT nStateMask) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_STATE;
	item.stateMask = nStateMask;
	item.state = 0;
	VERIFY(::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item));
	return item.state;
}

DWORD CCoolTreeCtrl::GetItemData(HTREEITEM hItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_PARAM;
	VERIFY(::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item));
	return (DWORD)item.lParam;
}

BOOL CCoolTreeCtrl::ItemHasChildren(HTREEITEM hItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = TVIF_CHILDREN;
	::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item);
	return item.cChildren;
}

BOOL CCoolTreeCtrl::SetItem(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, int nImage,
	int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam)
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.hItem = hItem;
	item.mask = nMask;
	item.pszText = (LPTSTR) lpszItem;
	item.iImage = nImage;
	item.iSelectedImage = nSelectedImage;
	item.state = nState;
	item.stateMask = nStateMask;
	item.lParam = lParam;
	return (BOOL)::SendMessage(m_hWnd, TVM_SETITEM, 0, (LPARAM)&item);
}

BOOL CCoolTreeCtrl::SetItemText(HTREEITEM hItem, LPCTSTR lpszText)
{
  ASSERT(::IsWindow(m_hWnd));
  TVITEM item;
  item.pszText = (LPTSTR) lpszText;
  return (BOOL) ::SendMessage(m_hWnd, TVM_SETITEM, 0, (LPARAM)&item);
}

HTREEITEM CCoolTreeCtrl::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage,
	int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
	HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	ASSERT(::IsWindow(m_hWnd));
	TVINSERTSTRUCT tvis;
	tvis.hParent = hParent;
	tvis.hInsertAfter = hInsertAfter;
	tvis.item.mask = nMask;
	tvis.item.pszText = (LPTSTR) lpszItem;
	tvis.item.iImage = nImage;
	tvis.item.iSelectedImage = nSelectedImage;
	tvis.item.state = nState;
	tvis.item.stateMask = nStateMask;
	tvis.item.lParam = lParam;
	return (HTREEITEM)::SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)&tvis);
}

HTREEITEM CCoolTreeCtrl::HitTest(CPoint pt, UINT* pFlags) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVHITTESTINFO hti;
	hti.pt = pt;
	HTREEITEM h = (HTREEITEM)::SendMessage(m_hWnd, TVM_HITTEST, 0,
		(LPARAM)&hti);
	if (pFlags != NULL)
		*pFlags = hti.flags;
	return h;
}

void CCoolTreeCtrl::OnDestroy()
{
	RemoveImageList(LVSIL_NORMAL);
	RemoveImageList(LVSIL_STATE);

	CWnd::OnDestroy();
}

void CCoolTreeCtrl::RemoveImageList(int nImageList)
{
	HIMAGELIST h = (HIMAGELIST)SendMessage(TVM_GETIMAGELIST,
		(WPARAM)nImageList);
	if (CImageList::FromHandlePermanent(h) != NULL)
		SendMessage(TVM_SETIMAGELIST, (WPARAM)nImageList, NULL);
}


CImageList* CCoolTreeCtrl::CreateDragImage(HTREEITEM hItem)
{
	ASSERT(::IsWindow(m_hWnd));

	HIMAGELIST hImageList = (HIMAGELIST)::SendMessage(m_hWnd,
		TVM_CREATEDRAGIMAGE, 0, (LPARAM)hItem);
	if (hImageList == NULL)
		return NULL;

	CImageList* pImageList = new CImageList;
	VERIFY(pImageList->Attach(hImageList));
	return pImageList;
}




