//////////////////////////////////////////////////////////////////////////////
//
//	File:		tracelnk.cpp
//	Module:		tracelnk.dll
//	Copyright:	1996-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
#define _WIN32_WINNT		0x0400
#define WIN32
#define NT

#define DBG_TRACE   0

#include <windows.h>
#include <stdio.h>
#include "detours.h"
#include "syelog.h"

#define PULONG_PTR			PVOID
#define PLONG_PTR			PVOID
#define ULONG_PTR			PVOID
#define LONG_PTR			PVOID
#define ENUMRESNAMEPROCA 	PVOID
#define ENUMRESNAMEPROCW 	PVOID
#define ENUMRESLANGPROCA 	PVOID
#define ENUMRESLANGPROCW 	PVOID
#define ENUMRESTYPEPROCA 	PVOID
#define ENUMRESTYPEPROCW 	PVOID
#define STGOPTIONS          PVOID

//////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4127)   // Many of our asserts are constants.

#ifndef _DEFINED_ASMBREAK_
#define _DEFINED_ASMBREAK_
#define ASMBREAK()	__asm { int 3 }
//#define ASMBREAK()	DebugBreak()
#endif	// _DEFINED_ASMBREAK_

#define ASSERT_ALWAYS(x)   \
    do {                                                        \
	if (!(x)) {                                                 \
            AssertMessage(#x, __FILE__, __LINE__);              \
			ASMBREAK();                                         \
	}                                                           \
    } while (0)

#ifndef NDEBUG
#define ASSERT(x)           ASSERT_ALWAYS(x)
#else
#define ASSERT(x)
#endif

#define UNUSED(c)    (c) = (c)
#define ARRAYOF(x)	   	(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////////////
static HMODULE s_hInst = NULL;
static WCHAR s_wzDllPath[MAX_PATH];

BOOL ProcessEnumerate();
BOOL InstanceEnumerate(HINSTANCE hInst);
BOOL ImportEnumerate(HINSTANCE hInst);

VOID _PrintEnter(const CHAR *psz, ...);
VOID _PrintExit(const CHAR *psz, ...);
VOID _Print(const CHAR *psz, ...);
VOID _VPrint(PCSTR msg, va_list args, PCHAR pszBuf, LONG cbBuf);

VOID AssertMessage(CONST PCHAR pszMsg, CONST PCHAR pszFile, ULONG nLine);

//////////////////////////////////////////////////////////////////////////////
//
// Trampolines
//

#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

extern "C" {
    //  Trampolines for SYELOG library.
    //
    DETOUR_TRAMPOLINE(HANDLE WINAPI
                      Real_CreateFileW(LPCWSTR a0, DWORD a1, DWORD a2,
                                       LPSECURITY_ATTRIBUTES a3, DWORD a4, DWORD a5,
                                       HANDLE a6),
                      CreateFileW);

    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_WriteFile(HANDLE hFile,
                                     LPCVOID lpBuffer,
                                     DWORD nNumberOfBytesToWrite,
                                     LPDWORD lpNumberOfBytesWritten,
                                     LPOVERLAPPED lpOverlapped),
                      WriteFile);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_FlushFileBuffers(HANDLE hFile),
                      FlushFileBuffers);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_CloseHandle(HANDLE hObject),
                      CloseHandle);

    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_WaitNamedPipeW(LPCWSTR lpNamedPipeName, DWORD nTimeOut),
                      WaitNamedPipeW);
    DETOUR_TRAMPOLINE(BOOL WINAPI
                      Real_SetNamedPipeHandleState(HANDLE hNamedPipe,
                                                   LPDWORD lpMode,
                                                   LPDWORD lpMaxCollectionCount,
                                                   LPDWORD lpCollectDataTimeout),
                      SetNamedPipeHandleState);

    DETOUR_TRAMPOLINE(DWORD WINAPI
                      Real_GetCurrentProcessId(VOID),
                      GetCurrentProcessId);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime),
                      GetSystemTimeAsFileTime);

    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_InitializeCriticalSection(LPCRITICAL_SECTION lpSection),
                      InitializeCriticalSection);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_EnterCriticalSection(LPCRITICAL_SECTION lpSection),
                      EnterCriticalSection);
    DETOUR_TRAMPOLINE(VOID WINAPI
                      Real_LeaveCriticalSection(LPCRITICAL_SECTION lpSection),
                      LeaveCriticalSection);
}

DETOUR_TRAMPOLINE(BOOL WINAPI
                  Real_FreeLibrary(HMODULE a0),
                  FreeLibrary);

DETOUR_TRAMPOLINE(DWORD WINAPI
                  Real_GetModuleFileNameW(HMODULE a0,
                                          LPWSTR a1,
                                          DWORD a2),
                  GetModuleFileNameW);

