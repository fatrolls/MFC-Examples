
#ifndef DUI_LABEL_H_
#define DUI_LABEL_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"

class SKIN_CONTROLS_EXPORT CDUILabel : public CDUIControl
{
public:
	CDUILabel();
	virtual ~CDUILabel();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintText(CDC* pDC);

	virtual void SetHyperLink(bool bHyperLink, COLORREF clrTextNormal, COLORREF clrTextHover, bool bUnderline = true);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

	// 操作相关
	virtual bool OnMouseMove(const CPoint& point);
	virtual bool OnMouseLeave();
	virtual bool OnLButtonDown(const CPoint& point);
	virtual bool OnLButtonUp(const CPoint& point);
	virtual bool OnMouseCursor(const CPoint& point);

	virtual void OnClick();

protected:
	bool m_bHyperLink; // 超链接
	BYTE m_byStatus; // 0 normal 1 hover
	bool m_bMouseHover;	// 在鼠标移动的时候 如果是在当前控件下移动 只刷新一次
	COLORREF m_clrHover;
	bool m_bUnderline;
};

#endif // DUI_LABEL_H_
