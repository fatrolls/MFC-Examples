#if !defined(AFX_LISTPRINTPAGE1_H__2DCD2CC1_9D76_11D1_8BAC_0000B43382FE__INCLUDED_)
#define AFX_LISTPRINTPAGE1_H__2DCD2CC1_9D76_11D1_8BAC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ListPrintPage1.h : header file
//
#include "FontCombo.h"
/////////////////////////////////////////////////////////////////////////////
// CListPrintPage1 dialog

class CListPrintPage1 : public CDialog
{
// Construction
public:
	void Update();
	CListPrintPage1(CWnd* pParent = NULL);   // standard constructor

	CString csFtHead;
	CString csFtFoot;
	CString csFtPrint;
	int iFtHead;
	int iFtFoot;
	int iFtPrint;

// Dialog Data
	//{{AFX_DATA(CListPrintPage1)
	enum { IDD = IDD_LISTPAGE1 };
	CComboBox	wndCbSzHead;
	CComboBox	wndCbSzFooter;
	CComboBox	wndCbSzCorpo;
	CFontCombo	wndCbHead;
	CFontCombo	wndCbFooter;
	CFontCombo	wndCbCorpo;
	CString	csFooter;
	CString	csHead;
	CString	csPage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListPrintPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CListPrintPage1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTPRINTPAGE1_H__2DCD2CC1_9D76_11D1_8BAC_0000B43382FE__INCLUDED_)
