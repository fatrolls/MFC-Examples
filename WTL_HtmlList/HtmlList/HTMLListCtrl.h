/////////////////////////////////////////////////////////////////////////////
// HTMLViewerCtrl - A HTML Viewer control
//
//	Author:		Ernest Laurentin
//	E-mail:		elaurentin@netzero.net
//
//	This class encapsulates HTML List Control
//	Based on MFC version Written by Manoj Subberwal (Monty) email : xMonty@gmail.com
//	copyright 2005-2006
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is
//	not sold for profit without the authors written consent, and
//	providing that this notice and the authors name and all copyright
//	notices remains intact.
//
//	This file is provided "as is" with no expressed or implied warranty.
//	The author accepts no liability for any damage/loss of business that
//	this c++ class may cause.
//
//	Version history
//  03/26/2005: v1.00 : Initial Revision
/////////////////////////////////////////////////////////////////////////////
#ifndef HTMLLISTCTRL_H
#define HTMLLISTCTRL_H

#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#ifndef __ATLWIN_H__
	#error HTMLListCtrl.h requires atlwin.h to be included first
#endif

#ifndef __ATLGDI_H__
	#error HTMLListCtrl.h requires atlgdi.h to be included first
#endif

#include "MemDC.h"
#include "DrawHTML.h"

#define HTMLLIST_CLASS	_T("WTL_HtmlListCtrl")

//Item Types
#define HTML_TEXT					1
#define NORMAL_TEXT					2
#define SINGLE_LINE_TEXT			3

#define HTMLLIST_STYLE_CHECKBOX		1	
#define HTMLLIST_STYLE_GRIDLINES	2
#define HTMLLIST_STYLE_IMAGES		4

#define HLCN_INITIALIZE				0
#define HTMLLIST_SELECTIONCHANGED	1
#define HTMLLIST_LBUTTONDOWN		2
#define HTMLLIST_RBUTTONDOWN		3
#define HTMLLIST_LBUTTONDBLCLICK	4
#define HTMLLIST_ITEMCHECKED		5
#define HTMLLIST_KEYDOWN			6

//Padding between items
#define ITEM_PADDING_TOP			5
#define ITEM_PADDING_BOTTOM			5
#define ITEM_PADDING_LEFT			5	//if check box then after checkbox padding
#define ITEM_PADDING_CHECKBOX_LEFT	3
#define ITEM_IMAGE_PADDING_LEFT		5
#define ITEM_IMAGE_PADDING_RIGHT	5
#define ITEM_CHECKBOX_WIDTH			16

#define INVALID_ITEM				-1
#define NONE_SELECTED				-1
#define AUTO		0

// HTML List Notification
typedef struct tagNMHTMLLISTITEM
{
	NMHDR hdr;
	int	nItemNo;
	LPTSTR szItemText;
	LPARAM lItemData;
	BOOL bChecked;
} NMHTMLLISTITEM, *LPNMHTMLLISTITEM;

typedef struct tagNMHTMLKEYDOWN
{
    NMHDR hdr;
    WORD wVKey;
    UINT flags;
} NMHTMLKEYDOWN, *LPNMHTMLKEYDOWN;

// HTML List item
typedef struct tagHTMLITEM
{
	tagHTMLITEM()
	{
		nItemNo = INVALID_ITEM;
		lItemData = 0;
		nHeight = 0;
		nStyle = NORMAL_TEXT;
		rcItem.SetRectEmpty();
		bChecked = FALSE;
		bHeightSpecified = FALSE;
	}

	int			nItemNo;
	int			nHeight;
	int			nStyle;
	LPTSTR		szItemText;
	LPARAM		lItemData;
	CRect		rcItem;
	BOOL		bChecked;
	BOOL		bHeightSpecified;
	UINT		uiImage;
} HTMLITEM, *LPHTMLITEM;


/////////////////////////////////////////////////////////////////////////////
// CHTMLListCtrlImpl - client side for HTML List control

