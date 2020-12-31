// ScrollDemoView.h : interface of the CScrollDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCROLLDEMOVIEW_H__DCCF4E0D_9735_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_SCROLLDEMOVIEW_H__DCCF4E0D_9735_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScrollDemoView : public CScrollView
{
protected: // create from serialization only
	CScrollDemoView();
	DECLARE_DYNCREATE(CScrollDemoView)

// Attributes
public:
	CScrollDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScrollDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_bSmooth;
	void GetCellRect (int row, int col, LPRECT pRect);
	void DrawAddress (CDC* pDC, int row, int col);
	void DrawPointer (CDC* pDC, int row, int col, BOOL bHighlight);
	CFont m_font;
	int m_nCurrentCol;
	int m_nCurrentRow;
	int m_nRibbonWidth;
	int m_nCellHeight;
	int m_nCellWidth;
	//{{AFX_MSG(CScrollDemoView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ScrollDemoView.cpp
inline CScrollDemoDoc* CScrollDemoView::GetDocument()
   { return (CScrollDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLDEMOVIEW_H__DCCF4E0D_9735_11D2_8E53_006008A82731__INCLUDED_)
