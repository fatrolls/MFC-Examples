#ifndef __COLORBTN_H__
#define __COLORBTN_H__

/////////////////////////////////////////////////////////////////////////////
// colorBtn.h : header file for the CColorButton class
//
// Written by Bob Ryan (ryan@cyberzone.net)
// Copyright (c) 1998.
//
// This code may be freely distributable in any application.  If
// you make any changes to the source, please let me know so that
// I might make a better version of the class.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
/////////////////////////////////////////////////////////////////////////////

class CColorButton : public CButton
{
DECLARE_DYNAMIC(CColorButton)
public:
	CColorButton(); 
	virtual ~CColorButton(); 

	BOOL Attach(const UINT nID, CWnd* pParent, 
		const COLORREF BGColor = RGB(192, 192, 192),		// gray button
		const COLORREF FGColor = RGB(1, 1, 1),				// black text 
		const COLORREF DisabledColor = RGB(128, 128, 128),	// dark gray disabled text
		const UINT nBevel = 2
	);

	
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	void DrawFrame(CDC *DC, CRect R, int Inset);
	void DrawFilledRect(CDC *DC, CRect R, COLORREF color);
	void DrawLine(CDC *DC, CRect EndPoints, COLORREF color);
	void DrawLine(CDC *DC, long left, long top, long right, long bottom, COLORREF color);
	void DrawButtonText(CDC *DC, CRect R, const char *Buf, COLORREF TextColor);

	COLORREF GetFGColor() { return m_fg; }	
	COLORREF GetBGColor() { return m_bg; }
    COLORREF GetDisabledColor() { return m_disabled; }
	UINT GetBevel() { return m_bevel; }

private:
	COLORREF m_fg, m_bg, m_disabled;
	UINT m_bevel;

};
#endif 
