// Control.cpp -- IOCTL handlers for feature driver
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

	case IOCTL_FEATURE_CLEAR:				// code == 0x800
		{						// IOCTL_FEATURE_CLEAR
		URB urb;
		UsbBuildFeatureRequest(&urb, URB_FUNCTION_CLEAR_FEATURE_TO_INTERFACE, FEATURE_LED_DISPLAY, 1, NULL);
		status = SendAwaitUrb(fdo, &urb);
		if (!NT_SUCCESS(status))
			KdPrint((DRIVERNAME " - Clear feature failed with status %X\n", status));
		break;
		}						// IOCTL_FEATURE_CLEAR

	case IOCTL_FEATURE_SET:				// code == 0x801
		{						// IOCTL_FEATURE_SET
		URB urb;
		UsbBuildFeatureRequest(&urb, URB_FUNCTION_SET_FEATURE_TO_INTERFACE, FEATURE_LED_DISPLAY, 1, NULL);
		status = SendAwaitUrb(fdo, &urb);
		if (!NT_SUCCESS(status))
			KdPrint((DRIVERNAME " - Set feature failed with status %X\n", status));
		break;
		}						// IOCTL_FEATURE_SET

	case IOCTL_GET_STATUS:				// code == 0x802
		{						// IOCTL_GET_STATUS
		if (cbin < 2 || cbout < sizeof(USHORT))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		PUCHAR data = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
		
		// Determine opcode based on first byte of data. If an interface or
		// endpoint is specified, its index is the second byte of data

		USHORT opcode;
		USHORT index;

		switch (data[0])
			{					// determine opcode
		case 0:
			opcode = URB_FUNCTION_GET_STATUS_FROM_DEVICE;
			index = 0;
			break;

		case 1:
			opcode = URB_FUNCTION_GET_STATUS_FROM_INTERFACE;
			index = data[1];
			break;

		case 2:
			opcode = URB_FUNCTION_GET_STATUS_FROM_ENDPOINT;
			index = data[1];
			break;

		default:
			opcode = URB_FUNCTION_GET_STATUS_FROM_OTHER;
			index = data[1];
			break;
			}					// determine opcode

		// Create and submit URB to obtain 2-byte status

		URB urb;
		UsbBuildGetStatusRequest(&urb, opcode, index, data, NULL, NULL);
		status = SendAwaitUrb(fdo, &urb);
		if (NT_SUCCESS(status))
			info = sizeof(USHORT);
		else
			KdPrint((DRIVERNAME " - Get status failed with status %X\n", status));

		break;
		}						// IOCTL_GET_STATUS

	case IOCTL_GET_CONFIGURATION:				// code == 0x803
		{						// IOCTL_GET_CONFIGURATION
		if (cbout < sizeof(UCHAR))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}
		
		URB urb = {0};
		urb.UrbControlGetConfigurationRequest.Hdr.Length = sizeof(_URB_CONTROL_GET_CONFIGURATION_REQUEST);
		urb.UrbControlGetConfigurationRequest.Hdr.Function = URB_FUNCTION_GET_CONFIGURATION;
		urb.UrbControlGetConfigurationRequest.TransferBufferLength = sizeof(UCHAR);
		urb.UrbControlGetConfigurationRequest.TransferBuffer = Irp->AssociatedIrp.SystemBuffer;

		status = SendAwaitUrb(fdo, &urb);
		if (NT_SUCCESS(status))
			info = sizeof(UCHAR);
		else
			KdPrint((DRIVERNAME " - Get configuration failed with status %X\n", status));

		break;
		}						// IOCTL_GET_CONFIGURATION

	case IOCTL_GET_INTERFACE:				// code == 0x804
		{						// IOCTL_GET_INTERFACE
		if (cbin < sizeof(UCHAR) || cbout < sizeof(UCHAR))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		URB urb = {0};
		urb.UrbControlGetInterfaceRequest.Hdr.Length = sizeof(_URB_CONTROL_GET_INTERFACE_REQUEST);
		urb.UrbControlGetInterfaceRequest.Hdr.Function = URB_FUNCTION_GET_INTERFACE;
		urb.UrbControlGetInterfaceRequest.TransferBufferLength = sizeof(UCHAR);
		urb.UrbControlGetInterfaceRequest.TransferBuffer = Irp->AssociatedIrp.SystemBuffer;
		urb.UrbControlGetInterfaceRequest.Interface = *(PUCHAR) Irp->AssociatedIrp.SystemBuffer;

		status = SendAwaitUrb(fdo, &urb);
		if (NT_SUCCESS(status))
			info = sizeof(UCHAR);
		else
			KdPrint((DRIVERNAME " - Get interface failed with status %X\n", status));

		break;
		}						// IOCTL_GET_INTERFACE

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl
