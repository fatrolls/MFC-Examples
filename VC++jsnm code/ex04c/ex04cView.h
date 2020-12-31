// ex04cView.h : interface of the CEx04cView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX04CVIEW_H__94911C0B_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04CVIEW_H__94911C0B_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx04cView : public CScrollView
{
protected: // create from serialization only
	CEx04cView();
	DECLARE_DYNCREATE(CEx04cView)

// Attributes
public:
	CEx04cDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04cView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEx04cView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx04cView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_nColor;
	CRect m_rectEllipse;
};

#ifndef _DEBUG  // debug version in ex04cView.cpp
inline CEx04cDoc* CEx04cView::GetDocument()
   { return (CEx04cDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04CVIEW_H__94911C0B_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
