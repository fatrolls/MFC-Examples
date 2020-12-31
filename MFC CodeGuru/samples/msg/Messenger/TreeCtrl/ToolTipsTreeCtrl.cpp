//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================

// ToolTipsTreeCtrl.cpp : implementation file
//

#include "StdAfx.h"
#include "ToolTipsTreeCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipsTreeCtrl

CToolTipsTreeCtrl::CToolTipsTreeCtrl()
{
}

CToolTipsTreeCtrl::~CToolTipsTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CToolTipsTreeCtrl, CMultiSelTreeCtrl)
	//{{AFX_MSG_MAP(CToolTipsTreeCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTW, 0, 0xFFFF, OnToolTipText)
	ON_NOTIFY_EX_RANGE(TTN_NEEDTEXTA, 0, 0xFFFF, OnToolTipText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolTipsTreeCtrl message handlers

CString CToolTipsTreeCtrl::GetToolTips(CTreeCursor &cursor, UINT nFlags)
{
	nFlags;

	return cursor.GetText();
}

int CToolTipsTreeCtrl::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	UINT nFlags;

	HTREEITEM hTreeItem = CTreeCtrl::HitTest(point,&nFlags);
	if(hTreeItem)
	{
		CRect rect;
		
		GetItemRect(hTreeItem,&rect,TRUE);
		pTI->hwnd = GetSafeHwnd();
		pTI->uId = (UINT)hTreeItem;
		pTI->rect = rect;		
		pTI->lpszText = LPSTR_TEXTCALLBACK;
	
		return pTI->uId;
	}

	return -1;
}

BOOL CToolTipsTreeCtrl::OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
	id;
	// need to handle both ANSI and UNICODE versions of the message
	CString strTipText;
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;

	// allow top level routing frame to handle the message
//	if (GetRoutingFrame() != NULL)
//		return FALSE;

	// Do not process the message from built in tooltip 
	if(pNMHDR->idFrom != (UINT)GetSafeHwnd() &&	
		((pNMHDR->code == TTN_NEEDTEXTA && pTTTA->uFlags & TTF_IDISHWND) ||
		(pNMHDR->code == TTN_NEEDTEXTW && pTTTW->uFlags & TTF_IDISHWND)))
	{
		return FALSE;
	}

	// Get the mouse position
	CPoint point;
	const MSG* pMessage = GetCurrentMessage();

	ASSERT(pMessage);
	point = pMessage->pt;
	ScreenToClient(&point);

	UINT nFlags;
	CTreeCursor	cursor = HitTest(point,&nFlags);

	if(cursor)
	{
		strTipText = GetToolTips(cursor,nFlags);
	}

#ifndef _UNICODE
	if (pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, strTipText, 80);
	else
		_mbstowcsz(pTTTW->szText, strTipText, 80);
#else
	if (pNMHDR->code == TTN_NEEDTEXTA)
		_wcstombsz(pTTTA->szText, strTipText, 80);
	else
		lstrcpyn(pTTTW->szText, strTipText, 80);
#endif
	*pResult = 0;

	return TRUE;    // message was handled
}
  

