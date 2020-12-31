// NetSampleDlg.h : header file
//

#if !defined(AFX_NETSAMPLEDLG_H__347C5696_9C76_11D1_9436_0000C014F0A1__INCLUDED_)
#define AFX_NETSAMPLEDLG_H__347C5696_9C76_11D1_9436_0000C014F0A1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NetSearch.h"

/////////////////////////////////////////////////////////////////////////////
// CNetSampleDlg dialog

class CNetSampleDlg : public CDialog
{

	CNetSearch<CNetSampleDlg>	m_NetWalker;

	BOOL	OnNetResourceHit(NETRESOURCE &);

// Construction
public:
	CNetSampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNetSampleDlg)
	enum { IDD = IDD_NETSAMPLE_DIALOG };
	CListBox	m_ctrlList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetSampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNetSampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSAMPLEDLG_H__347C5696_9C76_11D1_9436_0000C014F0A1__INCLUDED_)
