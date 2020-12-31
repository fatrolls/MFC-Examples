#if !defined(_COOLTREEFOO_H__INCLUDED_)
#define _COOLTREEFOO_H__INCLUDED_


////////////////////////////////////////////////////////////////
// CCoolTreeCtrl 1997 by Rainer Pfitzner. 
// Compiles with Visual C++ 5.0 on Windows 95

//////////////////
// CCoolTreeCtrl encapsulates IE 4.0 common coolbar for MFC.
//
class CCoolTreeCtrl : public CWnd {
protected:
	DECLARE_DYNAMIC(CCoolTreeCtrl)

	// Operations
public:
	CCoolTreeCtrl();

	BOOL Create(DWORD dwStyle, CRect rect, CWnd* pParentWnd, UINT nID);

	HTREEITEM InsertItem( LPTV_INSERTSTRUCT lptvis)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HTREEITEM)SendMessage(TVM_INSERTITEM, (WPARAM)0, (LPARAM)lptvis); }

	BOOL DeleteAllItems()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_DELETEITEM, (WPARAM)0, (LPARAM)TVI_ROOT); }

	BOOL Expand(HTREEITEM hitem, UINT code)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_EXPAND, (WPARAM)code, (LPARAM)hitem); }

	HTREEITEM GetItemRect(HTREEITEM hItem, LPRECT prc, UINT code)
		{ ASSERT(::IsWindow(m_hWnd));
		*(HTREEITEM*)prc = hItem;
		  return (HTREEITEM)SendMessage(TVM_GETITEMRECT, (WPARAM)code, (LPARAM)prc); } 
	
	UINT GetIndent(int iCol)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (UINT)SendMessage(TVM_GETINDENT, (WPARAM)iCol, (LPARAM)0L); }

	BOOL SetIndent(int indent)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_SETINDENT, (WPARAM)indent, (LPARAM)0L); }
	
	UINT GetCount()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (UINT)SendMessage(TVM_GETCOUNT, (WPARAM)0, (LPARAM)0L); }
															
	HIMAGELIST SetImageList(HIMAGELIST himl, int iImage)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HIMAGELIST)SendMessage(TVM_SETIMAGELIST, (WPARAM)iImage, (LPARAM)himl); }

	HIMAGELIST SetImageList(CImageList* piml, int iImage)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HIMAGELIST)SendMessage(TVM_SETIMAGELIST, (WPARAM)iImage, (LPARAM)(HIMAGELIST)piml); }

	HIMAGELIST GetImageList()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HIMAGELIST)SendMessage(TVM_GETIMAGELIST, (WPARAM)0, (LPARAM)0L); }

	HTREEITEM GetNextItem(HTREEITEM hitem, UINT code)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HTREEITEM)SendMessage(TVM_GETNEXTITEM, (WPARAM)code, (LPARAM)hitem); }

	HTREEITEM SelectItem(HTREEITEM hitem, UINT code)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HTREEITEM)SendMessage(TVM_SELECTITEM, (WPARAM)code, (LPARAM)hitem); }
													
