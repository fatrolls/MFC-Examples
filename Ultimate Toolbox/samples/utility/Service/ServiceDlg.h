// ServiceDlg.h : header file
//

#if !defined(AFX_SERVICEDLG_H__E906DAA6_18DB_11D1_B900_444553540000__INCLUDED_)
#define AFX_SERVICEDLG_H__E906DAA6_18DB_11D1_B900_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXIteratorService.h"

/////////////////////////////////////////////////////////////////////////////
// CServiceDlg dialog

class CServiceDlg : public CDialog
{
// Construction
public:
	CServiceDlg(CWnd* pParent = NULL);	// standard constructor
	 ~CServiceDlg();

// Dialog Data
	//{{AFX_DATA(CServiceDlg)
	enum { IDD = IDD_SERVICE_DIALOG };
	CListBox	m_ctrlListService;
	CListBox	m_ctrlListAction;
	CString	m_sDisplayName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServiceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString BarToCR(LPCTSTR sIn);
	void UpdateServiceList();
	void ReportIfFail(BOOL bReturn);
	void OutputDword(DWORD dwOut, int nActionCode);
	void OutputString(LPCTSTR sOut);
	void OutputStatus(LPSERVICE_STATUS lpss);
	BOOL Confirm();
	HICON m_hIcon;
	COXIteratorService m_itersrv;
	COXIteratorService m_itersrvLast;

	// Generated message map functions
	//{{AFX_MSG(CServiceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDblclkListAction();
	afx_msg void OnDblclkListService();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVICEDLG_H__E906DAA6_18DB_11D1_B900_444553540000__INCLUDED_)
