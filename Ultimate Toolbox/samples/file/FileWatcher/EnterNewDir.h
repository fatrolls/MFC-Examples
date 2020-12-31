// EnterNewDir.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEnterNewDir dialog

class CEnterNewDir : public CDialog
{
// Construction
public:
	CEnterNewDir(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnterNewDir)
	enum { IDD = IDD_ENTER_DIR };
	BOOL	m_bChangeAttributes;
	BOOL	m_bChangeCreation;
	BOOL	m_bChangeDirName;
	BOOL	m_bChangeFileName;
	BOOL	m_bChangeLastAccess;
	BOOL	m_bChangeLastWrite;
	BOOL	m_bChangeSecurity;
	BOOL	m_bChangeSize;
	CString	m_sDir;
	BOOL	m_bSubTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnterNewDir)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnterNewDir)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
