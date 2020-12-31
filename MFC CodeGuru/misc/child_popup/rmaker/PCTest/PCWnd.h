#if !defined(AFX_PCWND_H__F811DE85_4497_11D1_80AD_080009CC78D8__INCLUDED_)
#define AFX_PCWND_H__F811DE85_4497_11D1_80AD_080009CC78D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PCWnd.h : header file
//

/////////////////////////////////////////////////////////////////////
// Class CPopChildWnd encapsulates a child-popup window, that can be dragged
// in or out of a parent-owner window to make itself instantly a
// child or popup.
// To use CPopChildWnd:
//	1. Embed a CPopChildWnd in the parent-owner class.
//	2. Call CPopChildWnd's Create function when the parent-owner is created.
//	3. Call CPopChildWnd's Destroy function when the parent-owner is 
//      destroyed.
//
// Normally you want to derive a class from CPopChildWnd and override its OnDraw
// member function.
//


class CPopChildWnd;

/////////////////////////////////////////////////////////////////////////////
// CPCWnd window

class CPCWnd : public CWnd
{
// Construction
public:
	CPCWnd();

	BOOL Create(CPopChildWnd* pOuter, DWORD dwStyle, const RECT& rect, 
		                              HWND hParentWnd, UINT nID);

// Attributes
public:

// Operations
public:
	CPoint GetOffPoint() { return m_point; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPCWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPCWnd)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message); 
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void Draw(CDC* pDC);

	CPoint m_point;
	CPopChildWnd* m_pOuter;
};


class CPopChildWnd
{
public:
	CPopChildWnd();
	~CPopChildWnd();

	void Create(HWND hParentOwnerWnd, CRect& rect, BOOL bChildFirst);
	void Destroy();

	void SetBkColor(COLORREF color=RGB(129, 129, 129)) 
	{ m_BkColor = color; }
	void SetPos(CRect& rect, BOOL bChildOnly=TRUE);

	void Switch();

protected:
	// overridable
	virtual void OnDraw(CDC* pDC, CPCWnd* pWnd);

	virtual BOOL OnMouseMove(CPCWnd* pWnd);
	virtual BOOL OnLButtonDown(CPCWnd* pWnd, CPoint point);
	virtual BOOL OnLButtonUp(CPCWnd* pWnd);
	COLORREF OnGetBkColor() { return m_BkColor; }
	virtual BOOL OnSetCursor(CPCWnd* pWnd, UINT nHitTest, UINT message);
	BOOL Captured();

	friend class CPCWnd;

	enum { TOUCH, INSIDE, OUTSIDE };
	int RectRect(CRect rc1, CRect rc2);
	BOOL OnChange(CPCWnd* pWnd);

	CPCWnd m_ChildWnd;
	CPCWnd m_PopupWnd;
	COLORREF m_BkColor;
	HWND m_hParentOwner;
	CPoint m_offPt;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCWND_H__F811DE85_4497_11D1_80AD_080009CC78D8__INCLUDED_)
