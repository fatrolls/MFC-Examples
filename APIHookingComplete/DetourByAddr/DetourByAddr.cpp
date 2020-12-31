#pragma comment(lib, "detoured.lib")
#pragma comment(lib, "detours.lib")

#undef UNICODE
#include <cstdio>
#include <windows.h>
#include <detours\detours.h> //*IMPORTANT: Look at path if compiler error

typedef void (WINAPI *pFunc)(DWORD);
void WINAPI MyFunc(DWORD);

pFunc FuncToDetour = (pFunc)(0x0100347C); //Set it at address to detour in
										//the process
INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		{
		DisableThreadLibraryCalls(hDLL);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)FuncToDetour, MyFunc);
		DetourTransactionCommit();
		}
		break;
	case DLL_PROCESS_DETACH:
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)FuncToDetour, MyFunc);
		DetourTransactionCommit();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

void WINAPI MyFunc(DWORD someParameter)
{
	//Some things can happen here
}