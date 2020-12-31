// Test.cpp -- Test program for USB42.SYS
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

int main(int argc, char* argv[])
	{							// main
	HANDLE hdevice = CreateFile("\\\\.\\USB42", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open USB42 device - error %d\n", GetLastError());
		return 1;
		}

	BYTE answer[64];
	DWORD junk;
	if (DeviceIoControl(hdevice, IOCTL_USB42_READ, NULL, 0, answer, sizeof(answer), &junk, NULL))
		{
		printf("The answer is %d\n", LOBYTE(answer[0]));
		}
	else
		printf("Error %d in call to DeviceIoControl\n", GetLastError());
	
	CloseHandle(hdevice);
	return 0;
	}							// main

