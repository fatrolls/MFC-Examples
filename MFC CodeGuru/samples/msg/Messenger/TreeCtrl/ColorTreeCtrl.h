#ifndef COLOR_TREE_CTRL_H
#define COLOR_TREE_CTRL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ColorTreeCtrl.h : header file
//

#ifndef __AFXTEMPL_H__
	#include <afxtempl.h>
#endif


#ifndef CUSTOM_TREE_CTRL_H
	#include "CustomTreeCtrl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorTreeCtrl window


class CColorTreeCtrl : public CCustomTreeCtrl
{
public:
	class CColorTreeItem
	{
	public:
		COLORREF Color;
		COLORREF ColorText;
		CString Text;

		LOGFONT *pLogFont;
	public:
		CColorTreeItem();
		CColorTreeItem(const CColorTreeItem &x);
		virtual ~CColorTreeItem();

		void RemoveFont();
		void SetFont(LOGFONT &logFont);

		CColorTreeItem &operator = (const CColorTreeItem &x);
	};

	class CColorTreeItemArray : public CArray<CColorTreeItem, CColorTreeItem &>
	{
	public:
		long Action;
	public:
		CColorTreeItemArray();
		CColorTreeItemArray &operator = (const CColorTreeItemArray &x);

		void DrawItem(CDC &cdc,CRect &crect,UINT nState,DWORD &dwWidth,BOOL isFocus);
		CString GetText();
	};

// Construction
public:
	CColorTreeCtrl();

// Attributes
public:
	CMap<void *, void *, CColorTreeItemArray, CColorTreeItemArray &> m_TreeItem;

// Operations
public:
	virtual CString GetToolTips(CTreeCursor &cursor,UINT nFlags);

	int AddText(CTreeCursor &cursor,LPCSTR str,COLORREF colorText = -1,COLORREF color = -1);
	void RemoveText(CTreeCursor &cursor);
	BOOL GetText(CTreeCursor &cursor,int index,CString &text);
	BOOL SetText(CTreeCursor &cursor,int index,LPCSTR text);

	BOOL GetAction(CTreeCursor &cursor,long &action);
	BOOL SetAction(CTreeCursor &cursor,long action);

	BOOL SetFont(CTreeCursor &cursor,int index,LOGFONT &logFont);

	BOOL GetColor(CTreeCursor &cursor,int index,COLORREF &colorText,COLORREF &color);
	BOOL SetColor(CTreeCursor &cursor,int index,COLORREF colorText,COLORREF color);

	void InvalidateRect(CTreeCursor &cursor);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorTreeCtrl)
	//}}AFX_VIRTUAL

// Overidables
protected:
	virtual BOOL DrawItem(CTreeCursor &htreeitem,CDC &cdc,
								CRect &crect,UINT nState,DWORD &dwWidth);
// Implementation
public:
	virtual ~CColorTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif
