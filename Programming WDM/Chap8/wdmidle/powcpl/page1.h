// Page1.h -- Declaration of CPage1 sample property page
// Copyright (C) 1998 by Walter Oney
// All rights reserved

#ifndef page1_H
#define page1_H

#include "resource.h"

///////////////////////////////////////////////////////////////////////////////
// CPage1 dialog

class CDriver;

class CPage1 : public CShellPropPage
{
	DECLARE_DYNAMIC(CPage1)

// Construction
public:
	CPage1(CCmdTarget* parent);
	virtual ~CPage1();

	static BOOL DevicesPresent();
	static LPGUID InterfaceGuid();

// Dialog Data
	//{{AFX_DATA(CPage1)
	enum { IDD = IDD_page1 };
	CStatic	m_ctlIsidle;
	CComboBox	m_ctlIdleunplugged;
	CComboBox	m_ctlIdleplugged;
	CButton	m_ctlIdlenow;
	CButton	m_ctlWakeup;
	CListBox	m_ctlDevicelist;
	BOOL	m_wakeup;
	int		m_idleplugged;
	int		m_idleunplugged;
	//}}AFX_DATA

	CDriver* m_current;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPage1)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int ConvertTimeout(DWORD to);
	void InitializeDeviceList(CListBox* list);

	// Generated message map functions
	//{{AFX_MSG(CPage1)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDevicelist();
	afx_msg void OnDestroy();
	afx_msg void OnWakeup();
	afx_msg void OnSelendokIdleplugged();
	afx_msg void OnSelendokIdleunplugged();
	afx_msg void OnIdlenow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif
