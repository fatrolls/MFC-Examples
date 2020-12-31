#if !defined(AFX_WORKSPACEDLG_H__A53D9124_76C7_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_WORKSPACEDLG_H__A53D9124_76C7_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WorkspaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDlg dialog

class CWorkspaceDlg : public CDialog
{
// Construction
public:
	CWorkspaceDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkspaceDlg)
	enum { IDD = IDD_DIALOG_WORKSPACE };
	BOOL	m_bLoadOnEnter;
	BOOL	m_bSaveOnExit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWorkspaceDlg)
	afx_msg void OnSaveWorkspace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORKSPACEDLG_H__A53D9124_76C7_11D1_A3D5_0080C83F712F__INCLUDED_)
