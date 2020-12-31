// SendDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendDataDlg dialog

#include "OXCommMsg.h"

class CSendDataDlg : public CDialog
{
// Construction
public:
	CSendDataDlg(COXCommMsg* pCommMsg, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSendDataDlg)
	enum { IDD = IDD_SEND_DATA };
	CButton	m_wndBrowse;
	CListBox	m_wndList;
	CString	m_sValue;
	int		m_nType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	COXCommMsg* m_pCommMsg;

	// Generated message map functions
	//{{AFX_MSG(CSendDataDlg)
	afx_msg void OnAdd();
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
