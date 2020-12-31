// IOCTLS.H -- IOCTL code definitions for wdmidle driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef IOCTLS_H
#define IOCTLS_H

#ifndef CTL_CODE
	#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_GET_POWERINFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_POWERINFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IDLENOW		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)

typedef struct _POWERINFO {
	unsigned long ulConservation;	// idle timeout in conservation mode
	unsigned long ulPerformance;	// idle timeout in performance mode
	unsigned char bWakeup;			// TRUE if wakeup feature should be armed
	unsigned char bCanWake;			// device capable of waking system
	unsigned char bCanIdle;			// device can be idled
	unsigned char bIdle;			// device is idle right now
	} POWERINFO, *PPOWERINFO;

#endif
