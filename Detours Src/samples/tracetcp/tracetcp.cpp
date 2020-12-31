//////////////////////////////////////////////////////////////////////
//
//	File:		tracetcp.cpp
//	Module:		tracetcp.dll
//	Copyright:	1996-2001, Microsoft Corporation
//
//	Microsoft Research Detours Package Version 1.5 (Build 46)
//
#define _WIN32_WINNT		0x0400
#define WIN32
#define NT

#define DBG_TRACE   0

#if _MSC_VER >= 1300
#include <winsock2.h>
#endif
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

//////////////////////////////////////////////////////////////////////
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

#define UNUSED(c)    	(c) = (c)
#define ARRAYOF(x)	   	(sizeof(x)/sizeof(x[0]))

//////////////////////////////////////////////////////////////////////
static HMODULE s_hInst = NULL;
static WCHAR s_wzDllPath[MAX_PATH];

VOID _PrintDump(SOCKET socket, PCHAR pszData, INT cbData);
VOID _PrintEnter(PCSTR psz, ...);
VOID _PrintExit(PCSTR psz, ...);
VOID _Print(PCSTR psz, ...);

VOID AssertMessage(CONST PCHAR pszMsg, CONST PCHAR pszFile, ULONG nLine);

//////////////////////////////////////////////////////////////////////////////
//
#pragma warning(disable:4100)   // Trampolines don't use formal parameters.

extern "C" {
    DETOUR_TRAMPOLINE(HANDLE WINAPI
                      Real_CreateFileW(LPCWSTR a0,
                                       DWORD a1,
                                       DWORD a2,
                                       LPSECURITY_ATTRIBUTES a3,
                                       DWORD a4,
                                       DWORD a5,
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

DETOUR_TRAMPOLINE(DWORD WINAPI Real_GetModuleFileNameW(HMODULE a0,
                                                          LPWSTR a1,
                                                          DWORD a2),
                  GetModuleFileNameW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_CreateProcessW(LPCWSTR a0,
                                                     LPWSTR a1,
                                                     LPSECURITY_ATTRIBUTES a2,
                                                     LPSECURITY_ATTRIBUTES a3,
                                                     BOOL a4,
                                                     DWORD a5,
                                                     LPVOID a6,
                                                     LPCWSTR a7,
                                                     struct _STARTUPINFOW* a8,
                                                     LPPROCESS_INFORMATION a9),
                  CreateProcessW);

DETOUR_TRAMPOLINE(SOCKET WINAPI Real_WSAAccept(SOCKET a0,
                                                  sockaddr* a1,
                                                  LPINT a2,
                                                  LPCONDITIONPROC a3,
                                                  DWORD a4),
                  WSAAccept);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAAddressToStringA(LPSOCKADDR a0,
                                                         DWORD a1,
                                                         struct _WSAPROTOCOL_INFOA* a2,
                                                         LPSTR a3,
                                                         LPDWORD a4),
                  WSAAddressToStringA);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAAddressToStringW(LPSOCKADDR a0,
                                                         DWORD a1,
                                                         struct _WSAPROTOCOL_INFOW* a2,
                                                         LPWSTR a3,
                                                         LPDWORD a4),
                  WSAAddressToStringW);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetHostByAddr(HWND a0,
                                                              u_int a1,
                                                              char* a2,
                                                              int a3,
                                                              int a4,
                                                              char* a5,
                                                              int a6),
                  WSAAsyncGetHostByAddr);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetHostByName(HWND a0,
                                                              u_int a1,
                                                              char* a2,
                                                              char* a3,
                                                              int a4),
                  WSAAsyncGetHostByName);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetProtoByName(HWND a0,
                                                               u_int a1,
                                                               char* a2,
                                                               char* a3,
                                                               int a4),
                  WSAAsyncGetProtoByName);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetProtoByNumber(HWND a0,
                                                                 u_int a1,
                                                                 int a2,
                                                                 char* a3,
                                                                 int a4),
                  WSAAsyncGetProtoByNumber);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetServByName(HWND a0,
                                                              u_int a1,
                                                              char* a2,
                                                              char* a3,
                                                              char* a4,
                                                              int a5),
                  WSAAsyncGetServByName);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSAAsyncGetServByPort(HWND a0,
                                                              u_int a1,
                                                              int a2,
                                                              char* a3,
                                                              char* a4,
                                                              int a5),
                  WSAAsyncGetServByPort);

DETOUR_TRAMPOLINE(int WINAPI Real_WSACancelAsyncRequest(HANDLE a0),
                  WSACancelAsyncRequest);

DETOUR_TRAMPOLINE(int WINAPI Real_WSACancelBlockingCall(void),
                  WSACancelBlockingCall);

DETOUR_TRAMPOLINE(int WINAPI Real_WSACleanup(void),
                  WSACleanup);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_WSACloseEvent(HANDLE a0),
                  WSACloseEvent);

DETOUR_TRAMPOLINE(int WINAPI Real_WSAConnect(SOCKET a0,
                                                sockaddr* a1,
                                                int a2,
                                                LPWSABUF a3,
                                                LPWSABUF a4,
                                                LPQOS a5,
                                                LPQOS a6),
                  WSAConnect);

DETOUR_TRAMPOLINE(HANDLE WINAPI Real_WSACreateEvent(void),
                  WSACreateEvent);

