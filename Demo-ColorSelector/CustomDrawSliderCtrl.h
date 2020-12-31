#if !defined(AFX_CUSTOMDRAWSLIDERCTRL_H__A5580780_B870_40D7_AC86_ED4F9CDEDC4A__INCLUDED_)
#define AFX_CUSTOMDRAWSLIDERCTRL_H__A5580780_B870_40D7_AC86_ED4F9CDEDC4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomDrawSliderCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomDrawSliderCtrl window

class CCustomDrawSliderCtrl : public CSliderCtrl
{
// Construction
public:
	CCustomDrawSliderCtrl();				// default constructor
	CCustomDrawSliderCtrl( COLORREF cr );	// constructs the control and sets its primary color


// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomDrawSliderCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	COLORREF GetShadowColor() const;
	COLORREF GetHiliteColor() const;
	COLORREF GetPrimaryColor() const;
	void SetPrimaryColor( COLORREF cr );
	virtual ~CCustomDrawSliderCtrl();

	// Generated message map functions
protected:

	COLORREF m_crPrimary;
	COLORREF m_crShadow;
	COLORREF m_crHilite;
	COLORREF m_crMidShadow;
	COLORREF m_crDarkerShadow;

	CBrush m_normalBrush;
	CBrush m_focusBrush;

	//{{AFX_MSG(CCustomDrawSliderCtrl)
	afx_msg void OnReflectedCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMDRAWSLIDERCTRL_H__A5580780_B870_40D7_AC86_ED4F9CDEDC4A__INCLUDED_)
