// ex13bView.h : interface of the CEx13bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX13BVIEW_H__0D7C0115_71B1_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
#define AFX_EX13BVIEW_H__0D7C0115_71B1_11D0_8FDA_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx13bView : public CView
{
protected: // create from serialization only
	CEx13bView();
	DECLARE_DYNCREATE(CEx13bView)

// Attributes
public:
	CEx13bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx13bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx13bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx13bView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex13bView.cpp
inline CEx13bDoc* CEx13bView::GetDocument()
   { return (CEx13bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX13BVIEW_H__0D7C0115_71B1_11D0_8FDA_00C04FC2A0C2__INCLUDED_)
