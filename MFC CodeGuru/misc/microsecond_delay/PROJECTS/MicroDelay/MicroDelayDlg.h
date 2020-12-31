// MicroDelayDlg.h : header file
//

#if !defined(AFX_MICRODELAYDLG_H__D7406E74_9B3A_11D1_94DB_00400540824C__INCLUDED_)
#define AFX_MICRODELAYDLG_H__D7406E74_9B3A_11D1_94DB_00400540824C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CMicroDelayDlg dialog
#include "MicroSecond.h"

class CMicroDelayDlg : public CDialog
{
// Construction
public:
	void Tweek();

    CMicroSecond* puSec;
    
	CMicroDelayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMicroDelayDlg)
	enum { IDD = IDD_MICRODELAY_DIALOG };
	int		m_nLoopCount1;
	int		m_nLoopCount2;
	int		m_nLoop_per_uSecond;
	int		m_nMilliSecondPerTenSeconds;
	CString	m_strError;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMicroDelayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMicroDelayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDoit();
	virtual void OnOK();
	afx_msg void OnInitialize();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MICRODELAYDLG_H__D7406E74_9B3A_11D1_94DB_00400540824C__INCLUDED_)
