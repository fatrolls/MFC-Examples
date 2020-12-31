#if !defined(AFX_SKINSCROLLBAR_H__F5B158D2_0277_45F4_B61A_4F41E69C8CFA__INCLUDED_)
#define AFX_SKINSCROLLBAR_H__F5B158D2_0277_45F4_B61A_4F41E69C8CFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SkinScrollBar.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CSkinScrollBar window
class CSkinScrollBar : public CScrollBar
{
// Construction
public:
	CSkinScrollBar();
	HBITMAP	m_hBmp;
	int		m_nWid;
	int		m_nFrmHei;
	int		m_nHei;

	SCROLLINFO	m_si;
	BOOL		m_bDrag;
	CPoint		m_ptDrag;
	int			m_nDragPos;

	UINT		m_uClicked;
	BOOL		m_bNotify;
	UINT		m_uHtPrev;
	BOOL		m_bPause;
	BOOL		m_bTrace;
// Attributes
public:

// Operations
public:
	


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinScrollBar)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawArrow(UINT uArrow,int nState);
	void SetBitmap(HBITMAP hBmp);
	BOOL IsVertical();
	virtual ~CSkinScrollBar();

	// Generated message map functions
protected:
	void DrawThumb(CDC *pDestDC, RECT *pDestRect, CDC *pSourDC, RECT *pSourRect);
	void TileBlt(CDC *pDestDC,RECT *pDestRect,CDC *pSourDC,RECT *pSourRect);
	RECT GetRect(UINT uSBCode);
	RECT GetImageRect(UINT uSBCode,int nState=0);
	UINT HitTest(CPoint pt);
	//{{AFX_MSG(CSkinScrollBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSCROLLBAR_H__F5B158D2_0277_45F4_B61A_4F41E69C8CFA__INCLUDED_)
