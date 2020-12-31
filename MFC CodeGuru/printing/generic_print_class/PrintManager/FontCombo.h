#if !defined(AFX_FONTCOMBO_H__8DA387F0_9D67_11D1_8BAC_0000B43382FE__INCLUDED_)
#define AFX_FONTCOMBO_H__8DA387F0_9D67_11D1_8BAC_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FontCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFontCombo window
typedef enum {FONTS} STYLE;

class CFontCombo : public CComboBox
{
// Construction
public:
	CFontCombo();
	CFontCombo(STYLE);

// Attributes
public:
	void SetHilightColors (COLORREF hilight,COLORREF hilightText)
	{
		m_clrHilight = hilight;
		m_clrHilightText = hilightText;
	};
	void SetNormalColors (COLORREF clrBkgnd,COLORREF clrText)
	{
		m_clrNormalText = clrText;
		m_clrBkgnd = clrBkgnd;
	};
	static BOOL CALLBACK EnumFontProc (LPLOGFONT lplf, LPTEXTMETRIC lptm, DWORD dwType, LPARAM lpData);
	void FillFonts ();
	int	GetSelFont (LOGFONT&);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFontCombo)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFontCombo();
	void InitFonts ();

	// Generated message map functions
protected:
	STYLE m_enStyle;
	COLORREF m_clrHilight;
	COLORREF m_clrNormalText;
	COLORREF m_clrHilightText;
	COLORREF m_clrBkgnd;
	BOOL m_bInitOver;
	void DrawDefault (LPDRAWITEMSTRUCT);
	void DrawFont(LPDRAWITEMSTRUCT);
	//{{AFX_MSG(CFontCombo)
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg	long OnInitFonts (WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONTCOMBO_H__8DA387F0_9D67_11D1_8BAC_0000B43382FE__INCLUDED_)
