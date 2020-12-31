// OccEx.cpp : implementation file
//

#include "stdafx.h"
#include <afxconv.h>
#include "OccEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// HACK #1: 
// COleControlContainerEx cannot access pWnd->m_pCtrlCont and 
// pWnd->m_pCtrlSite since these are protected members of CWnd. 
// The original COleControlContainer is a friend of CWnd, so the
// orginal implementation has access to these members. A clean
// solution would be to derive a class from CWnd, granting this
// access; but we would have to derive from CDialog, CView, 
// CFormView etc too...
// The following two functions access the members via offsets
// to the last public member. This is version dependent, so check.
#if _MFC_VER != 0x0421
	#error These hacks are for MFC 4.21. Please check.
#endif
static inline COleControlContainer*& GetControlContainer(CWnd* pWnd)
{
	return *(COleControlContainer**)((void**)&pWnd->m_nFlags + 4);
}

static inline COleControlSite*& GetControlSite(CWnd* pWnd)
{
	return *(COleControlSite**)((void**)&pWnd->m_nFlags + 5);
}

/////////////////////////////////////////////////////////////////////////////
// COccManagerEx

COccManagerEx::COccManagerEx(CRuntimeClass* pContainerClass, CRuntimeClass* pSiteClass)
:	m_pContainerClass(pContainerClass)
,	m_pSiteClass(pSiteClass)
{
	if (pContainerClass)
		ASSERT(pContainerClass->IsDerivedFrom(RUNTIME_CLASS(COleControlContainerEx))
			&& pContainerClass->m_pfnCreateObject != NULL);
	if (pSiteClass)
		ASSERT(pSiteClass->IsDerivedFrom(RUNTIME_CLASS(COleControlSiteEx))
			&& pSiteClass->m_pfnCreateObject != NULL);
}

COleControlContainer* COccManagerEx::CreateContainer(CWnd* pWnd)
{
	if (m_pContainerClass == NULL)
		return COccManager::CreateContainer(pWnd);

	COleControlContainerEx* pContainer = STATIC_DOWNCAST(COleControlContainerEx, m_pContainerClass->CreateObject());
	pContainer->m_pWnd = pWnd;
	pContainer->Init();
	return pContainer;
}

COleControlSite* COccManagerEx::CreateSite(COleControlContainer* pCtrlCont)
{
	if (m_pSiteClass == NULL)
		return COccManager::CreateSite(pCtrlCont);

	COleControlSiteEx* pSite = STATIC_DOWNCAST(COleControlSiteEx, m_pSiteClass->CreateObject());
	pSite->m_pCtrlCont = pCtrlCont;
	pSite->Init();
	return pSite;
}

/////////////////////////////////////////////////////////////////////////////
// COleControlContainerEx

IMPLEMENT_DYNCREATE(COleControlContainerEx, 
		CCmdTarget) // COleControlContainer has no type info

COleControlContainerEx::COleControlContainerEx()
:	COleControlContainer(NULL)
,	m_pCapture(NULL)
,	m_pFocus(NULL)
,	m_bSupportWindowlessActivation(true)
,	m_pfnContWndProc(NULL)
{
}

void COleControlContainerEx::Init()
{
}

COleControlContainerEx::~COleControlContainerEx()
{
}

// HACK #2: 
// There seems to be an error in the MFC 4.21 import library: 
// COleControlContainer::interfaceMap (and COleControlSite::interfaceMap)
// is wrong!!!
// The Macro BEGIN_INTERFACE_MAP(COleControlContainerEx, COleControlContainer)
// expands (among others) to 
//		const AFX_INTERFACEMAP* PASCAL COleControlContainerEx::_GetBaseInterfaceMap() 
//		{
//			return &COleControlContainer::interfaceMap; 
//		}
// which returns the wrong value and causes the program to crash.
// To workaround the bug, I use COleControlContainer::GetInterfaceMap() to get
// the correct pointer, storing it in a static variable.
// Since COleControlContainer::GetInterfaceMap() is protected, I access it
// via an inline function COleControlContainerEx::GetBaseInterfaceMap().

