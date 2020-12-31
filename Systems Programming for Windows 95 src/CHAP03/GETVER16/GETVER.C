#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
	{							// WinMain
	char msg[128];
	wsprintf(msg, "Windows version is %4.4X", GetVersion());
	MessageBox(GetFocus(), msg, "GetVersion Value", MB_OK | MB_ICONINFORMATION);
	return 0;
	}							// WinMain
	
