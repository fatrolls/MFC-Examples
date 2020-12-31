//{{AFX_INCLUDES()
#include "calendar.h"
//}}AFX_INCLUDES
#if !defined(AFX_ACTIVEXDIALOG_H__1917789D_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
#define AFX_ACTIVEXDIALOG_H__1917789D_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ActiveXDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CActiveXDialog dialog

class CActiveXDialog : public CDialog
{
// Construction
public:
	CActiveXDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveXDialog)
	enum { IDD = IDD_ACTIVEXDIALOG };
	CCalendar	m_calendar;
	short	m_sDay;
	short	m_sMonth;
	short	m_sYear;
	//}}AFX_DATA
	COleVariant m_varValue;
	unsigned long m_BackColor;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveXDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CActiveXDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewMonthCalendar1();
	afx_msg void OnSelectDate();
	afx_msg void OnNextWeek();
	virtual void OnOK();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACTIVEXDIALOG_H__1917789D_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
