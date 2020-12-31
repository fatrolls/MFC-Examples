// SketchView.h : interface of the CSketchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKETCHVIEW_H__1260AFCD_9CAC_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_SKETCHVIEW_H__1260AFCD_9CAC_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSketchView : public CScrollView
{
protected: // create from serialization only
	CSketchView();
	DECLARE_DYNCREATE(CSketchView)

// Attributes
public:
	CSketchDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSketchView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSketchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void InvertLine (CDC* pDC, POINT from, POINT to);
	CPoint m_ptFrom;
	CPoint m_ptTo;
	HCURSOR m_hCursor;
	//{{AFX_MSG(CSketchView)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SketchView.cpp
inline CSketchDoc* CSketchView::GetDocument()
   { return (CSketchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKETCHVIEW_H__1260AFCD_9CAC_11D2_8E53_006008A82731__INCLUDED_)
