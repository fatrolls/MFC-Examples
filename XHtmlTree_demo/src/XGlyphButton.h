// XGlyphButton.cpp  Version 1.1
//
// Author: Hans Dietrich
//         hdietrich2@hotmail.com
//
// This software is released into the public domain.  You are free to use it
// in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this software
// may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef XGLYPHBUTTON_H
#define XGLYPHBUTTON_H

/////////////////////////////////////////////////////////////////////////////
// CXGlyphButton window

class CXGlyphButton : public CButton
{
// Construction/Destruction
public:
	CXGlyphButton();
	virtual ~CXGlyphButton();

	// some predefined glyphs from WingDings
	enum 
	{
		BTN_DELETE            = 0xFB, 
		BTN_CHECK             = 0xFC,
		BTN_LEFTARROW         = 0xDF,
		BTN_RIGHTARROW        = 0xE0,
		BTN_UPARROW           = 0xE1,
		BTN_DOWNARROW         = 0xE2,
		BTN_HOLLOW_LEFTARROW  = 0xEF,
		BTN_HOLLOW_RIGHTARROW = 0xF0,
		BTN_HOLLOW_UPARROW    = 0xF1,
		BTN_HOLLOW_DOWNARROW  = 0xF2
	};

	void SetCharSet(BYTE bCharSet);
	void SetFaceName(LPCTSTR lpszFaceName);
	void SetFont(LOGFONT* plf);
	void SetFont(CFont* pFont);
	void SetGlyph(UINT cGlyph);
	void SetGlyph(LOGFONT* plf, UINT cGlyph);
	void SetGlyph(CFont* pFont, UINT cGlyph);
	void SetGlyph(LONG lHeight, LONG lPointSize, LONG lWeight, 
			LPCTSTR lpszFaceName, UINT cGlyph);
	void SetGlyph(LONG lPointSize, LPCTSTR lpszFaceName, UINT cGlyph);
	void SetHeight(LONG lHeight);
	void SetPointSize(LONG lPointSize);
	void SetWeight(LONG lWeight);
	void SetWingDingButton(UINT nButton);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGlyphButton)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	LONG GetFontHeight(LONG nPointSize);
	LONG GetFontPointSize(LONG nHeight);
	void ReconstructFont();

	LOGFONT		m_lf;
	UINT		m_cGlyph;
	CFont		m_font;

	// Generated message map functions

	//{{AFX_MSG(CXGlyphButton)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XGLYPHBUTTON_H