DETOUR_TRAMPOLINE(int WINAPI Real_WSADuplicateSocketA(SOCKET a0,
                                                         DWORD a1,
                                                         struct _WSAPROTOCOL_INFOA* a2),
                  WSADuplicateSocketA);

DETOUR_TRAMPOLINE(int WINAPI Real_WSADuplicateSocketW(SOCKET a0,
                                                         DWORD a1,
                                                         struct _WSAPROTOCOL_INFOW* a2),
                  WSADuplicateSocketW);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAEnumNameSpaceProvidersA(LPDWORD a0,
                                                                LPWSANAMESPACE_INFOA a1),
                  WSAEnumNameSpaceProvidersA);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAEnumNameSpaceProvidersW(LPDWORD a0,
                                                                LPWSANAMESPACE_INFOW a1),
                  WSAEnumNameSpaceProvidersW);

DETOUR_TRAMPOLINE(int WINAPI Real_WSAEnumNetworkEvents(SOCKET a0,
                                                          HANDLE a1,
                                                          LPWSANETWORKEVENTS a2),
                  WSAEnumNetworkEvents);

DETOUR_TRAMPOLINE(int WINAPI Real_WSAEnumProtocolsA(LPINT a0,
                                                       struct _WSAPROTOCOL_INFOA* a1,
                                                       LPDWORD a2),
                  WSAEnumProtocolsA);

DETOUR_TRAMPOLINE(int WINAPI Real_WSAEnumProtocolsW(LPINT a0,
                                                       struct _WSAPROTOCOL_INFOW* a1,
                                                       LPDWORD a2),
                  WSAEnumProtocolsW);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_WSAGetOverlappedResult(SOCKET a0,
                                                             LPWSAOVERLAPPED a1,
                                                             LPDWORD a2,
                                                             BOOL a3,
                                                             LPDWORD a4),
                  WSAGetOverlappedResult);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_WSAIsBlocking(void),
                  WSAIsBlocking);

DETOUR_TRAMPOLINE(SOCKET WINAPI Real_WSAJoinLeaf(SOCKET a0,
                                                    sockaddr* a1,
                                                    int a2,
                                                    LPWSABUF a3,
                                                    LPWSABUF a4,
                                                    LPQOS a5,
                                                    LPQOS a6,
                                                    DWORD a7),
                  WSAJoinLeaf);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAProviderConfigChange(LPHANDLE a0,
                                                             LPWSAOVERLAPPED a1,
                                                             LPWSAOVERLAPPED_COMPLETION_ROUTINE a2),
                  WSAProviderConfigChange);

DETOUR_TRAMPOLINE(int WINAPI Real_WSARecv(SOCKET a0,
                                             LPWSABUF a1,
                                             DWORD a2,
                                             LPDWORD a3,
                                             LPDWORD a4,
                                             LPWSAOVERLAPPED a5,
                                             LPWSAOVERLAPPED_COMPLETION_ROUTINE a6),
                  WSARecv);

DETOUR_TRAMPOLINE(int WINAPI Real_WSARecvDisconnect(SOCKET a0,
                                                       LPWSABUF a1),
                  WSARecvDisconnect);

DETOUR_TRAMPOLINE(int WINAPI Real_WSARecvFrom(SOCKET a0,
                                                 LPWSABUF a1,
                                                 DWORD a2,
                                                 LPDWORD a3,
                                                 LPDWORD a4,
                                                 sockaddr* a5,
                                                 LPINT a6,
                                                 LPWSAOVERLAPPED a7,
                                                 LPWSAOVERLAPPED_COMPLETION_ROUTINE a8),
                  WSARecvFrom);

DETOUR_TRAMPOLINE(BOOL WINAPI Real_WSAResetEvent(HANDLE a0),
                  WSAResetEvent);

DETOUR_TRAMPOLINE(int WINAPI Real_WSASend(SOCKET a0,
                                             LPWSABUF a1,
                                             DWORD a2,
                                             LPDWORD a3,
                                             DWORD a4,
                                             LPWSAOVERLAPPED a5,
                                             LPWSAOVERLAPPED_COMPLETION_ROUTINE a6),
                  WSASend);

DETOUR_TRAMPOLINE(int WINAPI Real_WSASendDisconnect(SOCKET a0,
                                                       LPWSABUF a1),
                  WSASendDisconnect);

DETOUR_TRAMPOLINE(int WINAPI Real_WSASendTo(SOCKET a0,
                                               LPWSABUF a1,
                                               DWORD a2,
                                               LPDWORD a3,
                                               DWORD a4,
                                               sockaddr* a5,
                                               int a6,
                                               LPWSAOVERLAPPED a7,
                                               LPWSAOVERLAPPED_COMPLETION_ROUTINE a8),
                  WSASendTo);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAStringToAddressA(LPSTR a0,
                                                         INT a1,
                                                         struct _WSAPROTOCOL_INFOA* a2,
                                                         LPSOCKADDR a3,
                                                         LPINT a4),
                  WSAStringToAddressA);

DETOUR_TRAMPOLINE(INT WINAPI Real_WSAStringToAddressW(LPWSTR a0,
                                                         INT a1,
                                                         struct _WSAPROTOCOL_INFOW* a2,
                                                         LPSOCKADDR a3,
                                                         LPINT a4),
                  WSAStringToAddressW);

