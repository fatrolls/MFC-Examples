// IOCTLS.H -- IOCTL code definitions for s5933dk1 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_GET_VERSION		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_RESET				CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_READWRITE_MAILBOX	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MAILBOX_WAIT		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_READ_DMA			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_OUT_DIRECT, FILE_READ_ACCESS)
#define IOCTL_WRITE_DMA			CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_IN_DIRECT, FILE_WRITE_ACCESS)

typedef struct _READWRITE_MAILBOX_PARAMS {
	unsigned char buffer[4];	// buffer to r/w into/from
	unsigned char mailbox;		// mailbox index (1-4)
	unsigned char read;			// TRUE if read, FALSE if write
	unsigned char nbytes;		// # bytes to r/w (0-3)
	} READWRITE_MAILBOX_PARAMS, *PREADWRITE_MAILBOX_PARAMS;

typedef struct _MAILBOX_WAIT_PARAMS {
	unsigned long mask;			// mask of MBEF bits to test
	unsigned long mbef;			// value to compare with masked MBEF
	} MAILBOX_WAIT_PARAMS, *PMAILBOX_WAIT_PARAMS;

#endif
