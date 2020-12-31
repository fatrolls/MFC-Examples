// RegTestDlg.h : header file
//

#if !defined(AFX_REGTESTDLG_H__9DF82145_3F46_11D1_9FB1_444553540000__INCLUDED_)
#define AFX_REGTESTDLG_H__9DF82145_3F46_11D1_9FB1_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CRegTestDlg dialog

class CRegTestDlg : public CDialog
{
// Construction
public:
	CRegTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRegTestDlg)
	enum { IDD = IDD_REGTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRegTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGTESTDLG_H__9DF82145_3F46_11D1_9FB1_444553540000__INCLUDED_)
