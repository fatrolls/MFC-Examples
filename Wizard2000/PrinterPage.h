#if !defined(AFX_PRINTERPAGE_H__C7A07F10_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
#define AFX_PRINTERPAGE_H__C7A07F10_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrinterPage.h : header file
//

#include "NewWizPage.h"

/////////////////////////////////////////////////////////////////////////////
// CPrinterPage dialog

class CPrinterPage : public CNewWizPage
{
// Construction
public:
	CPrinterPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrinterPage)
	enum { IDD = IDW_PRINTER };
	CStatic	m_CaptionCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrinterPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL OnQueryCancel();

	// Generated message map functions
	//{{AFX_MSG(CPrinterPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTERPAGE_H__C7A07F10_2EF0_11D4_9FA9_0030DB0011C6__INCLUDED_)
