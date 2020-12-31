// DatePickerDlg.h : header file
//

#if !defined(AFX_DATEPICKERDLG_H__497A0326_55F0_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_DATEPICKERDLG_H__497A0326_55F0_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DateTimeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDatePickerDlg dialog

class CDatePickerDlg : public CDialog
{
// Construction
public:
	CDatePickerDlg(CWnd* pParent = NULL);	// standard constructor

// Attributes
public:
	CDateTimeCtrl m_DateTime;
	CTime	      m_SysTime;
	CFont		  m_font;

// Dialog Data
	//{{AFX_DATA(CDatePickerDlg)
	enum { IDD = IDD_DATEPICKER_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDatePickerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDatePickerDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnDateChange(NMHDR* pNotifyStruct, LRESULT* result);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATEPICKERDLG_H__497A0326_55F0_11D1_ABBA_00A0243D1382__INCLUDED_)
