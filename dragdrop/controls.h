/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  1/2001
**************************************************************************/
//controls.h
#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include "editdroptarget.h"
#include "listviewdroptarget.h"
#include "staticdroptarget.h"
#include "treedroptarget.h"

class CEditBox : public CWindowImpl<CEditBox, WTL::CEdit>, public WTL::CEditCommands<CEditBox>
{
	CIDropTarget* m_pDropTarget;
public:
	CEditBox():m_pDropTarget(NULL){}

	BEGIN_MSG_MAP(CEditBox)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP_ALT(CEditCommands<CEditBox>, 1)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RevokeDragDrop(m_hWnd); //calls release
		m_pDropTarget=NULL;
		return 0;
	}

	bool InitDragDrop()
	{
			m_pDropTarget = new CEditDropTarget(m_hWnd);
			if(m_pDropTarget == NULL)
				return false;
			m_pDropTarget->AddRef();

			if(FAILED(RegisterDragDrop(m_hWnd,m_pDropTarget))) //calls addref
			{
				m_pDropTarget = NULL;
				return false;
			}
			else
				m_pDropTarget->Release(); //i decided to AddRef explicitly after new

			FORMATETC ftetc={0};
			ftetc.cfFormat = CF_TEXT;
			ftetc.dwAspect = DVASPECT_CONTENT;
			ftetc.lindex = -1;
			ftetc.tymed = TYMED_ISTREAM;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.tymed = TYMED_HGLOBAL;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat=CF_HDROP;
			m_pDropTarget->AddSuportedFormat(ftetc);
		return true;
	}


};

class CTreeBox : public CWindowImpl<CTreeBox, WTL::CTreeViewCtrl>
{
	CIDropTarget* m_pDropTarget;
public:
	BEGIN_MSG_MAP(CTreeBox)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		REFLECTED_NOTIFY_HANDLER(IDC_TREE1, TVN_BEGINDRAG, OnBegindrag)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()
	
	CTreeBox():m_pDropTarget(NULL){}
	
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RevokeDragDrop(m_hWnd); //calls release
		m_pDropTarget=NULL;
		return 0;
	}

	LRESULT OnBegindrag(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		NMTREEVIEW* pnmtv = (NMTREEVIEW*)pnmh;
		USES_CONVERSION;
		CComBSTR bstr;
		GetItemText(pnmtv->itemNew.hItem, bstr.m_str);
		
		CIDropSource* pdsrc = new CIDropSource;
		if(pdsrc == NULL)
			return 0;
		pdsrc->AddRef();

		CIDataObject* pdobj = new CIDataObject(pdsrc);
		if(pdobj == NULL)
			return 0;
		pdobj->AddRef();

		FORMATETC fmtetc = {0};
		fmtetc.cfFormat = CF_TEXT;
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.tymed = TYMED_HGLOBAL;

		STGMEDIUM medium = {0};
		medium.tymed = TYMED_HGLOBAL;
		TCHAR* str = OLE2T(bstr.m_str);

		medium.hGlobal = GlobalAlloc(GMEM_MOVEABLE, strlen(str)+1); //for NULL
		TCHAR* pMem = (TCHAR*)GlobalLock(medium.hGlobal);
		strcpy(pMem,str);
		GlobalUnlock(medium.hGlobal);

		pdobj->SetData(&fmtetc,&medium,TRUE);
		
		CDragSourceHelper dragSrcHelper;
		// get drag image from the window through DI_GETDRAGIMAGE (treeview seems to already support it)
		dragSrcHelper.InitializeFromWindow(m_hWnd, pnmtv->ptDrag, pdobj);
		DWORD dwEffect;
		HRESULT hr = ::DoDragDrop(pdobj, pdsrc, DROPEFFECT_COPY, &dwEffect);
		pdsrc->Release();
		pdobj->Release();
		return 0;
	}

	bool InitDragDrop()
	{
			m_pDropTarget = new CTreeDropTarget(m_hWnd);
			if(m_pDropTarget == NULL)
				return false;
			m_pDropTarget->AddRef();

			if(FAILED(RegisterDragDrop(m_hWnd,m_pDropTarget))) //calls addref
			{
				m_pDropTarget = NULL;
				return false;
			}
			else
				m_pDropTarget->Release(); //i decided to AddRef explicitly after new

			FORMATETC ftetc={0};
			ftetc.cfFormat = CF_TEXT;
			ftetc.dwAspect = DVASPECT_CONTENT;
			ftetc.lindex = -1;
			ftetc.tymed = TYMED_HGLOBAL;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat=CF_HDROP;
			m_pDropTarget->AddSuportedFormat(ftetc);
		return true;
	}
};

class CStaticBox : public CWindowImpl<CStatic,WTL::CStatic>
{
	CIDropTarget* m_pDropTarget;
	bool m_bDragMode;
public:
	BEGIN_MSG_MAP(CStaticBox)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	CStaticBox():m_bDragMode(false), m_pDropTarget(NULL){}
	
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RevokeDragDrop(m_hWnd); //calls release
		m_pDropTarget=NULL;
		return 0;
	}

	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CMenu menu;
		if(!menu.CreatePopupMenu())
			return 0;
		menu.AppendMenu(MF_STRING, 1, "Copy");
		int nCmd = menu.TrackPopupMenu(TPM_RETURNCMD,LOWORD(lParam),HIWORD(lParam),m_hWnd);
		if(nCmd == 1)
		{
			CIDataObject* pdobj = new CIDataObject(NULL);
			if(pdobj == NULL)
				return 0;
			pdobj->AddRef();
			BITMAP bmap;
			HBITMAP hBitmap = (HBITMAP)OleDuplicateData(GetBitmap(), CF_BITMAP, NULL);
			GetObject(hBitmap, sizeof(BITMAP), &bmap);
			RECT rc={0,0,bmap.bmWidth,bmap.bmHeight};
			HDC hdc = GetDC();
			FORMATETC fmtetc = {0};
			STGMEDIUM medium = {0};
			fmtetc.dwAspect = DVASPECT_CONTENT;
			fmtetc.lindex = -1;
			fmtetc.cfFormat = CF_ENHMETAFILE;
			fmtetc.tymed = TYMED_ENHMF;
			HDC hMetaDC = CreateEnhMetaFile(hdc, NULL, NULL, NULL);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HGDIOBJ hOldBmp = ::SelectObject(hdcMem, hBitmap);
			::BitBlt(hMetaDC, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
			::SelectObject(hdcMem, hOldBmp);
			medium.hEnhMetaFile = CloseEnhMetaFile(hMetaDC);
			DeleteDC(hdcMem);
			ReleaseDC(hdc);
			medium.tymed = TYMED_ENHMF;
			pdobj->SetData(&fmtetc,&medium,TRUE);
			OleSetClipboard(pdobj);
			OleFlushClipboard(); //render the data
			pdobj->Release();
		}
		return 0;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_bDragMode = true;
		return 0;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(m_bDragMode && wParam == MK_LBUTTON)
		{
			CIDropSource* pdsrc = new CIDropSource;
			if(pdsrc == NULL)
				return 0;
			pdsrc->AddRef();

			CIDataObject* pdobj = new CIDataObject(pdsrc);
			if(pdobj == NULL)
				return 0;
			pdobj->AddRef();

			FORMATETC fmtetc = {0};
			STGMEDIUM medium = {0};
			fmtetc.dwAspect = DVASPECT_CONTENT;
			fmtetc.lindex = -1;
			//////////////////////////////////////
			fmtetc.cfFormat = CF_BITMAP;
			fmtetc.tymed = TYMED_GDI;			
			medium.tymed = TYMED_GDI;
			HBITMAP hBitmap = (HBITMAP)OleDuplicateData(GetBitmap(), fmtetc.cfFormat, NULL);
			medium.hBitmap = hBitmap;
			pdobj->SetData(&fmtetc,&medium,FALSE);
			//////////////////////////////////////
			BITMAP bmap;
			GetObject(hBitmap, sizeof(BITMAP), &bmap);
			RECT rc={0,0,bmap.bmWidth,bmap.bmHeight};
			HDC hdc = GetDC();
			fmtetc.cfFormat = CF_ENHMETAFILE;
			fmtetc.tymed = TYMED_ENHMF;
			HDC hMetaDC = CreateEnhMetaFile(hdc, NULL, NULL, NULL);
			HDC hdcMem = CreateCompatibleDC(hdc);
			HGDIOBJ hOldBmp = ::SelectObject(hdcMem, hBitmap);
			::BitBlt(hMetaDC, 0, 0, rc.right, rc.bottom, hdcMem, 0, 0, SRCCOPY);
			::SelectObject(hdcMem, hOldBmp);
			medium.hEnhMetaFile = CloseEnhMetaFile(hMetaDC);
			DeleteDC(hdcMem);
			ReleaseDC(hdc);
			medium.tymed = TYMED_ENHMF;
			pdobj->SetData(&fmtetc,&medium,TRUE);
			//////////////////////////////////////
			CDragSourceHelper dragSrcHelper;
			POINT pt={LOWORD(lParam), HIWORD(lParam)};
			//rc is off because i used static box with style where bmp doesn't take whole window
			dragSrcHelper.InitializeFromBitmap(hBitmap, pt, rc, pdobj); //will own the bmp
			DWORD dwEffect;
			HRESULT hr = ::DoDragDrop(pdobj, pdsrc, DROPEFFECT_COPY|DROPEFFECT_MOVE, &dwEffect);
			pdsrc->Release();
			pdobj->Release();
			m_bDragMode = false;
		}
		return 0;
	}
	
	bool InitDragDrop()
	{
			m_pDropTarget = new CStaticDropTarget(m_hWnd);
			if(m_pDropTarget == NULL)
				return false;
			m_pDropTarget->AddRef();

			if(FAILED(RegisterDragDrop(m_hWnd,m_pDropTarget))) //calls addref
			{
				m_pDropTarget = NULL;
				return false;
			}
			else
				m_pDropTarget->Release(); //i decided to AddRef explicitly after new

			FORMATETC ftetc={0};
			ftetc.cfFormat = CF_BITMAP;
			ftetc.dwAspect = DVASPECT_CONTENT;
			ftetc.lindex = -1;
			ftetc.tymed = TYMED_GDI;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat = CF_DIB;
			ftetc.tymed = TYMED_HGLOBAL;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat = CF_HDROP;
			ftetc.tymed = TYMED_HGLOBAL;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat = CF_ENHMETAFILE;
			ftetc.tymed = TYMED_ENHMF;
			m_pDropTarget->AddSuportedFormat(ftetc);
		return true;
	}
};

