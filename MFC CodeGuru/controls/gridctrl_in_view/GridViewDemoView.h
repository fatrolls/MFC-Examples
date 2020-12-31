// GridViewDemoView.h : interface of the CGridViewDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDVIEWDEMOVIEW_H__19E18FBF_DFF6_11D1_8CE7_000000000000__INCLUDED_)
#define AFX_GRIDVIEWDEMOVIEW_H__19E18FBF_DFF6_11D1_8CE7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "GridCtrl.h"

class CGridViewDemoView : public CView
{
protected: // create from serialization only
	CGridViewDemoView();
	DECLARE_DYNCREATE(CGridViewDemoView)

// Attributes
public:
	CGridViewDemoDoc* GetDocument();
	CGridCtrl* m_pGridCtrl;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridViewDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridViewDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridViewDemoView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GridViewDemoView.cpp
inline CGridViewDemoDoc* CGridViewDemoView::GetDocument()
   { return (CGridViewDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEWDEMOVIEW_H__19E18FBF_DFF6_11D1_8CE7_000000000000__INCLUDED_)
