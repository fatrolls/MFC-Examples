#if !defined(AFX_MYLISTCTRL_H__CBAA6793_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
#define AFX_MYLISTCTRL_H__CBAA6793_F21D_11D1_9F9F_84E5D3000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyListCtrl.h : header file
//

#include "SortedListCtrl.h"
#include "MyItemInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

class CMyListCtrl : public CSortedListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyListCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListCtrl)
	    afx_msg void OnGetDispInfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	int CompareItems(CItemInfo *pItemInfo1, CItemInfo *pItemInfo2);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__CBAA6793_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
