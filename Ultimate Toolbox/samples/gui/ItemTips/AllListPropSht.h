/////////////////////////////////////////////////////////////////////////////
// CAllListSheet

#include "StandardDlg.h"
#include "DerivedDlg.h"

class CAllListSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CAllListSheet)

// Construction
public:
	CAllListSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CAllListSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

	CStandardDlg m_standardPage;
	CDerivedDlg	m_derivedPage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllListSheet)
	//}}AFX_VIRTUAL
	afx_msg void OnAppAbout();

// Implementation
public:
	virtual ~CAllListSheet();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CAllListSheet)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
