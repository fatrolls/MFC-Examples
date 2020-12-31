// ConfigListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigListCtrl.h"
#include "CellCtrls\ListCtrlCellWnd.h"
#include "CellCtrls\CellButton.h"

// CConfigListCtrl

IMPLEMENT_DYNAMIC(CConfigListCtrl, CListCtrl)

CConfigListCtrl::CConfigListCtrl() : m_bInit(FALSE), m_bCaretExists(FALSE), m_bTabbedIn(FALSE), m_bKeyUp(FALSE), m_bIsEnabled(TRUE)
{
}

CConfigListCtrl::~CConfigListCtrl()
{
	ForEachCellCtrl(&CConfigListCtrl::DeleteCellCtrl);
}

BEGIN_MESSAGE_MAP(CConfigListCtrl, CListCtrl)
	ON_WM_CHAR()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_SETFOCUS()
	ON_WM_VSCROLL()
	ON_MESSAGE(WM_CELL_CTRL_MSG, OnCellCtrlMsg)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_THEMECHANGED()
	ON_WM_ENABLE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CConfigListCtrl message handlers
void CConfigListCtrl::DeleteCellCtrl(DWORD dwLocation, CCellCtrl *pCellCtrl)
{
	delete pCellCtrl;
}

void CConfigListCtrl::OnInactiveResizeColumn(DWORD dwLocation, CCellCtrl *pCellCtrl)
{
	WORD	a,b;
	CRect	rcCtrl;

	a = HIWORD(dwLocation);
	b = LOWORD(dwLocation);
	GetSubItemRect(a, b, LVIR_LABEL, rcCtrl);

	pCellCtrl->OnInactiveResizeColumn(rcCtrl);
}

void CConfigListCtrl::ForEachCellCtrl(OpOnCellCtrl OpOnCtrl)
{
	DWORD				dwLocation;
	CCellCtrl			*pCellCtrl;

	POSITION Pos = m_CtrlMap.GetStartPosition();

	while (Pos)
	{
		m_CtrlMap.GetNextAssoc(Pos, dwLocation, pCellCtrl);
		(this->*OpOnCtrl)(dwLocation, pCellCtrl);		
	}
}

void CConfigListCtrl::DeActivateCell()
{
	m_ActiveCell.m_lItem = m_ActiveCell.m_lSubItem = -1;
	if (m_ActiveCell.m_pCellCtrl)
		m_ActiveCell.m_pCellCtrl->OnKillActive();
	m_ActiveCell.m_pCellCtrl = NULL;
}

void CConfigListCtrl::ShiftItemsRight(int nCol)
{
	if (nCol) // Only required when nCol = 0. Done automatically otherwise
		return;

	int LastCol = GetHeaderCtrl()->GetItemCount() - 1;

	while (nCol < LastCol)
	{
		for (int Row = 0; Row < GetItemCount(); Row++)
			SetItem(Row, LastCol, GetItemText(Row, LastCol - 1));

		LastCol--;
	}

	if (nCol < GetHeaderCtrl()->GetItemCount() - 1)
		for (int Row = 0; Row < GetItemCount(); Row++)
			SetItem(Row, nCol, _T(""));
}

void CConfigListCtrl::RemoveCtrl(int nItem, int nSubItem)
{
	CCellCtrl				*pCellCtrl;

  	if (m_CtrlMap.Lookup(GetMapKey(nItem, nSubItem), pCellCtrl))
	{
		m_CtrlMap.RemoveKey(GetMapKey(nItem, nSubItem));

		if (m_ActiveCell.m_pCellCtrl == pCellCtrl)
			DeActivateCell();

		delete pCellCtrl; 

		m_CtrlSet.Remove(GetMapKey(nItem, nSubItem));
	}
}

void CConfigListCtrl::RemoveCtrlRow(int nItem)
{
	for (int nSubItem = 0; nSubItem < GetHeaderCtrl()->GetItemCount(); nSubItem++)
		RemoveCtrl(nItem, nSubItem);

	IncrCtrlMapRow(nItem, FALSE);
	m_CtrlSet.IncrementHIWORD(nItem, FALSE);

	Invalidate();
}

