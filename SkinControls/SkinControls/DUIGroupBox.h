
#ifndef DUI_GROUPBOX_H_
#define DUI_GROUPBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"

class SKIN_CONTROLS_EXPORT CDUIGroupBox : public CDUIControl
{
public:
	CDUIGroupBox(void);
	virtual ~CDUIGroupBox(void);

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintText(CDC* pDC);

	virtual void SetBorderColor(COLORREF clrBorder);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

	// 操作相关
	virtual bool OnMouseMove(const CPoint& point);
	virtual bool OnMouseLeave();
	virtual bool OnLButtonDown(const CPoint& point);
	virtual bool OnLButtonUp(const CPoint& point);
	virtual bool OnRButtonDown(const CPoint& point);
	virtual bool OnRButtonUp(const CPoint& point);
	virtual bool OnMouseCursor(const CPoint& point);

protected:
	COLORREF m_clrBorder; // 边框颜色
};

#endif // DUI_GROUPBOX_H_
