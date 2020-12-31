// WaitingTreeCtrl.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2000-2001 by Paolo Messina
// (http://www.geocities.com/ppescher - ppescher@yahoo.com)
//
// The contents of this file are subject to the Artistic License (the "License").
// You may not use this file except in compliance with the License. 
// You may obtain a copy of the License at:
// http://www.opensource.org/licenses/artistic-license.html
//
// If you find this code useful, credits would be nice!
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EXWaitingTreeCtrl.h"

#pragma warning(push)
#pragma warning(disable: 4201)
#include <mmsystem.h>
#pragma warning(pop)

#pragma comment(lib, "winmm.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EXWaitingTreeCtrl
IMPLEMENT_DYNAMIC(EXWaitingTreeCtrl, CTreeCtrl )

EXWaitingTreeCtrl::EXWaitingTreeCtrl()
{
	m_bDrawSnapshot = FALSE;

	m_sWaitMsg = _T("Loading...");
	m_bShowWaitMsg = FALSE;
	m_hIconMsg = NULL;	// default: blank icon
	m_nTimerDelay = 0;	// default: no timer

	m_hRedrawEvent = NULL;
	m_hTimerEvent = NULL;
	m_hThread = NULL;
}

EXWaitingTreeCtrl::~EXWaitingTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(EXWaitingTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(EXWaitingTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemExpanded)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EXWaitingTreeCtrl message handlers

void EXWaitingTreeCtrl::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (pNMTreeView->action & TVE_EXPAND)
		PreExpandItem(pNMTreeView->itemNew.hItem);

	*pResult = 0;
}

void EXWaitingTreeCtrl::OnItemExpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (pNMTreeView->action & TVE_EXPAND)
		ExpandItem(pNMTreeView->itemNew.hItem);
	else if (pNMTreeView->action & TVE_COLLAPSE)
	{
		if (WantsRefresh(pNMTreeView->itemNew.hItem))
		{
			// delete child items
			DeleteChildren(pNMTreeView->itemNew.hItem);
		}
	}

	*pResult = 0;
}

void EXWaitingTreeCtrl::PreAnimation(HTREEITEM hItemMsg)
{
	UNREFERENCED_PARAMETER(hItemMsg);
}

void EXWaitingTreeCtrl::PostAnimation()
{
}

void EXWaitingTreeCtrl::DoAnimation(BOOL bTimerEvent, int iMaxSteps, int iStep)
{
	UNREFERENCED_PARAMETER(bTimerEvent);
	UNREFERENCED_PARAMETER(iMaxSteps);
	UNREFERENCED_PARAMETER(iStep);
}

int EXWaitingTreeCtrl::GetPopulationCount(int *piMaxSubItems)
{
	if (piMaxSubItems != NULL)
		*piMaxSubItems = m_iItemCount;
	return m_iItemIndex;
}

void EXWaitingTreeCtrl::SetPopulationCount(int iMaxSubItems, int iFirstSubItem)
{
	m_iItemCount = iMaxSubItems;
	m_iItemIndex = iFirstSubItem;

	SetEvent(m_hRedrawEvent);
}

void EXWaitingTreeCtrl::UpdatePopulation(int iSubItems)
{
	m_iItemIndex = iSubItems;

	SetEvent(m_hRedrawEvent);
}

void EXWaitingTreeCtrl::IncreasePopulation(int iSubItemsToAdd)
{
	m_iItemIndex += iSubItemsToAdd;

	SetEvent(m_hRedrawEvent);
}

void EXWaitingTreeCtrl::SetAnimationDelay(UINT nMilliseconds)
{
	// if greater than zero, periodic DoAnimation() will be called
	m_nTimerDelay = nMilliseconds;
}

DWORD WINAPI EXWaitingTreeCtrl::AnimationThreadProc(LPVOID pThis)
{
	EXWaitingTreeCtrl* me = (EXWaitingTreeCtrl*)pThis;

	HANDLE events[2] = { me->m_hTimerEvent, me->m_hRedrawEvent };
	
	while (!me->m_bAbortAnimation)
	{
		DWORD wait = WaitForMultipleObjects(2, events, FALSE, INFINITE);
		
		if (me->m_bAbortAnimation || wait == WAIT_FAILED)
			break;

		if (wait == WAIT_OBJECT_0)	// timer event
			me->DoAnimation(TRUE, me->m_iItemCount, me->m_iItemIndex);
		else	// redraw event
			me->DoAnimation(FALSE, me->m_iItemCount, me->m_iItemIndex);
	}

	return 0;
}

void EXWaitingTreeCtrl::StartAnimation()
{
	// user-defined setup
	PreAnimation(m_hItemMsg);

	// animation can go
	m_bAbortAnimation = FALSE;
	// automatic reset events, signaled
	m_hTimerEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	m_hRedrawEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
	// start animation thread
	DWORD dwThreadID = 0;
	m_hThread = CreateThread(NULL, 0, AnimationThreadProc, this,
		THREAD_PRIORITY_HIGHEST, &dwThreadID);
	// setup timer, if specified
	if (m_nTimerDelay > 0)
		m_nTimerID = (UINT)timeSetEvent(m_nTimerDelay, 5, (LPTIMECALLBACK)m_hTimerEvent,
			0, TIME_PERIODIC | TIME_CALLBACK_EVENT_SET);
}

void EXWaitingTreeCtrl::StopAnimation()
{
	// stop and destroy timer
	timeKillEvent(m_nTimerID);
	// signal thread to terminate
	m_bAbortAnimation = TRUE;
	SetEvent(m_hRedrawEvent);	// make sure it can see the signal
	// wait thread termination
	WaitForSingleObject(m_hThread, INFINITE);
	// clean up
	CloseHandle(m_hTimerEvent);
	m_hTimerEvent = NULL;
	CloseHandle(m_hRedrawEvent);
	m_hRedrawEvent = NULL;
	CloseHandle(m_hThread);
	m_hThread = NULL;

	// user-defined cleanup
	PostAnimation();
}

void EXWaitingTreeCtrl::PopulateRoot()
{
	PreExpandItem(TVI_ROOT);
	ExpandItem(TVI_ROOT);
	// force update, don't scroll
	SetRedraw(FALSE);
	SCROLLINFO si;
	GetScrollInfo(SB_HORZ, &si);
	EnsureVisible(GetChildItem(TVI_ROOT));
	SetScrollInfo(SB_HORZ, &si, FALSE);
	SetRedraw();
}

void EXWaitingTreeCtrl::PreExpandItem(HTREEITEM hItem)
{
	if (!NeedsChildren(hItem))
	{
		if (WantsRefresh(hItem))
		{
			// delete child items before populating
			DeleteChildren(hItem);
		}
		else
		{
			// doesn't want new items
			m_hItemToPopulate = NULL;
			return;
		}
	}
	// if it wants new child items, go on
	m_hItemToPopulate = hItem;

	// fix redraw when expanded programatically
	UpdateWindow();
	// hide changes until it's expanded
	SetRedraw(FALSE);
	// add wait msg, to allow item expansion
	m_hItemMsg = InsertItem(m_sWaitMsg, m_hItemToPopulate);
	// zero progress
	m_iItemCount = 1;
	m_iItemIndex = 0;
}

void EXWaitingTreeCtrl::ExpandItem(HTREEITEM hItem)
{
	if (m_hItemToPopulate == NULL)
		return;	// just expand, doesn't want new items

	ASSERT(hItem == m_hItemToPopulate);	// should never fail!!!

	if (m_bShowWaitMsg)
	{
		// display wait msg now, make sure it's visible
		SetRedraw();
		EnsureVisible(m_hItemMsg);
		UpdateWindow();
	}
	// setup animation thread, call PreAnimation
	StartAnimation();
	// draw icon
	if (m_bShowWaitMsg)
		DrawUserIcon();
	// delay redraw after populating
	SetRedraw(FALSE);
	// take a snapshot of the background
	TakeSnapshot();
	// del temporary item (wait msg still shown)
	DeleteItem(m_hItemMsg);
	// fill in with sub items
	BOOL bCheckChildren = PopulateItem(hItem);
	// clean up animation thread, call PostAnimation
	StopAnimation();
	// change parent to reflect current children number
	if (hItem != TVI_ROOT)
	{
		TVITEM item;
		item.hItem = hItem;
		item.mask = TVIF_HANDLE | TVIF_CHILDREN;
		item.cChildren = NeedsChildren(hItem) ? 0 : 1;
		if (bCheckChildren)
			SetItem(&item);
		else if (item.cChildren == 0)
			// restore item's plus button if no children inserted
			SetItemState(hItem, 0, TVIS_EXPANDED);
	}
	// clean up snapshot
	DestroySnapshot();
	// redraw now
	SetRedraw(TRUE);
}

BOOL EXWaitingTreeCtrl::WantsRefresh(HTREEITEM hItem)
{
	UNREFERENCED_PARAMETER(hItem);

	// default implementation, no refresh
	return FALSE;
}

