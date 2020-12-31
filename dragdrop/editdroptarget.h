/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  1/2001
**************************************************************************/
#ifndef __DROPTARGET_H__
#define __DROPTARGET_H__

#include "DragDropImpl.h"

class CEditDropTarget : public CIDropTarget
{
public:
	CEditDropTarget(HWND hTargetWnd):CIDropTarget(hTargetWnd){}	
	
	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect)
	{
		if(pFmtEtc->cfFormat == CF_TEXT && medium.tymed == TYMED_ISTREAM)
		{
			if(medium.pstm != NULL)
			{
				// this is a MESS and a better code is REQUIRED!
				// unfortunately you can't rely on STAT to be supported by all streams
				// so you can't get the size in advance
				//maybe it's better to use GetHGlobalFromStream
				const int BUF_SIZE = 10000;
				TCHAR buff[BUF_SIZE+1];
				ULONG cbRead=0;
				HRESULT hr = medium.pstm->Read(buff, BUF_SIZE, &cbRead);
				if( SUCCEEDED(hr) && cbRead > 0 && cbRead < BUF_SIZE)
				{
					buff[cbRead]=0;
					int nLen = ::SendMessage(m_hTargetWnd, WM_GETTEXTLENGTH, 0, 0);
					::SendMessage(m_hTargetWnd, EM_SETSEL, nLen, -1);
					::SendMessage(m_hTargetWnd, EM_REPLACESEL, TRUE, (LPARAM)buff);
				}
				else
					for(;(hr==S_OK && cbRead >0) && SUCCEEDED(hr) ;)
					{
						buff[cbRead]=0;
						int nLen = ::SendMessage(m_hTargetWnd, WM_GETTEXTLENGTH, 0, 0);
						::SendMessage(m_hTargetWnd, EM_SETSEL, nLen, -1);
						::SendMessage(m_hTargetWnd, EM_REPLACESEL, TRUE, (LPARAM)buff);
						cbRead=0;
						hr = medium.pstm->Read(buff, BUF_SIZE, &cbRead);
					}
			}
		}
		if(pFmtEtc->cfFormat == CF_TEXT && medium.tymed == TYMED_HGLOBAL)
		{
			TCHAR* pStr = (TCHAR*)GlobalLock(medium.hGlobal);
			if(pStr != NULL)
			{
				int nLen = ::SendMessage(m_hTargetWnd, WM_GETTEXTLENGTH, 0, 0);
				::SendMessage(m_hTargetWnd, EM_SETSEL, nLen, -1);
				::SendMessage(m_hTargetWnd, EM_REPLACESEL, TRUE, (LPARAM)pStr);
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
				int nLen = ::SendMessage(m_hTargetWnd, WM_GETTEXTLENGTH, 0, 0);
				::SendMessage(m_hTargetWnd, EM_SETSEL, nLen, -1);
				::SendMessage(m_hTargetWnd, EM_REPLACESEL, TRUE, (LPARAM)szFileName);
				}  
				//DragFinish(hDrop); // base class calls ReleaseStgMedium
			}
			GlobalUnlock(medium.hGlobal);
		}
		return true; //let base free the medium
	}

};
#endif //__DROPTARGET_H__