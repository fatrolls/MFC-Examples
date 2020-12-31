// TestHTMLHelpDlg.h : header file
//

#if !defined(AFX_TESTHTMLHELPDLG_H__8CE99828_B818_11D1_B855_444553540000__INCLUDED_)
#define AFX_TESTHTMLHELPDLG_H__8CE99828_B818_11D1_B855_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestHTMLHelpDlg dialog

class CTestHTMLHelpDlg : public CDialog
{
// Construction
public:
	CTestHTMLHelpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestHTMLHelpDlg)
	enum { IDD = IDD_TESTHTMLHELP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestHTMLHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestHTMLHelpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTHTMLHELPDLG_H__8CE99828_B818_11D1_B855_444553540000__INCLUDED_)
