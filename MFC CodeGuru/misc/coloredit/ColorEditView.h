// ColorEditView.h : interface of the CColorEditView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_COLOREDITVIEW_H__F6898253_462B_11D1_B99D_00A0C9763A0A__INCLUDED_)
#define AFX_COLOREDITVIEW_H__F6898253_462B_11D1_B99D_00A0C9763A0A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "memdc.h"

//  Copyright (c) 1996-1997, Keith Rule
//  You may freely use or modify this code provided this 
//  copyright is included in all derived versions.

class CColorEditView : public CScrollView
{
protected: // create from serialization only
	CColorEditView();
	DECLARE_DYNCREATE(CColorEditView)

// Attributes
public:
	CColorEditDoc* GetDocument();

// Operations
public:
	long						m_selectStart;
	long						m_selectEnd;
	long						m_caret;
	COLORREF					m_bkColor;
	BOOL						m_mouseDown;
	BOOL						m_mouseMove;
	long						m_indent;
	long						m_tabSize;
	CFont						m_font;
	CPoint						m_caretPos;
	BOOL						m_caretVisible;
	long						m_cHeight;
	long						m_autoScrollCount;
	CSize						m_scrollSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEditView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint m_mousePosition;
	void AutoScroll();
	BOOL m_scrollTimerEnabled;
	void ScrollToCaret();
	long m_nLinesPerPage;
	long m_nPageEndLine;
	long m_nPageStartLine;
	long m_nCurPage;
	void CheckPoint();
	void EnableCheckPoint();
	void DisableCheckPoint();
	BOOL ReplaceSelection(CString string);
	CPoint TextPosition2ScreenCoord(CDC* pDC, long pos);
	long GetSearchPosition();
	void ScrollToSelection();
	void SetSelection(long start, long end);
	void ScrollToCurrent();
	void SetCurrentPosition(long position);
	long CurrentPosition();
	void CalcScrollSize(CDC* pDC = NULL);
	long SelectionPoint(CPoint point);
	CPoint DrawText(CDC * pDC, CPoint pos, int line, BOOL bDrawSelection = TRUE);
	CSize GetScrollSize(CDC* pDC);
	CPoint GetExtent(CDC *pDC, const CString& string, long xoffset = 0, long line = 1);
	CPoint GetCaretPos(CDC* pDC, long xoffset);
	virtual ~CColorEditView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CColorEditView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditFind();
	afx_msg void OnUpdateEditFind(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ColorEditView.cpp
inline CColorEditDoc* CColorEditView::GetDocument()
   { return (CColorEditDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDITVIEW_H__F6898253_462B_11D1_B99D_00A0C9763A0A__INCLUDED_)
