// MultiCheckListBox.cpp : implementation file
//

#include "stdafx.h"
#include "CheckBoxTest.h"
#include "MultiCheckListBox.h"
#include <afximpl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

class _AFX_CHECKLIST_STATE : public CNoTrackObject
{
public:
	_AFX_CHECKLIST_STATE();
	virtual ~_AFX_CHECKLIST_STATE();

	HBITMAP m_hbitmapCheck;
	CSize m_sizeCheck;
};

_AFX_CHECKLIST_STATE::_AFX_CHECKLIST_STATE()
{
	CBitmap bitmap;

	if (afxData.bWin4 || AfxGetCtl3dState()->m_pfnSubclassDlgEx != NULL)
		VERIFY(bitmap.LoadBitmap(AFX_IDB_CHECKLISTBOX_95));
	else
		VERIFY(bitmap.LoadBitmap(AFX_IDB_CHECKLISTBOX_NT));

	BITMAP bm;
	bitmap.GetObject(sizeof (BITMAP), &bm);
	m_sizeCheck.cx = bm.bmWidth / 3;
	m_sizeCheck.cy = bm.bmHeight;
	m_hbitmapCheck = (HBITMAP)bitmap.Detach();
}

_AFX_CHECKLIST_STATE::~_AFX_CHECKLIST_STATE()
{
	if (m_hbitmapCheck != NULL)
		::DeleteObject(m_hbitmapCheck);
}

EXTERN_PROCESS_LOCAL(_AFX_CHECKLIST_STATE, _afxChecklistState)

/////////////////////////////////////////////////////////////////////////////
// AFX_CHECK_DATA

struct AFX_CHECK_DATA
{
public:
	int m_nCheck;
	BOOL m_bEnabled;
	DWORD m_dwUserData;
	int m_nCheck2;

	AFX_CHECK_DATA()
	{
		m_nCheck = 0;
		m_bEnabled = TRUE;
		m_dwUserData = 0;
		m_nCheck2 = 0;
	};
};

/////////////////////////////////////////////////////////////////////////////
// CMultiCheckListBox

CMultiCheckListBox::CMultiCheckListBox()
{
}

CMultiCheckListBox::~CMultiCheckListBox()
{
}


BEGIN_MESSAGE_MAP(CMultiCheckListBox, CCheckListBox)
	//{{AFX_MSG_MAP(CMultiCheckListBox)
	ON_WM_MEASUREITEM()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiCheckListBox message handlers
void CMultiCheckListBox::PreDrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	_AFX_CHECKLIST_STATE* pChecklistState = _afxChecklistState;

	if ((((LONG)lpDrawItemStruct->itemID) >= 0) &&
	   ((lpDrawItemStruct->itemAction & (ODA_DRAWENTIRE | ODA_SELECT)) != 0))
	{
		int cyItem = GetItemHeight(lpDrawItemStruct->itemID);

		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		COLORREF newBkColor = GetSysColor(COLOR_WINDOW);

		BOOL fDisabled = !IsWindowEnabled() || !IsEnabled(lpDrawItemStruct->itemID);
		if ((lpDrawItemStruct->itemState & ODS_SELECTED) && !fDisabled)
			newBkColor = GetSysColor(COLOR_HIGHLIGHT);

		COLORREF oldBkColor = pDC->SetBkColor(newBkColor);

		int nCheck;
		CDC bitmapDC;
		HBITMAP hOldBitmap;
		CRect rectCheck;
		CRect rectItem;
		CRect rectCheckBox;
		if (bitmapDC.CreateCompatibleDC(pDC))
		{
			nCheck = GetCheck(lpDrawItemStruct->itemID);
			hOldBitmap = (HBITMAP)::SelectObject(bitmapDC.m_hDC, pChecklistState->m_hbitmapCheck);

			rectCheck = lpDrawItemStruct->rcItem;
			rectCheck.left += 1;
			rectCheck.top += 1 + max(0, (cyItem - pChecklistState->m_sizeCheck.cy) / 2);
			rectCheck.right = rectCheck.left + pChecklistState->m_sizeCheck.cx;
			rectCheck.bottom = rectCheck.top + pChecklistState->m_sizeCheck.cy;

			rectItem = lpDrawItemStruct->rcItem;
			rectItem.right = rectItem.left + pChecklistState->m_sizeCheck.cx + 2;
			rectItem.right += pChecklistState->m_sizeCheck.cx + 2;

			rectCheckBox = OnGetCheckPosition(rectItem, rectCheck);

			ASSERT(rectCheck.IntersectRect(rectItem, rectCheckBox));
			ASSERT((rectCheck == rectCheckBox) && (rectCheckBox.Size() == pChecklistState->m_sizeCheck));

			CBrush first_brush(newBkColor);
			pDC->FillRect(rectItem, &first_brush);

			pDC->BitBlt(rectCheckBox.left, rectCheckBox.top,
				pChecklistState->m_sizeCheck.cx, pChecklistState->m_sizeCheck.cy, &bitmapDC,
				pChecklistState->m_sizeCheck.cx  * nCheck, 0, SRCCOPY);

			::SelectObject(bitmapDC.m_hDC, hOldBitmap);
		}

		pDC->SetBkColor(oldBkColor);
	}

	if (lpDrawItemStruct->itemData != 0)
	{
		AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lpDrawItemStruct->itemData;
		lpDrawItemStruct->itemData = pState->m_dwUserData;
	}
	
	lpDrawItemStruct->rcItem.left = lpDrawItemStruct->rcItem.left + pChecklistState->m_sizeCheck.cx + 2;
	CCheckListBox::PreDrawItem(lpDrawItemStruct);
}


