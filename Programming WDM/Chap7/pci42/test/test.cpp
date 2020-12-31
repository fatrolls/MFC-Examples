// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int main(int argc, char* argv[])
	{
	HANDLE hfile = CreateFile("\\\\.\\PCI42", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
		{
		puts("Can't open PCI42 device");
		return 1;
		}

	BYTE answer;
	DWORD numread;
	if (ReadFile(hfile, &answer, 1, &numread, NULL))
		printf("The answer is %d\n", answer);
	else
		printf("ReadFile failed - %d\n", GetLastError());

	CloseHandle(hfile);
	return 0;
	}
