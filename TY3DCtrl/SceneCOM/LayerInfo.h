// LayerInfo.h : Declaration of the CLayerInfo

#pragma once
#include "resource.h"       // main symbols

#include "SceneCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

#include <vector>
using namespace std;
class CLayerProperty;
// CLayerInfo

class ATL_NO_VTABLE CLayerInfo :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLayerInfo, &CLSID_LayerInfo>,
	public IDispatchImpl<ILayerInfo, &IID_ILayerInfo, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CLayerInfo():mLayerInfo(NULL)
	{
	}
    ~CLayerInfo();

DECLARE_REGISTRY_RESOURCEID(IDR_LAYERINFO)


BEGIN_COM_MAP(CLayerInfo)
	COM_INTERFACE_ENTRY(ILayerInfo)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}
     void Attach(CLayerProperty* pInfo)
	{
		mLayerInfo = pInfo;
	}
    CLayerProperty* GetInfos()
    {
		return mLayerInfo;
	}
private:
    CLayerProperty* mLayerInfo;
public:
    STDMETHOD(GetGeoType)(LONG* type);
    STDMETHOD(IsVisible)(VARIANT_BOOL* bVisible);

    STDMETHOD(GetLayerType)(LONG* type);
    STDMETHOD(GetLayerName)(BSTR* name);
    STDMETHOD(GetLayerPath)(BSTR* url);
    STDMETHOD(GetEnvelop)(DOUBLE* left, DOUBLE* top, DOUBLE* right, DOUBLE* bottom);
 
    STDMETHOD(SetVisible)(VARIANT_BOOL bVisible);
    STDMETHOD(GetFields)(VARIANT* names, VARIANT* types);

};

OBJECT_ENTRY_AUTO(__uuidof(LayerInfo), CLayerInfo)
