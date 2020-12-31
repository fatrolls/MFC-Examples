// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int main(int argc, char* argv[])
	{
	HANDLE hdevice = CreateFile("\\\\.\\POLLING", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open POLLING device - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk;
	BYTE buffer[16];
	if (ReadFile(hdevice, buffer, 13, &junk, NULL))
		{
		buffer[junk] = 0;
		printf("ReadFile succeeded, transferred %d bytes: '%s'\n", junk, buffer);
		}
	else
		printf("ReadFile failed - error %d\n", GetLastError());

	CloseHandle(hdevice);
	return 0;
	}

