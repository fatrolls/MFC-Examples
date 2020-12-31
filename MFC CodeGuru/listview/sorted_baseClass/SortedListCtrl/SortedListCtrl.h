#if !defined(AFX_SORTEDLISTCTRL_H__3D138C14_BE82_11D1_B971_ACBC3F000000__INCLUDED_)
#define AFX_SORTEDLISTCTRL_H__3D138C14_BE82_11D1_B971_ACBC3F000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SortedListCtrl.h : header file
//

#include "SortedHeaderCtrl.h"
#include "ItemInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CSortedListCtrl window

class CSortedListCtrl : public CListCtrl
{

public:
	CSortedListCtrl(BOOL EnableSorting = FALSE, BOOL DeleteItemData = FALSE);

	virtual ~CSortedListCtrl();

	// If Enable is true, the control will draw vertical lines 
	// between columns
	void EnableSeparatorLines (BOOL Enable);

	// Sort a column using given sorting order
	void SortColumn (int nCol, BOOL bAsc);

    // Resort the column currently sorted using the same order
    void ReSort();

	// Returns the sort order of the currently sorted column
	BOOL IsAscSorted ();

	// Returns the number of the currently sorted column
	// or NOT_SORTED if sorting has never been applied to any column
	int GetSortedColumn();

	static const int NOT_SORTED;

	BOOL SetFullRowSel(BOOL bFillRowSel);
	BOOL GetFullRowSel();

	BOOL m_bClientWidthSel;

protected:

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortedListCtrl)
	public:
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSortedListCtrl)
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	void RepaintSelectedItems();

	// Implementation - client area width
	int m_cxClient;

	// Implementation - state icon width
	int m_cxStateImageOffset;
	afx_msg LRESULT OnSetImageList(WPARAM wParam, LPARAM lParam);

	// Implementation - list view colors
	COLORREF m_clrText;
	COLORREF m_clrTextBk;
	COLORREF m_clrBkgnd;
	afx_msg LRESULT OnSetTextColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetTextBkColor(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetBkColor(WPARAM wParam, LPARAM lParam);

    static int CALLBACK CallbackCompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lParam3);
	virtual int CompareItems(CItemInfo *pItemInfo1, CItemInfo *pItemInfo2);
	void CSortedListCtrl::DrawSeparatorLines();

	CSortedHeaderCtrl m_HeaderCtrl;
	BOOL m_SeparatorLines;
	BOOL m_Sorting;
	BOOL m_bFullRowSel;
    BOOL m_bDeleteItemData;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SORTEDLISTCTRL_H__3D138C14_BE82_11D1_B971_ACBC3F000000__INCLUDED_)
