#if !defined(AFX_POSTDLG_H__3EC7DED4_1CE5_11D3_87F5_0080C86498A0__INCLUDED_)
#define AFX_POSTDLG_H__3EC7DED4_1CE5_11D3_87F5_0080C86498A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PostDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPostDlg dialog

#pragma warning ( disable : 4511 4512 )

class CPostDlg : public CDialog
{
// Construction
public:
	CPostDlg(CWnd* pParent = NULL);   // standard constructor


// Dialog Data
	//{{AFX_DATA(CPostDlg)
	enum { IDD = IDD_POST_ARTICLE_DLG };
	CString	m_strArtBody;
	CString	m_strSubject;
	CString	m_strFrom;
	CString	m_strTargetNewsGroups;
	//}}AFX_DATA

	CString m_sAttachment;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPostDlg)
	afx_msg void OnOk();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 )

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSTDLG_H__3EC7DED4_1CE5_11D3_87F5_0080C86498A0__INCLUDED_)
