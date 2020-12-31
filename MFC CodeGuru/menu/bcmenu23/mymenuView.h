// mymenuView.h : interface of the CMymenuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYMENUVIEW_H__3BAD410E_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
#define AFX_MYMENUVIEW_H__3BAD410E_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CMymenuView : public CView
{
protected: // create from serialization only
	CMymenuView();
	DECLARE_DYNCREATE(CMymenuView)

// Attributes
public:
	CMymenuDoc* GetDocument();
  BCMenu popmenu;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMymenuView)
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
	virtual ~CMymenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMymenuView)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mymenuView.cpp
inline CMymenuDoc* CMymenuView::GetDocument()
   { return (CMymenuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYMENUVIEW_H__3BAD410E_4BBC_11D1_AB73_89774BBAD26D__INCLUDED_)
