// Control.cpp -- IOCTL handlers for evwait driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

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

	case IOCTL_REGISTER_EVENT:				// code == 0x800
		{						// IOCTL_REGISTER_EVENT
		if (cbin < sizeof(HANDLE))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}
		if (!RegisterEvent(pdx, stack->FileObject, *(PHANDLE) Irp->AssociatedIrp.SystemBuffer, Irp->RequestorMode))
			{
			KdPrint(("EVWAIT - Error trying to register event handle\n"));
			status = STATUS_UNSUCCESSFUL;
			}
		break;
		}						// IOCTL_REGISTER_EVENT

	case IOCTL_SIGNAL_EVENT:				// code == 0x801
		{						// IOCTL_SIGNAL_EVENT
		SignalEvent(pdx, stack->FileObject);
		break;
		}						// IOCTL_SIGNAL_EVENT

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl
