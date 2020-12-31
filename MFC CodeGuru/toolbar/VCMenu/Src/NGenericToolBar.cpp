// NGenericToolBar.cpp: implementation of the CNGenericToolBar class.
//
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

Copyright (C) 1998 George H. Stahl (GStahl@VipMail.Com)
	- Added GenericToolBarModifyStyle

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "NGenericToolBar.h"

#include "afxpriv.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CNGenericToolBar,CToolBar)

BEGIN_MESSAGE_MAP(CNGenericToolBar,CToolBar)
	//{{AFX_MSG_MAP(CNGenericToolBar)
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_BUTTONSONLY,OnButtonsOnly)
	ON_COMMAND(IDM_BUTTONSANDTEXT,OnTextAndButtons)
	ON_COMMAND(IDM_TEXTONLY,OnTextOnly)
	ON_COMMAND(IDM_RECALCSIZE,OnRecalcSize)
 END_MESSAGE_MAP()

CArray<CNGenericToolBar*,CNGenericToolBar*> CNGenericToolBar::m_ToolbarList;
BOOL CNGenericToolBar::m_bButtons=FALSE;
BOOL CNGenericToolBar::m_bText=FALSE;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNGenericToolBar::CNGenericToolBar()
{
	m_bHasText=FALSE;
	m_bHasBitmaps=TRUE;
	m_bForceText=FALSE;
	m_bSysMenuIcon=FALSE;
	m_dwGenericToolBarStyle = 0x0000;
}

CNGenericToolBar::~CNGenericToolBar()
{

}

void CNGenericToolBar::OnRecalcSize()
{
	SettingChange();
	RecalcSize();
	GetParentFrame()->DelayRecalcLayout();
}

void CNGenericToolBar::SettingChange()
{
	TBBUTTON tb;
	for(int n=0; n<GetCount(); n++)
	{
		SendMessage(TB_GETBUTTON,n,(LPARAM)&tb);
		tb.iString=m_bText?m_TextIds[n]:-1;
		_SetButton(n,&tb);
	}
	SendMessage(TB_SETMAXTEXTROWS,m_bText||m_bForceText?4:0);
	SendMessage(TB_SETBITMAPSIZE,0,m_bButtons&&m_bHasBitmaps?MAKELONG(16,15):0);
	SendMessage(TB_AUTOSIZE);
}

BOOL CNGenericToolBar::RecalcSize()
{
	CRect rect;
	int cx=0,cy=0;

	SendMessage(TB_AUTOSIZE);
	for(int n=0; n<GetToolBarCtrl().GetButtonCount(); n++)
	{
		GetItemRect(n,&rect);
		if(rect.Width()>cx) cx=rect.Width();
		if(rect.Height()>cy) cy=rect.Height();
	}
	m_sizeButton.cx=cx;
	m_sizeButton.cy=cy-2;
	m_bDelayedButtonLayout=TRUE;
	return TRUE;
}

BOOL CNGenericToolBar::CreateEx(CWnd* pParentWnd, DWORD dwExStyle, DWORD dwStyle, UINT nID, LPCTSTR szTitle)
{
	if(!CToolBar::Create(pParentWnd,dwStyle,nID)) return FALSE;
	if(szTitle) SetWindowText(szTitle);
	m_pParent=pParentWnd;
	ModifyStyle(0,dwExStyle);
	m_pop.CreatePopupMenu();
	m_pop.AppendMenu(MF_STRING,IDM_BUTTONSONLY,"&Buttons");
	m_pop.AppendMenu(MF_STRING,IDM_BUTTONSANDTEXT,"Buttons &and Text");
	m_pop.AppendMenu(MF_STRING,IDM_TEXTONLY,"&Text");
	m_ToolbarList.Add(this);
	return TRUE;
}

