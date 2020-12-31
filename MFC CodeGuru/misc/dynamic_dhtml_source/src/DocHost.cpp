// DocHost.cpp: implementation of the CDocHostUIHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <mfcext.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDocHostUIHandler::CDocHostUIHandler()
{
	m_dwRefCount = 0;
}

CDocHostUIHandler::~CDocHostUIHandler()
{

}




HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ShowContextMenu( 
            /* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved)
{
	
	m_pBrowserView->OnContextMenu(*ppt);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetHostInfo( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo)
{
	pInfo->cbSize = sizeof(DOCHOSTUIINFO);
	pInfo->dwFlags = 1023; //All the flags
	pInfo->dwDoubleClick = DOCHOSTUIDBLCLK_DEFAULT ;
	
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ShowUI( 
    /* [in] */ DWORD dwID,
    /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
    /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
    /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
    /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::HideUI( void) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::UpdateUI( void) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::EnableModeless( 
    /* [in] */ BOOL fEnable) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::OnDocWindowActivate( 
    /* [in] */ BOOL fActivate) 
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CDocHostUIHandler::OnFrameWindowActivate( 
    /* [in] */ BOOL fActivate) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::ResizeBorder( 
    /* [in] */ LPCRECT prcBorder,
    /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
    /* [in] */ BOOL fRameWindow) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::TranslateAccelerator( 
    /* [in] */ LPMSG lpMsg,
    /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
    /* [in] */ DWORD nCmdID) 
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetOptionKeyPath( 
    /* [out] */ LPOLESTR __RPC_FAR *pchKey,
    /* [in] */ DWORD dw) 
{
	pchKey = NULL;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetDropTarget( 
    /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
    /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget) 
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::GetExternal( 
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch) 
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::TranslateUrl( 
    /* [in] */ DWORD dwTranslate,
    /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
    /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut) 
{
	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::FilterDataObject( 
    /* [in] */ IDataObject __RPC_FAR *pDO,
    /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet) 
{

	return S_FALSE;
}

HRESULT STDMETHODCALLTYPE CDocHostUIHandler::QueryInterface(REFIID iid, void** ppvObject)
{
	if (IsEqualIID(iid, IID_IDocHostUIHandler))
	{
		*ppvObject = (IDocHostUIHandler*)this;
		return S_OK;
	}
	
	if (IsEqualIID(iid, IID_IUnknown))
	{
		*ppvObject = this;
		return S_OK;
	}
	
	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE CDocHostUIHandler::AddRef()
{
	m_dwRefCount++;
	return m_dwRefCount;
}


ULONG STDMETHODCALLTYPE CDocHostUIHandler::Release()
{
	m_dwRefCount--;
	
	if (m_dwRefCount == 0)
	{
		delete this;
		return 0;
	}
	
	return m_dwRefCount;
}
