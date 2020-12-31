// TabView.h : interface of the CTabView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABVIEW_H__E22ADFB0_5063_11D1_8E9B_4854E827046F__INCLUDED_)
#define AFX_TABVIEW_H__E22ADFB0_5063_11D1_8E9B_4854E827046F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTabView : public CListView
{
protected: // create from serialization only
	CTabView();
	DECLARE_DYNCREATE(CTabView)

// Attributes
public:
	CTabDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabView)
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
	virtual ~CTabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTabView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TabView.cpp
inline CTabDoc* CTabView::GetDocument()
   { return (CTabDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABVIEW_H__E22ADFB0_5063_11D1_8E9B_4854E827046F__INCLUDED_)
