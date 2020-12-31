#if !defined(AFX_HARDWAREPAGE_H__C7A07F0F_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_HARDWAREPAGE_H__C7A07F0F_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HardwarePage.h : header file
//

#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CHardwarePage dialog

class CHardwarePage : public CNewWizPage
{
// Construction
public:
	CHardwarePage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHardwarePage)
	enum { IDD = IDW_HARDWARE };
	CStatic	m_CaptionCtrl;
	//}}AFX_DATA

	CFont m_Font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHardwarePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnWizardFinish();

	// Generated message map functions
	//{{AFX_MSG(CHardwarePage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HARDWAREPAGE_H__C7A07F0F_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
