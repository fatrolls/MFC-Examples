#pragma once
#include "..\Base\ControlBase.h"

class CButtonEx : public CControlBase
{
public:
	CButtonEx(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = "", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	bool SetBitmap(UINT nResourceID);
	bool SetBitmap(CString strImage);
	bool SetSmallBitmap(UINT nResourceID);
	bool SetSmallBitmap(CString strImage);
	~CButtonEx(void);
protected:

	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);

	void Draw(CDC &dc, CRect rcUpdate);
public:
	CString m_strFileImage;
	Image *m_pImage;
	Image *m_pSmallImage;
	CSize m_sizeImage;
	CSize m_sizeSmallImage;
	enumButtonState m_buttonState;
};