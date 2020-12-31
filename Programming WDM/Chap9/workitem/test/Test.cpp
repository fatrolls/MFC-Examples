// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

int main(int argc, char* argv[])
	{
	HANDLE hdevice = CreateFile("\\\\.\\WORKITEM", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open WORKITEM device - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk;
	DWORD evin = 42, evout = 0;

	if (!DeviceIoControl(hdevice, IOCTL_SUBMIT_ITEM, &evin, sizeof(evin), &evout, sizeof(evout), &junk, NULL))
		printf("Error %d in IOCTL_SUBMIT_ITEM call\n", GetLastError());
	else
		printf("IOCTL_SUBMIT_ITEM(%d) succeeded and returned %d\n", evin, evout);

	CloseHandle(hdevice);
	return 0;
	}
