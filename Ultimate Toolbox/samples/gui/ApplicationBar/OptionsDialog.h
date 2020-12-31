#if !defined(AFX_OPTIONSDIALOG_H__3F58E777_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_)
#define AFX_OPTIONSDIALOG_H__3F58E777_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDialog.h : header file
//
#include "ApplicationBarDlg.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsDialog dialog

class COptionsDialog : public CDialog
{
// Construction
public:
	void EnableApply(BOOL bApply=TRUE);
	UINT m_nEdge;
	COptionsDialog(CWnd* pParent = NULL);   // standard constructor
	CApplicationBarDlg m_appBar;
// Dialog Data
	//{{AFX_DATA(COptionsDialog)
	enum { IDD = IDD_DIALOG_OPTIONS };
	BOOL	m_bAutoHide;
	BOOL	m_bOnTop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDialog)
	afx_msg void OnRadioLeft();
	afx_msg void OnRadioTop();
	afx_msg void OnRadioRight();
	afx_msg void OnRadioBottom();
	afx_msg void OnApply();
	afx_msg void OnCheckAutohide();
	afx_msg void OnCheckOntop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDIALOG_H__3F58E777_C82D_11D3_AC76_0050BAAB46B1__INCLUDED_)
