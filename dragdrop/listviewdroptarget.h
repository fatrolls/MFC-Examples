/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  1/2001
**************************************************************************/
#ifndef __LISTVIEWDROPTARGET_H__
#define __LISTVIEWDROPTARGET_H__

#include "DragDropImpl.h"

class CListViewDropTarget : public CIDropTarget
{
public:
	CListViewDropTarget(HWND hTargetWnd):CIDropTarget(hTargetWnd){}	
	
	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect)
	{
		if(pFmtEtc->cfFormat == CF_TEXT && medium.tymed == TYMED_HGLOBAL)
		{
			TCHAR* pStr = (TCHAR*)GlobalLock(medium.hGlobal);
			if(pStr != NULL)
			{
				LVITEM lvitem={0};
				lvitem.iItem = 0;
				lvitem.mask = LVIF_TEXT;
				lvitem.pszText = pStr;
				ListView_InsertItem(m_hTargetWnd, &lvitem);
			}
			GlobalUnlock(medium.hGlobal);
		}
		if(pFmtEtc->cfFormat == CF_HDROP && medium.tymed == TYMED_HGLOBAL)
		{
			HDROP hDrop = (HDROP)GlobalLock(medium.hGlobal);
			if(hDrop != NULL)
			{
				TCHAR szFileName[MAX_PATH];

				UINT cFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); 
				for(UINT i = 0; i < cFiles; ++i)
				{
				DragQueryFile(hDrop, i, szFileName, sizeof(szFileName)); 
				LVITEM lvitem={0};
				lvitem.iItem = 0;
				lvitem.mask = LVIF_TEXT;
				lvitem.pszText = szFileName;
				ListView_InsertItem(m_hTargetWnd, &lvitem);
				UpdateWindow(m_hTargetWnd);
				}  
				//DragFinish(hDrop); // base class calls ReleaseStgMedium
			}
			GlobalUnlock(medium.hGlobal);
		}
		return true; //let base free the medium
	}

};

#endif //__LISTVIEWDROPTARGET_H__