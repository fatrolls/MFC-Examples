// HTMLListCtrl.cpp : implementation file
//
//	Written by Manoj Subberwal (Monty) email : xMonty@gmail.com
//	copyright 2005-2006

// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage caused through use.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HTMLListCtrl.h"
#include "memdc.h"
#include <shlwapi.h>
#include "NewControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTMLListCtrl

CHTMLListCtrl::CHTMLListCtrl()
{
	m_nTotalItems = 0;
	m_nListHeight = 0;
	m_nWndHeight = 0;
	m_nWndWidth = 0;

	m_nSelectedItem = NONE_SELECTED;
	//Create a light pen for border
	m_penLight.CreatePen(PS_SOLID,1,RGB(200,200,200));

	//Create the Font
	LOGFONT lf = {0};
	lf.lfHeight = -11;
	lf.lfWeight = FW_NORMAL;
	
	_tcscpy(lf.lfFaceName,"Tahoma");
	m_font.CreateFontIndirect(&lf);

	m_clrBkSelectedItem = RGB(127,202,254);

	m_dwExtendedStyles = 0;

	m_bHasFocus = FALSE;

	m_ImageList.Create(16,16,ILC_COLOR24|ILC_MASK,4,4);

	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP_CHECKMARK);
	m_ImageList.Add(&bm,RGB(255,0,255));

	m_pImageList = NULL;
}

CHTMLListCtrl::~CHTMLListCtrl()
{
	DeleteAllItems();
}


BEGIN_MESSAGE_MAP(CHTMLListCtrl, CWnd)
	//{{AFX_MSG_MAP(CHTMLListCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHTMLListCtrl message handlers

BOOL CHTMLListCtrl::Create(CWnd *pParent, CRect rc, UINT nID,DWORD dwStyle)
{
	//Get a New Class Name
	CString sWindowClassName = ::AfxRegisterWndClass(CS_DBLCLKS); 

	//Try to create it with default styles
	if(!CWnd::Create(sWindowClassName,"HTMLListCtrl",dwStyle,rc,pParent,nID))
	{
		return FALSE;
	}

	
	m_nControlID = nID;

	m_nWndWidth = rc.Width();
	m_nWndHeight = rc.Height();

	m_nListHeight = 0;

	//Set the scrolling info
	SCROLLINFO scrlinfo;
	scrlinfo.cbSize = sizeof(scrlinfo);

	scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
	scrlinfo.nMax = 0;
	scrlinfo.nMin = 0;
	scrlinfo.nPage = 0;
	scrlinfo.nPos = 0;
	SetScrollInfo(SB_VERT,&scrlinfo);

	
	return TRUE;
}

int CHTMLListCtrl::InsertItem(CString sText, UINT uiImage, int nStyle, int nHeight)
{
	//Allocate memory
	HTMLLIST_ITEM *pItem = new HTMLLIST_ITEM;
	pItem->sItemText = sText;
	pItem->nStyle = nStyle;
	pItem->nItemNo = m_nTotalItems;
	pItem->uiImage = uiImage;
	
	if(nHeight == AUTO)
	{
		//Calculate items height
		pItem->nHeight = CalculateItemHeight(sText,nStyle,uiImage,m_nWndWidth);
		pItem->bHeightSpecified = FALSE;
	}
	else
	{
		pItem->nHeight = nHeight;
		pItem->bHeightSpecified = TRUE;
	}

	m_listItems.AddTail(pItem);
	
	m_nTotalItems ++;

	m_nListHeight += pItem->nHeight;

	SCROLLINFO scrlinfo;
	scrlinfo.cbSize = sizeof(scrlinfo);

	scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
	scrlinfo.nMax = m_nListHeight;
	scrlinfo.nMin = 0;
	scrlinfo.nPage = m_nWndHeight;
	scrlinfo.nPos = 0;
	SetScrollInfo(SB_VERT,&scrlinfo);

	m_mapItems.SetAt(pItem->nItemNo,pItem);

	return (m_nTotalItems - 1);
}

