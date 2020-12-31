// EventLogDlg.h : header file
//

#if !defined(AFX_EVENTLOGDLG_H__B2FDEA48_8819_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_EVENTLOGDLG_H__B2FDEA48_8819_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "EvntLog.h"

/////////////////////////////////////////////////////////////////////////////
// CEventLogDlg dialog

class CEventLogDlg : public CDialog
{
// Construction
public:
	CEventLogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEventLogDlg)
	enum { IDD = IDD_EVENTLOG_DIALOG };
	CButton	m_ctlButtonRefresh;
	CButton	m_ctlButtonReport;
	CListBox	m_ctlListEvents;
	int		m_nEvent;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	COXEventLog	m_EventLog;

	// Generated message map functions
	//{{AFX_MSG(CEventLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreateButton();
	afx_msg void OnOpenButton();
	afx_msg void OnRegButton();
	afx_msg void OnRepButton();
	afx_msg void OnRfrButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTLOGDLG_H__B2FDEA48_8819_11D1_A3D5_0080C83F712F__INCLUDED_)
