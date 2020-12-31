#pragma once
#include "..\Base\ControlBase.h"

class CLinkButton : public CControlBase
{
public:
	CLinkButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle, CString strLink,
		COLORREF clrTextNormal = RGB(39, 134, 230) ,COLORREF clrTextHover = RGB(21, 112, 235),
		COLORREF clrTextDown = RGB(21, 112, 235) ,COLORREF clrTextDisable =  RGB(128, 128, 128),
		BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE);
	~CLinkButton(void);
	void SetTitleText(CString strTitle);

protected:
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);

	void Draw(CDC &dc, CRect rcUpdate);

public:
	COLORREF m_clrTextNormal;
	COLORREF m_clrTextHover;
	COLORREF m_clrTextDown;
	COLORREF m_clrTextDisable;
	CString m_strLink;
	CRect m_rcText;
	enumButtonState m_buttonState;
	bool m_bDown;
};