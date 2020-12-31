/////////////////////////////////////////////////////////////////////////////
// CTreeCursor TREECTRLEX_INLINE functions

#define TREECTRLEX_INLINE inline

TREECTRLEX_INLINE CTreeCursor::CTreeCursor() : m_hTreeItem(NULL),	m_pTree(NULL)
{ }
TREECTRLEX_INLINE CTreeCursor::CTreeCursor(HTREEITEM hTreeItem, CTreeCtrlEx* pTree) :	m_hTreeItem(hTreeItem),	m_pTree(pTree)
{ }
TREECTRLEX_INLINE CTreeCursor::CTreeCursor(const CTreeCursor& posSrc)
{ *this = posSrc; }
TREECTRLEX_INLINE CTreeCursor::~CTreeCursor()
{ }
TREECTRLEX_INLINE CTreeCursor::operator HTREEITEM()
{ return m_hTreeItem; }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::InsertAfter(LPCTSTR strItem,HTREEITEM hAfter,int nImageIndex)
{ return _Insert(strItem,nImageIndex,hAfter); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::AddHead(LPCTSTR strItem,int nImageIndex)
{ return _Insert(strItem,nImageIndex,TVI_FIRST); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::AddTail(LPCTSTR strItem,int nImageIndex)
{ return _Insert(strItem,nImageIndex,TVI_LAST); }
TREECTRLEX_INLINE  BOOL CTreeCursor::GetRect(LPRECT lpRect, BOOL bTextOnly)
{ return m_pTree->GetItemRect(m_hTreeItem,lpRect,bTextOnly); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetNext(UINT nCode)
{ return m_pTree->GetNextItem(m_hTreeItem,nCode); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetChild()
{ return m_pTree->GetChildItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetNextSibling()
{ return m_pTree->GetNextSiblingItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetPrevSibling()
{ return m_pTree->GetPrevSiblingItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetParent()
{ return m_pTree->GetParentItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetFirstVisible()
{ return m_pTree->GetFirstVisibleItem(); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetNextVisible()
{ return m_pTree->GetNextVisibleItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetPrevVisible()
{ return m_pTree->GetPrevVisibleItem(m_hTreeItem); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetSelected()
{ return m_pTree->GetSelectedItem(); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetDropHilight()
{ return m_pTree->GetDropHilightItem(); }
TREECTRLEX_INLINE CTreeCursor CTreeCursor::GetRoot()
{ return m_pTree->GetRootItem(); }
TREECTRLEX_INLINE CString CTreeCursor::GetText()
{ return m_pTree->GetItemText(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::GetImage(int& nImage, int& nSelectedImage)
{ return m_pTree->GetItemImage(m_hTreeItem,nImage,nSelectedImage); }
TREECTRLEX_INLINE UINT CTreeCursor::GetState(UINT nStateMask)
{ return m_pTree->GetItemState(m_hTreeItem,nStateMask); }
TREECTRLEX_INLINE DWORD CTreeCursor::GetData()
{ return m_pTree->GetItemData(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetText(LPCTSTR lpszItem)
{ return m_pTree->SetItemText(m_hTreeItem,lpszItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetImage(int nImage, int nSelectedImage)
{ return m_pTree->SetItemImage(m_hTreeItem, nImage, nSelectedImage); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetState(UINT nState, UINT nStateMask)
{ return m_pTree->SetItemState(m_hTreeItem, nState, nStateMask); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetData(DWORD dwData)
{ return m_pTree->SetItemData(m_hTreeItem, dwData); }
TREECTRLEX_INLINE BOOL CTreeCursor::HasChildren()
{ return m_pTree->ItemHasChildren(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetInsertMark(BOOL fAfter)
{ return m_pTree->SetInsertMark(m_hTreeItem, fAfter); }
TREECTRLEX_INLINE BOOL CTreeCursor::GetCheck() const
{ return m_pTree->GetCheck(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SetCheck(BOOL fCheck)
{ return m_pTree->SetCheck(m_hTreeItem, fCheck); }
TREECTRLEX_INLINE BOOL CTreeCursor::Delete()
{ return m_pTree->DeleteItem(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::Expand(UINT nCode)
{ return m_pTree->Expand(m_hTreeItem,nCode); }
TREECTRLEX_INLINE BOOL CTreeCursor::Select(UINT nCode)
{ return (BOOL) m_pTree->Select(m_hTreeItem, nCode); }
TREECTRLEX_INLINE BOOL CTreeCursor::Select()
{ return (BOOL) m_pTree->SelectItem(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SelectDropTarget()
{ return (BOOL) m_pTree->SelectDropTarget(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SelectSetFirstVisible()
{ return (BOOL) m_pTree->SelectSetFirstVisible(m_hTreeItem); }
TREECTRLEX_INLINE CEdit* CTreeCursor::EditLabel()
{ return m_pTree->EditLabel(m_hTreeItem); }
TREECTRLEX_INLINE CImageList* CTreeCursor::CreateDragImage()
{ return m_pTree->CreateDragImage(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::SortChildren()
{ return m_pTree->SortChildren(m_hTreeItem); }
TREECTRLEX_INLINE BOOL CTreeCursor::EnsureVisible()
{ return m_pTree->EnsureVisible(m_hTreeItem); }

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx TREECTRLEX_INLINE functions

TREECTRLEX_INLINE CTreeCtrlEx::CTreeCtrlEx()
{ }
TREECTRLEX_INLINE CTreeCtrlEx::~CTreeCtrlEx()
{ }
TREECTRLEX_INLINE CToolTipCtrl* CTreeCtrlEx::GetToolTips() const
{ ASSERT(::IsWindow(m_hWnd)); return (CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, TVM_GETTOOLTIPS, 0, 0L)); }
TREECTRLEX_INLINE CToolTipCtrl* CTreeCtrlEx::SetToolTips(CToolTipCtrl* pWndTip)
{ ASSERT(::IsWindow(m_hWnd)); return (CToolTipCtrl*)CWnd::FromHandle((HWND)::SendMessage(m_hWnd, TVM_SETTOOLTIPS, (WPARAM)pWndTip->GetSafeHwnd(), 0L)); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::GetBkColor() const
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_GETBKCOLOR, 0, 0L); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::SetBkColor(COLORREF clr)
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_SETBKCOLOR, 0, (LPARAM)clr); }
TREECTRLEX_INLINE SHORT CTreeCtrlEx::GetItemHeight() const
{ ASSERT(::IsWindow(m_hWnd)); return (SHORT) ::SendMessage(m_hWnd, TVM_GETITEMHEIGHT, 0, 0L); }
TREECTRLEX_INLINE SHORT CTreeCtrlEx::SetItemHeight(SHORT cyHeight)
{ ASSERT(::IsWindow(m_hWnd)); return (SHORT) ::SendMessage(m_hWnd, TVM_SETITEMHEIGHT, cyHeight, 0L); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::GetTextColor() const
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_GETTEXTCOLOR, 0, 0L); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::SetTextColor(COLORREF clr)
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_SETTEXTCOLOR, 0, (LPARAM)clr); }
TREECTRLEX_INLINE BOOL CTreeCtrlEx::SetInsertMark(HTREEITEM hItem, BOOL fAfter)
{ ASSERT(::IsWindow(m_hWnd)); return (BOOL) ::SendMessage(m_hWnd, TVM_SETINSERTMARK, fAfter, (LPARAM)hItem); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::GetInsertMarkColor() const
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_GETINSERTMARKCOLOR, 0, 0L); }
TREECTRLEX_INLINE COLORREF CTreeCtrlEx::SetInsertMarkColor(COLORREF clrNew)
{ ASSERT(::IsWindow(m_hWnd)); return (COLORREF) ::SendMessage(m_hWnd, TVM_SETINSERTMARKCOLOR, 0, (LPARAM)clrNew); }
TREECTRLEX_INLINE CImageList* CTreeCtrlEx::SetImageList(CImageList* pImageList, int nImageListType)
{ return CTreeCtrl::SetImageList(pImageList,nImageListType); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetNextItem(HTREEITEM hItem, UINT nCode)
{ return CTreeCursor(CTreeCtrl::GetNextItem(hItem, nCode), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetChildItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetChildItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetNextSiblingItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetNextSiblingItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetPrevSiblingItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetPrevSiblingItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetParentItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetParentItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetFirstVisibleItem()
{ return CTreeCursor(CTreeCtrl::GetFirstVisibleItem(), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetNextVisibleItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetNextVisibleItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetPrevVisibleItem(HTREEITEM hItem)
{ return CTreeCursor(CTreeCtrl::GetPrevVisibleItem(hItem), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetSelectedItem()
{ return CTreeCursor(CTreeCtrl::GetSelectedItem(), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetDropHilightItem()
{ return CTreeCursor(CTreeCtrl::GetDropHilightItem(), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::GetRootItem()
{ return CTreeCursor(CTreeCtrl::GetRootItem(), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
{ return CTreeCursor(_InsertItem(lpInsertStruct), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
                                                      int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
                                                      HTREEITEM hParent, HTREEITEM hInsertAfter)
{ return CTreeCursor(CTreeCtrl::InsertItem(nMask, lpszItem, nImage,
                     nSelectedImage, nState, nStateMask, lParam, hParent, hInsertAfter), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, 
                                                      HTREEITEM hInsertAfter)
{ return CTreeCursor(CTreeCtrl::InsertItem(lpszItem, hParent, hInsertAfter), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
                                                      HTREEITEM hParent, HTREEITEM hInsertAfter)
{ return CTreeCursor(CTreeCtrl::InsertItem(lpszItem, nImage, nSelectedImage,
                     hParent, hInsertAfter), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::HitTest(CPoint pt, UINT* pFlags)
{ return CTreeCursor(CTreeCtrl::HitTest(pt,pFlags), this); }
TREECTRLEX_INLINE CTreeCursor CTreeCtrlEx::HitTest(TVHITTESTINFO* pHitTestInfo)
{ return CTreeCursor(CTreeCtrl::HitTest((TV_HITTESTINFO*)pHitTestInfo), this); }
TREECTRLEX_INLINE HTREEITEM CTreeCtrlEx::_InsertItem(LPTVINSERTSTRUCT lpInsertStruct)
{ ASSERT(::IsWindow(m_hWnd)); return (HTREEITEM)::SendMessage(m_hWnd, TVM_INSERTITEM, 0, (LPARAM)lpInsertStruct); }
TREECTRLEX_INLINE BOOL CTreeCtrlEx::_GetItem(TVITEM* pItem) const
{ ASSERT(::IsWindow(m_hWnd)); return (BOOL)::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)pItem); }

/////////////////////////////////////////////////////////////////////////////
