#ifndef CUSTOM_TREE_CTRL_H
#define CUSTOM_TREE_CTRL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomTreeCtrl.h : header file
//

#ifndef TOOL_TIPS_TREE_CTRL_H
	#include "ToolTipsTreeCtrl.h"
#endif


/////////////////////////////////////////////////////////////////////////////
// CCustomTreeCtrl window
class CCustomTreeCtrl : public CToolTipsTreeCtrl
{

// Construction
public:
	CCustomTreeCtrl();

// Attributes
public:

// Operations
public:

// Overidables
protected:
	virtual BOOL DrawItem(CTreeCursor &hTreeItem,CDC &cdc,
								CRect &crect,UINT nState,DWORD &dwWidth);

	virtual void SetItemWidth(CTreeCursor &hTreeItem,CDC &cdc,DWORD dwWidth);
// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTreeCtrl)
	//}}AFX_VIRTUAL


// Implementation
public:
	virtual ~CCustomTreeCtrl();


// Implementation Member Variables
private:	
	BOOL	m_bNoPaint;
	CTreeCursor m_hSelItem;

	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomTreeCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////



//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTREECTRL_H__4CAC5D55_C2EB_11D1_B7DA_0060084C3BF4__INCLUDED_)
