#if !defined(AFX_HTMLLISTCTRL_H__AC7C4049_9583_405D_9CBD_9F89E5C909BB__INCLUDED_)
#define AFX_HTMLLISTCTRL_H__AC7C4049_9583_405D_9CBD_9F89E5C909BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HTMLListCtrl.h : header file
//
//	Written by Manoj Subberwal (Monty) email : xMonty@gmail.com
//	copyright 2005-2006

// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage caused through use.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "DrawHTML.h"
#include <AfxTempl.h>


#define DEFAULT_STYLES				WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP

#define HTMLLIST_STYLE_CHECKBOX		1	
#define HTMLLIST_STYLE_GRIDLINES	2
#define HTMLLIST_STYLE_IMAGES		4

#define INVALID_ITEM	-1

//Item Types
#define HTML_TEXT			1
#define NORMAL_TEXT			2
#define SINGLE_LINE_TEXT	3
//end

//Calculate Item height Automatically
#define AUTO	0

//Padding between items
#define ITEM_PADDING_TOP			5
#define ITEM_PADDING_BOTTOM			5
#define ITEM_PADDING_LEFT			5	//if check box then after checkbox padding

#define ITEM_PADDING_CHECKBOX_LEFT	3

#define ITEM_IMAGE_PADDING_LEFT		5
#define ITEM_IMAGE_PADDING_RIGHT	5

#define ITEM_CHECKBOX_WIDTH			16

//for selection
#define NONE_SELECTED		-1

//Events
#define HTMLLIST_SELECTIONCHANGED	1
#define HTMLLIST_LBUTTONDOWN		2
#define HTMLLIST_RBUTTONDOWN		3
#define HTMLLIST_LBUTTONDBLCLICK	4
#define HTMLLIST_ITEMCHECKED		5

/////////////////////////////////////////////////////////////////////////////
// CHTMLListCtrl window
struct NM_HTMLLISTCTRL
{
	NMHDR hdr;
	int nItemNo;
	CString sItemText;
	LPARAM lItemData;
	BOOL bChecked;
};
struct HTMLLIST_ITEM
{
	HTMLLIST_ITEM()
	{
		nItemNo = INVALID_ITEM;
		lItemData = 0;
		nHeight = 0;
		nStyle = NORMAL_TEXT;
		rcItem.SetRectEmpty();
		bChecked = FALSE;
		bHeightSpecified = FALSE;
	}

	int			nItemNo;
	int			nHeight;
	int			nStyle;
	CString		sItemText;
	LPARAM		lItemData;
	CRect		rcItem;
	BOOL		bChecked;
	BOOL		bHeightSpecified;
	UINT		uiImage;
};

class CHTMLListCtrl : public CWnd
{
// Construction
public:
	CHTMLListCtrl();

// Attributes
private:
	HTMLLIST_ITEM * GetInternalData(int nPos);
	CRect GetItemRect(int nPos);
	int CalculateItemHeight(CString sText,int nStyle,UINT uiImage,int nWidth);

	CList<HTMLLIST_ITEM*,HTMLLIST_ITEM*> m_listItems;
	CMap<int,int,HTMLLIST_ITEM*,HTMLLIST_ITEM*> m_mapItems;
	int m_nTotalItems;

	//Controls id
	UINT	m_nControlID;
	//List Height (Not the actual window height)
	int m_nListHeight;

	//Actual window width
	int m_nWndWidth;
	int m_nWndHeight;

	//GDI stuff
	CFont		 m_font;
	CPen		 m_penLight;
	COLORREF	 m_clrBkSelectedItem;
	
	//selected item
	int m_nSelectedItem;

	//
	BOOL m_bHasFocus;

	//
	DWORD m_dwExtendedStyles;

	//
	CImageList m_ImageList;
	CImageList *m_pImageList;
// Operations
public:
	int	GetItemCount()
	{
		return m_listItems.GetCount();
	}
	void SetImageList(CImageList *pImageList)
	{
		m_pImageList = pImageList;
	}
	CImageList* GetImageList()
	{
		return m_pImageList;
	}
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHTMLListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetInternalData(int nPos,HTMLLIST_ITEM *pData);
	BOOL IsRectVisible(CRect rcClipBox,CRect rcItem);
	void SendCheckStateChangedNotification(int nPos);
	void SendSelectionChangeNotification(int nPos);
	virtual void DrawItem(CDC *pDC,CRect rcItem, HTMLLIST_ITEM *pItem, BOOL bSelected);
	void SetImage(int nPos,UINT uiImage);
	UINT GetImage(int nPos);
	void ReArrangeWholeLayout();
	void ReArrangeItems();
	BOOL DeleteItem(int nPos);
	void SetItemText(int nPos,CString sItemText,BOOL bCalculateHeight = FALSE);
	BOOL GetItemCheck(int nPos);
	void SetItemCheck(int nPos,BOOL bChecked = TRUE);
	void EnsureVisible(int nPos);
	DWORD GetExtendedStyle();
	void SetExtendedStyle(DWORD dwExStyle);
	CString GetItemText(int nPos);
	int GetSelectedItem();
	void SetItemData(int nPos,LPARAM lItemData);
	LPARAM GetItemData(int nPos);
	void DeleteAllItems();

	int InsertItem(CString sText,UINT uiImage,int nStyle=HTML_TEXT,int nHeight=AUTO);

	BOOL Create(CWnd *pParent,CRect rc,UINT nID,DWORD dwStyle=DEFAULT_STYLES);
	virtual ~CHTMLListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHTMLListCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	afx_msg BOOL OnMouseWheel( UINT nFlags, short zDelta, CPoint pt );
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLLISTCTRL_H__AC7C4049_9583_405D_9CBD_9F89E5C909BB__INCLUDED_)
