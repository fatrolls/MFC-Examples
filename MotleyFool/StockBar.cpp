//StockBar.cpp : Implementation of CStockBar

//***************************************************************************//
//                                                                           //
//  This file was created using the DeskBand ATL Object Wizard 2.0           //
//  By Erik Thompson © 2001                                                  //
//  Email questions and comments to erikt@radbytes.com						 //
//                                                                           //
//***************************************************************************//

#include "stdafx.h"
#include <wchar.h>
#include "MotleyFool.h"
#include "StockBar.h"

const WCHAR TITLE_CStockBar[] = L"The Motley Fool";

/////////////////////////////////////////////////////////////////////////////
// CStockBar

CStockBar::CStockBar(): 
	m_dwBandID(0), 
	m_dwViewMode(0), 
	m_bShow(FALSE), 
	m_bEnterHelpMode(FALSE), 
	m_hWndParent(NULL), 
	m_pSite(NULL)
{
	m_ReflectWnd.GetToolBar().GetEditBox().SetBand(this);
}

BOOL CStockBar::RegisterAndCreateWindow()
{
	RECT rect;
	::GetClientRect(m_hWndParent, &rect);
	m_ReflectWnd.Create(m_hWndParent, rect, NULL, WS_CHILD);
	// The toolbar is the window that the host will be using so it is the window that is important.
	return m_ReflectWnd.GetToolBar().IsWindow();
}

// IDeskBand
STDMETHODIMP CStockBar::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
	m_dwBandID = dwBandID;
	m_dwViewMode = dwViewMode;

	if (pdbi)
	{
		if (pdbi->dwMask & DBIM_MINSIZE)
		{
			pdbi->ptMinSize.x = 250;
			pdbi->ptMinSize.y = 22;
		}
		if (pdbi->dwMask & DBIM_MAXSIZE)
		{
			pdbi->ptMaxSize.x = 0; // ignored
			pdbi->ptMaxSize.y = -1;	// width
		}
		if (pdbi->dwMask & DBIM_INTEGRAL)
		{
			pdbi->ptIntegral.x = 0; // ignored
			pdbi->ptIntegral.y = 0; // not sizeable
		}
		if (pdbi->dwMask & DBIM_ACTUAL)
		{
			pdbi->ptActual.x = 250;
			pdbi->ptActual.y = 22;
		}
		if (pdbi->dwMask & DBIM_TITLE)
		{
			wcscpy(pdbi->wszTitle, TITLE_CStockBar);
		}
		if (pdbi->dwMask & DBIM_BKCOLOR)
		{
			//Use the default background color by removing this flag.
			pdbi->dwMask &= ~DBIM_BKCOLOR;
		}
		if (pdbi->dwMask & DBIM_MODEFLAGS)
		{
			pdbi->dwModeFlags = DBIMF_VARIABLEHEIGHT;
		}
	}
	return S_OK;
}

// IOleWindow
STDMETHODIMP CStockBar::GetWindow(HWND* phwnd)
{
	HRESULT hr = S_OK;
	if (NULL == phwnd)
	{
		hr = E_INVALIDARG;
	}
	else
	{
		*phwnd = m_ReflectWnd.GetToolBar().m_hWnd;
	}
	return hr;
}

STDMETHODIMP CStockBar::ContextSensitiveHelp(BOOL fEnterMode)
{
	m_bEnterHelpMode = fEnterMode;
	return S_OK;
}

// IDockingWindow
STDMETHODIMP CStockBar::CloseDW(unsigned long dwReserved)
{
	ShowDW(FALSE);
	return S_OK;
}

STDMETHODIMP CStockBar::ResizeBorderDW(const RECT* prcBorder, IUnknown* punkToolbarSite, BOOL fReserved)
{
	// Not used by any band object.
	return E_NOTIMPL;
}

