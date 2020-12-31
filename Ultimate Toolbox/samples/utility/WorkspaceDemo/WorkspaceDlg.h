// WorkspaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg dialog

class CWorkspaceDlg : public CDialog
{
// Construction
public:
	CWorkspaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkspaceDlg)
	enum { IDD = IDD_WORKSPACE_DLG };
	CString	m_sFilePath;
	int		m_nRegistryType;
	CString	m_sRegistry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWorkspaceDlg)
	afx_msg void OnBrowse();
	afx_msg void OnLoad();
	afx_msg void OnStore();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
