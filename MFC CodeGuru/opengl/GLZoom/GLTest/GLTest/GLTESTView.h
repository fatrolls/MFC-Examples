// GLView.h : interface of the CGLTESTView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLVIEW_H__9EAE1CB1_645A_11D1_959E_B829D7A5296C__INCLUDED_)
#define AFX_GLVIEW_H__9EAE1CB1_645A_11D1_959E_B829D7A5296C__INCLUDED_

#include "entity.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CGLTESTView : public CView
{
public:
	DECLARE_DYNCREATE(CGLTESTView)
	CGLTESTView();
	virtual BOOL MakeActive();
	virtual void SetupOrtho(int cx, int cy);
	virtual void SetupOrtho();
	static void GetCurrent(HDC& hdc, HGLRC& rc);
	static BOOL SetCurrent(HDC hdc, HGLRC rc); 

protected: // create from serialization only
	BOOL RenderScene();
	GLdouble xOrg;
	GLdouble xMax;
	GLdouble yOrg;
	GLdouble yMax;
	GLdouble zMax;
	GLdouble m_PixelX;
	GLdouble m_PixelY;
	VERTEX m_StartPoint;
	VERTEX m_EndPoint;
	VERTEX m_MovePoint;
	VERTEX m_PrevZoomLeft;
	VERTEX m_PrevZoomRight;
	CPoint m_CursorPosition;
	CPoint m_StartPosition;
	BOOL m_FirstPickPoint;
	BOOL m_CanZoomPrev;
	int currTool;
	int	m_width, m_height; // the size of the window

	virtual void DrawZoomRect();
	virtual void DrawRubberBand();
	virtual BOOL InitializeOpenGL();
	virtual BOOL SetupPixelFormat( void );
	virtual BOOL SetupViewport(int cx, int cy);
	virtual void SetLimits();

	int		m_PixelFormat;
	HGLRC	m_hRC;
	CDC*	m_pDC;
   	CString	m_WindowTitle;

public:
	CGLTESTDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLTESTView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGLTESTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CGLTESTView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnZoomWindow();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnZoomOut();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomPrevious();
	afx_msg void OnPan();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnUpdateZoomWindow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomPrevious(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GLView.cpp
inline CGLTESTDoc* CGLTESTView::GetDocument()
   { return (CGLTESTDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLVIEW_H__9EAE1CB1_645A_11D1_959E_B829D7A5296C__INCLUDED_)