int CHTMLListCtrl::CalculateItemHeight(CString sText, int nStyle, UINT uiImage,int nItemWidth)
{
	int nImageWidth = 0;
	int nPadding = ITEM_PADDING_LEFT; //default space 

	if(m_dwExtendedStyles & HTMLLIST_STYLE_IMAGES)
	{
		if(m_pImageList)
		{
			if(m_pImageList->GetImageCount())
			{
				IMAGEINFO Info = {0};
				if(m_pImageList->GetImageInfo(uiImage,&Info))
				{
					nImageWidth = Info.rcImage.right - Info.rcImage.left;
					nImageWidth += (ITEM_IMAGE_PADDING_LEFT + ITEM_IMAGE_PADDING_RIGHT);
				}
			}
		}
	}

	if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
	{
		nPadding += ITEM_PADDING_CHECKBOX_LEFT + ITEM_CHECKBOX_WIDTH ;
	}
	
	if(nStyle == NORMAL_TEXT)
	{
		CDC *pDC = GetDC();
	
		CFont *pOldFont = pDC->SelectObject(&m_font);

		CRect rc;
		rc.SetRectEmpty();

		rc.left = 0;

		rc.right = nItemWidth - nPadding;

		rc.right -= nImageWidth;

		pDC->DrawText(sText,&rc,DT_WORDBREAK|DT_CALCRECT|DT_EXTERNALLEADING );

		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
		return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
	}
	else if(nStyle == HTML_TEXT)
	{
		CDC *pDC = GetDC();
		
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		CFont *pOldFont = memDC.SelectObject(&m_font);

		int nWidth = 0;

		nWidth = nItemWidth - nPadding;
		nWidth -= nImageWidth;

		CRect rc(0,0,nWidth,m_nWndHeight);
		
		int nHeight = DrawHTML(memDC.GetSafeHdc(),sText,sText.GetLength(),&rc,DT_LEFT|DT_CALCRECT|DT_WORDBREAK|DT_EXTERNALLEADING);

		memDC.SelectObject(pOldFont);
		ReleaseDC(pDC);
		return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
	}
	else if(nStyle == SINGLE_LINE_TEXT)
	{
		CDC *pDC = GetDC();
	
		CFont *pOldFont = pDC->SelectObject(&m_font);

		CRect rc;
		rc.SetRectEmpty();

		rc.left = 0;

		rc.right = nItemWidth - nPadding;
		rc.right -= nImageWidth;

		pDC->DrawText(sText,&rc,DT_VCENTER|DT_CALCRECT|DT_SINGLELINE);

		pDC->SelectObject(pOldFont);
		ReleaseDC(pDC);
		return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
	}
	return 0;
}

void CHTMLListCtrl::DeleteAllItems()
{
	m_nListHeight = 0;
	m_nTotalItems = 0;

	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		delete pItem;
	}
	m_listItems.RemoveAll();
	m_mapItems.RemoveAll();
}

LPARAM CHTMLListCtrl::GetItemData(int nPos)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
		return pItem->lItemData;
	else
		return NULL;
}

void CHTMLListCtrl::SetItemData(int nPos, LPARAM lItemData)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		pItem->lItemData = lItemData;
	}
}

void CHTMLListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//CDC *pDC = &dc;
	CMemDC pDC(&dc);

	CFont *pOldFont = pDC->SelectObject(&m_font);

	CRect rcWnd;
	GetClientRect(&rcWnd);

	CRect rcItem = rcWnd;
	rcItem.bottom = 0;
	
	int nScrollPos = GetScrollPos(SB_VERT);

	rcItem.OffsetRect(0,-nScrollPos);

	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);

		//Create the bounding rect for item
		rcItem.bottom = rcItem.top + pItem->nHeight;
		
		if(i == m_nSelectedItem)
		{
			//Call the virtual function for drawing the item
			DrawItem(pDC,rcItem,pItem,TRUE);
		}
		else
		{
			DrawItem(pDC,rcItem,pItem,FALSE);
		}

		pItem->rcItem = rcItem;
		//Move rcItem to next item
		rcItem.OffsetRect(0,pItem->nHeight);
	}

	//Release GDI stuff
	pDC->SelectObject(pOldFont);
}

