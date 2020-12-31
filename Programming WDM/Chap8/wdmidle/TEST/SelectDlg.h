
// Copyright (C) 1999 by Walter Oney
// All rights reserved
#if !defined(AFX_SELECTDLG_H__4377587E_A170_11D2_87F9_000000000000__INCLUDED_)
#define AFX_SELECTDLG_H__4377587E_A170_11D2_87F9_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectDlg.h : header file
//

#include "DeviceList.h"

/////////////////////////////////////////////////////////////////////////////
// CSelectDlg dialog

class CSelectDlg : public CDialog
{
// Construction
public:
	CSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectDlg)
	enum { IDD = IDD_SELECT };
	CComboBox	m_ctlDevicelist;
	int		m_devicelist;
	//}}AFX_DATA

	CDeviceList* m_list;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTDLG_H__4377587E_A170_11D2_87F9_000000000000__INCLUDED_)
