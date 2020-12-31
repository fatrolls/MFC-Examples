// Control.cpp -- IOCTL handlers for pnpevent driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"
#include "guids.h"

struct _RANDOM_NOTIFICATION : public _TARGET_DEVICE_CUSTOM_NOTIFICATION
	{
	WCHAR text[14];
	};

typedef struct _RANDOM_NOTIFICATION RANDOM_NOTIFICATION, *PRANDOM_NOTIFICATION;

// From NTDDK.H (missing from beta-3 DDK?)

extern "C"
NTKERNELAPI
NTSTATUS
IoReportTargetDeviceChangeAsynchronous(
    IN PDEVICE_OBJECT PhysicalDeviceObject,
    IN PVOID NotificationStructure,  // always begins with a PLUGPLAY_NOTIFICATION_HEADER
    IN PDEVICE_CHANGE_COMPLETE_CALLBACK Callback,       OPTIONAL
    IN PVOID Context    OPTIONAL
    );

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchControl
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
		{						// process request

	case IOCTL_GENERATE_EVENT:				// code == 0x800
		{						// IOCTL_GENERATE_EVENT

		RANDOM_NOTIFICATION notify;
		notify.Version = 1;
		notify.Size = sizeof(notify);
		notify.Event = GUID_PNPEVENT_EVENT;
		notify.FileObject = NULL;
		notify.NameBufferOffset = FIELD_OFFSET(RANDOM_NOTIFICATION, text)
			- FIELD_OFFSET(RANDOM_NOTIFICATION, CustomDataBuffer);
		*(PULONG)(notify.CustomDataBuffer) = 42;
		wcscpy(notify.text, L"Hello, world!");

//		status = IoReportTargetDeviceChange(pdx->Pdo, &notify);
		status = IoReportTargetDeviceChangeAsynchronous(pdx->Pdo, &notify, NULL, NULL);
		if (NT_SUCCESS(status))
			status = STATUS_SUCCESS; // i.e., not STATUS_PENDING
		else
			KdPrint(("PNPEVENT - IoReportTargetDeviceChange failed - %X\n", status));
		break;
		}						// IOCTL_GENERATE_EVENT

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl
