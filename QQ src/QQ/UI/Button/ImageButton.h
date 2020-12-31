#pragma once
#include "..\Base\ControlBase.h"


class CImageButton : public CControlBase
{
public:
	CImageButton(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = "", BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	bool SetBitmap(UINT nResourceID);
	bool SetBitmap(CString strImage);
	~CImageButton(void);
protected:
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);

	void Draw(CDC &dc, CRect rcUpdate);
	
public:
	CString m_strFileImage;
	Image *m_pImage;
	CSize m_sizeImage;
	enumButtonState m_buttonState;
};