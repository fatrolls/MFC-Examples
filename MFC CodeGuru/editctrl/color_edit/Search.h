#if !defined(AFX_SEARCH_H__08C82341_4635_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_SEARCH_H__08C82341_4635_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Search.h : header file
//

#include "RegExp.h"
#include "ColorString.h"
#include "ColorEditDoc.h"
#include "ColorEditView.h"

/////////////////////////////////////////////////////////////////////////////
// CSearch dialog

class CSearch : public CDialog
{
// Construction
public:
	CSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSearch)
	enum { IDD = IDD_SEARCH };
	CEdit	m_search_ctrl;
	CButton	m_replaceBtn;
	CButton	m_findBtn;
	CString	m_replace_string;
	CString	m_search_string;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CRegExp				m_r;
	CColorString*		m_pString;
	CColorEditView*		m_view;

	// Generated message map functions
	//{{AFX_MSG(CSearch)
	afx_msg void OnFindNext();
	afx_msg void OnReplace();
	afx_msg void OnReplaceAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCH_H__08C82341_4635_11D1_B99D_00A0C9763A0A__INCLUDED_)
