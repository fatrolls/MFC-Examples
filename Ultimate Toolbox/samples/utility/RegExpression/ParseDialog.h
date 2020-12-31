#if !defined(AFX_PARSEDIALOG_H__5303F544_A729_11D3_AC52_0050BAAB46B1__INCLUDED_)
#define AFX_PARSEDIALOG_H__5303F544_A729_11D3_AC52_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParseDialog.h : header file
//

#include "OXRegExpression.h"
#include "MyRegular.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CParseDialog dialog

class CParseDialog : public CDialog
{
// Construction
public:
	CParseDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParseDialog)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_btnParse;
	CListCtrl	m_wndListResult;
	CString	m_sRule;
	CString	m_sInfo;
	//}}AFX_DATA
	CMyRegular m_reg;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParseDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParseDialog)
	afx_msg BOOL OnParse();
	afx_msg void OnChangeEditRule();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARSEDIALOG_H__5303F544_A729_11D3_AC52_0050BAAB46B1__INCLUDED_)
