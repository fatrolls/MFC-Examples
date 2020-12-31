/////////////////////////////////////////////////////////////////////////////
// CTest2Page dialog

#include "OXContextHelpPropertyPage.h"

class CTest2Page : public COXContextHelpPropertyPage
{
// Construction
public:
	CTest2Page();

	BOOL AdjustToolTips();


// Dialog Data
	//{{AFX_DATA(CTest2Page)
	enum { IDD = IDD_COLOR };
	CScrollBar	m_scroll1;
	CComboBox	m_combo1;
	CButton	m_check1;
	CButton	m_button2;
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTest2Page)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTest2Page)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