void CConfigListCtrl::RemoveCtrlColumn(int nSubItem)
{
	for (int nItem = 0; nItem < GetItemCount(); nItem++)
		RemoveCtrl(nItem, nSubItem);

	IncrCtrlMapColumn(nSubItem, FALSE);
	m_CtrlSet.IncrementLOWORD(nSubItem, FALSE);
}

void CConfigListCtrl::RemoveAllCtrls()
{
	ForEachCellCtrl(&CConfigListCtrl::DeleteCellCtrl);
}

void CConfigListCtrl::InsertCtrl(int nItem, int nSubItem, CCellCtrl *pCellCtrl)
{
  	ASSERT(pCellCtrl);

	RemoveCtrl(nItem, nSubItem);
	m_CtrlMap.SetAt(GetMapKey(nItem, nSubItem), pCellCtrl);
	m_CtrlSet.Insert(GetMapKey(nItem, nSubItem));
} 

int CConfigListCtrl::InsertItem(int nItem, CCellCtrl *pCellCtrl, LPCTSTR lpszDefaultTextValue /* = "\0"*/)
{
	InsertBookmark(nItem);
	ASSERT(pCellCtrl);

	InsertCtrl(nItem, 0, pCellCtrl);
	
	pCellCtrl->Initialize(m_hWnd, &m_bIsEnabled, lpszDefaultTextValue);

	return CListCtrl::InsertItem(nItem, _T("\0"));
}

BOOL CConfigListCtrl::SetItem(int nItem, int nSubItem, LPCTSTR lpszItem)
{
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIS_SELECTED;
	lvi.iItem = nItem;
	lvi.iSubItem = nSubItem;
	lvi.pszText = (LPTSTR)lpszItem;

	return CListCtrl::SetItem(&lvi);
}

BOOL CConfigListCtrl::SetItem(int nItem, int nSubItem, CCellCtrl *pCellCtrl, LPCTSTR lpszDefaultTextValue /* = "\0"*/)
{
	ASSERT(pCellCtrl);

	InsertCtrl(nItem, nSubItem, pCellCtrl);
	pCellCtrl->Initialize(m_hWnd, &m_bIsEnabled, lpszDefaultTextValue);

	return SetItem(nItem, nSubItem, pCellCtrl->GetSelectedTextValue());
}

DWORD IncrLOWORD(DWORD dwLocation, DWORD dwCompVal, BOOL incr)
{
	if (LOWORD(dwLocation) >= dwCompVal)
		dwLocation = MAKELONG(LOWORD(dwLocation) + ((incr)? 1 : -1), HIWORD(dwLocation));

	return dwLocation;
}

DWORD IncrHIWORD(DWORD dwLocation, DWORD dwCompVal, BOOL incr)
{
	if (HIWORD(dwLocation) >= dwCompVal)
		dwLocation = MAKELONG(LOWORD(dwLocation), HIWORD(dwLocation) + ((incr)? 1 : -1));

	return dwLocation;
}

void CConfigListCtrl::CopyMaps(const CCellMap &SourceMap, CCellMap &DestMap, DWORD dwCompVal /*= 0*/, BOOL Incr /*= TRUE*/,
																			DWORD (*pFunc)(DWORD, DWORD, BOOL) /*= NULL*/)
{
	DWORD				dwLocation;
	CCellCtrl			*pCellCtrl;

	POSITION Pos = SourceMap.GetStartPosition();
	DestMap.RemoveAll();	

	while (Pos)
	{
		SourceMap.GetNextAssoc(Pos, dwLocation, pCellCtrl);
		
		if (pFunc)
			dwLocation = (*pFunc)(dwLocation, dwCompVal, Incr);

		DestMap.SetAt(dwLocation, pCellCtrl);
	}
}

void CConfigListCtrl::IncrCtrlMapRow(WORD wRow, BOOL incr /*= TRUE*/)
{
	CCellMap			CtrlMap;
	CopyMaps(m_CtrlMap, CtrlMap, wRow, incr, IncrHIWORD);
	CopyMaps(CtrlMap, m_CtrlMap);
}

void CConfigListCtrl::IncrCtrlMapColumn(WORD wCol, BOOL incr /*= TRUE*/)
{
	CCellMap			CtrlMap;
	CopyMaps(m_CtrlMap, CtrlMap, wCol, incr, IncrLOWORD);
	CopyMaps(CtrlMap, m_CtrlMap);
}

