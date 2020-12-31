// SkinCtrls.cpp : implementation file
//

#include "stdafx.h"
#include "SkinCtrls.h"
#include "skinctrlmgr.h"
#include "..\shared\wclassdefines.h"
#include "..\shared\winclasses.h"
#include "..\shared\roundcorner.h"

//#define ACTIVATE_VIEWER
//#include "imageviewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// globals -- no other way using windows hooks.
static CSkinCtrl*	g_pCtrl = NULL;
static HHOOK		g_hMsgHook = NULL;
static int			g_nScrollbar = -1;

const int CORNER = 4;
const int EDGE = 1;
const int SCROLLCX = ::GetSystemMetrics(SM_CXHSCROLL);

//#define RC_THIN RC_NORMAL

/////////////////////////////////////////////////////////////////////////////
// CSkinCtrls

BOOL CSkinTreeview::AttachWindow(CWnd* pCtrl)
{
	if (!(pCtrl->GetExStyle() & WS_EX_CLIENTEDGE))
		m_dwBaseStyle &= ~SKCS_EDGEMASK;

	return CSkinCtrl::AttachWindow(pCtrl);
}
/*
BOOL CSkinTreeview::OnPaint(CDC* pDC)
{
	if (GetStyle() & TVS_HASBUTTONS)
	{
		CTreeCtrl* pTree = GetTree();

		COLORREF crBack = GetSysColor(COLOR_WINDOW);
		int nIndent = pTree->GetIndent();
		HTREEITEM htItem = pTree->GetFirstVisibleItem();

		CImageList* pILNormal = pTree->GetImageList(TVSIL_NORMAL);
		CImageList* pILState = pTree->GetImageList(TVSIL_STATE);

		while (htItem)
		{
			if (pTree->ItemHasChildren(htItem))
			{
				CRect rButton = GetItemButtonRect(htItem, nIndent, pILNormal, pILState);
				
				// draw the arrow
				BOOL bExpanded = (pTree->GetItemState(htItem, TVIS_EXPANDED) & TVIS_EXPANDED);
				int nOffset = (rButton.Width() - 9) / 2;
				CPoint ptTopLeft = rButton.TopLeft();
				ptTopLeft.Offset(nOffset, nOffset);
				
				DrawItemButton(pDC, rButton, !bExpanded);
				
				pDC->ExcludeClipRect(rButton);
			}
			htItem = pTree->GetNextVisibleItem(htItem);
		}
	}

	return FALSE; // allow default drawing also
}

CRect CSkinTreeview::GetItemButtonRect(HTREEITEM htItem, int nIndent, CImageList* pILNormal, CImageList* pILState)
{
	const float FUDGE_FACTOR = 0.612f;

	CTreeCtrl* pTree = GetTree();
	CRect rItem;
	pTree->GetItemRect(htItem, rItem, TRUE);
				
	// offset for normal image
	if (pILNormal)
	{
		int nImage, nSel;
		
		if (pTree->GetItemImage(htItem, nImage, nSel))
		{
			int cx, cy;
			ImageList_GetIconSize(pILNormal->m_hImageList, &cx, &cy);
			rItem.OffsetRect(-(cx + nIndent / 2 - 13 + (32 - cx) / 2), 0);		
		}
	}
				
	// offset for state image
	if (pILState)
	{
		int nState = (pTree->GetItemState(htItem, LVIS_STATEIMAGEMASK) & LVIS_STATEIMAGEMASK);
		int nImage = nState >> 12;
					
		if (nImage)
		{
			int cx, cy;
			ImageList_GetIconSize(pILState->m_hImageList, &cx, &cy);
			rItem.OffsetRect(-cx, 0);
		}
	}
				
	// rItem.left is now the centre of the button
	rItem.OffsetRect(-(nIndent + 1) / 2, 0);
				
	int nButtonWidth = (int)(rItem.Height() * FUDGE_FACTOR);
				
	rItem.left -= (nButtonWidth) / 2;
	rItem.right = rItem.left + nButtonWidth;
	rItem.DeflateRect(0, (rItem.Height() - nButtonWidth) / 2);
	rItem.OffsetRect(0, 1);

	rItem.bottom = rItem.top + rItem.Width();

	return rItem;
}


void CSkinTreeview::DrawItemButton(CDC* pDC, CRect rButton, BOOL bPlus)
{
	COLORREF crLine = GetColor(COLOR_3DDKSHADOW);
	COLORREF crBorder = GetColor(COLOR_3DSHADOW);
	
	if (GetControlBitmap(SKCB_TREEPLUS, IM_HOT, NULL, SKCB_TREEALL))
	{
		COLORREF crMask;

		CRect rScreen(rButton);
		GetTree()->ClientToScreen(rScreen);

		int nState = IsHot(rScreen, TRUE) ? IM_HOT : IM_COLD;
		CBitmap* pButton = GetControlBitmap(bPlus ? SKCB_TREEPLUS : SKCB_TREEMINUS, nState, &crMask, SKCB_TREEALL);

		BITMAP bm;
		pButton->GetBitmap(&bm);

		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		CBitmap *pOldBitmap = dcMem.SelectObject(pButton);

		CSkinBase::StretchBlt(pDC, rButton.left, rButton.top, rButton.Width(), rButton.Height(),
								&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);
		
		dcMem.SelectObject(pOldBitmap);
	}
	else // manual
	{
		// border
		pDC->FillSolidRect(rButton.left + 1, rButton.top, rButton.Width() - 2, 1, crBorder);
		pDC->FillSolidRect(rButton.left, rButton.top + 1, 1, rButton.Height() - 2, crBorder);
		pDC->FillSolidRect(rButton.right  - 1, rButton.top + 1, 1, rButton.Height() - 2, crBorder);
		pDC->FillSolidRect(rButton.left + 1, rButton.bottom - 1, rButton.Width() - 2, 1, crBorder);
	}

	if (!GetControlBitmap(SKCB_TREEPLUS))
	{
		CPoint ptCenter = rButton.CenterPoint();

		// horz line
		pDC->FillSolidRect(rButton.left + 2, ptCenter.y, rButton.Width() - 4, 1, crLine);

		if (bPlus) // vert line
			pDC->FillSolidRect(ptCenter.x, rButton.top + 2, 1, rButton.Height() - 4, crLine);
	}
}
*/
void CSkinTreeview::OnSetIni()
{
	CSkinCtrl::OnSetIni();

	GetTree()->SetBkColor(GetColor(COLOR_WINDOW));
}

LRESULT CSkinTreeview::OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage)
{
	switch (dwStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			CDC* pDC = CDC::FromHandle(pNMCD->hdc);
			NMTVCUSTOMDRAW* pTVCD = (NMTVCUSTOMDRAW*)pNMCD;

			BOOL bSelected = (pNMCD->uItemState & CDIS_SELECTED);

			if (bSelected)
				return CDRF_DODEFAULT;

			// else
			pTVCD->clrText = GetColor(COLOR_WINDOWTEXT);
			pTVCD->clrTextBk = GetBkgndColor();

			return CDRF_NEWFONT;
		}
	}
	// default
	return CDRF_DODEFAULT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinListview::AttachWindow(CWnd* pCtrl)
{
	if (!(pCtrl->GetExStyle() & WS_EX_CLIENTEDGE))
		m_dwBaseStyle &= ~SKCS_EDGEMASK;

	return CSkinCtrl::AttachWindow(pCtrl);
}

LRESULT CSkinListview::OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage)
{
	switch (dwStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			CDC* pDC = CDC::FromHandle(pNMCD->hdc);
			NMLVCUSTOMDRAW* pLVCD = (NMLVCUSTOMDRAW*)pNMCD;

			pLVCD->clrText = GetColor(COLOR_WINDOWTEXT);
			pLVCD->clrTextBk = GetBkgndColor();
			pDC->SetBkColor(GetBkgndColor());

			return CDRF_NEWFONT;
		}
	}
	// default
	return CDRF_DODEFAULT;
}

void CSkinListview::OnSetIni()
{
	CSkinCtrl::OnSetIni();

	GetList()->SetBkColor(GetColor(COLOR_WINDOW));
	GetList()->SetTextBkColor(GetColor(COLOR_WINDOW));
	GetList()->SetTextColor(GetColor(COLOR_WINDOWTEXT));
}

