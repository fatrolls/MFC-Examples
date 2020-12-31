// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"

int main(int argc, char* argv[])
	{							// main
	BOOL cancel;
	if (argc >= 2 && _stricmp(argv[1], "-cancel") == 0)
		cancel = TRUE;
	else
		cancel = FALSE;

	HANDLE hdevice = CreateFile("\\\\.\\USBISO", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open USBISO device - error %d\n", GetLastError());
		return 1;
		}

	DWORD junk;
	BYTE data[4096];
	OVERLAPPED ol;
	memset(&ol, 0, sizeof(ol));
	ol.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	DWORD code;

	if (ReadFile(hdevice, data, 4096, &junk, &ol))
		code = 0;
	else
		code = GetLastError();

	if (code == ERROR_IO_PENDING)
		{						// wait for operation to finish
		if (cancel)
			CancelIo(hdevice);
		if (GetOverlappedResult(hdevice, &ol, &junk, TRUE))
			code = 0;
		else
			code = GetLastError();
		}						// wait for operation to finish

	if (code == 0)
		{
		printf("Read %d bytes successfully:\n", junk);
		DWORD offset = 0;
		while (offset < junk)
			{
			printf("%2.2X  %2.2X%2.2X%2.2X%2.2X %2.2X%2.2X%2.2X%2.2X %2.2X%2.2X%2.2X%2.2X %2.2X%2.2X%2.2X%2.2X\n",
				offset, data[offset], data[offset+1], data[offset+2], data[offset+3], data[offset+4], data[offset+5], data[offset+6], data[offset+7],
				data[offset+8], data[offset+9], data[offset+10], data[offset+11], data[offset+12], data[offset+13], data[offset+14], data[offset+15]);
			offset += 16;
			}
		}
	else
		printf("Error %d from ReadFile\n", GetLastError());
	
	CloseHandle(hdevice);
	return 0;
	}							// main

