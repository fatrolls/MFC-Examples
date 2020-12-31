// Location.h : CLocation 的声明

#pragma once
#include "resource.h"       // 主符号


#include "SceneCOM_i.h"

#include <osgEarth/Viewpoint>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;
using namespace osgEarth;

// CLocation

class ATL_NO_VTABLE CLocation :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLocation, &CLSID_Location>,
	public IDispatchImpl<ILocation, &IID_ILocation, &LIBID_SceneCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CLocation()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_LOCATION)


BEGIN_COM_MAP(CLocation)
	COM_INTERFACE_ENTRY(ILocation)
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
    void Attach(Viewpoint& vp)
    {
        mLocation = vp;
    }
    Viewpoint& GetVP()
    {
        return mLocation;
    }
private:
    Viewpoint mLocation;
public:



};

OBJECT_ENTRY_AUTO(__uuidof(Location), CLocation)
