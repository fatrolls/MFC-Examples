#include "stdafx.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

BOOL CListCtrlEx::SetItemCountEx(int iCount, DWORD dwFlags /* = LVSICF_NOINVALIDATEALL */)
{
  ASSERT(::IsWindow(m_hWnd));

  // can't have dwFlags on a control that isn't virutal
  ASSERT(dwFlags == 0 || (GetStyle() & LVS_OWNERDATA));

  return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMCOUNT, (WPARAM) iCount,
    (LPARAM) dwFlags);
}

CSize CListCtrlEx::SetIconSpacing(int cx, int cy)
{
  ASSERT(::IsWindow(m_hWnd));
  DWORD dwRet = (DWORD) ::SendMessage(m_hWnd, LVM_SETICONSPACING,
    0, (LPARAM) MAKELONG(cx, cy));

  return CSize(dwRet);
}

CSize CListCtrlEx::SetIconSpacing(CSize size)
{
  ASSERT(::IsWindow(m_hWnd));
  DWORD dwRet = (DWORD) ::SendMessage(m_hWnd, LVM_SETICONSPACING,
    0, (LPARAM) MAKELONG(size.cx, size.cy));

  return CSize(dwRet);
}

BOOL CListCtrlEx::GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& ref)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(nArea == LVIR_BOUNDS || nArea == LVIR_ICON || nArea == LVIR_LABEL);

  RECT rect;
  rect.top = iSubItem;
  rect.left = nArea;
  BOOL bRet = (BOOL) ::SendMessage(m_hWnd, LVM_GETSUBITEMRECT,
    iItem, (LPARAM) &rect);

  if (bRet)
    ref = rect;
  return bRet;
}

int CListCtrlEx::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat,
  int nWidth, int nSubItem, int nOrder, int nImage)
{
  LVCOLUMN column;
  column.mask = LVCF_TEXT|LVCF_FMT;
  column.pszText = (LPTSTR)lpszColumnHeading;
  column.fmt = nFormat;
  column.iOrder = nOrder;
  column.iImage = nImage;
  if (nWidth != -1)
  {
    column.mask |= LVCF_WIDTH;
    column.cx = nWidth;
  }
  else
  {
    column.mask |= LVCF_WIDTH;
    column.cx = GetStringWidth(column.pszText) + 15;
  }
  if (nSubItem != -1)
  {
    column.mask |= LVCF_SUBITEM;
    column.iSubItem = nSubItem;
  }
  return InsertColumn(nCol, &column);
}

int CListCtrlEx::InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask,
  int nImage, LPARAM lParam, int nIndent)
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM item;
  item.mask = nMask;
  item.iItem = nItem;
  item.iSubItem = 0;
  item.pszText = (LPTSTR)lpszItem;
  item.state = nState;
  item.stateMask = nStateMask;
  item.iImage = nImage;
  item.lParam = lParam;
  item.iIndent = nIndent;
  return InsertItem(&item);
}

int CListCtrlEx::HitTest(CPoint pt, UINT* pFlags) const
{
  ASSERT(::IsWindow(m_hWnd));
  LVHITTESTINFO hti;
  hti.pt = pt;
  int nRes = (int) ::SendMessage(m_hWnd, LVM_HITTEST, 0, (LPARAM)&hti);
  if (pFlags != NULL)
    *pFlags = hti.flags;
  return nRes;
}

BOOL CListCtrlEx::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
  int nImage, UINT nState, UINT nStateMask, LPARAM lParam, int nIndent)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT((GetStyle() & LVS_OWNERDATA)==0);
  LVITEM lvi;
  lvi.mask = nMask;
  lvi.iItem = nItem;
  lvi.iSubItem = nSubItem;
  lvi.stateMask = nStateMask;
  lvi.state = nState;
  lvi.pszText = (LPTSTR) lpszItem;
  lvi.iImage = nImage;
  lvi.lParam = lParam;
  lvi.iIndent = nIndent;
  return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)&lvi);
}

BOOL CListCtrlEx::SetItemState(int nItem, UINT nState, UINT nStateMask)
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM lvi;
  lvi.stateMask = nStateMask;
  lvi.state = nState;
  return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
}

BOOL CListCtrlEx::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT((GetStyle() & LVS_OWNERDATA)==0);
  LVITEM lvi;
  lvi.iSubItem = nSubItem;
  lvi.pszText = (LPTSTR) lpszText;
  return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi);
}

CString CListCtrlEx::GetItemText(int nItem, int nSubItem) const
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM lvi;
  memset(&lvi, 0, sizeof(LVITEM));
  lvi.iSubItem = nSubItem;
  CString str;
  int nLen = 128;
  int nRes;
  do
  {
    nLen *= 2;
    lvi.cchTextMax = nLen;
    lvi.pszText = str.GetBufferSetLength(nLen);
    nRes  = (int)::SendMessage(m_hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,
      (LPARAM)&lvi);
  } while (nRes == nLen-1);
  str.ReleaseBuffer();
  return str;
}

int CListCtrlEx::GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM lvi;
  memset(&lvi, 0, sizeof(LVITEM));
  lvi.iSubItem = nSubItem;
  lvi.cchTextMax = nLen;
  lvi.pszText = lpszText;
  return (int)::SendMessage(m_hWnd, LVM_GETITEMTEXT, (WPARAM)nItem,
    (LPARAM)&lvi);
}

