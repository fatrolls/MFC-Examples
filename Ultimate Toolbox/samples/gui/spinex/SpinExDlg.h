// SpinExDlg.h : header file
//

#include "OXSpinCtrl.h"
#include "ColorBar.h"

#if !defined(AFX_SPINEXDLG_H__B6E68EBA_1621_11D1_A271_0000929B340A__INCLUDED_)
#define AFX_SPINEXDLG_H__B6E68EBA_1621_11D1_A271_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSpinExDlg dialog

class CSpinExDlg : public CDialog
{
// Construction
public:
	COXSpinCtrl m_SpinEx4;
	CSpinExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpinExDlg)
	enum { IDD = IDD_SPINEX_DIALOG };
	CColorBar	m_ColorBar;
	CEdit	m_Buddy4;
	COXSpinCtrl	m_SpinEx3;
	CEdit	m_Buddy3;
	CEdit	m_Buddy2;
	COXSpinCtrl	m_SpinEx2;
	CEdit	m_Buddy1;
	COXSpinCtrl	m_SpinEx1;
	int		m_nBuddy4;
	int		m_nBuddy1;
	int		m_nBuddy3;
	int		m_nBuddy2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinExDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_nColorBarHei;
	int m_nColorBarWid;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpinExDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnChangeBuddy4();
	afx_msg void OnChangeBuddy1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINEXDLG_H__B6E68EBA_1621_11D1_A271_0000929B340A__INCLUDED_)
