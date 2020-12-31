// ChkFrameDlg.h : header file
//

#if !defined(AFX_CHKFRAMEDLG_H__F3089B4C_AA09_11D1_A435_00A024E01A10__INCLUDED_)
#define AFX_CHKFRAMEDLG_H__F3089B4C_AA09_11D1_A435_00A024E01A10__INCLUDED_

#include "CheckFrm.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CChkFrameDlg dialog

class CChkFrameDlg : public CDialog
{
// Construction
public:
	CChkFrameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChkFrameDlg)
	enum { IDD = IDD_CHKFRAME_DIALOG };
	CButton	m_btnCheck;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChkFrameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CCheckFrame m_ChkFrame;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChkFrameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheck2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHKFRAMEDLG_H__F3089B4C_AA09_11D1_A435_00A024E01A10__INCLUDED_)
