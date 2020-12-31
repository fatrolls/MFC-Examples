#if !defined(AFX_TIMEOUTDLG_H__172F958D_051F_11D2_88B0_0080C859A484__INCLUDED_)
#define AFX_TIMEOUTDLG_H__172F958D_051F_11D2_88B0_0080C859A484__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TimeoutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeoutDlg dialog

class CTimeoutDlg : public CDialog
{
// Construction
public:
	CTimeoutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeoutDlg)
	enum { IDD = IDD_TIMEOUT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	DWORD m_dwRxTimeout;
	DWORD m_dwTxTimeout;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeoutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeoutDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEOUTDLG_H__172F958D_051F_11D2_88B0_0080C859A484__INCLUDED_)
