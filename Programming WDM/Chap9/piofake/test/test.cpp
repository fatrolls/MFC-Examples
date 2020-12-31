// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int main(int argc, char* argv[])
	{							// main
	HANDLE hdevice = CreateFile("\\\\.\\PIOFAKE", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Can't open PIOFAKE device - %d\n", GetLastError());
		return 1;
		}

	DWORD junk;
	char* message = "Hello, world!";
	
	if (WriteFile(hdevice, message, strlen(message), &junk, NULL))
		printf("WriteFile succeeded, sent %d bytes\n", junk);
	else
		printf("WriteFile failed - %d\n", GetLastError());

	CloseHandle(hdevice);
	return 0;
	}							// main
