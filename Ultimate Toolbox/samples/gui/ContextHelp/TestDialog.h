// TestDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestDialog dialog
#include "OXContextHelpDialog.h"

class CTestDialog : public COXContextHelpDialog
{
// Construction
public:
	CTestDialog(CWnd* pParent = NULL);   // standard constructor

	BOOL AdjustToolTips();

// Dialog Data
	//{{AFX_DATA(CTestDialog)
	enum { IDD = IDD_TESTBOX };
	CScrollBar	m_scroll1;
	CEdit	m_edit1;
	CComboBox	m_combo1;
	CButton	m_check1;
	CButton	m_btTwo;
	CButton	m_btCancel;
	CButton	m_btOk;
	BOOL	m_bCheck1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	static const DWORD m_nHelpIDs[];
	virtual const DWORD* GetHelpIDs() {return m_nHelpIDs;}
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDialog)
	afx_msg void OnCheck1();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
