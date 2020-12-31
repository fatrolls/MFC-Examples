// InstanceManagerDemoDlg.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////
// CInstanceManagerDemoDlg dialog

class CInstanceManagerDemoDlg : public CDialog
{
// Construction
public:
	CInstanceManagerDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInstanceManagerDemoDlg)
	enum { IDD = IDD_INSTANCEMANAGERDEMO_DIALOG };
	CSpinButtonCtrl	m_wndMaxNumberSpin;
	CString	m_sTitle;
	int		m_nMaxNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstanceManagerDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	BOOL InitializeTitle();

	// Generated message map functions
	//{{AFX_MSG(CInstanceManagerDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCloseAll();
	afx_msg void OnSetTitle();
	afx_msg void OnChangeMaxNumber();
	//}}AFX_MSG
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
