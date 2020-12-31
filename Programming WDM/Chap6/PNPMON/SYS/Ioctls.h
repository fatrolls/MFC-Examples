// IOCTLS.H -- IOCTL code definitions for pnpmon driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_REGISTER		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_DEREGISTER	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GETEVENT		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct _REGISTER_PARAMS {
	GUID guid;
	PVOID hevent;
	} REGISTER_PARAMS, *PREGISTER_PARAMS;

typedef struct _UNREGISTER_PARAMS {
	GUID guid;
	} UNREGISTER_PARAMS, *PUNREGISTER_PARAMS;

typedef struct _GETEVENT_PARAMS {
	GUID guid;
	GUID event;
	ULONG datasize;
	LONG textoffset;
	WCHAR linkname[256];
	UCHAR data[256];
	} GETEVENT_PARAMS, *PGETEVENT_PARAMS;

#endif
