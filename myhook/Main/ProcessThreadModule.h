#ifndef __PROCESS_THREAD_MODULE_H__
#define __PROCESS_THREAD_MODULE_H__

#define MAX_PROCESS_NUM 128
#define MAX_MODULE_NUM 500
#define MAX_THREAD_NUM 1024

#include <tlhelp32.h>
typedef HANDLE (WINAPI *CREATETOOLHELP32SNAPSHOT_PROC)(DWORD dwFlags, DWORD th32ProcessID);
typedef BOOL (WINAPI *PROCESS32FIRST_PROC)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL (WINAPI *PROCESS32NEXT_PROC)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);
typedef BOOL (WINAPI *MODULE32FIRST_PROC)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL (WINAPI *MODULE32NEXT_PROC)(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
typedef BOOL (WINAPI *THREAD32FIRST_PROC)(HANDLE hSnapshot, LPTHREADENTRY32 lpme);
typedef BOOL (WINAPI *THREAD32NEXT_PROC)(HANDLE hSnapshot, LPTHREADENTRY32 lpme);

class CProcessThreadModule  
{
public:
	bool EnumModule(DWORD dwProcessID);
	bool EnumThread(DWORD dwProcessID);
	bool EnumProcess();
	CProcessThreadModule();
	virtual ~CProcessThreadModule();

	DWORD m_dwProcessNum;
	DWORD m_dwThreadNum;
	DWORD m_dwModuleNum;
	PROCESSENTRY32 m_Process[MAX_PROCESS_NUM];
	MODULEENTRY32  m_Module[MAX_MODULE_NUM];
	THREADENTRY32  m_Thread[MAX_THREAD_NUM];
protected:
	DWORD m_dwProcessID;
	HMODULE m_hKernelDll;
    CREATETOOLHELP32SNAPSHOT_PROC m_pCreateSnap;
    PROCESS32FIRST_PROC  m_pProcessFirst;
    PROCESS32NEXT_PROC   m_pProcessNext;
	MODULE32FIRST_PROC   m_pModuleFirst;
    MODULE32NEXT_PROC    m_pModuleNext;
	THREAD32FIRST_PROC   m_pThreadFirst;
    THREAD32NEXT_PROC    m_pThreadNext;
};

#endif