// NGenericPopup.cpp : implementation file
//
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "stdafx.h"
#include "NGenericPopup.h"
#include "NGenericToolBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OBM_CHECK           32760 // From Winuser.h

/////////////////////////////////////////////////////////////////////////////
// CNGenericPopup

CNGenericPopup::CNGenericPopup()
{
	m_sztick=GetMenuCheckMarkDimensions();
	m_tick.Attach((HBITMAP)LoadImage(NULL,MAKEINTRESOURCE(OBM_CHECK),IMAGE_BITMAP,0,0,LR_LOADMAP3DCOLORS|LR_SHARED));
	m_pMenu=new CMenu;
}

CNGenericPopup::~CNGenericPopup()
{
	m_pMenu->m_hMenu=NULL;
	delete m_pMenu;
}


IMPLEMENT_DYNAMIC(CNGenericPopup, CWnd)

BEGIN_MESSAGE_MAP(CNGenericPopup, CWnd)
	//{{AFX_MSG_MAP(CNGenericPopup)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CAPTURECHANGED()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNGenericPopup message handlers

BOOL CNGenericPopup::ShowMenu(int nOrient, BOOL bFromKey, CNGenericToolBar* pToolbar, int x, int y, CWnd* pParent, HMENU hMenu)
{
	ASSERT(hMenu);

	HideMenu();
	m_pToolbar=pToolbar;
	m_pMenu->m_hMenu=hMenu;
	m_pParent=pParent;
	m_nSelectedItem=-1;
	m_bMouseInMenu=FALSE;
	m_nOrient=nOrient;

	if(!CreateEx(0,AfxRegisterWndClass(CS_SAVEBITS,LoadCursor(NULL,IDC_ARROW),(HBRUSH)CBrush(GetSysColor(COLOR_BTNFACE))),NULL,WS_POPUP,x,y,100,100,*pParent,0)) 
		return FALSE;
	m_pParent->SendMessage(WM_ENTERMENULOOP,FALSE);
	SetCapture();

	int cx=0,cy=0,n;
	CSize siz;
	CRect rect;
	CDC& dc=*GetDC();
	dc.SelectObject((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	GetClientRect(rect);
	CString tmp;
	LPCTSTR q;

	cy=4;
	m_rectItem.SetSize(0);
	m_accelList.SetSize(0);
	for(n=0; n<(int)m_pMenu->GetMenuItemCount(); n++)
	{
		m_pMenu->GetMenuString(n,tmp,MF_BYPOSITION);
		for(q=tmp; *q; q++)
		{
			if(*q=='&')
			{
				int s=m_accelList.GetSize();
				m_accelList.SetSize(s+1);
				m_accelList[s].nKey=toupper(*(q+1));
				m_accelList[s].nId=m_pMenu->GetMenuItemID(n);
				break;
			}
		}
		siz=DrawMenuItem(n,dc,rect,FALSE,FALSE);
		m_rectItem.Add(CRect(4,cy,0,cy+siz.cy-1));
		if(siz.cx>cx) cx=siz.cx;
		cy+=siz.cy;
	}
	cy+=2;
	cx+=8;
	ReleaseDC(&dc);

	for(n=0; n<m_rectItem.GetSize(); n++)
		m_rectItem[n].right=cx-4;

	if(m_nOrient==POP_MENU_RIGHT) x-=cx;
	else if(m_nOrient==POP_MENU_BOTTOM) y-=cy;
	MoveWindow(x,y,cx,cy);
	ShowWindow(SW_SHOWNA);
	SetFocus();
	if(bFromKey) SelectItem(0);

	return TRUE;
}

BOOL CNGenericPopup::HideMenu()
{
	if(IsWindow(*this)) DestroyWindow();
	return TRUE;
}


void CNGenericPopup::OnPaint() 
{
	int n;
	CSize siz;

	CPaintDC dc(this); // device context for painting
	CRect rect;

	GetClientRect(rect);
	dc.FillSolidRect(rect,GetSysColor(COLOR_BTNFACE));
	dc.Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_WINDOWTEXT));

	dc.SelectObject((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	rect.InflateRect(-4,-4);
	for(n=0; n<(int)m_pMenu->GetMenuItemCount(); n++)
	{
		siz=DrawMenuItem(n,dc,rect,n==m_nSelectedItem,TRUE);
		rect.top+=siz.cy;
	}
}

void CNGenericPopup::SelectItem(int nItem)
{
	if(m_nSelectedItem==nItem) return;

	CRect rect;
	CDC& dc=*GetDC();
	dc.SelectObject((HFONT)GetStockObject(DEFAULT_GUI_FONT));

	if(m_nSelectedItem!=-1)
	{
		rect=m_rectItem[m_nSelectedItem];
		DrawMenuItem(m_nSelectedItem,dc,rect,FALSE,TRUE);
	}

	if(nItem!=-1)
	{
		rect=m_rectItem[nItem];
		DrawMenuItem(nItem,dc,rect,TRUE,TRUE);
	}
	m_nSelectedItem=nItem;

	ReleaseDC(&dc);
}


CSize CNGenericPopup::DrawMenuItem(int nItem, CDC& dc, const CRect& rect, BOOL bHighlight, BOOL bReallyDraw)
{
	CString tmp,tmp1,tmp2;
	char* p,*q;
	CSize siz;
	UINT nState;
	CRect rect2;

	nState=m_pMenu->GetMenuState(nItem,MF_BYPOSITION|MF_DISABLED|MF_CHECKED|MF_GRAYED|MF_SEPARATOR);
	if(nState&MF_SEPARATOR)
	{
		if(bReallyDraw)
		{
			rect2=rect;
			rect2.top=rect.top+4;
			rect2.bottom=rect2.top+2;
			dc.Draw3dRect(rect2,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DHILIGHT));
		}
		siz.cx=0;
		siz.cy=10;
	}
	else
	{
		m_pMenu->GetMenuString(nItem,tmp,MF_BYPOSITION);
		siz=dc.GetTextExtent(tmp);

		p=(char*)(LPCTSTR)tmp;
		q=(char*)tmp1.GetBufferSetLength(1024);

		while(*p && *p!='\t') *(q++)=*(p++);
		if(*p) { p++; siz.cx+=16; }
		*q='\0';
		q=(char*)tmp2.GetBufferSetLength(1024);
		while(*p) *(q++)=*(p++);
		*q='\0';

		tmp1.ReleaseBuffer();
		tmp2.ReleaseBuffer();

		if(bReallyDraw)
		{
			rect2=rect;
			rect2.top-=1;
			rect2.bottom+=1;
			if(bHighlight)
			{
				dc.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
				dc.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
				dc.FillSolidRect(rect2,GetSysColor(COLOR_HIGHLIGHT));
			}
			else
			{
				dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
				dc.SetTextColor(GetSysColor(COLOR_WINDOWTEXT));
				dc.FillSolidRect(rect2,GetSysColor(COLOR_BTNFACE));
			}

			rect2=rect;
			rect2.left+=m_sztick.cx;
			rect2.right-=m_sztick.cx;
			if(nState&MF_CHECKED)
			{
				CDC pMemDC;
				
				pMemDC.CreateCompatibleDC(&dc);
				pMemDC.SelectObject(m_tick);
				dc.BitBlt(rect.left,rect.top,m_sztick.cx,m_sztick.cy,&pMemDC,0,0,SRCCOPY);
			}
			if(nState&MF_GRAYED)
			{
				if(!bHighlight)
				{
					dc.SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
					dc.DrawText(tmp1,rect2,DT_LEFT|DT_SINGLELINE);
					dc.DrawText(tmp2,rect2,DT_RIGHT|DT_SINGLELINE);
					dc.SetBkMode(TRANSPARENT);
					rect2.OffsetRect(-1,-1);
					dc.SetTextColor(GetSysColor(COLOR_3DSHADOW));
					dc.DrawText(tmp1,rect2,DT_LEFT|DT_SINGLELINE);
					dc.DrawText(tmp2,rect2,DT_RIGHT|DT_SINGLELINE);
					dc.SetBkMode(OPAQUE);
				}
				else
				{
					dc.SetTextColor(GetSysColor(COLOR_BTNFACE));
					dc.DrawText(tmp1,rect2,DT_LEFT|DT_SINGLELINE);
					dc.DrawText(tmp2,rect2,DT_RIGHT|DT_SINGLELINE);
				}
			}
			else
			{
				dc.DrawText(tmp1,rect2,DT_LEFT|DT_SINGLELINE);
				dc.DrawText(tmp2,rect2,DT_RIGHT|DT_SINGLELINE);
			}
		}
		siz.cx+=m_sztick.cx*2;
		siz.cy+=4;
	}
	return siz;
}

void CNGenericPopup::OnDestroy() 
{
	m_pParent->SendMessage(WM_EXITMENULOOP,FALSE);
	ReleaseCapture();
	CWnd::OnDestroy();
}

void CNGenericPopup::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd* pWnd;
	CRect rect;

	m_pParent->SendMessage(WM_ENTERIDLE,MSGF_MENU,(LPARAM)m_hWnd);

	GetClientRect(rect);
	rect.InflateRect(-4,-4);
	ClientToScreen(&rect);
	
	ClientToScreen(&point);
	pWnd=WindowFromPoint(point);

	if(!pWnd) return;
	if(rect.PtInRect(point))
	{
		ScreenToClient(&point);
		for(int n=0; n<m_rectItem.GetSize(); n++)
		{
			if(m_rectItem[n].PtInRect(point))
			{
				if(m_nSelectedItem!=n)
				{
					m_pParent->SendMessage(WM_MENUSELECT,m_pMenu->GetMenuItemID(n),MAKELPARAM(m_pMenu->GetMenuState(n,MF_BITMAP|MF_POPUP|MF_BYPOSITION|MF_DISABLED|MF_CHECKED|MF_GRAYED)|MF_MOUSESELECT|MF_HILITE,m_pMenu->m_hMenu));
					SelectItem(n);
					m_bMouseInMenu=TRUE;
				}
				return;

			}
		}
	}
	if(m_bMouseInMenu) SelectItem(-1);
	m_bMouseInMenu=FALSE;
	if(pWnd==m_pToolbar) 
	{
		pWnd->ScreenToClient(&point);
		pWnd->PostMessage(WM_MOUSEMOVE,nFlags,MAKELONG(point.x,point.y));
		return;
	}
}

