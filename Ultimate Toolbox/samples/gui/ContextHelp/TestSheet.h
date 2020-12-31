// TestSheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestSheet dialog

#include "OXContextHelpPropertySheet.h"

class CTestSheet : public COXContextHelpPropertySheet
{
// Construction
public:
	CTestSheet(UINT nIDCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);
	CTestSheet(LPCTSTR pszCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);

protected:
	BOOL AdjustToolTips() ;

// Dialog Data
	//{{AFX_DATA(CTestSheet)
	enum { IDD = IDD_TESTBOX };
	CButton	m_btCancel;
	CButton	m_btOk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSheet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSheet)
		// NOTE: the ClassWizard will add member functions here
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
