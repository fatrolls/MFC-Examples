// addonsim.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\s5933dk1\ioctls.h"
#include "..\sys\s5933.h"

int main(int argc, char* argv[])
	{
	HANDLE hfile = CreateFile("\\\\.\\S5933DK1", GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, 0, NULL);
	if (hfile == INVALID_HANDLE_VALUE)
		{
		puts("Can't open S5933DK1 device");
		return 1;
		}

	// Wait for outgoing mailbox 1, byte 0 to become free (note that add-on
	// definition of in vs. out is the opposite of the S5933's)

	DWORD junk;

	MAILBOX_WAIT_PARAMS wait;
	wait.mask = MBEF_IN1_0;
	wait.mbef = 0;

	if (DeviceIoControl(hfile, IOCTL_MAILBOX_WAIT, &wait, sizeof(wait), NULL, 0, &junk, NULL))
		{						// wait satisifed
		READWRITE_MAILBOX_PARAMS write;
		write.buffer[0] = 42;	// what else?
		write.mailbox = 1;
		write.read = FALSE;
		write.nbytes = 1;

		if (DeviceIoControl(hfile, IOCTL_READWRITE_MAILBOX, &write, sizeof(write), &write, sizeof(write),
			&junk, NULL))
			puts("Data byte written okay");
		else
			printf("Error %d writing to mailbox\n", GetLastError());
		}						// wait satisified
	else
		printf("Error %d waiting for outgoing mailbox to empty\n", GetLastError());

	CloseHandle(hfile);
	return 0;
	}
