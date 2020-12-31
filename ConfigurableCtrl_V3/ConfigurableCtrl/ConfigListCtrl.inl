// inline functions 
// (A) 'overloaded' CListCtrl functions

int CConfigListCtrl::InsertItem(const LVITEM* pItem)
{
	InsertBookmark(pItem->iItem);
	return CListCtrl::InsertItem(pItem);
}

int CConfigListCtrl::InsertItem(int nItem, LPCTSTR lpszItem)
{
	InsertBookmark(nItem);
	return CListCtrl::InsertItem(nItem, lpszItem);
}

int CConfigListCtrl::InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
{
	InsertBookmark(nItem);
	return CListCtrl::InsertItem(nItem, lpszItem, nImage);
}

BOOL CConfigListCtrl::SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
{
	RemoveCtrl(nItem, nSubItem);
	return CListCtrl::SetItem(nItem, nSubItem, nMask, lpszItem, nImage, nState, nStateMask, lParam);
}
	
BOOL CConfigListCtrl::SetItem(const LVITEM *pItem)
{
	RemoveCtrl(pItem->iItem, pItem->iSubItem);
	return CListCtrl::SetItem(pItem);
}

BOOL CConfigListCtrl::DeleteItem(int nItem)
{
	RemoveCtrlRow(nItem);
	return CListCtrl::DeleteItem(nItem);
}

BOOL CConfigListCtrl::DeleteAllItems()
{
	RemoveAllCtrls();
	return CListCtrl::DeleteAllItems();
}

int CConfigListCtrl::InsertColumn(int nCol, const LVCOLUMN* pColumn)
{
	InsertColumn(nCol);
	int iRetVal = CListCtrl::InsertColumn(nCol, pColumn);
	ShiftItemsRight(nCol);
	return iRetVal;
}

int CConfigListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat /*= LVCFMT_LEFT*/, int nWidth /*= -1*/, int nSubItem /*= -1*/)
{
	InsertColumn(nCol);
	int iRetVal = CListCtrl::InsertColumn(nCol, lpszColumnHeading, nFormat, nWidth, nSubItem);
	ShiftItemsRight(nCol);
	return iRetVal;
}

BOOL CConfigListCtrl::DeleteColumn(int nCol)
{
	RemoveCtrlColumn(nCol);
	return CListCtrl::DeleteColumn(nCol);
}

// (B) Other functions

void CConfigListCtrl::DeleteCtrl(int nItem, int nSubItem)
{
	CRect ref;
	RemoveCtrl(nItem, nSubItem);
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, ref);
	InvalidateRect(ref, FALSE);
}

DWORD CConfigListCtrl::GetMapKey(int nItem, int nSubItem) const
{
	return MAKELONG(WORD(nSubItem), WORD(nItem));
}





