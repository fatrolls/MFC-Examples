// ex06aView.h : interface of the CEx06aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX06AVIEW_H__0A7D2CB7_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
#define AFX_EX06AVIEW_H__0A7D2CB7_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx06aView : public CView
{
protected: // create from serialization only
	CEx06aView();
	DECLARE_DYNCREATE(CEx06aView)

// Attributes
public:
	CEx06aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx06aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx06aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex06aView.cpp
inline CEx06aDoc* CEx06aView::GetDocument()
   { return (CEx06aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06AVIEW_H__0A7D2CB7_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