void CConfigListCtrl::InsertBookmark(WORD nItem)
{
	IncrCtrlMapRow(nItem);
	m_CtrlSet.IncrementHIWORD(nItem);
}

void CConfigListCtrl::InsertColumn(WORD nItem)
{
	IncrCtrlMapColumn(nItem);
	m_CtrlSet.IncrementLOWORD(nItem);
}

void CConfigListCtrl::PreSubclassWindow() 
{
	CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();

	if (pHeaderCtrl)
	{
		VERIFY(m_HeaderCtrl.SubclassWindow(pHeaderCtrl->m_hWnd));
	}

	m_bIsEnabled = this->IsWindowEnabled();
	
	CListCtrl::PreSubclassWindow();
}

void CConfigListCtrl::DrawItemText(CDC *pDC, int nItem, int nSubItem, const LPRECT	prcBounding, UINT uiItemState)
{
	CBrush							Brush;
	RECT							rcTxt;
	CString							strText;

	if (!IsWindowEnabled())
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT)); // Text in a disabled CListCtrl stays black, so not using COLOR_GRAYTEXT
	}
	else if (uiItemState & (ODS_FOCUS | ODS_SELECTED))
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		Brush.CreateSolidBrush(GetSysColor(COLOR_WINDOW));
		pDC->SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
	}
	strText = GetItemText(nItem, nSubItem);
	pDC->FillRect(prcBounding, &Brush);
	
	CopyRect(&rcTxt, prcBounding);
	rcTxt.top += ::GetSystemMetrics(SM_CYFIXEDFRAME);

	pDC->DrawText(strText, &rcTxt, DT_LEFT | DT_BOTTOM | DT_END_ELLIPSIS);

	Brush.DeleteObject();
}

void CConfigListCtrl::CreateCaret()
{
	if (!m_bCaretExists)
	{
		LONG lHeight = ::GetSystemMetrics(SM_CYVTHUMB) + 2*::GetSystemMetrics(SM_CYEDGE) - 2*::GetSystemMetrics(SM_CYFIXEDFRAME);
		CreateSolidCaret(1, lHeight);
		m_bCaretExists = TRUE;
	}
}

void CConfigListCtrl::DeleteCaret()
{
	if (m_bCaretExists)
	{
		::DestroyCaret();
		m_bCaretExists = FALSE;
	}
}

void CConfigListCtrl::OnDrawInitialize(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC								DC;
	CRect							rc;
	int								iSavedDC;

	DC.Attach(lpDrawItemStruct->hDC);
	iSavedDC = DC.SaveDC();
	
	GetWindowRect(&rc);

	WINDOWPOS wp;
	wp.hwnd = this->m_hWnd;
	wp.cx = rc.Width() ;
	wp.cy = rc.Height() ;
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;

	SendMessage(WM_WINDOWPOSCHANGED, 0, reinterpret_cast<LPARAM> (&wp));

	DC.RestoreDC(iSavedDC);
	DC.Detach();
}

void CConfigListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC								DC;
	RECT							&rcItem = lpDrawItemStruct->rcItem;
	int								iSavedDC;
	UINT							&uiItemID = lpDrawItemStruct->itemID,
									&uiItemState = lpDrawItemStruct->itemState;
	LONG							lCol;
	RECT							rcCtrl;
	CCellCtrl						*pCellCtrl;

	DC.Attach(lpDrawItemStruct->hDC);
	iSavedDC = DC.SaveDC();

	if (!m_bInit)
	{
		OnDrawInitialize(lpDrawItemStruct); 
		m_bInit = TRUE;
	}

	for (lCol = 0; lCol < GetHeaderCtrl()->GetItemCount(); lCol++)
	{
		GetSubItemRect(uiItemID, lCol, LVIR_LABEL, (CRect &)rcCtrl);

		if (m_CtrlMap.Lookup(GetMapKey(uiItemID, lCol), pCellCtrl))
			pCellCtrl->DrawCtrl(&DC, &rcCtrl, uiItemState);
		else
			DrawItemText(&DC, uiItemID, lCol, &rcCtrl, uiItemState);
	}
	DC.RestoreDC(iSavedDC);
	DC.Detach();
}

void CConfigListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = ::GetSystemMetrics(SM_CYVTHUMB) + 2*::GetSystemMetrics(SM_CYEDGE);
}

void CConfigListCtrl::InvalidateActiveCellRect()
{
//	CRect ref;
//	GetSubItemRect(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, LVIR_BOUNDS, ref);
//	InvalidateRect(ref, FALSE);
	// Only redraw text area to avoid potential flicking of frame:
	InvalidateRect(&GetItemCellCtrl(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem)->GetTextRect(), TRUE);
	SetItem(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, m_ActiveCell.m_pCellCtrl->GetSelectedTextValue());
}

BOOL CConfigListCtrl::IsOnCellCtrl(int iItem, int iSubItem, CCellCtrl **ppCellCtrl) const
{
	BOOL bIsOnCtrl = FALSE;

//	if ((DWORD)iItem < m_dwBookmarkCount && (DWORD)iSubItem < m_dwColumnCount)
		if (m_CtrlMap.Lookup(GetMapKey(iItem, iSubItem), *ppCellCtrl))
			bIsOnCtrl = TRUE;
			
	return bIsOnCtrl;
}

CCellCtrl *CConfigListCtrl::GetItemCellCtrl(int iItem, int iSubItem) const
{
	BOOL bIsOnCtrl = FALSE;
	CCellCtrl *pCellCtrl = 0;

//	if ((DWORD)iItem < m_dwBookmarkCount && (DWORD)iSubItem < m_dwColumnCount)
		if (!m_CtrlMap.Lookup(GetMapKey(iItem, iSubItem), pCellCtrl))
			pCellCtrl = 0;
			
	return pCellCtrl;
}

void CConfigListCtrl::OnResizeColumn()
{
//	Invalidate(FALSE); // causes flicking.
	RECT rc;
	GetWindowRect(&rc);
	InvalidateRect(&rc, FALSE);

	ForEachCellCtrl(&CConfigListCtrl::OnInactiveResizeColumn);

	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		m_ActiveCell.m_pCellCtrl->OnResizeColumn();
}

void CConfigListCtrl::OnHeaderLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus(); // If don't put this, control does not have focus: caret is on wrong ctrl. 
}

void CConfigListCtrl::SetColumnMinWidth(int nCol)
// Set the column to the minimum wisth required so that all items in this column can be fully
// diplayed.
{
	int							nItem = 0,
								nWidth,
								nMinWidth = 0;
	CCellCtrl					*pCellCtrl;

// WARNING: GetNextItem always returns 0 if only one row.
// AS A RESULT CANNOT BE USED.	

	for (nItem = 0; nItem < GetItemCount(); nItem++)
	{
		if (m_CtrlMap.Lookup(GetMapKey(nItem, nCol), pCellCtrl))
			nWidth = pCellCtrl->GetMinWidth();
		else
			nWidth = GetStringWidth(GetItemText(nItem, nCol) + _T("i"));
	
		if (nWidth > nMinWidth)
			nMinWidth = nWidth;
	}
	if (!nCol) nMinWidth += GetSystemMetrics(SM_CXEDGE); // First column has a small indentation

	SetColumnWidth(nCol, nMinWidth);
	ForEachCellCtrl(&CConfigListCtrl::OnInactiveResizeColumn); // Remember: column will probably have been resized
}

BOOL CConfigListCtrl::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	BOOL bCall;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnCommand(wParam, lParam);

	return (bCall)? CListCtrl::OnCommand(wParam, lParam) : TRUE;
}

void CConfigListCtrl::OnParentMove(int x, int y)
{
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		m_ActiveCell.m_pCellCtrl->OnParentMove(x, y);
}

void CConfigListCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		bCall = m_ActiveCell.m_pCellCtrl->OnChar(nChar, nRepCnt, nFlags);
		InvalidateActiveCellRect();
		SetItem(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, m_ActiveCell.m_pCellCtrl->GetSelectedTextValue());
	}
	// Never call CListCtrl::OnChar: reason:
	// If do so, will automatically highlight a row in which first character of first column is same as typed character.
	// No notification received, and m_ActiveCell remains the active cell, so display is inconsistent.   
	//if (bCall)
	//	CListCtrl::OnChar(nChar, nRepCnt, nFlags);
}

void CConfigListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		m_ActiveCell.m_pCellCtrl->OnHScroll(nSBCode, nPos, pScrollBar);
	
	if (bCall)
		CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CConfigListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		m_ActiveCell.m_pCellCtrl->OnKeyDown(nChar, nRepCnt, nFlags);
		InvalidateActiveCellRect();
	}
	else
		CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CConfigListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		bCall = m_ActiveCell.m_pCellCtrl->OnKeyUp(nChar, nRepCnt, nFlags);
	//	InvalidateActiveCellRect();
	}
	if (bCall) 	
		CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CConfigListCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CListCtrl::OnKillFocus(pNewWnd);

	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		CListCtrlCellWnd *pListCtrlCellWnd = dynamic_cast<CListCtrlCellWnd *>(pNewWnd);

		// The code below is unfortunately needed when open a color picker and press 'enter' with 'Other'
		// button selected. Works with both CMFCColorDialog and CColorDialog.
		if (!pListCtrlCellWnd)
		{
			pNewWnd = pNewWnd->GetParentOwner();

			if (pNewWnd)
				pListCtrlCellWnd = dynamic_cast<CListCtrlCellWnd *>(pNewWnd->GetParent());
		}

		if (!pListCtrlCellWnd)
		{
			m_ActiveCell.m_pCellCtrl->OnKillActive();
			m_ActiveCell.m_pCellCtrl->OnKillFocus(pNewWnd);
			InvalidateActiveCellRect();
			m_ActiveCell.m_lItem = -1;
			m_ActiveCell.m_lSubItem = -1;
			m_ActiveCell.m_pCellCtrl = NULL;
		}
	}
	DeleteCaret();
}

void CConfigListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	BOOL bCall = TRUE;
	LVHITTESTINFO Info;
	CCellCtrl *pCellCtrl = NULL;
	BOOL bCaretExisted = m_bCaretExists;
	RECT rcSubItem;
	CWnd *pNewFocusedWin = NULL;

	Info.flags = 0;
	Info.pt = point;

	int iItem = SubItemHitTest(&Info);

	if (IsOnCellCtrl(Info.iItem, Info.iSubItem, &pCellCtrl) && !(pCellCtrl->GetStyle() & CLCS_DISABLED))
	{
		m_ActiveCell.m_lItem = Info.iItem;
		m_ActiveCell.m_lSubItem = Info.iSubItem;

		if (m_ActiveCell.m_pCellCtrl && m_ActiveCell.m_pCellCtrl != pCellCtrl)
			m_ActiveCell.m_pCellCtrl->OnKillActive();

		m_ActiveCell.m_pCellCtrl = pCellCtrl;

// The bounding rect for a combobox can be inaccurate without couple of lines below.
// 	Try commenting these and: use mousewheel up and down several time, then click 
//	on combo to see.
		GetSubItemRect(Info.iItem, Info.iSubItem, LVIR_LABEL, (CRect &)rcSubItem);
		pCellCtrl->SetWindowRect(&rcSubItem);

		SetFocus(); // only get focus when left mouse button is up otherwise
		
		bCall = pCellCtrl->OnLButtonDown(nFlags, point);
		pNewFocusedWin = GetFocus();
		SetItem(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, m_ActiveCell.m_pCellCtrl->GetSelectedTextValue());

		if (m_bCaretExists)
			pCellCtrl->OnCaretHandlingLButtonDown(nFlags, point);
	}
	else
		DeActivateCell();

//	this->Invalidate(FALSE); // Have to put this line, otherwise change of state of a cell is slow to show up.
	// Does not seem necessary anymore - might have been before.

	if (bCall)
		CListCtrl::OnLButtonDown(nFlags, point); // setfocus is called in here: m_bCaretExists is always true after this line

	if (pCellCtrl && !bCaretExisted)
		pCellCtrl->OnCaretHandlingLButtonDown(nFlags, point);

	if (pNewFocusedWin)
		::SetFocus(pNewFocusedWin->m_hWnd);
}

