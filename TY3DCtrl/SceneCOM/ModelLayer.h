// ModelLayer.h : Declaration of the CModelLayer

#pragma once
#include "resource.h"       // main symbols

#include <osgEarth/ModelLayer>

#include "SceneCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

using namespace osgEarth;
class IConfigOpt;
// CModelLayer

class ATL_NO_VTABLE CModelLayer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CModelLayer, &CLSID_ModelLayer>,
	public IDispatchImpl<IModelLayer, &IID_IModelLayer, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CModelLayer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MODELLAYER)


BEGIN_COM_MAP(CModelLayer)
	COM_INTERFACE_ENTRY(IModelLayer)
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
    void Attach(osgEarth::ModelLayer* pLayer)
	{
		mLayer = pLayer;
	}
	osgEarth::ModelLayer* GetLayer()
	{
		return mLayer;
	}
private:
    osgEarth::ModelLayer* mLayer;
public:

    STDMETHOD(FromConfig)(IConfigOpt* conf);



};

OBJECT_ENTRY_AUTO(__uuidof(::ModelLayer), CModelLayer)
