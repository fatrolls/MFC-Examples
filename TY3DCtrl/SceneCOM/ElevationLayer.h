// ElevationLayer.h : Declaration of the CElevationLayer

#pragma once
#include "resource.h"       // main symbols

#include <osgEarth/ElevationLayer>

#include "SceneCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

using namespace osgEarth;
class IConfigOpt;
// CElevationLayer

class ATL_NO_VTABLE CElevationLayer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CElevationLayer, &CLSID_ElevationLayer>,
	public IDispatchImpl<IElevationLayer, &IID_IElevationLayer, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CElevationLayer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ELEVATIONLAYER)


BEGIN_COM_MAP(CElevationLayer)
	COM_INTERFACE_ENTRY(IElevationLayer)
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
    void Attach(osgEarth::ElevationLayer* pLayer)
	{
		mLayer = pLayer;
	}
	osgEarth::ElevationLayer* GetLayer()
	{
		return mLayer;
	}
private:
    osgEarth::ElevationLayer* mLayer;
public:

    STDMETHOD(FromConfig)(IConfigOpt* conf);


};

OBJECT_ENTRY_AUTO(__uuidof(::ElevationLayer), CElevationLayer)
