// dllmain.h : Declaration of module class.

class CSceneCOMModule : public ATL::CAtlDllModuleT< CSceneCOMModule >
{
public :
	DECLARE_LIBID(LIBID_SceneCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SCENECOM, "{C8F21FB5-3265-4F9F-BA74-86D6E315BFD0}")
};

extern class CSceneCOMModule _AtlModule;