DETOUR_TRAMPOLINE(HMODULE WINAPI
                  Real_GetModuleHandleW(LPCWSTR a0),
                  GetModuleHandleW);

DETOUR_TRAMPOLINE(FARPROC WINAPI
                  Real_GetProcAddress(HMODULE a0,
                                      LPCSTR a1),
                  GetProcAddress);

DETOUR_TRAMPOLINE(HMODULE WINAPI
                  Real_LoadLibraryExW(LPCWSTR a0,
                                      HANDLE a1,
                                      DWORD a2),
                  LoadLibraryExW);

DETOUR_TRAMPOLINE(HMODULE WINAPI
                  Real_LoadLibraryW(LPCWSTR a0),
                  LoadLibraryW);

//////////////////////////////////////////////////////////////////////////////
//
BOOL WINAPI Mine_FreeLibrary(HMODULE a0)
{
    return TRUE;
}

DWORD WINAPI Mine_GetModuleFileNameW(HMODULE a0,
                                     LPWSTR a1,
                                     DWORD a2)
{
    return Real_GetModuleFileNameW(a0, a1, a2);
}

HMODULE WINAPI Mine_GetModuleHandleW(LPCWSTR a0)
{
    return Real_GetModuleHandleW(a0);
}

FARPROC WINAPI Mine_GetProcAddress(HMODULE a0,
                                   LPCSTR a1)
{
    _PrintEnter("GetProcAddress(%x,%hs)\n", a0, a1);

    FARPROC rv = 0;
    __try {
        rv = Real_GetProcAddress(a0, a1);
    } __finally {
        _PrintExit("GetProcAddress(,) -> %x\n", rv);
    };
    return rv;
}

HMODULE WINAPI Mine_LoadLibraryExW(LPCWSTR a0,
                                   HANDLE a1,
                                   DWORD a2)
{
    _PrintEnter("LoadLibraryExW(%ls,%x,%x)\n", a0, a1, a2);

    HMODULE rv = 0;
    __try {
        rv = Real_LoadLibraryExW(a0, a1, a2);
    } __finally {
        _PrintExit("LoadLibraryExW(,,) -> %x\n", rv);
		if (rv) {
			InstanceEnumerate(rv);
            ImportEnumerate(rv);
		}
    };
    return rv;
}

HMODULE WINAPI Mine_LoadLibraryW(LPCWSTR a0)
{
    _PrintEnter("LoadLibraryW(%ls)\n", a0);

    HMODULE rv = 0;
    __try {
        rv = Real_LoadLibraryW(a0);
    } __finally {
        _PrintExit("LoadLibraryW() -> %x\n", rv);
    };
    return rv;
}

/////////////////////////////////////////////////////////////
// TrampolineWith
//
VOID TrampolineWith(VOID)
{
#define DETOUR(x,y)   DetourFunctionWithTrampoline((PBYTE)x, (PBYTE)y)
    DETOUR(Real_FreeLibrary, Mine_FreeLibrary);
    DETOUR(Real_GetModuleHandleW, Mine_GetModuleHandleW);
    DETOUR(Real_GetProcAddress, Mine_GetProcAddress);
    DETOUR(Real_LoadLibraryExW, Mine_LoadLibraryExW);
    DETOUR(Real_LoadLibraryW, Mine_LoadLibraryW);
}

////////////////////////////////////////////////////////////// Logging System.
//
static BOOL s_bLog = 1;
static LONG s_nTlsIndent = -1;
static LONG s_nTlsThread = -1;
static LONG s_nThreadCnt = 0;

VOID _PrintEnter(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent);
		TlsSetValue(s_nTlsIndent, (PVOID)(nIndent + 1));
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}
		
	if (s_bLog && psz) {
		CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
		*pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

		va_list  args;
		va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

		va_end(args);
	}
	SetLastError(dwErr);
}

VOID _PrintExit(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent) - 1;
        ASSERT(nIndent >= 0);
		TlsSetValue(s_nTlsIndent, (PVOID)nIndent);
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}
		
	if (s_bLog && psz) {
		CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
		*pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

		va_list  args;
		va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

		va_end(args);
	}
	SetLastError(dwErr);
}

