// ReportCtrlDemoView.h : interface of the CReportCtrlDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTCTRLDEMOVIEW_H__070C2D0E_5E8C_44A7_81B3_5A16B97E59C0__INCLUDED_)
#define AFX_REPORTCTRLDEMOVIEW_H__070C2D0E_5E8C_44A7_81B3_5A16B97E59C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportCtrl.h"

class CReportCtrlDemoView : public CFormView
{
protected: // create from serialization only
	CReportCtrlDemoView();
	DECLARE_DYNCREATE(CReportCtrlDemoView)

public:
	//{{AFX_DATA(CReportCtrlDemoView)
	enum{ IDD = IDD_REPORTCTRLDEMO_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CReportCtrlDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReportCtrlDemoView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CReportCtrlDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CReportCtrl m_wndList;

// Generated message map functions
protected:
	//{{AFX_MSG(CReportCtrlDemoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ReportCtrlDemoView.cpp
inline CReportCtrlDemoDoc* CReportCtrlDemoView::GetDocument()
   { return (CReportCtrlDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPORTCTRLDEMOVIEW_H__070C2D0E_5E8C_44A7_81B3_5A16B97E59C0__INCLUDED_)
