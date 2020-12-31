#pragma once

#include "CellDropDown.h"
#include "..\utilities.h"

class CCellColorCtrl : public CCellDropDown  
{
public:
	CCellColorCtrl();
	virtual ~CCellColorCtrl();
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual int GetMinWidth();
	virtual void AddToCtrlTypeStyle(DWORD dwFlags);
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	virtual LONG GetStyle();
	virtual void OnOpenDropDown();
	virtual void GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/);
	virtual void OnSelCloseDropDown(LPARAM lParam);
	inline COLORREF GetSelectedColor()
	{
		COLORREF SelColor = atox(m_strText.GetBuffer(0));
		m_strText.ReleaseBuffer();
		return SelColor;
	}
protected:
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText);
private:
	static DWORD	m_dwDateCtrlStyle;
};