void CConfigListCtrl::InvalidateHotRect()
{
	RECT rcSubItem;
	GetSubItemRect(m_HotCell.m_lItem, m_HotCell.m_lSubItem, LVIR_LABEL, (CRect &)rcSubItem);
	InvalidateRect(&rcSubItem, FALSE);
}

void CConfigListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	if (IsAppThemed())
	{
		CCellCtrl *pCellCtrl = NULL;
		LVHITTESTINFO Info;

		Info.flags = 0;
		Info.pt = point;

		int iItem = SubItemHitTest(&Info);

		if (IsOnCellCtrl(Info.iItem, Info.iSubItem, &pCellCtrl))
		{
			if (m_HotCell.m_pCellCtrl != pCellCtrl)
			{
				if (m_HotCell.m_pCellCtrl)
				{
					m_HotCell.m_pCellCtrl->OnKillHot();
					InvalidateHotRect();
				}
				m_HotCell.Assign(pCellCtrl, Info.iItem, Info.iSubItem);
				m_HotCell.m_pCellCtrl->OnSetHot();
				InvalidateHotRect();
			}
			pCellCtrl->OnHotMouseMove(nFlags, point);
		}
		else if (m_HotCell.m_pCellCtrl)
		{
			m_HotCell.m_pCellCtrl->OnKillHot();
			InvalidateHotRect();
			m_HotCell.Assign(NULL, -1, -1);
		}
	}

	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnMouseMove(nFlags, point);
	
	if (bCall) CListCtrl::OnMouseMove(nFlags, point);
}

BOOL CConfigListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnMouseWheel(nFlags, zDelta, pt);
	
	return (bCall)? CListCtrl::OnMouseWheel(nFlags, zDelta, pt) : TRUE;
}

void CConfigListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnRButtonDown(nFlags, point);
	
	if (bCall) CListCtrl::OnRButtonDown(nFlags, point);
}

void CConfigListCtrl::OnSetFocus(CWnd* pOldWnd)
{
	CListCtrl::OnSetFocus(pOldWnd);
	CreateCaret();

	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		m_ActiveCell.m_pCellCtrl->OnSetFocus(pOldWnd);
}

void CConfigListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnVScroll(nSBCode, nPos, pScrollBar);
	
	if (bCall)
		CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CConfigListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnLButtonUp(nFlags, point);
	
	if (bCall)
		CListCtrl::OnLButtonUp(nFlags, point);
}

void CConfigListCtrl::OnTimer(UINT_PTR nIDEvent)
{
	BOOL bCall = TRUE;
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
		bCall = m_ActiveCell.m_pCellCtrl->OnTimer(nIDEvent);
	
	if (bCall)
		CListCtrl::OnTimer(nIDEvent);
}

LRESULT CConfigListCtrl::OnCellCtrlMsg(WPARAM wParam, LPARAM lParam)
{
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		m_ActiveCell.m_pCellCtrl->OnCellCtrlMsg(wParam, lParam);
		SetItem(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, m_ActiveCell.m_pCellCtrl->GetSelectedTextValue());
	}
	return TRUE; 
}

void CConfigListCtrl::OnEscape(DWORD dwLocation, CCellCtrl *pCellCtrl)
{
	CCellButton *pButton = dynamic_cast<CCellButton *>(pCellCtrl);

	if (pButton)
		pButton->OnEscape();
}

void CConfigListCtrl::OnEnter(DWORD dwLocation, CCellCtrl *pCellCtrl)
{
	CCellButton *pButton = dynamic_cast<CCellButton *>(pCellCtrl);

	if (pButton)
		pButton->OnEnter();
}

BOOL CConfigListCtrl::OnEnterEsc(WPARAM param)
{
	if (param == VK_ESCAPE) 
		ForEachCellCtrl(&CConfigListCtrl::OnEscape);
	else if (param == VK_RETURN)
		ForEachCellCtrl(&CConfigListCtrl::OnEnter);
	return TRUE;
}

