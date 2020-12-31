// ProjectTreeCtrl.h : Declaration of the CProjectTreeCtrl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "ProjectTreeCOM_i.h"
#include "_IProjectTreeCtrlEvents_CP.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
#include "LayerTree.h"

// CProjectTreeCtrl
class ATL_NO_VTABLE CProjectTreeCtrl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CProjectTreeCtrl, IProjectTreeCtrl>,
	public IPersistStreamInitImpl<CProjectTreeCtrl>,
	public IOleControlImpl<CProjectTreeCtrl>,
	public IOleObjectImpl<CProjectTreeCtrl>,
	public IOleInPlaceActiveObjectImpl<CProjectTreeCtrl>,
	public IViewObjectExImpl<CProjectTreeCtrl>,
	public IOleInPlaceObjectWindowlessImpl<CProjectTreeCtrl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CProjectTreeCtrl>,
	public CProxy_IProjectTreeCtrlEvents<CProjectTreeCtrl>,
	public IObjectWithSiteImpl<CProjectTreeCtrl>,
	public IServiceProviderImpl<CProjectTreeCtrl>,
	public IPersistStorageImpl<CProjectTreeCtrl>,
	public ISpecifyPropertyPagesImpl<CProjectTreeCtrl>,
	public IQuickActivateImpl<CProjectTreeCtrl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CProjectTreeCtrl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_ProjectTreeCtrl, &__uuidof(_IProjectTreeCtrlEvents), &LIBID_ProjectTreeCOMLib>,
	public IPropertyNotifySinkCP<CProjectTreeCtrl>,
	public IObjectSafetyImpl<CProjectTreeCtrl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CProjectTreeCtrl, &CLSID_ProjectTreeCtrl>,
    public CComControl<CProjectTreeCtrl>, public WTL::CUpdateUI<CProjectTreeCtrl>, public WTL::CIdleHandler  
{
public:


	CProjectTreeCtrl():mhMenu(NULL)
	{
        m_bWindowOnly = TRUE;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_PROJECTTREECTRL)


BEGIN_COM_MAP(CProjectTreeCtrl)
	COM_INTERFACE_ENTRY(IProjectTreeCtrl)
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

BEGIN_PROP_MAP(CProjectTreeCtrl)
	//PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	//PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	//PROP_ENTRY_TYPE("AutoSize", DISPID_AUTOSIZE, CLSID_NULL, VT_BOOL)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CProjectTreeCtrl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IProjectTreeCtrlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CProjectTreeCtrl)
    MESSAGE_HANDLER(WM_CREATE, OnCreate)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
    MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
    COMMAND_HANDLER(ID_OPEN_PROPERTIES,0, OnProperties)
    COMMAND_HANDLER(ID_LAYERPROPERTIES,0, OnLayerProperties)
    COMMAND_HANDLER(ID_ADD_LOCATION,0, OnAddLocaion)
    COMMAND_HANDLER(ID_NEW_CATALOG,0, OnAddCatalog)

    NOTIFY_HANDLER(ID_LAYER_TREE, NM_DBLCLK, OnDoubleClickTree)
    REFLECT_NOTIFICATIONS()
    CHAIN_MSG_MAP(CUpdateUI<CProjectTreeCtrl>)  
	CHAIN_MSG_MAP(CComControl<CProjectTreeCtrl>)
	//DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()

BEGIN_UPDATE_UI_MAP(CProjectTreeCtrl)  
    UPDATE_ELEMENT(ID_NEW_CATALOG, UPDUI_MENUPOPUP)
    UPDATE_ELEMENT(ID_ADD_LOCATION, UPDUI_MENUPOPUP)
END_UPDATE_UI_MAP()  
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IProjectTreeCtrl,
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

// IProjectTreeCtrl
public:
	
    HRESULT OnDraw(ATL_DRAWINFO& di);
	//void OnAutoSizeChanged()
	//{
	//	ATLTRACE(_T("OnAutoSizeChanged\n"));
	//}
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
    
    CLayerTree mTree;
    HMENU mhMenu;
    WTL::CPoint m_hitPoint;
    LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    //HRESULT OnDraw(ATL_DRAWINFO& di);
    LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

    LRESULT OnAddCatalog(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    
    LRESULT OnAddLocaion(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnLayerProperties(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
    LRESULT OnDoubleClickTree(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
    STDMETHOD(AttachScene)(VARIANT scene);
    STDMETHOD(readEarth)(BSTR strEarthPath, VARIANT_BOOL* bSuc);
    STDMETHOD(writeEarth)(BSTR strEarthPath, VARIANT_BOOL* bSuc);
    virtual BOOL OnIdle()  
    {  
        return FALSE;  
    }  
};

OBJECT_ENTRY_AUTO(__uuidof(ProjectTreeCtrl), CProjectTreeCtrl)
