#ifndef __cplusplus
extern "C" {
#endif

#pragma comment(lib, "detoured.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "Ws2_32.lib")

#undef UNICODE
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <detours\detours.h> //*IMPORTANT: Look at path if compiler error
#include "DlgRecvSend.h"

#define MINPACKETLEN 5
#define VERBOSEOUTPUT 0

DWORD threadID;	//Thread ID of function for creating the dialog (not used)
HMODULE g_hDLL;	//HMODULE of this DLL

int (WINAPI *precv)(SOCKET socket, char* buffer, int length, int flags) = NULL;
int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags);
//
int (WINAPI *psend)(SOCKET socket, const char* buffer, int length, int flags) = NULL;
int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags);
//
int (WINAPI *pWSASend)(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) = NULL;
int WINAPI MyWSASend(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
//
int (WINAPI *pWSARecv)(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,LPWSAOVERLAPPED lpOverlapped, 
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine) = NULL;
int WINAPI MyWSARecv(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,LPWSAOVERLAPPED lpOverlapped, 
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);
//

//This function is exported on ordinal 1 just in case this DLL
//will be loaded with DetourCreateProcessWithDll
__declspec(dllexport) void DetourAndErrorCheck(PVOID* pFunctionToDetour, PVOID pReplacement,
						 const char* functionName);
void CheckAndDetach(PVOID* pDetouredFunction, PVOID pReplacement,
						const char* functionName);
void LogAndVerboseOutput(const char* functionName, const char* buffer);

DWORD WINAPI DlgInit(LPVOID);

BOOL APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
		CreateThread(NULL, NULL, &DlgInit, NULL, NULL, &threadID); //Initialize Dialog
		::g_hDLL = hDLL;
		LONG errorCode = 0;
		DisableThreadLibraryCalls(hDLL);
		DetourRestoreAfterWith();	//Start finding function pointers
		psend = (int (WINAPI *)(SOCKET, const char*, int, int))
			DetourFindFunction("Ws2_32.dll", "send");
		precv = (int (WINAPI *)(SOCKET, char*, int, int))
			DetourFindFunction("Ws2_32.dll", "recv");
		pWSASend = (int (WINAPI *)(SOCKET, LPWSABUF, DWORD,
			LPDWORD, DWORD, LPWSAOVERLAPPED, LPWSAOVERLAPPED_COMPLETION_ROUTINE))
			DetourFindFunction("Ws2_32.dll", "WSASend");
		pWSARecv = (int (WINAPI *)(SOCKET, LPWSABUF, DWORD,
			LPDWORD, LPDWORD, LPWSAOVERLAPPED,  LPWSAOVERLAPPED_COMPLETION_ROUTINE))
			DetourFindFunction("Ws2_32.dll", "WSARecv");
		DetourAndErrorCheck(&(PVOID&)psend, MySend, "send"); //Begin detouring
		DetourAndErrorCheck(&(PVOID&)precv, MyRecv, "recv");
		DetourAndErrorCheck(&(PVOID&)pWSASend, MyWSASend, "WSASend");
		DetourAndErrorCheck(&(PVOID&)pWSARecv, MyWSARecv, "WSARecv");
		}
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		CheckAndDetach(&(PVOID&)psend, MySend, "send");
		CheckAndDetach(&(PVOID&)precv, MyRecv, "recv");
		CheckAndDetach(&(PVOID&)pWSASend, MyWSASend, "WSASend");
		CheckAndDetach(&(PVOID&)pWSARecv, MyWSARecv, "WSARecv");
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

DWORD WINAPI DlgInit(LPVOID)
{
	DialogBoxParam(::g_hDLL, MAKEINTRESOURCE(DLG_MAIN), NULL, DlgProc,
			NULL);
	return 0;
}
int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags)
{
	if(length > MINPACKETLEN)
	{
		LogAndVerboseOutput("MySend", buffer);
	}
	return psend(socket, buffer, length, flags);
}

