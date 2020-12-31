#if !defined(AFX_OPTIONSDLG_H__DBF9C2B5_E4CD_11D3_98F4_204C4F4F5020__INCLUDED_)
#define AFX_OPTIONSDLG_H__DBF9C2B5_E4CD_11D3_98F4_204C4F4F5020__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsDlg.h : header file
//

#include "OXWABook.h"

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

class COptionsDlg : public CDialog
{
// Construction
public:
	CString m_sEdit3;
	CString m_sEdit2;
	CString m_sEdit1;
	int m_nSel3;
	int m_nSel2;
	int m_nSel1;
	void UpdateControls();
	BOOL IsThirdEnabled();
	BOOL IsSecondEnabled();
	BOOL IsFirstEnabled();
	COptionsDlg(CWnd* pParent = NULL);   // standard constructor
	tOXWABOptions m_options;

// Dialog Data
	//{{AFX_DATA(COptionsDlg)
	enum { IDD = IDD_DIALOG_BROWSE };
	CEdit	m_edt3;
	CEdit	m_edt2;
	CEdit	m_edt1;
	CComboBox	m_cmb3;
	CComboBox	m_cmb2;
	CComboBox	m_cmb1;
	CString	m_sCaption;
	CString	m_sDest;
	CString	m_sEntry;
	BOOL	m_bChk1;
	BOOL	m_bChk2;
	BOOL	m_bChk3;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bDefault;

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnRadioDefault();
	afx_msg void OnRadioCustom();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeCombo3();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSDLG_H__DBF9C2B5_E4CD_11D3_98F4_204C4F4F5020__INCLUDED_)
