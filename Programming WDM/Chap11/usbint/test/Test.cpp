// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

int main(int argc, char* argv[])
	{

	HANDLE hdevice = CreateFile("\\\\.\\USBINT", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open USBINT device - error %d\n", GetLastError());
		return 1;
		}

	int numint = 0;
	printf("00 interrupts\r");
	
	while (TRUE)
		{						// count interrupts
		DWORD junk;
		if (DeviceIoControl(hdevice, IOCTL_WAITINT, NULL, 0, NULL, 0, &junk, NULL))
			printf("%2.2d interrupts\r", ++numint);
		else
			{
			printf("Error %d in call to DeviceIoControl\n", GetLastError());
			break;
			}
		}						// count interrupts

	CloseHandle(hdevice);
	return 0;
	}

