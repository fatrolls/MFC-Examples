#pragma once

#include "CellCtrl.h"

class CCellEdit : virtual public CCellCtrl  
{
public:
	CCellEdit();
	virtual ~CCellEdit();
	virtual void Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText);
	virtual void DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState = 0);
	virtual int GetMinWidth();
	virtual const RECT &GetTextRect() const; 
public:
	virtual void OnKillActive();
	virtual void OnResizeColumn();
	virtual BOOL OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar); 
	virtual BOOL OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
	virtual BOOL OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	virtual void OnKillFocus(CWnd* pNewWnd);
	virtual void OnSetFocus(CWnd* pOldWnd); 

	virtual void OnCaretHandlingLButtonDown(UINT nFlags, CPoint point);

	void SelectAll();
	BOOL Copy();
	BOOL Cut();
	BOOL Paste();
	void Undo();
	virtual void AddToCtrlTypeStyle(DWORD dwFlags);
	virtual void RemoveFromCtrlTypeStyle(DWORD dwFlags);
	virtual LONG GetStyle();
protected:
	struct CCaretPosDets
	{
		CCaretPosDets() : m_point(0,0), m_CharPos(0), m_StartPos(0), m_StartSelPos(-1)
		{}
		CPoint	m_point;
		LONG	m_CharPos,
				m_StartPos,
				m_StartSelPos;
	};
	CCaretPosDets m_CaretPosDets;
	RECT		m_rcTxt;
	BOOL		m_ShowCaret,
				m_InvalidateCaret;
	CMenu		m_PopUpMenu;
	CString		m_strUndoText;

	inline void HideCaret()
	{
		if (m_ShowCaret)
		{
			GetWindowFromHandle()->HideCaret();
			m_ShowCaret = FALSE;
		}
	}
	inline void ShowCaret()
	{
		if (!m_ShowCaret)
		{
			GetWindowFromHandle()->ShowCaret();
			m_ShowCaret = TRUE;
		}
	}
	inline void InvalidateCaret()
	{
		m_InvalidateCaret = TRUE;
		HideCaret();
		GetWindowFromHandle()->InvalidateRect(&m_rcTxt, FALSE);
	}
	void InsertItemIntoPopUpMenu(UINT uiItemID);
private:
	BOOL IsPrintableChar(UINT nChar);
	void MoveCaretPos(TCHAR ch, BOOL bForward = TRUE);
	void ReCalculateCaret();
	BOOL IsCaretInCell(const CPoint &pt);
	void CalculateCaretFromPt(const CPoint &point);
	void RemoveSelString();
	void GetLeftRightSelPos(LONG &lLeftSelPos, LONG &lRightSelPos);
	void GetSelectedString(CString &str);
	void EnableMenuItems();
	static DWORD m_dwEditStyle; // style common to all edit controls	
	int GetRightIncr(CDC *pDC);
	void ReComputeInternalAlignment(CDC *pDC);
	BOOL ShiftTextLeftwards();
	void ScrollTextToEnd(CDC *pDC);

	Alignment m_InternalAlign;
};