// TreeView_Select(hwnd, hitem, TVGN_CARET)
// TreeView_Select(hwnd, hitem, TVGN_DROPHILITE)
// TreeView_Select(hwnd, hitem, TVGN_FIRSTVISIBLE)

	BOOL GetItem( LPTVITEM pItem)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_GETITEM, (WPARAM)0, (LPARAM)pItem); }

	BOOL SetItem( LPTVITEM pItem)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_SETITEM, (WPARAM)0, (LPARAM)pItem); }

	HWND EditLabel(HTREEITEM hitem)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HWND)SendMessage(TVM_EDITLABEL, (WPARAM)0, (LPARAM)hitem); }

	HWND GetEditControl()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HWND)SendMessage(TVM_GETEDITCONTROL, (WPARAM)0, (LPARAM)0L); }

	UINT GetVisibleCount()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (UINT)SendMessage(TVM_GETVISIBLECOUNT, (WPARAM)0, (LPARAM)0L); }

	HTREEITEM HitTest(LPTVHITTESTINFO lphti)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (HTREEITEM)SendMessage(TVM_HITTEST, (WPARAM)0, (LPARAM)lphti); }

	BOOL SortChildren(HTREEITEM hitem, BOOL recurse)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_SORTCHILDREN, (WPARAM)recurse, (LPARAM)hitem); }

	BOOL EnsureVisible(HTREEITEM hitem)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_ENSUREVISIBLE, (WPARAM)0, (LPARAM)hitem); }

	BOOL SortChildrenCB(LPTV_SORTCB psort, BOOL recurse)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_SORTCHILDRENCB, (WPARAM)recurse, (LPARAM)psort); }

	BOOL EndEditLabelNow( BOOL fCancel)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_ENDEDITLABELNOW, (WPARAM)fCancel, (LPARAM)0L); }

	BOOL GetISearchString(LPCTSTR lpsz)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(TVM_GETISEARCHSTRING, (WPARAM)0, (LPARAM)lpsz); }

	COLORREF SetBkColor(COLORREF clr)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (COLORREF)SendMessage(TVM_SETBKCOLOR, (WPARAM)0, (LPARAM)clr); }

	COLORREF GetBkColor()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (COLORREF)SendMessage(TVM_GETBKCOLOR, (WPARAM)0, (LPARAM)0); }

	COLORREF SetTextColor(COLORREF clr)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (COLORREF)SendMessage(TVM_SETTEXTCOLOR, (WPARAM)0, (LPARAM)clr); }

	COLORREF GetTextColor()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (COLORREF)SendMessage(TVM_GETTEXTCOLOR, (WPARAM)0, (LPARAM)0); }

	UINT SetScrollTime(UINT uTime)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (UINT)SendMessage(TVM_SETSCROLLTIME, (WPARAM)0, (LPARAM)uTime); }

	UINT GetScrollTime()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (UINT)SendMessage(TVM_GETSCROLLTIME, (WPARAM)0, (LPARAM)0); }

	int SetBorder(DWORD dwFlags, int xBorder, int yBorder)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(TVM_SETBORDER, (WPARAM)dwFlags, (LPARAM)MAKELPARAM(xBorder, yBorder)); }

	int GetBorder()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(TVM_GETBORDER, (WPARAM)0, (LPARAM)0); }

	int SetItemHeight(int iHeight)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(TVM_SETITEMHEIGHT, (WPARAM)iHeight, (LPARAM)0); }

	int GetItemHeight()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(TVM_GETITEMHEIGHT, (WPARAM)0, (LPARAM)0); }


	HTREEITEM InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage,
					int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam,
					HTREEITEM hParent, HTREEITEM hInsertAfter);

	BOOL SetItem(HTREEITEM hItem, UINT nMask, LPCTSTR lpszItem, int nImage,
				int nSelectedImage, UINT nState, UINT nStateMask, LPARAM lParam);

	BOOL SetItemText(HTREEITEM hItem, LPCTSTR lpszText);

// ie4 added 6.may.98
	BOOL SetWorkAreas(int nWorkAreas, LPRECT prc)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(LVM_SETWORKAREAS, (WPARAM)nWorkAreas, (LPARAM)prc); }

	BOOL GetWorkAreas(int nWorkAreas, LPRECT prc)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(LVM_GETWORKAREAS, (WPARAM)nWorkAreas, (LPARAM)prc); }

	BOOL GetNumberOfWorkAreas(LPINT pnWorkAreas)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(LVM_GETNUMBEROFWORKAREAS, (WPARAM)0, (LPARAM)pnWorkAreas); }

	int GetSelectionMark()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(LVM_GETSELECTIONMARK, (WPARAM)0, (LPARAM)0L); }

	int SetSelectionMark(int i)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (int)SendMessage(LVM_SETSELECTIONMARK, (WPARAM)0, (LPARAM)i); }

	DWORD GetHoverTime()
		{ ASSERT(::IsWindow(m_hWnd));
		  return (DWORD)SendMessage(LVM_GETHOVERTIME, (WPARAM)0, (LPARAM)0L); }

	DWORD SetHoverTime(DWORD dwHoverTimeMs)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (DWORD)SendMessage(LVM_SETHOVERTIME, (WPARAM)0, (LPARAM)dwHoverTimeMs); }

	BOOL GetBkImage(LPLVBKIMAGE plvbki)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(LVM_GETBKIMAGE, (WPARAM)0, (LPARAM)plvbki); }

	BOOL SetBkImage(LPLVBKIMAGE plvbki)
		{ ASSERT(::IsWindow(m_hWnd));
		  return (BOOL)SendMessage(LVM_SETBKIMAGE, (WPARAM)0, (LPARAM)plvbki); }



	HTREEITEM HitTest(CPoint pt, UINT* pFlags = NULL) const;
	CString GetItemText(HTREEITEM hItem) const;
	BOOL GetItemImage(HTREEITEM hItem, int& nImage, int& nSelectedImage) const;
	UINT GetItemState(HTREEITEM hItem, UINT nStateMask) const;
	DWORD GetItemData(HTREEITEM hItem) const;
	BOOL ItemHasChildren(HTREEITEM hItem) const;
	CImageList* CreateDragImage(HTREEITEM hItem);

// Implementation
public:
	virtual ~CCoolTreeCtrl();	

protected:
	void RemoveImageList(int nImageList);

	// Generated message map functions
	//{{AFX_MSG(CCoolTreeCtrl)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //

