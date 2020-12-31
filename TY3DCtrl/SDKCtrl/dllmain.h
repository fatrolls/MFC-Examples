// dllmain.h : 模块类的声明。

class CSDKCtrlModule : public ATL::CAtlDllModuleT< CSDKCtrlModule >
{
public :
	DECLARE_LIBID(LIBID_SDKCtrlLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SDKCTRL, "{F90F2656-3FDD-40C2-92B2-4E2570F89D9F}")
};

extern class CSDKCtrlModule _AtlModule;
