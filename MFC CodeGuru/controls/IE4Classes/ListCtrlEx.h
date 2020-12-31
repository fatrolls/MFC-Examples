#ifndef __LSCTL_H__
#define __LSCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

class CListCtrlEx : public CListCtrl
{
  DECLARE_DYNAMIC(CListCtrlEx)

// Constructors
public:
  CListCtrlEx()
  { }

// Attributes
  BOOL GetItem(LVITEM* pItem) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_GETITEM, 0, (LPARAM)pItem); }
  BOOL SetItem(const LVITEM* pItem)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEM, 0, (LPARAM)pItem); }
  BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
    int nImage, UINT nState, UINT nStateMask, LPARAM lParam, int nIndent);
  int GetNextItem(int nItem, int nFlags) const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0)); }
  POSITION GetFirstSelectedItemPosition() const
	{ ASSERT(::IsWindow(m_hWnd)); return (POSITION) (1+GetNextItem(-1, LVIS_SELECTED)); }
  int GetNextSelectedItem(POSITION& pos) const
	{ ASSERT(::IsWindow(m_hWnd)); int nOldPos = (int)pos-1; pos = (POSITION) (1+GetNextItem(nOldPos, LVIS_SELECTED)); return nOldPos; }
  BOOL GetColumn(int nCol, LVCOLUMN* pColumn) const
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_GETCOLUMN, nCol, (LPARAM)pColumn); }
  BOOL SetColumn(int nCol, const LVCOLUMN* pColumn)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_SETCOLUMN, nCol, (LPARAM)pColumn); }
  BOOL SetItemState(int nItem, LVITEM* pItem)
  { ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_SETITEMSTATE, nItem, (LPARAM)pItem); }
  BOOL SetItemState(int nItem, UINT nState, UINT nStateMask);
  UINT GetItemState(int nItem, UINT nMask) const
  { ASSERT(::IsWindow(m_hWnd)); return (UINT) ::SendMessage(m_hWnd, LVM_GETITEMSTATE, nItem, nMask); }
  CString GetItemText(int nItem, int nSubItem) const;
  int GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const;
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
  DWORD GetItemData(int nItem) const;
	BOOL SetColumnOrderArray(int iCount, LPINT piArray);
	BOOL GetColumnOrderArray(LPINT piArray, int iCount = -1);
	CSize SetIconSpacing(CSize size);
	CSize SetIconSpacing(int cx, int cy);
	CHeaderCtrl* GetHeaderCtrl();
	HCURSOR GetHotCursor()
	{ ASSERT(::IsWindow(m_hWnd)); return (HCURSOR) ::SendMessage(m_hWnd, LVM_GETHOTCURSOR, 0, 0); }
	HCURSOR SetHotCursor(HCURSOR hc)
	{ ASSERT(::IsWindow(m_hWnd) && hc != NULL); return (HCURSOR) ::SendMessage(m_hWnd, LVM_SETHOTCURSOR, 0, (LPARAM) hc); }
	BOOL GetSubItemRect(int iItem, int iSubItem, int nArea, CRect& ref);
	int GetHotItem()
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_GETHOTITEM, 0, 0); }
	int SetHotItem(int iIndex)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_SETHOTITEM, (WPARAM) iIndex, 0); }
	int GetSelectionMark()
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_GETSELECTIONMARK, 0, 0); }
	int SetSelectionMark(int iIndex)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_SETSELECTIONMARK, 0, (LPARAM) iIndex); }
	DWORD GetExtendedStyle()
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0); }
	DWORD SetExtendedStyle(DWORD dwNewStyle)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, (LPARAM) dwNewStyle); }
	int SubItemHitTest(LPLVHITTESTINFO pInfo)
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_SUBITEMHITTEST, 0, (LPARAM) pInfo); }
	void SetWorkAreas(int nWorkAreas, LPRECT lpRect)
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, LVM_SETWORKAREAS, nWorkAreas, (LPARAM) lpRect); }
	BOOL SetItemCountEx(int iCount, DWORD dwFlags = LVSICF_NOINVALIDATEALL);
	CSize ApproximateViewRect(CSize sz = CSize(-1, -1), int iCount = -1) const
	{ ASSERT(::IsWindow(m_hWnd)); return CSize((DWORD) ::SendMessage(m_hWnd, LVM_APPROXIMATEVIEWRECT, iCount, MAKELPARAM(sz.cx, sz.cy))); }
	BOOL GetBkImage(LVBKIMAGE* plvbkImage) const
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, LVM_GETBKIMAGE, 0, (LPARAM)plvbkImage); }
	DWORD GetHoverTime() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD) ::SendMessage(m_hWnd, LVM_GETHOVERTIME, 0, 0); }
	void GetWorkAreas(int nWorkAreas, LPRECT prc) const
	{ ASSERT(::IsWindow(m_hWnd)); ::SendMessage(m_hWnd, LVM_GETWORKAREAS, nWorkAreas, (LPARAM)prc); }
	BOOL SetBkImage(HBITMAP hbm, BOOL fTile = TRUE, int xOffsetPercent = 0, int yOffsetPercent = 0);
	BOOL SetBkImage(LPTSTR pszUrl, BOOL fTile = TRUE, int xOffsetPercent = 0, int yOffsetPercent = 0);
	BOOL SetBkImage(LVBKIMAGE* plvbkImage)
	{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, LVM_SETBKIMAGE, 0, (LPARAM)plvbkImage); }
	DWORD SetHoverTime(DWORD dwHoverTime = (DWORD)-1)
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, LVM_SETHOVERTIME, 0, dwHoverTime); }
	UINT GetNumberOfWorkAreas() const
	{ ASSERT(::IsWindow(m_hWnd)); UINT nWorkAreas; ::SendMessage(m_hWnd, LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)&nWorkAreas); return nWorkAreas; }
	BOOL GetCheck(int nItem) const;
	BOOL SetCheck(int nItem, BOOL fCheck = TRUE);

// Operations
  int InsertItem(const LVITEM* pItem)
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)pItem); }
  int FindItem(LVFINDINFO* pFindInfo, int nStart = -1) const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_FINDITEM, nStart, (LPARAM)pFindInfo); }
  int HitTest(LVHITTESTINFO* pHitTestInfo) const
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_HITTEST, 0, (LPARAM)pHitTestInfo); }
  int HitTest(CPoint pt, UINT* pFlags = NULL) const;
  int InsertColumn(int nCol, const LVCOLUMN* pColumn)
  { ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn); }
  int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
    int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1, 
    int nOrder = -1, int nImage = -1);

// Overridables

// Implementation
public:
  int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState,
    UINT nStateMask, int nImage, LPARAM lParam, int nIndent);
  int AddItem(int nItem, int nSubItem, LPCTSTR strItem, int nImage = -1);
  int AddItem(int nItem, int nSubItem, LPCTSTR strItem, int nImage,
    LPARAM dwParam, int nIndent = 0);
};

#endif //__LSCTL_H__

/////////////////////////////////////////////////////////////////////////////
