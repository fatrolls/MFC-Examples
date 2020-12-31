// KillHRDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKillHRDlg dialog

class CKillHRDlg : public CDialog
{
// Construction
public:
	CKillHRDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKillHRDlg)
	enum { IDD = IDD_KILLHR_DIALOG };
	CEdit	m_editFileName;
	CButton	m_btnGo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKillHRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON    m_hIcon;
   CString  m_strFileName;

   void StripHardReturns(CString strFileName);
   BOOL FileExists(CString strFileName);

	// Generated message map functions
	//{{AFX_MSG(CKillHRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnGoClick();
	afx_msg void OnChangeEditFileName();
	//}}AFX_MSG

   afx_msg void OnDropFiles(HDROP hDropInfo);

	DECLARE_MESSAGE_MAP()
};
