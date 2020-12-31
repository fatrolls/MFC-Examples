// FastTestView.h : interface of the CFastTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FASTTESTVIEW_H__7137DC99_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
#define AFX_FASTTESTVIEW_H__7137DC99_B77C_11D1_AE72_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "LocationsSet.h"

class CFastTestView : public CListView
{
protected: // create from serialization only
	CFastTestView();
	DECLARE_DYNCREATE(CFastTestView)

// Attributes
public:
	CFastTestDoc* GetDocument();

// Operations
public:

    CLocationsSet*  m_pLocationsSet;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFastTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFastTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFastTestView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FastTestView.cpp
inline CFastTestDoc* CFastTestView::GetDocument()
   { return (CFastTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FASTTESTVIEW_H__7137DC99_B77C_11D1_AE72_0004AC31E75C__INCLUDED_)
