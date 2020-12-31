// NGenericMenu.cpp: implementation of the CNGenericMenu class.
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
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "afxpriv.h"
#include "NGenericMenu.h"
#include "NGenericPopup.h"
#include "NMDIClient.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CNGenericMenu,CNGenericToolBar)

BEGIN_MESSAGE_MAP(CNGenericMenu,CNGenericToolBar)
	//{{AFX_MSG_MAP(CNGenericMenu)
	ON_WM_NCPAINT()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
	ON_MESSAGE_VOID(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_NOTIFY_REFLECT(TBN_DROPDOWN,OnDropDown)
	ON_NOTIFY_REFLECT(TBN_HOTITEMCHANGE,OnHotChange)
	ON_UPDATE_COMMAND_UI_RANGE(65000,65100,OnMenuUpdate)
	ON_MESSAGE(WM_MENU_DISMISS, OnDismiss)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNGenericMenu::CNGenericMenu()
{
	m_bHasBitmaps=FALSE;
	m_bItemDropped=FALSE;
	m_bForceText=TRUE;
	m_pParent=NULL;
	m_hMenu=NULL;
	m_bSysMenuIcon=FALSE;
}

CNGenericMenu::~CNGenericMenu()
{

}

BOOL CNGenericMenu::Create(CFrameWnd* pParent)
{
	m_pParent=pParent;
	m_hMenu=NULL;
	if(!CNGenericToolBar::CreateEx(pParent,TBSTYLE_FLAT|TBSTYLE_LIST|TBSTYLE_AUTOSIZE|TBSTYLE_TRANSPARENT|TBSTYLE_TOOLTIPS)) return FALSE;
	SetWindowText("Menu");
	SendMessage(TB_BUTTONSTRUCTSIZE,sizeof(TBBUTTON));
	SendMessage(TB_SETBITMAPSIZE,0,MAKELPARAM(0,0));
	return TRUE;
}

BOOL CNGenericMenu::SetMenu(HMENU hMenu)
{
	m_hMenu=hMenu;
	if(!hMenu) return FALSE;
	CToolBarCtrl* pCtrl=&GetToolBarCtrl();
	CMenu* pMenu=CMenu::FromHandle(hMenu);
	int nCount=pMenu->GetMenuItemCount();
	int* idString=new int[nCount];
	TBBUTTON* pTB=new TBBUTTON[nCount];
	int n;
	char tmp[65];
	LPCTSTR q;

	m_accelList.SetSize(0);

	CFrameWnd* pChildFrame=m_pParent->GetActiveFrame();
	if(pChildFrame && pChildFrame!=m_pParent)
	{
		m_hSysMenuIcon=(HICON)GetClassLong(*pChildFrame,GCL_HICONSM);
	}

	for(n=0; n<nCount; n++)
	{
		pMenu->GetMenuString(n,tmp,64,MF_BYPOSITION);
		tmp[strlen(tmp)+1]='\0';
		idString[n]=pCtrl->AddStrings(tmp);
		for(q=tmp; *q; q++)
		{
			if(*q=='&')
			{
				int s=m_accelList.GetSize();
				m_accelList.SetSize(s+1);
				m_accelList[s].nKey=toupper(*(q+1));
				m_accelList[s].nId=65000+n;
				break;
			}
		}
		memset(&pTB[n],0,sizeof(TBBUTTON));
		pTB[n].iBitmap=1;
		pTB[n].idCommand=65000+n;
		pTB[n].fsState=TBSTATE_ENABLED;
		pTB[n].fsStyle=TBSTYLE_BUTTON|TBSTYLE_DROPDOWN|TBSTYLE_AUTOSIZE;
		pTB[n].iString=idString[n];
	}

	while(pCtrl->DeleteButton(0))
		;

	pCtrl->AddButtons(nCount,pTB);

	delete []idString;
	delete []pTB;

	RecalcSize();

	return TRUE;
}

void CNGenericMenu::OnDropDown(NMHDR * pNotifyStruct, LRESULT* result)
{
	LPNMTOOLBAR lpnmtb = (LPNMTOOLBAR)pNotifyStruct;

	ShowDropDown(FALSE,lpnmtb->iItem);
	*result=TBDDRET_DEFAULT;
}

void CNGenericMenu::ShowDropDown(BOOL bFromKey, int iItem)
{
	HMENU hPopup;
	CRect rect;
	CWnd* pParent;

	hPopup=*m_pParent->GetActiveFrame()->GetSystemMenu(FALSE);
	if(!m_bItemDropped)
	{
		if(iItem==-1)
			m_pParent->GetActiveFrame()->SendMessage(WM_INITMENU,(WPARAM)hPopup);
		else
			m_pParent->SendMessage(WM_INITMENU,(WPARAM)m_hMenu);
	}
	else
	{
		if(m_iItem==-1 && iItem!=-1)
			m_pParent->SendMessage(WM_INITMENU,(WPARAM)m_hMenu);
		else if(m_iItem!=-1 && iItem==-1)
			m_pParent->GetActiveFrame()->SendMessage(WM_INITMENU,(WPARAM)hPopup);

		if(m_iItem!=-1) SendMessage(TB_SETSTATE,m_iItem,TBSTATE_ENABLED);
	}
	m_iItem=iItem;
	m_bItemDropped=TRUE;

	if(iItem!=-1) SendMessage(TB_SETSTATE,iItem,TBSTATE_ENABLED|TBSTATE_PRESSED);

	if(iItem!=-1)
	{
		hPopup=::GetSubMenu(m_hMenu,iItem-65000);
		GetItemRect(iItem-65000,rect);
		ClientToScreen(rect);
	}
	else
	{
		CRect wr;

		GetWindowRect(wr);
		rect=m_rectSysMenu;
		rect.OffsetRect(wr.left,wr.top);
	}

	if(iItem!=-1)
	{
		pParent=m_pParent;
		pParent->SendMessage(WM_INITMENUPOPUP,(WPARAM)hPopup,iItem-65000);
	}
	else
	{
		pParent=m_pParent->GetActiveFrame();
		pParent->SendMessage(WM_INITMENUPOPUP,(WPARAM)hPopup,0);
	}
	
	if(m_dwStyle & CBRS_ALIGN_LEFT)
		m_popup.ShowMenu(POP_MENU_LEFT,bFromKey,this,rect.right+1,rect.top,m_pParent,hPopup);
	else if(m_dwStyle & CBRS_ALIGN_RIGHT)
		m_popup.ShowMenu(POP_MENU_RIGHT,bFromKey,this,rect.left,rect.top,m_pParent,hPopup);
	else if(m_dwStyle & CBRS_ALIGN_TOP)
		m_popup.ShowMenu(POP_MENU_TOP,bFromKey,this,rect.left,rect.bottom+1,m_pParent,hPopup);
	else if(m_dwStyle & CBRS_ALIGN_BOTTOM)
		m_popup.ShowMenu(POP_MENU_BOTTOM,bFromKey,this,rect.left,rect.top,m_pParent,hPopup);
}

void CNGenericMenu::OnHotChange(NMHDR * pNotifyStruct, LRESULT* result)
{
	LPNMTBHOTITEM lpnmtb = (LPNMTBHOTITEM)pNotifyStruct;

	if(m_bItemDropped && lpnmtb->idNew!=m_iItem)
	{
		if(lpnmtb->idNew)
			ShowDropDown(FALSE,lpnmtb->idNew);
		else
		{
			CPoint pt;
			CRect r;

			GetCursorPos(&pt);
			GetWindowRect(r);
			pt.x-=r.left;
			pt.y-=r.top;
			if(m_bSysMenuIcon && m_rectSysMenu.PtInRect(pt))
				ShowDropDown(FALSE,-1);
		}
	}

	*result=0;
}

void CNGenericMenu::OnOverSysMenu()
{
	if(m_bItemDropped && m_iItem!=-1)
		ShowDropDown(FALSE,-1);
}

void CNGenericMenu::OnMenuUpdate(CCmdUI* pCmd)
{
	if(!m_hMenu) return;
	CMenu* pMenu=CMenu::FromHandle(m_hMenu);
	if(!pMenu) return;
	pCmd->Enable(pMenu->GetMenuState(pCmd->m_nID-65000,MF_DISABLED));
}

LRESULT CNGenericMenu::OnDismiss(WPARAM wParam, LPARAM lParam)
{
	if(m_bItemDropped)
	{
		if(m_iItem!=-1) SendMessage(TB_SETSTATE,m_iItem,TBSTATE_ENABLED);
	}
	m_iItem=0;
	m_bItemDropped=FALSE;
	return 0;
}

void CNGenericMenu::SubclassMDIClient(HWND hWndClient)
{
	CNMDIClient* pClient=new CNMDIClient(this);
	pClient->SubclassWindow(hWndClient);
}

BOOL CNGenericMenu::TranslateMenuChar(UINT nChar)
{
	for(int n=0; n<m_accelList.GetSize(); n++)
	{
		if(m_accelList[n].nKey==(UINT)toupper(nChar))
		{
			ShowDropDown(TRUE,m_accelList[n].nId);
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CNGenericMenu::KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_bItemDropped)
	{
		if(nChar==VK_LEFT)
		{
			if(m_iItem>65000)
				ShowDropDown(TRUE,m_iItem-1);
			else if(m_iItem==-1)
				ShowDropDown(TRUE,65000+GetToolBarCtrl().GetButtonCount()-1);
			else
				ShowDropDown(TRUE,m_bSysMenuIcon?-1:65000+GetToolBarCtrl().GetButtonCount()-1);
		}
		if(nChar==VK_RIGHT)
		{
			if(m_iItem==-1)
				ShowDropDown(TRUE,65000);
			else if(m_iItem<65000+GetToolBarCtrl().GetButtonCount()-1)
				ShowDropDown(TRUE,m_iItem+1);
			else
				ShowDropDown(TRUE,m_bSysMenuIcon?-1:65000);
		}
	}

	return FALSE;
}

CSize CNGenericMenu::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	DWORD dwMode = LM_STRETCH;
	dwMode |= bHorz ? LM_HORZ : 0;

	return CalcLayout(dwMode);
}

void CNGenericMenu::OnNcPaint() 
{
	EraseNonClient(TRUE);
}


void CNGenericMenu::OnSysCommand(UINT nID, LPARAM lParam) 
{
	if(m_bSysMenuIcon)
	{
		switch(nID&0xfff0)
		{
		case SC_KEYMENU:
			ShowDropDown(TRUE,-1);
			break;
		case SC_MOUSEMENU:
			ShowDropDown(FALSE,-1);
			break;
		}
		m_pParent->GetActiveFrame()->PostMessage(WM_SYSCOMMAND,nID,lParam);
	}
}

void CNGenericMenu::OnIdleUpdateCmdUI()
{
	BOOL bSysMenuIcon=(m_pParent->GetActiveFrame()!=m_pParent && m_pParent->GetActiveFrame()->IsZoomed())?TRUE:FALSE;
	if(bSysMenuIcon!=m_bSysMenuIcon)
	{
		m_bSysMenuIcon=bSysMenuIcon;
		SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE|SWP_FRAMECHANGED);
	}
	CNGenericToolBar::OnIdleUpdateCmdUI(0,0);
}
