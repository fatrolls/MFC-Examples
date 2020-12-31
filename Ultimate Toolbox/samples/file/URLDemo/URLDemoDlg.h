// URLDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CURLDemoDlg dialog

class CURLDemoDlg : public CDialog
{
// Construction
public:
	CURLDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CURLDemoDlg)
	enum { IDD = IDD_URLDEMO_DIALOG };
	CString	m_sBaseName;
	CString	m_sDirectory;
	CString	m_sExtension;
	CString	m_sFile;
	int		m_nPort;
	CString	m_sProtocol;
	CString	m_sServer;
	CString	m_sShare;
	CString	m_sURL_UNC;
	BOOL	m_bURLPart;
	BOOL	m_bIncludeDirs;
	BOOL	m_bIncludeFiles;
	BOOL	m_bRecursive;
	BOOL	m_bDepthFirst;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURLDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CURLDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCombineURL();
	afx_msg void OnSplitURL();
	afx_msg void OnTest();
	afx_msg void OnCombineUNC();
	afx_msg void OnSplitUNC();
	afx_msg void OnList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
