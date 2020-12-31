// ProgressDemoView.h : interface of the CProgressDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROGRESSDEMOVIEW_H__DA78950C_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_PROGRESSDEMOVIEW_H__DA78950C_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CProgressDemoView : public CView
{
protected: // create from serialization only
	CProgressDemoView();
	DECLARE_DYNCREATE(CProgressDemoView)

// Attributes
public:
	CProgressDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProgressDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CProgressDemoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ProgressDemoView.cpp
inline CProgressDemoDoc* CProgressDemoView::GetDocument()
   { return (CProgressDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSDEMOVIEW_H__DA78950C_5B4D_11D1_ABBA_00A0243D1382__INCLUDED_)