DETOUR_TRAMPOLINE(DWORD WINAPI Real_WSAWaitForMultipleEvents(DWORD a0,
                                                                void** a1,
                                                                BOOL a2,
                                                                DWORD a3,
                                                                BOOL a4),
                  WSAWaitForMultipleEvents);

DETOUR_TRAMPOLINE(SOCKET WINAPI Real_accept(SOCKET a0,
                                               sockaddr* a1,
                                               int* a2),
                  accept);

DETOUR_TRAMPOLINE(int WINAPI Real_closesocket(SOCKET a0),
                  closesocket);

DETOUR_TRAMPOLINE(int WINAPI Real_connect(SOCKET a0,
                                             sockaddr* a1,
                                             int a2),
                  connect);

DETOUR_TRAMPOLINE(int WINAPI Real_listen(SOCKET a0,
                                            int a1),
                  listen);

DETOUR_TRAMPOLINE(int WINAPI Real_recv(SOCKET a0,
                                          char* a1,
                                          int a2,
                                          int a3),
                  recv);

DETOUR_TRAMPOLINE(int WINAPI Real_recvfrom(SOCKET a0,
                                              char* a1,
                                              int a2,
                                              int a3,
                                              sockaddr* a4,
                                              int* a5),
                  recvfrom);

DETOUR_TRAMPOLINE(int WINAPI Real_send(SOCKET a0,
                                          char* a1,
                                          int a2,
                                          int a3),
                  send);

DETOUR_TRAMPOLINE(int WINAPI Real_sendto(SOCKET a0,
                                            char* a1,
                                            int a2,
                                            int a3,
                                            sockaddr* a4,
                                            int a5),
                  sendto);

DETOUR_TRAMPOLINE(int WINAPI Real_shutdown(SOCKET a0,
                                              int a1),
                  shutdown);

/////////////////////////////////////////////////////////////
// Detours
//
BOOL WINAPI Mine_CreateProcessW(LPCWSTR lpApplicationName,
                                LPWSTR lpCommandLine,
                                LPSECURITY_ATTRIBUTES lpProcessAttributes,
                                LPSECURITY_ATTRIBUTES lpThreadAttributes,
                                BOOL bInheritHandles,
                                DWORD dwCreationFlags,
                                LPVOID lpEnvironment,
                                LPCWSTR lpCurrentDirectory,
                                LPSTARTUPINFOW lpStartupInfo,
                                LPPROCESS_INFORMATION lpProcessInformation)
{
    _PrintEnter("CreateProcessW(%ls,%ls,%lx,%lx,%lx,%lx,%lx,%ls,%lx,%lx)\n",
                lpApplicationName,
                lpCommandLine,
                lpProcessAttributes,
                lpThreadAttributes,
                bInheritHandles,
                dwCreationFlags,
                lpEnvironment,
                lpCurrentDirectory,
                lpStartupInfo,
                lpProcessInformation);

    _Print("Calling DetourCreateProcessWithDllW(,%ls)\n", s_wzDllPath);
    
    BOOL rv = 0;
    __try {
        rv = DetourCreateProcessWithDllW(lpApplicationName,
                                   lpCommandLine,
                                   lpProcessAttributes,
                                   lpThreadAttributes,
                                   bInheritHandles,
                                   dwCreationFlags,
                                   lpEnvironment,
                                   lpCurrentDirectory,
                                   lpStartupInfo,
                                   lpProcessInformation,
                                   s_wzDllPath,
                                   Real_CreateProcessW);
    } __finally {
        _PrintExit("CreateProcessW(,,,,,,,,,) -> %lx\n", rv);
    };
    return rv;
}

SOCKET WINAPI Mine_WSAAccept(SOCKET a0,
                                sockaddr* a1,
                                LPINT a2,
                                LPCONDITIONPROC a3,
                                DWORD a4)
{

    SOCKET rv = 0;
    __try {
        rv = Real_WSAAccept(a0, a1, a2, a3, a4);
    } __finally {
		_PrintEnter("%lx: WSAAccept(,%lx,%lx,%lx,%lx) -> %lx\n", a0, a1, a2, a3, a4, rv);
        _PrintExit(NULL);
    };
    return rv;
}

