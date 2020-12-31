#pragma once

#include "CellDropDown.h"

class CPopUpScrollList;

class CCellComboBox : public CCellDropDown  
{
	friend CPopUpScrollList;
public:
	CCellComboBox();
	virtual ~CCellComboBox();
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText);
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual void DrawItem(CDC *pDC, const LPRECT prcItem, const CString &strLabel, BOOL bSelected = FALSE, BOOL bDisabled = FALSE);
	virtual int GetMinWidth();

	inline LONG GetDisplayedRows() const 
	{
		return m_lDisplayedRows;
	}
	inline void SetDisplayedRows(LONG lDisplayedRows)
	{
		m_lDisplayedRows = lDisplayedRows;
	}
	inline LONG GetSelectedItem() const
	{
		return m_lSelectedItem;
	}
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point); 
	virtual void AddToCtrlTypeStyle(DWORD dwFlags);
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	virtual LONG GetStyle();
	BOOL InsertItem(int Idx, LPCTSTR strText);
	BOOL SetSelectedItem(LONG lSelectedItem);
	BOOL RemoveItem(int Idx);
protected:
	BOOL			m_bHighlighted;
	LONG			m_lDisplayedRows,
					m_lSelectedItem;
	CStringArray	m_astrItems;

	virtual void OnOpenDropDown();
	virtual void GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/);
	virtual void OnSelCloseDropDown(LPARAM lParam);
private:
	static DWORD	m_dwComboStyle; 
};