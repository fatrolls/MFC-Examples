// SceneNode.h : CSceneNode

#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "SceneCOM_i.h"

using namespace ATL;
#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include <osg/Node>
#include <osgEarth/MapNode>

using namespace osgEarth;
class ISceneMap;
// CSceneNode

class ATL_NO_VTABLE CSceneNode :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSceneNode, &CLSID_SceneNode>,
	public IDispatchImpl<ISceneNode, &IID_ISceneNode, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSceneNode():
        mMapNode(NULL){};


DECLARE_REGISTRY_RESOURCEID(IDR_SCENENODE)


BEGIN_COM_MAP(CSceneNode)
	COM_INTERFACE_ENTRY(ISceneNode)
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
	void Attach(MapNode* pNode)
	{
		mMapNode = pNode;
	}
	MapNode* GetNode()
	{
		return mMapNode;
	}
private:
	MapNode* mMapNode;
public:
    STDMETHOD( FromFile)(BSTR strFileName);
    STDMETHOD( GetMap)(ISceneMap** sceneMap);

};

OBJECT_ENTRY_AUTO(__uuidof(SceneNode), CSceneNode)
