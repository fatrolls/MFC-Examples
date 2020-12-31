// MyBrowserView.h : interface of the CMyBrowserView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYBROWSERVIEW_H__7A739621_F300_11D1_9F48_C49E4E07811D__INCLUDED_)
#define AFX_MYBROWSERVIEW_H__7A739621_F300_11D1_9F48_C49E4E07811D__INCLUDED_

#include "webbrowser.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMyBrowserView : public CView
{
protected: // create from serialization only
	CMyBrowserView();
	DECLARE_DYNCREATE(CMyBrowserView)

// Attributes
public:
	CMyBrowserDoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CWebBrowser m_Browser;
	virtual ~CMyBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyBrowserView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnReload();
	afx_msg void OnForward();
	afx_msg void OnBack();
	afx_msg void OnStop();
	afx_msg void OnUrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyBrowserView.cpp
inline CMyBrowserDoc* CMyBrowserView::GetDocument()
   { return (CMyBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYBROWSERVIEW_H__7A739621_F300_11D1_9F48_C49E4E07811D__INCLUDED_)