class CListViewBox : public CWindowImpl<CListViewBox,WTL::CListViewCtrl>
{
	CIDropTarget* m_pDropTarget;
public:	
	BEGIN_MSG_MAP(CTreeBox)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		REFLECTED_NOTIFY_HANDLER(IDC_LISTVIEW, LVN_BEGINDRAG, OnBegindragListview)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	CListViewBox():m_pDropTarget(NULL){}

	bool InitDragDrop()
	{
			m_pDropTarget = new CListViewDropTarget(m_hWnd);
			if(m_pDropTarget == NULL)
				return false;
			m_pDropTarget->AddRef();

			if(FAILED(RegisterDragDrop(m_hWnd,m_pDropTarget))) //calls addref
			{
				m_pDropTarget = NULL;
				return false;
			}
			else
				m_pDropTarget->Release(); //i decided to AddRef explicitly after new

			FORMATETC ftetc={0};
			ftetc.cfFormat = CF_TEXT;
			ftetc.dwAspect = DVASPECT_CONTENT;
			ftetc.lindex = -1;
			ftetc.tymed = TYMED_HGLOBAL;
			m_pDropTarget->AddSuportedFormat(ftetc);
			ftetc.cfFormat=CF_HDROP;
			m_pDropTarget->AddSuportedFormat(ftetc);
		return true;
	}

