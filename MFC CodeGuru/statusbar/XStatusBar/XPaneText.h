/*****************************************************************************
 *
 * Autor:			Joachim Raidl
 * Klasse:			XPaneText
 * JRRC:			%J%
 * Beschreibung:	Dieses Klasse ist vollständig inline. Mit ihr kann ein
 *					Pane der Statuszeile temporär auf Text umgeschaltet
 *					werden. Der Text bleibt solange im Pane sichtbar, bis
 *					das erzeugte XPaneText-Objekt wieder zerstört wird. Dies
 *					erfolgt normalerweise automatisch am Ende eines Blocks.
 *					Hierbei ist es egal, ob das gewünschte Pane im Text-
 *					Bitmap-, Nummer- oder Progress-Bar-Modus erzeugt wurde.
 *					Auch ist es egal, ob der Pane gerade aktiv oder disabled
 *					ist, die Darstellung entspricht immer dem aktiven Zustand.
 * Inlines:			XPaneText(), ~XPaneText(), 
 * Beispiel:		XPaneText t("Jetzt wird gerade berechnet ...");
 *
 ****************************************************************************/

#ifndef __XPANETEXT__
#define __XPANETEXT__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "XStatusBar.h"

class XPaneText
{
protected:
	int	index;

public:
	XPaneText(LPCSTR text, int ix = 0)
	{
		ASSERT(XStatusBar::aktBar);

		index = ix;
		XStatusBar::aktBar->SavePane(ix);
		XStatusBar::aktBar->SetMode(ix, XSB_TEXT | XStatusBar::aktBar->GetMode(ix) & XSB_ALIGN);

		COLORREF fg = XStatusBar::aktBar->GetFgColor(ix);
		COLORREF bk = XStatusBar::aktBar->GetBkColor(ix);
		XStatusBar::aktBar->SetFgColor(ix, fg, fg);		// Gleiche Fg- und Bk-Farbe für
		XStatusBar::aktBar->SetBkColor(ix, bk, bk);		// On- und Off-Modus

		XStatusBar::aktBar->SetText(ix, text, text);	// Gleicher Text in beiden Modi
	}

	~XPaneText()
	{
		ASSERT(XStatusBar::aktBar);

		XStatusBar::aktBar->RestorePane(index);
	}
};

#endif // __XPANETEXT__
