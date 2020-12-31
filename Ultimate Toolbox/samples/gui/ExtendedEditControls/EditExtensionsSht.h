/////////////////////////////////////////////////////////////////////////////
// CEditExtensionsSheet

#include "ExtendedEditDlg.h"
#include "NumericEditDlg.h"
#include "CurrencyEditDlg.h"
#include "PhysicalEditDlg.h"
#include "MaskedEditDlg.h"
#include "DropEditDlg.h"

class CEditExtensionsSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CEditExtensionsSheet)

// Construction
public:
	CEditExtensionsSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CEditExtensionsSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

protected:
	void AddControlPages(void);

// Attributes
public:

	CExtendedEditDlg m_extendedEditPage;
	CNumericEditDlg m_numericEditPage;
	CCurrencyEditDlg m_currencyEditPage;
	CPhysicalEditDlg m_physicalEditPage;
	CMaskedEditDlg m_maskedEditPage;
	CDropEditDlg m_dropEditPage;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditExtensionsSheet)
	//}}AFX_VIRTUAL
	afx_msg void OnAppAbout();

// Implementation
public:
	virtual ~CEditExtensionsSheet();
	virtual BOOL OnInitDialog();

	// Generated message map functions
protected:

	HICON m_hIcon;

	//{{AFX_MSG(CEditExtensionsSheet)
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
