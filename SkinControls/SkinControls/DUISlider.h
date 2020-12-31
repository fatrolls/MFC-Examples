
#ifndef DUI_SLIDER_H_
#define DUI_SLIDER_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIProgress.h"

// 滑动条
class SKIN_CONTROLS_EXPORT CDUISlider : public CDUIProgress
{
public:
	CDUISlider();
	virtual ~CDUISlider();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintStatusImage(CDC* pDC);

	// 操作相关
	virtual bool OnMouseMove(const CPoint& point);
	virtual bool OnMouseLeave();
	virtual bool OnLButtonDown(const CPoint& point);
	virtual bool OnLButtonUp(const CPoint& point);

	virtual void SetThumbImage(LPCTSTR lpszThumb, BitmapFormat bf = BF_UNKNOWN, COLORREF clrTrans = CLR_NONE);

	virtual CRect GetThumbRect();

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

protected:
	BYTE m_byButtonState; // 3个状态 0 normal 1 hover 2 down
	CSkinImage m_ImageThumb;
	COLORREF m_clrThumbTrans;
	CSize m_szThumb;
	bool m_bMouseHover;
	bool m_bLButtonDown;
};

#endif // DUI_SLIDER_H_
