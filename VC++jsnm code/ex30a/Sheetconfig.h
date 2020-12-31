// SheetConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageServer dialog

class CPageServer : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageServer)

// Construction
public:
	CPageServer();
	~CPageServer();

// Dialog Data
	//{{AFX_DATA(CPageServer)
	enum { IDD = IDD_PROPPAGE_SERVER };
	CString	m_strDirect;
	UINT	m_nPortServer;
	CString	m_strDefault;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageServer)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CPageAdv dialog

class CPageAdv : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAdv)

// Construction
public:
	CPageAdv();
	~CPageAdv();

// Dialog Data
	//{{AFX_DATA(CPageAdv)
	enum { IDD = IDD_PROPPAGE_ADV };
	CString	m_strIPServer;
	CString	m_strIPClient;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAdv)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAdv)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CPageClient dialog

class CPageClient : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageClient)

// Construction
public:
	CPageClient();
	~CPageClient();

// Dialog Data
	//{{AFX_DATA(CPageClient)
	enum { IDD = IDD_PROPPAGE_CLIENT };
	CString	m_strProxy;
	CString	m_strServerIP;
	CString	m_strServerName;
	BOOL	m_bUseProxy;
	CString	m_strFile;
	UINT	m_nPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageClient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageClient)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CSheetConfig

class CSheetConfig : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheetConfig)

// Construction
public:
	CSheetConfig(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheetConfig(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

public:
	CPageAdv m_pageAdv;
	CPageClient m_pageClient;
	CPageServer m_pageServer;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSheetConfig)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSheetConfig();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSheetConfig)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