BOOL CNGenericToolBar::LoadToolBar(LPCTSTR lpszResourceName)
{
	if(!CToolBar::LoadToolBar(lpszResourceName)) return FALSE;

	CString tmp;
	LPCTSTR p,q;
	SendMessage(TB_SETMAXTEXTROWS,4);
	m_accelList.SetSize(0);
	for(int n=0; n<GetCount(); n++)
	{
		if(GetItemID(n)!=-1)
		{
			tmp.LoadString(GetItemID(n));
			p=tmp;
			while(*p && *p!='\n')
				p++;
			if(*p)
			{
				p++;
				while(*p && *p!='\n')
					p++;
			}
			if(*p)
			{
				for(q=p; *q; q++)
				{
					if(*q=='&')
					{
						int s=m_accelList.GetSize();
						m_accelList.SetSize(s+1);
						m_accelList[s].nKey=toupper(*(q+1));
						m_accelList[s].nId=GetItemID(n);
						break;
					}
				}
				SetButtonText(n,p+1);
				m_bHasText=TRUE;
				m_bText=TRUE;
			}
			else
			{
				if(m_bHasText) SetButtonText(n," ");
			}
		}
	}


	TBBUTTON tb;
	m_TextIds.SetSize(0);
	for(n=0; n<GetCount(); n++)
	{
		SendMessage(TB_GETBUTTON,n,(LPARAM)&tb);
		m_TextIds.Add(tb.iString);
		tb.iString=m_bText?m_TextIds[n]:-1;
	}
	return TRUE;
}

BOOL CNGenericToolBar::SetButtonText(int nIndex, LPCTSTR lpszText)
{
	if(!CToolBar::SetButtonText(nIndex,lpszText)) return FALSE;
	return RecalcSize();
}


void CNGenericToolBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	m_pop.CheckMenuItem(IDM_BUTTONSONLY,m_bButtons&&!m_bText?MF_CHECKED:MF_UNCHECKED);
	m_pop.CheckMenuItem(IDM_BUTTONSANDTEXT,m_bButtons&&m_bText?MF_CHECKED:MF_UNCHECKED);
	m_pop.CheckMenuItem(IDM_TEXTONLY,!m_bButtons&&m_bText?MF_CHECKED:MF_UNCHECKED);
	m_pop.EnableMenuItem(IDM_BUTTONSONLY,MF_ENABLED);
	m_pop.EnableMenuItem(IDM_BUTTONSANDTEXT,m_bHasText?MF_ENABLED:MF_GRAYED);
	m_pop.EnableMenuItem(IDM_TEXTONLY,m_bHasText?MF_ENABLED:MF_GRAYED);
	m_pop.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);
}

void CNGenericToolBar::OnButtonsOnly()
{
	if(!m_bText && m_bButtons) return;
	m_bText=FALSE;
	m_bButtons=TRUE;
	SendToAllToolbars(WM_COMMAND,IDM_RECALCSIZE);
}

void CNGenericToolBar::OnTextOnly()
{
	if(m_bText && !m_bButtons) return;
	m_bText=TRUE;
	m_bButtons=FALSE;
	SendToAllToolbars(WM_COMMAND,IDM_RECALCSIZE);
}

void CNGenericToolBar::OnTextAndButtons()
{
	if(m_bText && m_bButtons) return;
	m_bText=TRUE;
	m_bButtons=TRUE;
	SendToAllToolbars(WM_COMMAND,IDM_RECALCSIZE);
}

void CNGenericToolBar::OnDestroy() 
{
	CToolBar::OnDestroy();
	for(int n=0; n<m_ToolbarList.GetSize(); n++)
		if(m_ToolbarList[n]==this)
		{
			m_ToolbarList.RemoveAt(n);
			break;
		}
}

void CNGenericToolBar::SendToAllToolbars(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	for(int n=0; n<m_ToolbarList.GetSize(); n++)
		m_ToolbarList[n]->SendMessage(uMsg,wParam,lParam);
}

void CNGenericToolBar::SetVisualState(BOOL bButtons, BOOL bText)
{
	if(!bText && !bButtons) bButtons=TRUE;
	m_bText=bText;
	m_bButtons=bButtons;
	SendToAllToolbars(WM_COMMAND,IDM_RECALCSIZE);
}

BOOL CNGenericToolBar::GetVisualState(BOOL bText)
{
	if(bText) return m_bText;
	else return m_bButtons;
}

