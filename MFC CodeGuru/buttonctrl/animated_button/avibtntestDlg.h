// avibtntestDlg.h : header file
//

#if !defined(AFX_AVIBTNTESTDLG_H__A68C9449_82D9_11D1_85B9_444553540000__INCLUDED_)
#define AFX_AVIBTNTESTDLG_H__A68C9449_82D9_11D1_85B9_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CAvibtntestDlg dialog
#include "AniButton.h"
class CAvibtntestDlg : public CDialog
{
// Construction
public:
	CAvibtntestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAvibtntestDlg)
	enum { IDD = IDD_AVIBTNTEST_DIALOG };
	CAniButton	m_ctrOK;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAvibtntestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAvibtntestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AVIBTNTESTDLG_H__A68C9449_82D9_11D1_85B9_444553540000__INCLUDED_)