void CConfigListCtrl::ActivateCellCtrl(DWORD dw)
{
	CCellCtrl *pCellCtrl;
	if (m_CtrlMap.Lookup(dw, pCellCtrl))
	{
		SetItemState(-1, 0, LVIS_SELECTED|LVIS_FOCUSED);
		m_ActiveCell.m_pCellCtrl = pCellCtrl;
		m_ActiveCell.m_lItem = HIWORD(dw);
		m_ActiveCell.m_lSubItem = LOWORD(dw);
		m_ActiveCell.m_pCellCtrl->OnSetActive();
		SetItemState(m_ActiveCell.m_lItem, LVIS_SELECTED, LVIS_SELECTED|LVIS_FOCUSED);
		RECT rcSubItem;
		GetSubItemRect(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem, LVIR_LABEL, (CRect &)rcSubItem);
		pCellCtrl->SetWindowRect(&rcSubItem);
		pCellCtrl->OnCaretHandlingLButtonDown(0, CPoint(0,0));
	}
}

DWORD CConfigListCtrl::GetNextEnabled(DWORD dw)
{
	CCellCtrl *pCellCtrl = NULL;

	while (m_CtrlMap.Lookup(dw, pCellCtrl) && pCellCtrl &&
						pCellCtrl->GetStyle() & CLCS_DISABLED && dw != m_CtrlSet.Last())
		dw = m_CtrlSet.Next(dw);

	return dw;
}

DWORD CConfigListCtrl::GetPrevEnabled(DWORD dw)
{
	CCellCtrl *pCellCtrl = NULL;

	while (m_CtrlMap.Lookup(dw, pCellCtrl) && pCellCtrl &&
						pCellCtrl->GetStyle() & CLCS_DISABLED && dw != m_CtrlSet.First())
		dw = m_CtrlSet.Prev(dw);

	return dw;
}

