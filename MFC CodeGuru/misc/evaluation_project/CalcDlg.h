/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Klasse:			CCalcDlg
 *
 ****************************************************************************/

class CCalcDlg : public CDialog
{
// Construction
public:
	CCalcDlg(CWnd* pParent = NULL);	// standard constructor
	void Variable();

// Dialog Data
	//{{AFX_DATA(CCalcDlg)
	enum { IDD = IDD_CALC_DIALOG };
	CListBox	m_ergCtrl;
	CListBox	m_varCtrl;
	CComboBox	m_eingabeCtrl;
	CString	m_eingabe;
	CString	m_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
