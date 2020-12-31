// MailSendDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMailSendDlg dialog

class CMailSendDlg : public CDialog
{
// Construction
public:
	CMailSendDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMailSendDlg)
	enum { IDD = IDD_MAILSEND_DIALOG };
	CListBox	m_lbAttachments;
	CString	m_sAddress;
	CString	m_sContent;
	CString	m_sPassword;
	CString	m_sProfile;
	CString	m_sSubject;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailSendDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMailSendDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSendMail();
	afx_msg void OnAbout();
	afx_msg void OnButtonAddattachment();
	afx_msg void OnButtonRemoveattachment();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
