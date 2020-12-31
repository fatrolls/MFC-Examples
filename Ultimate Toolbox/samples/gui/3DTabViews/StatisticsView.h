#if !defined(AFX_STATISTICSVIEW_H__BC7A1604_77E6_11D2_A76E_525400DAF3CE__INCLUDED_)
#define AFX_STATISTICSVIEW_H__BC7A1604_77E6_11D2_A76E_525400DAF3CE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// StatisticsView.h : header file
//

#include <afxcview.h>
#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CStatisticsView view

//class CStatisticsView : public COXTabViewPage<CListView>
class CStatisticsView : public CListView
{
protected:
	CStatisticsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CStatisticsView)

// Attributes
public:

// Operations
public:
	CTabViewsDoc* GetDocument();

protected:
	void Populate(BOOL bForFirstTime=FALSE);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatisticsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CStatisticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CStatisticsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatisticsView.cpp
inline CTabViewsDoc* CStatisticsView::GetDocument()
   { return (CTabViewsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATISTICSVIEW_H__BC7A1604_77E6_11D2_A76E_525400DAF3CE__INCLUDED_)
