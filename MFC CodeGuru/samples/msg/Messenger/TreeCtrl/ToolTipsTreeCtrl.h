#ifndef TOOL_TIPS_TREE_CTRL_H
#define TOOL_TIPS_TREE_CTRL_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ToolTipsTreeCtrl.h : header file
//

#ifndef __MULTISELTREECTRL_H
	#include "MultiSelTreeCtrl.h"
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolTipsTreeCtrl window

class CToolTipsTreeCtrl : public CMultiSelTreeCtrl
{
// Construction
public:
	CToolTipsTreeCtrl();

// Attributes
public:

// Operations
public:
	virtual CString GetToolTips(CTreeCursor &cursor,UINT nFlags);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipsTreeCtrl)
	public:
	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolTipsTreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipsTreeCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText( UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif 
