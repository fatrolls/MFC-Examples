// DialogsplDlg.h : header file
//

#if !defined(AFX_DIALOGSPLDLG_H__0B145F26_A61A_11D1_ABA0_442100C10000__INCLUDED_)
#define AFX_DIALOGSPLDLG_H__0B145F26_A61A_11D1_ABA0_442100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDialogsplDlg dialog

class CDialogsplDlg : public CDialog
{
// Construction
public:
	CDialogsplDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogsplDlg)
	enum { IDD = IDD_DIALOGSPL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogsplDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDialogsplDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGSPLDLG_H__0B145F26_A61A_11D1_ABA0_442100C10000__INCLUDED_)
