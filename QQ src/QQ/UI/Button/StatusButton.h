#pragma once
#include "..\Base\ControlBase.h"


class CStatusButton : public CControlBase
{
public:
	CStatusButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = "", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	bool SetBitmap(UINT nResourceID);
	bool SetBitmap(CString strImage);
	bool SetStatusBitmap(UINT nResourceID);
	bool SetStatusBitmap(CString strImage);
	~CStatusButton(void);

protected:
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);
	void Draw(CDC &dc, CRect rcUpdate);
	
public:
	CString m_strFileImage;
	Image *m_pImage;
	CSize m_sizeImage;
	Image *m_pStatusImage;
	CSize m_sizeStatusImage;
	enumButtonState m_buttonState;
};