BOOL CHTMLListCtrl::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
}

void CHTMLListCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();

	NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

	pNMHDR->hdr.code = HTMLLIST_LBUTTONDOWN;
	pNMHDR->hdr.hwndFrom = GetSafeHwnd();
	pNMHDR->hdr.idFrom = m_nControlID;

	pNMHDR->lItemData = 0;
	pNMHDR->nItemNo = -1;
	pNMHDR->sItemText = "";
	pNMHDR->bChecked = 0;
	//Send LButton down event first
	GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);

	delete pNMHDR;


	BOOL bItemSelected = FALSE;
	m_nSelectedItem = NONE_SELECTED;

	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		if(pItem->rcItem.PtInRect(point))
		{
			if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
			{
				//see if we clicked in the box
				CPoint pt = pItem->rcItem.TopLeft();
				pt.x += 3;
				pt.y += pItem->rcItem.Height() / 2 - 8;
				

				CRect rcBox(pt,CPoint(pt.x + 15,pt.y + 15));
				
				if(rcBox.PtInRect(point))
				{
					if(pItem->bChecked)
					{
						pItem->bChecked = FALSE;
					}
					else
					{
						pItem->bChecked = TRUE;
					}
					NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

					pNMHDR->hdr.code = HTMLLIST_ITEMCHECKED;
					pNMHDR->hdr.hwndFrom = GetSafeHwnd();
					pNMHDR->hdr.idFrom = m_nControlID;

					pNMHDR->lItemData = pItem->lItemData;
					pNMHDR->nItemNo = pItem->nItemNo;
					pNMHDR->sItemText = pItem->sItemText;
					pNMHDR->bChecked = pItem->bChecked;

					//Send check changed Event
					GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);
					delete pNMHDR;
				}
			}
			//Send WM_NOTIFY msg to parent
			NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

			pNMHDR->hdr.code = HTMLLIST_SELECTIONCHANGED;
			pNMHDR->hdr.hwndFrom = GetSafeHwnd();
			pNMHDR->hdr.idFrom = m_nControlID;

			pNMHDR->lItemData = pItem->lItemData;
			pNMHDR->nItemNo = pItem->nItemNo;
			pNMHDR->sItemText = pItem->sItemText;
			pNMHDR->bChecked = pItem->bChecked;

			//Send Selection changed Event
			GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);

			delete pNMHDR;

			m_nSelectedItem = i;
			Invalidate(FALSE);
			bItemSelected = TRUE;
			break;
		}
	}
	if(!bItemSelected)
	{
		NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

		pNMHDR->hdr.code = HTMLLIST_SELECTIONCHANGED;
		pNMHDR->hdr.hwndFrom = GetSafeHwnd();
		pNMHDR->hdr.idFrom = m_nControlID;

		pNMHDR->lItemData = 0;
		pNMHDR->nItemNo = NONE_SELECTED;
		pNMHDR->sItemText = "";
		
		GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);

		delete pNMHDR;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CHTMLListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	//nPos is not valid in case of THUMB type msgs see below url
	//http://support.microsoft.com/kb/q152252/

	int nScrollPos = GetScrollPos(SB_VERT);
	int nLimit = GetScrollLimit(SB_VERT);

	int nScroll = nLimit;

	int SCROLL_AMT_Y = 50;

	switch(nSBCode) {
		case SB_LINEUP:      // Scroll up.      
		case SB_PAGEUP:
			if(nScrollPos <= 0)
			{
				return;
			}
			nScroll = min(nScrollPos,SCROLL_AMT_Y);
			SetScrollPos(SB_VERT,nScrollPos - nScroll);
			break;   
		case SB_LINEDOWN:   // Scroll down.
		case SB_PAGEDOWN:
			if(nScrollPos >= nLimit)
			{
				return;
			}
			nScroll = min(nScroll-nScrollPos,SCROLL_AMT_Y);
			SetScrollPos(SB_VERT,nScrollPos + nScroll);
		    break;
		case SB_THUMBPOSITION:
			{
				HWND hWndScroll;
				if ( pScrollBar == NULL )
					hWndScroll = m_hWnd;
				else
					hWndScroll = pScrollBar->m_hWnd;
				
				SCROLLINFO info;
				info.cbSize = sizeof(SCROLLINFO);
				info.fMask = SIF_TRACKPOS;
				::GetScrollInfo(hWndScroll, SB_VERT, &info);
				
				nPos = info.nTrackPos;

				int nScr = nScrollPos - nPos;
				
				SetScrollPos(SB_VERT,nPos);
			}
			break;
		case SB_THUMBTRACK:
			{
				HWND hWndScroll;
				if ( pScrollBar == NULL )
					hWndScroll = m_hWnd;
				else
					hWndScroll = pScrollBar->m_hWnd;
				
				SCROLLINFO info;
				info.cbSize = sizeof(SCROLLINFO);
				info.fMask = SIF_TRACKPOS;
				::GetScrollInfo(hWndScroll, SB_VERT, &info);
				
				nPos = info.nTrackPos;

				int nScr = nScrollPos - nPos;
				
				SetScrollPos(SB_VERT,nPos,FALSE);
			}
			break;
	}	
	
	Invalidate();
	UpdateWindow();	
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CHTMLListCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	CRect rc;
	GetClientRect(&rc);

	m_nWndHeight = rc.Height();
	m_nWndWidth = rc.Width();

	ReArrangeWholeLayout();
	
	SCROLLINFO scrlinfo;
	scrlinfo.cbSize = sizeof(scrlinfo);

	scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
	scrlinfo.nMax = m_nListHeight;
	scrlinfo.nMin = 0;
	scrlinfo.nPage = m_nWndHeight;
	scrlinfo.nPos = 0;
	SetScrollInfo(SB_VERT,&scrlinfo);
	Invalidate(FALSE);
}

