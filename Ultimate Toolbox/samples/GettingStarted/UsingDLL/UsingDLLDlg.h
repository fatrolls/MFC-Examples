// UsingDLLDlg.h : header file
//

#if !defined(AFX_USINGDLLDLG_H__F8BE97CD_A983_4FAE_95B5_EDE302C33EE6__INCLUDED_)
#define AFX_USINGDLLDLG_H__F8BE97CD_A983_4FAE_95B5_EDE302C33EE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUsingDLLDlg dialog

#include "OXStaticHyperLink.h"

class CUsingDLLDlg : public CDialog
{
// Construction
public:
	CUsingDLLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUsingDLLDlg)
	enum { IDD = IDD_USINGDLL_DIALOG };
	COXStaticHyperLink	m_HyperLink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingDLLDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUsingDLLDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDLLDLG_H__F8BE97CD_A983_4FAE_95B5_EDE302C33EE6__INCLUDED_)
