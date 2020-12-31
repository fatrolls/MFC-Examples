// ex06bView.h : interface of the CEx06bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX06BVIEW_H__6F45AD99_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX06BVIEW_H__6F45AD99_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx06bView : public CView
{
protected: // create from serialization only
	CEx06bView();
	DECLARE_DYNCREATE(CEx06bView)

// Attributes
public:
	CEx06bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx06bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx06bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex06bView.cpp
inline CEx06bDoc* CEx06bView::GetDocument()
   { return (CEx06bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06BVIEW_H__6F45AD99_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
