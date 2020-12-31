// DlgDemo.h : header file
//
#include "OXLayoutManager.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDemo dialog

class CDlgDemo : public CDialog
{
// Construction
public:
	CDlgDemo(CWnd* pParent = NULL);   // standard constructor

	COXLayoutManager m_LayoutManager;

// Dialog Data
	//{{AFX_DATA(CDlgDemo)
	enum { IDD = IDD_DEMO };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDemo)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