int WINAPI MyWSASend(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesSent, DWORD dwFlags, LPWSAOVERLAPPED lpOverlapped,
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	if(lpBuffers->len > MINPACKETLEN)
		LogAndVerboseOutput("MyWSASend", lpBuffers->buf);

	return pWSASend(socket, lpBuffers, dwBufferCount, lpNumberOfBytesSent,
		dwFlags, lpOverlapped, lpCompletionRoutine);
}
int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags)
{
	if(length > MINPACKETLEN)
		LogAndVerboseOutput("MyRecv", buffer);
	return precv(socket, buffer, length, flags);
}

int WINAPI MyWSARecv(SOCKET socket, LPWSABUF lpBuffers, DWORD dwBufferCount,
	LPDWORD lpNumberOfBytesRecvd, LPDWORD lpFlags,LPWSAOVERLAPPED lpOverlapped, 
	LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	if(lpBuffers->len > MINPACKETLEN)
	{
		if(strstr(lpBuffers->buf, "MSG ") != 0 && (strstr(lpBuffers->buf, "MIME-Version") != 0
		&& strstr(lpBuffers->buf, "X-MMS-IM-Format") != 0))
		{
			ParseAndStoreEmail(socket, lpBuffers->buf);
		}
		LogAndVerboseOutput("MyWSARecv", lpBuffers->buf);
	}
	return pWSARecv(socket, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd,
		lpFlags, lpOverlapped, lpCompletionRoutine);
}
__declspec(dllexport) void DetourAndErrorCheck(PVOID* pFunctionToDetour, PVOID pReplacement,
						 const char* functionName)
{
	char* debugString = new char[256];
	ZeroMemory(debugString, 256);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(pFunctionToDetour, pReplacement);
	int errorCode = DetourTransactionCommit();
	if(errorCode == NO_ERROR)
	{
		sprintf_s(debugString, 255, "Address of %s: 0x%x\n"
			"Address of replacement function: 0x%x\n"
			"%s() was detoured successfully", functionName, pFunctionToDetour,
			pReplacement, functionName);
	OutputDebugString(debugString);
	}
	else
	{
		if(errorCode == ERROR_INVALID_DATA)
			OutputDebugString("ERROR_INVALID_DATA returned");
		else if(errorCode == ERROR_INVALID_OPERATION)
			OutputDebugString("ERROR_INVALID_OPERATION returned");
		else
			OutputDebugString("Other error code returned");
	sprintf_s(debugString, 255, "%s() was not able to be detoured\n"
			"Address of %s: 0x%x\n"
			"Address of replacement function: 0x%x", functionName,
			functionName, pFunctionToDetour, pReplacement);
	OutputDebugString(debugString);
	}
	delete [] debugString;
}

void CheckAndDetach(PVOID* pDetouredFunction, PVOID pReplacement,
						const char* functionName)
{
	if(pDetouredFunction != NULL)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pDetouredFunction, pReplacement);
		DetourTransactionCommit();
	}
	else
	{
		int errorSize = 64 + strlen(functionName);
		char* errorString = new char[errorSize];
		ZeroMemory(errorString, 32);
		sprintf_s(errorString, errorSize, "%s could not be detached\n"
							"Was it detoured in the first place?");
		OutputDebugString(errorString);
		delete [] errorString;
	}
}

void LogAndVerboseOutput(const char* functionName, const char* buffer)
{
	if(VERBOSEOUTPUT == 1)
	{
	int debugSize = (64 + strlen(functionName) + strlen(buffer));
	char *debugString = new char[debugSize];
	ZeroMemory(debugString, debugSize);
	sprintf_s(debugString, debugSize, "----------In %s()----------\n"
									"%s\n"
									"----------$$END$$----------",
									functionName, buffer);
	OutputDebugString(debugString);
	delete [] debugString;
	}
}
#ifndef __cplusplus
}
#endif