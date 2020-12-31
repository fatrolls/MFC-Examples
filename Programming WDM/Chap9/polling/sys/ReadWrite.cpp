// Read/Write request processors for polling driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS StartPollingThread(PDEVICE_EXTENSION pdx);
VOID StopPollingThread(PDEVICE_EXTENSION pdx);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCleanup
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CLEANUP\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	CleanupRequests(&pdx->dqReadWrite, stack->FileObject, STATUS_CANCELLED);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchCleanup

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCreate
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CREATE\n"));
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
	KdPrint((DRIVERNAME " - IRP_MJ_CLOSE\n"));
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

NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchReadWrite
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	IoMarkIrpPending(Irp);
	StartPacket(&pdx->dqReadWrite, fdo, Irp, OnCancelReadWrite);
	return STATUS_PENDING;
	}							// DispatchReadWrite

#pragma LOCKEDCODE

VOID OnCancelReadWrite(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// OnCancelReadWrite
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	CancelRequest(&pdx->dqReadWrite, Irp);
	}							// OnCancelReadWrite

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE				// because of raised IRQL later on

VOID PollingThreadRoutine(PDEVICE_EXTENSION pdx)
	{							// PollingThreadRoutine
	KdPrint(("POLLING - Starting polling thread\n"));
	NTSTATUS status;
	KTIMER timer;
	KeInitializeTimerEx(&timer, SynchronizationTimer);

	// Wait for a request to arrive at our StartIoRead routine or for
	// someone to kill this thread.

	PVOID mainevents[] = {
		(PVOID) &pdx->evKill,
		(PVOID) &pdx->evRequest,
		};

	PVOID pollevents[] = {
		(PVOID) &pdx->evKill,
		(PVOID) &timer,
		};

	ASSERT(arraysize(mainevents) <= THREAD_WAIT_OBJECTS);
	ASSERT(arraysize(pollevents) <= THREAD_WAIT_OBJECTS);

	BOOLEAN kill = FALSE;
	
	while (!kill)
		{						// until told to quit
		status = KeWaitForMultipleObjects(arraysize(mainevents),
			mainevents, WaitAny, Executive, KernelMode, FALSE, NULL, NULL);
		if (!NT_SUCCESS(status))
			{					// error in wait
			KdPrint(("POLLING - KeWaitForMultipleObjects failed - %X\n", status));
			break;
			}					// error in wait
		if (status == STATUS_WAIT_0)
			break;				// kill event was set

		ULONG numxfer = 0;

		// Starting the timer with a zero due time will cause us to perform the
		// first poll immediately. Thereafter, polls occur at the POLLING_INTERVAL
		// interval (measured in milliseconds).

		LARGE_INTEGER duetime = {0};

		#define POLLING_INTERVAL 500
		KeSetTimerEx(&timer, duetime, POLLING_INTERVAL, NULL);

		PIRP Irp = GetCurrentIrp(&pdx->dqReadWrite);

		while (TRUE)
			{					// read next byte

			// Check to see if we should continue processing this IRP

			if (!Irp)
				break;			// no current IRP (so why did evRequest get signalled??)
			
			if (Irp->Cancel)
				{				// someone wants to cancel this IRP
				status = STATUS_CANCELLED;
				break;
				}				// someone wants to cancel this IRP
			
			if ((status = AreRequestsBeingAborted(&pdx->dqReadWrite)))
				break;			// powering down or something

			// Block until time to poll again

			status = KeWaitForMultipleObjects(arraysize(pollevents),
				pollevents, WaitAny, Executive, KernelMode, FALSE, NULL, NULL);
			
			if (!NT_SUCCESS(status))
				{					// error in wait
				KdPrint(("POLLING - KeWaitForMultipleObjects failed - %X\n", status));
				kill = TRUE;
				break;				// from read next byte
				}					// error in wait
			
			if (status == STATUS_WAIT_0)
				{					// told to quit
				status = STATUS_DELETE_PENDING;
				kill = TRUE;
				break;				// from read next byte
				}					// told to quit

			// Poll the device. Read a data byte if one is ready.

			if (pdx->nbytes)
				{				// request not yet satisfied
				#define CTLPORT_DATA_READY 1
				if (READ_PORT_UCHAR(pdx->portbase) == CTLPORT_DATA_READY)
					{			// data byte is ready
					*pdx->buffer++ = READ_PORT_UCHAR(pdx->portbase + 1);
					--pdx->nbytes;
					++numxfer;
					}			// data byte is ready
				}				// request not yet satisfied

			if (!pdx->nbytes)
				break;			// request now satisfied, leave loop
			}					// read next byte

		KeCancelTimer(&timer);
		StartNextPacket(&pdx->dqReadWrite, pdx->DeviceObject);
		if (Irp)
			{					// IRP is complete
			IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
			CompleteRequest(Irp, status, numxfer);
			}					// IRP is complete
		}						// until told to quit

	KdPrint(("POLLING - Terminating polling thread\n"));
	PsTerminateSystemThread(STATUS_SUCCESS);
	}							// PollingThreadRoutine

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	// Identify the I/O resources we're supposed to use.

	PHYSICAL_ADDRESS portbase;
	BOOLEAN gotport = FALSE;
	
	if (!translated)
		return STATUS_DEVICE_CONFIGURATION_ERROR;		// no resources assigned??

	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = translated->PartialDescriptors;
	ULONG nres = translated->Count;
	for (ULONG i = 0; i < nres; ++i, ++resource)
		{						// for each resource
		switch (resource->Type)
			{					// switch on resource type

		case CmResourceTypePort:
			portbase = resource->u.Port.Start;
			pdx->nports = resource->u.Port.Length;
			pdx->mappedport = (resource->Flags & CM_RESOURCE_PORT_IO) == 0;
			gotport = TRUE;
			break;

		default:
			KdPrint((DRIVERNAME " - Unexpected I/O resource type %d\n", resource->Type));
			break;
			}					// switch on resource type
		}						// for each resource

	if (!(TRUE
		&& gotport
		))
		{
		KdPrint((DRIVERNAME " - Didn't get expected I/O resources\n"));
		return STATUS_DEVICE_CONFIGURATION_ERROR;
		}

	if (pdx->mappedport)
		{						// map port address for RISC platform
		pdx->portbase = (PUCHAR) MmMapIoSpace(portbase, pdx->nports, MmNonCached);
		if (!pdx->mappedport)
			{
			KdPrint((DRIVERNAME " - Unable to map port range %I64X, length %X\n", portbase, pdx->nports));
			return STATUS_INSUFFICIENT_RESOURCES;
			}
		}						// map port address for RISC platform
	else
		pdx->portbase = (PUCHAR) portbase.QuadPart;

	status = StartPollingThread(pdx);

	return status;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID StartIo(IN PDEVICE_OBJECT fdo, IN PIRP Irp)
	{							// StartIo
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		{
		CompleteRequest(Irp, status, 0);
		return;
		}

	pdx->buffer = (PUCHAR) Irp->AssociatedIrp.SystemBuffer;
	pdx->nbytes = stack->Parameters.Read.Length;

	KeSetEvent(&pdx->evRequest, 0, FALSE); // wake up polling thread
	}							// StartIo

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	StopPollingThread(pdx);

	if (pdx->portbase && pdx->mappedport)
		MmUnmapIoSpace(pdx->portbase, pdx->nports);
	pdx->portbase = NULL;
	}							// StopDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartPollingThread(PDEVICE_EXTENSION pdx)
	{							// StartPollingThread
	NTSTATUS status;
	HANDLE hthread;

	KeInitializeEvent(&pdx->evKill, NotificationEvent, FALSE);
	KeInitializeEvent(&pdx->evRequest, SynchronizationEvent, FALSE);

	status = PsCreateSystemThread(&hthread, THREAD_ALL_ACCESS, NULL, NULL, NULL,
		(PKSTART_ROUTINE) PollingThreadRoutine, pdx);
	if (!NT_SUCCESS(status))
		return status;

	status = ObReferenceObjectByHandle(hthread, THREAD_ALL_ACCESS, NULL,
		KernelMode, (PVOID*) &pdx->thread, NULL);

	ZwClose(hthread);

	return STATUS_SUCCESS;
	}							// StartPollingThread

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopPollingThread(PDEVICE_EXTENSION pdx)
	{							// StopPollingThread
	KeSetEvent(&pdx->evKill, 0, FALSE);
	if (pdx->thread)
		{						// wait for thread to die
		if (!win98)
			KeWaitForSingleObject(pdx->thread, Executive, KernelMode, FALSE, NULL);
		ObDereferenceObject(pdx->thread);
		pdx->thread = NULL;
		}						// wait for thread to die
	}							// StopPollingThread

