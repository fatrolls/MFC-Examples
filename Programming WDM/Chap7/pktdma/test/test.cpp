// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\..\pci42\s5933dk1\ioctls.h"

#define BUFSIZE 8192

int main(int argc, char* argv[])
	{
	HANDLE hdevice = CreateFile("\\\\.\\PKTDMA", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		puts("Can't open PKTDMA device");
		return 1;
		}

	HANDLE hsim = CreateFile("\\\\.\\S5933DK1", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		puts("Can't open S5933DK1 device");
		CloseHandle(hdevice);
		return 1;
		}

	PDWORD inbuf = (PDWORD) malloc(BUFSIZE);
	PDWORD outbuf = (PDWORD) malloc(BUFSIZE);

	for (int i = 0; i < BUFSIZE / sizeof(DWORD); ++i)
		outbuf[i] = i;
	memset(inbuf, 0, BUFSIZE);

	// Start a read from the DK1 add-on simulator

	OVERLAPPED ol = {0};
	ol.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	DWORD numread;

	BOOL okay = DeviceIoControl(hsim, IOCTL_READ_DMA, NULL, 0, inbuf, BUFSIZE, &numread, &ol);
	if (!okay && GetLastError() == ERROR_IO_PENDING)
		{						// read started okay
		DWORD numwritten;
		okay = WriteFile(hdevice, outbuf, BUFSIZE, &numwritten, NULL);
		if (okay)
			printf("WriteFile succeeded in writing %d bytes\n", numwritten);
		else
			printf("WriteFile failed - %d\n", GetLastError());

		if (GetOverlappedResult(hsim, &ol, &numread, TRUE))
			{					// read succeeded
			printf("Overlapped IOCTL_READ_DMA succeeded in reading %d bytes\n", numread);
			for (i = 0; i < BUFSIZE / sizeof(DWORD); ++i)
				if (inbuf[i] != outbuf[i])
					{			// incorrect data
					printf("However, data element %d doesn't match\n", i);
					break;
					}			// incorrect data
			}					// read succeeded
		else
			printf("Overlapped IOCTL_READ_DMA failed - %d\n", GetLastError());
		}						// read started okay
	else
		printf("IOCTL_READ_DMA failed - %d\n", GetLastError());

	CloseHandle(ol.hEvent);
	free(inbuf);
	free(outbuf);
	CloseHandle(hsim);
	CloseHandle(hdevice);
	return 0;
	}
