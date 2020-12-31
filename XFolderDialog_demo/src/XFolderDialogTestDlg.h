// XFolderDialogTestDlg.h : header file
//

#ifndef XFOLDERDIALOGTESTDLG_H
#define XFOLDERDIALOGTESTDLG_H

/////////////////////////////////////////////////////////////////////////////
// CXFolderDialogTestDlg dialog

class CXFolderDialogTestDlg : public CDialog
{
// Construction
public:
	CXFolderDialogTestDlg(CWnd* pParent = NULL);	// standard constructor
	~CXFolderDialogTestDlg();

// Dialog Data
	//{{AFX_DATA(CXFolderDialogTestDlg)
	enum { IDD = IDD_XFOLDERDIALOGTEST_DIALOG };
	CStatic		m_IconXp;
	CStatic		m_IconVista;
	CStatic		m_IconOther;
	CComboBox	m_comboListViewMode;
	CStatic		m_Path;
	int			m_nOsVersion;
	int			m_nListViewModeIndex;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXFolderDialogTestDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON	m_hIcon;
	HICON	m_hGray, m_hGreen, m_hRed;
	BOOL	m_bUseRegistry;			// TRUE = read/write registry for list view mode
	BOOL	m_bPersist;				// TRUE = persist view

	CString m_strInitialFolder;

	struct LIST_VIEW_MODES
	{
		TCHAR *	pszMode;
		int		nMode;
	};

	static const LIST_VIEW_MODES m_XpModes[];
	static const LIST_VIEW_MODES m_VistaModes[];

	// Generated message map functions
	//{{AFX_MSG(CXFolderDialogTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCXFolderDialog();
	afx_msg void OnCFileDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XFOLDERDIALOGTESTDLG_H
