#ifndef __TRCTL_H__
#define __TRCTL_H__

#ifndef __AFXWIN_H__
  #include <afxwin.h>
#endif

/////////////////////////////////////////////////////////////////////////////

class CTreeCursor;
class CTreeCtrlEx;

/////////////////////////////////////////////////////////////////////////////
// CTreeCursor

class CTreeCursor
{
// Attributes
protected:
  HTREEITEM m_hTreeItem;
  CTreeCtrlEx *m_pTree;

// Implementation
protected:
  CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem,int nImageIndex,HTREEITEM hAfter);

// Operations
public:
  CTreeCursor();
  CTreeCursor(HTREEITEM hTreeItem, CTreeCtrlEx* pTree);
  CTreeCursor(const CTreeCursor& posSrc);
  ~CTreeCursor();
  const CTreeCursor& operator =(const CTreeCursor& posSrc);
  operator HTREEITEM();

  CTreeCursor InsertAfter(LPCTSTR strItem,HTREEITEM hAfter,int nImageIndex = -1);
  CTreeCursor AddHead(LPCTSTR strItem,int nImageIndex = -1);
  CTreeCursor AddTail(LPCTSTR strItem,int nImageIndex = -1);

  int GetImageID();

  BOOL GetRect(LPRECT lpRect, BOOL bTextOnly);
  CTreeCursor GetNext(UINT nCode);
  CTreeCursor GetChild();
  CTreeCursor GetNextSibling();
  CTreeCursor GetPrevSibling();
  CTreeCursor GetParent();
  CTreeCursor GetFirstVisible();
  CTreeCursor GetNextVisible();
  CTreeCursor GetPrevVisible();
  CTreeCursor GetSelected();
  CTreeCursor GetDropHilight();
  CTreeCursor GetRoot();
  CString GetText();
  BOOL GetImage(int& nImage, int& nSelectedImage);
  UINT GetState(UINT nStateMask);
  DWORD GetData();
  BOOL Set(UINT nMask, LPCTSTR lpszItem, int nImage, 
    int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam);
  BOOL SetText(LPCTSTR lpszItem);
  BOOL SetImage(int nImage, int nSelectedImage);
  BOOL SetState(UINT nState, UINT nStateMask);
  BOOL SetData(DWORD dwData);
  BOOL HasChildren();
  BOOL SetInsertMark(BOOL fAfter = TRUE);
  BOOL GetCheck() const;
  BOOL SetCheck(BOOL fCheck = TRUE);

  BOOL Delete();

  BOOL Expand(UINT nCode = TVE_EXPAND);
  BOOL Select(UINT nCode);
  BOOL Select();
  BOOL SelectDropTarget();
  BOOL SelectSetFirstVisible();
  CEdit* EditLabel();
  CImageList* CreateDragImage();
  BOOL SortChildren();
  BOOL EnsureVisible();
};

/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

class CTreeCtrlEx : public CTreeCtrl
{
  DECLARE_DYNAMIC(CTreeCtrlEx)

// Attributes
public:
  CTreeCtrlEx();
  
  CToolTipCtrl* GetToolTips() const;
  CToolTipCtrl* SetToolTips(CToolTipCtrl* pWndTip);
  COLORREF GetBkColor() const;
  COLORREF SetBkColor(COLORREF clr);
  SHORT GetItemHeight() const;
  SHORT SetItemHeight(SHORT cyHeight);
  COLORREF GetTextColor() const;
  COLORREF SetTextColor(COLORREF clr);
  BOOL SetInsertMark(HTREEITEM hItem, BOOL fAfter = TRUE);
  COLORREF GetInsertMarkColor() const;
  COLORREF SetInsertMarkColor(COLORREF clrNew);
  
// Operations
public:
  ~CTreeCtrlEx();
  CImageList* SetImageList(CImageList* pImageList, int nImageListType = TVSIL_NORMAL);

  CTreeCursor GetNextItem(HTREEITEM hItem, UINT nCode);
  CTreeCursor GetChildItem(HTREEITEM hItem);
  CTreeCursor GetNextSiblingItem(HTREEITEM hItem);
  CTreeCursor GetPrevSiblingItem(HTREEITEM hItem);
  CTreeCursor GetParentItem(HTREEITEM hItem);
  CTreeCursor GetFirstVisibleItem();
  CTreeCursor GetNextVisibleItem(HTREEITEM hItem);
  CTreeCursor GetPrevVisibleItem(HTREEITEM hItem);
  CTreeCursor GetSelectedItem();
  CTreeCursor GetDropHilightItem();
  CTreeCursor GetRootItem();
  CTreeCursor InsertItem(LPTVINSERTSTRUCT lpInsertStruct);
  CTreeCursor InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
    int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
    HTREEITEM hParent, HTREEITEM hInsertAfter);
  CTreeCursor InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, 
    HTREEITEM hInsertAfter = TVI_LAST);
  CTreeCursor InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
    HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
  CTreeCursor HitTest(CPoint pt, UINT* pFlags = NULL);
  CTreeCursor HitTest(TVHITTESTINFO* pHitTestInfo);
  HTREEITEM _InsertItem(LPTVINSERTSTRUCT lpInsertStruct);
  BOOL _GetItem(TVITEM* pItem) const;
  BOOL GetCheck(HTREEITEM hItem) const;
  BOOL SetCheck(HTREEITEM hItem, BOOL fCheck = TRUE);
};


#include "TreeCtrlEx.inl"

#endif //__TBCTL_H__

/////////////////////////////////////////////////////////////////////////////
