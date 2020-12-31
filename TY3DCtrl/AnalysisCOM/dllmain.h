// dllmain.h : 模块类的声明。

class CAnalysisCOMModule : public ATL::CAtlDllModuleT< CAnalysisCOMModule >
{
public :
	DECLARE_LIBID(LIBID_AnalysisCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ANALYSISCOM, "{FE048A35-9386-450C-AAE9-2B5817C2D5DB}")
};

extern class CAnalysisCOMModule _AtlModule;
