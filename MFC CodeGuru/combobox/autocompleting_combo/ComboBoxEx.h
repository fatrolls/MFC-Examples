#if !defined(AFX_COMBOBOXEX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_COMBOBOXEX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// ComboBoxEx.h : header file
//
// Copyright (c) Chris Maunder 1997.
// Please feel free to use and distribute.


/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx window

class CComboBoxEx : public CComboBox
{
// Construction
public:
	CComboBoxEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboBoxEx();

	BOOL m_bAutoComplete;

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxEx)
	afx_msg void OnEditUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXEX_H__115F422E_5CD5_11D1_ABBA_00A0243D1382__INCLUDED_)
