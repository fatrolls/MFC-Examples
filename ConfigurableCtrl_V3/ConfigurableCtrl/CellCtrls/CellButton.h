#pragma once

#include "CellCtrl.h"

#define DEFAULT_BUTTON_WIDTH (::GetSystemMetrics(SM_CXVSCROLL) + ::GetSystemMetrics(SM_CXEDGE))

class CCellButton : virtual public CCellCtrl  
{
public:
	CCellButton();
	virtual ~CCellButton();
	virtual BOOL OnPressButton(UINT nFlags, CPoint point) = 0; 
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){return TRUE;}
	virtual BOOL OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar){return TRUE;}
	virtual void OnEnter(){}
	virtual void OnEscape(){}
	virtual void OnHotMouseMove(UINT nFlags, CPoint point);
	virtual void OnKillHot();
protected:
	RECT				m_rcClickRect; // the rectangle sensitive to a click
	BOOL				m_bIsButtonHot;
	inline int GetThemeButtonStateId(BOOL PressedState, int NormalStateId, int HotStateId, int PressedStateId, int DisabledStateId)
	{
		if (IsDisabled())
			return DisabledStateId;
		if (PressedState)
			return PressedStateId;
		if (m_bIsButtonHot)
			return HotStateId;

		return NormalStateId;
	}
};