// Borrowed from MFC
void CNGenericToolBar::_SetButton(int nIndex, TBBUTTON* pButton)
{
	// get original button state
	TBBUTTON button;
	VERIFY(DefWindowProc(TB_GETBUTTON, nIndex, (LPARAM)&button));

	// prepare for old/new button comparsion
	button.bReserved[0] = 0;
	button.bReserved[1] = 0;
	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
	pButton->fsState ^= TBSTATE_ENABLED;
	pButton->bReserved[0] = 0;
	pButton->bReserved[1] = 0;

	// nothing to do if they are the same
	if (memcmp(pButton, &button, sizeof(TBBUTTON)) != 0)
	{
		// don't redraw everything while setting the button
		DWORD dwStyle = GetStyle();
		ModifyStyle(WS_VISIBLE, 0);
		VERIFY(DefWindowProc(TB_DELETEBUTTON, nIndex, 0));
		VERIFY(DefWindowProc(TB_INSERTBUTTON, nIndex, (LPARAM)pButton));
		ModifyStyle(0, dwStyle & WS_VISIBLE);

		// invalidate appropriate parts
		if (((pButton->fsStyle ^ button.fsStyle) & TBSTYLE_SEP) ||
			((pButton->fsStyle & TBSTYLE_SEP) && pButton->iBitmap != button.iBitmap))
		{
			// changing a separator
			Invalidate(FALSE);
		}
		else
		{
			// invalidate just the button
			CRect rect;
			SendMessage(TB_AUTOSIZE);
			if (DefWindowProc(TB_GETITEMRECT, nIndex, (LPARAM)&rect))
				InvalidateRect(rect, FALSE);    // don't erase background
		}
	}
}

// Calculate the non-client area - adjusting for grippers
void CNGenericToolBar::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
     CToolBar::OnNcCalcSize(bCalcValidRects,lpncsp);
     // adjust non-client area for gripper at left or top
     if (m_dwStyle & CBRS_FLOATING)
	 {          // no grippers
     }
	 else if (m_dwStyle & CBRS_ORIENT_HORZ)
	 {
          // move 2 pixels right to make room
          lpncsp->rgrc[0].left += 2;
          lpncsp->rgrc[0].right += 2;
     }
	 else
	 {          // move 4 pixels downto make room
          lpncsp->rgrc[0].top += 4;
          lpncsp->rgrc[0].bottom += 4;     
	 }

	 // Adjust for system menu icon
	 if(m_bSysMenuIcon)
	 {
		if(m_dwStyle&CBRS_ORIENT_HORZ)
		{
		  // move 16 pixels right to make room
		  lpncsp->rgrc[0].left += 16;
		  lpncsp->rgrc[0].right += 16;
		}
		else
		{    // move 16 pixels downto make room
		  lpncsp->rgrc[0].top += 16;
		  lpncsp->rgrc[0].bottom += 16;     
		}
	 }
}

// Draw the gripper at left or top
void CNGenericToolBar::DrawGripper(CWindowDC *pDC, CRect& rectWindow)
{
     // get the gripper rect (1 pixel smaller than toolbar)
     CRect gripper = rectWindow;
     gripper.DeflateRect(1,1);
     if (m_dwStyle & CBRS_FLOATING)
	 {          // no grippers
     }
	 else if (m_dwStyle & CBRS_ORIENT_HORZ)
	 {          // gripper at left
          gripper.right = gripper.left+3;
          pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),::GetSysColor(COLOR_3DSHADOW));
          gripper.OffsetRect(+4,0);
          pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),::GetSysColor(COLOR_3DSHADOW));
          rectWindow.left += 8; 
	 } else
	 {          // gripper at top
          gripper.bottom = gripper.top+3;
          pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),::GetSysColor(COLOR_3DSHADOW));
          gripper.OffsetRect(0,+4);
          pDC->Draw3dRect(gripper,::GetSysColor(COLOR_3DHIGHLIGHT),::GetSysColor(COLOR_3DSHADOW));
          rectWindow.top += 8;
     }
}

void CNGenericToolBar::DrawSysMenuIcon(CWindowDC* pDC, CRect& rectWindow)
{
	if(!m_bSysMenuIcon) return; // Do nothing if this isn't needed

	if(m_dwStyle&CBRS_ORIENT_HORZ)
	{
		DrawIconEx(*pDC,rectWindow.left+2,rectWindow.top+6,m_hSysMenuIcon,16,16,0,NULL,DI_NORMAL);
		m_rectSysMenu.SetRect(rectWindow.left+2,rectWindow.top+6,rectWindow.left+2+16,rectWindow.top+6+16);
		rectWindow.left+=16;
	}
	else
	{
		DrawIconEx(*pDC,rectWindow.left+12,rectWindow.top+2,m_hSysMenuIcon,16,16,0,NULL,DI_NORMAL);
		m_rectSysMenu.SetRect(rectWindow.left+12,rectWindow.top+2,rectWindow.left+12+16,rectWindow.top+2+16);
		rectWindow.top+=16;
	}
}


