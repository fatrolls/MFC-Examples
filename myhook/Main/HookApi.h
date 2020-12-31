#ifndef __HHOK_API_H__
#define __HOOK_API_H__

typedef void (WINAPI *APIFUNC)(void);
//API信息结构， 是一个列表
typedef struct _APIINFO
{
	//dll name
	char module_name[100];
	//dll中要被挂钩的函数名称
	char api_name[100];
	//自己的挂钩函数
	char my_api_name[100];
	//友员函数
	char my_friend_api_name[100];
	//函数参数个数
	int param_count;
	//函数开始地址
    int start_pos;
	//APIFUNC
	APIFUNC old_api, my_api;
	//是否正在挂钩
	int bHooking;
	//保存的原始函数的开头20个字节数
	BYTE save_bytes[20];
	//互斥对象
	CRITICAL_SECTION cs;
    //原来函数的保护属性
	DWORD old_protection_flags;
	_APIINFO* pNext;
} APIINFO, *PAPIINFO;

//用于挂钩的类
class CApiInfo
{
public:
	CApiInfo();
	virtual ~CApiInfo();
    //当前列表中挂钩函数的个数
	int m_count;
	//函数挂钩列表
	PAPIINFO m_pList;
    //添加一个挂钩
	PAPIINFO AddHook(char* modulename, char* apiname, char* myapiname, int paramcount, APIFUNC oldapi = NULL,
		             APIFUNC myapi = NULL, char* myfriendapiname = NULL, int startpos = 0);
	//删除所有挂钩函数
	void DeleteAllHooks();
    PAPIINFO FindByMyApi(APIFUNC myapi);
	PAPIINFO FindByOldApi(APIFUNC oldapi);
	PAPIINFO FindByApiName(char* apiname);
	PAPIINFO FindByMyApiName(char* myapiname);
	void Lock(PAPIINFO pInfo);
	void Unlock(PAPIINFO pInfo);
};

bool WINAPI InjectLib(DWORD process_id, char *lib_name);
bool WINAPI InjectLib(HANDLE hProcess, char *lib_name);
bool WINAPI EjectLib(DWORD process_id, char *lib_name);
bool WINAPI EjectLib(HANDLE hProcess, char *lib_name);

#define HOOKAPI_DLL_NAME	"HookAPINT.dll"
#define MY_DLL_NAME			"mydll.dll"

class CHookApi  
{
public:
	CHookApi();
	virtual ~CHookApi();
protected:
	HMODULE m_hMyDll;
	CApiInfo m_apiinfo;
	CString m_strDllPath;
private:
	bool LoadMyDll();
};

#endif
