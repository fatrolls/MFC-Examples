// RotoZoomView.h : interface of the CRotoZoomView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROTOZOOMVIEW_H__B368F86D_CEF7_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_ROTOZOOMVIEW_H__B368F86D_CEF7_11D1_91CA_0020AFF82585__INCLUDED_

#include "Dib.h"
#include "DrawDib.h"
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRotoZoomView : public CView
{
protected: // create from serialization only
	CRotoZoomView();
	DECLARE_DYNCREATE(CRotoZoomView)

// Attributes
public:
	CRotoZoomDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRotoZoomView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_Alpha;
	BOOL m_MotionBlur;
	BOOL m_DoubleSize;

	MMRESULT m_MMTimer;
	float Cosines[360];
	float Sines[360];
	int m_Angle;
	float m_Zoom;
	float m_ZoomFactor;

	CDib m_Tile;
	CDib m_Layer0;
	CDib m_Layer1;
	CDrawDib m_DrawDib;

	HRESULT IsDoubleSize ( WPARAM, LPARAM );

	virtual ~CRotoZoomView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRotoZoomView)
	afx_msg void OnMotionBlur();
	afx_msg void OnUpdateMotionBlur(CCmdUI* pCmdUI);
	afx_msg void OnDoubleSize();
	afx_msg void OnUpdateDoubleSize(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAlphaNone();
	afx_msg void OnUpdateAlphaNone(CCmdUI* pCmdUI);
	afx_msg void OnAlphaAlpha();
	afx_msg void OnUpdateAlphaAlpha(CCmdUI* pCmdUI);
	afx_msg void OnAlphaStippled();
	afx_msg void OnUpdateAlphaStippled(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in RotoZoomView.cpp
inline CRotoZoomDoc* CRotoZoomView::GetDocument()
   { return (CRotoZoomDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTOZOOMVIEW_H__B368F86D_CEF7_11D1_91CA_0020AFF82585__INCLUDED_)
