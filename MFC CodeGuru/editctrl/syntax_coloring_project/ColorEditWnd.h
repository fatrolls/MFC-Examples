

/////////////////////////////////////////////////////////////////////////////
//Header for the ColorEditWnd class
/////////////////////////////////////////////////////////////////////////////


#ifndef _COLORIZED_VIEW_
#define _COLORIZED_VIEW_

#include "Colorize.h"

class CScriptText : public CStringArray
{
public:
	CScriptText & operator = (CScriptText & source);
public:
	//offsets for scrolling
	long			cFirstCharacter;
	long			cFirstLine;
	long			cViewX;
	long			cViewY;
	//caret and cursor control
	long			cAnchorX;
	long			cAnchorY;
	long			cCursorX;
	long			cCursorY;
};

class ColorEditWnd : public CWnd
{
private:
	long CharDX;
	long CharDY;
	long TAB_SIZE;
	HCURSOR cCursor;
	BOOL cCaretOn;


public:
	CScriptText		cTheText;
	BOOL cCaseSensitive;

private:
	BOOL cWasHilighted;
	BOOL cLeftDown;
	BOOL cIgnoreCtl;
	CFont cfont;
	void InsertChar(int pChar, BOOL pRedraw);
	void InsertString(CString &pString, BOOL pRedraw);
	void InsertChar(int pChar);
	void InsertString(CString &pString);
	void DeleteChar();
	void DrawCursor(CDC * pDC, BOOL pShow);
	void DrawCursor(BOOL pShow);
	Colorize * cColorize;
	void DrawLine();
	void DrawLine(long pLine);
	BOOL IsHilighted(long pX,long pY);
	BOOL Hilight();
	void UpdateAnchor(BOOL pTestShift);
	void RemoveHilighted();

public:
	void Reset();
	void LoadText(CString &pText);
	void UnloadText(CString &pText);
	void Retab();
	void DoCopy();
	void DoPaste();

public:
	ColorEditWnd(CWnd * parent, CRect & rect,
		int nID,CString &keywordsFile, BOOL caseSensitive);
	ColorEditWnd(CWnd * parent, CRect & rect,
		int nID, CString &keywordsFile, BOOL caseSensitive, 
		long pCharDX, long pCharDY, long pTabSize,
		int pFontSize, CString pFontName);


public:
	virtual ~ColorEditWnd();

protected:

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg void OnHScroll( UINT nSBCode, UINT nPos, CScrollBar* pScrollBar );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
#endif
