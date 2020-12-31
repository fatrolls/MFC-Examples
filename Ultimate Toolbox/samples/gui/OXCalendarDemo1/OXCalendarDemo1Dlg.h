// OXCalendarDemo1Dlg.h : header file
//

#if !defined(AFX_OXCALENDARDEMO1DLG_H__4EDE7CB9_874D_11D1_A4E3_0020359647BF__INCLUDED_)
#define AFX_OXCALENDARDEMO1DLG_H__4EDE7CB9_874D_11D1_A4E3_0020359647BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "OXCalendar.h"
/////////////////////////////////////////////////////////////////////////////
// COXCalendarDemo1Dlg dialog

class COXCalendarDemo1Dlg : public CDialog
{
// Construction
public:
	COXCalendarDemo1Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(COXCalendarDemo1Dlg)
	enum { IDD = IDD_OXCALENDARDEMO1_DIALOG };
	COXCalendar	m_Calendar2;
	COXCalendar	m_Calendar1;
	CString	m_First;
	CString	m_Last;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXCalendarDemo1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COXCalendarDemo1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OXCALENDARDEMO1DLG_H__4EDE7CB9_874D_11D1_A4E3_0020359647BF__INCLUDED_)
