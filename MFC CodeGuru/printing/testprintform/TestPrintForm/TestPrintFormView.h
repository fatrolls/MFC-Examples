// TestPrintFormView.h : interface of the CTestPrintFormView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTPRINTFORMVIEW_H__F206742C_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_TESTPRINTFORMVIEW_H__F206742C_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#include "PrinterJob.h"

#include "SinglePagePrintJob.h"
#include "MultiPagePrintJob.h"

class CTestPrintFormDoc;

class CTestPrintFormView : public CFormView
{
protected: // create from serialization only
	CTestPrintFormView();
	DECLARE_DYNCREATE(CTestPrintFormView)

public:
	//{{AFX_DATA(CTestPrintFormView)
	enum { IDD = IDD_TESTPRINTFORM_FORM };
	CListCtrl	wndList;
	BOOL	bCheck;
	CString	csVal1;
	CString	csVal2;
	CString	csVal3;
	CString	csVal4;
	//}}AFX_DATA

// Attributes
public:
	CTestPrintFormDoc* GetDocument();

// Operations
public:

// Print routines
	CSinglePagePrintJob	cSingleJob;
	CMultiPagePrintJob  cMultiJob;

//	CFormPrinterJob	cJob;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintFormView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestPrintFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestPrintFormView)
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestPrintFormView.cpp
inline CTestPrintFormDoc* CTestPrintFormView::GetDocument()
   { return (CTestPrintFormDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINTFORMVIEW_H__F206742C_101A_11D2_8432_0000B43382FE__INCLUDED_)
