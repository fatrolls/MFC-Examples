
#ifndef DUI_IMAGECONTROL_H_
#define DUI_IMAGECONTROL_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"
#include "SkinImage.h"

class SKIN_CONTROLS_EXPORT CDUIImageControl : public CDUIControl
{
public:
	CDUIImageControl(void);
	virtual ~CDUIImageControl(void);

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintBkImage(CDC* pDC);
	virtual void PaintText(CDC* pDC);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

protected:
	CSkinImage m_Image;
	COLORREF m_clrTransColor;
};

#endif // DUI_IMAGECONTROL_H_
