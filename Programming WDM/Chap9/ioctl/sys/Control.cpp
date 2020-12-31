// Control.cpp -- IOCTL handlers for ioctl driver
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

	case IOCTL_GET_VERSION_BUFFERED:				// code == 0x800
		{						// IOCTL_GET_VERSION_BUFFERED
		if (cbout < sizeof(ULONG))
			{					// not enough output data
			status = STATUS_INVALID_BUFFER_SIZE;
			break;
			}					// not enough output data

		PULONG pversion = (PULONG) Irp->AssociatedIrp.SystemBuffer;
		info = sizeof(ULONG);
		*pversion = 0x04000A;
		break;
		}						// IOCTL_GET_VERSION_BUFFERED

	case IOCTL_GET_VERSION_DIRECT:				// code == 0x801
		{						// IOCTL_GET_VERSION_DIRECT
		if (cbout < sizeof(ULONG))
			{					// not enough output data
			status = STATUS_INVALID_BUFFER_SIZE;
			break;
			}					// not enough output data

		PMDL pmdl = Irp->MdlAddress;

		// If the system is low on memory, MmGetSystemAddressForMdl will
		// bug-check unless the MDL_MAPPING_CAN_FAIL flag is set in MdlFlags.
		// Win2K has a new function named MmGetSystemAddressForMdlSafe that
		// returns NULL instead, but Win98 doesn't export it. But, since the
		// MDL is supposed to be a completely opaque structure, we should
		// not set the flag ourselves.

		PULONG pversion = (PULONG) MmGetSystemAddressForMdl(pmdl);
		info = sizeof(ULONG);
		*pversion = 0x0004000B;
		break;
		}						// IOCTL_GET_VERSION_DIRECT

	case IOCTL_GET_VERSION_NEITHER:				// code == 0x802
		{						// IOCTL_GET_VERSION_NEITHER
		if (cbout < sizeof(ULONG))
			{					// not enough output data
			status = STATUS_INVALID_BUFFER_SIZE;
			break;
			}					// not enough output data

		PULONG pversion = (PULONG) Irp->UserBuffer;
		
		if (Irp->RequestorMode != KernelMode)
			{					// untrusted caller
			__try
				{
				ProbeForWrite(pversion, sizeof(ULONG), 1);
				*pversion = 0x0004000C;
				}
			__except(EXCEPTION_EXECUTE_HANDLER)
				{
				status = GetExceptionCode();
				break;
				}
			}					// untrusted caller
		else
			*pversion = 0x0004000C;	// trusted caller

		info = sizeof(ULONG);
		break;
		}						// IOCTL_GET_VERSION_NEITHER

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl
