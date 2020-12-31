// ImageViewerView.h : interface of the CImageViewerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEVIEWERVIEW_H__AEC8616F_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
#define AFX_IMAGEVIEWERVIEW_H__AEC8616F_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OXImageViewer.h"

class CImageViewerView : public CView
{
protected: // create from serialization only
	CImageViewerView();
	DECLARE_DYNCREATE(CImageViewerView)

// Attributes
public:
	CImageViewerDoc* GetDocument();
	inline COXImageViewer* GetImageViewer() { return &m_imageViewer; }

protected:
	COXImageViewer m_imageViewer;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageViewerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageViewerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageViewerView.cpp
inline CImageViewerDoc* CImageViewerView::GetDocument()
   { return (CImageViewerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEVIEWERVIEW_H__AEC8616F_D4E6_11D2_B476_00E0291A4FD3__INCLUDED_)