VOID _Print(const CHAR *psz, ...)
{
	DWORD dwErr = GetLastError();
	
	LONG nIndent = 0;
	LONG nThread = 0;
	if (s_nTlsIndent >= 0) {
		nIndent = (LONG)TlsGetValue(s_nTlsIndent);
	}
	if (s_nTlsThread >= 0) {
		nThread = (LONG)TlsGetValue(s_nTlsThread);
	}

	if (s_bLog && psz) {
        CHAR szBuf[1024];
        PCHAR pszBuf = szBuf;
		LONG nLen = (nIndent > 0) ? (nIndent < 35 ? nIndent * 2 : 70) : 0;
        *pszBuf++ = (CHAR)('0' + ((nThread / 100) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 10) % 10));
		*pszBuf++ = (CHAR)('0' + ((nThread / 1) % 10));
        *pszBuf++ = ' ';
        while (nLen-- > 0) {
            *pszBuf++ = ' ';
        }

        va_list  args;
        va_start(args, psz);

        while ((*pszBuf++ = *psz++) != 0) {
            // Copy characters.
        }
        SyelogV(SYELOG_SEVERITY_INFORMATION,
                szBuf, args);

        va_end(args);
	}
	SetLastError(dwErr);
}

VOID AssertMessage(CONST PCHAR pszMsg, CONST PCHAR pszFile, ULONG nLine)
{
    Syelog(SYELOG_SEVERITY_FATAL,
           "ASSERT(%s) failed in %s, line %d.\n", pszMsg, pszFile, nLine);
}

VOID NullExport()
{
}

//////////////////////////////////////////////////////////////////////////////
//
PIMAGE_NT_HEADERS NtHeadersForInstance(HINSTANCE hInst)
{
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hInst;
	__try {
		if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
			SetLastError(ERROR_BAD_EXE_FORMAT);
			return NULL;
		}
		
		PIMAGE_NT_HEADERS pNtHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader +
														  pDosHeader->e_lfanew);
		if (pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
			SetLastError(ERROR_INVALID_EXE_SIGNATURE);
			return NULL;
		}
		if (pNtHeader->FileHeader.SizeOfOptionalHeader == 0) {
			SetLastError(ERROR_EXE_MARKED_INVALID);
			return NULL;
		}
		return pNtHeader;
	} __except(EXCEPTION_EXECUTE_HANDLER) {
	}
	SetLastError(ERROR_EXE_MARKED_INVALID);
	
	return NULL;
}

static inline PBYTE RvaToVa(PBYTE pbBase, UINT nOffset)
{
    return nOffset ? pbBase + nOffset : NULL;
}

BOOL ImportEnumerate(HINSTANCE hInst)
{
    PBYTE pbBase = (PBYTE)hInst;
	PIMAGE_NT_HEADERS pNtHeader;					// Read & Write
	PIMAGE_SECTION_HEADER pSectionHeaders;
	DWORD nPeOffset;
	DWORD nSectionsOffset;
	
	////////////////////////////////////////////////////// Process DOS Header.
	//
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)pbBase;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) {
		return FALSE;
	}
	nPeOffset = pDosHeader->e_lfanew;

	/////////////////////////////////////////////////////// Process PE Header.
	//
    pNtHeader = (PIMAGE_NT_HEADERS)RvaToVa(pbBase, nPeOffset);
	if (pNtHeader->Signature != IMAGE_NT_SIGNATURE) {
		return FALSE;
	}
	if (pNtHeader->FileHeader.SizeOfOptionalHeader == 0) {
		return FALSE;
	}
	nSectionsOffset = nPeOffset
		+ sizeof(pNtHeader->Signature)
		+ sizeof(pNtHeader->FileHeader)
		+ pNtHeader->FileHeader.SizeOfOptionalHeader;

	///////////////////////////////////////////////// Process Section Headers.
	//
    pSectionHeaders = (PIMAGE_SECTION_HEADER)RvaToVa(pbBase, nSectionsOffset);

	//////////////////////////////////////////////////////// Get Import Table.
	//
	DWORD rvaImageDirectory = pNtHeader->OptionalHeader
		.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress;
	PIMAGE_IMPORT_DESCRIPTOR iidp
		= (PIMAGE_IMPORT_DESCRIPTOR)RvaToVa(pbBase, rvaImageDirectory);
    
	if (iidp == NULL) {
		return FALSE;
	}

    for (DWORD nFiles = 0; iidp[nFiles].Characteristics != 0; nFiles++) {
        // Count the files.
    }
    
    for (DWORD n = 0; n < nFiles; n++, iidp++) {
        DWORD rvaName = iidp->Name;
        PCHAR pszName = (PCHAR)RvaToVa(pbBase, rvaName);
        
        DWORD rvaThunk = (DWORD)iidp->OriginalFirstThunk;
        PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)RvaToVa(pbBase, rvaThunk);
        rvaThunk = (DWORD)iidp->FirstThunk;
        PIMAGE_THUNK_DATA pBoundThunk = (PIMAGE_THUNK_DATA)RvaToVa(pbBase, rvaThunk);

        Syelog(SYELOG_SEVERITY_INFORMATION,
               "%s [%08x %08x]\n", pszName, pThunk, pBoundThunk);
        
        DWORD nNames = 0;
        if (pThunk == NULL) {
            break;
        }
        
        for (; pThunk[nNames].u1.Ordinal; nNames++) {
            // Count the imports.
        }   

        for (DWORD f = 0; f < nNames; f++) {
            DWORD nOrdinal = 0;
            PCHAR pszName = NULL;
            PDWORD pFunc = (PDWORD)pBoundThunk[f].u1.Function;
            
            DWORD rvaName = pThunk[f].u1.Ordinal;
            if (rvaName & IMAGE_ORDINAL_FLAG) {
                nOrdinal = IMAGE_ORDINAL(rvaName);
            }
            else {
                PIMAGE_IMPORT_BY_NAME pName
                    = (PIMAGE_IMPORT_BY_NAME)RvaToVa(pbBase, rvaName);
                if (pName) {
                    pszName = (PCHAR)pName->Name;
                }
            }
            Syelog(SYELOG_SEVERITY_INFORMATION,
                   "  %-32.32s %4d %08x\n", pszName, nOrdinal, pFunc);
        }
    }
	return TRUE;
}

