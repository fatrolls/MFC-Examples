// NMDIGenericMenu.cpp: implementation of the CNGenericMenu class.
//
/*
Copyright (C) 1998 George H. Stahl (GStahl@VipMail.Com)

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
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CNMDIGenericMenu,CNGenericMenu)
void CNMDIGenericMenu::SubclassMDIClient(HWND hWndClient)
{
	CNMDIClient* pClient=new CNMDIClient(this);
	pClient->SubclassWindow(hWndClient);
}
