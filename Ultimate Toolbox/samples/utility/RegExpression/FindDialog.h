#if !defined(AFX_FINDDIALOG_H__390D85A1_9E9C_11D3_AC4A_0050BAAB46B1__INCLUDED_)
#define AFX_FINDDIALOG_H__390D85A1_9E9C_11D3_AC4A_0050BAAB46B1__INCLUDED_

#include "OXRegExpression.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FindDialog.h : header file
//
#include "OXHistoryCombo.h"
#include "MyRegular.h"
 
const int ACTION_CANCEL=1;
const int ACTION_CONTINUE=2;

/////////////////////////////////////////////////////////////////////////////
// CFindDialog dialog

class CFindDialog : public CDialog
{
// Construction
public:
	CEditView* m_pView;
	int m_nStartSearch;
	CMyRegular m_reg;
	CFindDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindDialog)
	enum { IDD = IDD_DIALOG_FIND };
	CListCtrl	m_lstResult;
	COXHistoryCombo	m_cmbHistory;
	BOOL	m_bFocus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFindDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnFindButton();
	afx_msg void OnItemchangedListResult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListResult(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDDIALOG_H__390D85A1_9E9C_11D3_AC4A_0050BAAB46B1__INCLUDED_)
