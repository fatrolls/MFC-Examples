// PingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog

class CPingDlg : public CDialog
{
// Construction
public:
	CPingThreadParmList *m_lpPingParms;
	CPingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPingDlg)
	enum { IDD = IDD_PING_DIALOG };
	CString	m_ping_hostname;
	BOOL	m_ping_opt_resolve;
	UINT	m_ping_opt_ttl_val;
	BOOL	m_ping_opt_dontfragment;
	UINT	m_ping_opt_packetlen_val;
	UINT	m_ping_opt_numpackets_val;
	UINT	m_ping_opt_rroute_val;
	UINT	m_ping_opt_timestamp_val;
	BOOL	m_ping_opt_interrupt;
	BOOL	m_ping_opt_tos_high_reliab;
	BOOL	m_ping_opt_tos_high_thru;
	BOOL	m_ping_opt_tos_low_delay;
	BOOL	m_ping_opt_tos_none;
	UINT	m_ping_opt_timeout_val;
	BOOL	m_ping_opt_rrloose;
	BOOL	m_ping_opt_rrstrict;
	CString	m_ping_opt_routes;
	BOOL	m_ping_opt_tracert;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPingDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPingOptTosNone();
	afx_msg void OnPingOptTosHighReliab();
	afx_msg void OnPingOptTosHighThru();
	afx_msg void OnPingOptTosLowDelay();
	afx_msg void OnPingOptRrloose();
	afx_msg void OnPingOptRrstrict();
	afx_msg void OnChangePingOptRVal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};
