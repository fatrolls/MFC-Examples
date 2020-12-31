#pragma once

#include "CellButton.h"
#include "..\utilities.h"

class CCellSpinCtrl : virtual public CCellCtrl
{
private:
	static DWORD	m_dwSpinCtrlStyle;
	UINT_PTR		m_TimerID;
	short			m_TimerStep;
	void UnPressButtons();
	void InstantiateTimer();
public:
	CCellSpinCtrl(void);
	virtual ~CCellSpinCtrl(void);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);
	const RECT &GetTextRect() const;
	void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	void AddToCtrlTypeStyle(DWORD dwFlags);
	void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	LONG GetStyle();
	virtual void OnHotMouseMove(UINT nFlags, CPoint point);
	virtual void OnKillHot();
	virtual BOOL OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual void OnIncrement() = 0;
	virtual void OnDecrement() = 0;
	virtual void DrawTextArea(CDC *pDC, const LPRECT prcCell, BOOL bHighlighted) = 0;
	RECT		m_rcUpClick,
				m_rcDownClick,
				m_rcTxtArea;
	BOOL		m_TopPressed,
				m_BottomPressed,
				m_TopPressedNotReleased,
				m_BottomPressedNotReleased,
				m_bIsTopHot,
				m_bIsBottomHot;
	inline int GetThemeUpDownButtonStateId(BOOL IsUpButton, int NormalStateId, int HotStateId, int PressedStateId, int DisabledStateId)
	{
		if (IsDisabled())
			return DisabledStateId;
		if ((IsUpButton && m_TopPressed) || (!IsUpButton && m_BottomPressed))
			return PressedStateId;
		if ((IsUpButton && m_bIsTopHot) || (!IsUpButton && m_bIsBottomHot))
			return HotStateId;

		return NormalStateId;
	}
};

