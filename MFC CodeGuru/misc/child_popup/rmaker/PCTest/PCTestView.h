// PCTestView.h : interface of the CPCTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PCTESTVIEW_H__D1BB416F_804D_11D1_80B6_080009CC78D8__INCLUDED_)
#define AFX_PCTESTVIEW_H__D1BB416F_804D_11D1_80B6_080009CC78D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "PCWnd.h"

class CPCTestView : public CView
{
protected: // create from serialization only
	CPCTestView();
	DECLARE_DYNCREATE(CPCTestView)

// Attributes
public:
	CPCTestDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPCTestView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CPopChildWnd m_pcWnd;
};

#ifndef _DEBUG  // debug version in PCTestView.cpp
inline CPCTestDoc* CPCTestView::GetDocument()
   { return (CPCTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCTESTVIEW_H__D1BB416F_804D_11D1_80B6_080009CC78D8__INCLUDED_)
