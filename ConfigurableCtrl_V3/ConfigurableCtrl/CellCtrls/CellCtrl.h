#pragma once

#include "..\ConfigListCtrl.h"

class CCellCtrl  
{
public:
	CCellCtrl();
	virtual ~CCellCtrl();
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText = _T(""))
	{
		m_hParentWnd = hParentWnd;
		m_pParentEnabled = pParentEnabled;
		m_strText = strText;

		LOGFONT LogFont;
		::ZeroMemory(&LogFont, sizeof(LogFont));
		LogFont.lfHeight = -11;
		LogFont.lfWeight = FW_NORMAL;
		wcscpy_s(LogFont.lfFaceName, _T("MS Sans Serif"));
		m_Font.CreateFontIndirect(&LogFont);
		LogFont.lfWeight = FW_BOLD;
		m_BoldFont.CreateFontIndirect(&LogFont);
	}
	inline void SetDefaultTextValue(const CString &strDefault)
	{
		m_strText = strDefault;
	}
	inline CString GetSelectedTextValue()
	{
		return m_strText;
	}
	inline void OnSetHot(){ m_bHot = TRUE; }
	virtual void OnKillHot(){ m_bHot = FALSE; }

	virtual const RECT &GetTextRect() const = 0; // This function returns the text area rect, to prevent flicking
	virtual const RECT &GetModDrawAreaRect() const{ return GetTextRect(); } // This returns the area that changes on user editing. 
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0) = 0;
	virtual int GetMinWidth() = 0; // Returns the min width for a complete display of control 
	virtual void OnKillActive(){ m_bActive = FALSE;}
	virtual void OnSetActive(){ m_bActive = TRUE;}
	virtual void OnResizeColumn(){}
	virtual void OnInactiveResizeColumn(const CRect &Rect){}
	virtual void SetWindowRect(LPRECT lpRect){}
	inline bool IsDisabled() const
	{ 
		return !*m_pParentEnabled || m_dwStyle & CLCS_DISABLED; 
	}
public:
// Message Handler called from parent control
// If returns FALSE, base class version of parent function never called 
	virtual BOOL OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){return TRUE;}
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){return TRUE;}
	virtual BOOL OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){return TRUE;}
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point)
	{
		OnSetActive();
		return TRUE;
	} 
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point){ return TRUE; }
	virtual BOOL OnTimer(UINT_PTR nIDEvent){ return TRUE; }
	virtual BOOL OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){return TRUE;} 
	virtual BOOL OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){return TRUE;}
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt){return TRUE;} 
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point){return TRUE;} 
	virtual BOOL OnRButtonDown(UINT nFlags, CPoint point){return TRUE;}

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam){return TRUE;} // Note: return value meaning: indication whether parent superclass version of function should be called (and not indication of whether message was processed)
	// if returns false, presumably message was processed and parent function OnCommmand returns TRUE always. Don't return FALSE, without processing messages.     

	virtual void OnKillFocus(CWnd* pNewWnd){}
	virtual void OnSetFocus(CWnd* pOldWnd){} 
	virtual void OnParentMove(int x, int y){} 
	virtual void OnHotMouseMove(UINT nFlags, CPoint point){} 

// Special Message Handlers called from parent control.
// For instance function below manages caret and is called in a different order,
// depending on whether control is just receiving focus from another control or
// cell is receiving focus from elsewhere in the control.
	virtual void OnCaretHandlingLButtonDown(UINT nFlags, CPoint point){}

	virtual void OnCellCtrlMsg(WPARAM wParam, LPARAM lParam){}

	void AddToStyle(DWORD dwFlags);
	void RemoveFromStyle(DWORD dwFlags);
// The 2 pure virtuals below are so that it is possible to configure the style that
// applies to a particular control type, but not to all controls
	virtual void AddToCtrlTypeStyle(DWORD dwFlags) = 0;
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags) = 0;
	virtual LONG GetStyle() = 0; // returns the style
	virtual void OnThemeChanged(){}
protected:
// It would be nice if we could just have a pointer to first character in cell, rather than a duplicate of string
	CString			m_strText;
	HWND			m_hParentWnd; 
	BOOL			m_bActive,
					m_bHot;
// get rid of...
	CWnd *GetWindowFromHandle()
	{
// I'm sure there is a better method than this.
		CWnd *pWnd;
		pWnd = pWnd->FromHandle(m_hParentWnd);
		return pWnd;
	}
	inline void SelectFont(CDC *pDC)
	{
		CFont *pFont;
		pFont = pFont->FromHandle((HFONT)((m_bActive && (GetStyle() & CLCS_BOLD_ON_ACTIVE))? m_BoldFont : m_Font));
		pDC->SelectObject(pFont);
	}
	void DrawFrameCtrl(CDC *pDC, const LPRECT prcCell);
	int GetAlignDrawFlag() const;
	DWORD			m_dwStyle;
	CFont			m_Font,
					m_BoldFont;
	inline int GetThemeStateId(int NormalStateId, int HotStateId, int FocusedStateId, int DisabledStateId)
	{
		if (IsDisabled())
			return DisabledStateId;
		if (m_bActive)
			return FocusedStateId;
		if (m_bHot)
			return HotStateId;

		return NormalStateId;
	}
private:
	BOOL			*m_pParentEnabled;
};