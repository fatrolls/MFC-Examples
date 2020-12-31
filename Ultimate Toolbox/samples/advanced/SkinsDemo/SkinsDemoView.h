// SkinsDemoView.h : interface of the CSkinsDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKINSDEMOVIEW_H__5CCC63AA_7818_4647_B917_01BF3EBC90A8__INCLUDED_)
#define AFX_SKINSDEMOVIEW_H__5CCC63AA_7818_4647_B917_01BF3EBC90A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXSkinnedView.h"

// STEP 8: Derive your view class from COXSkinnedView<...>
#define BASEVIEW CView
class CSkinsDemoView : public COXSkinnedView<BASEVIEW>
{
protected: // create from serialization only
	CSkinsDemoView();
	DECLARE_DYNCREATE(CSkinsDemoView)

// Attributes
public:
	CSkinsDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinsDemoView)
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
	virtual ~CSkinsDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSkinsDemoView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnItem1();
	afx_msg void OnItem2();
	afx_msg void OnUpdateItem2(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SkinsDemoView.cpp
inline CSkinsDemoDoc* CSkinsDemoView::GetDocument()
   { return (CSkinsDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDEMOVIEW_H__5CCC63AA_7818_4647_B917_01BF3EBC90A8__INCLUDED_)
