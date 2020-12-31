#pragma once

#include "CellButton.h"

// Window drop down types
enum WinDDT
{
	WDDT_ButtonClickOnly,			// Drop Down type - Usually this
	WDDT_ClickAnyWhere				// Drop List Type
};
	
class CCellDropDown : public CCellButton  
{
public:
	CCellDropDown();
	virtual ~CCellDropDown();
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual int GetMinWidth();
	const RECT &GetTextRect() const;
	virtual void OnInactiveResizeColumn(const CRect &Rect);
	virtual void OnResizeColumn();
	virtual BOOL OnPressButton(UINT nFlags, CPoint point);
	virtual void OnCellCtrlMsg(WPARAM wParam, LPARAM lParam);
	virtual void SetWindowRect(LPRECT lpRect);
	virtual void OnKillActive();
	virtual void OnKillFocus(CWnd* pNewWnd);
	virtual void OnParentMove(int x, int y); 
	virtual BOOL OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnEnter();
	virtual void OnEscape();
protected:
	CWnd		*m_pPopUpWnd;
	WinDDT		m_eDropDownType;
	BOOL		m_bPumpActionButtonEffect;

	RECT		m_rcButton, // The right hand side combo button bounding rectangle
				m_rcBounding,
				m_rcTextArea;

	LONG		m_lButtonOffset;

	inline const int GetMinLegalWidth() const
	{
		return m_lButtonOffset;
	}
	void ActivatePushButton(const CPoint &point);
	virtual void OnOpenDropDown() = 0;
	virtual void GetDropDownBoundingRect(RECT &rc, BOOL downwards = TRUE) = 0;
	virtual void OnSelCloseDropDown(LPARAM lParam) = 0;
	virtual void OnSelChangeDropDown(LPARAM lParam){};
	BOOL DrawThemeCombobox(HDC hDc, const LPRECT prcCell);
	void CloseDropDown();
	inline BOOL IsPopupOpen() const { return m_bPopUpOpen; }
	void CalculateTextAreaRect();
private:
	BOOL		m_bPopUpBlocked,
				m_bPopUpOpen;
	void Inactivate();
};

class CButtonCritSect : public CCriticalSection
{
public:
	CButtonCritSect() : m_bIsButtonPushed(FALSE){}
	~CButtonCritSect(){}
	inline void SetPushButtonStatus(BOOL bStatus)
	{
		Lock();
		m_bIsButtonPushed = bStatus;
		Unlock();
	}
	inline BOOL IsButtonPushed()
	{
		BOOL bPushed;
		Lock();
		bPushed = m_bIsButtonPushed;
		Unlock();
		return bPushed;
	}
private:
	BOOL m_bIsButtonPushed;
};

static CButtonCritSect g_CritSect;
