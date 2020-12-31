// XColourPopup.h : header file
//
// Written by Chris Maunder (chrismaunder@codeguru.com)
// Extended by Alexander Bischofberger (bischofb@informatik.tu-muenchen.de)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is
// not sold for profit without the authors written consent, and
// providing that this notice and the authors name is included. If
// the source code in  this file is used in any commercial application
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// It's free - so you get what you pay for.


#ifndef XCOLOURPOPUP_H
#define XCOLOURPOPUP_H

// CXColourPopup messages
#define CPN_SELCHANGE        WM_USER + 1001        // Color Picker Selection change
#define CPN_DROPDOWN         WM_USER + 1002        // Color Picker drop down
#define CPN_CLOSEUP          WM_USER + 1003        // Color Picker close up
#define CPN_SELENDOK         WM_USER + 1004        // Color Picker end OK
#define CPN_SELENDCANCEL     WM_USER + 1005        // Color Picker end (cancelled)

// To hold the colors and their names
typedef struct
{
	COLORREF	crColor;
	TCHAR *		szName;
	int			nSystemColor;
}
ColorTableEntry;

/////////////////////////////////////////////////////////////////////////////
// CXColourPopup window

class CXColourPopup : public CWnd
{
// Construction
public:
	CXColourPopup();

	CXColourPopup(CWnd * pParentWnd,
				CPoint p,
				COLORREF crColor = RGB(255,255,255),
				COLORREF * pCustomColors = NULL,
				int nSelectedRow = -1,
				int nSelectedCol = -1,
				LPCTSTR szCustomText = NULL);

	virtual ~CXColourPopup();

// Attributes
public:

// Operations
public:
	BOOL Create(CPoint p, COLORREF crColor, CWnd * pParentWnd,
		LPCTSTR szCustomText = NULL);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXColourPopup)
public:
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	void Init();
	BOOL GetCellRect(int row, int col, const LPRECT & rect);
	void SetWindowSize();
	void CreateToolTips();
	void ChangeSelection(int row, int col);
	void EndSelection(int nMessage);
	void DrawCell(CDC * pDC, int row, int col);
	COLORREF GetColor(int row, int col)
	{
		return (0x00FFFFFF & m_crColors[row * m_nNumColumns + col].crColor);
	}
	void SetColor(int row, int col, COLORREF rgb)
	{
		m_crColors[row * m_nNumColumns + col].crColor = rgb;
	}
	LPCTSTR GetColorName(int row, int col)
	{
		return m_crColors[row * m_nNumColumns + col].szName;
	}

	// protected attributes
protected:
	static ColorTableEntry m_crColors[];
	COLORREF *     m_pCustomColors;
	int            m_nNumColors;
	int            m_nNumColumns, m_nNumRows;
	int            m_nBoxSize, m_nMargin;
	int            m_nCurrentRow, m_nCurrentCol;
	int            m_nSelectedRow, m_nSelectedCol;
	BOOL           m_bShowCustom;
	CString        m_strCustomText;
	CRect          m_TextRect, m_WindowRect, m_DividerRect;
	CFont          m_Font;
	COLORREF       m_crInitialColor, m_crColor;
	CToolTipCtrl   m_ToolTip;
	CWnd *         m_pParent;

	// Generated message map functions
protected:
	//{{AFX_MSG(CXColourPopup)
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif //XCOLOURPOPUP_H
