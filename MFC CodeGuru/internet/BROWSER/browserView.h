// browserView.h : interface of the CBrowserView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BROWSERVIEW_H__FB8B0E0F_F15A_11D1_BE66_080042010BFF__INCLUDED_)
#define AFX_BROWSERVIEW_H__FB8B0E0F_F15A_11D1_BE66_080042010BFF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "webbrowser2.h"

class CBrowserView : public CView
{
public: // create from serialization only
	CBrowserView();
	DECLARE_DYNCREATE(CBrowserView)

// Attributes
public:
	CWebBrowser2	m_WebBrowser2;
	CBrowserDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrowserView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void NavigateURL(LPCTSTR lpszName);
	virtual ~CBrowserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBrowserView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in browserView.cpp
inline CBrowserDoc* CBrowserView::GetDocument()
   { return (CBrowserDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BROWSERVIEW_H__FB8B0E0F_F15A_11D1_BE66_080042010BFF__INCLUDED_)