BOOL EXWaitingTreeCtrl::GetItemImageRect(HTREEITEM hItem, LPRECT pRect)
{
	if (GetImageList(TVSIL_NORMAL) == NULL)
		return FALSE;	// no images

	CRect rc;
	// get item rect
	if (!GetItemRect(hItem, &rc, TRUE))
		return FALSE;

	int cx = GetSystemMetrics(SM_CXSMICON);
	int cy = GetSystemMetrics(SM_CYSMICON);

	// move onto the icon space
	int margin = (rc.Height()-cy)/2;
	rc.OffsetRect(-cx-3 , margin);
	rc.right = rc.left + cx;	// make it square
	rc.bottom = rc.top + cy;	// make it square

	*pRect = rc;
	return TRUE;
}

void EXWaitingTreeCtrl::DrawUserIcon()
{
	// draw user defined icon

	CRect rcIcon;
	if (!GetItemImageRect(m_hItemMsg, &rcIcon))
		return;	// no image

	// create background brush with current bg color (take rgb part only)
	HBRUSH hBrush = CreateSolidBrush(GetBkColor() & 0x00FFFFFF);

	CClientDC dc(this);

	if (m_hIconMsg != NULL)
		DrawIconEx(dc.GetSafeHdc(), rcIcon.left, rcIcon.top, m_hIconMsg,
			rcIcon.Width(), rcIcon.Height(), 0, hBrush, DI_NORMAL);
	else
		FillRect(dc.GetSafeHdc(), &rcIcon, hBrush);

	DeleteObject(hBrush);
}

void EXWaitingTreeCtrl::SetWaitMessage(LPCTSTR pszText, HICON hIcon)
{
	m_sWaitMsg = pszText;
	m_hIconMsg = hIcon;
}

void EXWaitingTreeCtrl::RefreshSubItems(HTREEITEM hParent)
{
//	if (hParent != TVI_ROOT && !ItemHasChildren(hParent))
//		return;

	SetRedraw(FALSE);
	DeleteChildren(hParent);
	if (hParent == TVI_ROOT)
		PopulateRoot();
	else
	{
		PreExpandItem(hParent);
		ExpandItem(hParent);
	}
	SetRedraw(TRUE);
}

inline BOOL EXWaitingTreeCtrl::NeedsChildren(HTREEITEM hParent)
{
	return (GetChildItem(hParent) == NULL);
}

void EXWaitingTreeCtrl::DeleteChildren(HTREEITEM hParent)
{
	HTREEITEM hChild = GetChildItem(hParent);
	HTREEITEM hNext;

	while (hChild != NULL)
	{
		hNext = GetNextSiblingItem(hChild);
		DeleteItem(hChild);
		hChild = hNext;
	}
}

BOOL EXWaitingTreeCtrl::OnEraseBkgnd(CDC* pDC) 
{
	if (!m_bDrawSnapshot)
		return CTreeCtrl::OnEraseBkgnd(pDC);

	DrawSnapshot(pDC);
	SetEvent(m_hRedrawEvent);

	return TRUE;
}

void EXWaitingTreeCtrl::TakeSnapshot()
{
	CClientDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);
	int width = rcClient.Width(), height = rcClient.Height();

	// create the snapshot
	CDC dcSnapshot;
	dcSnapshot.CreateCompatibleDC(&dc);
	m_bmpSnapshot.CreateCompatibleBitmap(&dc, width, height);
	// copy the control's background
	CBitmap* pOldBmp = dcSnapshot.SelectObject(&m_bmpSnapshot);
	dcSnapshot.BitBlt(0, 0, width, height, &dc, 0, 0, SRCCOPY);
	dcSnapshot.SelectObject(pOldBmp);

	m_bDrawSnapshot = TRUE;
}

void EXWaitingTreeCtrl::DrawSnapshot(CDC *pDC)
{
	BITMAP bm;
	m_bmpSnapshot.GetBitmap(&bm);

	// prepare the snapshot
	CDC dcSnapshot;
	dcSnapshot.CreateCompatibleDC(pDC);
	// copy to the control's background
	CBitmap* pOldBmp = dcSnapshot.SelectObject(&m_bmpSnapshot);
	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcSnapshot, 0, 0, SRCCOPY);
	dcSnapshot.SelectObject(pOldBmp);
}

void EXWaitingTreeCtrl::DestroySnapshot()
{
	m_bmpSnapshot.DeleteObject();

	m_bDrawSnapshot = FALSE;
}