//BEGIN_INTERFACE_MAP(COleControlContainerEx, COleControlContainer)

	const AFX_INTERFACEMAP* PASCAL COleControlContainerEx::_GetBaseInterfaceMap() 
	{
//		return &COleControlContainer::interfaceMap; 
		static const AFX_INTERFACEMAP* pBaseMap = NULL;
		if (pBaseMap == NULL)
		{
			COleControlContainerEx temp;
			pBaseMap = temp.GetBaseInterfaceMap();
#ifdef _DEBUG
			ASSERT(pBaseMap != &COleControlContainerEx::interfaceMap);
			if (pBaseMap == &COleControlContainer::interfaceMap)
			{
				TRACE2("*** Can remove COleControlContainer hack - %s (%d) ***\n", 
					__FILE__, __LINE__);
				ASSERT(FALSE);
			}
#endif
		}
		return pBaseMap;
	} 
	const AFX_INTERFACEMAP* COleControlContainerEx::GetInterfaceMap() const 
		{ return &COleControlContainerEx::interfaceMap; } 
	const AFX_DATADEF AFX_INTERFACEMAP COleControlContainerEx::interfaceMap = 
		{ &COleControlContainerEx::_GetBaseInterfaceMap, &COleControlContainerEx::_interfaceEntries[0], }; 
	const AFX_DATADEF AFX_INTERFACEMAP_ENTRY COleControlContainerEx::_interfaceEntries[] = 
	{ 

	INTERFACE_PART(COleControlContainerEx, IID_IOleInPlaceFrame, OleInPlaceFrame)
END_INTERFACE_MAP()

BOOL COleControlContainerEx::CreateControl(CWnd* pWndCtrl, REFCLSID clsid,
		LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, UINT nID,
		CFile* pPersist, BOOL bStorage, BSTR bstrLicKey,
		COleControlSite** ppNewSite)
{
	ASSERT_VALID(this);
	ASSERT(pWndCtrl->m_hWnd == NULL);

	// This is copied from COleControlContainer::CreateControl
	// Changes:
	// - use COleControlSiteEx::CreateControl instead of COleControlSite::CreateControl
	// - automatically subclass the container window to forward keyboard and mouse
	//   input messages.

	COleControlSite* pSite = NULL;

	TRY
	{
		pSite = afxOccManager->CreateSite(this);
	}
	CATCH_ALL(e)
	{
		return FALSE;
	}
	END_CATCH_ALL

	if (pSite == NULL)
		return FALSE;

// HACK #3: 
// COleControlSite::CreateControl is not virtual, so I check the type of the site
// object and simulate the virtual call by an appropriate cast.
	COleControlSiteEx* pSiteEx = DYNAMIC_DOWNCAST(COleControlSiteEx, pSite);
	BOOL bCreated;
	if (pSiteEx)
		bCreated = SUCCEEDED(pSiteEx->CreateControl(pWndCtrl, clsid,
			lpszWindowName, dwStyle, rect, nID, pPersist, bStorage, bstrLicKey));
	else
		bCreated = SUCCEEDED(pSite->CreateControl(pWndCtrl, clsid,
			lpszWindowName, dwStyle, rect, nID, pPersist, bStorage, bstrLicKey));

	if (bCreated)
	{
		// Note that COleControlSiteEx::CreateControl creates a "pseudo" m_hWnd, i.e.
		// a unique value wich can never collide with a real HWND.
		// This is necessary for the m_siteMap mechanism used in COleControlContainer.
		// See comments in COleControlSiteEx::CreateControl
		ASSERT(pSite->m_hWnd != NULL);
		m_siteMap.SetAt(pSite->m_hWnd, pSite);
		if (ppNewSite != NULL)
			*ppNewSite = pSite;

		if (pSiteEx && pSiteEx->IsWindowlessActive() && m_pfnContWndProc == NULL)
		{
			// subclass container window to handle UI messages
			TRACE0("Subclassing container window\n");
			m_pfnContWndProc = (WNDPROC)SetWindowLong(m_pWnd->m_hWnd, GWL_WNDPROC, (LONG)ContWndProc);
		}
	}
	else
	{
		delete pSite;
	}

	return bCreated;
}

// This window proc is used for the subclassed container window
LRESULT CALLBACK COleControlContainerEx::ContWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	CWnd* pWnd = CWnd::FromHandlePermanent(hWnd);
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->m_hWnd == hWnd);
	COleControlContainerEx* pContainer = STATIC_DOWNCAST(COleControlContainerEx, GetControlContainer(pWnd));

	if (pContainer == NULL)
		return AfxCallWndProc(pWnd, hWnd, nMsg, wParam, lParam);

	ASSERT_VALID(pContainer);
	ASSERT(pContainer->m_pWnd == pWnd);

	LRESULT lResult;
	if (pContainer->OnWindowMessage(nMsg, wParam, lParam, lResult))
		return lResult;

	return CallWindowProc(pContainer->m_pfnContWndProc, hWnd, nMsg, wParam, lParam);
}

bool COleControlContainerEx::OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	COleControlSiteEx* pTarget = NULL;
	if ((msg >= WM_KEYFIRST && msg <= WM_IME_KEYLAST)
		|| msg == WM_HELP
		|| msg == WM_CANCELMODE)
	{
		// pass keyboard messages to pseudo focus
		pTarget = m_pFocus;
	}
	else if ((msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST)
		|| msg == WM_SETCURSOR)
	{
		if (m_pCapture)
		{
			// pass keyboard messages to pseudo capture
			pTarget = m_pCapture;
		}
		else
		{
			// check if the mouse is over a windowless control
			CPoint pt; GetCursorPos(&pt);
			m_pWnd->ScreenToClient(&pt);

			pTarget = WindowlessSiteFromPoint(pt);
		}
	}

	if (pTarget == NULL)
		return false;

	return pTarget->OnWindowMessage(msg, wParam, lParam, lResult);
}

COleControlSiteEx* COleControlContainerEx::WindowlessSiteFromPoint(CPoint pt)
{
	HWND hWnd;
	COleControlSite* pSite;
	POSITION pos = m_siteMap.GetStartPosition();
	while (pos != NULL)
	{
		m_siteMap.GetNextAssoc(pos, (void*&)hWnd, (void*&)pSite);
		if ((DWORD)hWnd & 1)
		{
			ASSERT_KINDOF(COleControlSiteEx, pSite);
			if ((pSite->m_dwStyle & WS_VISIBLE) != 0 && pSite->m_rect.PtInRect(pt))
			{
				// TODO: use IViewObjectEx::QueryHitPoint to support non-rectangular controls
				return static_cast<COleControlSiteEx*>(pSite);
			}
		}
	}
	return NULL;
}

void COleControlContainerEx::OnDraw(CDC* pDC)
{
	HWND hWnd;
	COleControlSite* pSite;
	POSITION pos = m_siteMap.GetStartPosition();
	while (pos != NULL)
	{
		m_siteMap.GetNextAssoc(pos, (void*&)hWnd, (void*&)pSite);
		if ((DWORD)hWnd & 1)
		{
			ASSERT_KINDOF(COleControlSiteEx, pSite);
			if ((pSite->m_dwStyle & WS_VISIBLE) != 0)
				static_cast<COleControlSiteEx*>(pSite)->Draw(pDC);
		}
	}
}

