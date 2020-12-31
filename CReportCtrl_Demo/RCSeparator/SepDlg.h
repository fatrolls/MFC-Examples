#if !defined(AFX_SEPDLG_H__7C1CDA5A_3F3A_47BA_BD31_64D3F4E504DC__INCLUDED_)
#define AFX_SEPDLG_H__7C1CDA5A_3F3A_47BA_BD31_64D3F4E504DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SepDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSepDlg dialog

class CSepDlg : public CDialog
{
// Construction
public:
	CString GetSep() const;
	BOOL UseSep() const;
	CSepDlg(BOOL bNoSep, LPCTSTR lpSep, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSepDlg)
	enum { IDD = IDD_DIALOG1 };
	CEdit	m_wndSep;
	BOOL	m_bNoSep;
	CString	m_sSep;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSepDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSepDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPDLG_H__7C1CDA5A_3F3A_47BA_BD31_64D3F4E504DC__INCLUDED_)
