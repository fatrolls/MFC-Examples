#undef UNICODE
#include <vector>
#include <string>
#include <windows.h>
#include <Tlhelp32.h>
using std::vector;
using std::string;

int main(void)
{
	vector<string>processNames; //Hold every process available
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	HANDLE hTool32 = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL); //Create the snapshot
	BOOL bProcess = Process32First(hTool32, &pe32); //Call this and see if its valid
	if(bProcess == TRUE)
	{
		while((Process32Next(hTool32, &pe32)) == TRUE) //While processes left to be enumerated
		{
			processNames.push_back(pe32.szExeFile); //Save process name
			if(strcmp(pe32.szExeFile, "notepad.exe") == 0) //Process we want to inject to
			{
				char* DirPath = new char[MAX_PATH];
				char* FullPath = new char[MAX_PATH];
				GetCurrentDirectory(MAX_PATH, DirPath); //Holds directory for convenience
				sprintf_s(FullPath, MAX_PATH, "%s\\testdll.dll", DirPath); //Copy DLL name in there
				HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD	| PROCESS_VM_OPERATION	|
					PROCESS_VM_WRITE, FALSE, pe32.th32ProcessID);
				LPVOID LoadLibraryAddr = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),
					"LoadLibraryA"); //Get LoadLibraryA address
				LPVOID LLParam = (LPVOID)VirtualAllocEx(hProcess, NULL, strlen(FullPath),
					MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); //Allocate some memory for DLL string
				WriteProcessMemory(hProcess, LLParam, FullPath, strlen(FullPath), NULL); //Write it
				CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibraryAddr,
					LLParam, NULL, NULL); //New thread with LoadLibrary as start and our string as param
				CloseHandle(hProcess);
				delete [] DirPath;
				delete [] FullPath;
			}
		}
	}
	CloseHandle(hTool32);
	return 0;
}