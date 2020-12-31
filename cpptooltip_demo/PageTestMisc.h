#if !defined(AFX_PAGETESTMISC_H__44A50C42_ACB1_40C2_A880_1E8FDFFB0500__INCLUDED_)
#define AFX_PAGETESTMISC_H__44A50C42_ACB1_40C2_A880_1E8FDFFB0500__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTestMisc.h : header file
//
#include "PPToolTip.h"
/////////////////////////////////////////////////////////////////////////////
// CPageTestMisc dialog

class CPageTestMisc : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageTestMisc)

// Construction
public:
	CPPToolTip m_tooltip;
	CPageTestMisc();
	~CPageTestMisc();

// Dialog Data
	//{{AFX_DATA(CPageTestMisc)
	enum { IDD = IDD_PAGETEST_MISC };
	BOOL	m_wrap_text;
	UINT	m_width_tip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageTestMisc)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_bResizedButton;
	CButton * m_pButton;
	// Generated message map functions
	//{{AFX_MSG(CPageTestMisc)
	virtual BOOL OnInitDialog();
	afx_msg void OnRuntimeResize();
	afx_msg void OnChangeWrapText();
	afx_msg void OnChangeWidthTip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETESTMISC_H__44A50C42_ACB1_40C2_A880_1E8FDFFB0500__INCLUDED_)
