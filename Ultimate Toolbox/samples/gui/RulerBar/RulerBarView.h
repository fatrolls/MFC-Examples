// RulerBarView.h : interface of the CRulerBarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RULERBARVIEW_H__12E49E93_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
#define AFX_RULERBARVIEW_H__12E49E93_E788_11D2_A7F6_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXRulerOrganizer.h"


class CRulerBarView : public CEditView
{
protected: // create from serialization only
	CRulerBarView();
	DECLARE_DYNCREATE(CRulerBarView)

// Attributes
public:
	CRulerBarDoc* GetDocument();

protected:
	COXRulerOrganizer m_ruler;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerBarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRulerBarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void UpdateRulerBars();

// Generated message map functions
protected:
	//{{AFX_MSG(CRulerBarView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RulerBarView.cpp
inline CRulerBarDoc* CRulerBarView::GetDocument()
   { return (CRulerBarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERBARVIEW_H__12E49E93_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
