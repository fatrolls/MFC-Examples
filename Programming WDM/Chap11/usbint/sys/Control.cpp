// Control.cpp -- IOCTL handlers for usbint driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchControl
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

	case IOCTL_WAITINT :				// code == 0x800
		{						// IOCTL_WAITINT

		// Use up a pending interrupt first. We increment numints each time we
		// get an interrupt, and we decrement it each time we complete an IOCTL.

		if (InterlockedDecrement(&pdx->numints) >= 0)
			{					// pending interrupt
			status = STATUS_SUCCESS;
			break;
			}					// pending interrupt
			
		// Pend this IOCTL until an interrupt occurs

		InterlockedIncrement(&pdx->numints); // restore counter
		status = GenericCacheControlRequest(pdx->pgx, Irp, &pdx->InterruptIrp);
		break;
		}						// IOCTL_WAITINT 

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return status == STATUS_PENDING ? status : CompleteRequest(Irp, status, info);
	}							// DispatchControl
