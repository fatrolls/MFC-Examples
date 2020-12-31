// Control.cpp -- IOCTL handlers for wmiextra driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"
#include "guids.h"

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

	case IOCTL_FIRE_EVENT:				// code == 0x800
		{						// IOCTL_FIRE_EVENT
		if (!pdx->evenable)
			{					// event not enabled
			status = STATUS_INVALID_DEVICE_REQUEST;
			break;
			}					// event not enabled

		// Construct an event object in nonpaged memory. The system will free this
		// when it's no longer needed

		PULONG junk = (PULONG) ExAllocatePool(NonPagedPool, sizeof(ULONG));
		if (!junk)
			{
			status = STATUS_INSUFFICIENT_RESOURCES;
			break;
			}

		*junk = 42;
		status = WmiFireEvent(fdo, (LPGUID) &GUID_WMIEXTRA_EVENT, 0, sizeof(ULONG), junk);
		if (!NT_SUCCESS(status))
			KdPrint((DRIVERNAME " - WmiFireEvent failed - %X\n", status));
		break;
		}						// IOCTL_FIRE_EVENT


	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl
