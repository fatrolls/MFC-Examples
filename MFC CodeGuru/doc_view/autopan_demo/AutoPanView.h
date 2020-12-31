// AutoPanView.h : interface of the CAutoPanView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPANVIEW_H__4E9C2720_CFCD_11D1_87BA_400011900025__INCLUDED_)
#define AFX_AUTOPANVIEW_H__4E9C2720_CFCD_11D1_87BA_400011900025__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAutoPanView : public CScrollView
{
protected: // create from serialization only
	CAutoPanView();
	DECLARE_DYNCREATE(CAutoPanView)

// Attributes
public:
	CAutoPanDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoPanView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoPanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoPanView)
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoPanView.cpp
inline CAutoPanDoc* CAutoPanView::GetDocument()
   { return (CAutoPanDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOPANVIEW_H__4E9C2720_CFCD_11D1_87BA_400011900025__INCLUDED_)