INT WINAPI Mine_WSAAddressToStringA(LPSOCKADDR a0,
                                       DWORD a1,
                                       struct _WSAPROTOCOL_INFOA* a2,
                                       LPSTR a3,
                                       LPDWORD a4)
{
    _PrintEnter("WSAAddressToStringA(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    INT rv = 0;
    __try {
        rv = Real_WSAAddressToStringA(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAAddressToStringA(,,,,) -> %lx\n", rv);
    };
    return rv;
}

INT WINAPI Mine_WSAAddressToStringW(LPSOCKADDR a0,
                                       DWORD a1,
                                       struct _WSAPROTOCOL_INFOW* a2,
                                       LPWSTR a3,
                                       LPDWORD a4)
{
    _PrintEnter("WSAAddressToStringW(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    INT rv = 0;
    __try {
        rv = Real_WSAAddressToStringW(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAAddressToStringW(,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetHostByAddr(HWND a0,
                                            u_int a1,
                                            char* a2,
                                            int a3,
                                            int a4,
                                            char* a5,
                                            int a6)
{
    _PrintEnter("WSAAsyncGetHostByAddr(%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetHostByAddr(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
        _PrintExit("WSAAsyncGetHostByAddr(,,,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetHostByName(HWND a0,
                                            u_int a1,
                                            char* a2,
                                            char* a3,
                                            int a4)
{
    _PrintEnter("WSAAsyncGetHostByName(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetHostByName(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAAsyncGetHostByName(,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetProtoByName(HWND a0,
                                             u_int a1,
                                             char* a2,
                                             char* a3,
                                             int a4)
{
    _PrintEnter("WSAAsyncGetProtoByName(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetProtoByName(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAAsyncGetProtoByName(,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetProtoByNumber(HWND a0,
                                               u_int a1,
                                               int a2,
                                               char* a3,
                                               int a4)
{
    _PrintEnter("WSAAsyncGetProtoByNumber(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetProtoByNumber(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAAsyncGetProtoByNumber(,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetServByName(HWND a0,
                                            u_int a1,
                                            char* a2,
                                            char* a3,
                                            char* a4,
                                            int a5)
{
    _PrintEnter("WSAAsyncGetServByName(%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetServByName(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("WSAAsyncGetServByName(,,,,,) -> %lx\n", rv);
    };
    return rv;
}

HANDLE WINAPI Mine_WSAAsyncGetServByPort(HWND a0,
                                            u_int a1,
                                            int a2,
                                            char* a3,
                                            char* a4,
                                            int a5)
{
    _PrintEnter("WSAAsyncGetServByPort(%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    HANDLE rv = 0;
    __try {
        rv = Real_WSAAsyncGetServByPort(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("WSAAsyncGetServByPort(,,,,,) -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSACancelAsyncRequest(HANDLE a0)
{
    _PrintEnter("WSACancelAsyncRequest(%lx)\n", a0);

    int rv = 0;
    __try {
        rv = Real_WSACancelAsyncRequest(a0);
    } __finally {
        _PrintExit("WSACancelAsyncRequest() -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSACancelBlockingCall(void)
{
    _PrintEnter("WSACancelBlockingCall()\n");

    int rv = 0;
    __try {
        rv = Real_WSACancelBlockingCall();
    } __finally {
        _PrintExit("WSACancelBlockingCall() -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSACleanup(void)
{
    _PrintEnter("WSACleanup()\n");

    int rv = 0;
    __try {
        rv = Real_WSACleanup();
    } __finally {
        _PrintExit("WSACleanup() -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_WSACloseEvent(HANDLE a0)
{
    _PrintEnter("WSACloseEvent(%lx)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_WSACloseEvent(a0);
    } __finally {
        _PrintExit("WSACloseEvent() -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSAConnect(SOCKET a0,
                              sockaddr* a1,
                              int a2,
                              LPWSABUF a3,
                              LPWSABUF a4,
                              LPQOS a5,
                              LPQOS a6)
{
    int rv = 0;
    __try {
        rv = Real_WSAConnect(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
		_PrintEnter("%lx: WSAConnect(,%lx,%lx,%lx,%lx,%lx,%lx) -> %lx\n",
					a0, a1, a2, a3, a4, a5, a6, rv);
        _PrintExit(NULL);
    };
    return rv;
}

HANDLE WINAPI Mine_WSACreateEvent(void)
{
    _PrintEnter("WSACreateEvent()\n");

    HANDLE rv = 0;
    __try {
        rv = Real_WSACreateEvent();
    } __finally {
        _PrintExit("WSACreateEvent() -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSADuplicateSocketA(SOCKET a0,
                                       DWORD a1,
                                       struct _WSAPROTOCOL_INFOA* a2)
{
    _PrintEnter("%lx: WSADuplicateSocketA(,%lx,%lx)\n", a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_WSADuplicateSocketA(a0, a1, a2);
    } __finally {
        _PrintExit("%lx: WSADuplicateSocketA(,,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_WSADuplicateSocketW(SOCKET a0,
                                       DWORD a1,
                                       struct _WSAPROTOCOL_INFOW* a2)
{
    _PrintEnter("%lx: WSADuplicateSocketW(,%lx,%lx)\n", a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_WSADuplicateSocketW(a0, a1, a2);
    } __finally {
        _PrintExit("%lx: WSADuplicateSocketW(,,) -> %lx\n", a0, rv);
    };
    return rv;
}

INT WINAPI Mine_WSAEnumNameSpaceProvidersA(LPDWORD a0,
                                              LPWSANAMESPACE_INFOA a1)
{
    _PrintEnter("WSAEnumNameSpaceProvidersA(%lx,%lx)\n", a0, a1);

    INT rv = 0;
    __try {
        rv = Real_WSAEnumNameSpaceProvidersA(a0, a1);
    } __finally {
        _PrintExit("WSAEnumNameSpaceProvidersA(,) -> %lx\n", rv);
    };
    return rv;
}

INT WINAPI Mine_WSAEnumNameSpaceProvidersW(LPDWORD a0,
                                              LPWSANAMESPACE_INFOW a1)
{
    _PrintEnter("WSAEnumNameSpaceProvidersW(%lx,%lx)\n", a0, a1);

    INT rv = 0;
    __try {
        rv = Real_WSAEnumNameSpaceProvidersW(a0, a1);
    } __finally {
        _PrintExit("WSAEnumNameSpaceProvidersW(,) -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSAEnumNetworkEvents(SOCKET a0,
                                        HANDLE a1,
                                        LPWSANETWORKEVENTS a2)
{
    _PrintEnter("%lx: WSAEnumNetworkEvents(,%lx,%lx)\n", a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_WSAEnumNetworkEvents(a0, a1, a2);
    } __finally {
        _PrintExit("%lx: WSAEnumNetworkEvents(,,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_WSAEnumProtocolsA(LPINT a0,
                                     struct _WSAPROTOCOL_INFOA* a1,
                                     LPDWORD a2)
{
    _PrintEnter("WSAEnumProtocolsA(%lx,%lx,%lx)\n", a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_WSAEnumProtocolsA(a0, a1, a2);
    } __finally {
        _PrintExit("WSAEnumProtocolsA(,,) -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSAEnumProtocolsW(LPINT a0,
                                     struct _WSAPROTOCOL_INFOW* a1,
                                     LPDWORD a2)
{
    _PrintEnter("WSAEnumProtocolsW(%lx,%lx,%lx)\n", a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_WSAEnumProtocolsW(a0, a1, a2);
    } __finally {
        _PrintExit("WSAEnumProtocolsW(,,) -> %lx\n", rv);
    };
    return rv;
}

BOOL WINAPI Mine_WSAGetOverlappedResult(SOCKET a0,
                                           LPWSAOVERLAPPED a1,
                                           LPDWORD a2,
                                           BOOL a3,
                                           LPDWORD a4)
{
    _PrintEnter("%lx: WSAGetOverlappedResult(,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    BOOL rv = 0;
    __try {
        rv = Real_WSAGetOverlappedResult(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("%lx: WSAGetOverlappedResult(,,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

BOOL WINAPI Mine_WSAIsBlocking(void)
{
    _PrintEnter("WSAIsBlocking()\n");

    BOOL rv = 0;
    __try {
        rv = Real_WSAIsBlocking();
    } __finally {
        _PrintExit("WSAIsBlocking() -> %lx\n", rv);
    };
    return rv;
}

SOCKET WINAPI Mine_WSAJoinLeaf(SOCKET a0,
                                  sockaddr* a1,
                                  int a2,
                                  LPWSABUF a3,
                                  LPWSABUF a4,
                                  LPQOS a5,
                                  LPQOS a6,
                                  DWORD a7)
{
    _PrintEnter("%lx: WSAJoinLeaf(,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7);

    SOCKET rv = 0;
    __try {
        rv = Real_WSAJoinLeaf(a0, a1, a2, a3, a4, a5, a6, a7);
    } __finally {
        _PrintExit("%lx: WSAJoinLeaf(,,,,,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

INT WINAPI Mine_WSAProviderConfigChange(LPHANDLE a0,
                                           LPWSAOVERLAPPED a1,
                                           LPWSAOVERLAPPED_COMPLETION_ROUTINE a2)
{
    _PrintEnter("WSAProviderConfigChange(%lx,%lx,%lx)\n", a0, a1, a2);

    INT rv = 0;
    __try {
        rv = Real_WSAProviderConfigChange(a0, a1, a2);
    } __finally {
        _PrintExit("WSAProviderConfigChange(,,) -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSARecv(SOCKET a0,
                           LPWSABUF a1,
                           DWORD a2,
                           LPDWORD a3,
                           LPDWORD a4,
                           LPWSAOVERLAPPED a5,
                           LPWSAOVERLAPPED_COMPLETION_ROUTINE a6)
{
    int rv = -1;
    __try {
        rv = Real_WSARecv(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
		if (rv == 0) {
			_PrintEnter("%lx: WSARecv(,%lx,%lx,%lx,%lx,%lx,%lx)\n",
						a0, a1, a2, a3, a4, a5, a6);
			_PrintDump(a0, a1[0].buf, a1[0].len < *a3 ? a1[0].len : *a3);
			_PrintExit("%lx: WSARecv(,,,,,,) -> %lx\n", a0, rv);
		}
    };
    return rv;
}

int WINAPI Mine_WSARecvDisconnect(SOCKET a0,
                                     LPWSABUF a1)
{
    _PrintEnter("%lx: WSARecvDisconnect(,%lx)\n", a0, a1);

    int rv = 0;
    __try {
        rv = Real_WSARecvDisconnect(a0, a1);
    } __finally {
        _PrintExit("%lx: WSARecvDisconnect(,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_WSARecvFrom(SOCKET a0,
                               LPWSABUF a1,
                               DWORD a2,
                               LPDWORD a3,
                               LPDWORD a4,
                               sockaddr* a5,
                               LPINT a6,
                               LPWSAOVERLAPPED a7,
                               LPWSAOVERLAPPED_COMPLETION_ROUTINE a8)
{
    _PrintEnter("%lx: WSARecvFrom(,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7, a8);

    int rv = 0;
    __try {
        rv = Real_WSARecvFrom(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    } __finally {
        _PrintExit("%lx: WSARecvFrom(,,,,,,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

BOOL WINAPI Mine_WSAResetEvent(HANDLE a0)
{
    _PrintEnter("WSAResetEvent(%lx)\n", a0);

    BOOL rv = 0;
    __try {
        rv = Real_WSAResetEvent(a0);
    } __finally {
        _PrintExit("WSAResetEvent() -> %lx\n", rv);
    };
    return rv;
}

int WINAPI Mine_WSASend(SOCKET a0,
                           LPWSABUF a1,
                           DWORD a2,
                           LPDWORD a3,
                           DWORD a4,
                           LPWSAOVERLAPPED a5,
                           LPWSAOVERLAPPED_COMPLETION_ROUTINE a6)
{
    _PrintEnter("%lx: WSASend(,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6);

    int rv = 0;
    __try {
        rv = Real_WSASend(a0, a1, a2, a3, a4, a5, a6);
    } __finally {
        _PrintExit("%lx: WSASend(,,,,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_WSASendDisconnect(SOCKET a0,
                                     LPWSABUF a1)
{
    _PrintEnter("%lx: WSASendDisconnect(,%lx)\n", a0, a1);

    int rv = 0;
    __try {
        rv = Real_WSASendDisconnect(a0, a1);
    } __finally {
        _PrintExit("%lx: WSASendDisconnect(,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_WSASendTo(SOCKET a0,
                             LPWSABUF a1,
                             DWORD a2,
                             LPDWORD a3,
                             DWORD a4,
                             sockaddr* a5,
                             int a6,
                             LPWSAOVERLAPPED a7,
                             LPWSAOVERLAPPED_COMPLETION_ROUTINE a8)
{
    _PrintEnter("%lx: WSASendTo(,%lx,%lx,%lx,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5, a6, a7, a8);

    int rv = 0;
    __try {
        rv = Real_WSASendTo(a0, a1, a2, a3, a4, a5, a6, a7, a8);
    } __finally {
        _PrintExit("%lx: WSASendTo(,,,,,,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

INT WINAPI Mine_WSAStringToAddressA(LPSTR a0,
                                       INT a1,
                                       struct _WSAPROTOCOL_INFOA* a2,
                                       LPSOCKADDR a3,
                                       LPINT a4)
{
    _PrintEnter("WSAStringToAddressA(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    INT rv = 0;
    __try {
        rv = Real_WSAStringToAddressA(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAStringToAddressA(,,,,) -> %lx\n", rv);
    };
    return rv;
}

INT WINAPI Mine_WSAStringToAddressW(LPWSTR a0,
                                       INT a1,
                                       struct _WSAPROTOCOL_INFOW* a2,
                                       LPSOCKADDR a3,
                                       LPINT a4)
{
    _PrintEnter("WSAStringToAddressW(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    INT rv = 0;
    __try {
        rv = Real_WSAStringToAddressW(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAStringToAddressW(,,,,) -> %lx\n", rv);
    };
    return rv;
}

DWORD WINAPI Mine_WSAWaitForMultipleEvents(DWORD a0,
                                              void** a1,
                                              BOOL a2,
                                              DWORD a3,
                                              BOOL a4)
{
    _PrintEnter("WSAWaitForMultipleEvents(%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4);

    DWORD rv = 0;
    __try {
        rv = Real_WSAWaitForMultipleEvents(a0, a1, a2, a3, a4);
    } __finally {
        _PrintExit("WSAWaitForMultipleEvents(,,,,) -> %lx\n", rv);
    };
    return rv;
}

SOCKET WINAPI Mine_accept(SOCKET a0,
                             sockaddr* a1,
                             int* a2)
{
    SOCKET rv = 0;
    __try {
        rv = Real_accept(a0, a1, a2);
    } __finally {
		WCHAR wzAddress[512] = L"";
		if (rv != INVALID_SOCKET) {
			DWORD nAddress = ARRAYOF(wzAddress);
			if (Real_WSAAddressToStringW(a1, *a2, NULL, wzAddress, &nAddress) != 0) {
				wzAddress[0] = 0;
			}
		}

		if (wzAddress[0]) {
			_PrintEnter("%lx: accept(,%ls,%lx) -> %lx\n", a0, wzAddress, a2, rv);
		}
		else {
			_PrintEnter("%lx: accept(,%lx,%lx) -> %lx\n", a0, a1, a2, rv);
		}
		_PrintExit(NULL);
    };
    return rv;
}

int WINAPI Mine_closesocket(SOCKET a0)
{
    int rv = 0;
    __try {
        rv = Real_closesocket(a0);
    } __finally {
        _PrintEnter("%lx: closesocket() -> %lx\n", a0, rv);
        _PrintExit(NULL);
    };
    return rv;
}

int WINAPI Mine_connect(SOCKET a0,
                           sockaddr* name,
                           int namelen)
{
    int rv = 0;
    __try {
        rv = Real_connect(a0, name, namelen);
    } __finally {
		WCHAR wzAddress[512];
		DWORD nAddress = ARRAYOF(wzAddress);
		if (Real_WSAAddressToStringW(name, namelen, NULL, wzAddress, &nAddress) == 0) {
			_PrintEnter("%lx: connect(,%lx:%ls,%lx) -> %lx\n",
						a0, name, wzAddress, namelen, rv);
		}
		else {
			_PrintEnter("%lx: connect(,%lx,%lx) -> %lx\n",
						a0, name, namelen, rv);
		}
        _PrintExit(NULL);
    };
    return rv;
}

int WINAPI Mine_listen(SOCKET a0,
                          int a1)
{
    _PrintEnter("%lx: listen(,%lx)\n", a0, a1);

    int rv = 0;
    __try {
        rv = Real_listen(a0, a1);
    } __finally {
        _PrintExit("%lx: listen(,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_recv(SOCKET a0,
                        char* a1,
                        int a2,
                        int a3)
{
    _PrintEnter("%lx: recv(,%lx,%lx,%lx)\n", a0, a1, a2, a3);

    int rv = 0;
    __try {
        rv = Real_recv(a0, a1, a2, a3);
    } __finally {
        _PrintExit("%lx: recv(,%s,,) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

int WINAPI Mine_recvfrom(SOCKET a0,
                            char* a1,
                            int a2,
                            int a3,
                            sockaddr* a4,
                            int* a5)
{
    _PrintEnter("%lx: recvfrom(,%lx,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    int rv = 0;
    __try {
        rv = Real_recvfrom(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("%lx: recvfrom(,%s,,,,) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

VOID _PrintDump(SOCKET socket, PCHAR pszData, INT cbData)
{
	if (pszData && cbData > 0) {
		CHAR szBuffer[256];
		PCHAR pszBuffer = szBuffer;
		INT cbBuffer = 0;
		INT nLines = 0;
		
		while (cbData > 0) {
			if (nLines > 20) {
				*pszBuffer++ = '.';
				*pszBuffer++ = '.';
				*pszBuffer++ = '.';
				cbBuffer += 3;
				break;
			}

			if (*pszData == '\t') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 't';
				cbBuffer += 2;
				pszData++;
				cbData--;
				continue;
			}
			if (*pszData == '\r') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'r';
				cbBuffer += 2;
				pszData++;
				cbData--;
				continue;
			}
			else if (*pszData == '\n') {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'n';
				cbBuffer += 2;
				*pszBuffer++ = '\0';
				_Print("%lx:   %hs\n", socket, szBuffer);
				nLines++;
				pszBuffer = szBuffer;
				cbBuffer = 0;
				pszData++;
				cbData--;
				continue;
			}
			else if (cbBuffer >= 80) {
				*pszBuffer++ = '\0';
				_Print("%lx:   %hs\n", socket, szBuffer);
				nLines++;
				pszBuffer = szBuffer;
				cbBuffer = 0;
			}
			
			if (*pszData < ' ' || *pszData >= 127) {
				*pszBuffer++ = '\\';
				*pszBuffer++ = 'x';
				*pszBuffer++ = "0123456789ABCDEF"[(*pszData & 0xf0) >> 4];
				*pszBuffer++ = "0123456789ABCDEF"[(*pszData & 0x0f)];
				cbBuffer += 4;
			}
			else {
				*pszBuffer++ = *pszData;
			}
			cbBuffer++;
			pszData++;
			cbData--;
		}
		
		if (cbBuffer > 0) {
			*pszBuffer++ = '\0';
			_Print("%lx:   %hs\n", socket, szBuffer);
		}
	}
}

int WINAPI Mine_send(SOCKET a0,
                        char* a1,
                        int a2,
                        int a3)
{
    _PrintEnter("%lx: send(,%lx,%lx,%lx)\n", a0, a1, a2, a3);
	_PrintDump(a0, a1, a2);

    int rv = 0;
    __try {
        rv = Real_send(a0, a1, a2, a3);
    } __finally {
        _PrintExit("%lx: send(,,,) -> %lx\n", a0, rv);
    };
    return rv;
}

int WINAPI Mine_sendto(SOCKET a0,
                          char* a1,
                          int a2,
                          int a3,
                          sockaddr* a4,
                          int a5)
{
    _PrintEnter("%lx: sendto(,%s,%lx,%lx,%lx,%lx)\n", a0, a1, a2, a3, a4, a5);

    int rv = 0;
    __try {
        rv = Real_sendto(a0, a1, a2, a3, a4, a5);
    } __finally {
        _PrintExit("%lx: sendto(%ls,,,,,) -> %lx\n", a0, a1, rv);
    };
    return rv;
}

int WINAPI Mine_shutdown(SOCKET a0,
                            int a1)
{
    _PrintEnter("%lx: shutdown(,%lx)\n", a0, a1);

    int rv = 0;
    __try {
        rv = Real_shutdown(a0, a1);
    } __finally {
        _PrintExit("%lx: shutdown(,) -> %lx\n", a0, rv);
    };
    return rv;
}

/////////////////////////////////////////////////////////////
// TrampolineWith
//

VOID SetDetour(PBYTE pbTrampoline, PBYTE pbDetour)
{
	PBYTE pbRealTrampoline = NULL;
	PBYTE pbRealTarget = NULL;

	if (!DetourFunctionWithTrampolineEx(pbTrampoline, pbDetour,
										&pbRealTrampoline, &pbRealTarget)) {
		ASSERT(!"DetourFailed!");
	}
}

VOID TrampolineWith(VOID)
{
    DetourFunctionWithTrampoline((PBYTE)Real_CreateProcessW,
                                 (PBYTE)Mine_CreateProcessW);
    
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAccept,
                                 (PBYTE)Mine_WSAAccept);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAddressToStringA,
                                 (PBYTE)Mine_WSAAddressToStringA);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAddressToStringW,
                                 (PBYTE)Mine_WSAAddressToStringW);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetHostByAddr,
                                 (PBYTE)Mine_WSAAsyncGetHostByAddr);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetHostByName,
                                 (PBYTE)Mine_WSAAsyncGetHostByName);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetProtoByName,
                                 (PBYTE)Mine_WSAAsyncGetProtoByName);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetProtoByNumber,
                                 (PBYTE)Mine_WSAAsyncGetProtoByNumber);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetServByName,
                                 (PBYTE)Mine_WSAAsyncGetServByName);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAAsyncGetServByPort,
                                 (PBYTE)Mine_WSAAsyncGetServByPort);
    DetourFunctionWithTrampoline((PBYTE)Real_WSACancelAsyncRequest,
                                 (PBYTE)Mine_WSACancelAsyncRequest);
    DetourFunctionWithTrampoline((PBYTE)Real_WSACancelBlockingCall,
                                 (PBYTE)Mine_WSACancelBlockingCall);
    DetourFunctionWithTrampoline((PBYTE)Real_WSACleanup,
                                 (PBYTE)Mine_WSACleanup);
    DetourFunctionWithTrampoline((PBYTE)Real_WSACloseEvent,
                                 (PBYTE)Mine_WSACloseEvent);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAConnect,
                                 (PBYTE)Mine_WSAConnect);
    DetourFunctionWithTrampoline((PBYTE)Real_WSACreateEvent,
                                 (PBYTE)Mine_WSACreateEvent);
    DetourFunctionWithTrampoline((PBYTE)Real_WSADuplicateSocketA,
                                 (PBYTE)Mine_WSADuplicateSocketA);
    DetourFunctionWithTrampoline((PBYTE)Real_WSADuplicateSocketW,
                                 (PBYTE)Mine_WSADuplicateSocketW);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAEnumNameSpaceProvidersA,
                                 (PBYTE)Mine_WSAEnumNameSpaceProvidersA);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAEnumNameSpaceProvidersW,
                                 (PBYTE)Mine_WSAEnumNameSpaceProvidersW);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAEnumNetworkEvents,
                                 (PBYTE)Mine_WSAEnumNetworkEvents);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAEnumProtocolsA,
                                 (PBYTE)Mine_WSAEnumProtocolsA);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAEnumProtocolsW,
                                 (PBYTE)Mine_WSAEnumProtocolsW);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAIsBlocking,
                                 (PBYTE)Mine_WSAIsBlocking);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAJoinLeaf,
                                 (PBYTE)Mine_WSAJoinLeaf);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAProviderConfigChange,
                                 (PBYTE)Mine_WSAProviderConfigChange);
    DetourFunctionWithTrampoline((PBYTE)Real_WSARecv,
                                 (PBYTE)Mine_WSARecv);
    DetourFunctionWithTrampoline((PBYTE)Real_WSARecvDisconnect,
                                 (PBYTE)Mine_WSARecvDisconnect);
    DetourFunctionWithTrampoline((PBYTE)Real_WSARecvFrom,
                                 (PBYTE)Mine_WSARecvFrom);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAResetEvent,
                                 (PBYTE)Mine_WSAResetEvent);
    DetourFunctionWithTrampoline((PBYTE)Real_WSASend,
                                 (PBYTE)Mine_WSASend);
    DetourFunctionWithTrampoline((PBYTE)Real_WSASendDisconnect,
                                 (PBYTE)Mine_WSASendDisconnect);
    DetourFunctionWithTrampoline((PBYTE)Real_WSASendTo,
                                 (PBYTE)Mine_WSASendTo);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAStringToAddressA,
                                 (PBYTE)Mine_WSAStringToAddressA);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAStringToAddressW,
                                 (PBYTE)Mine_WSAStringToAddressW);
    DetourFunctionWithTrampoline((PBYTE)Real_WSAWaitForMultipleEvents,
                                 (PBYTE)Mine_WSAWaitForMultipleEvents);
    DetourFunctionWithTrampoline((PBYTE)Real_accept,
                                 (PBYTE)Mine_accept);
    DetourFunctionWithTrampoline((PBYTE)Real_closesocket,
                                 (PBYTE)Mine_closesocket);
    DetourFunctionWithTrampoline((PBYTE)Real_connect,
                                 (PBYTE)Mine_connect);
    DetourFunctionWithTrampoline((PBYTE)Real_listen,
                                 (PBYTE)Mine_listen);
    DetourFunctionWithTrampoline((PBYTE)Real_recv,
                                 (PBYTE)Mine_recv);
    DetourFunctionWithTrampoline((PBYTE)Real_recvfrom,
                                 (PBYTE)Mine_recvfrom);
    DetourFunctionWithTrampoline((PBYTE)Real_send,
                                 (PBYTE)Mine_send);
    DetourFunctionWithTrampoline((PBYTE)Real_sendto,
                                 (PBYTE)Mine_sendto);
    DetourFunctionWithTrampoline((PBYTE)Real_shutdown,
                                 (PBYTE)Mine_shutdown);
}
//
//////////////////////////////////////////////////////////////////////////////

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

	WCHAR wzExeName[MAX_PATH];
    s_hInst = hDll;
    
	Real_GetModuleFileNameW(hDll, s_wzDllPath, ARRAYOF(s_wzDllPath));
	Real_GetModuleFileNameW(NULL, wzExeName, ARRAYOF(wzExeName));

    SyelogOpen("tracetcp", SYELOG_FACILITY_APPLICATION);
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "##################################################################\n");
    Syelog(SYELOG_SEVERITY_INFORMATION,
           "### %ls\n", wzExeName);
	TrampolineWith();

	ThreadAttach(hDll);
	
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
