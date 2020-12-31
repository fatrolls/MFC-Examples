// dllmain.h : 模块类的声明。

class CProjectTreeCOMModule : public ATL::CAtlDllModuleT< CProjectTreeCOMModule >
{
public :
	DECLARE_LIBID(LIBID_ProjectTreeCOMLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROJECTTREECOM, "{0F170C2E-09A5-46FB-962F-477B93C9D221}")
};

extern class CProjectTreeCOMModule _AtlModule;