DWORD CListCtrlEx::GetItemData(int nItem) const
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM lvi;
  memset(&lvi, 0, sizeof(LVITEM));
  lvi.iItem = nItem;
  lvi.mask = LVIF_PARAM;
  VERIFY(::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)&lvi));
  return (DWORD)lvi.lParam;
}

int CListCtrlEx::AddItem(int nItem, int nSubItem, LPCTSTR strItem, 
                         int nImage)
{
  LVITEM lvItem;
  lvItem.mask = LVIF_TEXT;
  lvItem.iItem = nItem;
  lvItem.iSubItem = nSubItem;
  lvItem.pszText = (LPTSTR)strItem;
  if (nImage != -1)
  {
    lvItem.mask |= LVIF_IMAGE;
    lvItem.iImage = nImage;
  }
  if (nSubItem == 0)
    return InsertItem(&lvItem);
  return SetItem(&lvItem);
}

int CListCtrlEx::AddItem(int nItem, int nSubItem, LPCTSTR strItem,
                         int nImageIndex, LPARAM lParam, int nIndent)
{
  LV_ITEM lvItem;
  lvItem.mask = LVIF_TEXT | LVIF_PARAM;
  lvItem.iItem = nItem;
  lvItem.iSubItem = nSubItem;
  lvItem.pszText = (LPTSTR)strItem;
  lvItem.lParam = lParam;
  lvItem.iIndent = nIndent;
  if (nImageIndex != -1)
  {
    lvItem.mask |= LVIF_IMAGE;
    lvItem.iImage = nImageIndex;
  }
  if (nSubItem == 0)
    return InsertItem(&lvItem);
  return SetItem(&lvItem);
}

BOOL CListCtrlEx::SetColumnOrderArray(int iCount, LPINT piArray)
{
  ASSERT(::IsWindow(m_hWnd));
  ASSERT(AfxIsValidAddress(piArray, iCount * sizeof(int), FALSE));

  return (BOOL) ::SendMessage(m_hWnd, LVM_SETCOLUMNORDERARRAY,
    (WPARAM) iCount, (LPARAM) piArray);
}

BOOL CListCtrlEx::GetColumnOrderArray(LPINT piArray, int iCount /* = -1 */)
{
  ASSERT(::IsWindow(m_hWnd));

  // if -1 was passed, find the count ourselves

  int nCount = iCount;
  if (nCount == -1)
  {
    CHeaderCtrl* pCtrl = GetHeaderCtrl();
    ASSERT(pCtrl != NULL);
    if (pCtrl != NULL)
      nCount = pCtrl->GetItemCount();
  }
  if (nCount == -1)
    return FALSE;

  ASSERT(AfxIsValidAddress(piArray, nCount * sizeof(int)));
  return (BOOL) ::SendMessage(m_hWnd, LVM_GETCOLUMNORDERARRAY,
    (WPARAM) nCount, (LPARAM) piArray);
}

BOOL CListCtrlEx::SetBkImage(HBITMAP hbm, BOOL fTile /*= TRUE*/,
                             int xOffsetPercent /*= 0*/, int yOffsetPercent /*= 0*/)
{
  LVBKIMAGE lv;

  lv.ulFlags = LVBKIF_SOURCE_HBITMAP;
  if (fTile)
    lv.ulFlags |= LVBKIF_STYLE_TILE;
  else
    lv.ulFlags |= LVBKIF_STYLE_NORMAL;
  lv.hbm = hbm;
  lv.xOffsetPercent = xOffsetPercent;
  lv.yOffsetPercent = yOffsetPercent;
  return SetBkImage(&lv);
}

BOOL CListCtrlEx::SetBkImage(LPTSTR pszUrl, BOOL fTile /*= TRUE*/,
                           int xOffsetPercent /*= 0*/, int yOffsetPercent /*= 0*/)
{
  LVBKIMAGE lv;

  lv.ulFlags = LVBKIF_SOURCE_URL;
  if (fTile)
    lv.ulFlags |= LVBKIF_STYLE_TILE;
  else
    lv.ulFlags |= LVBKIF_STYLE_NORMAL;
  lv.pszImage = pszUrl;
  lv.xOffsetPercent = xOffsetPercent;
  lv.yOffsetPercent = yOffsetPercent;
  return SetBkImage(&lv);
}

BOOL CListCtrlEx::GetCheck(int nItem) const
{
  ASSERT(::IsWindow(m_hWnd));
  int nState = (int)::SendMessage(m_hWnd, LVM_GETITEMSTATE, (WPARAM)nItem,
    (LPARAM)LVIS_STATEIMAGEMASK);
  // Return zero if it's not checked, or nonzero otherwise.
  return ((BOOL)(nState >> 12) -1);
}

BOOL CListCtrlEx::SetCheck(int nItem, BOOL fCheck)
{
  ASSERT(::IsWindow(m_hWnd));
  LVITEM lvi;
  lvi.stateMask = LVIS_STATEIMAGEMASK;

  /*
  Since state images are one-based, 1 in this macro turns the check off, and
  2 turns it on.
  */
  lvi.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));
  return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
}

CHeaderCtrl* CListCtrlEx::GetHeaderCtrl()
{
	ASSERT(::IsWindow(m_hWnd));

	HWND hWnd = (HWND) ::SendMessage(m_hWnd, LVM_GETHEADER, 0, 0);
	if (hWnd == NULL)
		return NULL;
	else
		return (CHeaderCtrl*) CHeaderCtrl::FromHandle(hWnd);
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

/////////////////////////////////////////////////////////////////////////////

