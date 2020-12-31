// scribvw.h : interface of the CScribView class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "OXZoomVw.h" // Should be REMARKED IF USING OXClass.h in stdafx.h

// Derive the view from COXZoomView to add scrolling functionality.
class CScribView : public COXZoomView
{
protected: // create from serialization only
	CScribView();
	DECLARE_DYNCREATE(CScribView)

// Attributes
public:
	CScribDoc* GetDocument();
     
protected:
	CStroke*    m_pStrokeCur;   // the stroke in progress
	CPoint      m_ptPrev;       // the last mouse pt in the stroke in progress
	CPoint		m_ptStart;		// starting point of zooming

    enum { IDLE, DRAWING, ZOOMING } action; 
	
// Operations
public:

// Implementation
public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
	virtual ~CScribView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CScribView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoom100();
	afx_msg void OnUpdateZoom100(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnZoomToWindow();
	afx_msg void OnUpdateZoom(CCmdUI* pCmdUI);
	afx_msg void OnZoomUp();
	afx_msg void OnUpdateZoomUp(CCmdUI* pCmdUI);
	afx_msg void OnZoomDown();
	afx_msg void OnUpdateZoomDown(CCmdUI* pCmdUI);
	afx_msg void OnWindowDuplicate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in scribvw.cpp
inline CScribDoc* CScribView::GetDocument()
   { return (CScribDoc*) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
