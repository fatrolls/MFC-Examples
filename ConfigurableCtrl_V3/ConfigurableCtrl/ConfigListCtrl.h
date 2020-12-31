#pragma once

#include "ConfigHeaderCtrl.h"
#include "utilities.h"

// Just one value for handling user defined messages from pop up.
// (In fact, it would be nice if we could avoid avoid this altogether and use
// WM_COMMAND message for instance. However, this might cause conflicts between 
// values at some stage.)  
#define WM_CELL_CTRL_MSG			  WM_USER + 0x1000 
// WPARAM values: (for handling a particular message):
// (Put all new values below for clarity) 
#define ID_POPUP_SELCLOSE             0xA000
#define ID_POPUP_SELCHANGE			  0xB000
#define ID_POPUP_CLOSE				  0xC000
// Use LPARAM for passing values

// Used with GetKeyState to indicate control or shift key pressed:
#define KEY_PRESSED					0x8000

class CCellCtrl;

#define BOOKMARK_COUNT						100
#define COLUMN_COUNT						20

typedef CMap<DWORD, DWORD, CCellCtrl *, CCellCtrl *> CCellMap;

// All styles common to all controls (or vast majority - there will always be the odd one out)
// Remove these?
#define CLCS_BOLD_ON_ACTIVE				0x00000001  // Control's font becomes active on selection
#define CLCS_ACTIVE_FRM_PLAIN			0x00000002
#define CLCS_ACTIVE_FRM_NORMAL			0x00000004
#define CLCS_DISABLED					0x00000008
#define CLCS_ALIGN_RIGHT				0x00000010
#define CLCS_ALIGN_CENTER				0x00000020
// leave space for another 3 Active FRM styles 0x00000008, 0x00000010, 0x00000020
#define CLCS_INACTIVE_FRM_PLAIN			0x00000040
#define CLCS_INACTIVE_FRM_NORMAL		0x00000080
// leave space for another 3 Inactive FRM styles 0x00000100, 0x00000200, 0x00000400
#define CLCS_POPUP_OUTOF_FRM			0x00010000 // Choose this style if want pop up of a CCellDropDown to not be contrained by bounaries of config list ctrl 

#include "CellCtrls\CellCtrl.h"

// Note: CConfigListCtrl is designed in such a way that there are no details of any 
// controls within the class. All implementation is done outside.
// This has the advantage that new controls can be easily implemented without ever touching
// CConfigListCtrl.
// Every effort must be made to keep this separate implentation between CConfigListCtrl and
// the CCellCtrls that are inserted.

enum Alignment
{
	Left,
	Right,
	Center
};

class CConfigListCtrl;
typedef void (CConfigListCtrl::*OpOnCellCtrl)(DWORD dwLocation, CCellCtrl *pCellCtrl);

class CConfigListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CConfigListCtrl)
public:
	CConfigHeaderCtrl		m_HeaderCtrl; // For handling header messages
