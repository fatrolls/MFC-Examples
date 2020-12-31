#if !defined(AFX_LBTABDEMOPROPSHEET_H__D7B746B8_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
#define AFX_LBTABDEMOPROPSHEET_H__D7B746B8_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LBTabDemoPropSheet.h : header file
//
#include "LBTabCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoPropSheet

class CLBTabDemoPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CLBTabDemoPropSheet)

// Construction
public:
	CLBTabDemoPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CLBTabDemoPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBTabDemoPropSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLBTabDemoPropSheet();
	CLBTabCtrl m_TabCtrlEx;
	// Generated message map functions
protected:

	//{{AFX_MSG(CLBTabDemoPropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBTABDEMOPROPSHEET_H__D7B746B8_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
