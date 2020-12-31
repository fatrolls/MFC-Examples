#if !defined(AFX_MYLISTCTRL_H__60CB2B85_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
#define AFX_MYLISTCTRL_H__60CB2B85_E9A4_11D1_8855_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyListCtrl.h : header file
//

#include "OXItemTip.h"

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:

protected:
	BOOL m_bFirstTimeHooking;
	COXItemTip m_ItemTip;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	//}}AFX_MSG
	virtual LRESULT OnNeedItemTip(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__60CB2B85_E9A4_11D1_8855_0080C83F712F__INCLUDED_)