CRect CHTMLListCtrl::GetItemRect(int nPos)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		return pItem->rcItem;
	}
	else
	{
		return NULL;
	}
}

BOOL CHTMLListCtrl::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
	int nVertScroll = GetScrollPos(SB_VERT);

	int maxpos = GetScrollLimit(SB_VERT);

	if(zDelta < 0)
	{
		int nNewPos = min(nVertScroll + 40 , maxpos);
		
		SetScrollPos(SB_VERT,nNewPos);

		UpdateWindow();
	}
	else
	{
		int nNewPos = max((nVertScroll - 40) , 0) ;
		
		SetScrollPos(SB_VERT, nNewPos);

		UpdateWindow();
	}
	Invalidate();
	return CWnd::OnMouseWheel(nFlags,zDelta,pt);
}

int CHTMLListCtrl::GetSelectedItem()
{
	return m_nSelectedItem;
}

CString CHTMLListCtrl::GetItemText(int nPos)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		return pItem->sItemText;
	}
	else
	{
		return "";
	}
}

void CHTMLListCtrl::SetExtendedStyle(DWORD dwExStyle)
{
	m_dwExtendedStyles = dwExStyle;

	ReArrangeWholeLayout();
	SCROLLINFO scrlinfo;
	scrlinfo.cbSize = sizeof(scrlinfo);

	scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
	scrlinfo.nMax = m_nListHeight;
	scrlinfo.nMin = 0;
	scrlinfo.nPage = m_nWndHeight;
	scrlinfo.nPos = 0;
	SetScrollInfo(SB_VERT,&scrlinfo);

	Invalidate(FALSE);
}

DWORD CHTMLListCtrl::GetExtendedStyle()
{
	return m_dwExtendedStyles;
}

void CHTMLListCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);
	m_bHasFocus = TRUE;
	if(m_nSelectedItem != NONE_SELECTED)
	{
		InvalidateRect(GetItemRect(m_nSelectedItem));
	}
}

void CHTMLListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CWnd::OnKillFocus(pNewWnd);
	m_bHasFocus = FALSE;
	if(m_nSelectedItem != NONE_SELECTED)
	{
		InvalidateRect(GetItemRect(m_nSelectedItem));
	}
}

UINT CHTMLListCtrl::OnGetDlgCode()
{
    return DLGC_WANTARROWS|DLGC_WANTCHARS;
}

void CHTMLListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == VK_UP)
	{
		if(m_nSelectedItem == NONE_SELECTED)
		{
			m_nSelectedItem = 0;
		}
		else
		{
			if(m_nSelectedItem > 0)
			{
				m_nSelectedItem --;
			}
		}
		EnsureVisible(m_nSelectedItem);
		Invalidate(FALSE);
		SendSelectionChangeNotification(m_nSelectedItem);
	}
	else if(nChar == VK_DOWN)
	{
		if(m_nSelectedItem == NONE_SELECTED)
		{
			m_nSelectedItem = m_nTotalItems - 1;
		}
		else
		{
			if(m_nSelectedItem < (m_nTotalItems - 1))
			{
				m_nSelectedItem ++;
			}
		}
		EnsureVisible(m_nSelectedItem);
		Invalidate(FALSE);
		SendSelectionChangeNotification(m_nSelectedItem);
	}
	else if(nChar == VK_SPACE)
	{
		if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
		{
			if(m_nSelectedItem != NONE_SELECTED)
			{
				if(GetItemCheck(m_nSelectedItem))
				{
					SetItemCheck(m_nSelectedItem,FALSE);
				}
				else
				{
					SetItemCheck(m_nSelectedItem);
				}
				SendCheckStateChangedNotification(m_nSelectedItem);
			}
		}
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CHTMLListCtrl::EnsureVisible(int nPos)
{
	int nScrollPos = GetScrollPos(SB_VERT);
	
	int nItemPos = 0;
	int nScrollAmount = 0;

	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		if(pItem->nItemNo == nPos)
		{
			if(nItemPos < nScrollPos)
			{
				//Item is above
				nScrollAmount = nScrollPos - nItemPos;
			}
			else if( (nItemPos + pItem->nHeight)> (nScrollPos + m_nWndHeight) )
			{
				//Item is below
				nScrollAmount = (nScrollPos + m_nWndHeight) - nItemPos - pItem->nHeight;
			}
			break;
		}
		nItemPos += pItem->nHeight;
	}

	if(nScrollAmount)
	{
		SetScrollPos(SB_VERT,nScrollPos - nScrollAmount);
		Invalidate(FALSE);
	}
}

void CHTMLListCtrl::SetItemCheck(int nPos,BOOL bCheck)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		pItem->bChecked = bCheck;
		InvalidateRect(pItem->rcItem,FALSE);
	}
}

BOOL CHTMLListCtrl::GetItemCheck(int nPos)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		return pItem->bChecked;
	}
	else
	{
		return FALSE;
	}
}

void CHTMLListCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

	pNMHDR->hdr.code = HTMLLIST_RBUTTONDOWN;
	pNMHDR->hdr.hwndFrom = GetSafeHwnd();
	pNMHDR->hdr.idFrom = m_nControlID;

	pNMHDR->lItemData = 0;
	pNMHDR->nItemNo = -1;
	pNMHDR->sItemText = "";
	pNMHDR->bChecked = 0;

	GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);

	delete pNMHDR;	
	CWnd::OnRButtonDown(nFlags, point);
}

void CHTMLListCtrl::SetItemText(int nPos, CString sItemText,BOOL bCalculateHeight)
{
	HTMLLIST_ITEM* pItem = GetInternalData(nPos);
	if(pItem)
	{
		pItem->sItemText = sItemText;
		if(bCalculateHeight)
		{
			pItem->bHeightSpecified = FALSE;
			ReArrangeWholeLayout();
			Invalidate(FALSE);
		}
		else
		{
			InvalidateRect(pItem->rcItem,FALSE);
		}
	}
}

