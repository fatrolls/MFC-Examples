// AddrDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddrDialog dialog

class CAddrDialog : public CDialog
{
// Construction
public:
	CAddrDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddrDialog)
	enum { IDD = IDD_ADDRDIALOG };
	CString	m_strFile;
	CString	m_strServerName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddrDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddrDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
