// splitdlgDlg.h : header file
//

#if !defined(AFX_SPLITDLGDLG_H__0DB1DF88_BF0B_11D1_B39A_00C02658086B__INCLUDED_)
#define AFX_SPLITDLGDLG_H__0DB1DF88_BF0B_11D1_B39A_00C02658086B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CSplitdlgDlg dialog
#include "SplitterBar.h"

class CSplitdlgDlg : public CDialog
{
// Construction
public:
	CSplitdlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSplitdlgDlg)
	enum { IDD = IDD_SPLITDLG_DIALOG };
	CListCtrl	m_wndList;
	CTreeCtrl	m_wndTree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitdlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CSplitterBar m_wndSplitterBar;
	
	// Generated message map functions
	//{{AFX_MSG(CSplitdlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITDLGDLG_H__0DB1DF88_BF0B_11D1_B39A_00C02658086B__INCLUDED_)
