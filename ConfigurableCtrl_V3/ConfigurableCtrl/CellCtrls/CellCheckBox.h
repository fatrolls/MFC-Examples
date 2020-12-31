#pragma once

#include "CellButton.h"

class CCellCheckBox : public CCellButton  
{
public:
	CCellCheckBox();
	virtual ~CCellCheckBox();
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual int GetMinWidth(); 
	virtual const RECT &GetTextRect() const;
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText);
	virtual BOOL OnPressButton(UINT nFlags, CPoint point);
	virtual void OnEnter();
	virtual void AddToCtrlTypeStyle(DWORD dwFlags);
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	virtual LONG GetStyle();
	virtual const RECT &GetModDrawAreaRect() const{ return m_rcArea; }
	CString GetDisplayedText();
	BOOL IsChecked();
	void SetIsChecked(BOOL bChecked);
private:
	RECT						m_rcArea;
	static CImageList			m_CheckBoxImageList;
	static void InitImageList();
	static DWORD				m_dwCheckBoxStyle;
};