BOOL InstanceEnumerate(HINSTANCE hInst)
{
	WCHAR wzDllName[MAX_PATH];

	PIMAGE_NT_HEADERS pinh = NtHeadersForInstance(hInst);
	if (pinh && Real_GetModuleFileNameW(hInst, wzDllName, ARRAYOF(wzDllName))) {
        Syelog(SYELOG_SEVERITY_INFORMATION,
               "### %08lx: %-43.43ls %08x\n",
               hInst, wzDllName, pinh->OptionalHeader.CheckSum);
        return TRUE;
	}
	return FALSE;
}

BOOL ProcessEnumerate()
{
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "######################################################### Binaries\n");
	for (HINSTANCE hInst = NULL; (hInst = DetourEnumerateModules(hInst)) != NULL;) {
		InstanceEnumerate(hInst);
	}
    Syelog(SYELOG_SEVERITY_INFORMATION, "###\n");

    return ImportEnumerate(GetModuleHandle(NULL));
}

//////////////////////////////////////////////////////////////////////////////
//
// DLL module information
//
BOOL ThreadAttach(HMODULE hDll)
{
	if (s_nTlsIndent >= 0) {
		TlsSetValue(s_nTlsIndent, (PVOID)0);
	}
	if (s_nTlsThread >= 0) {
		LONG nThread = InterlockedIncrement(&s_nThreadCnt);
		TlsSetValue(s_nTlsThread, (PVOID)nThread);
	}
	return TRUE;
}

BOOL ThreadDetach(HMODULE hDll)
{
	if (s_nTlsIndent >= 0) {
		TlsSetValue(s_nTlsIndent, (PVOID)0);
	}
	if (s_nTlsThread >= 0) {
		TlsSetValue(s_nTlsThread, (PVOID)0);
	}
	return TRUE;
}

BOOL ProcessAttach(HMODULE hDll)
{
	s_bLog = FALSE;
	s_nTlsIndent = TlsAlloc();
	s_nTlsThread = TlsAlloc();
	ThreadAttach(hDll);
	
	WCHAR wzExeName[MAX_PATH];

    s_hInst = hDll;
	Real_GetModuleFileNameW(hDll, s_wzDllPath, ARRAYOF(s_wzDllPath));
	Real_GetModuleFileNameW(NULL, wzExeName, ARRAYOF(wzExeName));

    SyelogOpen("tracelnk", SYELOG_FACILITY_APPLICATION);
	ProcessEnumerate();
    
	TrampolineWith();

	s_bLog = TRUE;
	return TRUE;
}

BOOL ProcessDetach(HMODULE hDll)
{
	ThreadDetach(hDll);
	
	s_bLog = FALSE;
    SyelogClose();

	if (s_nTlsIndent >= 0) {
		TlsFree(s_nTlsIndent);
	}
	if (s_nTlsThread >= 0) {
		TlsFree(s_nTlsThread);
	}
	return TRUE;
}

BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD dwReason, PVOID lpReserved)
{
	switch (dwReason) {
	  case DLL_PROCESS_ATTACH:
		return ProcessAttach(hModule);
	  case DLL_PROCESS_DETACH:
		return ProcessDetach(hModule);
	  case DLL_THREAD_ATTACH:
		return ThreadAttach(hModule);
	  case DLL_THREAD_DETACH:
		return ThreadDetach(hModule);
	}
	return TRUE;
}
//
///////////////////////////////////////////////////////////////// End of File.
