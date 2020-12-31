// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	//{{AFX_MSG_MAP(CListCtrlEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

int CListCtrlEx::AddItem(LPCTSTR strItem, int nItem, int nSubItem, UINT nState, int nImageIndex, long nParam)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nItem;
	lvItem.iSubItem = nSubItem;
	lvItem.pszText = (LPTSTR)strItem;

	if (nState != -1)
	{
		lvItem.mask |= LVIF_STATE;
		lvItem.state = nState;
	}
	if (nImageIndex != -1)
	{
		lvItem.mask |= LVIF_IMAGE;
		lvItem.iImage = nImageIndex;
	}
	if (nParam != -1)
	{
		lvItem.mask |= LVIF_PARAM;
		lvItem.lParam = nParam;
	}
	if (nSubItem == 0)
		return InsertItem(&lvItem);
	else
		return SetItem(&lvItem);
}

DWORD CListCtrlEx::GetViewStyle() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (DWORD) (::GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK);
}

DWORD CListCtrlEx::SetViewStyle(DWORD dwNewView)
{
	ASSERT(::IsWindow(m_hWnd));
	return (DWORD) (::SetWindowLong(m_hWnd, GWL_STYLE, (::GetWindowLong(m_hWnd, GWL_STYLE) & ~LVS_TYPEMASK) | dwNewView) & LVS_TYPEMASK);
}

// Available with IE4 Dll => commctl.dll v4.71.1712.3
#ifndef NOLISTVIEWEX

POSITION CListCtrlEx::GetFirstSelectedItemPosition() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (POSITION)(1+GetNextItem(-1, LVIS_SELECTED));
}

int CListCtrlEx::GetNextSelectedItem(POSITION& pos) const
{
	ASSERT(::IsWindow(m_hWnd));
	int nReturn = (int)pos-1;
	pos = (POSITION)(1+GetNextItem(nReturn, LVIS_SELECTED));
	return nReturn;
}

BOOL CListCtrlEx::GetColumnOrderArray(LPINT pnArray, int nCount) const
{
	ASSERT(::IsWindow(m_hWnd));

	if (nCount == -1)
	{
		CHeaderCtrl* pHeader = GetHeaderCtrl();
		if (pHeader != NULL)
			nCount = pHeader->GetItemCount();
	}
	
	if (nCount == -1)
		return FALSE;

	ASSERT(AfxIsValidAddress(pnArray, nCount * sizeof(int)));
	return (BOOL) ::SendMessage(m_hWnd, LVM_GETCOLUMNORDERARRAY, (WPARAM)nCount, (LPARAM)pnArray);
}

BOOL CListCtrlEx::SetColumnOrderArray(int nCount, LPINT pnArray)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(AfxIsValidAddress(pnArray, nCount * sizeof(int), FALSE));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETCOLUMNORDERARRAY, (WPARAM)nCount, (LPARAM)pnArray);
}

CSize CListCtrlEx::SetIconSpacing(CSize size)
{
	ASSERT(::IsWindow(m_hWnd));
	return CSize((DWORD) ::SendMessage(m_hWnd, LVM_SETICONSPACING, 0, MAKELPARAM(size.cx, size.cy)));
}

CSize CListCtrlEx::SetIconSpacing(int cx, int cy)
{
	ASSERT(::IsWindow(m_hWnd));
	return CSize((DWORD) ::SendMessage(m_hWnd, LVM_SETICONSPACING, 0, MAKELPARAM(cx, cy)));
}

CHeaderCtrl* CListCtrlEx::GetHeaderCtrl() const
{
	ASSERT(::IsWindow(m_hWnd));

	HWND hWnd = (HWND) ::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0L);
	if (hWnd == NULL)
		return NULL;
	else
		return (CHeaderCtrl*) CHeaderCtrl::FromHandle(hWnd);
}

HCURSOR CListCtrlEx::GetHotCursor() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (HCURSOR) ::SendMessage(m_hWnd, LVM_GETHOTCURSOR, 0, 0L);
}

HCURSOR CListCtrlEx::SetHotCursor(HCURSOR hc)
{
	ASSERT(::IsWindow(m_hWnd) && hc != NULL);
	return (HCURSOR) ::SendMessage(m_hWnd, LVM_SETHOTCURSOR, 0, (LPARAM)hc);
}

BOOL CListCtrlEx::GetSubItemRect(int nItem, int nSubItem, int nArea, CRect & rcRef) const
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT(nArea == LVIR_BOUNDS || nArea == LVIR_ICON || nArea == LVIR_LABEL);

	RECT rect;
	rect.top = nSubItem;
	rect.left = nArea;

	BOOL bReturn = (BOOL) ::SendMessage(m_hWnd, LVM_GETSUBITEMRECT, nItem, (LPARAM) &rect);
	if (bReturn)
		rcRef = rect;
	return bReturn;
}

int CListCtrlEx::GetHotItem() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_GETHOTITEM, 0, 0L);
}

int CListCtrlEx::SetHotItem(int nIndex)
{
	ASSERT(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_SETHOTITEM, (WPARAM)nIndex, 0L);
}

int CListCtrlEx::GetSelectionMark() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_GETSELECTIONMARK, 0, 0L);
}

