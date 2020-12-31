// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __TREECTLX_H__
#define __TREECTLX_H__

#ifdef _AFX_NO_AFXCMN_SUPPORT
	#error Windows Common Control classes not supported in this library variant.
#endif

#ifndef __AFXWIN_H__
	#include <afxwin.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// TREECTLX - MFC Tree Control Helper Classes

class CTreeCursor;
class CTreeCtrlEx;


/////////////////////////////////////////////////////////////////////////////
// CTreeCursor

class CTreeCursor
{
	// Attributes
protected:
	HTREEITEM	m_hTreeItem;
	CTreeCtrlEx	*m_pTree;

	// Implementation
protected:
	CTreeCursor CTreeCursor::_Insert(LPCTSTR strItem,int nImageIndex,int nImageSelectedIndex,HTREEITEM hAfter);

	// Operation
public:
	CTreeCursor();
	CTreeCursor(HTREEITEM hTreeItem, CTreeCtrlEx* pTree);
	CTreeCursor(const CTreeCursor& posSrc);
	~CTreeCursor();
	const CTreeCursor& operator =(const CTreeCursor& posSrc);
	operator HTREEITEM();
	operator !();

	CTreeCursor InsertAfter(LPCTSTR strItem,HTREEITEM hAfter,int nImageIndex = -1,int nImageSelectedIndex = -1);
	CTreeCursor AddHead(LPCTSTR strItem,int nImageIndex = -1,int nImageSelectedIndex = -1);
	CTreeCursor AddTail(LPCTSTR strItem,int nImageIndex = -1,int nImageSelectedIndex = -1);

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
// Operations
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


	CTreeCursor Find(DWORD dwData);
	CTreeCursor Find(LPCSTR pData);

private:
	CTreeCursor Find(CTreeCursor cursor,DWORD dwData);
	CTreeCursor Find(CTreeCursor cursor,LPCSTR pData);
};


/////////////////////////////////////////////////////////////////////////////
// CTreeCtrlEx

class CTreeCtrlEx : public CTreeCtrl
{
	DECLARE_DYNAMIC(CTreeCtrlEx)

// Construction
public:
	CTreeCtrlEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeCtrlEx();
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
	CTreeCursor InsertItem(LPTV_INSERTSTRUCT lpInsertStruct);
	CTreeCursor InsertItem(UINT nMask, LPCTSTR lpszItem, int nImage, 
		int nSelectedImage,	UINT nState, UINT nStateMask, LPARAM lParam, 
		HTREEITEM hParent, HTREEITEM hInsertAfter);
	CTreeCursor InsertItem(LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, 
		HTREEITEM hInsertAfter = TVI_LAST);
	CTreeCursor InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage,
		HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	CTreeCursor HitTest(CPoint pt, UINT* pFlags = NULL);
	CTreeCursor HitTest(TV_HITTESTINFO* pHitTestInfo);

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeCtrlEx)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.


#include "TreeCtrlEx.inl"

#endif 
