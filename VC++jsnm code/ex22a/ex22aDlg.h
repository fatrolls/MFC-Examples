// ex22aDlg.h : header file
//

#if !defined(AFX_EX22ADLG_H__2CBCCCC9_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_)
#define AFX_EX22ADLG_H__2CBCCCC9_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CEx22aDlg dialog

class CEx22aDlg : public CDialog
{
// Construction
public:
	CEx22aDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEx22aDlg)
	enum { IDD = IDD_EX22A_DIALOG };
	double	m_dLeft;
	double	m_dRight;
	double	m_dResult;
	int		m_nOperation;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx22aDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEx22aDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCompute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX22ADLG_H__2CBCCCC9_98CE_11D0_BED3_00C04FC2A0C2__INCLUDED_)
