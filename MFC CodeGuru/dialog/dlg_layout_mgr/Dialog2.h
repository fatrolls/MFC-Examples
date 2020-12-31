#if !defined(AFX_DIALOG2_H__C7662C62_E9CF_11D1_8034_4854E82A1622__INCLUDED_)
#define AFX_DIALOG2_H__C7662C62_E9CF_11D1_8034_4854E82A1622__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Dialog2.h : header file
//

#include "DialogMgr.h"

/////////////////////////////////////////////////////////////////////////////
// Dialog2 dialog

class Dialog2 : public CDialogMgr
{
// Construction
public:
	DECLARE_LAYOUT();

	Dialog2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Dialog2)
	enum { IDD = IDD_DIALOG1 };
	CTabCtrl	m_tab;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Dialog2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Dialog2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG2_H__C7662C62_E9CF_11D1_8034_4854E82A1622__INCLUDED_)
