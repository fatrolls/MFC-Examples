// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

void ShowStatus(LPCTSTR thing, WORD status);

int main(int argc, char* argv[])
	{
	HANDLE hdevice = CreateFile("\\\\.\\FEATURE", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open FEATURE device - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk;

	if (DeviceIoControl(hdevice, IOCTL_FEATURE_SET,	NULL, 0, NULL, 0, &junk, NULL))
		puts("Set feature request succeeded");
	else
		printf("Error %d trying to set feature\n", GetLastError());

	BYTE data[2];
	data[0] = 0;				// for get device status
	if (DeviceIoControl(hdevice, IOCTL_GET_STATUS,	data, 2, data, 2, &junk, NULL))
		ShowStatus("Device", *(PWORD) data);
	else
		printf("Error %d trying to get device status\n", GetLastError());

	data[0] = 1;				// for get interface status
	data[1] = 0;
	if (DeviceIoControl(hdevice, IOCTL_GET_STATUS,	data, 2, data, 2, &junk, NULL))
		ShowStatus("Interface 0", *(PWORD) data);
	else
		printf("Error %d trying to get interface status\n", GetLastError());

	data[0] = 2;				// for get endpoint status
	data[1] = 0;
	if (DeviceIoControl(hdevice, IOCTL_GET_STATUS,	data, 2, data, 2, &junk, NULL))
		ShowStatus("Endpoint 0", *(PWORD) data);
	else
		printf("Error %d trying to get endpoint status\n", GetLastError());

	if (DeviceIoControl(hdevice, IOCTL_GET_CONFIGURATION, data, 1, data, 1, &junk, NULL))
		printf("Device is using configuration number %d\n", data[0]);
	else
		printf("Error %d trying to get configuration\n", GetLastError());

	data[0] = 0;
	if (DeviceIoControl(hdevice, IOCTL_GET_INTERFACE, data, 1, data, 1, &junk, NULL))
		printf("Interface 0 is using alternate setting %d\n", data[0]);
	else
		printf("Error %d trying to get configuration\n", GetLastError());
	
	Sleep(5000);

	if (DeviceIoControl(hdevice, IOCTL_FEATURE_CLEAR,	NULL, 0, NULL, 0, &junk, NULL))
		puts("Clear feature request succeeded");
	else
		printf("Error %d trying to clear feature\n", GetLastError());

	CloseHandle(hdevice);
	return 0;
	}

void ShowStatus(LPCTSTR thing, WORD status)
	{							// ShowStatus
	printf("%s status is %2.2X\n", thing, status);
	}							// ShowStatus
