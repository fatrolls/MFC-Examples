// ex04bView.h : interface of the CEx04bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04BVIEW_H__94911C1D_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04BVIEW_H__94911C1D_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx04bView : public CView
{
protected: // create from serialization only
	CEx04bView();
	DECLARE_DYNCREATE(CEx04bView)

// Attributes
public:
	CEx04bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04bView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx04bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04bView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nColor;
	CRect m_rectEllipse;
};

#ifndef _DEBUG  // debug version in ex04bView.cpp
inline CEx04bDoc* CEx04bView::GetDocument()
   { return (CEx04bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04BVIEW_H__94911C1D_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