BOOL CHTMLListCtrl::DeleteItem(int nPos)
{
	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		if(pItem->nItemNo == nPos)
		{
			//Is this the last item
			if(pos != NULL)
			{
				//pos is now pointing to the next row, so go back
				m_listItems.GetPrev(pos);
				m_listItems.RemoveAt(pos);
			}
			else
			{
				m_listItems.RemoveAt(m_listItems.GetTailPosition());
			}
			
			if(m_nSelectedItem == pItem->nItemNo)
			{
				m_nSelectedItem = NONE_SELECTED;
			}

			//Adjust scrollbar 
			m_nListHeight -= pItem->nHeight;
			SCROLLINFO scrlinfo;
			scrlinfo.cbSize = sizeof(scrlinfo);

			scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
			scrlinfo.nMax = m_nListHeight;
			scrlinfo.nMin = 0;
			scrlinfo.nPage = m_nWndHeight;
			scrlinfo.nPos = 0;
			SetScrollInfo(SB_VERT,&scrlinfo);	

			//delete pItem;
			m_nTotalItems --;

			ReArrangeItems();
			Invalidate(FALSE);
			return TRUE;
		}
	}
	return FALSE;
}

void CHTMLListCtrl::ReArrangeItems()
{
	m_mapItems.RemoveAll();
	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		pItem->nItemNo = i;
		SetInternalData(i,pItem);
	}
}

void CHTMLListCtrl::ReArrangeWholeLayout()
{
	m_nTotalItems = 0;
	m_nListHeight = 0;
	m_mapItems.RemoveAll();

	POSITION pos = m_listItems.GetHeadPosition();
	for(int i = 0;i < m_listItems.GetCount();i++)
	{
		HTMLLIST_ITEM *pItem = m_listItems.GetNext(pos);
		pItem->nItemNo = i;
		
		if(!pItem->bHeightSpecified)
		{
			//Calculate items height
			pItem->nHeight = CalculateItemHeight(pItem->sItemText,pItem->nStyle,pItem->uiImage,m_nWndWidth);
		}
		

		m_nTotalItems ++;

		m_nListHeight += pItem->nHeight;
		SetInternalData(i,pItem);
	}
}

UINT CHTMLListCtrl::GetImage(int nPos)
{
	HTMLLIST_ITEM *pItem = GetInternalData(nPos);
	if(pItem)
	{
		return pItem->uiImage;
	}
	return 0;
}

void CHTMLListCtrl::SetImage(int nPos, UINT uiImage)
{
	HTMLLIST_ITEM *pItem = GetInternalData(nPos);
	if(pItem)
	{
		pItem->uiImage = uiImage;
		InvalidateRect(pItem->rcItem,FALSE);
	}
}

void CHTMLListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{	
	NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

	pNMHDR->hdr.code = HTMLLIST_LBUTTONDBLCLICK;
	pNMHDR->hdr.hwndFrom = GetSafeHwnd();
	pNMHDR->hdr.idFrom = m_nControlID;

	pNMHDR->lItemData = 0;
	pNMHDR->nItemNo = -1;
	pNMHDR->sItemText = "";
	pNMHDR->bChecked = 0;

	GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);

	delete pNMHDR;	
	CWnd::OnLButtonDblClk(nFlags, point);
}

