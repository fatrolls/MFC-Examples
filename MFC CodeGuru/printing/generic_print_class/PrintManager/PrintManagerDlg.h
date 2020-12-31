// PrintManagerDlg.h : header file
//

#if !defined(AFX_PRINTMANAGERDLG_H__8BEC3136_9E36_11D1_8BB1_0000B43382FE__INCLUDED_)
#define AFX_PRINTMANAGERDLG_H__8BEC3136_9E36_11D1_8BB1_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPrintManagerDlg dialog

class CPrintManagerDlg : public CDialog
{
// Construction
public:
	void PopulateList();
	CPrintManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintManagerDlg)
	enum { IDD = IDD_PRINTMANAGER_DIALOG };
	CListCtrl	wndList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintManagerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPrintManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTMANAGERDLG_H__8BEC3136_9E36_11D1_8BB1_0000B43382FE__INCLUDED_)
