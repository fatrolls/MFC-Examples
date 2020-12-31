// NMDIClient.cpp : implementation file
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
#include "NMDIClient.h"
#include "NGenericMenu.h"
#include "NMDIMenuFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNMDIClient

CNMDIClient::CNMDIClient(CNGenericMenu* pMenu)
{
	m_pMenu=pMenu;
}

CNMDIClient::~CNMDIClient()
{
}


BEGIN_MESSAGE_MAP(CNMDIClient, CWnd)
	//{{AFX_MSG_MAP(CNMDIClient)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MDISETMENU,OnSetMenu)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNMDIClient message handlers

LRESULT CNMDIClient::OnSetMenu(WPARAM wParam, LPARAM lParam)
{
	if(wParam) m_pMenu->SetMenu((HMENU)wParam);
	else m_pMenu->SetMenu(((CNMDIMenuFrameWnd*)GetParentFrame())->m_hDefaultMenu);
	return DefWindowProc(WM_MDISETMENU,NULL,lParam);
}


void CNMDIClient::PostNcDestroy() 
{
	CWnd::PostNcDestroy();
	delete this;
}

