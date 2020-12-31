// ex21bView.h : interface of the CEx21bView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EX21BVIEW_H__CBB31410_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
#define AFX_EX21BVIEW_H__CBB31410_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEx21bView : public CView
{
protected: // create from serialization only
	CEx21bView();
	DECLARE_DYNCREATE(CEx21bView)

// Attributes
public:
	CEx21bDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx21bView)
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
	virtual ~CEx21bView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CEx21bView)
	afx_msg void OnTestEx21cdll();
	afx_msg void OnTestEx21ddll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ex21bView.cpp
inline CEx21bDoc* CEx21bView::GetDocument()
   { return (CEx21bDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX21BVIEW_H__CBB31410_974D_11D0_BED2_00C04FC2A0C2__INCLUDED_)
