// AddressBookDlg.h : header file
//

#if !defined(AFX_ADDRESSBOOKDLG_H__4FD8257C_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_)
#define AFX_ADDRESSBOOKDLG_H__4FD8257C_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXWABook.h"
#include "OptionsDlg.h"
#include "utsampleabout.h"

/////////////////////////////////////////////////////////////////////////////
// CAddressBookDlg dialog

typedef enum{
	E_EMAIL=0,
		E_NAME
}E_ABENUM;

class CAddressBookDlg : public CDialog
{
// Construction
public:
	BOOL FillUserProperties(COXMailUser* pUser);
	COXMailUser* GetUser();
	COptionsDlg m_dlgOpt;
	void PopulateList(COXMailUser* pUser, BOOL bList=FALSE);
	CAddressBookDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAddressBookDlg)
	enum { IDD = IDD_ADDRESSBOOK_DIALOG };
	CListCtrl	m_lstResults;
	CString	m_sLDAP;
	int		m_nSearchBy;
	CString	m_sEmail;
	CString	m_sName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddressBookDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COXWABook m_ABook;

	// Generated message map functions
	//{{AFX_MSG(CAddressBookDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonCreate();
	afx_msg void OnButtonEdit();
	afx_msg void OnButtonFinddialog();
	afx_msg void OnButtonLdap();
	afx_msg void OnButtonDelete();
	afx_msg void OnButtonAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRESSBOOKDLG_H__4FD8257C_E3AD_11D3_ACA4_0050BAAB46B1__INCLUDED_)