template< class T, class TBase = CWindow, class TWinTraits = CControlWinTraits >
class ATL_NO_VTABLE CHTMLListCtrlImpl : public CWindowImpl< T, TBase, TWinTraits >
{

protected:
	typedef CWindowImpl< T, TBase, TWinTraits >	baseClass;
	CAtlList< LPHTMLITEM > m_listItems;
	CAtlMap<int, LPHTMLITEM> m_mapItems;
	UINT m_nControlID;
	int m_nSelectedItem;
	int m_nTotalItems;
	int m_nListHeight;
	int m_nWndWidth;
	int m_nWndHeight;
	BOOL m_bHasFocus;
	DWORD m_dwExtendedStyles;
	CImageList *m_pImageList;

	//GDI stuff
	CFont		m_font;
	CPen		m_penLight;
	COLORREF	m_clrTextColor;	// default text color
	COLORREF	m_clrBackColor; // default background color
	COLORREF	m_clrBkSelectedItem;

public:
	DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

// Constructors
	CHTMLListCtrlImpl() { _ResetVariables();  }
	virtual ~CHTMLListCtrlImpl() { }

	HWND Create(HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = WS_CHILD|WS_VISIBLE, DWORD dwExStyle = 0,
			_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		dwStyle |= WS_BORDER|WS_CHILD|WS_VISIBLE|WS_VSCROLL|WS_TABSTOP;
		return _BaseClass::Create(hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

// Attributes
	static LPCTSTR GetWndClassName()
	{
		return HTMLLIST_CLASS;
	}

	void SetTextColor(COLORREF clr)
	{
		m_clrTextColor = clr;
		if ( IsWindow() )
			Invalidate();
	}

	COLORREF GetTextColor() const
	{
		return m_clrTextColor;
	}

	void SetBackColor(COLORREF clr)
	{
		m_clrBackColor = clr;
		if ( IsWindow() )
			Invalidate();
	}

	COLORREF GetBackColor() const
	{
		return m_clrBackColor;
	}

	void SetBkSelectedColor(COLORREF clr)
	{
		m_clrBkSelectedItem = clr;
		if ( IsWindow() )
			Invalidate();
	}

	COLORREF GetBkSelectedColor() const
	{
		return m_clrBkSelectedItem;
	}

	void SetImageList(CImageList *pImageList)
	{
		m_pImageList = pImageList;
	}

	CImageList* GetImageList()
	{
		return m_pImageList;
	}

	void SetExtendedStyle(DWORD dwExStyle)
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
		Invalidate();
	}

	DWORD GetExtendedStyle() const
	{
		return m_dwExtendedStyles;
	}

	BOOL SubclassWindow(HWND hWnd)
	{
		ATLASSERT(m_hWnd == NULL);
		ATLASSERT(::IsWindow(hWnd));
		BOOL bRet = baseClass::SubclassWindow(hWnd);
		if ( bRet ) Initialize();
		return bRet;
	}

	HWND UnsubclassWindow(BOOL bForce = FALSE)
	{
		Uninitialize();
		return baseClass::UnsubclassWindow(bForce);
	}

	int GetItemCount() const
	{
		return m_nTotalItems;
	}

	int InsertItem(LPCTSTR szText, int nStyle=HTML_TEXT, int nHeight=AUTO)
	{
		// Allocate memory
		ATLASSERT( szText != NULL );
		LPHTMLITEM pItem = new HTMLITEM();
		int nLen = _tcslen( szText );
		pItem->szItemText = new TCHAR[nLen+1];
		_tcscpy(pItem->szItemText, szText);
		pItem->nStyle = nStyle;
		pItem->nItemNo = m_nTotalItems;

		if (nHeight == AUTO)
		{
			//Calculate items height
			pItem->nHeight = CalculateItemHeight(szText,nStyle,pItem->uiImage,m_nWndWidth);
			pItem->bHeightSpecified = FALSE;
		}
		else
		{
			pItem->nHeight = nHeight;
			pItem->bHeightSpecified = TRUE;
		}

		// Add item to array
		m_listItems.AddTail( pItem );

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
	
		m_mapItems.SetAt(pItem->nItemNo, pItem);

		return (m_nTotalItems - 1);
	}

	int GetSelectedItem() const
	{
		return m_nSelectedItem;
	}

	void SetItemText(int nPos, LPCTSTR szText, BOOL bCalculateHeight = TRUE)
	{
		LPHTMLITEM pItem = GetInternalData(nPos);
		if(pItem)
		{
			delete []pItem->szItemText;
			pItem->szItemText = 0;
			int nLen = _tcslen( szText );
			pItem->szItemText = new TCHAR[nLen+1];
			_tcscpy(pItem->szItemText, szText);
			if (bCalculateHeight)
			{
				pItem->bHeightSpecified = FALSE;
				ReArrangeWholeLayout();
				Invalidate();
			}
			else
			{
				InvalidateRect(pItem->rcItem, TRUE);
			}
		}
	}

	int GetItemText(int nPos, LPTSTR szItemText, int nSize) const
	{
		HTMLITEM* pItem = GetInternalData(nPos);
		int nLen = 0;
		if(pItem)
		{
			nLen = __min( (int)_tcslen(pItem->szItemText), nSize-1 );
			_tcsncpy(szItemText, pItem->szItemText, nLen);
			szItemText[nLen] = 0;
		}
		return nLen;
	}

	BOOL DeleteItem(int nPos)
	{
		POSITION pos = m_listItems.GetHeadPosition();
		for(int i = 0;i < (int)m_listItems.GetCount();i++)
		{
			LPHTMLITEM pItem = m_listItems.GetNext(pos);
			if (pItem->nItemNo == nPos)
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
				
				if (m_nSelectedItem == pItem->nItemNo)
				{
					m_nSelectedItem = NONE_SELECTED;
				}

				// Adjust scrollbar 
				m_nListHeight -= pItem->nHeight;
				SCROLLINFO scrlinfo;
				scrlinfo.cbSize = sizeof(scrlinfo);

				scrlinfo.fMask = SIF_PAGE|SIF_RANGE;
				scrlinfo.nMax = m_nListHeight;
				scrlinfo.nMin = 0;
				scrlinfo.nPage = m_nWndHeight;
				scrlinfo.nPos = 0;
				SetScrollInfo(SB_VERT,&scrlinfo);	

				// free resources
				delete pItem->szItemText;
				delete pItem;

				m_nTotalItems--;

				ReArrangeItems();
				Invalidate();
				return TRUE;
			}
		}
		return FALSE;
	}

