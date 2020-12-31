// TEST.CPP -- test program for LOOPBACK.SYS
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int main(int argc, char* argv[])
	{							// main
	HANDLE hdevice = CreateFile("\\\\.\\LOOPBACK", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open LOOPBACK device - error %d\n", GetLastError());
		return 1;
		}

	#define TESTSIZE 100

	DWORD data[TESTSIZE];
	for (int i = 0; i < TESTSIZE; ++i)
		data[i] = i;

	DWORD junk;
	if (WriteFile(hdevice, data, sizeof(data), &junk, NULL))
		printf("Write transferred %d bytes okay\n", junk);
	else
		printf("Error %d trying to write data\n", GetLastError());

	memset(data, 0, sizeof(data));

	if (ReadFile(hdevice, data, sizeof(data), &junk, NULL))
		{
		for (i = 0; i < TESTSIZE; ++i)
			if (data[i] != (DWORD) i)
				break;
		if (i >= TESTSIZE)
			printf("Read transferred %d bytes correctly\n", junk);
		else
			printf("Read claimed to transfer %d bytes okay, but %d'th DWORD is incorrect\n", junk, i);
		}
	else
		printf("Error %d trying to read data\n", GetLastError());
	
	CloseHandle(hdevice);
	return 0;
	}							// main

