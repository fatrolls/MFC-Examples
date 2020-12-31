#pragma once
#include "..\Base\ControlBase.h"

class CArea : public CControlBase
{
public:
	CArea(HWND hWnd, UINT uControlID, CRect rc, int nBeginTransparent = 50, int nEndTransparent = 50, 
		COLORREF clr = RGB(255, 255, 255), BOOL bIsVisible = TRUE);
	~CArea(void);

protected:
	void Draw(CDC &dc, CRect rcUpdate);
	int		m_nBeginTransparent;
	int		m_nEndTransparent;
	COLORREF m_clr;
};
