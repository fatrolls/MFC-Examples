// JPGtestDlg.h : header file
//

#if !defined(AFX_JPGTESTDLG_H__F8562DF9_85B7_11D1_A4E1_0020359647BF__INCLUDED_)
#define AFX_JPGTESTDLG_H__F8562DF9_85B7_11D1_A4E1_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CJPGtestDlg dialog

class CJPGtestDlg : public CDialog
{
// Construction
public:
	CJPGtestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CJPGtestDlg)
	enum { IDD = IDD_JPGTEST_DIALOG };
	CStatic	m_Time_Static;
	CString	m_sGraphicsFile;
	CString	m_sJPEGFile;
	BOOL	m_bGray;
	BOOL	m_bBase;
	BOOL	m_bProgr;
	BOOL	m_bOpt;
	UINT	m_nQuality;
	UINT	m_nSmooth;
	UINT	m_nMaxMem;
	int		m_nDCT;
	UINT	m_nColors;
	UINT	m_nMaxMem2;
	BOOL	m_bOnePass;
	BOOL	m_bGrayScale2;
	BOOL	m_bFast;
	BOOL	m_bNoSmooth;
	BOOL	m_bOS2;
	int		m_nDither;
	int		m_nScale;
	int		m_nDCT2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJPGtestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CJPGtestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGraphButton();
	afx_msg void OnJpgButton();
	afx_msg void OnCompress();
	afx_msg void OnUnCompress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPGTESTDLG_H__F8562DF9_85B7_11D1_A4E1_0020359647BF__INCLUDED_)
