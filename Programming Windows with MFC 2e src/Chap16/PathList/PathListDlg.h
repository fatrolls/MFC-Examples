// PathListDlg.h : header file
//

#if !defined(AFX_PATHLISTDLG_H__710413E6_AC66_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_PATHLISTDLG_H__710413E6_AC66_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPathListDlg dialog

class CPathListDlg : public CDialog
{
// Construction
public:
	CPathListDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPathListDlg)
	enum { IDD = IDD_PATHLIST_DIALOG };
	CPathComboBox	m_wndCBEx;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathListDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPathListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelEndOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHLISTDLG_H__710413E6_AC66_11D2_8E53_006008A82731__INCLUDED_)
