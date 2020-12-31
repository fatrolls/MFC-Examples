#if !defined(AFX_CUSTOMIZEASSERTDLG_H__6EC9E164_1A72_11D2_888E_0080C83F712F__INCLUDED_)
#define AFX_CUSTOMIZEASSERTDLG_H__6EC9E164_1A72_11D2_888E_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CustomizeAssertDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeAssertDlg dialog

class CCustomizeAssertDlg : public CDialog
{
// Construction
public:
	CCustomizeAssertDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeAssertDlg)
	enum { IDD = IDD_CUSTOMIZE };
	BOOL	m_bSendMail;
	CString	m_sEmailAddress;
	CString	m_sNote1;
	CString	m_sNote2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeAssertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeAssertDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZEASSERTDLG_H__6EC9E164_1A72_11D2_888E_0080C83F712F__INCLUDED_)
