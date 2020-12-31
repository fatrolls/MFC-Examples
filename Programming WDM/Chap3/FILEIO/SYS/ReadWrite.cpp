// Read/Write request processors for fileio driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCreate
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	// Claim the remove lock in Win2K so that removal waits until the
	// handle closes. Don't do this in Win98, however, because this
	// device might be removed by surprise with handles open, whereupon
	// we'll deadlock in HandleRemoveDevice waiting for a close that
	// can never happen because we can't run the user-mode code that
	// would do the close.

	NTSTATUS status;
	if (win98)
		status = STATUS_SUCCESS;
	else 
		status = IoAcquireRemoveLock(&pdx->RemoveLock, stack->FileObject);

	if (NT_SUCCESS(status))
		InterlockedIncrement(&pdx->handles);
	return CompleteRequest(Irp, status, 0);
	}							// DispatchCreate

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchClose
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	InterlockedDecrement(&pdx->handles);
	
	// Release the remove lock to match the acquisition done in DispatchCreate

	if (!win98)
		IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	// A likely time to want to perform file I/O operations is during configuration of
	// the device, in order to read a firmware file for downloading to the device. This
	// stage is problematic in Win98 because the init order for CONFIGMG is before that
	// of IFSMgr. The portable file I/O library solves that particular problem.

	HANDLE hfile;
	status = OpenFile(L"\\SystemRoot\\System32\\Drivers\\fileio.jnk", TRUE, &hfile);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - OpenFile failed - %X\n", status));
		return status;
		}

	PVOID buffer = NULL;

	__try
		{
		ULONG size = (ULONG) GetFileSize(hfile);
		if (!size)
			__leave;			// file is empty

		buffer = ExAllocatePool(PagedPool, size);
		if (!buffer)
			{
			KdPrint((DRIVERNAME " - Unable to allocate %d bytes for data buffer\n", size));
			status = STATUS_INSUFFICIENT_RESOURCES;
			__leave;
			}
		
		ULONG numread;
		status = ReadFile(hfile, buffer, size, &numread);

		if (!NT_SUCCESS(status))
			{
			KdPrint((DRIVERNAME " - ReadFile failed - %X\n", status));
			__leave;
			}

		KdPrint((DRIVERNAME " - ReadFile succeeded and read %d bytes\n", numread));

		// Preserve the data buffer for the associated test program

		pdx->RandomJunk = buffer;
		pdx->RandomJunkSize = numread;
		buffer = NULL;
		}
	__finally
		{
		CloseFile(hfile);
		if (buffer)
			ExFreePool(buffer);
		}

	return status;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	if (pdx->RandomJunk)
		ExFreePool(pdx->RandomJunk);
	pdx->RandomJunk = NULL;
	}							// StopDevice
