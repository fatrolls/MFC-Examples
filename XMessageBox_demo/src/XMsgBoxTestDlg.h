// XsgBoxTestDlg.h : header file
//

#ifndef XMSGBOXTESTDLG_H
#define XMSGBOXTESTDLG_H

#include "XMessageBox.h"

/////////////////////////////////////////////////////////////////////////////
// CXMsgBoxTestDlg dialog

class CXMsgBoxTestDlg : public CDialog
{
// Construction
public:
	CXMsgBoxTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXMsgBoxTestDlg)
	enum { IDD = IDD_MSGBOXTEST_DIALOG };
	CButton	m_radLanguage;
	CButton	m_chkNoSound;
	CButton	m_chkRightJustify;
	CButton	m_chkCustomButtons;
	CButton m_chkCustomIcon;
	CButton	m_chkReport;
	CButton	m_chkYesToAll;
	CButton	m_chkNoToAll;
	CButton	m_chkHelp;
	CButton	m_radDontAsk;
	CButton	m_radButton;
	CStatic	m_stcResult;
	CButton	m_radString;
	CButton	m_radIcon;
	CButton	m_radDefButton;
	int		m_nDefButton;
	int		m_nIcon;
	int		m_nString;
	int		m_nButton;
	int		m_nDontAsk;
	int		m_nLanguage;
	int		m_nTimeout;
	int		m_nDisabled;
	BOOL	m_bVistaStyle;
	BOOL	m_bNarrow;
	CString	m_strHelpContextId;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXMsgBoxTestDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	XMESSAGEBOX_REPORT_FUNCTION m_lpReportFunc;
	BOOL m_bRightJustify;
	int XMsgBox(UINT uType);
	void DisplayResult(int nResult, BOOL bReadFromRegistry);
	BOOL GetOptions(CString& strText, UINT *pnButton, UINT *pnDefButton, 
		UINT *pnIcon, UINT *pnDontAsk, UINT *pnHelpId, CString& strCustomButtons,
		int *pnTimeout, int  *pnDisabled, UINT * pnIdIcon);

	// Generated message map functions
	//{{AFX_MSG(CXMsgBoxTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnWindowsMessageBox();
	afx_msg void OnXMessageBox();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOnlineHelp();
	afx_msg void OnGallery();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XMSGBOXTESTDLG_H