BOOL CConfigListCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYUP) 
		m_bKeyUp = TRUE;
	else if (pMsg->wParam == VK_TAB && m_bKeyUp)
	{ 
		m_bKeyUp = FALSE;

		if (GetKeyState(VK_SHIFT) & KEY_PRESSED)
		{
			if (!m_bTabbedIn)
			{
				m_bTabbedIn = TRUE;
				ActivateCellCtrl(GetPrevEnabled(m_CtrlSet.Last()));
				return TRUE;
			}
			else if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1 && 
				GetMapKey(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem) != m_CtrlSet.First())
			{
				DWORD dw = GetPrevEnabled(m_CtrlSet.Prev(GetMapKey(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem)));

				CCellCtrl *pCellCtrl = NULL;
				
				m_CtrlMap.Lookup(dw, pCellCtrl);

				if (pCellCtrl && pCellCtrl->GetStyle() & CLCS_DISABLED)
					m_bTabbedIn = FALSE;
				else
				{
					m_ActiveCell.m_pCellCtrl->OnKillActive();
					ActivateCellCtrl(dw);
					return TRUE;
				}
			}
			else
				m_bTabbedIn = FALSE;	
		}
		else
		{
			if (!m_bTabbedIn)
			{
				m_bTabbedIn = TRUE;
				ActivateCellCtrl(GetNextEnabled(m_CtrlSet.First()));
				return TRUE;
			}
			else if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1 && 
				GetMapKey(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem) != m_CtrlSet.Last())
			{
				DWORD dw = GetNextEnabled(m_CtrlSet.Next(GetMapKey(m_ActiveCell.m_lItem, m_ActiveCell.m_lSubItem)));

				CCellCtrl *pCellCtrl = NULL;
				
				m_CtrlMap.Lookup(dw, pCellCtrl);

				if (pCellCtrl && pCellCtrl->GetStyle() & CLCS_DISABLED)
					m_bTabbedIn = FALSE;
				else
				{
					m_ActiveCell.m_pCellCtrl->OnKillActive();
					ActivateCellCtrl(dw);
					return TRUE;
				}
			}
			else
				m_bTabbedIn = FALSE;
		}
	}
	else if (pMsg->wParam == VK_TAB)
	{ 
		m_bKeyUp = TRUE;
		m_bTabbedIn = TRUE;
		return PreTranslateMessage(pMsg);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

void CConfigListCtrl::OnThemeChanged(DWORD dwLocation, CCellCtrl *pCellCtrl)
{
	pCellCtrl->OnThemeChanged();
}

LRESULT CConfigListCtrl::OnThemeChanged()
{
	// This feature requires Windows XP or greater.
	// The symbol _WIN32_WINNT must be >= 0x0501.
	ForEachCellCtrl(&CConfigListCtrl::OnThemeChanged);

	// When theme changes, MeasureItem never seems to be called again, as it should. 
	// Not found a correct solution so heigth is correctly recomputed after a theme change...
	// Not too bad, as user won't change theme while this application is open that often...
	// Still annoying!

	return 1;
}

void CConfigListCtrl::OnEnable(BOOL bEnable)
{
	CListCtrl::OnEnable(bEnable);

	m_bIsEnabled = this->IsWindowEnabled();
}

void CConfigListCtrl::EnableCtrl(int iItem, int iSubItem, BOOL Enable /*= TRUE*/)
{
	CCellCtrl *pCellCtrl;

	if (IsOnCellCtrl(iItem, iSubItem, &pCellCtrl))
	{
		if (Enable)
			pCellCtrl->AddToStyle(CLCS_DISABLED);
		else
			pCellCtrl->RemoveFromStyle(CLCS_DISABLED);

		CRect rcCtrl;
		GetSubItemRect(iItem, iSubItem, LVIR_LABEL, rcCtrl);
		InvalidateRect(&rcCtrl, FALSE);
	}
}

BOOL CConfigListCtrl::IsCtrlEnabled(int iItem, int iSubItem)
{
	BOOL Enabled = m_bIsEnabled;
	CCellCtrl *pCellCtrl;

	if (IsOnCellCtrl(iItem, iSubItem, &pCellCtrl))
		Enabled = pCellCtrl->GetStyle() & CLCS_DISABLED;

	return Enabled;
}

BOOL CConfigListCtrl::SetItemValueFromCtrl(const CCellCtrl *pCellCtrl, const CString &strValue)
{
	DWORD				dwLocation;
	CCellCtrl			*pSearchCellCtrl;
	BOOL				bFound = FALSE;

	POSITION Pos = m_CtrlMap.GetStartPosition();

	while (Pos && !bFound)
	{
		m_CtrlMap.GetNextAssoc(Pos, dwLocation, pSearchCellCtrl);

		if (pSearchCellCtrl == pCellCtrl)
		{
			SetItem(HIWORD(dwLocation), LOWORD(dwLocation), strValue);
			bFound = FALSE;
		}
	}
	return bFound;
}

void CConfigListCtrl::OnSizing(UINT fwSide, LPRECT pRect)
{
	if (m_ActiveCell.m_lItem != -1 && m_ActiveCell.m_lSubItem != -1)
	{
		CCellButton *pButton = dynamic_cast<CCellButton *>(m_ActiveCell.m_pCellCtrl);

		if (pButton)
			pButton->OnEscape();
	}
}

BOOL  CConfigListCtrl::SetCtrlAlignment(int iItem, int iSubItem, Alignment align)
{
	CCellCtrl *pCellCtrl;

	if (IsOnCellCtrl(iItem, iSubItem, &pCellCtrl))
	{
		switch(align)
		{
			case Center:
				pCellCtrl->AddToStyle(CLCS_ALIGN_CENTER);
				pCellCtrl->RemoveFromStyle(CLCS_ALIGN_RIGHT);
			break;

			case Right:
				pCellCtrl->RemoveFromStyle(CLCS_ALIGN_CENTER);
				pCellCtrl->AddToStyle(CLCS_ALIGN_RIGHT);
			break;

			case Left:
			default:
				pCellCtrl->RemoveFromStyle(CLCS_ALIGN_CENTER);
				pCellCtrl->RemoveFromStyle(CLCS_ALIGN_RIGHT);
		}
		InvalidateRect(&pCellCtrl->GetModDrawAreaRect(), FALSE);
		return TRUE;
	}
	return FALSE;
}

BOOL  CConfigListCtrl::GetCtrlAlignment(int iItem, int iSubItem, Alignment &align)
{
	CCellCtrl *pCellCtrl;
	align = Left;

	if (IsOnCellCtrl(iItem, iSubItem, &pCellCtrl))
	{
		if (pCellCtrl->GetStyle() & CLCS_ALIGN_CENTER)
			align = Center;
		else if (pCellCtrl->GetStyle() & CLCS_ALIGN_RIGHT)
			align = Right;

		return TRUE;
	}
	return FALSE;
}