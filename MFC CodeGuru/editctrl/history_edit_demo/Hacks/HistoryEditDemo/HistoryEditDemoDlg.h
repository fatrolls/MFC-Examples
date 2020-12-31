// HistoryEditDemoDlg.h : header file
//

#if !defined(AFX_HISTORYEDITDEMODLG_H__63E7CA67_BC22_11D1_8EE6_94D40BC10000__INCLUDED_)
#define AFX_HISTORYEDITDEMODLG_H__63E7CA67_BC22_11D1_8EE6_94D40BC10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HistoryEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CHistoryEditDemoDlg dialog

class CHistoryEditDemoDlg : public CDialog
{
// Construction
public:
	CHistoryEditDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHistoryEditDemoDlg)
	enum { IDD = IDD_HISTORYEDITDEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistoryEditDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
  CHistoryEdit    m_HistoryEdit;    // CHistoryEdit control

	// Generated message map functions
	//{{AFX_MSG(CHistoryEditDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAllowselect();
	afx_msg void OnAdd();
	afx_msg void OnClear();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTORYEDITDEMODLG_H__63E7CA67_BC22_11D1_8EE6_94D40BC10000__INCLUDED_)
