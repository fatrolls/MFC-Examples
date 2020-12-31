// TrickBtnDemoDlg.h : header file
//

#if !defined(AFX_TRICKBTNDEMODLG_H__B6A0FBA5_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
#define AFX_TRICKBTNDEMODLG_H__B6A0FBA5_FDF4_11D1_AB40_8C80B0000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Trickbutton.h"

/////////////////////////////////////////////////////////////////////////////
// CTrickBtnDemoDlg dialog

class CTrickBtnDemoDlg : public CDialog
{
// Construction
public:
	CTrickBtnDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTrickBtnDemoDlg)
	enum { IDD = IDD_TRICKBTNDEMO_DIALOG };
	CTrickButton	m_TrickButton;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrickBtnDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTrickBtnDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTrickbutton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRICKBTNDEMODLG_H__B6A0FBA5_FDF4_11D1_AB40_8C80B0000000__INCLUDED_)
