
#ifndef DUI_CHECKBOX_H_
#define DUI_CHECKBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIButton.h"

// µ¥Ñ¡¿ò 8¸ö×´Ì¬Í¼
class SKIN_CONTROLS_EXPORT CDUICheckBox : public CDUIButton
{
public:
	CDUICheckBox();
	virtual ~CDUICheckBox();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintStatusImage(CDC* pDC);
	virtual void PaintText(CDC* pDC);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);

	virtual bool GetCheck() const { return m_bCheck; }
	virtual void SetCheck(bool bCheck = true, bool bRedraw = false);

	virtual void OnClick();

protected:
	bool m_bCheck;
};

#endif // DUI_CHECKBOX_H_