STDMETHODIMP CStockBar::ShowDW(BOOL fShow)
{
	m_bShow = fShow;
	m_ReflectWnd.GetToolBar().ShowWindow(m_bShow ? SW_SHOW : SW_HIDE);
	return S_OK;
}

// IObjectWithSite
STDMETHODIMP CStockBar::SetSite(IUnknown* pUnkSite)
{
//If a site is being held, release it.
	if(m_pSite)
	{
		m_ReflectWnd.GetToolBar().SetBrowser(NULL);
		m_pSite->Release();
		m_pSite = NULL;
	}

	//If punkSite is not NULL, a new site is being set.
	if(pUnkSite)
	{
		//Get the parent window.
		IOleWindow  *pOleWindow = NULL;

		m_hWndParent = NULL;

		if(SUCCEEDED(pUnkSite->QueryInterface(IID_IOleWindow, (LPVOID*)&pOleWindow)))
		{
			pOleWindow->GetWindow(&m_hWndParent);
			pOleWindow->Release();
		}

		if(!::IsWindow(m_hWndParent))
			return E_FAIL;

		if(!RegisterAndCreateWindow())
			return E_FAIL;

		//Get and keep the IInputObjectSite pointer.
		if(FAILED(pUnkSite->QueryInterface(IID_IInputObjectSite, (LPVOID*)&m_pSite)))
		{
			return E_FAIL;
		}  

		IWebBrowser2* s_pFrameWB = NULL;
		IOleCommandTarget* pCmdTarget = NULL;
		HRESULT hr = pUnkSite->QueryInterface(IID_IOleCommandTarget, (LPVOID*)&pCmdTarget);
		if (SUCCEEDED(hr))
		{
			IServiceProvider* pSP;
			hr = pCmdTarget->QueryInterface(IID_IServiceProvider, (LPVOID*)&pSP);

			pCmdTarget->Release();

			if (SUCCEEDED(hr))
			{
				hr = pSP->QueryService(SID_SWebBrowserApp, IID_IWebBrowser2, (LPVOID*)&s_pFrameWB);
				pSP->Release();
				_ASSERT(s_pFrameWB);
				m_ReflectWnd.GetToolBar().SetBrowser(s_pFrameWB);
				s_pFrameWB->Release();
			}
		}
	}
	return S_OK;
}

STDMETHODIMP CStockBar::GetSite(REFIID riid, void **ppvSite)
{
	*ppvSite = NULL;

	if(m_pSite)
	{
	   return m_pSite->QueryInterface(riid, ppvSite);
	}
	return E_FAIL;
}

void CStockBar::FocusChange(BOOL bHaveFocus)
{
	if (m_pSite)
	{
		IUnknown* pUnk = NULL;
		if (SUCCEEDED(QueryInterface(IID_IUnknown, (LPVOID*)&pUnk)) && pUnk != NULL)
		{
			m_pSite->OnFocusChangeIS(pUnk, bHaveFocus);
			pUnk->Release();
			pUnk = NULL;
		}
	}
}

STDMETHODIMP CStockBar::HasFocusIO(void)
{
	// if any of the windows in our toolbar have focus then return S_OK else S_FALSE.
	if (m_ReflectWnd.GetToolBar().m_hWnd == ::GetFocus())
		return S_OK;
	if (m_ReflectWnd.GetToolBar().GetEditBox().m_hWnd == ::GetFocus())
		return S_OK;
	return S_FALSE;
}
STDMETHODIMP CStockBar::TranslateAcceleratorIO(LPMSG lpMsg)
{
	// the only window that needs to translate messages is our edit box so forward them.
	return m_ReflectWnd.GetToolBar().GetEditBox().TranslateAcceleratorIO(lpMsg);
}
STDMETHODIMP CStockBar::UIActivateIO(BOOL fActivate, LPMSG lpMsg)
{
	// if our deskband is being activated then set focus to the edit box.
	if(fActivate)
	{
		m_ReflectWnd.GetToolBar().GetEditBox().SetFocus();
	}
	return S_OK;
}
