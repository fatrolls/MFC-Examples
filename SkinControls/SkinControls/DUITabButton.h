
#ifndef DUI_TABBUTTON_H_
#define DUI_TABBUTTON_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIRadioBox.h"

// TAB°´Å¥
class SKIN_CONTROLS_EXPORT CDUITabButton : public CDUIRadioBox
{
public:
	CDUITabButton();
	virtual ~CDUITabButton();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintStatusImage(CDC* pDC);
	virtual void PaintText(CDC* pDC);
	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

	virtual void SetCheckTextColor(COLORREF clrCheckText, bool bRedraw = false);
	virtual void SetImage2(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);

protected:
	COLORREF m_clrCheckTextColor;
	CSkinImage m_ImageStatus2;
};

#endif // DUI_TABBUTTON_H_
