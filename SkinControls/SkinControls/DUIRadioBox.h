
#ifndef DUI_RADIOBOX_H_
#define DUI_RADIOBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUICheckBox.h"

// µ¥Ñ¡°´Å¥
class SKIN_CONTROLS_EXPORT CDUIRadioBox : public CDUICheckBox
{
public:
	CDUIRadioBox();
	virtual ~CDUIRadioBox();

public:
	virtual LPCTSTR GetClass() const;

	virtual void SetCheck(bool bCheck = true, bool bRedraw = false);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);

	virtual void OnClick();

	virtual void SetGroup(WORD wGroup);
	virtual WORD GetGroup() const { return m_wGroup; }

protected:
	WORD m_wGroup;
};

#endif // DUI_RADIOBOX_H_
