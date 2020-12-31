// SceneCtrl.h : Declaration of the CSceneCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "SceneCOM_i.h"
#include "_ISceneCtrlEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

#include "Earth.h"
class ISceneNode;
class ISceneMap;
// CSceneCtrl
class ATL_NO_VTABLE CSceneCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CSceneCtrl, ISceneCtrl>,
	public IPersistStreamInitImpl<CSceneCtrl>,
	public IOleControlImpl<CSceneCtrl>,
	public IOleObjectImpl<CSceneCtrl>,
	public IOleInPlaceActiveObjectImpl<CSceneCtrl>,
	public IViewObjectExImpl<CSceneCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CSceneCtrl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CSceneCtrl>,
	public CProxy_ISceneCtrlEvents<CSceneCtrl>,
	public IObjectWithSiteImpl<CSceneCtrl>,
	public IServiceProviderImpl<CSceneCtrl>,
	public IPersistStorageImpl<CSceneCtrl>,
	public ISpecifyPropertyPagesImpl<CSceneCtrl>,
	public IQuickActivateImpl<CSceneCtrl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CSceneCtrl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_SceneCtrl, &__uuidof(_ISceneCtrlEvents), &LIBID_SceneCOMLib>,
	public IPropertyNotifySinkCP<CSceneCtrl>,
	public IObjectSafetyImpl<CSceneCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CSceneCtrl, &CLSID_SceneCtrl>,
	public CComControl<CSceneCtrl>
{
public:


	CSceneCtrl():mEarth(NULL),mThreadHandle(NULL)
	{
		m_bWindowOnly = TRUE;
		//CalcExtent(m_sizeExtent);
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_SCENECTRL)


BEGIN_COM_MAP(CSceneCtrl)
	COM_INTERFACE_ENTRY(ISceneCtrl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CSceneCtrl)
	//PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	//PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	//PROP_ENTRY_TYPE("AutoSize", DISPID_AUTOSIZE, CLSID_NULL, VT_BOOL)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CSceneCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_ISceneCtrlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CSceneCtrl)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	CHAIN_MSG_MAP(CComControl<CSceneCtrl>)//CComCompositeControl
    DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

BEGIN_SINK_MAP(CSceneCtrl)
	//Make sure the Event Handlers have __stdcall calling convention
END_SINK_MAP()

	//STDMETHOD(OnAmbientPropertyChange)(DISPID dispid)
	//{
	//	if (dispid == DISPID_AMBIENT_BACKCOLOR)
	//	{
	//		SetBackgroundColorFromAmbient();
	//		FireViewChange();
	//	}
	//	return IOleControlImpl<CSceneCtrl>::OnAmbientPropertyChange(dispid);
	//}
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_ISceneCtrl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ISceneCtrl
	//void OnAutoSizeChanged()
	//{
	//	ATLTRACE(_T("OnAutoSizeChanged\n"));
	//}

	enum { IDD = IDD_SCENECTRL };
	STDMETHOD(_InternalQueryService)(REFGUID /*guidService*/, REFIID /*riid*/, void** /*ppvObject*/)
	{
		return E_NOTIMPL;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
    CEarth* mEarth;
    HANDLE  mThreadHandle;
    LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    //HRESULT OnDraw(ATL_DRAWINFO& di);
    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    STDMETHOD(ReplaceScene)(ISceneNode* scene);
    STDMETHOD( GetMap)(ISceneMap** ppMap);
    STDMETHOD( GetLocation)(ILocation** viewpoint);
    STDMETHOD( GotoLocation)(ILocation* viewpoint);
};

OBJECT_ENTRY_AUTO(__uuidof(SceneCtrl), CSceneCtrl)
