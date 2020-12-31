// IsamSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIsamSelect dialog

class CIsamSelect : public CDialog
{
// Construction
public:
	CIsamSelect(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIsamSelect)
	enum { IDD = IDD_ISAM_SELECT };
	CString	m_strIsam;
	CString	m_strDirectory;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIsamSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIsamSelect)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