BOOL CMultiCheckListBox::OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult) 
{
	switch (message)
	{
	case WM_DRAWITEM:
		ASSERT(pLResult == NULL);       // no return value expected
		PreDrawItem((LPDRAWITEMSTRUCT)lParam);
		break;
	default:
		return CCheckListBox::OnChildNotify(message, wParam, lParam, pLResult);
	}

	return TRUE;
}

PROCESS_LOCAL(_AFX_CHECKLIST_STATE, _afxChecklistState)

void CMultiCheckListBox::SetCheck(int nIndex, int nCheck)
{
	ASSERT(::IsWindow(m_hWnd));

	if (nCheck == 2)
	{
		if (m_nStyle == BS_CHECKBOX || m_nStyle == BS_AUTOCHECKBOX)
			return;
	}

	LRESULT lResult = DefWindowProc(LB_GETITEMDATA, nIndex, 0);
	if (lResult != LB_ERR)
	{

		AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lResult;

		if (pState == NULL)
			pState = new AFX_CHECK_DATA;

		pState->m_nCheck2 = nCheck;
		VERIFY(DefWindowProc(LB_SETITEMDATA, nIndex, (LPARAM)pState) != LB_ERR);

		InvalidateCheck(nIndex);
	}
}

int CMultiCheckListBox::GetCheck(int nIndex)
{
	ASSERT(::IsWindow(m_hWnd));

	LRESULT lResult = DefWindowProc(LB_GETITEMDATA, nIndex, 0);
	if (lResult != LB_ERR)
	{
		AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lResult;
		if (pState != NULL)
			return pState->m_nCheck2;  // check in first checkbox
	}
	return 0; // The default
}

void CMultiCheckListBox::InvalidateCheck(int nIndex)
{
	CRect rect;
	_AFX_CHECKLIST_STATE* pChecklistState = _afxChecklistState;

	GetItemRect(nIndex, rect);
	rect.right = rect.left + pChecklistState->m_sizeCheck.cx + 2;
	rect.right = rect.left + pChecklistState->m_sizeCheck.cx + 2;
	InvalidateRect(rect, FALSE);
}

void CMultiCheckListBox::SetMultiCheck(int nIndex, int nCheck)
{
	ASSERT(::IsWindow(m_hWnd));

	if (nCheck == 2)
	{
		if (m_nStyle == BS_CHECKBOX || m_nStyle == BS_AUTOCHECKBOX)
			return;
	}

	LRESULT lResult = DefWindowProc(LB_GETITEMDATA, nIndex, 0);
	if (lResult != LB_ERR)
	{

		AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lResult;

		if (pState == NULL)
			pState = new AFX_CHECK_DATA;

		pState->m_nCheck = nCheck;
		VERIFY(DefWindowProc(LB_SETITEMDATA, nIndex, (LPARAM)pState) != LB_ERR);

		InvalidateMultiCheck(nIndex);
	}
}

int CMultiCheckListBox::GetMultiCheck(int nIndex)
{
	ASSERT(::IsWindow(m_hWnd));

	LRESULT lResult = DefWindowProc(LB_GETITEMDATA, nIndex, 0);
	if (lResult != LB_ERR)
	{
		AFX_CHECK_DATA* pState = (AFX_CHECK_DATA*)lResult;
		if (pState != NULL)
			return pState->m_nCheck;
	}
	return 0; // The default
}

void CMultiCheckListBox::InvalidateMultiCheck(int nIndex)
{
	CRect rect;
	_AFX_CHECKLIST_STATE* pChecklistState = _afxChecklistState;

	GetItemRect(nIndex, rect);
	rect.left += pChecklistState->m_sizeCheck.cx + 2;
	InvalidateRect(rect, FALSE);
}

