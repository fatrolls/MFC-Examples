// WizPropertySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizPropertySheet
#ifndef __WIZ_PROP_SHEET__
#define __WIZ_PROP_SHEET__

#include "WizPropertyPage.h"

class CWizPropertySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizPropertySheet)

// Construction
public:
	void EnablePages(BOOL bEnable, int nStart, int nEnd = -1);
	CWizPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CWizPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	
	void AddPage( CWizPropertyPage *pPage );


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizPropertySheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizPropertySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizPropertySheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//friend class CPropertyPage;
};

/////////////////////////////////////////////////////////////////////////////
#endif