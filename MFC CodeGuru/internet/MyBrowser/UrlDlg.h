#if !defined(AFX_URLDLG_H__61268E60_F313_11D1_9F48_BB48CBBB2FFF__INCLUDED_)
#define AFX_URLDLG_H__61268E60_F313_11D1_9F48_BB48CBBB2FFF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// UrlDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// UrlDlg dialog

class UrlDlg : public CDialog
{
// Construction
public:
	UrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(UrlDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_Edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(UrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(UrlDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLDLG_H__61268E60_F313_11D1_9F48_BB48CBBB2FFF__INCLUDED_)
