#if !defined(AFX_MYSTATIC_H__0AE83BA1_1C32_11D2_B475_B0D808C10000__INCLUDED_)
#define AFX_MYSTATIC_H__0AE83BA1_1C32_11D2_B475_B0D808C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MyStatic.h : header file
//

#include "OXStaticText.h"

#define WM_APP_CUSTOMIZE		WM_APP+122
#define WM_APP_CLOSE			WM_APP+123

/////////////////////////////////////////////////////////////////////////////
// CMyStatic window

class CMyStatic : public COXStaticText
{
// Construction
public:
	CMyStatic();

// Attributes
public:

protected:
	BOOL m_bPressedDown;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	afx_msg LONG OnMouseEnter(WPARAM wParam, LPARAM lParam);
	afx_msg LONG OnMouseLeave(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__0AE83BA1_1C32_11D2_B475_B0D808C10000__INCLUDED_)
