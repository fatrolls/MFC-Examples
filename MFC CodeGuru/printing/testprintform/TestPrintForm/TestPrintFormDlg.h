#if !defined(AFX_TESTPRINTFORMDLG_H__B5ED7C12_1118_11D2_8434_0000B43382FE__INCLUDED_)
#define AFX_TESTPRINTFORMDLG_H__B5ED7C12_1118_11D2_8434_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TestPrintFormDlg.h : header file
//
#include "SinglePagePrintJobDlg.h"
#include "MultiPagePrintJobDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormDlg dialog

class CTestPrintFormDlg : public CDialog
{
// Construction
public:
	CTestPrintFormDlg(CWnd* pParent = NULL);   // standard constructor

	CSinglePagePrintJobDlg	cSingleJob;
	CMultiPagePrintJobDlg  cMultiJob;

// Dialog Data
	//{{AFX_DATA(CTestPrintFormDlg)
	enum { IDD = IDD_DIALOG1 };
	CListCtrl	wndList;
	BOOL	bCheck;
	CString	csVal1;
	CString	csVal2;
	CString	csVal3;
	CString	csVal4;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintFormDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestPrintFormDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINTFORMDLG_H__B5ED7C12_1118_11D2_8434_0000B43382FE__INCLUDED_)
