#pragma once
// popupcolorbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPopupColorBar window

#include "ListCtrlCellWnd.h"

class CCellColorCtrl;
class CColorCtrl;

#define	FLAG_COLOR_SELECTED			0x00000001
#define FLAG_COLOR_HIGLIGHTED		0x00000002

struct COLOR_INFO
{
	COLORREF	m_ColorRef;
	LPCTSTR		m_Name;
	RECT		m_Rect;
	LONG		m_StatusFlag;

	COLOR_INFO(COLORREF	ColorRef = 0, LPCTSTR Name = _T(""), RECT Rect = RECT()) : m_ColorRef(ColorRef), m_Name(Name), m_Rect(Rect), m_StatusFlag(0)
	{}
};

class ColorInfoLess
{
public:
	bool operator () (const COLOR_INFO *a, const COLOR_INFO *b) const
	{
		return a->m_ColorRef < b->m_ColorRef;
	}
};

class CPopupColorBar : public CListCtrlCellWnd
{
// Construction
public:
	CPopupColorBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPopupColorBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPopupColorBar();
	void Create(HWND hParentWnd, CCellColorCtrl *pCellColorCtrl);
	BOOL PreTranslateMessage(MSG* pMsg);
	void GetBoundingRect(const RECT &rcCellBounding, RECT &rcBounding, BOOL Downwards = TRUE);
	void OpenDropDown(const COLORREF ColorRef);
	void OnEnter();	
	// Generated message map functions
protected:
	//{{AFX_MSG(CPopupColorBar)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CArray<COLOR_INFO>						m_ColorInfo;
	CRect									m_RectOther, m_RectOtherColor;

	short								m_ColorColumns, m_ColorRows, m_SelColor, m_HighlightColor;
	BOOL								m_ShowOtherButton, m_HighlightOtherButton, m_ShowOtherColor;
	COLORREF							m_ActiveColor;
	CToolTipCtrl						*m_pToolTip;
	void PaintButtons(CDC* pDC);
	void PaintButton(CDC* pDC, CRect Rect, COLORREF ColorRef, LONG status);
	void ComputeDetails();
	short GetColorButtonFromPt(const CPoint& point);
	void FireColor(COLORREF ColorRef);
	void DrawSeparator(CDC* pDC);
	void DrawOtherButton(CDC* pDC);
	void DisplayColorDialog();
};