// PizzaDlg.h : header file
//

#if !defined(AFX_PIZZADLG_H__36762C79_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
#define AFX_PIZZADLG_H__36762C79_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DBListBox.h"	// Added by ClassView
#include "ClientsRecordset.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CPizzaDlg dialog

class CPizzaDlg : public CDialog
{
// Construction
public:
	void DoDelivery( void );
	CClientsRecordset Clients;
	CDBListBox ClientsLB;
	void OnOK( void );
	void PopulateLB( void );
	CPizzaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPizzaDlg)
	enum { IDD = IDD_PIZZA_DIALOG };
	CString	m_SurName;
	CString	m_SecondName;
	CString	m_Address;
	CString	m_AddrNo;
	CString	m_Phone;
	CString	m_id;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPizzaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPizzaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddNew();
	afx_msg void OnDelete();
	afx_msg void OnClose();
	afx_msg void OnFind();
	afx_msg void OnChange();
	afx_msg void OnClear();
	afx_msg void OnSelchange();
	afx_msg void OnDblclkClientsLB();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIZZADLG_H__36762C79_0B4C_11D2_9BA2_967BD4D5D031__INCLUDED_)
