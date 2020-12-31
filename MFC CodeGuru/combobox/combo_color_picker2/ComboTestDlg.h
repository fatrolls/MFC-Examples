// ComboTestDlg.h : header file
//

#if !defined(AFX_COMBOTESTDLG_H__6C1518E6_8FF0_11D1_B7B1_00A024DE65ED__INCLUDED_)
#define AFX_COMBOTESTDLG_H__6C1518E6_8FF0_11D1_B7B1_00A024DE65ED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ColorComboEx.h"

/////////////////////////////////////////////////////////////////////////////
// CComboTestDlg dialog

class CComboTestDlg : public CDialog
{
// Construction
public:
	CComboTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CComboTestDlg)
	enum { IDD = IDD_COMBOTEST_DIALOG };
	CColorComboEx	m_ColorCombo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComboTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOTESTDLG_H__6C1518E6_8FF0_11D1_B7B1_00A024DE65ED__INCLUDED_)
