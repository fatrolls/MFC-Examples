// gridlistView.h : interface of the CGridlistView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRIDLISTVIEW_H__92CA598F_9434_11D1_88D5_444553540000__INCLUDED_)
#define AFX_GRIDLISTVIEW_H__92CA598F_9434_11D1_88D5_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGridlistView : public CView
{
protected: // create from serialization only
	CGridlistView();
	DECLARE_DYNCREATE(CGridlistView)

// Attributes
public:
	CGridlistDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridlistView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGridlistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGridlistView)
	afx_msg void OnTestGridlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in gridlistView.cpp
inline CGridlistDoc* CGridlistView::GetDocument()
   { return (CGridlistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDLISTVIEW_H__92CA598F_9434_11D1_88D5_444553540000__INCLUDED_)
