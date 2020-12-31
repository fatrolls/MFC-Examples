// dllmain.h : 模块类的声明。

class CDataSourceCOMModule : public ATL::CAtlDllModuleT< CDataSourceCOMModule >
{
public :
	DECLARE_LIBID(LIBID_DataSourceCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_DATASOURCECOM, "{821440B0-0D92-46E2-AF95-643ECF9E80E9}")
};

extern class CDataSourceCOMModule _AtlModule;
