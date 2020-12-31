// CaptionPainterEx.cpp: implementation of the CCaptionPainterEx class.
//
//////////////////////////////////////////////////////////////////////

#include "STDAFX.H"
#include "CaptionPainterEx.h"
#include "PixLib.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCaptionPainterEx::CCaptionPainterEx():
	m_pTitle(NULL)
{

}

CCaptionPainterEx::~CCaptionPainterEx()
{

}

#define COLOR_WHITE RGB(255,255,255)
#define COLOR_BLACK RGB(0,0,0)
#define NCOLORSHADES 64		// this many shades in gradient

//////////////////
// Paint custom caption.
// This is the function that actually does the shading. It creates a
// bitmap that's used to paint the caption. It looks horrible, but it's
// just a lot of bit-twiddling GDI stuff.
//
void CCaptionPainterEx::PaintCaption(BOOL bActive, const PAINTCAP* pc)
{
	if (!pc)
	{
		// pc = 0 means system setting change: invalidate fonts.
		m_fontCaption.DeleteObject();
		m_fontAcme.DeleteObject();
		return;
	}

	ASSERT(pc->m_pDC);
	CDC& dc = *(pc->m_pDC);

	int cxCap = pc->m_szCaption.cx;
	int cyCap = pc->m_szCaption.cy;

	if (!bActive) {
		// Inactive caption: don't do shading, just fill w/bg color
		PxLib::PaintRect(dc, 0, 0, cxCap, cyCap, GetSysColor(COLOR_INACTIVECAPTION));

	} else {
		// Active caption: do shading
		//
		COLORREF clrBG = GetSysColor(COLOR_ACTIVECAPTION); // background color
		int r = GetRValue(clrBG);				// red..
		int g = GetGValue(clrBG);				// ..green
		int b = GetBValue(clrBG);				// ..blue color vals
		int x = 5*cxCap/6;						// start 5/6 of the way right
		int w = x;								// width of area to shade
		int xDelta= max(w/NCOLORSHADES,1);		// width of one shade band

		// Paint far right 1/6 of caption the background color
		PxLib::PaintRect(dc, x, 0, cxCap-x, cyCap, clrBG);

		// Compute new color brush for each band from x to x + xDelta.
		// Excel uses a linear algorithm from black to normal, i.e.
		//
		//		color = CaptionColor * r
		//
		// where r is the ratio x/w, which ranges from 0 (x=0, left)
		// to 1 (x=w, right). This results in a mostly black title bar,
		// since we humans don't distinguish dark colors as well as light
		// ones. So instead, I use the formula
		//
		//		color = CaptionColor * [1-(1-r)^2]
		//
		// which still equals black when r=0 and CaptionColor when r=1,
		// but spends more time near CaptionColor. For example, when r=.5,
		// the multiplier is [1-(1-.5)^2] = .75, closer to 1 than .5.
		// I leave the algebra to the reader to verify that the above formula
		// is equivalent to
		//
		//		color = CaptionColor - (CaptionColor*(w-x)*(w-x))/(w*w)
		//
		// The computation looks horrendous, but it's only done once each
		// time the caption changes size; thereafter BitBlt'ed to the screen.
		//
		while (x > xDelta) {						// paint bands right to left
			x -= xDelta;							// next band
			int wmx2 = (w-x)*(w-x);					// w minus x squared
			int w2  = w*w;							// w squared
			PxLib::PaintRect(dc, x, 0, xDelta, cyCap,	
				RGB(r-(r*wmx2)/w2, g-(g*wmx2)/w2, b-(b*wmx2)/w2));
		}

		PxLib::PaintRect(dc,0,0,x,cyCap,COLOR_BLACK);  // whatever's left ==> black
	}

	// Use caption painter to draw icon and buttons
	int cxIcon  = DrawIcon(*pc);
	int cxButns = DrawButtons(*pc);

	// Now draw text. First Create fonts if needed
	//
	if (!m_fontCaption.m_hObject)
		CreateFonts();

	// Paint "ACME TEXT" using ACME font, always white
	const CString&	srcStr = m_pTitle ? *m_pTitle : m_Title;
	CString			appName;
	CString			docName = "";

	int	i = srcStr.Find('|');
	if(i == -1)
		appName = srcStr;
	else
	{
		appName = srcStr.Left(i) + " ";
		docName = srcStr.Mid(i + 1);
	}

	CRect rc(CPoint(0,0), pc->m_szCaption);					// text rectangle
	rc.left  += cxIcon+2;									// start after icon
	rc.right -= cxButns;									// don't draw past buttons
	dc.SetBkMode(TRANSPARENT);								// draw on top of our shading
	dc.SetTextColor(COLOR_WHITE);							// always white
	CFont* pOldFont = dc.SelectObject(&m_fontAcme);
	dc.DrawText(appName, &rc, DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);

	// Now paint window title (caption)
	rc.left += dc.GetTextExtent(appName).cx;				// move past "ACME EDIT "
	if (rc.right > rc.left) {								// if still room:
		COLORREF clrText;									// text color
		if (!bActive)
			clrText = GetSysColor(COLOR_INACTIVECAPTIONTEXT);
		else
		{
			// Excel always uses white for title color, but I use the user's
			// selected color--unless it's too dark, then I use white.
			//
			clrText = GetSysColor(COLOR_CAPTIONTEXT);
			if (PxLib::GetLuminosity(clrText) < 90) // good from trial & error
				clrText = COLOR_WHITE;
		}

		// Paint the text. Use DT_END_ELLIPSIS to draw ellipsis if text
		// won't fit. Win32 sure is friendly!
		//
		dc.SetTextColor(clrText);
		dc.SelectObject(&m_fontCaption);
		dc.DrawText(docName, &rc,
			DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	} 

	// Restore DC
	dc.SelectObject(pOldFont);
}

//////////////////
// Helper function to build the fonts I need.
//
void CCaptionPainterEx::CreateFonts()
{
	// Get current system caption font, just to get its size
	//
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	VERIFY(SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, &ncm, 0));
	ncm.lfCaptionFont.lfWeight = 400;
	m_fontCaption.CreateFontIndirect(&ncm.lfCaptionFont);

	// Create "ACME" font same size as caption font, but use Book Antiqua
	//
	m_fontAcme.CreatePointFont(120, "Book Antiqua");// 12 pt for now
	LOGFONT lf;
	m_fontAcme.GetLogFont(&lf);						// get font info
	m_fontAcme.DeleteObject();						// I don't really want 12 pt
	lf.lfWeight|=FW_BOLD;							// make bold
	lf.lfHeight = ncm.lfCaptionFont.lfHeight;		// same height as caption font
	m_fontAcme.CreateFontIndirect(&lf);				// create font
}