void CNGenericPopup::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rect;
	GetClientRect(rect);
	if(!rect.PtInRect(point))
	{
		m_pToolbar->SendMessage(WM_MENU_DISMISS);
		DestroyWindow();
	}
}

void CNGenericPopup::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rect;
	UINT nID;

	GetClientRect(rect);
	if(rect.PtInRect(point))
	{
		for(int n=0; n<m_rectItem.GetSize(); n++)
		{
			if(m_rectItem[n].PtInRect(point))
			{
				if(m_pMenu->GetMenuState(n,MF_BYPOSITION|MF_DISABLED|MF_GRAYED)&0xff)
					break;
				m_pToolbar->SendMessage(WM_MENU_DISMISS);
				DestroyWindow();
				if((nID=m_pMenu->GetMenuItemID(n))!=0)
				{
					m_pParent->PostMessage(WM_COMMAND,nID,NULL);
					TRACE("Command Message %d\n",nID);
				}
				break;

			}
		}
	}
}

void CNGenericPopup::OnCaptureChanged(CWnd *pWnd) 
{
	if(pWnd!=this) SetCapture();
}

BOOL CNGenericPopup::KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nItem;

	if(nChar==VK_ESCAPE)
	{
		m_pToolbar->SendMessage(WM_MENU_DISMISS);
		DestroyWindow();
		return TRUE;
	}
	if(m_nSelectedItem!=-1 || nChar==VK_DOWN /* Cheat */)
	{
		if(nChar==VK_DOWN && m_nSelectedItem<m_rectItem.GetSize()-1)
		{
			nItem=m_nSelectedItem+1;

			while(nItem<m_rectItem.GetSize())
			{
				if(!(m_pMenu->GetMenuState(nItem,MF_BYPOSITION|MF_DISABLED|MF_CHECKED|MF_GRAYED|MF_SEPARATOR)&MF_SEPARATOR)) 
				{
					SelectItem(nItem);
					break;
				}
				nItem++;
			}
			return TRUE;
		}
		if(nChar==VK_UP && m_nSelectedItem)
		{
			nItem=m_nSelectedItem-1;

			while(nItem>=0)
			{
				if(!(m_pMenu->GetMenuState(nItem,MF_BYPOSITION|MF_DISABLED|MF_CHECKED|MF_GRAYED|MF_SEPARATOR)&MF_SEPARATOR)) 
				{
					SelectItem(nItem);
					break;
				}
				nItem--;
			}
			return TRUE;
		}
		if(nChar==VK_RETURN)
		{
			UINT nID;

			if(!(m_pMenu->GetMenuState(m_nSelectedItem,MF_BYPOSITION|MF_DISABLED|MF_CHECKED|MF_GRAYED|MF_SEPARATOR)&(MF_DISABLED|MF_GRAYED))) 
			{
				if((nID=m_pMenu->GetMenuItemID(m_nSelectedItem))!=0)
				{
					m_pToolbar->SendMessage(WM_MENU_DISMISS);
					DestroyWindow();
					m_pParent->PostMessage(WM_COMMAND,nID,NULL);
				}
			}
			return TRUE;
		}
		if(TranslateMenuChar(nChar)) return TRUE;
	}
	return FALSE;
}

BOOL CNGenericPopup::TranslateMenuChar(UINT nChar)
{
	for(int n=0; n<m_accelList.GetSize(); n++)
	{
		if(m_accelList[n].nKey==(UINT)toupper(nChar))
		{
			m_pToolbar->SendMessage(WM_MENU_DISMISS);
			DestroyWindow();
			m_pParent->PostMessage(WM_COMMAND,m_accelList[n].nId);
			return TRUE;
		}
	}
	return FALSE;
}

void CNGenericPopup::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(KeyboardFilter(nChar,nRepCnt,nFlags)) return;
	if(m_pToolbar->KeyboardFilter(nChar,nRepCnt,nFlags)) return;
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}
