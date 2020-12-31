// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include <conio.h>
#include "..\sys\ioctls.h"

DWORD WINAPI ThreadProc(LPVOID junk);
HANDLE hEvent;

int main(int argc, char* argv[])
	{
	HANDLE hdevice = CreateFile("\\\\.\\EVWAIT", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open EVWAIT device - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk;
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (!DeviceIoControl(hdevice, IOCTL_REGISTER_EVENT, &hEvent, sizeof(hEvent), NULL, 0, &junk, NULL))
		{
		printf("Error %d in IOCTL_REGISTER_EVENT call\n", GetLastError());
		CloseHandle(hEvent);
		CloseHandle(hdevice);
		return 1;
		}

	HANDLE hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, &junk);

	printf("Press any key to generate event, Ctrl+Break to terminate test:>");
	int ch = _getche();
	if (ch == 0 || ch == 0xE0)
		ch = _getche();

	if (!DeviceIoControl(hdevice, IOCTL_SIGNAL_EVENT, NULL, 0, NULL, 0, &junk, NULL))
		printf("Error %d in IOCTL_SIGNAL_EVENT call\n", GetLastError());

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hEvent);
	CloseHandle(hdevice);
	return 0;
	}

DWORD WINAPI ThreadProc(LPVOID junkola)
	{							// ThreadProc
	WaitForSingleObject(hEvent, INFINITE);
	puts("Event happened");
	return 0;
	}							// ThreadProc