void CHTMLListCtrl::DrawItem(CDC *pDC, CRect rcItem, HTMLLIST_ITEM *pItem, BOOL bSelected)
{
	CRect rcClipBox;
	pDC->GetClipBox(&rcClipBox);

	if(!IsRectVisible(rcClipBox,rcItem))
	{
		return;
	}

	COLORREF clrText = RGB(0,0,0);
	COLORREF clrOld;
	CRect rcImage(0,0,0,0);
		
	if(bSelected)
	{
		//clrText = RGB(255,255,255);
		pDC->FillSolidRect(&rcItem,m_clrBkSelectedItem);
	}
	else
	{
		pDC->FillSolidRect(&rcItem,RGB(255,255,255));
	}
	if(m_dwExtendedStyles & HTMLLIST_STYLE_GRIDLINES)
	{
		pDC->DrawEdge(&rcItem,BDR_SUNKENINNER,BF_LEFT|BF_BOTTOM|BF_FLAT);
	}
	
	CPoint ptCheckBox = rcItem.TopLeft();

	if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
	{
		ptCheckBox.x += ITEM_PADDING_CHECKBOX_LEFT;
		ptCheckBox.y += rcItem.Height() / 2 - 8;
		
		m_ImageList.Draw(pDC,pItem->bChecked?1:0,ptCheckBox,ILD_TRANSPARENT);
		ptCheckBox.x += ITEM_CHECKBOX_WIDTH;
	}
	
	//Draw image if an imagelist is attached
	if(m_dwExtendedStyles & HTMLLIST_STYLE_IMAGES)
	{
		if(m_pImageList)
		{
			IMAGEINFO imgInfo = {0};
			m_pImageList->GetImageInfo(0,&imgInfo);
			rcImage = imgInfo.rcImage;
			
			CPoint pt = ptCheckBox;
			pt.x += ITEM_IMAGE_PADDING_LEFT;
			pt.y = rcItem.top;
			pt.y += rcItem.Height() / 2 - rcImage.Height()/2;
			
			m_pImageList->Draw(pDC,pItem->uiImage,pt,ILD_TRANSPARENT);			
		}
	}
	
	if(pItem->nStyle == NORMAL_TEXT)
	{
		clrOld = pDC->SetTextColor(clrText);
		
		CRect rc = rcItem;
		
		if(rcImage.Width())
		{
			//make space for the Image already drawn
			rc.DeflateRect(rcImage.Width() + ITEM_IMAGE_PADDING_LEFT + ITEM_IMAGE_PADDING_RIGHT,0,0,0);
		}
		
		if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
		{
			rc.left += ITEM_PADDING_LEFT + ITEM_CHECKBOX_WIDTH;
		}
		else
		{
			rc.left += ITEM_PADDING_LEFT;
		}
		
		if(!pItem->bHeightSpecified)
			rc.top += ITEM_PADDING_TOP;
		
		pDC->DrawText(pItem->sItemText,pItem->sItemText.GetLength(),&rc,
			DT_LEFT|DT_WORDBREAK);
	}
	else if(pItem->nStyle == HTML_TEXT)
	{
		//Draw HTML
		clrOld = pDC->SetTextColor(clrText);
		
		CRect rc = rcItem;
		if(rcImage.Width())
		{
			//make space for the Image already drawn
			rc.DeflateRect(rcImage.Width() + ITEM_IMAGE_PADDING_LEFT + ITEM_IMAGE_PADDING_RIGHT,0,0,0);
		}
		if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
		{
			rc.left += ITEM_PADDING_LEFT + ITEM_CHECKBOX_WIDTH;
		}
		else
		{
			rc.left += ITEM_PADDING_LEFT;
		}
		
		if(!pItem->bHeightSpecified)
			rc.top += ITEM_PADDING_TOP;
		
		DrawHTML(pDC->GetSafeHdc(),pItem->sItemText,pItem->sItemText.GetLength(),
			&rc,DT_LEFT|DT_WORDBREAK);
	}
	else if(pItem->nStyle == SINGLE_LINE_TEXT)
	{
		clrOld = pDC->SetTextColor(clrText);
		
		CRect rc = rcItem;
		if(rcImage.Width())
		{
			//make space for the Image already drawn
			rc.DeflateRect(rcImage.Width() + ITEM_IMAGE_PADDING_LEFT + ITEM_IMAGE_PADDING_RIGHT,0,0,0);
		}
		if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
		{
			rc.left += ITEM_PADDING_LEFT + ITEM_CHECKBOX_WIDTH;
		}
		else
		{
			rc.left += ITEM_PADDING_LEFT;
		}
		
		if(!pItem->bHeightSpecified)
			rc.top += ITEM_PADDING_TOP;
		
		//See if we can fit the text in one line
		char szBuffer[_MAX_PATH];
		memset(szBuffer,0,_MAX_PATH);
		
		_tcscpy(szBuffer,pItem->sItemText);
		
		if(PathCompactPath(pDC->GetSafeHdc(),szBuffer,rc.Width()))
		{
			pDC->DrawText(szBuffer,_tcslen(szBuffer),&rc,
				DT_LEFT|DT_SINGLELINE|DT_VCENTER);	
		}
		else
		{
			pDC->DrawText(pItem->sItemText,pItem->sItemText.GetLength(),&rc,
				DT_LEFT|DT_SINGLELINE|DT_VCENTER);
		}
	}
	
	pDC->SetTextColor(clrOld);
	
	//Draw the focus rect if focused
	if(m_bHasFocus && (bSelected))
	{
		pDC->DrawFocusRect(&rcItem);
	}
}

