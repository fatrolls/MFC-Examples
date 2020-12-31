#if !defined(AFX_COLORSELECTOR_H__07E27536_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
#define AFX_COLORSELECTOR_H__07E27536_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ColorSelector.h : header file
//

#define COLORS_NUM	20

/////////////////////////////////////////////////////////////////////////////
// CColorSelector window

class CColorSelector : public CButton
{
// Construction
public:
	CColorSelector();

// Attributes
protected:
	COLORREF		m_rgbColors [COLORS_NUM];
	CRect			m_Rect [COLORS_NUM];
	BOOL			m_bReady;
	int				m_iSel;

// Operations
public:
	BOOL SelectColor (COLORREF color);
	COLORREF GetColor () const
	{
		ASSERT (m_iSel >= 0 && m_iSel < COLORS_NUM);
		return m_rgbColors [m_iSel];
	}

protected:
	void InitColors ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorSelector)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorSelector();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorSelector)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG

	virtual void DrawItem (LPDRAWITEMSTRUCT lpDIS);
	void Adjust ();
	int HitTest (POINT point) const;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSELECTOR_H__07E27536_C6D9_11D1_A647_00A0C93A70EC__INCLUDED_)