void CSkinListview::OnStyleChanged(BOOL bExStyle, DWORD dwOldStyle, DWORD dwNewStyle)
{
	if (!bExStyle)
	{
		OnSetIni();

		if ((dwNewStyle & LVS_TYPEMASK) == LVS_REPORT)
		{
			CWnd* pChild = GetChildWnd(WC_HEADER);
			
			if (pChild && !GetSkinCtrl(pChild))
				Skin(*pChild);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinIPaddress::OnPaint(CDC* pDC)
{
	// draw a dot between each edit box
	CWnd* pEdit1 = GetChildWnd(WC_EDIT);
	ASSERT (pEdit1);

	if (pEdit1)
	{
		CWnd* pEdit2 = pEdit1->GetNextWindow();
		ASSERT (pEdit2);

		CWnd* pEdit3 = pEdit2->GetNextWindow();
		ASSERT (pEdit3);

		CWnd* pEdit4 = pEdit3->GetNextWindow();
		ASSERT (pEdit4);

		CRect r1, r2, r3, r4;

		((CEdit*)pEdit1)->GetRect(r1);
		((CEdit*)pEdit2)->GetRect(r2);
		((CEdit*)pEdit3)->GetRect(r3);
		((CEdit*)pEdit4)->GetRect(r4);

		CWnd* pThis = GetCWnd();

		pEdit1->MapWindowPoints(pThis, r1);
		pEdit2->MapWindowPoints(pThis, r2);
		pEdit3->MapWindowPoints(pThis, r3);
		pEdit4->MapWindowPoints(pThis, r4);

		COLORREF crDot = GetColor(COLOR_WINDOWTEXT);
		pDC->SetPixelV((r1.right + r2.left) / 2, r1.bottom - 2, crDot);
		pDC->SetPixelV((r2.right + r3.left) / 2, r1.bottom - 2, crDot);
		pDC->SetPixelV((r3.right + r4.left) / 2, r1.bottom - 2, crDot);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinEdit::AttachWindow(CWnd* pCtrl)
{
	if (!(pCtrl->GetExStyle() & WS_EX_CLIENTEDGE))
		m_dwBaseStyle &= ~SKCS_EDGEMASK;

	return CSkinCtrl::AttachWindow(pCtrl);
}

LRESULT CSkinEdit::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_KEYDOWN:
			if (wp == VK_BACK || wp == VK_DELETE)
				Invalidate();

			else if (wp == VK_UP || wp == VK_DOWN || wp == VK_LEFT || wp == VK_RIGHT || 
				wp == VK_PRIOR || wp == VK_NEXT || wp == VK_END || wp == VK_HOME)
			{
				Default();
				Refresh(TRUE);
				return 0;
			}
			break;

		case WM_KEYUP:
			if (wp == VK_UP || wp == VK_DOWN || wp == VK_LEFT || wp == VK_RIGHT || 
				wp == VK_PRIOR || wp == VK_NEXT || wp == VK_END || wp == VK_HOME)
			{
				Default();
				Refresh(TRUE);
				return 0;
			}
			break;

		case WM_MOUSEWHEEL:
			Default();
			Refresh(TRUE);
			return 0;

		case WM_VSCROLL:
		case WM_HSCROLL:
			Default();
			Refresh(TRUE);
			return 0;
	}

	return CSkinCtrl::OnMsg(msg, wp, lp);
}

COLORREF CSkinEdit::GetBkgndColor() 
{ 
	if (!IsWindowEnabled() || (GetStyle() & ES_READONLY))
		return GetColor(COLOR_3DFACE);
	
	// else
	return CSkinCtrl::GetBkgndColor();
}

void CSkinEdit::OnNotifyReflect(UINT uNotify, LRESULT lrParent)
{
	switch (uNotify)
	{
		case EN_UPDATE:
			SendMessage(WM_NCPAINT);
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinRichedit::AttachWindow(CWnd* pCtrl)
{
	if (CSkinEdit::AttachWindow(pCtrl))
	{
		// otherwise we don't receive EN_UPDATEs
		DWORD dwEventMask = pCtrl->SendMessage(EM_GETEVENTMASK);
		dwEventMask |= ENM_UPDATE;
		pCtrl->SendMessage(EM_SETEVENTMASK, 0, dwEventMask);
		
		return TRUE;
	}
	
	return FALSE;
}

LRESULT CSkinRichedit::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_MOUSEWHEEL:
		case WM_KEYUP:
		case WM_KEYDOWN:
		case WM_VSCROLL:
		case WM_HSCROLL:
			Default(); // bypass CSkinEdit
			return 0;
	}

	return CSkinEdit::OnMsg(msg, wp, lp);
}

void CSkinRichedit::OnSetIni()
{
	CSkinEdit::OnSetIni();

	GetRichEdit()->SetBackgroundColor(FALSE, GetColor(COLOR_WINDOW));
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinCombobox::AttachWindow(CWnd* pCtrl)
{
	DWORD dwStyle = pCtrl->GetStyle();
	int nType = (dwStyle & 0xf);
	
	// droplist drawing can only be well done via ownerdraw
	if (nType == CBS_DROPDOWNLIST)
	{
		if (dwStyle & CBS_OWNERDRAWFIXED || dwStyle & CBS_OWNERDRAWVARIABLE)
			m_bIsOwnerdraw = TRUE;
/*		else
		{
			pCtrl->ModifyStyle(0, CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS);
			m_dwBaseStyle |= SKCS_DRAWITEM;
		}
*/	}
	
	return CSkinCtrl::AttachWindow(pCtrl);
}

void CSkinCombobox::OnNcCalcSize(LPRECT pClient)
{
	::InflateRect(pClient, -EDGE, 0);
	
	if ((GetStyle() & 0xf) != CBS_SIMPLE)
		pClient->right -= EDGE;
	
	else
		pClient->right += EDGE;
}

BOOL CSkinCombobox::OnPaint(CDC* pDC)
{
	int nType = (GetStyle() & 0xf);

	if (nType == CBS_DROPDOWN)
		return TRUE; // edit box draws

	CComboBox* pCombo = GetCombo();
	CRect rClient;
	GetClientRect(rClient);

	CRect rPaint(rClient);
	rPaint.DeflateRect(3, 3);
	rClient.InflateRect(5, 5);

	BOOL bEndPaint = FALSE;

	if (nType == CBS_SIMPLE)
	{
		// also exclude the divider between the edit and listbox
		CWnd* pLBox = GetChildWnd(WC_COMBOLBOX);
		
		if (pLBox)
		{
			CRect rLBox;
			pLBox->GetWindowRect(rLBox);
			pLBox->ScreenToClient(rLBox);
			pLBox->MapWindowPoints(pCombo, rLBox);

			pDC->ExcludeClipRect(rClient.left, rLBox.top, rClient.right, EDGE * 2);
		}
	}
	else if (!m_bIsOwnerdraw)
	{
		// all we do is paint the current selected item
		CComboBox* pCombo = GetCombo();
		BOOL bFocus = !pCombo->GetDroppedState() && CWnd::GetFocus() == pCombo;
		BOOL bEnabled = IsWindowEnabled();

		COLORREF crBack = bFocus ? GetColor(COLOR_HIGHLIGHT) : GetBkgndColor();
		COLORREF crText = GetColor(bFocus ? COLOR_HIGHLIGHTTEXT : bEnabled ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);

		pDC->SelectStockObject(ANSI_VAR_FONT);
		pDC->SetBkColor(crBack);
		pDC->SetTextColor(crText);
		pDC->SetBkMode(TRANSPARENT);
		
		CString sText;
		pCombo->GetWindowText(sText);

		rPaint.InflateRect(1, 1);
		rPaint.right -= SCROLLCX - 3;
		pDC->FillSolidRect(rPaint, GetBkgndColor());
		rPaint.DeflateRect(0, 1);
		
		if (bFocus)
		{
			pDC->FillSolidRect(rPaint, crBack);
			rPaint.right--;
			pDC->DrawFocusRect(rPaint);
		}

		rPaint.OffsetRect(1, -1);
		pDC->DrawText(sText, rPaint, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
		
		// finally redraw button
		CRect rButton;
		GetClientRect(rButton);
		DrawDropButton(pDC, rButton);

		bEndPaint = TRUE;
	}
	else
		rPaint.right -= SCROLLCX - 3;

	pDC->ExcludeClipRect(rClient.left, rClient.top, rClient.right, rPaint.top);
	pDC->ExcludeClipRect(rClient.left, rClient.top, rPaint.left, rClient.bottom);
	pDC->ExcludeClipRect(rPaint.right, rClient.top, rClient.right, rClient.bottom);
	pDC->ExcludeClipRect(rClient.left, rPaint.bottom, rClient.right, rClient.bottom);

	return bEndPaint;
}

void CSkinCombobox::DrawDropButton(CDC* pDC, CRect& rClient, LPPOINT ptCursor)
{
	rClient.top += (rClient.Height() - SCROLLCX) / 2;
	rClient.bottom = rClient.top + SCROLLCX;
	rClient.left = rClient.right - SCROLLCX;
	
	CSkinCtrl::DrawDropButton(pDC, rClient, ptCursor, GetBkgndColor());
}

void CSkinCombobox::OnSetFocus(BOOL bSet)
{
	if (!bSet) // kill focus
	{
		CWindowDC dc(GetCWnd());
		CRect rClient;
		GetDrawRect(NULL, rClient);
		DrawDropButton(&dc, rClient);
	}

	if (!m_bIsOwnerdraw)
		Invalidate(FALSE);
}

void CSkinCombobox::OnNcPaint(CDC* pDC)
{
	if ((GetStyle() & 0xf) != CBS_SIMPLE)
	{
		CSkinCtrl::OnNcPaint(pDC);
		
		CRect rClient;
		GetDrawRect(NULL, rClient);
		DrawDropButton(pDC, rClient);
	}
	else
	{
		CWnd* pLBox = GetChildWnd(WC_COMBOLBOX);
		
		if (pLBox)
		{
			CRect rLBox, rWindow;
			GetDrawRect(rWindow);
			
			pLBox->GetWindowRect(rLBox);
			pLBox->ScreenToClient(rLBox);
			pLBox->MapWindowPoints(GetCWnd(), rLBox);
			
			// paint a thin border around the combolbox
			pDC->FillSolidRect(rWindow.left, rLBox.top, EDGE, rLBox.Height(), GetParentBkgndColor());
			pDC->FillSolidRect(rWindow.left, rLBox.top - EDGE, rWindow.Width(), EDGE, GetParentBkgndColor());
			
			// then border the edit box
			rWindow.bottom = rLBox.top - 1;
			
			NcPaintBorder(pDC, rWindow, GetParentBkgndColor(), GetBkgndColor(), EdgeStyle());
		}
	}
}

void CSkinCombobox::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	CSkinCtrl::OnUpdateHotspots(pOldCursor, pNewCursor, uOldHitTest, uNewHitTest);

	if ((GetStyle() & 0xf) == CBS_SIMPLE)
		return;

	CRect rButton;
	GetDrawRect(NULL, rButton);
	rButton.top += (rButton.Height() - SCROLLCX) / 2;
	rButton.bottom = rButton.top + SCROLLCX;
	rButton.left = rButton.right - SCROLLCX;

	BOOL bOn = FALSE, bWasOn = FALSE;

	if (pOldCursor && pNewCursor)
	{
		bOn = rButton.PtInRect(*pNewCursor);
		bWasOn = rButton.PtInRect(*pOldCursor);
	}
	else if (pOldCursor)
		bWasOn = rButton.PtInRect(*pOldCursor);

	else if (pNewCursor)
		bOn = rButton.PtInRect(*pNewCursor);

	if (bOn != bWasOn)
	{
		CWindowDC dc(GetCWnd());
		CSkinCtrl::DrawDropButton(&dc, rButton, NULL, GetBkgndColor());
	}
}

COLORREF CSkinCombobox::GetBkgndColor()
{
	if (IsWindowEnabled())
		return m_bIsOwnerdraw ? ::GetSysColor(COLOR_WINDOW) : GetColor(COLOR_WINDOW);
	else
		return m_bIsOwnerdraw ? ::GetSysColor(COLOR_3DFACE) : GetColor(COLOR_3DFACE);
}

BOOL CSkinCombobox::OnEraseBkgnd(CDC* pDC)
{
	CRect rClient;
	GetClientRect(rClient);
	
	if ((GetStyle() & 0xf) != CBS_SIMPLE)
	{
		CRect rButton = rClient;
		DrawDropButton(pDC, rButton);
		pDC->ExcludeClipRect(rButton);
	}
	else
	{
		CWnd* pLBox = GetChildWnd(WC_COMBOLBOX);
		
		if (pLBox)
		{
			CRect rLBox;
			pLBox->GetWindowRect(rLBox);
			pLBox->ScreenToClient(rLBox);
			pLBox->MapWindowPoints(GetCWnd(), rLBox);

			rClient.bottom = rLBox.top - 1;
		}
	}
	
	rClient.DeflateRect(2, 2);
	rClient.right--;
	pDC->FillSolidRect(rClient, GetBkgndColor());
	
	return TRUE;
}

void CSkinCombobox::OnNotifyReflect(UINT uNotify, LRESULT lrParent)
{
	switch (uNotify)
	{
		case CBN_DROPDOWN:
		case CBN_CLOSEUP:
			{
				CWindowDC dc(GetCWnd());
				CRect rClient;
				GetDrawRect(NULL, rClient);
				DrawDropButton(&dc, rClient);

				DelayRedraw(200);
			}
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinUpdown::OnPaint(CDC* pDC)
{
	CRect rClient;
	GetClientRect(rClient);

	if (CWinClasses::IsClass(::GetParent(GetHwnd()), WC_DATETIMEPICK))
	{
		rClient.bottom--;
		rClient.right--;
	}

	DrawSpinButton(pDC, rClient, NULL, !(GetStyle() & UDS_HORZ), GetParentBkgndColor());
	return TRUE;
}

void CSkinUpdown::OnNcPaint(CDC* pDC)
{
	CRect rWindow;
	GetDrawRect(rWindow);

	if (CWinClasses::IsClass(::GetParent(GetHwnd()), WC_DATETIMEPICK))
	{
		rWindow.bottom--;
		rWindow.right--;
	}

	DrawSpinButton(pDC, rWindow, NULL, !(GetStyle() & UDS_HORZ), GetParentBkgndColor());
}

void CSkinUpdown::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// if its move on or off then its a simple redraw
	if (!pOldCursor || !pNewCursor)
		Invalidate(FALSE);

	else
	{
		CRect rWindow, rBack, rForward;
		GetDrawRect(rWindow);

		rBack = rForward = rWindow;

		if (GetStyle() & UDS_HORZ)
		{
			rBack.right = (rBack.right + rBack.left) / 2;
			rForward.left = rBack.right;
		}
		else
		{
			rBack.bottom = (rBack.top + rBack.bottom) / 2;
			rForward.top = rBack.bottom;
		}

		BOOL bOn = rBack.PtInRect(*pNewCursor);
		BOOL bWasOn = rBack.PtInRect(*pOldCursor);

		if (bOn != bWasOn)
		{
			Invalidate(FALSE);
			return;
		}

		bOn = rForward.PtInRect(*pNewCursor);
		bWasOn = rForward.PtInRect(*pOldCursor);

		if (bOn != bWasOn)
		{
			Invalidate(FALSE);
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinScrollbar::AttachWindow(CWnd* pCtrl)
{
	DWORD dwStyle = pCtrl->GetStyle();

	if ((dwStyle & SBS_SIZEBOX) || (dwStyle & SBS_SIZEGRIP))
	{
		if (CSkinCtrl::AttachWindow(pCtrl))
		{
			m_dwBaseStyle |= SKCS_PAINT | SKCS_ERASEBKGND | SKCS_NCPAINT;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSkinScrollbar::OnPaint(CDC* pDC)
{
	return TRUE;
}

void CSkinScrollbar::OnNcPaint(CDC* pDC)
{
}


//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinHotkey::OnPaint(CDC* pDC)
{
/*	// all we do is paint the current selected item
	CComboBox* pCombo = GetCombo();
	BOOL bFocus = !pCombo->GetDroppedState() && CWnd::GetFocus() == pCombo;
	COLORREF crBack = bFocus ? GetColor(COLOR_HIGHLIGHT) : GetBkgndColor();
	COLORREF crText = bFocus ? GetColor(COLOR_HIGHLIGHTTEXT) : GetColor(COLOR_WINDOWTEXT);
	pDC->SelectStockObject(ANSI_VAR_FONT);
	pDC->SetBkColor(crBack);
	pDC->SetTextColor(crText);
	
	CString sText;
	pCombo->GetWindowText(sText);
	
	CRect rClient;
	GetClientRect(rClient);
	rClient.right -= SCROLLCX - 3;
	rClient.DeflateRect(3, 3);
	
	pDC->ExtTextOut(rClient.left + 1, rClient.top + 1, ETO_CLIPPED | ETO_OPAQUE, rClient, sText, NULL);
*/	
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinListbox::AttachWindow(CWnd* pCtrl)
{
	DWORD dwStyle = pCtrl->GetStyle();
	
	if (!(pCtrl->GetExStyle() & WS_EX_CLIENTEDGE))
		m_dwBaseStyle &= ~SKCS_EDGEMASK;

	// we don't support LBS_DISABLENOSCROLL at present
	if (pCtrl->GetStyle() & LBS_DISABLENOSCROLL)
	{
		TRACE("*** CSkinListbox cannot support LBS_DISABLENOSCROLL. must be removed in dialog template or elsewhere prior to creation time");
		return FALSE;
	}

	return CSkinCtrl::AttachWindow(pCtrl);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinStatic::AttachWindow(CWnd* pCtrl)
{
	DWORD dwStyle = pCtrl->GetStyle();
	int nType = (dwStyle & 0x1F);
	
	switch (nType)
	{
		case SS_LEFT:
		case SS_RIGHT:
		case SS_CENTER:
		case SS_SIMPLE:
		case SS_LEFTNOWORDWRAP:
			m_dwBaseStyle |= SKCS_NCPAINT;
			break;

		case SS_ETCHEDHORZ:       
		case SS_ETCHEDVERT:       
		case SS_ETCHEDFRAME: 
			m_dwBaseStyle |= SKCS_PAINT | SKCS_NCPAINT | SKCS_NOBASENCPAINT | SKCS_ETCHEDEDGE;
			break;

		case SS_ICON:
			m_dwBaseStyle |= SKCS_NOEDGE | SKCS_PAINT | SKCS_NOBASENCPAINT;

		default:
			m_dwBaseStyle |= SKCS_PAINT | SKCS_NCPAINT | SKCS_NOBASENCPAINT;
			break;
	}

	return CSkinCtrl::AttachWindow(pCtrl);
}

COLORREF CSkinStatic::GetBkgndColor() 
{
	DWORD dwStyle = GetStyle();

	if (dwStyle & SS_SUNKEN)
	{
		int nType = (dwStyle & 0x1F);

		switch (nType)
		{
			case SS_BLACKRECT: 
				return GetColor(COLOR_3DDKSHADOW);

			case SS_GRAYRECT:         
				return GetColor(COLOR_3DSHADOW);

			case SS_WHITERECT:   
				return GetColor(COLOR_3DHIGHLIGHT);

			case SS_ETCHEDHORZ:       
			case SS_ETCHEDVERT:       
			case SS_ETCHEDFRAME: 
				return GetColor(COLOR_3DFACE);
		}
	}
	
	return GetParentBkgndColor(); 
}

LRESULT CSkinStatic::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_PAINT:
			{
				DWORD dwStyle = GetStyle();

				if ((dwStyle & SS_SUNKEN)/* && (dwStyle & 0x1F) == SS_ICON*/)
				{
					LRESULT lr = CSkinCtrl::OnMsg(msg, wp, lp);

					CWindowDC dc(GetCWnd());
					CRect rect;
					GetDrawRect(rect);
					
					if (!s_pRenderer)
						FillCorners(&dc, rect, GetParentBkgndColor());

					Draw3dEdge(&dc, rect, CORNER, SKCS_CLIENTEDGE, IsWindowEnabled() ? IM_COLD : IM_DISABLED);

					return lr;
				}
				break;
			}
	}

	return CSkinCtrl::OnMsg(msg, wp, lp);
}

BOOL CSkinStatic::OnPaint(CDC* pDC)
{
	int nType = (GetStyle() & 0x1F);

	switch (nType)
	{
		case SS_BLACKRECT: 
		case SS_GRAYRECT:         
		case SS_WHITERECT:   
			{
				CRect rClient;
				GetClientRect(rClient);

				pDC->FillSolidRect(rClient, GetBkgndColor());
				return TRUE;
			}

		case SS_BLACKFRAME: 
		case SS_GRAYFRAME:         
		case SS_WHITEFRAME:   
		case SS_ETCHEDHORZ:       
		case SS_ETCHEDVERT:       
		case SS_ETCHEDFRAME: 
			return TRUE;
	}

	return FALSE;
}

void CSkinStatic::OnNcPaint(CDC* pDC)
{
	CSkinCtrl::OnNcPaint(pDC);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinProgress::OnPaint(CDC* pDC)
{
	CRect rClient;
	GetClientRect(rClient);
	rClient.DeflateRect(1, 1);
	
	BOOL bSmooth = (GetStyle() & PBS_SMOOTH);
	BOOL bHorz = !(GetStyle() & PBS_VERTICAL);

	int nPos= GetProgress()->GetPos();
	
	int nLower, nUpper;
	GetProgress()->GetRange(nLower, nUpper);

	if (bHorz)
		rClient.right = rClient.left + (rClient.Width() * nPos) / (nUpper - nLower);
	else
		rClient.top = rClient.bottom - (rClient.Height() * nPos) / (nUpper - nLower);

	if (GetControlBitmap(SKCB_PROGRESSLEFT))
	{
		COLORREF crMask;
		CBitmap* pLeft = GetControlBitmap(SKCB_PROGRESSLEFT, IM_HOT, &crMask);
		CBitmap* pRight = GetControlBitmap(SKCB_PROGRESSRIGHT, IM_HOT, &crMask);
		CBitmap* pMid = GetControlBitmap(SKCB_PROGRESSMIDDLE, IM_HOT, &crMask);

		DrawPushButton(pDC, rClient, pLeft, pMid, pRight, GetBkgndColor(), crMask);
	}
	else
	{
		CPen* pOldPen = pDC->SelectObject(GetColorPen(COLOR_HIGHLIGHT));
		CBrush* pOldBr = pDC->SelectObject(GetColorBrush(COLOR_HIGHLIGHT));
		
		if (bSmooth)
			pDC->RoundRect(rClient, CPoint(CORNER * 2, CORNER * 2));
		
		else
		{
			// the standard bar element is 2/3 the client breadth
			const int DIVIDER = 2;
			CRect rBar(rClient);

			if (bHorz)
			{
				int nWidth = (rClient.Height() * 2) / 3;
				rBar.right = min(rClient.right, rBar.left + nWidth);
				
				while (rBar.right <= rClient.right)
				{
					pDC->RoundRect(rBar, CPoint(CORNER * 2, CORNER * 2));
					rBar.OffsetRect(DIVIDER + nWidth, 0);
				}
			}
			else
			{
				int nHeight = (rClient.Width() * 2) / 3;
				rBar.top = max(rClient.top, rBar.bottom - nHeight);
				
				while (rBar.top >= rClient.top)
				{
					pDC->RoundRect(rBar, CPoint(CORNER * 2, CORNER * 2));
					rBar.OffsetRect(0, -(DIVIDER + nHeight));
				}
			}
		}
	
		pDC->SelectObject(pOldBr);
		pDC->SelectObject(pOldPen);
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinDatetimepick::s_bDropDown = FALSE;
const UINT TIMER_DROP = 1;

void CSkinDatetimepick::OnNcCalcSize(LPRECT pClient)
{
	::InflateRect(pClient, -EDGE, -EDGE);
}

void CSkinDatetimepick::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	CSkinCtrl::OnUpdateHotspots(pOldCursor, pNewCursor, uOldHitTest, uNewHitTest);

	if (GetStyle() & DTS_UPDOWN)
		return;

	CRect rClient;
	GetDrawRect(NULL, rClient);
	rClient.InflateRect(0, EDGE);

	CRect rButton = rClient;
	rButton.top += (rButton.Height() - SCROLLCX) / 2;
	rButton.bottom = rButton.top + SCROLLCX;
	rButton.left = rButton.right - SCROLLCX;

	BOOL bOn = FALSE, bWasOn = FALSE;
	
	// if its move on or off then its a simple redraw
	if (pOldCursor && pNewCursor)
	{
		bOn = rButton.PtInRect(*pNewCursor);
		bWasOn = rButton.PtInRect(*pOldCursor);
	}
	else if (pOldCursor)
		bWasOn = rButton.PtInRect(*pOldCursor);

	else if (pNewCursor)
		bOn = rButton.PtInRect(*pNewCursor);

	if (bOn != bWasOn)
	{
		CWindowDC dc(GetCWnd());
		DrawDropButton(&dc, rClient);
	}
}

LRESULT CSkinDatetimepick::OnNotifyReflect(NMHDR* pNMHDR, LRESULT lrParent)
{
	switch (pNMHDR->code)
	{
	case DTN_DROPDOWN:
		s_bDropDown = TRUE;
		SendMessage(WM_NCPAINT);
		GetCtrl()->SetRedraw(FALSE);
		GetCtrl()->SetTimer(TIMER_DROP, 10, NULL);
		break;
		
	case DTN_CLOSEUP:
		s_bDropDown = FALSE;
		GetCtrl()->SetRedraw(TRUE);
		GetCtrl()->KillTimer(TIMER_DROP);
		DelayRedraw(200);
		break;
		
	case DTN_DATETIMECHANGE:
		Invalidate(FALSE);
		break;
	}
	
	return 0;
}

void CSkinDatetimepick::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == TIMER_DROP)
	{
		if (s_bDropDown)
		{
			GetCtrl()->SetRedraw(TRUE);
			
			CWindowDC dc(GetCWnd());
			CRect rClient;
			GetDrawRect(NULL, rClient);
			rClient.InflateRect(0, EDGE);
			DrawDropButton(&dc, rClient);
		}
		else
		{
			GetCtrl()->KillTimer(TIMER_DROP);
			GetCtrl()->SetRedraw(TRUE);
		}
	}
}

void CSkinDatetimepick::DrawDropButton(CDC* pDC, CRect& rClient, LPPOINT ptCursor)
{
	CRect rButton(rClient);
	rButton.left = rClient.right - SCROLLCX;

	if (rButton.Height() > SCROLLCX)
	{
		int nClip = max(0, (rButton.Height() - SCROLLCX) / 2);

		rButton.top += nClip;
		rButton.bottom = rButton.top + SCROLLCX;
		
		// paint over drop button first above and below the 
		pDC->FillSolidRect(rButton.left, rClient.top, rClient.right - rButton.left, nClip, GetBkgndColor());
		pDC->FillSolidRect(rButton.left, rButton.bottom, rClient.right - rButton.left, rClient.bottom - rButton.bottom, GetBkgndColor());
	}

	CSkinCtrl::DrawDropButton(pDC, rButton, ptCursor, GetBkgndColor());

	rClient = rButton;
}

BOOL CSkinDatetimepick::OnPaint(CDC* pDC)
{
	// ideally we could use the same approach as the combobox
	// except it doesn't work because the dropdown button gets 
	// drawn without reference to the clip rect
	
	// all we do is paint the current selected item
	CDateTimeCtrl* pPicker = GetPicker();
	
	BOOL bFocus = !s_bDropDown && (CWnd::GetFocus() == pPicker);
	BOOL bEnabled = IsWindowEnabled();
	
	pDC->SelectStockObject(ANSI_VAR_FONT);
	
	CString sText;
	pPicker->GetWindowText(sText);
	
	CRect rClient, rText;
	GetClientRect(rClient);
		
	rClient.right -= SCROLLCX;
	pDC->FillSolidRect(rClient, bFocus ? GetColor(COLOR_HIGHLIGHT) : GetBkgndColor());

	rText = rClient;
	CalcTextRect(pDC, sText, rText, DT_LEFT | DT_VCENTER);
	rText.OffsetRect(2, 0);

	pDC->SetTextColor(GetColor(bFocus ? COLOR_HIGHLIGHTTEXT : bEnabled ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
	pDC->SetBkMode(TRANSPARENT);
			
	pDC->DrawText(sText, rText, DT_TOP | DT_LEFT | DT_END_ELLIPSIS);
	
	if (bFocus)
		pDC->DrawFocusRect(rClient);
	
	return TRUE;
}

void CSkinDatetimepick::OnNcPaint(CDC* pDC)
{
	CSkinCtrl::OnNcPaint(pDC);

	if (!(GetStyle() & DTS_UPDOWN))
	{
		CRect rClient;
		GetDrawRect(NULL, rClient);
		rClient.InflateRect(0, EDGE);
		DrawDropButton(pDC, rClient);
	}	
}

BOOL CSkinDatetimepick::OnEraseBkgnd(CDC* pDC)
{
	CRect rClient;
	GetClientRect(rClient);
		
	if (!(GetStyle() & DTS_UPDOWN))
	{
		CRect rButton(rClient);
		rButton.InflateRect(0, EDGE);
		DrawDropButton(pDC, rButton);
		
		rButton.top--;
		pDC->ExcludeClipRect(rButton);
	}
	
	rClient.InflateRect(2, 2);
	
	if (CWnd::GetFocus() != GetCWnd())
		pDC->FillSolidRect(rClient, GetBkgndColor());
	
	return TRUE;
}

void CSkinDatetimepick::OnSetFocus(BOOL bSet) 
{
	Invalidate();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

CSkinButton* CSkinButton::NewButton(DWORD dwBtnStyle)
{
	CSkinButton* pButton = NULL;
	int nType = (dwBtnStyle & 0x0f); 

	switch (nType)
	{
		case BS_PUSHBUTTON:       
		case BS_DEFPUSHBUTTON: 
			return new CSkinButtonPush;
			
		case BS_CHECKBOX:         
		case BS_AUTOCHECKBOX:     
		case BS_3STATE:           
		case BS_AUTO3STATE:       
			return new CSkinButtonCheck;

		case BS_RADIOBUTTON:      
		case BS_AUTORADIOBUTTON:  
			return new CSkinButtonRadio;

		case BS_GROUPBOX:     
			return new CSkinButtonGroup;
			
		case BS_OWNERDRAW:        
		case BS_USERBUTTON: 
			return new CSkinButtonPush;

		default:
			return NULL; // let user draw
	}
}

BOOL CSkinButton::AttachWindow(CWnd* pCtrl)
{
	m_nButtonType = (pCtrl->GetStyle() & 0x0f); 
	
	BOOL bRes = CSkinCtrl::AttachWindow(pCtrl);

	// there's something odd going on in the file dialog (amongst others)
	// whereby the text is not rendered correctly perhaps because the text
	// is not present when we first render it.
	if (bRes)
		DelayRedraw(1);

	return bRes;
}

CRect CSkinButton::GetCheckRect()
{
	CRect rect;
	GetClientRect(rect);

	BOOL bRadio = (m_nButtonType == BS_AUTORADIOBUTTON || m_nButtonType == BS_RADIOBUTTON);
	BOOL bCheck = (m_nButtonType == BS_AUTOCHECKBOX || m_nButtonType == BS_CHECKBOX ||
					m_nButtonType == BS_AUTO3STATE || m_nButtonType == BS_3STATE);

	if (bRadio || bCheck)
	{
		UINT nStyle = GetStyle();
		
		if (nStyle & BS_LEFTTEXT)
			rect.left = rect.right - 16;
		else
			rect.right = rect.left + 16;
		
		// fall thru
		if (!(nStyle & BS_VCENTER) || (nStyle & BS_VCENTER) == BS_VCENTER)
		{
			rect.top = (rect.top + rect.bottom - 16) / 2;
			rect.bottom = rect.top + 16;
		}
		else if (nStyle & BS_BOTTOM)
			rect.top = rect.bottom - 16;
		
		else // top
			rect.bottom = rect.top + 16;
		
		if (bCheck)
		{
			rect.DeflateRect(1, 1);
			rect.right--;
			rect.bottom--;
		}
		else
			rect.DeflateRect(2, 2);
	}

	return rect;
}

UINT CSkinButton::GetTextAlignment()
{
	UINT nTextAlign = 0;
	UINT nStyle = GetStyle();

	// vert
	if (!(nStyle & BS_VCENTER))
		nTextAlign |= DT_VCENTER;
		
	else if ((nStyle & BS_VCENTER) == BS_VCENTER)
		nTextAlign |= DT_VCENTER;

	else if (nStyle & BS_BOTTOM)
		nTextAlign |= DT_BOTTOM;

	else // top
		nTextAlign |= DT_TOP;

	// horz
	if (!(nStyle & BS_CENTER))
	{
		if (m_nButtonType == BS_PUSHBUTTON || m_nButtonType == BS_DEFPUSHBUTTON)
			nTextAlign |= DT_CENTER;
		else
			nTextAlign |= DT_LEFT;
	}
	else if ((nStyle & BS_CENTER) == BS_CENTER)
		nTextAlign |= DT_CENTER;

	else if (nStyle & BS_LEFT)
		nTextAlign |= DT_LEFT;

	else // right
		nTextAlign |= DT_RIGHT;

	// lines
	if (!(nStyle & BS_MULTILINE))
		nTextAlign |= DT_SINGLELINE;

	return nTextAlign;
}

LRESULT CSkinButton::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	LRESULT lr = 0;

	switch (msg)
	{
	case WM_SETFOCUS:
	case WM_KILLFOCUS:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case BM_SETCHECK:
		{
			SetRedraw(FALSE);
			lr = Default();
			SetRedraw(TRUE);

			Invalidate(FALSE);
			UpdateWindow(GetHwnd());
			return lr;
		}

	case BM_SETSTATE:
		{
			BOOL bCurState = (SendMessage(BM_GETSTATE) & BST_PUSHED);

			if ((wp && bCurState) || (!wp && !bCurState))
				break; // no change

			SetRedraw(FALSE);
			lr = Default();
			SetRedraw(TRUE);

			Invalidate(FALSE);
			UpdateWindow(GetHwnd());
			return lr;
		}
	}

	return CSkinCtrl::OnMsg(msg, wp, lp);
}

////

BOOL CSkinButtonPush::AttachWindow(CWnd* pCtrl)
{
	if (CSkinButton::AttachWindow(pCtrl))
	{
		if (m_nButtonType == BS_OWNERDRAW || m_nButtonType == BS_USERBUTTON)
			m_dwBaseStyle |= SKCS_POSTDRAWITEM;

		return TRUE;
	}

	return FALSE;
}

BOOL CSkinButtonPush::OnPaint(CDC* pDC) // return FALSE to allow default painting
{
	// owner draw push buttons handled in OnDrawItem
	if (m_nButtonType == BS_OWNERDRAW || m_nButtonType == BS_USERBUTTON)
		return FALSE;

	CRect rClient;
	GetClientRect(rClient);
	
	int nState = 0;
	BOOL bFocus = FALSE, bDown = FALSE;

	if (!IsWindowEnabled())
		nState = IM_DISABLED;
	else
	{
		UINT uState = GetButton()->GetState();

		bDown = (uState & 0x0004);
		bFocus = (uState & 0x0008);

		nState = bDown ? IM_DOWN : (IsHot() ? IM_HOT : IM_COLD);
	}
	
	Draw(pDC, rClient, nState, bFocus, FALSE);

	return TRUE;
}

void CSkinButtonPush::Draw(CDC* pDC, LPRECT pRect, int nState, BOOL bFocus, BOOL bOwnerdraw)
{
	UINT nTextAlign = GetTextAlignment();
	
	CBitmap bmp;
	CRect rClient(pRect);
	CRect rText(rClient);
	
	bmp.CreateCompatibleBitmap(pDC, rClient.Width(), rClient.Height());
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = dcMem.SelectObject(&bmp);
		
	BOOL bClipLeft = HasCtrlStyle(SKBS_CLIPLEFT);
	BOOL bClipRight = HasCtrlStyle(SKBS_CLIPRIGHT);
	
	// bitmaps or std drawn
	if (GetControlBitmap(SKCB_BUTTONLEFT))
	{
		COLORREF crMask;
		CBitmap* pLeft = GetControlBitmap(bClipLeft ? SKCB_BUTTONCLIPLEFT : SKCB_BUTTONLEFT, nState, &crMask, SKCB_BUTTONLEFT);
		CBitmap* pRight = GetControlBitmap(bClipRight ? SKCB_BUTTONCLIPRIGHT : SKCB_BUTTONRIGHT, nState, NULL, SKCB_BUTTONRIGHT);
		CBitmap* pMid = GetControlBitmap(SKCB_BUTTONMIDDLE, nState);

		DrawPushButton(&dcMem, rClient, pLeft, pMid, pRight, GetParentBkgndColor(), crMask);
	}
	else
	{
		int nCorner = (min(rClient.Height(), rClient.Width()) / 2) - CORNER;

		DrawPushButton(&dcMem, rClient, nState, nCorner, GetParentBkgndColor(), bClipLeft, bClipRight);
	}

	// if we are ownerdraw then we transparentblt pDC to our memDC
	if (bOwnerdraw)
	{
		CSkinBase::BitBlt(&dcMem, 4, 4, rClient.Width() - 8, rClient.Height() - 8,
							pDC, 4, 4, SRCCOPY, GetSysColor(COLOR_3DFACE));
	}
	else // else we draw the text, bitmap or icon
	{
		CButton* pBtn = GetButton();
		DWORD dwStyle = pBtn->GetButtonStyle();

		if (dwStyle & (BS_ICON | BS_BITMAP)) // we must do it this way because BS_TEXT == 0
		{
			rText.DeflateRect(CORNER, CORNER);

			if (dwStyle & BS_ICON)
			{
				HICON hIcon = pBtn->GetIcon();

				if (hIcon)
				{
					CRect rIcon(0, 0, 33, 33); // 33 instead of 32 to allow for down state
					AlignRect(rIcon, rText, nTextAlign);

					if (nState == IM_DOWN) 
						rIcon.OffsetRect(1, 1);
					
					dcMem.DrawIcon(rIcon.TopLeft(), hIcon);
				}
			}
			else if (dwStyle & BS_BITMAP)
			{
				CBitmap* pBitmap = CBitmap::FromHandle(pBtn->GetBitmap());

				if (pBitmap)
				{
					BITMAP BM;
					pBitmap->GetBitmap(&BM);

					CRect rBM(0, 0, min(BM.bmWidth, rText.Width()), min(BM.bmWidth, rText.Height()));
					BM.bmWidth++; // to allow for down state
					BM.bmHeight++; // to allow for down state

					AlignRect(rBM, rText, nTextAlign);

					if (nState == IM_DOWN) 
						rBM.OffsetRect(1, 1);
					
					CDC dcBtn;
					dcBtn.CreateCompatibleDC(pDC);
					CBitmap* pOld = dcBtn.SelectObject(pBitmap);

					// use the std light gray color (192, 192, 192) as the transparent color
					CSkinBase::BitBlt(&dcMem, rBM.left, rBM.top, rBM.Width() - 1, rBM.Height() - 1, 
										&dcBtn, 0, 0, SRCCOPY, 0xc0c0c0);

					// cleanup
					dcBtn.SelectObject(pOld);
					dcBtn.DeleteDC();
				}
			}

			// Draw the focus circle on the inside of the button
			if (bFocus)
				dcMem.DrawFocusRect(rText);
		}
		else
		{
			// draw the text if there is any
			CString strText;
			pBtn->GetWindowText(strText);

			dcMem.SelectStockObject(ANSI_VAR_FONT);
			rText.DeflateRect(CORNER, 0);
			CalcTextRect(&dcMem, strText, rText, nTextAlign);
			
			if (nState == IM_DOWN) 
				rText.OffsetRect(1, 1);
			
			if (!strText.IsEmpty())
			{
				dcMem.SetBkMode(TRANSPARENT);
				
				COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_BTNTEXT : COLOR_GRAYTEXT);
				COLORREF oldcol = dcMem.SetTextColor(colorText);

				dcMem.DrawText(strText, rText, nTextAlign | DT_END_ELLIPSIS);
				dcMem.SetTextColor(oldcol);
				
				rText.InflateRect(2, 2);
			}
			else
				rText.DeflateRect(CORNER, CORNER);
			
			// Draw the focus circle on the inside of the button if it is non-stretched
			if (bFocus)
				dcMem.DrawFocusRect(rText);
		}
	}
	
	// blt to screen
	pDC->BitBlt(0, 0, rClient.right, rClient.bottom, &dcMem, 0, 0, SRCCOPY);
	
	// cleanup
	dcMem.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	dcMem.DeleteDC();
}

BOOL CSkinButtonPush::OnDrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	// sanity check
	if (!(m_nButtonType == BS_OWNERDRAW || m_nButtonType == BS_USERBUTTON))
		return FALSE;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	BOOL bDis = (lpDIS->itemState & ODS_DISABLED);
	BOOL bFocus = (!bDis && (lpDIS->itemState & ODS_FOCUS));
	BOOL bDown = (lpDIS->itemState & ODS_SELECTED);

	int nState = bDis ? IM_DISABLED : (bDown ? IM_DOWN : (IsHot() ? IM_HOT : IM_COLD));

	Draw(pDC, &lpDIS->rcItem, nState, bFocus, TRUE);

	return TRUE;
}

COLORREF CSkinButtonPush::GetBkgndColor()
{
	return CSkinCtrl::GetBkgndColor();
}

void CSkinButtonPush::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// update if the cursor has moved on or off
	if (!pOldCursor || !pNewCursor)
		Invalidate(FALSE);
}

////

BOOL CSkinButtonGroup::OnPaint(CDC* pDC)
{
	CString strText;
	GetCtrl()->GetWindowText(strText);
	CSize sizeExtent;
	
	pDC->SelectStockObject(ANSI_VAR_FONT);
	sizeExtent = pDC->GetTextExtent("ABC");
	
	CRect rText, rGroup;
	GetClientRect(rText);

	rGroup = rText;
	rGroup.top += sizeExtent.cy / 2;
	
	// draw outline
	Draw3dEdge(pDC, rGroup, min(9, min(rGroup.Height(), rGroup.Width() / 2)), SKCS_ETCHEDEDGE, IM_COLD);
	
	// draw text
	if (!strText.IsEmpty())
	{
		// add a buffer char to front and back
		strText = " " + strText + " ";

		rText.DeflateRect(CORNER, 0);
		UINT nAlign = (GetTextAlignment() & (DT_CENTER | DT_LEFT | DT_RIGHT));
		nAlign |= DT_TOP | DT_SINGLELINE;
		CalcTextRect(pDC, strText, rText, nAlign);
		
		COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
		COLORREF oldcol = pDC->SetTextColor(colorText);

		pDC->SetBkColor(GetBkgndColor());
		pDC->DrawText(strText, rText, nAlign);
		pDC->SetTextColor(oldcol);
	}
	
	return TRUE;
}

COLORREF CSkinButtonGroup::GetBkgndColor()
{
	return GetParentBkgndColor(); 
}

////

BOOL CSkinButtonCheck::OnPaint(CDC* pDC) // return FALSE to allow default painting
{
	CRect rClient, rText, rect;
	GetClientRect(rClient);
	rText = rect = rClient;
	
	UINT nState = GetButton()->GetState();

	BOOL bDown = (nState & 0x0004);
	BOOL bFocus = (nState & 0x0008);
	
	CString strText;
	GetCtrl()->GetWindowText(strText);
	UINT nTextAlign = GetTextAlignment();
	
	CBitmap bmp;
	
	GetClientRect(rClient);
	bmp.CreateCompatibleBitmap(pDC, rClient.Width(), rClient.Height());
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = dcMem.SelectObject(&bmp);
	
	dcMem.FillSolidRect(rClient, GetParentBkgndColor());
	
	UINT nStyle = GetStyle();
	int nCheck = GetButton()->GetCheck();
	CRect rButton = GetCheckRect();
		
	if (nStyle & BS_LEFTTEXT)
		rText.right = rButton.left - 3;
	else
		rText.left = rButton.right + 3;
	
	// border
	dcMem.SelectStockObject(NULL_PEN);
	CBrush* pOld = dcMem.SelectObject(GetColorBrush(bDown ? COLOR_3DHILIGHT : COLOR_WINDOW));
	
	dcMem.RoundRect(rButton.left, rButton.top, rButton.right + 1, rButton.bottom + 1, 6, 6);
	dcMem.SelectObject(pOld);

	Draw3dEdge(&dcMem, rButton, 2, SKCS_CLIENTEDGE, GetState(rClient));
		
	// draw state
	if (nCheck)
	{
		dcMem.SetBkMode(TRANSPARENT);
		dcMem.SetTextColor(GetColor(nCheck == 1 ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT));
		
		CFont* pOld = dcMem.SelectObject(GetFont(SBFONT_MARLETT));
		dcMem.DrawText("b", rButton, DT_CENTER | DT_VCENTER);
		dcMem.SelectObject(pOld);
	}
		
	pDC->BitBlt(0, 0, rClient.right, rClient.bottom, &dcMem, 0, 0, SRCCOPY);
	
	// cleanup
	dcMem.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	dcMem.DeleteDC();
	
	// draw the text if there is any
	if (!strText.IsEmpty())
	{
		pDC->SelectStockObject(ANSI_VAR_FONT);
		pDC->SetBkMode(TRANSPARENT);

		rText.DeflateRect(1, 1);
		CalcTextRect(pDC, strText, rText, nTextAlign);

		COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
		COLORREF oldcol = pDC->SetTextColor(colorText);

		pDC->DrawText(strText, rText, nTextAlign | DT_END_ELLIPSIS);
		pDC->SetTextColor(oldcol);
		
		rText.InflateRect(1, 1);
	}
	else
		rText.DeflateRect(CORNER, CORNER);
	
	// Draw the focus
	if (bFocus)
		pDC->DrawFocusRect(rText);
	
	return TRUE;
}

void CSkinButtonCheck::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// update if the cursor has moved on or off
	if (!pOldCursor || !pNewCursor)
		InvalidateRect(GetHwnd(), GetCheckRect(), FALSE);
}

COLORREF CSkinButtonCheck::GetBkgndColor()
{
	return GetParentBkgndColor(); 
}

////

BOOL CSkinButtonRadio::OnPaint(CDC* pDC) // return FALSE to allow default painting
{
	CRect rClient, rText, rect;
	GetClientRect(rClient);
	rText = rect = rClient;
	
	UINT nState = GetButton()->GetState();

	BOOL bDown = (nState & 0x0004);
	BOOL bFocus = (nState & 0x0008);
	
	CString strText;
	GetCtrl()->GetWindowText(strText);
	UINT nTextAlign = GetTextAlignment();
	
	CBitmap bmp;
	
	GetClientRect(rClient);
	bmp.CreateCompatibleBitmap(pDC, rClient.Width(), rClient.Height());
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	CBitmap *pOldBitmap = dcMem.SelectObject(&bmp);
	
	dcMem.FillSolidRect(rClient, GetParentBkgndColor());
	
	UINT nStyle = GetStyle();
	int nCheck = GetButton()->GetCheck();
		
	CRect rButton = GetCheckRect();
	
	// border
	dcMem.SelectStockObject(NULL_PEN);
	CBrush* pOld = dcMem.SelectObject(GetColorBrush(bDown ? COLOR_3DHILIGHT : COLOR_WINDOW));
	
	dcMem.Ellipse(rButton.left, rButton.top, rButton.right + 1, rButton.bottom + 1);
	dcMem.SelectObject(pOld);

	Draw3dEdge(&dcMem, rButton, rButton.Height() / 2, SKCS_CLIENTEDGE, GetState(rClient));
	
	// draw state
	if (nCheck > 0)
	{
		dcMem.SetBkMode(TRANSPARENT);
		dcMem.SetTextColor(GetColor(nCheck == 1 ? COLOR_WINDOWTEXT : COLOR_3DFACE));
		
		CFont* pOld = dcMem.SelectObject(GetFont(SBFONT_MARLETT));
		dcMem.DrawText("i", rButton, DT_CENTER | DT_VCENTER);
		dcMem.SelectObject(pOld);
	}
	
	pDC->BitBlt(0, 0, rClient.right, rClient.bottom, &dcMem, 0, 0, SRCCOPY);

	// cleanup
	dcMem.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	dcMem.DeleteDC();

	// draw the text if there is any
	if (nStyle & BS_LEFTTEXT)
		rText.right = rButton.left - 4;
	else
		rText.left = rButton.right + 4;
	
	if (!strText.IsEmpty())
	{
		pDC->SelectStockObject(ANSI_VAR_FONT);
		pDC->SetBkMode(TRANSPARENT);
		
		rText.DeflateRect(1, 1);
		CalcTextRect(pDC, strText, rText, nTextAlign);

		COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
		COLORREF oldcol = pDC->SetTextColor(colorText);

		pDC->DrawText(strText, rText, nTextAlign | DT_END_ELLIPSIS);
		pDC->SetTextColor(oldcol);
		
		rText.InflateRect(1, 1);
	}
	else
		rText.DeflateRect(CORNER, CORNER);

	// Draw the focus circle on the inside of the button if it is non-stretched
	if (bFocus)
		pDC->DrawFocusRect(rText);

	return TRUE;
}

void CSkinButtonRadio::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// update if the cursor has moved on or off
	if (!pOldCursor || !pNewCursor)
		InvalidateRect(GetHwnd(), GetCheckRect(), FALSE);
}

COLORREF CSkinButtonRadio::GetBkgndColor()
{
	return GetParentBkgndColor(); 
}

//////////////////////////////////////////////////////////////////////////////////////////////////

COLORREF CSkinCombolbox::GetParentBkgndColor()
{
	HWND hParent = GetParent();
	ASSERT (hParent);
	
	CSkinCtrl* pSkin = GetSkinCtrl(hParent);
	
	if (pSkin && CWinClasses::IsClass(hParent, WC_COMBOBOX))
	{
		DWORD dwStyle = ::GetWindowLong(hParent, GWL_STYLE);
		
		if ((dwStyle & 0xf) == CBS_SIMPLE)
		{
			return pSkin->GetParentBkgndColor();
		}
	}
	
	// else
	return CSkinCtrl::GetParentBkgndColor();
}

void CSkinCombolbox::DrawScrollbars(CDC* pDC, CRect rect, int nBar)
{
	rect.InflateRect(EDGE, EDGE);

	if (!IsPopup())
	{
		rect.right -= 2;
	}
	
	CSkinListbox::DrawScrollbars(pDC, rect, nBar);
}

void CSkinCombolbox::OnNcCalcSize(LPRECT pClient)
{
	pClient->right -= 2;
}

void CSkinCombolbox::OnNcPaint(CDC* pDC)
{
	CRect rWindow;
	GetDrawRect(rWindow);
	
	rWindow.right--;
	NcPaintBorder(pDC, rWindow, GetParentBkgndColor(), GetBkgndColor(), EdgeStyle());
	rWindow.right++;

	DrawScrollbars(pDC, rWindow);
	
	rWindow.right--;
	rWindow.top--;
	Draw3dEdge(pDC, rWindow, CORNER, SKCS_CLIENTEDGE, GetState(rWindow));
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int CSkinHeader::HitTest(POINT ptClient)
{
	CRect rClient, rParent;
	GetClientRect(rClient);

	CHeaderCtrl* pHeader = GetHeader();
	CWnd* pParent = pHeader->GetParent();

	pParent->GetClientRect(rParent);
	pParent->MapWindowPoints(pHeader, rParent);

	rClient.right = min(rParent.right, rClient.right);
	rClient.left = max(rParent.left, rClient.left);

	if (!rClient.PtInRect(ptClient))
		return -1;

	// else
	HDHITTESTINFO hhti;
	hhti.pt = ptClient;

	return SendMessage(HDM_HITTEST, 0, (LPARAM)&hhti);
}

BOOL CSkinHeader::OnPaint(CDC* pDC)
{
	// we do all the drawing ourselves
	CHeaderCtrl* pHeader = GetHeader();
	CRect rClient;
	GetClientRect(rClient);

	CRect rParent;
	CWnd* pParent = pHeader->GetParent();

	pParent->GetClientRect(rParent);
	pParent->MapWindowPoints(pHeader, rParent);

	rClient.right = min(rParent.right + 2, rClient.right);
	rClient.left = max(rParent.left, rClient.left);

	BOOL bMouseDown = !m_bDragging && IsHot() && (GetAsyncKeyState(MK_LBUTTON) & 0x8000);
	BOOL bTextured = (GetControlBitmap(SKCB_HEADERLEFT) != NULL);

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rClient.Width(), rClient.Height());
	CBitmap* pOldBM = dcMem.SelectObject(&bmp);
	
	CRect rMem(rClient);
	rMem.OffsetRect(-rClient.TopLeft());
	dcMem.FillSolidRect(rMem, GetParentBkgndColor());
	rMem.right -= 2;

	int nCount = pHeader->GetItemCount();

	dcMem.SelectStockObject(ANSI_VAR_FONT);
	dcMem.SetTextColor(GetColor(COLOR_WINDOWTEXT));
	dcMem.SetBkMode(TRANSPARENT);

	CImageList* pIL = pHeader->GetImageList();

	CPoint ptCursor;
	GetCursorPos(&ptCursor);

	int nHotItem = HitTest(ptCursor);
	int nItem = nCount;

	while (nItem--)
	{
		CRect rItem;
		pHeader->GetItemRect(nItem, rItem);

		if (rItem.right <= rClient.left || rItem.left >= rClient.right)
			continue;

		rItem.OffsetRect(-rClient.TopLeft());

		// else
		CString sText;
		HDITEM hdi;
		hdi.mask = HDI_TEXT | HDI_IMAGE | HDI_FORMAT;
		hdi.pszText = sText.GetBuffer(100);
		hdi.cchTextMax = 99;
		
		VERIFY (pHeader->GetItem(nItem, &hdi));
		sText.ReleaseBuffer();
		
		BOOL bDown = (!m_bDragging && bMouseDown && (nItem == nHotItem));
		BOOL bHot = (!m_bDragging && !bMouseDown && (nItem == nHotItem));

		BOOL bLeftEnd = (rItem.left == rMem.left);
		BOOL bRightEnd = (rItem.right >= rMem.right - 2);

		int nState = !IsWindowEnabled() ? IM_DISABLED : (bDown ? IM_DOWN : bHot ? IM_HOT : IM_COLD);

		CRect rOrgItem(rItem); // save
		rItem.left = max(rItem.left, rMem.left);
		rItem.right = min(rItem.right, rMem.right);

		if (bTextured)
		{
			COLORREF crMask;
			CBitmap* pMid = GetControlBitmap(SKCB_HEADERMIDDLE, nState, &crMask);
			CBitmap* pLeft = !bLeftEnd ? pMid : GetControlBitmap(bLeftEnd ? SKCB_HEADERLEFTEND : SKCB_HEADERLEFT, nState, NULL, SKCB_HEADERLEFT);
			CBitmap* pRight = !bRightEnd ? pMid : GetControlBitmap(bRightEnd ? SKCB_HEADERRIGHTEND : SKCB_HEADERRIGHT, nState, NULL, SKCB_HEADERRIGHT);

			DrawPushButton(&dcMem, rItem, pLeft, pMid, pRight, -1, crMask);

			// draw a divider
			if (!bRightEnd)
				dcMem.FillSolidRect(rItem.right - 1, rItem.top, 1, rItem.Height(), GetColor(COLOR_3DSHADOW));
		}
		else
		{
			DrawPushButton(&dcMem, rItem, nState, CORNER, -1, !bLeftEnd, !bRightEnd);
		}

		rItem = rOrgItem; // restore
		rItem.DeflateRect(4, 0);

		if (!sText.IsEmpty())
		{
			CalcTextRect(&dcMem, sText, rItem, DT_LEFT | DT_VCENTER);

			if (bDown)
				rItem.OffsetRect(1, 1);

			COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
			dcMem.SetTextColor(colorText);

			dcMem.DrawText(sText, rItem, DT_LEFT | DT_TOP | DT_END_ELLIPSIS);
		}
	}
	
	pDC->BitBlt(rClient.left, 0, rClient.right, rClient.bottom, &dcMem, 0, 0, SRCCOPY);
	
	dcMem.SelectObject(pOldBM);
	dcMem.DeleteDC();
	bmp.DeleteObject();
	
	return TRUE;
}

void CSkinHeader::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	if (m_bDragging)
		return;

	CHeaderCtrl* pHeader = GetHeader();
	int nOldItem = -1;
	int nNewItem = -1;

	if (pOldCursor && pNewCursor)
	{
		nOldItem = HitTest(*pOldCursor);
		nNewItem = HitTest(*pNewCursor);
	}
	else if (pOldCursor)
	{
		nOldItem = HitTest(*pOldCursor);
	}
	else if (pNewCursor)
	{
		nNewItem = HitTest(*pNewCursor);
	}
	
	if (nOldItem != -1 || nNewItem != -1)
		Invalidate(FALSE);
}

LRESULT CSkinHeader::OnNotifyReflect(NMHDR* pNMHDR, LRESULT lrParent)
{
	switch (pNMHDR->code)
	{
	case HDN_TRACK:
	case HDN_ITEMCHANGED:
	case 0xfffffeb8://HDN_TRACK:
	case 0xfffffebf://HDN_ITEMCHANGED:
		{
			CWnd* pHeader = GetHeader();
			pHeader->Invalidate();
			break;
		}

	case HDN_BEGINTRACK:
	case HDN_BEGINDRAG:
	case 0xfffffeba://HDN_BEGINTRACK:
		if (!lrParent)
			m_bDragging = TRUE;
		break;

	case HDN_ENDTRACK:
	case HDN_ENDDRAG:
	case 0xfffffeb9://HDN_ENDTRACK:
		m_bDragging = FALSE;
		break;
	}
	
	return CSkinCtrl::OnNotifyReflect(pNMHDR, lrParent);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinMonthcal::AttachWindow(CWnd* pCtrl)
{
	// must change this prior to calling base class
	if (!(pCtrl->GetExStyle() & WS_EX_CLIENTEDGE))
	{
		if (IsPopup())
			m_dwBaseStyle &= ~SKCS_EDGEMASK;
		else
			m_dwBaseStyle = 0;
	}

	// enlarge to take account of border
	if (CSkinCtrl::AttachWindow(pCtrl))
	{
		if (!IsPopup() && EdgeStyle() != SKCS_NOEDGE)
		{
			CRect rCtrl;
			pCtrl->GetWindowRect(rCtrl);
			pCtrl->ScreenToClient(rCtrl);
			pCtrl->MapWindowPoints(pCtrl->GetParent(), rCtrl);

			rCtrl.right += 4;
			rCtrl.bottom += 4;
			pCtrl->MoveWindow(rCtrl);
		}		
		return TRUE;
	}
	
	return FALSE;
}

void CSkinMonthcal::OnNcCalcSize(LPRECT pClient)
{
	if (EdgeStyle() != SKCS_NOEDGE)
		::InflateRect(pClient, -EDGE - 2, -EDGE - 2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void CSkinTabcontrol::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	CSkinCtrl::OnUpdateHotspots(pOldCursor, pNewCursor, uOldHitTest, uNewHitTest);

	// redraw the border and selected item if we've moved on or off
	if ((pOldCursor || pNewCursor) && !(pOldCursor && pNewCursor))
	{
		Invalidate(FALSE);
	}
}

BOOL CSkinTabcontrol::OnEraseBkgnd(CDC* pDC) 
{
	CRect rClient, rTab, rTotalTab, rBkgnd, rEdge;
	COLORREF crBack;
	int nTab, nTabHeight = 0;
	
	// calc total tab width
	GetClientRect(rClient);
	nTab = GetTab()->GetItemCount();
	rTotalTab.SetRectEmpty();
	
	while (nTab--)
	{
		GetTab()->GetItemRect(nTab, rTab);
		rTotalTab.UnionRect(rTab, rTotalTab);
	}
	
	nTabHeight = rTotalTab.Height();
	
	// add a bit
	rTotalTab.InflateRect(2, 3);
	rEdge = rTotalTab;
	
	// then if background color is set, paint the visible background
	// area of the tabs in the bkgnd color
	// note: the mfc code for drawing the tabs makes all sorts of assumptions
	// about the background color of the tab control being the same as the page
	// color - in some places the background color shows thru' the pages!!
	// so we must only paint the background color where we need to, which is that
	// portion of the tab area not excluded by the tabs themselves
	crBack = GetParentBkgndColor();
	
	// full width of tab ctrl above top of tabs
	rBkgnd = rClient;
	rBkgnd.bottom = rTotalTab.top + 3;
	pDC->FillSolidRect(rBkgnd, crBack);
	
	// width of tab ctrl visible bkgnd including bottom pixel of tabs to left of tabs
	rBkgnd = rClient;
	rBkgnd.right = 2;
	rBkgnd.bottom = rBkgnd.top + (nTabHeight + 2);
	pDC->FillSolidRect(rBkgnd, crBack);
	
	// to right of tabs
	rBkgnd = rClient;
	rBkgnd.left += rTotalTab.Width() - 2;
	rBkgnd.bottom = rBkgnd.top + (nTabHeight + 2);
	pDC->FillSolidRect(rBkgnd, crBack);
	
	OnPaint(pDC);
	
	return TRUE;
}

void CSkinTabcontrol::OnNcPaint(CDC* pDC) 
{
	CRect rWindow, rClient;
	GetDrawRect(rWindow, rClient);

	BOOL bHot = IsHot(rWindow);

	// draw the rest of the border
	CRect rPage;
	GetClientRect(rPage);
	GetTab()->AdjustRect(FALSE, rPage);
	rPage.top -= 2;
	rClient.top += rPage.top;
	
	COLORREF crBkgnd = GetParentBkgndColor();
	
	pDC->FillSolidRect(rWindow.left, rWindow.top, EDGE, rClient.top - rWindow.top, crBkgnd);
	pDC->FillSolidRect(rWindow.left, rWindow.top, rWindow.right - rWindow.left, EDGE, crBkgnd);
	pDC->FillSolidRect(rWindow.right - EDGE, rWindow.top, EDGE, rClient.top - rWindow.top, crBkgnd);
	
	rWindow.top = rClient.top;

	Draw3dEdge(pDC, rWindow, 4, SKCS_BTNEDGE, bHot ? IM_HOT : IM_COLD);

	// rub out the base line of the selected tab if enough of the tab is visible
	int nSel = GetTab()->GetCurSel();

	if (nSel != -1)
	{
		CRect rTab;
		GetTab()->GetItemRect(nSel, rTab);

		if (rTab.right > 4)
		{
			ClientToWindow(rTab);
			pDC->FillSolidRect(rTab.left + 2, rWindow.top, rTab.Width() - 2, 2, GetBkgndColor());
		}
	}
}

BOOL CSkinTabcontrol::IsHot(LPRECT pRect)
{
	if (CSkinCtrl::IsHot(pRect))
		return TRUE;

	// else check if spin button has the capture
	CWnd* pSpin = GetChildWnd(WC_SPIN);
		
	return (pSpin && (pSpin->GetSafeHwnd() == GetCapture()));
}

BOOL CSkinTabcontrol::OnPaint(CDC* pDC) 
{
	// prepare dc
	pDC->SelectObject(GetTab()->GetFont());

	// clip out the spinctrl and bit more
	CWnd* pSpin = GetChildWnd(WC_SPIN);

	if (pSpin && pSpin->IsWindowVisible())
	{
		CRect rSpin;
		pSpin->GetWindowRect(rSpin);
		GetCtrl()->ScreenToClient(rSpin);
		rSpin.InflateRect(2, 2);

		pDC->ExcludeClipRect(rSpin);
	}
	
	// paint the tabs first and then the borders
	int nTab = GetTab()->GetItemCount();
	int nSel = GetTab()->GetCurSel();
	
	if (!nTab) // no pages added
		return TRUE;
	
	CRect rPage, rClient;
	GetClientRect(rClient);
	GetTab()->AdjustRect(FALSE, rClient);
	rClient.top -= 2;
	
	while (nTab--)
	{
		if (nTab != nSel)
		{
			VERIFY(GetTab()->GetItemRect(nTab, rPage));
			
			// if there is not enough of the tab showing then don't paint it
			if (rPage.right > 3)
			{
				DrawItem(pDC, nTab, rPage);
				DrawItemBorder(pDC, nTab, rPage, nSel);
			}
		}
	}
	
	// now selected tab
	VERIFY(GetTab()->GetItemRect(nSel, rPage));
	
	if (rPage.right > 3)
	{
		rPage.bottom++;
		rPage.top -= 2;
		
		DrawItem(pDC, nSel, rPage, TRUE);
		DrawItemBorder(pDC, nSel, rPage, nSel);
	}

	SendMessage(WM_NCPAINT); // to redraw the main border
	
	return TRUE;
}

void CSkinTabcontrol::DrawItem(CDC* pDC, int nItem, LPRECT pRect, BOOL bSelected)
{
	TC_ITEM     tci;
	CImageList* pilTabs = GetTab()->GetImageList();
	const int PADDING = 2;
	
	CRect rItem(pRect);

	// tab
	pDC->FillSolidRect(rItem, GetBkgndColor());
	
	// text & icon
	rItem.left += PADDING;
	rItem.top += PADDING + (bSelected ? 1 : 0);
	
	pDC->SetBkMode(TRANSPARENT);
	
	CString sTemp;
	tci.mask        = TCIF_TEXT | TCIF_IMAGE;
	tci.pszText     = sTemp.GetBuffer(100);
	tci.cchTextMax  = 99;
	GetTab()->GetItem(nItem, &tci);
	sTemp.ReleaseBuffer();
	
	// icon
	if (pilTabs)
	{
		pilTabs->Draw(pDC, tci.iImage, CPoint(rItem.left, rItem.top), ILD_TRANSPARENT);
		rItem.left += 16 + PADDING;
	}
	
	// text
	rItem.right -= PADDING;
	
	COLORREF colorText = GetColor(IsWindowEnabled() ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
	pDC->SetTextColor(colorText);

	pDC->DrawText(sTemp, rItem, DT_NOPREFIX | DT_CENTER | DT_END_ELLIPSIS);
}

void CSkinTabcontrol::DrawItemBorder(CDC* pDC, int nItem, LPRECT pRect, int nSelItem)
{
	COLORREF crHighlight = GetColor(COLOR_3DHILIGHT);
	COLORREF crShadow = GetColor(COLOR_3DSHADOW);
	
	if (nItem == nSelItem)
	{
		Draw3dEdge(pDC, pRect, 4, SKCS_BTNEDGE, IsHot() ? IM_HOT : IM_COLD, ISKCR_CLIPBOTTOM);
	}
	else // draw simple dividers
	{
		// only draw the left divider if its the first item or the previous item is not visible
		if (nItem == 0 || pRect->left < 4)
			pDC->FillSolidRect(pRect->left, pRect->top, 1, pRect->bottom - pRect->top - 1, crShadow);

		// don't draw the right divider if we preceed the selected item
		if (nItem != nSelItem - 1)
			pDC->FillSolidRect(pRect->right - 1, pRect->top, 1, pRect->bottom - pRect->top - 1, crShadow);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CSkinRebar::OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage)
{
	switch (dwStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			CDC* pDC = CDC::FromHandle(pNMCD->hdc);
		}
	}
	// default
	return CDRF_DODEFAULT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinTooltip::AttachWindow(CWnd* pCtrl)
{
	// don't ever hook these windows just setup the colors and return
	pCtrl->SendMessage(TTM_SETTIPBKCOLOR, (WPARAM)GetColor(COLOR_INFOBK), 0);
	pCtrl->SendMessage(TTM_SETTIPTEXTCOLOR, (WPARAM)GetColor(COLOR_INFOTEXT), 0);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void CSkinTrackbar::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// only update if the cursor has moved on or off the thumb
	CRect rThumb;
	GetSlider()->GetThumbRect(rThumb);

	BOOL bWasOn = FALSE, bOn = FALSE;
	
	if (pOldCursor && pNewCursor)
	{
		bWasOn = rThumb.PtInRect(*pOldCursor);
		bOn = rThumb.PtInRect(*pNewCursor);
	}
	else if (pOldCursor)
		bWasOn = rThumb.PtInRect(*pOldCursor);

	else if (pNewCursor)
		bOn = rThumb.PtInRect(*pNewCursor);
	
	if (bWasOn != bOn)
		Refresh();
}
/*
BOOL CSkinTrackbar::OnPaint(CDC* pDC)
{
	CRect rThumb, rChannel, rClient;

	GetSlider()->GetClientRect(rClient);
	GetSlider()->GetThumbRect(rThumb);
	GetSlider()->GetChannelRect(rChannel);

	BOOL bHorz = !(GetStyle() & TBS_VERT);

	// GetChannelRect bug
	if (!bHorz)
	{
		CRect rTemp(rChannel);

		rChannel.left = rTemp.top;
		rChannel.right = rTemp.bottom;
		rChannel.top = rTemp.left;
		rChannel.bottom = rTemp.right;
	}

	// clipping
	rThumb.IntersectRect(rThumb, rClient);

	int nState = m_bDragging ? IM_DOWN : (IsHot(rThumb) ? IM_HOT : IM_COLD);

	// fill bkgnd and draw channel
	pDC->FillSolidRect(rClient, GetParentBkgndColor());
	pDC->Draw3dRect(rChannel, GetColor(COLOR_3DSHADOW), GetColor(COLOR_3DHILIGHT));
				
	COLORREF crMask;
	CBitmap* pThumb = GetControlBitmap(bHorz ? SKCB_SLIDERTHUMBHORZ : SKCB_SLIDERTHUMBVERT, nState, &crMask);
				
	if (pThumb)
	{
		BITMAP bm;
		pThumb->GetBitmap(&bm);
					
		CDC dcMem;
		dcMem.CreateCompatibleDC(pDC);
		CBitmap *pOldBitmap = dcMem.SelectObject(pThumb);
					
		CSkinBase::StretchBlt(pDC, rThumb.left, rThumb.top, rThumb.Width(), rThumb.Height(),
							&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);
	
		dcMem.SelectObject(pOldBitmap);
	}
	else
	{
		COLORREF color = GetColor((nState == IM_DOWN || nState == IM_HOT) ? COLOR_3DHILIGHT : COLOR_3DFACE);
					
		pDC->FillSolidRect(rThumb, color);
		NcPaintBorder(pDC, rThumb, GetParentBkgndColor(), color, SKCS_BTNEDGE, FALSE);
	}

	return TRUE;
}
*/

LRESULT CSkinTrackbar::OnCustomDraw(NMCUSTOMDRAW* pNMCD, DWORD dwStage)
{
	switch (dwStage)
	{
	case CDDS_ITEMPREPAINT:
		{
			if (pNMCD->dwItemSpec == TBCD_CHANNEL)
			{
				CDC* pDC = CDC::FromHandle(pNMCD->hdc);
				CRect rClient;
				GetClientRect(rClient);
				
				pDC->Draw3dRect(&pNMCD->rc, GetColor(COLOR_3DSHADOW), GetColor(COLOR_3DHILIGHT));
				
				return CDRF_SKIPDEFAULT;
			}
			else if (pNMCD->dwItemSpec == TBCD_THUMB)
			{
				CDC* pDC = CDC::FromHandle(pNMCD->hdc);
				CRect rThumb(pNMCD->rc);

				// clip thumb to client rect
				CRect rClient;
				GetClientRect(rClient);
				rThumb.IntersectRect(rThumb, rClient);

				int nState = m_bDragging ? IM_HOT : (IsHot(rThumb) ? IM_HOT : IM_COLD);
				BOOL bHorz = (GetStyle() & TBS_HORZ);

				COLORREF crMask;
				CBitmap* pThumb = GetControlBitmap(bHorz ? SKCB_SLIDERTHUMBHORZ : SKCB_SLIDERTHUMBVERT, nState, &crMask);

				if (pThumb)
				{
					BITMAP bm;
					pThumb->GetBitmap(&bm);

					CDC dcMem;
					dcMem.CreateCompatibleDC(pDC);
					CBitmap *pOldBitmap = dcMem.SelectObject(pThumb);

					CSkinBase::StretchBlt(pDC, rThumb.left, rThumb.top, rThumb.Width(), rThumb.Height(),
											&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);

					dcMem.SelectObject(pOldBitmap);
				}
				else
				{
					COLORREF color = GetColor((nState == IM_DOWN || nState == IM_HOT) ? COLOR_3DHILIGHT : COLOR_3DFACE);

//					pDC->FillSolidRect(rThumb, color);
					DrawPushButton(pDC, rThumb, nState, min(rThumb.Height(), rThumb.Width()) / 2, GetParentBkgndColor());
				}

				return CDRF_SKIPDEFAULT;
			}
		}
	}
	// default
	return CDRF_DODEFAULT;
}

void CSkinTrackbar::OnScroll(UINT nSBCode, UINT nPos, BOOL bHorz)
{
	switch (nSBCode)
	{
	case TB_THUMBTRACK:
		m_bDragging = TRUE;
		break;

	default:
		m_bDragging = FALSE;
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////

LRESULT CSkinSHDLLDefView::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	UINT uRes = 0;
	LRESULT lr = 0;

	switch (msg) 
	{
	case WM_NOTIFY:
		{
			NMHDR* pNMHDR = (NMHDR*)lp;
			
			if (pNMHDR->code == NM_CUSTOMDRAW)
				return CSkinCtrl::OnMsg(msg, wp, lp);
			else
				return Default();
		}
		break;
	}

	// We don't handle it: pass along
	return CSkinCtrl::OnMsg(msg, wp, lp);
}

//////////////////////////////////////////////////////////////////////////////////////////

BOOL CSkinOther::OnEraseBkgnd(CDC* pDC)
{
	return CSkinCtrl::OnEraseBkgnd(pDC);
}

BOOL CSkinOther::AttachWindow(CWnd* pCtrl)
{
	// make an educated guess as to the edge style
	if (pCtrl->GetExStyle() & WS_EX_CLIENTEDGE)
		m_dwBaseStyle |= SKCS_CLIENTEDGE;

	m_dwBaseStyle |= SKCS_NCPAINT;

	return CSkinCtrl::AttachWindow(pCtrl);
}

void CSkinOther::OnNcPaint(CDC* pDC)
{
	CSkinCtrl::OnNcPaint(pDC);
}
