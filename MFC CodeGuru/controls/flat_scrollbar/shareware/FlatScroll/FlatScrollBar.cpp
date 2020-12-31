// FlatScrollBar.cpp : implementation file
//
#include "commctrl.h"
#include "stdafx.h"
#include "FlatScrollBar.h"

/////////////////////////////////////////////////////////////////////////////
// CFlatScrollBar

CFlatScrollBar::CFlatScrollBar()
{
	m_pWnd = NULL;
}

CFlatScrollBar::~CFlatScrollBar()
{
	m_pWnd = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CFlatScrollBar message handlers

BOOL CFlatScrollBar::EnableScrollBar(int wSBflags,UINT wArrows)
{
	return ::FlatSB_EnableScrollBar(m_pWnd->GetSafeHwnd(),wSBflags,wArrows);
}

BOOL CFlatScrollBar::ShowScrollBar(int code, BOOL bShow)
{
	return ::FlatSB_ShowScrollBar(m_pWnd->GetSafeHwnd(),code, bShow);
}

BOOL CFlatScrollBar::GetScrollRange(int code, LPINT lpMinPos, LPINT lpMaxPos)
{
	return ::FlatSB_GetScrollRange(m_pWnd->GetSafeHwnd(),code,lpMinPos,lpMaxPos);
}

BOOL CFlatScrollBar::GetScrollInfo(int code, LPSCROLLINFO lpsi)
{
	return ::FlatSB_GetScrollInfo(m_pWnd->GetSafeHwnd(),code,lpsi);
}

int  CFlatScrollBar::GetScrollPos(int code)
{
	return ::FlatSB_GetScrollPos(m_pWnd->GetSafeHwnd(),code);
}

BOOL CFlatScrollBar::GetScrollProp(int propIndex, LPINT pValue)
{
	return ::FlatSB_GetScrollProp(m_pWnd->GetSafeHwnd(),propIndex, pValue);
}

int  CFlatScrollBar::SetScrollPos(int code, int pos, BOOL fRedraw)
{
	return ::FlatSB_SetScrollPos(m_pWnd->GetSafeHwnd(),code,pos,fRedraw);
}

int  CFlatScrollBar::SetScrollInfo(int code, LPSCROLLINFO lpsi, BOOL fRedraw)
{
	return ::FlatSB_SetScrollInfo(m_pWnd->GetSafeHwnd(),code,lpsi,fRedraw);
}

int  CFlatScrollBar::SetScrollRange(int code, int min, int max, BOOL fRedraw)
{
	return ::FlatSB_SetScrollRange(m_pWnd->GetSafeHwnd(),code,min,max,fRedraw);
}

BOOL CFlatScrollBar::SetScrollProp(UINT index, int newValue, BOOL fRedraw)
{
	return ::FlatSB_SetScrollProp(m_pWnd->GetSafeHwnd(),index,newValue,fRedraw);
}

BOOL CFlatScrollBar::InitializeFlatSB(CWnd *pWnd)
{
	m_pWnd = pWnd;
	return ::InitializeFlatSB(pWnd->GetSafeHwnd());
}

HRESULT CFlatScrollBar::UninitializeFlatSB()
{
	return ::UninitializeFlatSB(m_pWnd->GetSafeHwnd());
}
