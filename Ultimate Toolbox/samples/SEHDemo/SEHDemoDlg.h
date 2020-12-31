// SEHDemoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSEHDemoDlg dialog

class CSEHDemoDlg : public CDialog
{
// Construction
public:
	CSEHDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSEHDemoDlg)
	enum { IDD = IDD_SEHDEMO_DIALOG };
	CButton	m_wndFPTrap;
	CButton	m_wndTrap;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSEHDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSEHDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAccessViolation();
	afx_msg void OnTrap();
	afx_msg void OnZeroFloat();
	afx_msg void OnZeroInteger();
	afx_msg void OnTrapFl();
	afx_msg void OnBreakpoint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