void COleControlContainerEx::AmbientPropertyChanged(DISPID dispid)
{
	POSITION pos = m_siteMap.GetStartPosition();
	while (pos != NULL)
	{
		HWND hWnd;
		COleControlSiteEx* pSite;
		m_siteMap.GetNextAssoc(pos, (void*&)hWnd, (void*&)pSite);
		ASSERT_KINDOF(COleControlSiteEx, pSite);

		ASSERT_VALID(pSite);
		pSite->AmbientPropertyChanged(dispid);
	}
}

/////////////////////////////////////////////////////////////////////////////
// COleControlContainerEx::XOleInPlaceFrame

// This replaces the IOleInPlaceFrame implementation in COleControlContainer.

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)
	return (HRESULT)pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(ULONG) COleControlContainerEx::XOleInPlaceFrame::AddRef()
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)
	return (ULONG)pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) COleControlContainerEx::XOleInPlaceFrame::Release()
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)
	return (ULONG)pThis->InternalRelease();
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::GetWindow(HWND* phWnd)
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)

	*phWnd = pThis->m_pWnd->m_hWnd;
	return S_OK;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::ContextSensitiveHelp(BOOL)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::GetBorder(LPRECT)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::RequestBorderSpace(
	LPCBORDERWIDTHS)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::SetBorderSpace(
	LPCBORDERWIDTHS)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::SetActiveObject(
	LPOLEINPLACEACTIVEOBJECT pActiveObject, LPCOLESTR pszObjName)
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)
	return pThis->m_xOleIPFrame.SetActiveObject(pActiveObject, pszObjName);
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::InsertMenus(HMENU,
	LPOLEMENUGROUPWIDTHS)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::SetMenu(HMENU, HOLEMENU, HWND)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::RemoveMenus(HMENU)
{
	return E_NOTIMPL;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::SetStatusText(
	LPCOLESTR lpszStatusText)
{
	METHOD_PROLOGUE_EX_(COleControlContainerEx, OleInPlaceFrame)
	USES_CONVERSION;

	CFrameWnd* pFrame = pThis->m_pWnd->GetParentFrame();
	ASSERT_VALID(pFrame);

	pFrame->SetMessageText(OLE2CT(lpszStatusText));

	return S_OK;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::EnableModeless(BOOL fEnable)
{
	METHOD_PROLOGUE_EX(COleControlContainerEx, OleInPlaceFrame)
	ASSERT_VALID(pThis);

	SCODE sc = E_UNEXPECTED;
	TRY
	{
		CFrameWnd* pFrame = pThis->m_pWnd->GetParentFrame();
		ASSERT_VALID(pFrame);

		if (!fEnable)
			pFrame->BeginModalState();
		else
			pFrame->EndModalState();
		sc = S_OK;
	}
	END_TRY

	return sc;
}

STDMETHODIMP COleControlContainerEx::XOleInPlaceFrame::TranslateAccelerator(
	LPMSG lpmsg, WORD wID)
{
	UNUSED_ALWAYS(lpmsg);
	UNUSED_ALWAYS(wID);

	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// COleControlSiteEx

IMPLEMENT_DYNCREATE(COleControlSiteEx, CCmdTarget) // COleControlSite is not DYNAMIC

// See comment "HACK #2" 

//BEGIN_INTERFACE_MAP(COleControlSiteEx, COleControlSite)

	const AFX_INTERFACEMAP* PASCAL COleControlSiteEx::_GetBaseInterfaceMap() 
	{
//		return &COleControlSite::interfaceMap; 
		static const AFX_INTERFACEMAP* pBaseMap = NULL;
		if (pBaseMap == NULL)
		{
			COleControlSiteEx temp;
			pBaseMap = temp.GetBaseInterfaceMap();
#ifdef _DEBUG
			ASSERT(pBaseMap != &COleControlSiteEx::interfaceMap);
			if (pBaseMap == &COleControlSite::interfaceMap)
			{
				ASSERT(FALSE);
				TRACE2("*** Can remove COleControlSite hack - %s (%d) ***\n", 
					__FILE__, __LINE__);
			}
#endif
		}
		return pBaseMap;
	} 
	const AFX_INTERFACEMAP* COleControlSiteEx::GetInterfaceMap() const 
		{ return &COleControlSiteEx::interfaceMap; } 
	const AFX_DATADEF AFX_INTERFACEMAP COleControlSiteEx::interfaceMap = 
		{ &COleControlSiteEx::_GetBaseInterfaceMap, &COleControlSiteEx::_interfaceEntries[0], }; 
	const AFX_DATADEF AFX_INTERFACEMAP_ENTRY COleControlSiteEx::_interfaceEntries[] = 
	{ 

	INTERFACE_PART(COleControlSiteEx, IID_IOleInPlaceSite, OleInPlaceSiteWindowless)
	INTERFACE_PART(COleControlSiteEx, IID_IOleInPlaceSiteEx, OleInPlaceSiteWindowless)
	INTERFACE_PART(COleControlSiteEx, IID_IOleInPlaceSiteWindowless, OleInPlaceSiteWindowless)
END_INTERFACE_MAP()

COleControlSiteEx::COleControlSiteEx()
:	COleControlSite(NULL)
,	m_dwActivateFlags(0)
,	m_pIPOW(NULL)
{
	TRACE0("COleControlSiteEx object created\n");
}

void COleControlSiteEx::Init()
{
}

COleControlSiteEx::~COleControlSiteEx()
{
	COleControlContainerEx* pContainer = DYNAMIC_DOWNCAST(COleControlContainerEx, m_pCtrlCont);
	if (pContainer)
	{
		if (pContainer->m_pFocus == this)
			pContainer->m_pFocus = NULL;
		if (pContainer->m_pCapture == this)
			pContainer->m_pCapture = NULL;
	}
	if (m_pIPOW)
	{
		m_pIPOW->Release();
		m_pIPOW = NULL;
	}
	TRACE0("COleControlSiteEx object destroyed\n");
}

void COleControlSiteEx::AmbientPropertyChanged(DISPID dispid)
{
	LPOLECONTROL pOleCtl = NULL;
	if (SUCCEEDED(m_pObject->QueryInterface(IID_IOleControl, (LPVOID*)&pOleCtl)))
	{
		ASSERT(pOleCtl != NULL);
		pOleCtl->OnAmbientPropertyChange(dispid);
		pOleCtl->Release();
	}
}

HRESULT COleControlSiteEx::CreateControl(CWnd* pWndCtrl, REFCLSID clsid,
	LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, UINT nID,
	CFile* pPersist, BOOL bStorage, BSTR bstrLicKey)
{
	// This is a copy of COleControlSite::CreateControl
	// Changes:
	// - Allow windowless activation.

	HRESULT hr = E_FAIL;
	m_hWnd = NULL;

	// Connect the OLE Control with its proxy CWnd object
	if (pWndCtrl != NULL)
	{
		ASSERT(GetControlSite(pWndCtrl) == NULL);
		m_pWndCtrl = pWndCtrl;
		GetControlSite(pWndCtrl) = this;
	}

	// Initialize OLE, if necessary
	_AFX_THREAD_STATE* pState = AfxGetThreadState();
	if (!pState->m_bNeedTerm && !AfxOleInit())
		return hr;

	if (SUCCEEDED(hr = CreateOrLoad(clsid, pPersist, bStorage, bstrLicKey)))
	{
		ASSERT(m_pObject != NULL);
		m_nID = nID;
		m_rect = rect;

		m_dwStyleMask = WS_GROUP | WS_TABSTOP;

		if (m_dwMiscStatus & OLEMISC_ACTSLIKEBUTTON)
			m_dwStyleMask |= BS_DEFPUSHBUTTON;

		if (m_dwMiscStatus & OLEMISC_INVISIBLEATRUNTIME)
			dwStyle &= ~WS_VISIBLE;

		m_dwStyle = dwStyle & m_dwStyleMask;

		// If control wasn't quick-activated, then connect sinks now.
		if (hr != S_FALSE)
		{
			m_dwEventSink = ConnectSink(m_iidEvents, &m_xEventSink);
			m_dwPropNotifySink = ConnectSink(IID_IPropertyNotifySink,
				&m_xPropertyNotifySink);
		}
		m_dwNotifyDBEvents = ConnectSink(IID_INotifyDBEvents, &m_xNotifyDBEvents);

		// Now that the object has been created, attempt to
		// in-place activate it.

		if (!SetExtent())
			TRACE1("Warning: SetExtent on OLE control (dialog ID %d) failed.\n",
				nID);

		if (SUCCEEDED(hr = m_pObject->QueryInterface(IID_IOleInPlaceObject,
				(LPVOID*)&m_pInPlaceObject)))
		{
			if (dwStyle & WS_VISIBLE)
			{
				// control is visible: just activate it
				hr = DoVerb(OLEIVERB_INPLACEACTIVATE);
			}
			else
			{
				// control is not visible: activate off-screen, hide, then move
				m_rect.OffsetRect(-32000, -32000);
				if (SUCCEEDED(hr = DoVerb(OLEIVERB_INPLACEACTIVATE)) &&
					SUCCEEDED(hr = DoVerb(OLEIVERB_HIDE)))
				{
					m_rect.OffsetRect(32000, 32000);
					hr = m_pInPlaceObject->SetObjectRects(m_rect, m_rect);
				}
			}
		}
		else
		{
			TRACE1("IOleInPlaceObject not supported on OLE control (dialog ID %d).\n", nID);
			TRACE1(">>> Result code: 0x%08lx\n", hr);
		}

		if (SUCCEEDED(hr))
			GetControlInfo();

		// if QueryInterface or activation failed, cleanup everything
		if (FAILED(hr))
		{
			if (m_pInPlaceObject != NULL)
			{
				m_pInPlaceObject->Release();
				m_pInPlaceObject = NULL;
			}
			if (m_pIPOW)
			{
				m_pIPOW->Release();
				m_pIPOW = NULL;
			}
			DisconnectSink(m_iidEvents, m_dwEventSink);
			DisconnectSink(IID_IPropertyNotifySink, m_dwPropNotifySink);
			DisconnectSink(IID_INotifyDBEvents, m_dwNotifyDBEvents);
			m_dwEventSink = 0;
			m_dwPropNotifySink = 0;
			m_dwNotifyDBEvents = 0;
			m_pObject->Release();
			m_pObject = NULL;
		}
	}

	if (SUCCEEDED(hr))
	{
		// --- Begin modification ---
		ASSERT((m_dwActivateFlags & ACTIVATE_WINDOWLESS) != 0 || m_hWnd != NULL);
// HACK#4:
// Lots of functions in CWnd and COleControlContainer rely on the fact that all active
// contained controls are in the HWND->COleControlSite map m_siteMap.
// Since windowless controls have no HWND, we just create a pseude HWND, i.e. a number
// which is guaranteed to be unique and which cannot be a valid window handle.
// We use (HWND)((DWORD)pSite | 1) for this (window handles are always even).
// The only places in MFC where the hwnd info from the map is really used as window handle
// are in the following functions:
// - CWnd::OnWndMsg for WM_CTLCOLOR
// - CWnd::ReflectLastMsg
// - some virtual functions in COleControlSite.
// The first two are never called for windowless controls, the COleControlSite functions
// are overridden here.
		if (m_hWnd == NULL)
		{
			m_hWnd = (HWND)((DWORD)this | 1);
			m_dwStyleMask |= WS_VISIBLE;
			m_dwStyle |= (dwStyle & WS_VISIBLE);
			VERIFY(SUCCEEDED(m_pInPlaceObject->QueryInterface(
				IID_IOleInPlaceObjectWindowless, (void**)&m_pIPOW)));
		}
		else
		{
			ASSERT(((DWORD)m_hWnd & 1) == 0);
		}
		// --- End modification ---

		AttachWindow();

		// Initialize the control's Caption or Text property, if any
		if (lpszWindowName != NULL)
			SetWindowText(lpszWindowName);

		// Initialize styles
		ModifyStyle(0, m_dwStyle | (dwStyle & (WS_DISABLED|WS_BORDER)), 0);
	}

	return hr;
}

void COleControlSiteEx::Draw(CDC* pDC)
{
	if (!IsWindowlessActive() || (m_dwStyle & WS_VISIBLE) == 0)
		return;

	LPVIEWOBJECT lpViewObject = NULL;
	if (FAILED(m_pObject->QueryInterface(IID_IViewObject, (void**)&lpViewObject)))
		return;

	// get RECTL describing window extents and origin
	RECTL rclWBounds;
	CPoint ptOrg = pDC->GetWindowOrg();
	CSize sizeExt = pDC->GetWindowExt();
	rclWBounds.left = ptOrg.x;
	rclWBounds.top = ptOrg.y;
	rclWBounds.right = sizeExt.cx;
	rclWBounds.bottom = sizeExt.cy;

	lpViewObject->Draw(DVASPECT_CONTENT, -1, NULL,
		NULL, NULL, pDC->m_hDC,
		(RECTL*)&m_rect, &rclWBounds, NULL, 0);
	lpViewObject->Release();
}

DWORD COleControlSiteEx::GetStyle() const
{
	DWORD dwStyle = m_dwStyle;
	if (!IsWindowlessActive())
		dwStyle |= (::GetWindowLong(m_hWnd, GWL_STYLE) & WS_VISIBLE);

	TRY
	{
		BOOL bEnabled = TRUE;
		GetProperty(DISPID_ENABLED, VT_BOOL, &bEnabled);
		if (!bEnabled)
			dwStyle |= WS_DISABLED;
	}
	END_TRY

	TRY
	{
		short sBorderStyle = 0;
		GetProperty(DISPID_BORDERSTYLE, VT_I2, &sBorderStyle);
		if (sBorderStyle == 1)
			dwStyle |= WS_BORDER;
	}
	END_TRY

	return dwStyle;
}

DWORD COleControlSiteEx::GetExStyle() const
{
	DWORD dwExStyle = 0;
	if (!IsWindowlessActive())
		dwExStyle |= ::GetWindowLong(m_hWnd, GWL_EXSTYLE);

	TRY
	{
		short sAppearance = 0;
		GetProperty(DISPID_APPEARANCE, VT_I2, &sAppearance);
		if (sAppearance == 1)
			dwExStyle |= WS_EX_CLIENTEDGE;
	}
	END_TRY

	return dwExStyle;
}

BOOL COleControlSiteEx::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	m_dwStyle = ((m_dwStyle & ~dwRemove) | dwAdd) & m_dwStyleMask;

	// Enabled property
	if ((dwRemove & WS_DISABLED) || (dwAdd & WS_DISABLED))
	{
		if (SafeSetProperty(DISPID_ENABLED, VT_BOOL, (~dwAdd & WS_DISABLED)))
		{
			dwRemove &= ~WS_DISABLED;
			dwAdd &= ~WS_DISABLED;
		}
	}

	// BorderStyle property
	if ((dwRemove & WS_BORDER) || (dwAdd & WS_BORDER))
	{
		if (SafeSetProperty(DISPID_BORDERSTYLE, VT_I2, (dwAdd & WS_BORDER)))
		{
			dwRemove &= ~WS_BORDER;
			dwAdd &= ~WS_BORDER;
		}
	}

	if (!IsWindowlessActive())
	{
		return CWnd::ModifyStyle(m_hWnd, dwRemove, dwAdd, nFlags);
	}
	else
	{
		if ((dwRemove & WS_VISIBLE) || (dwAdd & WS_VISIBLE))
		{
			//.TODO: Visible property changed
		}
		return TRUE;
	}
}

BOOL COleControlSiteEx::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	// BorderStyle property
	if ((dwRemove & WS_EX_CLIENTEDGE) || (dwAdd & WS_EX_CLIENTEDGE))
	{
		if (SafeSetProperty(DISPID_APPEARANCE, VT_I2, (dwAdd & WS_EX_CLIENTEDGE)))
		{
			dwRemove &= ~WS_EX_CLIENTEDGE;
			dwAdd &= ~WS_EX_CLIENTEDGE;
		}
	}

	if (!IsWindowlessActive())
	{
		return CWnd::ModifyStyleEx(m_hWnd, dwRemove, dwAdd, nFlags);
	}
	else
	{
		return TRUE;
	}
}

#ifdef _DEBUG
// The original implementations of the following two functions work
// perfectly with windowless controls, but both have an ASSERT(::IsWindow(m_hWnd))
// which will fire for a windowless control.
// We override these functions only in the _DEBUG version to get rid of the ASSERT.
void COleControlSiteEx::SetWindowText(LPCTSTR lpszString)
{
//	ASSERT(::IsWindow(m_hWnd));

	if (!SafeSetProperty(DISPID_CAPTION, VT_BSTR, lpszString))
		SafeSetProperty(DISPID_TEXT, VT_BSTR, lpszString);
}

void COleControlSiteEx::GetWindowText(CString& str) const
{
//	ASSERT(::IsWindow(m_hWnd));

	TRY
	{
		GetProperty(DISPID_CAPTION, VT_BSTR, &str);
	}
	CATCH_ALL(e)
	{
		TRY
		{
			GetProperty(DISPID_TEXT, VT_BSTR, &str);
		}
		END_TRY
	}
	END_CATCH_ALL
}
#endif

BOOL COleControlSiteEx::SetWindowPos(const CWnd* pWndInsertAfter, int x, int y, int cx,
	int cy, UINT nFlags)
{
	if (nFlags & SWP_HIDEWINDOW)
		ShowWindow(SW_HIDE);

	if ((nFlags & (SWP_NOMOVE|SWP_NOSIZE)) != (SWP_NOMOVE|SWP_NOSIZE))
	{
		int xNew;
		int yNew;
		if (nFlags & SWP_NOMOVE)
		{
			xNew = m_rect.left;
			yNew = m_rect.top;
		}
		else
		{
			xNew = x;
			yNew = y;
		}

		int cxNew;
		int cyNew;
		if (nFlags & SWP_NOSIZE)
		{
			cxNew = m_rect.Width();
			cyNew = m_rect.Height();
		}
		else
		{
			cxNew = cx;
			cyNew = cy;
		}

		MoveWindow(xNew, yNew, cxNew, cyNew, !(nFlags & SWP_NOREDRAW));
	}

	if (nFlags & SWP_SHOWWINDOW)
		ShowWindow(SW_SHOW);

	// we've handled hide, move, size, and show; let Windows do the rest
	nFlags &= ~(SWP_HIDEWINDOW|SWP_SHOWWINDOW);
	nFlags |= (SWP_NOMOVE|SWP_NOSIZE);

	if (!IsWindowlessActive())
	{
		return ::SetWindowPos(m_hWnd, pWndInsertAfter->GetSafeHwnd(),
			x, y, cx, cy, nFlags);
	}
	else
	{
		return TRUE;
	}
}

BOOL COleControlSiteEx::ShowWindow(int nCmdShow)
{
	BOOL bReturn;
	if (IsWindowlessActive())
		bReturn = (m_dwStyle & WS_VISIBLE) != 0;
	else
		bReturn = ::IsWindowVisible(m_hWnd);

	int iVerb = 0;
	switch (nCmdShow)
	{
	case SW_SHOW:
	case SW_SHOWNORMAL:
	case SW_SHOWNOACTIVATE:
		iVerb = OLEIVERB_SHOW;
		if (IsWindowlessActive())
			m_dwStyle |= WS_VISIBLE;
		break;

	case SW_HIDE:
		iVerb = OLEIVERB_HIDE;
		if (IsWindowlessActive())
			m_dwStyle &= ~WS_VISIBLE;
		break;
	}

	if (iVerb != 0)
		DoVerb(iVerb);

	return bReturn;
}

CWnd* COleControlSiteEx::SetFocus()
{
	CWnd* pWndPrev = CWnd::GetFocus();
	if (IsWindowlessActive())
	{
		DoVerb(OLEIVERB_UIACTIVATE);
	}
	else
	{
		if (m_dwMiscStatus & OLEMISC_NOUIACTIVATE)
			::SetFocus(m_hWnd);
		else
			DoVerb(OLEIVERB_UIACTIVATE);
	}
	return pWndPrev;
}

bool COleControlSiteEx::OnWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	if (m_pIPOW == NULL)
		return false;

	HRESULT hr = m_pIPOW->OnWindowMessage(msg, wParam, lParam, &lResult);

	return hr == S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// COleControlSiteEx::XOleInPlaceSiteWindowless

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	return (HRESULT)pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(ULONG) COleControlSiteEx::XOleInPlaceSiteWindowless::AddRef()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	return (ULONG)pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) COleControlSiteEx::XOleInPlaceSiteWindowless::Release()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	return (ULONG)pThis->InternalRelease();
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::GetWindow(HWND* phWnd)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	*phWnd = pThis->m_pCtrlCont->m_pWnd->GetSafeHwnd();
	return *phWnd != NULL ? S_OK : E_FAIL;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::ContextSensitiveHelp(BOOL fEnterMode)
{
	UNUSED_ALWAYS(fEnterMode);
	return E_NOTIMPL;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::CanInPlaceActivate()
{
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnInPlaceActivate()
{
	return OnInPlaceActivateEx(NULL, 0);
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnUIActivate()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	pThis->m_pCtrlCont->OnUIActivate(pThis);
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::GetWindowContext(LPOLEINPLACEFRAME* ppFrame,
	LPOLEINPLACEUIWINDOW* ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
		// pass to default implementation
	return pThis->m_xOleIPSite.GetWindowContext(ppFrame, ppDoc, lprcPosRect, lprcClipRect, lpFrameInfo);
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::Scroll(SIZE scrollExtent)
{
	UNUSED_ALWAYS(scrollExtent);
	return S_FALSE;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnUIDeactivate(BOOL fUndoable)
{
	UNUSED_ALWAYS(fUndoable);
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	pThis->m_pCtrlCont->OnUIDeactivate(pThis);
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnInPlaceDeactivate()
{
	return OnInPlaceDeactivateEx(TRUE);
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::DiscardUndoState()
{
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::DeactivateAndUndo()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	pThis->m_pInPlaceObject->UIDeactivate();
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnPosRectChange(LPCRECT lprcPosRect)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	CRect rectClip;
	pThis->m_pCtrlCont->m_pWnd->GetClientRect(rectClip);
	pThis->m_rect = lprcPosRect;
	return pThis->m_pInPlaceObject->SetObjectRects(pThis->m_rect, rectClip);
}

// IOleInPlaceSiteEx
STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnInPlaceActivateEx(BOOL* pfNoRedraw, DWORD dwFlags)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	pThis->m_dwActivateFlags = dwFlags;
	if (pfNoRedraw)
	{
		// TODO: look closer
		*pfNoRedraw = FALSE;
	}
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnInPlaceDeactivateEx(BOOL fNoRedraw)    
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	pThis->DetachWindow();
	pThis->m_dwActivateFlags = 0;
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::RequestUIActivate()
{
	return S_OK;
}

// IOleInPlaceSiteWindowless
STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::CanWindowlessActivate()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	if (STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_bSupportWindowlessActivation)
		return S_OK;
	else
		return E_FAIL; // use E_FAIL instead of S_FALSE, since the latter does not work with ATL controls
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::GetCapture()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	HWND hwndCapture = ::GetCapture();
	if (hwndCapture == NULL)
		return S_FALSE;
	else if (!pThis->IsWindowlessActive() && hwndCapture == pThis->m_hWnd)
		return S_OK;
	else if (hwndCapture == pThis->m_pCtrlCont->m_pWnd->GetSafeHwnd()
		&& STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pCapture == pThis)
		return S_OK;
	else
		return S_FALSE;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::SetCapture(BOOL fCapture)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	if (!fCapture)
	{
		if (GetCapture() == S_OK)
			::ReleaseCapture();
		STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pCapture = NULL;
	}
	else if (!pThis->IsWindowlessActive())
	{
		::SetCapture(pThis->m_hWnd);
	}
	else
	{
		STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pCapture = pThis;
		::SetCapture(pThis->m_pCtrlCont->m_pWnd->GetSafeHwnd());
	}
		
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::GetFocus()
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	HWND hwndFocus = ::GetFocus();
	if (hwndFocus == NULL)
		return S_FALSE;
	else if (!pThis->IsWindowlessActive() && hwndFocus == pThis->m_hWnd)
		return S_OK;
	else if (hwndFocus == pThis->m_pCtrlCont->m_pWnd->GetSafeHwnd()
		&& STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pFocus == pThis)
		return S_OK;
	else
		return S_FALSE;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::SetFocus(BOOL fFocus)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)
	if (!fFocus)
	{
		if (GetFocus() == S_OK)
			::SetFocus(NULL);
		STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pFocus = NULL;
	}
	else if (!pThis->IsWindowlessActive())
	{
		::SetFocus(pThis->m_hWnd);
	}
	else
	{
		STATIC_DOWNCAST(COleControlContainerEx, pThis->m_pCtrlCont)->m_pFocus = pThis;
		::SetFocus(pThis->m_pCtrlCont->m_pWnd->GetSafeHwnd());
	}

	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::GetDC(LPCRECT pRect, DWORD grfFlags, HDC* phDC)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	*phDC = pThis->WindowlessGetDC(pRect, grfFlags);

	return *phDC ? S_OK : E_FAIL;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::ReleaseDC(HDC hDC)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	pThis->WindowlessReleaseDC(hDC);

	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::InvalidateRect(LPCRECT pRect, BOOL fErase)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	pThis->WindowlessInvalidateRect(pRect, fErase);

	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::InvalidateRgn(HRGN hRGN, BOOL fErase)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	pThis->WindowlessInvalidateRgn(hRGN, fErase);

	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::ScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	pThis->WindowlessScrollRect(dx, dy, pRectScroll, pRectClip);
	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::AdjustRect(LPRECT prc)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	pThis->WindowlessAdjustRect(prc);

	return S_OK;
}

STDMETHODIMP COleControlSiteEx::XOleInPlaceSiteWindowless::OnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT* plResult)
{
	METHOD_PROLOGUE(COleControlSiteEx, OleInPlaceSiteWindowless)

	if (pThis->WindowlessOnDefWindowMessage(msg, wParam, lParam, *plResult))
		return S_OK;
	else
		return S_FALSE;
}

HDC COleControlSiteEx::WindowlessGetDC(LPCRECT pRect, DWORD grfFlags)
{
	HWND hwndContainer = m_pCtrlCont->m_pWnd->GetSafeHwnd();

	if (grfFlags & OLEDC_NODRAW)
		return ::GetDC(hwndContainer);
	if (grfFlags & OLEDC_OFFSCREEN)
		return NULL;

	HDC hDC = ::GetDC(hwndContainer);
	::IntersectClipRect(hDC, m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);
	if (pRect)
		::IntersectClipRect(hDC, pRect->left, pRect->top, pRect->right, pRect->bottom);

	if (grfFlags & OLEDC_PAINTBKGND)
	{
		::SendMessage(hwndContainer, WM_ERASEBKGND, (WPARAM)hDC, 0);
		// TODO: draw objects behind this one
	}

	return hDC;
}

void COleControlSiteEx::WindowlessReleaseDC(HDC hDC)
{
	// TODO: draw object on top of this
	HWND hwndContainer = m_pCtrlCont->m_pWnd->GetSafeHwnd();
	::ReleaseDC(hwndContainer, hDC);
}

void COleControlSiteEx::WindowlessInvalidateRect(LPCRECT pRect, BOOL fErase)
{
	CRect rect = m_rect;
	if (pRect)
		rect &= *pRect;

	m_pCtrlCont->m_pWnd->InvalidateRect(rect, fErase);
}

void COleControlSiteEx::WindowlessInvalidateRgn(HRGN hRGN, BOOL fErase)
{
	if (hRGN == NULL)
	{
		m_pCtrlCont->m_pWnd->InvalidateRect(m_rect, fErase);
	}
	else
	{
		CRgn rgnRect;
		rgnRect.CreateRectRgnIndirect(m_rect);
		CRgn rgn;
		rgn.CombineRgn(&rgnRect, CRgn::FromHandle(hRGN), RGN_AND);
		m_pCtrlCont->m_pWnd->InvalidateRgn(&rgn, fErase);
	}
}

void COleControlSiteEx::WindowlessScrollRect(INT dx, INT dy, LPCRECT pRectScroll, LPCRECT pRectClip)
{
	WindowlessInvalidateRect(pRectScroll, TRUE);
	m_pCtrlCont->m_pWnd->UpdateWindow();
	// TODO: make smarter
}

void COleControlSiteEx::WindowlessAdjustRect(LPRECT prc)
{
	UNUSED_ALWAYS(prc);
}

BOOL COleControlSiteEx::WindowlessOnDefWindowMessage(UINT msg, WPARAM wParam, LPARAM lParam, LRESULT& lResult)
{
	HWND hwndContainer = m_pCtrlCont->m_pWnd->GetSafeHwnd();

	switch (msg)
	{
	case WM_LBUTTONDOWN:
		// TODO: check if the control can be UI activated
		// (corresponds to (SendMesage(WM_GETDLGCODE) & DLGC_STATIC) == 0)
		SetFocus();
		return TRUE;
	case WM_SETCURSOR:
	case WM_CONTEXTMENU:
	case WM_HELP:
		// TODO: pass on to the container window's original window proc
		return FALSE;
	default:
		// TODO: pass on to the container window's original window proc
		lResult = ::DefWindowProc(hwndContainer, msg, wParam, lParam);
		return TRUE;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CWindowlessControl

IMPLEMENT_DYNCREATE(CWindowlessControl, CWnd)

CWindowlessControl::CWindowlessControl()
{
}

BOOL CWindowlessControl::CreateControl(LPCTSTR lpszClass, LPCTSTR lpszWindowName,
	DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID,
	CFile* pPersist, BOOL bStorage, BSTR bstrLicKey)
{
	ASSERT(lpszClass != NULL);

	CLSID clsid;
	HRESULT hr = AfxGetClassIDFromString(lpszClass, &clsid);
	if (FAILED(hr))
		return FALSE;

	return CreateControl(clsid, lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
}

BOOL CWindowlessControl::CreateControl(REFCLSID clsid, LPCTSTR lpszWindowName, DWORD dwStyle,
	const RECT& rect, CWnd* pParentWnd, UINT nID, CFile* pPersist,
	BOOL bStorage, BSTR bstrLicKey)
{
	ASSERT(pParentWnd != NULL);

#ifdef _DEBUG
	if (afxOccManager == NULL)
	{
		TRACE0("Warning: AfxEnableControlContainer has not been called yet.\n");
		TRACE0(">>> You should call it in your app's InitInstance function.\n");
	}
#endif

	if (pParentWnd == NULL)
		return FALSE;

//	if (!pParentWnd->InitControlContainer())
//		return FALSE;
// This does not work since InitControlContainer is protected;
// so we have to copy the implementation.
	COleControlContainer*& pCtrlCont = GetControlContainer(pParentWnd);
	TRY
	{
		if (pCtrlCont == NULL)
			pCtrlCont = afxOccManager->CreateContainer(pParentWnd);
	}
	END_TRY

	// Mark all ancestor windows as containing OLE controls.
	if (pCtrlCont != NULL)
	{
		CWnd* pWnd = pParentWnd;
		while ((pWnd != NULL) && !(pWnd->m_nFlags & WF_OLECTLCONTAINER))
		{
			pWnd->m_nFlags |= WF_OLECTLCONTAINER;
			pWnd = pWnd->GetParent();
			if (! (GetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE) & WS_CHILD))
				break;
		}
	}
	if (pCtrlCont == NULL)
		return FALSE;

// HACK #5: 
// COleControlContainer::CreateControl is not virtual, so I check the type of the 
// container object and simulate the virtual call by an appropriate cast.
	COleControlContainer* pContainer = GetControlContainer(pParentWnd);
	if (pContainer->IsKindOf(RUNTIME_CLASS(COleControlContainerEx)))
		return static_cast<COleControlContainerEx*>(pContainer)->CreateControl(this, clsid, lpszWindowName,
			dwStyle, rect, nID, pPersist, bStorage, bstrLicKey);
	else
		return pContainer->CreateControl(this, clsid, lpszWindowName,
			dwStyle, rect, nID, pPersist, bStorage, bstrLicKey);
}

