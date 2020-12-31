// BackgroundPainterView.h : interface of the CBackgroundPainterView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BACKGROUNDPAINTERVIEW_H__24987B21_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
#define AFX_BACKGROUNDPAINTERVIEW_H__24987B21_8DEB_11D2_A792_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBackgroundPainterView : public CView
{
protected: // create from serialization only
	CBackgroundPainterView();
	DECLARE_DYNCREATE(CBackgroundPainterView)

// Attributes
public:
	CBackgroundPainterDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgroundPainterView)
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
	virtual ~CBackgroundPainterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBackgroundPainterView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BackgroundPainterView.cpp
inline CBackgroundPainterDoc* CBackgroundPainterView::GetDocument()
   { return (CBackgroundPainterDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGROUNDPAINTERVIEW_H__24987B21_8DEB_11D2_A792_525400DAF3CE__INCLUDED_)
