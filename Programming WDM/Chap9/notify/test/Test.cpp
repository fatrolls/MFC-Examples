// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

DWORD WINAPI ThreadProc(LPVOID junk);

int main(int argc, char* argv[])
	{
	DWORD junk;
	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &junk);

	printf("Press any key to generate 'interesting' event, Ctrl+Break to terminate test:>");
	int ch = _getche();
	if (ch == 0 || ch == 0xE0)
		ch = _getche();

	HANDLE hdevice = CreateFile("\\\\.\\NOTIFY", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{													 
		printf("Unable to open NOTIFY device in main program - error %d\n", GetLastError());
		return 1;
		}

	if (!DeviceIoControl(hdevice, IOCTL_GENERATE_EVENT, &ch, sizeof(ch), NULL, 0, &junk, NULL))
		printf("Error %d in IOCTL_GENERATE_EVENT call\n", GetLastError());

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hdevice);
	return 0;
	}

DWORD WINAPI ThreadProc(LPVOID junkola)
	{							// ThreadProc
	HANDLE hdevice = CreateFile("\\\\.\\NOTIFY", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open NOTIFY device in notification thread - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk, event;
	if (DeviceIoControl(hdevice, IOCTL_WAIT_NOTIFY, NULL, 0, &event, sizeof(event), &junk, NULL))
		printf("Event happened: %X\n", event);
	else
		printf("Error %d in IOCTL_WAIT_NOTIFY call\n", GetLastError());

	return 0;
	}							// ThreadProc
