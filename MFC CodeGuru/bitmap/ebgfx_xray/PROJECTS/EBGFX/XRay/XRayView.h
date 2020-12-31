// XRayView.h : interface of the CXRayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XRAYVIEW_H__1394446F_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
#define AFX_XRAYVIEW_H__1394446F_CFB1_11D1_91CA_0020AFF82585__INCLUDED_

#include "..\Dib.h"	// Added by ClassView
#include "..\DrawDib.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CXRayView : public CView
{
protected: // create from serialization only
	CXRayView();
	DECLARE_DYNCREATE(CXRayView)

// Attributes
public:
	CXRayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXRayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_Alpha;
	COLORREF m_Color;

	CDrawDib m_DrawDib;
	CDib m_Layer0;
	int m_ScreenX, m_ScreenY;

	HRESULT OnParentMove ( LPARAM, WPARAM );

	virtual ~CXRayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXRayView)
	afx_msg void OnAlphaNone();
	afx_msg void OnUpdateAlphaNone(CCmdUI* pCmdUI);
	afx_msg void OnAlphaAlpha();
	afx_msg void OnUpdateAlphaAlpha(CCmdUI* pCmdUI);
	afx_msg void OnAlphaStippled();
	afx_msg void OnUpdateAlphaStippled(CCmdUI* pCmdUI);
	afx_msg void OnColor();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in XRayView.cpp
inline CXRayDoc* CXRayView::GetDocument()
   { return (CXRayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XRAYVIEW_H__1394446F_CFB1_11D1_91CA_0020AFF82585__INCLUDED_)
