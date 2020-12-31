//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPGLOB.CPP
//
// Implementation of global objects.

#include "wpp.h"

static char ArrowKeys[] = { VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 0 };

BOOL WPKeyboard::isArrowKey(int key)		
{
	return strchr(ArrowKeys, key) != NULL; 
}

void WPCursor::clip(WPWin *win)
{
	assert(win);
	WPRect rect = win;
	win->clientToScreen(&rect);
	clip(rect);
}

void WPCaret::create(WPWin *win, WPBitmap& bm)
{ 
	CreateCaret((*win)(), bm(), 0, 0); 
}

int WPWinIni::getPrinterName(char* buf, int len)
{ 
	int ret = get("windows", "device", buf, len); 
	strtok(buf,",");
	return ret;
}

int WPClipboard::getData(WORD fmt, LPSTR buf, int buflen)
{
	int len = 0;
	HGLOBAL hClipMem = (HGLOBAL)GetClipboardData(fmt);
	if (hClipMem) {
		LPSTR lpClipMem = (LPSTR)GlobalLock(hClipMem);
		if (lpClipMem) {
			len = GlobalSize(hClipMem);
			if (len<buflen)
				len = buflen;
			for (int i=len; i>0; i--)
				*buf++ = *lpClipMem++;
			GlobalUnlock(hClipMem);
		}
	}
	return len;
}

int WPClipboard::setData(WORD fmt, LPSTR buf, int buflen)
{
	int len = 0;
	HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, buflen);
	if (h) {
		LPSTR mem = (LPSTR)GlobalLock(h);
		if (mem) {
			for (int i=buflen; i>0; i--)
				*mem++ = *buf++;
			SetClipboardData(fmt, h);
		}
	}
	return len;
}
