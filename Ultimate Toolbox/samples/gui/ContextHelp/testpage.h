#include "OXContextHelpPropertyPage.h"

class CTestPage : public COXContextHelpPropertyPage
{
// Construction
public:
	CTestPage();

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CTestPage)
	enum { IDD = IDD_STYLE };
	CStatic	m_static3;
	CStatic	m_static4;
	CEdit	m_edit1;
	CButton	m_check1;
	CButton	m_button2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTestPage)
	afx_msg void OnTestbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
