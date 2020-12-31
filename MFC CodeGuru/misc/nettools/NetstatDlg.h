// NetstatDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg dialog

class CNetstatDlg : public CDialog
{
// Construction
public:
	CInetThreadParms *m_lpInetParms;
	CNetstatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetstatDlg)
	enum { IDD = IDD_NETSTAT_DIALOG };
	BOOL	m_connections;
	BOOL	m_icmpstats;
	BOOL	m_ifstats;
	BOOL	m_ipstats;
	BOOL	m_routes;
	BOOL	m_tcpstats;
	BOOL	m_udpstats;
	BOOL	m_all;
	BOOL	m_resolve;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetstatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetstatDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