	LRESULT OnBegindragListview(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
	{
		USES_CONVERSION;
		NMLISTVIEW* pnmlv = (NMLISTVIEW*)pnmh;
		CComBSTR bstr;
		GetItemText(pnmlv->iItem, 0, bstr.m_str);
		
		CIDropSource* pdsrc = new CIDropSource;
		if(pdsrc == NULL)
			return 0;
		pdsrc->AddRef();

		CIDataObject* pdobj = new CIDataObject(pdsrc);
		if(pdobj == NULL)
			return 0;
		pdobj->AddRef();

		FORMATETC fmtetc = {0};
		fmtetc.cfFormat = CF_TEXT;
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.tymed = TYMED_HGLOBAL;

		STGMEDIUM medium = {0};
		medium.tymed = TYMED_HGLOBAL;
		TCHAR* str = OLE2T(bstr.m_str);
		
		medium.hGlobal = GlobalAlloc(GMEM_MOVEABLE, strlen(str)+1); //for NULL
		TCHAR* pMem = (TCHAR*)GlobalLock(medium.hGlobal);
		strcpy(pMem,str);
		GlobalUnlock(medium.hGlobal);
		pdobj->SetData(&fmtetc,&medium,TRUE);
		/////////////////////////////////////////
		HRESULT hr;
		IStream* pStream;
		/*IStream* pStream;
		//ie5.0 API
		hr = SHCreateStreamOn("readme.txt",STGM_READ,&pStream);
		medium.pstm = pStream;
		fmtetc.tymed = TYMED_ISTREAM;
		medium.tymed = TYMED_ISTREAM;
		pdobj->SetData(&fmtetc,&medium,TRUE);*/
		/////////////////////////////////////////
		CreateStreamOnHGlobal(NULL, TRUE, &pStream);
		DWORD dwWritten;
		pStream->Write(str, strlen(str)+1, &dwWritten);
		LARGE_INTEGER dlibMove; dlibMove.QuadPart = 0;
		pStream->Seek(dlibMove,STREAM_SEEK_SET,NULL);
		medium.pstm = pStream;
		fmtetc.tymed = TYMED_ISTREAM;
		medium.tymed = TYMED_ISTREAM;
		pdobj->SetData(&fmtetc,&medium,TRUE);
		/////////////////////////////////////////
		
		CDragSourceHelper dragSrcHelper;
		if(1)	// get drag image from the window through DI_GETDRAGIMAGE (listview seems to already support it)
			dragSrcHelper.InitializeFromWindow(m_hWnd, pnmlv->ptAction, pdobj);
		else   // load drag image from bitmap
		{
		RECT rc;
		ListView_GetItemRect(m_hWnd, pnmlv->iItem, &rc, LVIR_SELECTBOUNDS);
		HBITMAP hBitmap = LoadBitmap(_Module.GetModuleInstance(), MAKEINTRESOURCE(IDB_DRAGIMG));
		dragSrcHelper.InitializeFromBitmap(hBitmap, pnmlv->ptAction, rc, pdobj);
		}
		DWORD dwEffect;
		hr = ::DoDragDrop(pdobj, pdsrc, DROPEFFECT_COPY, &dwEffect);
		pdsrc->Release();
		pdobj->Release();
		//ReleaseStgMedium(&medium); // SetData fRelease flag is set, so DataObject owns the data don't free the data
		return 0;
	}
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		RevokeDragDrop(m_hWnd); //calls release
		m_pDropTarget=NULL;
		return 0;
	}
};

#endif //__CONTROLS_H__