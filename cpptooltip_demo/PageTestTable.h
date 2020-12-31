#if !defined(AFX_PAGETESTTABLE_H__32CD5C3A_47B6_497A_BF9B_DAABEC672EF2__INCLUDED_)
#define AFX_PAGETESTTABLE_H__32CD5C3A_47B6_497A_BF9B_DAABEC672EF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTestTable.h : header file
//
#include "PPTooltip.h"
/////////////////////////////////////////////////////////////////////////////
// CPageTestTable dialog

class CPageTestTable : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageTestTable)

// Construction
public:
	CPPToolTip m_tooltip;
	CPageTestTable();
	~CPageTestTable();

// Dialog Data
	//{{AFX_DATA(CPageTestTable)
	enum { IDD = IDD_PAGETEST_TABLE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageTestTable)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageTestTable)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETESTTABLE_H__32CD5C3A_47B6_497A_BF9B_DAABEC672EF2__INCLUDED_)
