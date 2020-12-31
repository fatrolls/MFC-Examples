
#ifndef DUI_PROGRESS_H_
#define DUI_PROGRESS_H_
#pragma once

#include "SkinControlsDefine.h"
#include "DUIControl.h"
#include "SkinImage.h"

// ½ø¶ÈÌõ
class SKIN_CONTROLS_EXPORT CDUIProgress : public CDUIControl
{
public:
	CDUIProgress();
	virtual ~CDUIProgress();

public:
	virtual LPCTSTR GetClass() const;
	virtual void PaintStatusImage(CDC* pDC);

	virtual void SetRange(int nLower, int nUpper);
	virtual void GetRange(int& nLower, int& nUpper) const;

	virtual int GetValue() const;
	virtual void SetValue(int nPos, bool bRedraw = false);

	virtual void SetBgImage(LPCTSTR lpszBg, BitmapFormat bf = BF_UNKNOWN, COLORREF clrTrans = CLR_NONE);
	virtual void SetProgressImage(LPCTSTR lpszProgress, BitmapFormat bf = BF_UNKNOWN, COLORREF clrTrans = CLR_NONE);

	virtual bool IsHorizontal() const;
	virtual void SetHorizontal(bool bHorizontal = true);

	virtual void SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue);
	virtual void UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue);

protected:
	CSkinImage m_ImageBg;
	CSkinImage m_ImageProgress;
	COLORREF m_clrBgTrans;
	COLORREF m_clrProgressTrans;
	bool m_bHorizontal;
	int m_nMax;
	int m_nMin;
	int m_nPos;
};

#endif // DUI_PROGRESS_H_
