// CalUserDlg.h : header file
//
//{{AFX_INCLUDES()
#include "calendar.h"
//}}AFX_INCLUDES

#if !defined(AFX_CALUSERDLG_H__85FDD589_470B_11D2_AC96_006008A8274D__INCLUDED_)
#define AFX_CALUSERDLG_H__85FDD589_470B_11D2_AC96_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalUserDlg dialog

class CCalUserDlg : public CDialog
{
// Construction
public:
	CCalUserDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCalUserDlg)
	enum { IDD = IDD_CALUSER_DIALOG };
	CComboBox	m_ctlYear;
	CComboBox	m_ctlMonth;
	CCalendar	m_ctlCalendar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalUserDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static const CString m_strMonths[];
	void InitListOfYears ();
	void InitListOfMonths ();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCalUserDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeDate();
	afx_msg void OnNewDay(short nDay);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALUSERDLG_H__85FDD589_470B_11D2_AC96_006008A8274D__INCLUDED_)
