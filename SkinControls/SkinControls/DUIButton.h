
#ifndef DUI_BUTTON_H_
#define DUI_BUTTON_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"
#include "SkinImage.h"

// 按钮 
class SKIN_CONTROLS_EXPORT CDUIButton : public CDUIControl
{
public:
	CDUIButton();
	virtual ~CDUIButton();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintStatusImage(CDC* pDC);
	virtual void PaintText(CDC* pDC);

	// 操作相关
	virtual bool OnMouseMove(const CPoint& point);
	virtual bool OnMouseLeave();
	virtual bool OnLButtonDown(const CPoint& point);
	virtual bool OnLButtonUp(const CPoint& point);

	virtual void SetEnabled(bool bEnable  = true, bool bReDraw = false);

	virtual void SetImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN, COLORREF clrTrans = CLR_NONE);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

	virtual void OnClick();

protected:
	CSkinImage m_ImageStatus; // 按钮的图必须是有四个状态图的 依次的状态 见下m_byStatus
	BYTE m_byStatus; // 0 normal 1 hover 2 down 3 disable
	bool m_bMouseHover;	// 在鼠标移动的时候 如果是在当前控件下移动 只刷新一次
	COLORREF m_clrTrans; // 透明色
};

#endif // DUI_BUTTON_H_
