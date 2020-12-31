#pragma once
#include "..\Base\ControlBase.h"

#define					BUTTOM				1
#define					EDIT				2

class CEditEx : public CControlBase
{
public:
	CEditEx(HWND hWnd, UINT uControlID, CRect rc, CString strTitle = "", BOOL bPassWord = FALSE, BOOL bIsVisible = TRUE, BOOL bIsDisable = FALSE, BOOL bIsPressDown = FALSE);
	bool SetBitmap(UINT nResourceID);
	bool SetBitmap(CString strImage);
	bool SetSmallBitmap(UINT nResourceID);
	bool SetSmallBitmap(CString strImage);
	~CEditEx(void);

	virtual void SetRect(CRect rc);
	virtual BOOL OnFocus(bool bFocus);
	virtual BOOL IsDraw(CPoint point) ;
	BOOL GetLButtonDown();
	BOOL GetLButtonUp();
protected:
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnLButtonUp(UINT nFlags, CPoint point);
	void Draw(CDC &dc, CRect rcUpdate);

	void ShowEdit();
	void HideEdit();
	
public:
	CString m_strFileImage;
	Image *m_pImage;
	Image *m_pSmallImage;
	CSize m_sizeImage;
	CSize m_sizeSmallImage;
	bool m_bPassWord;
	bool m_bDown;
	bool m_bDownTemp;
	enumButtonState m_buttonState;
	enumButtonState m_EditState;
	CRect m_rcText;
	CFont	m_fontTemp;

	CEdit	*m_pEdit;
};