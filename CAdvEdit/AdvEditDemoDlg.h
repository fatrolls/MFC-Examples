// AdvEditDemoDlg.h : header file
//

#if !defined(AFX_ADVEDITDEMODLG_H__7A27F3CD_8F09_4B01_9C96_D30F4F2CB1DB__INCLUDED_)
#define AFX_ADVEDITDEMODLG_H__7A27F3CD_8F09_4B01_9C96_D30F4F2CB1DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "AdvEdit.h"
/////////////////////////////////////////////////////////////////////////////
// CAdvEditDemoDlg dialog

class CAdvEditDemoDlg : public CDialog
{
// Construction
public:
	CAdvEditDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdvEditDemoDlg)
	enum { IDD = IDD_ADVEDITDEMO_DIALOG };
	CAdvEdit	m_edt2;
	CAdvEdit	m_edt;
	//}}AFX_DATA
	CAdvEdit m_AdvEdit[7];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAdvEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVEDITDEMODLG_H__7A27F3CD_8F09_4B01_9C96_D30F4F2CB1DB__INCLUDED_)
