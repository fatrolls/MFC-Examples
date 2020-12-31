// ex08aView.h : interface of the CEx08aView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX08AVIEW_H__19177893_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08AVIEW_H__19177893_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx08aView : public CView
{
protected: // create from serialization only
	CEx08aView();
	DECLARE_DYNCREATE(CEx08aView)

// Attributes
public:
	CEx08aDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08aView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx08aView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx08aView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex08aView.cpp
inline CEx08aDoc* CEx08aView::GetDocument()
   { return (CEx08aDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08AVIEW_H__19177893_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