int CMultiCheckListBox::CheckFromPoint(CPoint point, BOOL& bInCheck)
{
	// assume did not hit anything
	bInCheck = FALSE;
	int nIndex = -1;

	_AFX_CHECKLIST_STATE* pChecklistState = _afxChecklistState;
	if ((GetStyle() & (LBS_OWNERDRAWFIXED|LBS_MULTICOLUMN)) == LBS_OWNERDRAWFIXED)
	{
		// optimized case for ownerdraw fixed, single column
		int cyItem = GetItemHeight(0);
		if (point.y < cyItem * GetCount())
		{
			nIndex = GetTopIndex() + point.y / cyItem;
			if (point.x < pChecklistState->m_sizeCheck.cx + 2)
				++bInCheck;
		}
	}
	else
	{
		// general case for ownerdraw variable or multiple column
		for (int i = GetTopIndex(); i < GetCount(); i++)
		{
			CRect itemRect;
			GetItemRect(i, &itemRect);
			if (itemRect.PtInRect(point))
			{
				nIndex = i;
				if (point.x < itemRect.left + pChecklistState->m_sizeCheck.cx + 2)
					++bInCheck;
				break;
			}
		}
	}
	return nIndex;
}

int CMultiCheckListBox::InMultiCheck(CPoint point, BOOL& bInMultiCheck)
{
	// assume did not hit anything
	bInMultiCheck = FALSE;
	int nIndex = -1;

	_AFX_CHECKLIST_STATE* pChecklistState = _afxChecklistState;
	if ((GetStyle() & (LBS_OWNERDRAWFIXED|LBS_MULTICOLUMN)) == LBS_OWNERDRAWFIXED)
	{
		// optimized case for ownerdraw fixed, single column
		int cyItem = GetItemHeight(0);
		if (point.y < cyItem * GetCount())
		{
			nIndex = GetTopIndex() + point.y / cyItem;
			if (point.x < pChecklistState->m_sizeCheck.cx + 2 + (pChecklistState->m_sizeCheck.cx + 2))
				++bInMultiCheck;
		}
	}
	else
	{
		// general case for ownerdraw variable or multiple column
		for (int i = GetTopIndex(); i < GetCount(); i++)
		{
			CRect itemRect;
			GetItemRect(i, &itemRect);
			if (itemRect.PtInRect(point))
			{
				nIndex = i;
				if (point.x < itemRect.left + pChecklistState->m_sizeCheck.cx + 2)
					++bInMultiCheck;
				break;
			}
		}
	}
	return nIndex;
}

void CMultiCheckListBox::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();

	// determine where the click is
	BOOL bInCheck;
	BOOL bInMultiCheck;
	int nIndex = CheckFromPoint(point, bInCheck);
	int n2Index = InMultiCheck(point, bInMultiCheck);

	// if the item is disabled, then eat the click
	if (!IsEnabled(nIndex))
		return;

	if (m_nStyle != BS_CHECKBOX && m_nStyle != BS_3STATE)
	{
		// toggle check mark automatically if check mark was hit
		if (bInCheck)
		{
			CWnd* pParent = GetParent();
			ASSERT_VALID(pParent);

			int nModulo = (m_nStyle == BS_AUTO3STATE) ? 3 : 2;
			int nCheck = GetCheck(nIndex);
			nCheck = (nCheck == nModulo) ? nCheck - 1 : nCheck;
			SetCheck(nIndex, (nCheck + 1) % nModulo);

			InvalidateCheck(nIndex);

			CListBox::OnLButtonDown(nFlags, point);

			// Inform of check
			pParent->SendMessage(WM_COMMAND,
				MAKEWPARAM(GetDlgCtrlID(), CLBN_CHKCHANGE),
				(LPARAM)m_hWnd);
			return;
		}
		if (bInMultiCheck)
		{
			CWnd* pParent = GetParent();
			ASSERT_VALID(pParent);
			int nModulo = (m_nStyle == BS_AUTO3STATE) ? 3 : 2;
			int nCheck = GetMultiCheck(nIndex);
			nCheck = (nCheck == nModulo) ? nCheck - 1 : nCheck;
			SetMultiCheck(nIndex, (nCheck + 1) % nModulo);

			CListBox::OnLButtonDown(nFlags, point);

			// Inform of check
			pParent->SendMessage(WM_COMMAND,
				MAKEWPARAM(GetDlgCtrlID(), CLBN_CHKCHANGE),
				(LPARAM)m_hWnd);
			return;
		}
	}

	// do default listbox selection logic
	CListBox::OnLButtonDown(nFlags, point);
}
