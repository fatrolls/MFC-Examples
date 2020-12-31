#if !defined(AFX_CREATEFOLDERDLG_H__588C2B1A_4A70_11D3_A4C4_0080C858F182__INCLUDED_)
#define AFX_CREATEFOLDERDLG_H__588C2B1A_4A70_11D3_A4C4_0080C858F182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateFolderDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateFolderDlg dialog

#pragma warning ( disable : 4511 4512 ) // VC6 level 4 - copy ctor & op=

class CCreateFolderDlg : public CDialog
{
// Construction
public:
	CCreateFolderDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateFolderDlg)
	enum { IDD = IDD_CREATE_FOLDER_DIALOG };
	CString	m_strFolderName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateFolderDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateFolderDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma warning ( default : 4511 4512 ) // VC6 level 4 - copy ctor & op=

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEFOLDERDLG_H__588C2B1A_4A70_11D3_A4C4_0080C858F182__INCLUDED_)
