#undef UNICODE
#include <windows.h>
#include <cstdio>

#define SIZE 6 //Number of bytes needed to redirect

typedef int (WINAPI *pMessageBoxW)(HWND, LPCWSTR, LPCWSTR, UINT);
int WINAPI MyMessageBoxW(HWND, LPCWSTR, LPCWSTR, UINT);

void BeginRedirect(LPVOID);

pMessageBoxW pOrigMBAddress = NULL;
BYTE oldBytes[SIZE] = {0}; //This will hold the overwritten bytes
BYTE JMP[SIZE] = {0};	//This holds the JMP to our code
DWORD oldProtect, myProtect = PAGE_EXECUTE_READWRITE; //Protection settings on memory
char debugBuffer[128]; //Used for DbgView

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved)
{
	switch(Reason)
	{
	case DLL_PROCESS_ATTACH:
		pOrigMBAddress = (pMessageBoxW) //Get MessageBoxW pointer
			GetProcAddress(GetModuleHandle("user32.dll"), "MessageBoxW");
		if(pOrigMBAddress != NULL)
			BeginRedirect(MyMessageBoxW);	//Valid? Redirect
		break;
	case DLL_PROCESS_DETACH:
		memcpy(pOrigMBAddress, oldBytes, SIZE);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

void BeginRedirect(LPVOID newFunction)
{
	sprintf_s(debugBuffer, 128, "pOrigMBAddress: %x", pOrigMBAddress);
	OutputDebugString(debugBuffer);
	BYTE tempJMP[SIZE] = {0xE9, 0x90, 0x90, 0x90, 0x90, 0xC3}; //JMP <NOP> RET for now
	memcpy(JMP, tempJMP, SIZE); //Copy into global for convenience later
	DWORD JMPSize = ((DWORD)newFunction - (DWORD)pOrigMBAddress - 5); //Get address difference
	VirtualProtect((LPVOID)pOrigMBAddress, SIZE, PAGE_EXECUTE_READWRITE, &oldProtect);
			//Change memory settings to make sure we can write the JMP in
	memcpy(oldBytes, pOrigMBAddress, SIZE); //Copy old bytes before writing JMP
	sprintf_s(debugBuffer, 128, "Old bytes: %x%x%x%x%x", oldBytes[0], oldBytes[1],
		oldBytes[2], oldBytes[3], oldBytes[4], oldBytes[5]);
	OutputDebugString(debugBuffer);
	memcpy(&JMP[1], &JMPSize, 4); //Write the address to JMP to
	sprintf_s(debugBuffer, 128, "JMP: %x%x%x%x%x", JMP[0], JMP[1],
		JMP[2], JMP[3], JMP[4], JMP[5]);
	OutputDebugString(debugBuffer);
	memcpy(pOrigMBAddress, JMP, SIZE); //Write it in process memory
	VirtualProtect((LPVOID)pOrigMBAddress, SIZE, oldProtect, NULL); //Change setts back
}

int  WINAPI MyMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uiType)
{
	VirtualProtect((LPVOID)pOrigMBAddress, SIZE, myProtect, NULL); //ReadWrite again
	memcpy(pOrigMBAddress, oldBytes, SIZE); //Unhook API
	MessageBoxW(NULL, L"This should pop up", L"Hooked MBW", MB_ICONEXCLAMATION);
	int retValue = MessageBoxW(hWnd, lpText, lpCaption, uiType); //Get ret value
	memcpy(pOrigMBAddress, JMP, SIZE); //Rehook API
	VirtualProtect((LPVOID)pOrigMBAddress, SIZE, oldProtect, NULL); //Normal setts
	return retValue; //Return what should be returned
}