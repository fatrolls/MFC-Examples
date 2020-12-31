#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
	{							// main
	HANDLE hdevice;

	hdevice = CreateFile("\\\\.\\MYVXD.VXD", 0, 0, NULL, 0, FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		puts("Unable to load MYVXD.VXD");
	else
		CloseHandle(hdevice);
	return 0;
	}							// main
