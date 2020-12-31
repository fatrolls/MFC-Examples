//=========================================================
//	TITLE:		Global 
//				for WinNT, MSVC 5.0, MFC 4.1
//				Copyright (C) Matrix Baltic Software
//				Vilnius, Lithuania
//	MODULE:		
//	PURPOSE:	
//
//	AUTHOR:		Audrius Vasiliauskas
// 
//	NOTES:		
//
//=========================================================


// NetworkTreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "NetworkTreeCtrl.h"

#ifndef WNET_ENUM_H
	#include "WNetEnum.h"
#endif

#ifndef APP_IDLE_H
	#include "AppIdle.h"
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetworkTreeCtrl

CNetworkTreeCtrl::CNetworkTreeCtrl()
{
}

CNetworkTreeCtrl::~CNetworkTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CNetworkTreeCtrl, CColorTreeCtrl)
	//{{AFX_MSG_MAP(CNetworkTreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetworkTreeCtrl message handlers
void CNetworkTreeCtrl::WNetEnum(LPNETRESOURCE lpNetResource, DWORD dwDeep,CTreeCursor &node)
{
	CWNetEnum wNetEnum;

	if(wNetEnum.Open(lpNetResource,dwDeep) != NO_ERROR)
		return;
	
	CheckMessageQueue(this);

	dwDeep ++;
	if(wNetEnum.Resource() == NO_ERROR)
	{
		int i;
		int count = wNetEnum;
		CTreeCursor cursor;

		for(i = 0;i < count;i ++)
		{
			CWNetResource data = wNetEnum[i];

			switch(data.dwDisplayType)
			{
			case RESOURCEDISPLAYTYPE_NETWORK:
				cursor = node.AddTail(data.RemoteName(),0,0);
				break;
			case RESOURCEDISPLAYTYPE_DOMAIN:
				cursor = node.AddTail(data.RemoteName(),1,1);
				break;
			case RESOURCEDISPLAYTYPE_SERVER:
				cursor = node.AddTail(data.RemoteName(),2,2);
				break;
			case RESOURCEDISPLAYTYPE_SHARE:
				if(data.IsPrint())
				{
					cursor = node.AddTail(data.RemoteName(),4,4);
				}
				else
				{
					cursor = node.AddTail(data.RemoteName(),3,3);
				}
				break;
			default:
				cursor = node.AddTail(data.RemoteName());
				break;
			}

			cursor.SetData(data.dwDisplayType);
			if(data.IsContainer())
			{
				WNetEnum(&data,dwDeep,cursor);
				if(!data.IsServer())
				{
					cursor.Expand();
				}
			}

		}
	}

	wNetEnum.Close();
}

void CNetworkTreeCtrl::Refresh()
{
	BeginWaitCursor(); // display the hourglass cursor

	SetRedraw(FALSE);
	DeleteAllItems();
	SetRedraw(TRUE);

	CTreeCursor root = GetRootItem();
	root.AddTail("Browsing Network ...");
	CheckMessageQueue();


	SetRedraw(FALSE);
	DeleteAllItems();
	WNetEnum(NULL,0,root);
	SetRedraw(TRUE);

	EndWaitCursor(); // remove the hourglass cursor
}