	void EnsureVisible(int nPos)
	{
		int nScrollPos = GetScrollPos(SB_VERT);
		
		int nItemPos = 0;
		int nScrollAmount = 0;

		POSITION pos = m_listItems.GetHeadPosition();
		for(int i = 0;i < (int)m_listItems.GetCount();i++)
		{
			HTMLITEM *pItem = m_listItems.GetNext(pos);
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
			SetScrollPos(SB_VERT,nScrollPos - nScrollAmount, FALSE);
			Invalidate();
		}
	}

	void SetItemCheck(int nPos, BOOL bCheck = TRUE)
	{
		HTMLITEM* pItem = GetInternalData(nPos);
		if(pItem)
		{
			pItem->bChecked = bCheck;
			InvalidateRect(&pItem->rcItem, TRUE);
		}
	}

	BOOL GetItemCheck(int nPos) const
	{
		HTMLITEM* pItem = GetInternalData(nPos);
		if(pItem)
		{
			return pItem->bChecked;
		}
		return FALSE;
	}

	// Methods
	// Message map and handlers

	BEGIN_MSG_MAP(CHTMLListCtrlImpl)
	  MESSAGE_HANDLER(WM_CREATE, OnCreate)
	  MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	  MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	  MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	  MESSAGE_HANDLER(WM_PAINT, OnPaint)
	  MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	  MESSAGE_HANDLER(WM_SIZE, OnSize)
      MESSAGE_HANDLER(WM_GETDLGCODE, OnGetDlgCode)
      MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
	  MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	  MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
	  MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
	  MESSAGE_HANDLER(WM_VSCROLL, OnVScroll)
	  MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
	  MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		LRESULT lRes = DefWindowProc();
		if(lRes != -1)
		{
			Initialize();
		}
		return lRes;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		Uninitialize();
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd); // device context for painting

		CMemDC dcMem( dc );
		int nOldMode = dc.SetBkMode( TRANSPARENT );
		HFONT pOldFont = dcMem.SelectFont( m_font );

		CRect rcWnd;
		GetClientRect(&rcWnd);
		dcMem.FillSolidRect(rcWnd, m_clrBackColor );

		CRect rcItem = rcWnd;
		rcItem.bottom = 0;

		int nScrollPos = GetScrollPos(SB_VERT);

		rcItem.OffsetRect(0,-nScrollPos);

		POSITION pos = m_listItems.GetHeadPosition();
		for(int i = 0;i < (int)m_listItems.GetCount();i++)
		{
			HTMLITEM* pItem = m_listItems.GetNext(pos);

			//Create the bounding rect for item
			rcItem.bottom = rcItem.top + pItem->nHeight;
			if(i == m_nSelectedItem)
			{
				//Call the virtual function for drawing the item
				DrawItem(&dcMem,rcItem,pItem,TRUE);
			}
			else
			{
				DrawItem(&dcMem,rcItem,pItem,FALSE);
			}

			pItem->rcItem = rcItem;
			//Move rcItem to next item
			rcItem.OffsetRect(0,pItem->nHeight);
		}

		//Release GDI stuff
		dcMem.SelectFont(pOldFont);
		dcMem.SetBkMode( nOldMode );
		return 0; // View fills entire client area
	}

	LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return TRUE; // View fills entire client area
	}

	LRESULT OnSetFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_bHasFocus = TRUE;
		if(m_nSelectedItem != NONE_SELECTED)
		{
			InvalidateRect(GetItemRect(m_nSelectedItem));
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_bHasFocus = FALSE;
		if(m_nSelectedItem != NONE_SELECTED)
		{
			InvalidateRect(GetItemRect(m_nSelectedItem));
		}
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DefWindowProc();
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
		return 0;
	}

	LRESULT OnGetDlgCode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		return DefWindowProc(uMsg, wParam, lParam) | DLGC_WANTARROWS|DLGC_WANTCHARS;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		NMHTMLKEYDOWN nmhdr = { 0 };
		nmhdr.hdr.code = HTMLLIST_KEYDOWN;
		nmhdr.hdr.hwndFrom = m_hWnd;
		nmhdr.hdr.idFrom = m_nControlID;
		nmhdr.wVKey = wParam;
		nmhdr.flags = 0;

		//Send keydown event first
		if ( GetParent().SendMessage(WM_NOTIFY, m_nControlID,(LPARAM)&nmhdr) == 1L )
			return 1L;

		int nChar = (int) wParam;
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
			Invalidate();
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
			Invalidate();
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
		else
			bHandled = FALSE;
		return 0;
	}

   	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		POINT point;
		point.x = LOWORD(lParam); point.y = HIWORD(lParam);
		SetFocus();

		NMHTMLLISTITEM nmhdr = { 0 };
		nmhdr.hdr.code = HTMLLIST_LBUTTONDOWN;
		nmhdr.hdr.hwndFrom = m_hWnd;
		nmhdr.hdr.idFrom = m_nControlID;

		nmhdr.lItemData = 0;
		nmhdr.nItemNo = -1;
		nmhdr.szItemText = NULL;
		nmhdr.bChecked = 0;

		//Send LButton down event first
		GetParent().SendMessage(WM_NOTIFY, m_nControlID,(LPARAM)&nmhdr);

		BOOL bItemSelected = FALSE;
		m_nSelectedItem = NONE_SELECTED;

		POSITION pos = m_listItems.GetHeadPosition();
		for(int iItem = 0;iItem < (int)m_listItems.GetCount();iItem++)
		{
			HTMLITEM *pItem = m_listItems.GetNext(pos);
			if( ::PtInRect(&pItem->rcItem, point))
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

						// Event notification
						NotifyParent(HTMLLIST_ITEMCHECKED, iItem);
					}
				}

				// Event notification
				NotifyParent(HTMLLIST_SELECTIONCHANGED, iItem);

				m_nSelectedItem = iItem;
				Invalidate();
				bItemSelected = TRUE;
				break;
			}
		}
		if(!bItemSelected)
		{
			nmhdr.hdr.code = HTMLLIST_SELECTIONCHANGED;
			nmhdr.hdr.hwndFrom = m_hWnd;
			nmhdr.hdr.idFrom = m_nControlID;

			nmhdr.lItemData = 0;
			nmhdr.nItemNo = NONE_SELECTED;
			nmhdr.szItemText = NULL;
			GetParent().SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)&nmhdr);
		}

		return 0;
	}

   	LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
	{
		POINT point;
		point.x = LOWORD(lParam); point.y = HIWORD(lParam);
		int nItem = -1;
		HTMLITEM hitem;
		if ( m_nSelectedItem != -1 )
		{
			LPHTMLITEM pItem = GetInternalData(m_nSelectedItem);
			if ( pItem && ::PtInRect(&pItem->rcItem, point))
			{
				nItem = m_nSelectedItem;
				memcpy(&hitem, pItem, sizeof(HTMLITEM));
			}
		}

		NMHTMLLISTITEM nmhdr = { 0 };
		nmhdr.hdr.code = HTMLLIST_LBUTTONDBLCLICK;
		nmhdr.hdr.hwndFrom = m_hWnd;
		nmhdr.hdr.idFrom = m_nControlID;

		nmhdr.lItemData = hitem.lItemData;
		nmhdr.nItemNo = nItem;
		nmhdr.szItemText = hitem.szItemText;
		nmhdr.bChecked = hitem.bChecked;

		GetParent().SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)&nmhdr);
		return 0;
	}

	LRESULT OnRButtonDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		NMHTMLLISTITEM nmhdr = { 0 };

		nmhdr.hdr.code = HTMLLIST_RBUTTONDOWN;
		nmhdr.hdr.hwndFrom = m_hWnd;
		nmhdr.hdr.idFrom = m_nControlID;

		nmhdr.lItemData = 0;
		nmhdr.nItemNo = -1;
		nmhdr.szItemText = "";
		nmhdr.bChecked = 0;

		GetParent().SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)&nmhdr);
		return 0;
	}

	LRESULT OnVScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		// call default
		DefWindowProc(uMsg, wParam, lParam);

		UINT nSBCode = LOWORD(wParam);
		UINT nPos = HIWORD(wParam);
		int nMinPos = 0, nMaxPos = 0;
		HWND hScrollWnd = (HWND) lParam;
		GetScrollRange(SB_VERT, &nMinPos, &nMaxPos);
		int nScrollPos = GetScrollPos(SB_VERT);
		int nLimit = nMaxPos; //GetScrollLimit(SB_VERT);

		int nScroll = nLimit;

		int SCROLL_AMT_Y = 50;

		switch(nSBCode) {
			case SB_LINEUP:      // Scroll up.      
			case SB_PAGEUP:
				if(nScrollPos <= 0)
				{
					return 0;
				}
				nScroll = min(nScrollPos,SCROLL_AMT_Y);
				SetScrollPos(SB_VERT,nScrollPos - nScroll);
				break;   
			case SB_LINEDOWN:   // Scroll down.
			case SB_PAGEDOWN:
				if(nScrollPos >= nLimit)
				{
					return 0;
				}
				nScroll = min(nScroll-nScrollPos,SCROLL_AMT_Y);
				SetScrollPos(SB_VERT,nScrollPos + nScroll);
				break;
			case SB_THUMBPOSITION:
				{
					HWND hWndScroll;
					if ( hScrollWnd == NULL )
						hWndScroll = m_hWnd;
					else
						hWndScroll = hScrollWnd;
					
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
					if ( hScrollWnd == NULL )
						hWndScroll = m_hWnd;
					else
						hWndScroll = hScrollWnd;
					
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
		return 0;
	}

	LRESULT OnMouseWheel(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int zDelta = (int)HIWORD(wParam);
		CPoint pt(LOWORD(lParam), HIWORD(lParam));

		int nMinPos = 0, nMaxPos = 0;
		GetScrollRange(SB_VERT, &nMinPos, &nMaxPos);
		int nScrollPos = GetScrollPos(SB_VERT);
		int nLimit = nMaxPos; //GetScrollLimit(SB_VERT);
		int nVertScroll = GetScrollPos(SB_VERT);
		if(zDelta < 0)
		{
			int nNewPos = min(nVertScroll + 40 , nMaxPos);
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
		bHandled = FALSE;
		return 0;
	}

protected:
   // Implementation
	void _ResetVariables()
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

		// set default color
		m_clrTextColor = RGB(0,0,0);
		m_clrBackColor = GetSysColor(COLOR_WINDOW);
		m_clrBkSelectedItem = RGB(127,202,254);
		m_dwExtendedStyles = 0;
		m_bHasFocus = FALSE;
		m_pImageList = NULL;
	}

	void Initialize()
	{
		// This is a little WTL subclass helper notification
		m_nControlID = GetDlgCtrlID();
		NMHDR nmh = { m_hWnd, m_nControlID, HLCN_INITIALIZE };
		::SendMessage(GetParent(), WM_NOTIFY, nmh.idFrom, (LPARAM) &nmh);
	}

	void Uninitialize()
	{
		DeleteAllItems();
		m_font.DeleteObject();
	}

	void SetInternalData(int nPos, LPHTMLITEM pItem)
	{
		m_mapItems.SetAt(nPos, pItem);
	}

	LPHTMLITEM GetInternalData(int nPos) const
	{
		LPHTMLITEM pItem = NULL;
		m_mapItems.Lookup(nPos, pItem);
		return pItem;
	}

	void DeleteAllItems()
	{
		m_nListHeight = 0;
		m_nTotalItems = 0;

		POSITION pos = m_listItems.GetHeadPosition();
		for(int i = 0;i < (int)m_listItems.GetCount();i++)
		{
			LPHTMLITEM pItem = m_listItems.GetNext(pos);
			delete pItem->szItemText;
			delete pItem;
		}
		m_listItems.RemoveAll();
		m_mapItems.RemoveAll();
	}

	CRect GetItemRect(int nPos) const
	{
		LPHTMLITEM pItem = GetInternalData(nPos);
		if ( pItem )
		{
			return pItem->rcItem;
		}
		CRect rcItem(0,0,0,0);
		return rcItem;
	}

	BOOL IsRectVisible(const RECT& rcClipBox, const RECT& rcItem) const
	{
		if (rcClipBox.top > rcItem.bottom) 
		{
			//Item is above the clip box
			return FALSE;
		}
		else if (rcClipBox.bottom < rcItem.top)
		{
			return FALSE;
		}
		return TRUE;
	}

	int CalculateItemHeight(CString sText, int nStyle, UINT uiImage,int nItemWidth) const
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
			CClientDC dc(m_hWnd);
			HFONT pOldFont = dc.SelectFont( m_font );

			CRect rc;
			rc.SetRectEmpty();

			rc.left = 0;

			rc.right = nItemWidth - nPadding;

			rc.right -= nImageWidth;

			dc.DrawText(sText,-1,&rc,DT_WORDBREAK|DT_CALCRECT|DT_EXTERNALLEADING );

			dc.SelectFont(pOldFont);
			return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
		}
		else if(nStyle == HTML_TEXT)
		{
			CClientDC dc(m_hWnd);
			CDC memDC;
			memDC.CreateCompatibleDC(dc);

			HFONT pOldFont = memDC.SelectFont( m_font );

			int nWidth = 0;

			nWidth = nItemWidth - nPadding;
			nWidth -= nImageWidth;

			CRect rc(0,0,nWidth,m_nWndHeight);
			
			int nHeight = DrawHTML(memDC.m_hDC,sText,sText.GetLength(),&rc,DT_LEFT|DT_CALCRECT|DT_WORDBREAK|DT_EXTERNALLEADING);

			memDC.SelectFont(pOldFont);

			return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
		}
		else if(nStyle == SINGLE_LINE_TEXT)
		{
			CClientDC dc(m_hWnd);
		
			HFONT pOldFont = dc.SelectFont( m_font );

			CRect rc;
			rc.SetRectEmpty();

			rc.left = 0;

			rc.right = nItemWidth - nPadding;
			rc.right -= nImageWidth;

			dc.DrawText(sText,-1,&rc,DT_VCENTER|DT_CALCRECT|DT_SINGLELINE);

			dc.SelectFont(pOldFont);
			return rc.Height() + ITEM_PADDING_BOTTOM + ITEM_PADDING_TOP;
		}
		return 0;
	}

	void DrawItem(CDC* pDC, CRect& rcItem, LPHTMLITEM pItem, BOOL bSelected)
	{
		CRect rcClipBox;
		pDC->GetClipBox(&rcClipBox);

		if(!IsRectVisible(rcClipBox,rcItem))
		{
			return;
		}

		COLORREF clrText = m_clrTextColor;
		COLORREF clrOld;
		CRect rcImage;
			
		if(bSelected)
		{
			//clrText = RGB(255,255,255);
			pDC->FillSolidRect(&rcItem, m_clrBkSelectedItem);
		}
		else
		{
			pDC->FillSolidRect(&rcItem, m_clrBackColor);
		}

		if(m_dwExtendedStyles & HTMLLIST_STYLE_GRIDLINES)
		{
			pDC->DrawEdge(&rcItem, BDR_SUNKENINNER,BF_LEFT|BF_BOTTOM|BF_FLAT);
		}

		CPoint ptCheckBox = rcItem.TopLeft();;
		if(m_dwExtendedStyles & HTMLLIST_STYLE_CHECKBOX)
		{
			ptCheckBox.x += ITEM_PADDING_CHECKBOX_LEFT;
			ptCheckBox.y += rcItem.Height() / 2 - 8;
			CRect rcCheckBox(0, 0, ITEM_CHECKBOX_WIDTH, ITEM_CHECKBOX_WIDTH);
			rcCheckBox.OffsetRect(ptCheckBox);
			DrawFrameControl(pDC->m_hDC, &rcCheckBox, DFC_BUTTON, (pItem->bChecked?DFCS_CHECKED:0));
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
				
				m_pImageList->Draw(pDC->m_hDC,pItem->uiImage,pt,ILD_TRANSPARENT);
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

			pDC->DrawText(pItem->szItemText, -1, &rc, DT_LEFT|DT_WORDBREAK);
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

			DrawHTML(pDC->m_hDC,pItem->szItemText, -1, &rc, DT_LEFT|DT_WORDBREAK);
		}
		
		pDC->SetTextColor(clrOld);

		//Draw the focus rect if focused
		if (m_bHasFocus && (bSelected))
		{
			pDC->DrawFocusRect(&rcItem);
		}
	}

	void ReArrangeItems()
	{
		m_mapItems.RemoveAll();
		POSITION pos = m_listItems.GetHeadPosition();
		for(int nIndex = 0;nIndex < (int)m_listItems.GetCount();nIndex++)
		{
			LPHTMLITEM pItem = m_listItems.GetNext(pos);
			pItem->nItemNo = nIndex;
			SetInternalData(nIndex, pItem);
		}
	}

	void ReArrangeWholeLayout()
	{
		m_nTotalItems = 0;
		m_nListHeight = 0;
		m_mapItems.RemoveAll();

		POSITION pos = m_listItems.GetHeadPosition();
		for(int nIndex = 0;nIndex < (int)m_listItems.GetCount();nIndex++)
		{
			LPHTMLITEM pItem = m_listItems.GetNext(pos);
			pItem->nItemNo = nIndex;

			if (!pItem->bHeightSpecified)
			{
				//Calculate items height
				pItem->nHeight = CalculateItemHeight(pItem->szItemText, pItem->nStyle,pItem->uiImage,m_nWndWidth);
			}

			m_nTotalItems++;
			m_nListHeight += pItem->nHeight;
			SetInternalData(nIndex, pItem);
		}
	}

	void NotifyParent(UINT uCode, int nPos)
	{
		HTMLITEM *pItem = GetInternalData(nPos);
		if(pItem)
		{
			NMHTMLLISTITEM nmhdr = { 0 };
			nmhdr.hdr.code = uCode;
			nmhdr.hdr.hwndFrom = m_hWnd;
			nmhdr.hdr.idFrom = m_nControlID;

			nmhdr.lItemData = pItem->lItemData;
			nmhdr.nItemNo = pItem->nItemNo;
			nmhdr.szItemText = pItem->szItemText;
			nmhdr.bChecked = pItem->bChecked;

			//Send Selection changed Event
			GetParent().SendMessage(WM_NOTIFY,m_nControlID,(LPARAM)&nmhdr);
		}
	}

	void SendSelectionChangeNotification(int nPos)
	{
		NotifyParent(HTMLLIST_SELECTIONCHANGED, nPos);
	}

	void SendCheckStateChangedNotification(int nPos)
	{
		NotifyParent(HTMLLIST_ITEMCHECKED, nPos);
	}

	LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		SetCursor(::LoadCursor(NULL, IDC_ARROW));
		bHandled = FALSE;
		return 1;
	}
};

class CHTMLListCtrl : public CHTMLListCtrlImpl<CHTMLListCtrl>
{
public:
   DECLARE_WND_CLASS( HTMLLIST_CLASS )  
};

#endif //HTMLLISTCTRL_H
