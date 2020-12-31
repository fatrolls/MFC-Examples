// Control.cpp -- IOCTL handlers for wdmidle driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

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

	// Delegate the IRP to GENERIC.SYS

	status = GenericHandlePowerIoctl(pdx->pgx, Irp);

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
	}							// DispatchControl
