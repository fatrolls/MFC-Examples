// PieClientDlg.h : header file
//

#if !defined(AFX_PIECLIENTDLG_H__3B5BA32C_3B72_11D2_AC82_006008A8274D__INCLUDED_)
#define AFX_PIECLIENTDLG_H__3B5BA32C_3B72_11D2_AC82_006008A8274D__INCLUDED_

#include "autopie.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPieClientDlg dialog

class CPieClientDlg : public CDialog
{
// Construction
public:
	CPieClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPieClientDlg)
	enum { IDD = IDD_PIECLIENT_DIALOG };
	CButton	m_wndSet;
	CButton	m_wndGet;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPieClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CAutoWindow m_autoWindow;
	CAutoChart m_autoChart;
	CAutoPie m_autoPie;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPieClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGet();
	afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PIECLIENTDLG_H__3B5BA32C_3B72_11D2_AC82_006008A8274D__INCLUDED_)
