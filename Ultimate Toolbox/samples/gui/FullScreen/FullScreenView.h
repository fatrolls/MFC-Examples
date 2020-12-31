// FullScreenView.h : interface of the CFullScreenView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FULLSCREENVIEW_H__2690A076_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_)
#define AFX_FULLSCREENVIEW_H__2690A076_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_

#include "..\..\..\INCLUDE\OXFullScreenFrame.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


  
class CFullScreenView : public CEditView
{
protected: // create from serialization only
	CFullScreenView();
	DECLARE_DYNCREATE(CFullScreenView)

// Attributes
public:
	CFullScreenDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFullScreenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFullScreenView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FullScreenView.cpp
inline CFullScreenDoc* CFullScreenView::GetDocument()
   { return (CFullScreenDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENVIEW_H__2690A076_0FC5_11D4_AD08_0050BAAB46B1__INCLUDED_)
