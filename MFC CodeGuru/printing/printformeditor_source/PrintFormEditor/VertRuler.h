#if !defined(AFX_VERTRULER_H__A98AD0D2_095E_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_VERTRULER_H__A98AD0D2_095E_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// VertRuler.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVertRuler window

class CVertRuler : public CButton
{
// Construction
public:
	CVertRuler();

// Attributes
public:
	int iFrom, iTo, iDiv, iPos, iTextStep, iGreatStep, iSmallStep, iTextDiv;
	CFont ft;
	COLORREF	crBack, crText, crLines;
	int	  yMouse;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVertRuler)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawMouse(const int y);
	void SetRange(const int r1, const int r2);
	void SetPos(const int pos);
	virtual ~CVertRuler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVertRuler)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VERTRULER_H__A98AD0D2_095E_11D2_840B_0000B43382FE__INCLUDED_)
