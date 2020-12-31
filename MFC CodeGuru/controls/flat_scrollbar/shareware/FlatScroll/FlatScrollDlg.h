// FlatScrollDlg.h : header file
//

#if !defined(AFX_FLATSCROLLDLG_H__D71BA159_0455_11D2_BAF6_0060083D6967__INCLUDED_)
#define AFX_FLATSCROLLDLG_H__D71BA159_0455_11D2_BAF6_0060083D6967__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CFlatScrollDlg dialog
#include "FlatScrollBar.h"

class CFlatScrollDlg : public CDialog
{
// Construction
public:
	CFlatScrollDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFlatScrollDlg)
	enum { IDD = IDD_FLATSCROLL_DIALOG };
	CEdit	m_edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlatScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CFlatScrollBar scrollbar;

	// Generated message map functions
	//{{AFX_MSG(CFlatScrollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLATSCROLLDLG_H__D71BA159_0455_11D2_BAF6_0060083D6967__INCLUDED_)