int CListCtrlEx::SetSelectionMark(int nIndex)
{
	ASSERT(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_SETSELECTIONMARK, 0, (LPARAM)nIndex);
}

DWORD CListCtrlEx::GetExtendedStyle() const
{ 
	ASSERT(::IsWindow(m_hWnd)); 
	return (DWORD) ::SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0L);
}

DWORD CListCtrlEx::SetExtendedStyle(DWORD dwNewStyle)
{
	ASSERT(::IsWindow(m_hWnd));
	return (DWORD) ::SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM)dwNewStyle);
}

int CListCtrlEx::SubItemHitTest(LPLVHITTESTINFO lpInfo)
{
	ASSERT(::IsWindow(m_hWnd));
	return (int) ::SendMessage(m_hWnd, LVM_SUBITEMHITTEST, 0, (LPARAM)lpInfo);
}

UINT CListCtrlEx::GetNumberOfWorkAreas() const
{
	ASSERT(::IsWindow(m_hWnd));
	UINT nWorkAreas;
	::SendMessage(m_hWnd, LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)&nWorkAreas);
	return nWorkAreas;
}

void CListCtrlEx::GetWorkAreas(int nWorkAreas, LPRECT lpRect) const
{
	ASSERT(::IsWindow(m_hWnd));
	::SendMessage(m_hWnd, LVM_GETWORKAREAS, (WPARAM)nWorkAreas, (LPARAM)lpRect);
}

void CListCtrlEx::SetWorkAreas(int nWorkAreas, LPRECT lpRect)
{
	ASSERT(::IsWindow(m_hWnd));
	::SendMessage(m_hWnd, LVM_SETWORKAREAS, (WPARAM)nWorkAreas, (LPARAM)lpRect);
}

BOOL CListCtrlEx::SetItemCountEx(int iCount, DWORD dwFlags)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT((GetStyle() & LVS_OWNERDATA));	

	return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMCOUNT, (WPARAM)iCount, (LPARAM)dwFlags);
}

CSize CListCtrlEx::ApproximateViewRect(CSize size, int nCount) const
{
	ASSERT(::IsWindow(m_hWnd));
	return CSize((DWORD) ::SendMessage(m_hWnd, LVM_APPROXIMATEVIEWRECT, nCount, MAKELPARAM(size.cx, size.cy)));
}

BOOL CListCtrlEx::GetBkImage(LVBKIMAGE* plvbkImage) const
{
	ASSERT(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_GETBKIMAGE, 0, (LPARAM)plvbkImage);
}

BOOL CListCtrlEx::SetBkImage(HBITMAP hbm, BOOL bTile, int xOffsetPercent, int yOffsetPercent)
{
	LVBKIMAGE lv;

	lv.ulFlags = LVBKIF_SOURCE_HBITMAP;
	lv.ulFlags |= (bTile) ? LVBKIF_STYLE_TILE : LVBKIF_STYLE_NORMAL;
	lv.hbm = hbm;
	lv.xOffsetPercent = xOffsetPercent;
	lv.yOffsetPercent = yOffsetPercent;
	return SetBkImage(&lv);
}

BOOL CListCtrlEx::SetBkImage(LPTSTR pszUrl, BOOL bTile, int xOffsetPercent, int yOffsetPercent)
{
	LVBKIMAGE lv;

	lv.ulFlags = LVBKIF_SOURCE_HBITMAP;
	lv.ulFlags |= (bTile) ? LVBKIF_STYLE_TILE : LVBKIF_STYLE_NORMAL;
	lv.pszImage = pszUrl;
	lv.xOffsetPercent = xOffsetPercent;
	lv.yOffsetPercent = yOffsetPercent;
	return SetBkImage(&lv);
}

BOOL CListCtrlEx::SetBkImage(LVBKIMAGE* plvbkImage)
{
	ASSERT(::IsWindow(m_hWnd));
	return (BOOL) ::SendMessage(m_hWnd, LVM_SETBKIMAGE, 0, (LPARAM)plvbkImage);
}

DWORD CListCtrlEx::GetHoverTime() const
{
	ASSERT(::IsWindow(m_hWnd));
	return (DWORD) ::SendMessage(m_hWnd, LVM_GETHOVERTIME, 0, 0L);
}

DWORD CListCtrlEx::SetHoverTime(DWORD dwHoverTime)
{
	ASSERT(::IsWindow(m_hWnd));
	return (DWORD) ::SendMessage(m_hWnd, LVM_SETHOVERTIME, 0, (LPARAM)dwHoverTime);
}

BOOL CListCtrlEx::GetCheck(int nItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	int nState = (int) ::SendMessage(m_hWnd, LVM_GETITEMSTATE, (WPARAM)nItem, (LPARAM)LVIS_STATEIMAGEMASK);

	return ((BOOL)(nState >> 12) -1);
}

BOOL CListCtrlEx::SetCheck(int nItem, BOOL bCheck)
{
	ASSERT(::IsWindow(m_hWnd));
	LVITEM lvi;
	lvi.stateMask = LVIS_STATEIMAGEMASK;
	lvi.state = INDEXTOSTATEIMAGEMASK((bCheck ? 2 : 1));

	return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
}

#endif // NOLISTVIEWEX