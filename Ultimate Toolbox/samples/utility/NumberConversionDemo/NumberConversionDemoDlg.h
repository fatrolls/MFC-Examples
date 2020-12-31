// NumberConversionDemoDlg.h : header file
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

/////////////////////////////////////////////////////////////////////////////
// CNumberConversionDemoDlg dialog

class CNumberConversionDemoDlg : public CDialog
{
// Construction
public:
	CNumberConversionDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNumberConversionDemoDlg)
	enum { IDD = IDD_NUMBERCONVERSIONDEMO_DIALOG };
	CEdit	m_wndOutput;
	CEdit	m_wndInput;
	CEdit	m_wndRadixOut;
	CEdit	m_wndRadixIn;
	CSpinButtonCtrl	m_wndSpinOut;
	CSpinButtonCtrl	m_wndSpinIn;
	int		m_nBaseIn;
	int		m_nBaseOut;
	int		m_nRadixIn;
	int		m_nRadixOut;
	CString	m_sInput;
	CString	m_sOutput;
	BOOL	m_bSeparated;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumberConversionDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNumberConversionDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOtherIn();
	afx_msg void OnOtherOut();
	afx_msg void OnStandardIn();
	afx_msg void OnStandardOut();
	afx_msg void OnConvert();
	afx_msg void OnCopyIn();
	afx_msg void OnPastIn();
	afx_msg void OnCopyOut();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