void CHTMLListCtrl::SendSelectionChangeNotification(int nPos)
{
	//Send WM_NOTIFY msg to parent
	HTMLLIST_ITEM *pItem = GetInternalData(nPos);
	if(pItem)
	{
		NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

		pNMHDR->hdr.code = HTMLLIST_SELECTIONCHANGED;
		pNMHDR->hdr.hwndFrom = GetSafeHwnd();
		pNMHDR->hdr.idFrom = m_nControlID;

		pNMHDR->lItemData = pItem->lItemData;
		pNMHDR->nItemNo = pItem->nItemNo;
		pNMHDR->sItemText = pItem->sItemText;
		pNMHDR->bChecked = pItem->bChecked;

		//Send Selection changed Event
		GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);
		delete pNMHDR;
		return;
	}
}

void CHTMLListCtrl::SendCheckStateChangedNotification(int nPos)
{
	//Send WM_NOTIFY msg to parent
	HTMLLIST_ITEM *pItem = GetInternalData(nPos);
	if(pItem)
	{
		NM_HTMLLISTCTRL *pNMHDR = new NM_HTMLLISTCTRL;

		pNMHDR->hdr.code = HTMLLIST_ITEMCHECKED;
		pNMHDR->hdr.hwndFrom = GetSafeHwnd();
		pNMHDR->hdr.idFrom = m_nControlID;

		pNMHDR->lItemData = pItem->lItemData;
		pNMHDR->nItemNo = pItem->nItemNo;
		pNMHDR->sItemText = pItem->sItemText;
		pNMHDR->bChecked = pItem->bChecked;

		//Send Selection changed Event
		GetParent()->SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)pNMHDR);
		delete pNMHDR;
		return;
	}
}

BOOL CHTMLListCtrl::IsRectVisible(CRect rcClipBox, CRect rcItem)
{
	if(rcClipBox.top > rcItem.bottom) 
	{
		//Item is above the clip box
		return FALSE;
	}
	else if(rcClipBox.bottom < rcItem.top)
	{
		return FALSE;
	}
	return TRUE;
}

HTMLLIST_ITEM * CHTMLListCtrl::GetInternalData(int nPos)
{
	HTMLLIST_ITEM *pData = NULL;
	m_mapItems.Lookup(nPos,pData);
	return pData;
}

void CHTMLListCtrl::SetInternalData(int nPos, HTMLLIST_ITEM *pData)
{
	m_mapItems.SetAt(nPos,pData);
}

void CHTMLListCtrl::OnDestroy() 
{
	CWnd::OnDestroy();
	if(m_font.m_hObject != NULL)
		m_font.DeleteObject();
}

BOOL CHTMLListCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	SetCursor(::LoadCursor(NULL, IDC_ARROW));
	return TRUE;//CWnd::OnSetCursor(pWnd, nHitTest, message);
}
