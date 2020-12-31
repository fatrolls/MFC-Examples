// demoDlg.h : header file
//

#if !defined(AFX_DEMODLG_H__922E95E7_B158_11D1_A9C2_7AAF7E000000__INCLUDED_)
#define AFX_DEMODLG_H__922E95E7_B158_11D1_A9C2_7AAF7E000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDao.h"


/////////////////////////////////////////////////////////////////////////////
// CDemoDlg dialog

class CDemoDlg : public CDialog
{
// Construction
public:
	CDemoDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data

	COXDao m_dao;
	BOOL m_add;
	BOOL m_isDirty;

	//{{AFX_DATA(CDemoDlg)
	enum { IDD = IDD_DEMO_DIALOG };
	CEdit	m_ctlEditPhone;
	CEdit	m_ctlEditLastName;
	CEdit	m_ctlEditFirstName;
	CEdit	m_ctlEditEmail;
	CEdit	m_ctlEditDate;
	CEdit	m_ctlEditCustnum;
	CEdit	m_ctlEditCompany;
	CEdit	m_ctlEditBalance;
	CString	m_sBalance;
	CString	m_sCompany;
	CString	m_sCustnum;
	CString	m_sDate;
	CString	m_sEmail;
	CString	m_sFirstName;
	CString	m_sLastName;
	CString	m_sPhone;
	BOOL	m_bOldCustomer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

	void LoadRecord();
	void SaveRecord();
	void ClearDialog();

	CString GetAppDir();

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnFirst();
	afx_msg void OnNext();
	afx_msg void OnPrev();
	afx_msg void OnLast();
	afx_msg void OnSave();
	afx_msg void OnChange(UINT nParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMODLG_H__922E95E7_B158_11D1_A9C2_7AAF7E000000__INCLUDED_)
