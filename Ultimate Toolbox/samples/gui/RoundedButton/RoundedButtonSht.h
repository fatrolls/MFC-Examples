#include "RoundedButtonDlg.h"
#include "RoundedButtonSamplesDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CRoundedButtonSheet

class CRoundedButtonSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CRoundedButtonSheet)

// Construction
public:
	CRoundedButtonSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, 
		UINT iSelectPage = 0);
	CRoundedButtonSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, 
		UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:
	CRoundedButtonDlg roundedButtonCustomize;
	CRoundedButtonSamplesDlg roundedButtonSamples;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRoundedButtonSheet)
	//}}AFX_VIRTUAL
	afx_msg void OnAppAbout();

// Implementation
public:
	virtual ~CRoundedButtonSheet();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CRoundedButtonSheet)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
