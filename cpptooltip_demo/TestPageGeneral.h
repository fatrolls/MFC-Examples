#if !defined(AFX_TESTPAGEGENERAL_H__8A9DC7AD_4FA8_47D0_B618_B31EF9D13B09__INCLUDED_)
#define AFX_TESTPAGEGENERAL_H__8A9DC7AD_4FA8_47D0_B618_B31EF9D13B09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestPageGeneral.h : header file
//
#include "PPTooltip.h"

/////////////////////////////////////////////////////////////////////////////
// CTestPageGeneral dialog

class CTestPageGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CTestPageGeneral)

// Construction
public:
	CPPToolTip m_tooltip;
	CTestPageGeneral();
	~CTestPageGeneral();

// Dialog Data
	//{{AFX_DATA(CTestPageGeneral)
	enum { IDD = IDD_PAGETEST_GENERAL };
	CString	m_tooltip_string;
	BOOL	m_disable_look;
	BOOL	m_enable_escape;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CTestPageGeneral)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CTestPageGeneral)
	virtual BOOL OnInitDialog();
	afx_msg void OnDisableLookButton();
	afx_msg void OnChangeTooltipString();
	afx_msg void OnShowHelp();
	afx_msg void OnShowHelp2();
	afx_msg void OnEnableSequences();
	//}}AFX_MSG
	afx_msg void NotifyDisplayTooltip(NMHDR * pNMHDR, LRESULT * result);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPAGEGENERAL_H__8A9DC7AD_4FA8_47D0_B618_B31EF9D13B09__INCLUDED_)
