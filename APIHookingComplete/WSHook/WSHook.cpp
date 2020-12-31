#pragma comment(lib, "detoured.lib")
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "Ws2_32.lib")

#undef UNICODE
#include <cstdio>
#include <Winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <detours\detours.h> //*IMPORTANT: Look at path if compiler error

//Prototypes
int (WINAPI *pSend)(SOCKET s, const char* buf, int len, int flags) = send;
int WINAPI MySend(SOCKET s, const char* buf, int len, int flags);
int (WINAPI *pRecv)(SOCKET s, char* buf, int len, int flags) = recv;
int WINAPI MyRecv(SOCKET s, char* buf, int len, int flags);

//Log files
FILE* pSendLogFile;
FILE* pRecvLogFile;

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:	//Do standard detouring
		DisableThreadLibraryCalls(hDLL);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pSend, MySend);
		if(DetourTransactionCommit() == NO_ERROR)
			OutputDebugString("send() detoured successfully");
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pRecv, MyRecv);
		if(DetourTransactionCommit() == NO_ERROR)
			OutputDebugString("recv() detoured successfully");
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();	//Detach
        DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pSend, MySend);
		DetourTransactionCommit();
		DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pRecv, MyRecv);
		DetourTransactionCommit();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

//Open file, write contents, close it
int WINAPI MySend(SOCKET s, const char* buf, int len, int flags)
{
	fopen_s(&pSendLogFile, "C:\\SendLog.txt", "a+");
	fprintf(pSendLogFile, "%s\n", buf);
	fclose(pSendLogFile);
	return pSend(s, buf, len, flags);
}

int WINAPI MyRecv(SOCKET s, char* buf, int len, int flags)
{
	fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
	fprintf(pRecvLogFile, "%s\n", buf);
	fclose(pRecvLogFile);
	return pRecv(s, buf, len, flags);
}