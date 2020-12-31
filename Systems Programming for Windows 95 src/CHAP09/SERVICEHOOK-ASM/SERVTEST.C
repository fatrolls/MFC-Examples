#include <windows.h>
#include <stdio.h>

HANDLE hDevice;
void WINAPI beginapp(DWORD);
void WINAPI endapp(DWORD);
char *getname(DWORD, char *);

int main(int argc, char *argv[])
	{							// main
	void (WINAPI *abegin)(DWORD) = beginapp;
	void (WINAPI *aend)(DWORD) = endapp;
	
	// Dynamically load the supporting VxD
	
	hDevice = CreateFile("\\\\.\\myvxd.vxd", 0, 0, NULL, 0,
		FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
		{						// can't load VxD
		puts("Can't load MYVXD.VXD");
		return 1;
		}						// can't load VxD
	
	DeviceIoControl(hDevice, 1, &abegin, sizeof(abegin), NULL, 0, NULL, NULL);
	DeviceIoControl(hDevice, 2, &aend, sizeof(aend), NULL, 0, NULL, NULL);
	
	// This loop terminates when you kill the app via Ctrl+Break. That
	// causes handles to be closed, which unloads the VxD.

	while (SleepEx(INFINITE, TRUE) == WAIT_IO_COMPLETION)
		;						// i.e., forever or until error
	return 0;
	}							// main

void WINAPI beginapp(DWORD psp)
	{							// beginapp
	char name[9];
	printf("Starting V86 App %s\n", getname(psp, name));
	}							// beginapp

void WINAPI endapp(DWORD psp)
	{							// endapp
	char name[9];
	printf("Ending   V86 App %s\n", getname(psp, name));
	}							// endapp

char *getname(DWORD psp, char *name)
	{							// getname
	char *p	 = (char *) (psp - 8);
	memcpy(name, p, 8);
	name[8] = 0;
	return name;
	}							// getname
