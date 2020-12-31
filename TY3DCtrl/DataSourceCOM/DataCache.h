// DataCache.h : CDataCache 的声明

#pragma once
#include "resource.h"       // 主符号



#include "DataSourceCOM_i.h"
#include "_IDataCacheEvents_CP.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;


// CDataCache

class ATL_NO_VTABLE CDataCache :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataCache, &CLSID_DataCache>,
	public IConnectionPointContainerImpl<CDataCache>,
	public CProxy_IDataCacheEvents<CDataCache>,
	public IDispatchImpl<IDataCache, &IID_IDataCache, &LIBID_DataSourceCOMLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CDataCache()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DATACACHE)


BEGIN_COM_MAP(CDataCache)
	COM_INTERFACE_ENTRY(IDataCache)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CDataCache)
	CONNECTION_POINT_ENTRY(__uuidof(_IDataCacheEvents))
END_CONNECTION_POINT_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
    STDMETHOD(CheckNew)(LONG id, LONG version, VARIANT_BOOL* b);
    STDMETHOD(BeginCache)(LONG id, BSTR url);


};

OBJECT_ENTRY_AUTO(__uuidof(DataCache), CDataCache)
