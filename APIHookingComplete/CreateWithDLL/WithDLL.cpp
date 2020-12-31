#pragma comment(lib, "detoured.lib")
#pragma comment(lib, "detours.lib")

#undef UNICODE
#include <cstdio>
#include <windows.h>
#include <detours\detours.h> //*IMPORTANT: Look at path if compiler error

int main()
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	char* DirPath = new char[MAX_PATH];
	char* DLLPath = new char[MAX_PATH]; //testdll.dll
	char* DetourPath = new char[MAX_PATH]; //detoured.dll
	GetCurrentDirectory(MAX_PATH, DirPath);
	sprintf_s(DLLPath, MAX_PATH, "%s\\testdll2.dll", DirPath);
	sprintf_s(DetourPath, MAX_PATH, "%s\\detoured.dll", DirPath);
	DetourCreateProcessWithDll(NULL, "C:\\windows\\notepad.exe", NULL,
		NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL,
		&si, &pi, DetourPath, DLLPath, NULL); //Just like CreateProcess
	delete [] DirPath;
	delete [] DLLPath;
	delete [] DetourPath;
	return 0;
}