public:
	CConfigListCtrl();
	virtual ~CConfigListCtrl();
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
// Have to change default height: a cell with a combo will be higher than an ordinary text cell. 
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	void DrawItemText(CDC *pDC, int nItem, int nSubItem, const LPRECT	prcBounding, UINT uiItemState);

	inline int InsertItem(const LVITEM* pItem);
	inline int InsertItem(int nItem, LPCTSTR lpszItem);
	inline int InsertItem(int nItem, LPCTSTR lpszItem, int nImage);
	int InsertItem(int nItem, CCellCtrl *pCellCtrl, LPCTSTR lpszDefaultTextValue = _T("\0"));

	inline BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem, int nImage, UINT nState, UINT nStateMask, LPARAM lParam);
	inline BOOL SetItem(const LVITEM *pItem);
	BOOL SetItem(int nItem, int nSubItem, LPCTSTR lpszItem);
	BOOL SetItem(int nItem, int nSubItem, CCellCtrl *pCellCtrl, LPCTSTR lpszDefaultTextValue = _T("\0"));

	inline BOOL DeleteItem(int nItem);
	inline BOOL DeleteAllItems();

	inline int InsertColumn(int nCol, const LVCOLUMN* pColumn);
	inline int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	inline BOOL DeleteColumn(int nCol);

	void InsertCtrl(int nItem, int nSubItem, CCellCtrl *pCellCtrl);
	inline void DeleteCtrl(int nItem, int nSubItem);

	BOOL IsOnCellCtrl(int iItem, int iSubItem, CCellCtrl **ppCellCtrl) const;
	CCellCtrl *GetItemCellCtrl(int iItem, int iSubItem) const;

	void OnResizeColumn();
	void OnHeaderLButtonDown(UINT nFlags, CPoint point); 

	void SetColumnMinWidth(int nCol);

	inline CCellCtrl *GetActiveCellCtrl() const
	{
		return m_ActiveCell.m_pCellCtrl;
	}
	void OnParentMove(int x, int y);
	BOOL OnEnterEsc(WPARAM param);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void EnableCtrl(int iItem, int iSubItem, BOOL Enable = TRUE);
	BOOL IsCtrlEnabled(int iItem, int iSubItem);
	BOOL SetItemValueFromCtrl(const CCellCtrl *pCellCtrl, const CString &strValue);
	void OnSizing(UINT fwSide, LPRECT pRect);
	BOOL SetCtrlAlignment(int iItem, int iSubItem, Alignment align);
	BOOL GetCtrlAlignment(int iItem, int iSubItem, Alignment &align);
protected:
	virtual void PreSubclassWindow();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
protected:
	DECLARE_MESSAGE_MAP()

	protected:
private:
	struct CCellDetails
	{
		CCellDetails() : m_lItem(-1), m_lSubItem(-1), m_pCellCtrl(NULL){}
		LONG		m_lItem,
					m_lSubItem;
		CCellCtrl	*m_pCellCtrl;
		void Assign(CCellCtrl *pCellCtrl, LONG lItem, LONG lSubItem)
		{
			m_pCellCtrl = pCellCtrl; 
			m_lItem = lItem; 
			m_lSubItem = lSubItem;
		}
	};
	void InsertBookmark(WORD nItem);
	void InsertColumn(WORD nItem);
	void RemoveCtrl(int nItem, int nSubItem);
	void RemoveCtrlRow(int nItem);
	void RemoveCtrlColumn(int nSubItem);
	void RemoveAllCtrls();
	void ShiftItemsRight(int nCol);
	void InvalidateActiveCellRect();
	inline DWORD GetMapKey(int nItem, int nSubItem) const;
	void CreateCaret();
	void DeleteCaret();
	void DeleteCellCtrl(DWORD dwLocation, CCellCtrl *pCellCtrl);
	void OnInactiveResizeColumn(DWORD dwLocation, CCellCtrl *pCellCtrl);
	void ForEachCellCtrl(OpOnCellCtrl OpOnCtrl);		
	void DeActivateCell();
	void OnDrawInitialize(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void OnEscape(DWORD dwLocation, CCellCtrl *pCellCtrl);
	void OnEnter(DWORD dwLocation, CCellCtrl *pCellCtrl);
	void OnThemeChanged(DWORD dwLocation, CCellCtrl *pCellCtrl);
	void ActivateCellCtrl(DWORD dw);
	void InvalidateHotRect();
	void IncrCtrlMapRow(WORD wRow, BOOL incr = TRUE);
	void IncrCtrlMapColumn(WORD wCol, BOOL incr = TRUE);
	DWORD GetNextEnabled(DWORD dw);
	DWORD GetPrevEnabled(DWORD dw);
	void CopyMaps(const CCellMap &SourceMap, CCellMap &DestMap, DWORD dwCompVal = 0, BOOL Incr = TRUE, DWORD (*pFunc)(DWORD, DWORD, BOOL) = NULL);

	CCellMap										m_CtrlMap;
	CDWordSet										m_CtrlSet; // Needed because CCellMap is not ordered. 
	BOOL											m_bInit,
													m_bCaretExists,
													m_bTabbedIn,
													m_bKeyUp,
													m_bIsEnabled;
	CCellDetails									m_ActiveCell,
													m_HotCell;
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg LRESULT OnCellCtrlMsg(WPARAM wParam, LPARAM lParam);
	
	LRESULT OnThemeChanged();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#include "ConfigListCtrl.inl"

