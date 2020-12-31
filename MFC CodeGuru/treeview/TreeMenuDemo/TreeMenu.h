#if !defined(AFX_TREEMENU_H__56B166C1_BF6F_11D1_9247_0080C882060B__INCLUDED_)
#define AFX_TREEMENU_H__56B166C1_BF6F_11D1_9247_0080C882060B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CoolTreeMenu.h : header file
//
#include "CoolTreeCtrl.h"



/////////////////////////////////////////////////////////////////////////////
// CTreeMenu window

class CTreeMenu : public CCoolTreeCtrl
{
// Construction
public:
	CTreeMenu();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMenu)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeMenu();
	void SetSelBkColor(COLORREF clrSelBkColor) { m_clrSelBkColor = clrSelBkColor;}
	void SetSelTextColor(COLORREF clrSelTextColor) { m_clrSelTextColor = clrSelTextColor;}

	// Generated message map functions
protected:
	COLORREF	m_clr3DFace;
	COLORREF	m_clr3DShadow;
	COLORREF	m_clr3DDkShadow;
	COLORREF	m_clr3DLight;
	COLORREF	m_clr3DHilight;
	COLORREF	m_clrSelBkColor;
	COLORREF	m_clrSelTextColor;


	CPoint	m_point;

	//{{AFX_MSG(CTreeMenu)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg void OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEMENU_H__56B166C1_BF6F_11D1_9247_0080C882060B__INCLUDED_)
