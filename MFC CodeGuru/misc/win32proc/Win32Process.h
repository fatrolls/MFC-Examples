// Win32Process.h: interface for the Win32Process class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WIN32PROCESS_H__3F3A24B1_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
#define AFX_WIN32PROCESS_H__3F3A24B1_FFCD_11D1_A30F_0000B481E689__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "winperf.h"
#include <tlhelp32.h>

typedef HANDLE (WINAPI *PFN_CREATETHELP32SNPSHT)(DWORD,DWORD); 
typedef BOOL (WINAPI *PFN_PROCESS32FIRST)(HANDLE,PROCESSENTRY32*); 
typedef BOOL (WINAPI *PFN_PROCESS32NEXT)(HANDLE,PROCESSENTRY32*); 
#define INITIAL_SIZE        51200
#define EXTEND_SIZE         25600
#define REGKEY_PERF         _T("software\\microsoft\\windows nt\\currentversion\\perflib")
#define REGSUBKEY_COUNTERS  _T("Counters")
#define PROCESS_COUNTER     _T("process")

class Win32Process  
{
public:
	bool IsWinNT();
	CStringArray* GetAllProcessesNames();
	CString GetLastError();
	bool EnumAllProcesses();
	bool GetProcessStatus(CString* procname, bool* status);
	bool Init();
	Win32Process();
	virtual ~Win32Process();

protected:
	TCHAR * ExtractProcessName(TCHAR * path);
	CStringArray m_strArray;
	bool m_bActive;
	bool FindProcesses95(CString* ProcessName, bool);
	bool FindProcessesNT(CString* ProcessName, bool);
	HMODULE m_hWin95Kernel;
	PFN_PROCESS32NEXT m_p_fnProcess32Next;
	PFN_PROCESS32FIRST m_p_fnProcess32First;
	PFN_CREATETHELP32SNPSHT m_p_fnCreateToolhelp32Snapshot;
	CString m_strLastError;
	bool m_bIsNt;
};

#endif // !defined(AFX_WIN32PROCESS_H__3F3A24B1_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
