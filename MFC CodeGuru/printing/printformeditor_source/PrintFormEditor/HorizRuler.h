#if !defined(AFX_HORIZRULER_H__17660EBE_0940_11D2_840B_0000B43382FE__INCLUDED_)
#define AFX_HORIZRULER_H__17660EBE_0940_11D2_840B_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// HorizRuler.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHorizRuler window

class CHorizRuler : public CButton
{
// Construction
public:
	CHorizRuler();

// Attributes
public:
	int iFrom, iTo, iDiv, iPos, iTextStep, iGreatStep, iSmallStep, iTextDiv;
	CFont ft;
	COLORREF	crBack, crText, crLines;
	int	  xMouse;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHorizRuler)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawMouse(const int x);
	void SetRange(const int r1, const int r2);
	void SetPos(const int pos);
	virtual ~CHorizRuler();

	// Generated message map functions
protected:
	//{{AFX_MSG(CHorizRuler)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HORIZRULER_H__17660EBE_0940_11D2_840B_0000B43382FE__INCLUDED_)
