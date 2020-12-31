// SceneMap.h : Declaration of the CSceneMap

#pragma once
#include "resource.h"       // main symbols

#include <osgEarth/Map>
#include <osgEarth/MapNode>

#include "SceneCOM_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

using namespace osgEarth;
struct IConfigOpt;
struct ILayerInfo;
struct ILocation;
// CSceneMap

class ATL_NO_VTABLE CSceneMap :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSceneMap, &CLSID_SceneMap>,
	public IDispatchImpl<ISceneMap, &IID_ISceneMap, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSceneMap():mMap(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SCENEMAP)


BEGIN_COM_MAP(CSceneMap)
	COM_INTERFACE_ENTRY(ISceneMap)
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
    void Attach(Map* pNode)
	{
		mMap = pNode;
	}
	Map* GetNode()
    {
		return mMap;
	}
private:
    Map* mMap;
public:
    STDMETHOD( GetModelLayerIds)(VARIANT* uids);
    STDMETHOD( GetElevationLayerIds)(VARIANT* uids);
    STDMETHOD( GetImageLayerIds)(VARIANT* uids);

    STDMETHOD( GetModelLayerInfo)(LONG uid, ILayerInfo** ppInfo);
    STDMETHOD( GetElevationLayerInfo)(LONG uid, ILayerInfo** ppInfo);
    STDMETHOD( GetImageLayerInfo)(LONG uid, ILayerInfo** ppInfo);

    STDMETHOD( AddLayer)(IConfigOpt* conf);
    //STDMETHOD( AddModelLayer)(IModelLayer* pLayer);
    //STDMETHOD( AddElevationLayer)(IElevationLayer* pLayer);
    //STDMETHOD( AddImageLayer)(IImageLayer* pLayer);
    ///STDMETHOD( AddMaskLayer)(IMaskLayer* pLayer);
    STDMETHOD( RemoveModelLayer)(LONG uid);
    STDMETHOD( RemoveElevationLayer)(LONG uid);
    STDMETHOD( RemoveImageLayer)(LONG uid);

    ///STDMETHOD( RemoveMaskLayer)(LONG uid);
};

OBJECT_ENTRY_AUTO(__uuidof(SceneMap), CSceneMap)
