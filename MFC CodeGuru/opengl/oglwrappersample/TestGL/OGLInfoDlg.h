#if !defined(AFX_OGLINFODLG_H__C81AF449_E711_11D1_ACB4_F679EAB0F608__INCLUDED_)
#define AFX_OGLINFODLG_H__C81AF449_E711_11D1_ACB4_F679EAB0F608__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OGLInfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COGLInfoDlg dialog

class COGLInfoDlg : public CDialog
{
// Construction
public:
	COGLInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COGLInfoDlg)
	enum { IDD = IDD_OGLINFO_DIALOG };
	CString	m_accel;
	CString	m_extensions;
	CString	m_rend;
	CString	m_vendor;
	CString	m_version;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGLInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COGLInfoDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGLINFODLG_H__C81AF449_E711_11D1_ACB4_F679EAB0F608__INCLUDED_)
