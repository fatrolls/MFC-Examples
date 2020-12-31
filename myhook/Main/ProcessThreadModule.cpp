#include "stdafx.h"
#include "ProcessThreadModule.h"

//////////////////////////////////////////////////////////////////////
// CProcessThreadModule Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcessThreadModule::CProcessThreadModule()
{
    m_hKernelDll = LoadLibrary("kernel32.dll");
	if (m_hKernelDll == NULL)
	{
		ASSERT(FALSE);
		return;	
	}
	m_pCreateSnap = (CREATETOOLHELP32SNAPSHOT_PROC)GetProcAddress(m_hKernelDll, "CreateToolhelp32Snapshot");
	m_pProcessFirst = (PROCESS32FIRST_PROC)GetProcAddress(m_hKernelDll, "Process32First");
	m_pProcessNext = (PROCESS32NEXT_PROC)GetProcAddress(m_hKernelDll, "Process32Next");
	m_pModuleFirst = (MODULE32FIRST_PROC)GetProcAddress(m_hKernelDll, "Module32First");
	m_pModuleNext = (MODULE32NEXT_PROC)GetProcAddress(m_hKernelDll, "Module32Next");
	m_pThreadFirst = (THREAD32FIRST_PROC)GetProcAddress(m_hKernelDll, "Thread32First");
	m_pThreadNext = (THREAD32NEXT_PROC)GetProcAddress(m_hKernelDll, "Thread32Next");
	m_dwProcessNum = -1;
	m_dwModuleNum = -1;
	m_dwThreadNum = -1;
	m_dwProcessID = -1;
}

CProcessThreadModule::~CProcessThreadModule()
{
    FreeLibrary(m_hKernelDll);
}

bool CProcessThreadModule::EnumProcess()
{
	m_dwProcessNum = -1;
	HANDLE hSnap = m_pCreateSnap(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
		return false;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(entry);
	if (!m_pProcessFirst(hSnap, &entry))
	{
		CloseHandle(hSnap);
		return false;
	}
    m_dwProcessNum = 0;
	do 
	{
		m_Process[m_dwProcessNum] = entry;
		m_dwProcessNum ++;
		if (m_dwProcessNum == MAX_PROCESS_NUM)
			break;
	} while(m_pProcessNext(hSnap, &entry));
	CloseHandle(hSnap);
    m_dwProcessID = 0;
	return true;
}

bool CProcessThreadModule::EnumModule(DWORD dwProcessID)
{
	m_dwModuleNum = -1;
    HANDLE hSnap = m_pCreateSnap(TH32CS_SNAPMODULE, dwProcessID);
	if (hSnap == INVALID_HANDLE_VALUE)
		return false;
    MODULEENTRY32 entry;
	entry.dwSize = sizeof(entry);
	if (!m_pModuleFirst(hSnap, &entry))
	{
		CloseHandle(hSnap);
		return false;
	}
    m_dwModuleNum = 0;
	do 
	{
		m_Module[m_dwModuleNum] = entry;
		m_dwModuleNum ++;
		if (m_dwModuleNum == MAX_MODULE_NUM)
			break;
	} while(m_pModuleNext(hSnap, &entry));
	CloseHandle(hSnap);	
	m_dwProcessID = dwProcessID;
	return true;
}

bool CProcessThreadModule::EnumThread(DWORD dwProcessID)
{
	m_dwThreadNum = -1;
    HANDLE hSnap = m_pCreateSnap(TH32CS_SNAPTHREAD, dwProcessID);
	if (hSnap == INVALID_HANDLE_VALUE)
		return false;
    THREADENTRY32 entry;
	entry.dwSize = sizeof(entry);
	if (!m_pThreadFirst(hSnap, &entry))
	{
		CloseHandle(hSnap);
		return false;
	}
    m_dwThreadNum = 0;
	do 
	{
		m_Thread[m_dwThreadNum] = entry;
		m_dwThreadNum ++;
		if (m_dwThreadNum == MAX_THREAD_NUM)
			break;
	} while(m_pThreadNext(hSnap, &entry));
	CloseHandle(hSnap);	
	m_dwProcessID = dwProcessID;
	return true;
}
