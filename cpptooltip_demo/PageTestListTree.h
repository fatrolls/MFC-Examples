#if !defined(AFX_PAGETESTLISTTREE_H__A8496499_8BA4_4555_AACB_C2E13A4A5948__INCLUDED_)
#define AFX_PAGETESTLISTTREE_H__A8496499_8BA4_4555_AACB_C2E13A4A5948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTestListTree.h : header file
//
#include "PPTooltip.h"
#include "afxcmn.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CPageTestListTree dialog

class CPageTestListTree : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageTestListTree)

// Construction
public:
	CPPToolTip m_tooltip;
	CPageTestListTree();
	~CPageTestListTree();

// Dialog Data
	//{{AFX_DATA(CPageTestListTree)
	enum { IDD = IDD_PAGETEST_LIST_TREE };
	CComboBox	m_combo;
	CListCtrl m_list_ctrl;
	CListBox m_list_box;
	CTreeCtrl m_tree;
	int m_place_tip;
	BOOL m_balloon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageTestListTree)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;
	// Generated message map functions
	//{{AFX_MSG(CPageTestListTree)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePlacement();
	afx_msg void OnChangeTypeTitletip();
	//}}AFX_MSG
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETESTLISTTREE_H__A8496499_8BA4_4555_AACB_C2E13A4A5948__INCLUDED_)