// Erase the non-client area (borders) - copied from MFC implementation
void CNGenericToolBar::EraseNonClient(BOOL bRaised)
{
     // get window DC that is clipped to the non-client area
     CWindowDC dc(this);
     CRect rectClient;
     GetClientRect(rectClient);
     CRect rectWindow;
     GetWindowRect(rectWindow);
     ScreenToClient(rectWindow);
     rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
     dc.ExcludeClipRect(rectClient);     // draw borders in non-client area
     rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);
	DrawBorders(&dc, rectWindow);     // erase parts not drawn
     dc.IntersectClipRect(rectWindow);
     SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);
     DrawGripper(&dc, rectWindow); // <-- my addition to draw gripper}
	 DrawSysMenuIcon(&dc, rectWindow); // Draw icon for system menu, if needed
}

BOOL CNGenericToolBar::TranslateMenuChar(UINT nChar)
{
	for(int n=0; n<m_accelList.GetSize(); n++)
	{
		if(m_accelList[n].nKey==(UINT)toupper(nChar))
		{
			m_pParent->PostMessage(WM_COMMAND,m_accelList[n].nId);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CNGenericToolBar::KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	return FALSE;
}

void CNGenericToolBar::DrawBorders(CDC* pDC, CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	DWORD dwStyle = m_dwStyle;
	if (!(dwStyle & CBRS_BORDER_ANY))
		return;

	// prepare for dark lines
	ASSERT(rect.top == 0 && rect.left == 0);

	COLORREF clr=GetSysColor(COLOR_3DSHADOW);
	if(dwStyle&CBRS_BORDER_RIGHT)
		pDC->FillSolidRect(rect.right-1,0,rect.right,rect.bottom,clr); //right
	if(dwStyle&CBRS_BORDER_BOTTOM)
		pDC->FillSolidRect(0,rect.bottom-1,rect.right,rect.bottom,clr); //bottom

	clr=GetSysColor(COLOR_3DHIGHLIGHT);
	if(dwStyle&CBRS_BORDER_TOP)
		pDC->FillSolidRect(0,0,rect.right,1,clr); //top
	if(dwStyle&CBRS_BORDER_LEFT)
		pDC->FillSolidRect(0,0,1,rect.bottom,clr); //left

	if(dwStyle&CBRS_BORDER_TOP)
		rect.top++;
	if(dwStyle&CBRS_BORDER_RIGHT)
		rect.right--;
	if(dwStyle&CBRS_BORDER_BOTTOM)
		rect.bottom--;
	if(dwStyle&CBRS_BORDER_LEFT)
		rect.left++;
}

// Because buttons are transparent, we need to repaint the background
void CNGenericToolBar::RepaintBackground()
{
     // get parent window (there should be one)
     CWnd* pParent = GetParent();
     if (pParent)
	 {
          // get rect for this toolbar
          CRect rw; GetWindowRect(&rw);
          // convert rect to parent coords
          CRect rc = rw; pParent->ScreenToClient(&rc);
          // invalidate this part of parent
          pParent->InvalidateRect(&rc);
          // now do all the other toolbars (etc) that belong to the parent
          for (CWnd* pSibling = pParent->GetWindow(GW_CHILD); pSibling; pSibling = pSibling->GetNextWindow(GW_HWNDNEXT))
		  {
               // but do not draw ourselves
               if (pSibling == this) continue;
               // convert rect to siblings coords
               CRect rc = rw; pSibling->ScreenToClient(&rc);
               // invalidate this part of sibling
               pSibling->InvalidateRect(&rc);
          }
     }
}

// Draw the separators in the client area
void CNGenericToolBar::DrawSeparators()
{
     // get a dc for the client area
     CClientDC dc(this);
     // draw the separators on it
     DrawSeparators(&dc);
}

// Draw the separators
void CNGenericToolBar::DrawSeparators(CClientDC* pDC)
{
     // horizontal vs vertical
     bool ishorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
     // get number of buttons
     int nIndexMax = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
     int nIndex;
     // try each button
     for (nIndex = 0; nIndex < nIndexMax; nIndex++)
	 {
          UINT dwStyle = GetButtonStyle(nIndex);
          UINT wStyle = LOWORD(dwStyle);
          // if it is a separator
          if (wStyle == TBBS_SEPARATOR)
		  {
               // get it's rectangle and width
               CRect rect;
               GetItemRect(nIndex,rect);
               // if small enough to be a true separator
               int w = rect.Width();
               if (w <= 8)
			   {
                    if (ishorz)
					{
                         // draw the separator bar in the middle
                         CRect rectbar = rect;
                         int x = (rectbar.left+rectbar.right)/2;
                         rectbar.left = x-1; rectbar.right = x+1;
						 rectbar.top++;
						 rectbar.bottom++;
                         pDC->Draw3dRect(rectbar,::GetSysColor(COLOR_3DSHADOW),::GetSysColor(COLOR_3DHILIGHT));
                    }
					else
					{
                         // draw the separator bar in the middle
                         CRect rectbar = rect;
                         rectbar.left = rectbar.left - m_sizeButton.cx;
                         rectbar.right = rectbar.left + m_sizeButton.cx;
                         rectbar.top = rectbar.bottom+1;
                         rectbar.bottom = rectbar.top+3;
                         int y = (rectbar.top+rectbar.bottom)/2;
                         rectbar.top = y-1; rectbar.bottom = y+1;
                         pDC->Draw3dRect(rectbar,::GetSysColor(COLOR_3DSHADOW),::GetSysColor(COLOR_3DHILIGHT));
                    }
               }
          }
     }
}

// Because buttons are transparent, we need to repaint background if style changes
void CNGenericToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
     static CUIntArray styles;
     // get the number of buttons
     int nIndexMax = (int)DefWindowProc(TB_BUTTONCOUNT, 0, 0);
     int nIndex;
     // save styles
     for (nIndex = 0; nIndex < nIndexMax; nIndex++)
	 {
          UINT dwStyle = GetButtonStyle(nIndex);
          styles.SetAtGrow(nIndex,dwStyle);
     }
     // do base class processing
     CToolBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
     // make checked button appear pushed in
     for (nIndex = 0; nIndex < nIndexMax; nIndex++)
	 {
          UINT dwStyle = GetButtonStyle(nIndex);
          if (dwStyle & TBBS_DISABLED)
		  {
               // don't touch if disabled (avoids flicker)
          } else if (dwStyle & TBBS_CHECKBOX)
		  {
               UINT dwStyleWas = dwStyle;
               // if checked, make it pressed, else not pressed
               if (dwStyle & TBBS_CHECKED)
			   {
                    dwStyle |= TBBS_PRESSED;
               } else if (!(styles[nIndex]&TBBS_CHECKED) && (styles[nIndex]&TBBS_PRESSED))
			   {
                    dwStyle |= TBBS_PRESSED;
               } else
			   {
                    dwStyle &= ~TBBS_PRESSED;
               }
               // set new style if changed
               if (dwStyleWas != dwStyle) SetButtonStyle(nIndex,dwStyle);
          }
     }
     // check for changes to style (buttons presssed/released)
     for (nIndex = 0; nIndex < nIndexMax; nIndex++)
	 {
          UINT dwStyle = GetButtonStyle(nIndex);
          if (styles[nIndex] != dwStyle)
		  {
               // repaint whole toolbar (not just this button)
               Invalidate();
               // no need to check any more
               break;
          }
     }
}

// Because buttons are transparent, we need to repaint background on size or move
void CNGenericToolBar::OnWindowPosChanging(LPWINDOWPOS lpwp)
{
     // default processing
     CToolBar::OnWindowPosChanging(lpwp);
     RepaintBackground();
}

// Paint the toolbar
void CNGenericToolBar::OnPaint()
{
     // standard toolbar
     CToolBar::OnPaint();
     // erase the background
     EraseNonClient(FALSE);
     // plus separators
     DrawSeparators();
}

// Paint the non-client area - copied from MFC implementatios
void CNGenericToolBar::OnNcPaint()
{
     //   EraseNonClient(); don't do it here
}

UINT CNGenericToolBar::OnNcHitTest(CPoint point) 
{
	CPoint pt(point);
	CRect wRect;

	GetWindowRect(wRect);
	pt.x-=wRect.left;
	pt.y-=wRect.top;

	// If SysMenu icon is visible, hittest it specially
	if(m_bSysMenuIcon && m_rectSysMenu.PtInRect(pt))
	{
		OnOverSysMenu();
		return HTSYSMENU;
	}

	return CToolBar::OnNcHitTest(point);
}

BOOL CNGenericToolBar::GenericToolBarModifyStyle(DWORD dwRemove, DWORD dwAdd)
{
	DWORD dwStyle = m_dwGenericToolBarStyle;
	DWORD dwNewStyle = (dwStyle & ~dwRemove) | dwAdd;
	if (dwStyle == dwNewStyle)
		return FALSE;

	m_dwGenericToolBarStyle = dwNewStyle;
	return TRUE;
}
