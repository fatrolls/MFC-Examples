#if !defined(AFX_PROPERTYPAGELISTTREE_H__3696ECE8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_PROPERTYPAGELISTTREE_H__3696ECE8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropertyPageListTree.h : header file
//

#include "OXCoolCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CPropertyPageListTree dialog

class CPropertyPageListTree : public CPropertyPage
{
	DECLARE_DYNCREATE(CPropertyPageListTree)

// Construction
public:
	CPropertyPageListTree();
	~CPropertyPageListTree();

// Dialog Data
	//{{AFX_DATA(CPropertyPageListTree)
	enum { IDD = IDD_DIALOG_LISTTREE };
	COXCoolCtrl<CTreeCtrl>	m_tree;
	COXCoolCtrl<CListCtrl>	m_list;
	COXCoolCtrl<CListBox>	m_listbox;
	COXCoolButton	m_btnDisable;
	BOOL	m_bDisable;
	//}}AFX_DATA
	CImageList m_il;


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPropertyPageListTree)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPropertyPageListTree)
	afx_msg void OnCheckDisableAll();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYPAGELISTTREE_H__3696ECE8_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
