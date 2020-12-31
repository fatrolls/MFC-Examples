// Read/Write request processors for usbint driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

#ifdef DBG
	#define MSGUSBSTRING(d,s,i) { \
		UNICODE_STRING sd; \
		if (i && NT_SUCCESS(GetStringDescriptor(d,i,&sd))) { \
			DbgPrint(s, sd.Buffer); \
			RtlFreeUnicodeString(&sd); \
		}}
#else
	#define MSGUSBSTRING(d,i,s)
#endif

NTSTATUS StartInterruptUrb(PDEVICE_EXTENSION pdx);
NTSTATUS OnInterrupt(PDEVICE_OBJECT junk, PIRP Irp, PDEVICE_EXTENSION pdx);
VOID StopInterruptUrb(PDEVICE_EXTENSION pdx);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID AbortPipe(PDEVICE_OBJECT fdo, USBD_PIPE_HANDLE hpipe)
	{							// AbortPipe
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	URB urb;

	urb.UrbHeader.Length = (USHORT) sizeof(_URB_PIPE_REQUEST);
	urb.UrbHeader.Function = URB_FUNCTION_ABORT_PIPE;
	urb.UrbPipeRequest.PipeHandle = hpipe;

	NTSTATUS status = SendAwaitUrb(fdo, &urb);
	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - Error %X in AbortPipe\n", status));
	}							// AbortPipe

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS CreateInterruptUrb(PDEVICE_OBJECT fdo)
	{							// CreateInterruptUrb
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ASSERT(pdx->PollingIrp == NULL);
	ASSERT(pdx->PollingUrb == NULL);

	PIRP Irp = IoAllocateIrp(pdx->LowerDeviceObject->StackSize, FALSE);
	if (!Irp)
		{
		KdPrint((DRIVERNAME " - Unable to create IRP for interrupt polling\n"));
		return STATUS_INSUFFICIENT_RESOURCES;
		}

	PURB urb = (PURB) ExAllocatePool(NonPagedPool, sizeof(_URB_BULK_OR_INTERRUPT_TRANSFER));
	if (!urb)
		{
		KdPrint((DRIVERNAME " - Unable to allocate interrupt polling URB\n"));
		IoFreeIrp(Irp);
		return STATUS_INSUFFICIENT_RESOURCES;
		}

	pdx->PollingIrp = Irp;
	pdx->PollingUrb = urb;

	return STATUS_SUCCESS;
	}							// CreateInterruptUrb

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DeleteInterruptUrb(PDEVICE_OBJECT fdo)
	{							// DeleteInterruptUrb
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	ASSERT(pdx->PollingIrp != NULL);
	ASSERT(pdx->PollingUrb != NULL);

	ExFreePool(pdx->PollingUrb);
	IoFreeIrp(pdx->PollingIrp);
	pdx->PollingIrp = NULL;
	pdx->PollingUrb = NULL;
	}							// DeleteInterruptUrb

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCleanup
	PAGED_CODE();
	KdPrint((DRIVERNAME " - IRP_MJ_CLEANUP\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	GenericCleanupControlRequests(pdx->pgx, STATUS_CANCELLED, stack->FileObject);

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

	// Only allow one handle at a time because we only have one place to
	// remember the pending IOCTL we use for notifying the application that
	// an interrupt has occurred. Setting the exclusive flag in our device
	// object is not likely to be effective in a production driver because
	// the named device object to which the open refers will usually be the PDO,
	// which won't necessarily have the exclusive attribute.

	if (InterlockedIncrement(&pdx->handles) > 1)
		{						// too many opens
		InterlockedDecrement(&pdx->handles);
		return CompleteRequest(Irp, STATUS_ACCESS_DENIED, 0);
		}						// too many opens

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

	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

	// Repower the device.

	status = GenericWakeupFromIdle(pdx->pgx, TRUE);
	if (NT_SUCCESS(status))
		status = STATUS_SUCCESS;	// most espcially not STATUS_PENDING
	else
		{
		InterlockedDecrement(&pdx->handles);
		if (!win98)
			IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);
		}

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

	// The cleanup routine should have gotten rid of any pending
	// WAITINT operation

	ASSERT(pdx->InterruptIrp == NULL);

	// Depower the device

	InterlockedDecrement(&pdx->handles);

	GenericIdleDevice(pdx->pgx, PowerDeviceD3);
	
	// Release the remove lock to match the acquisition done in DispatchCreate

	if (!win98)
		IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);

	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS GetStringDescriptor(PDEVICE_OBJECT fdo, UCHAR istring, PUNICODE_STRING s)
	{							// GetStringDescriptor
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	URB urb;

	UCHAR data[256];			// maximum-length buffer

	// If this is the first time here, read string descriptor zero and arbitrarily select
	// the first language identifer as the one to use in subsequent get-descriptor calls.

	if (!pdx->langid)
		{						// determine default language id
		UsbBuildGetDescriptorRequest(&urb, sizeof(_URB_CONTROL_DESCRIPTOR_REQUEST), USB_STRING_DESCRIPTOR_TYPE,
			0, 0, data, NULL, sizeof(data), NULL);
		status = SendAwaitUrb(fdo, &urb);
		if (!NT_SUCCESS(status))
			return status;
		pdx->langid = *(LANGID*)(data + 2);
		}						// determine default language id

	// Fetch the designated string descriptor.

	UsbBuildGetDescriptorRequest(&urb, sizeof(_URB_CONTROL_DESCRIPTOR_REQUEST), USB_STRING_DESCRIPTOR_TYPE,
		istring, pdx->langid, data, NULL, sizeof(data), NULL);
	status = SendAwaitUrb(fdo, &urb);
	if (!NT_SUCCESS(status))
		return status;

	ULONG nchars = (data[0] - 2) / 2;
	PWSTR p = (PWSTR) ExAllocatePool(PagedPool, data[0]);
	if (!p)
		return STATUS_INSUFFICIENT_RESOURCES;

	memcpy(p, data + 2, nchars*2);
	p[nchars] = 0;

	s->Length = (USHORT) (2 * nchars);
	s->MaximumLength = (USHORT) ((2 * nchars) + 2);
	s->Buffer = p;

	return STATUS_SUCCESS;
	}							// GetStringDescriptor

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnInterrupt(PDEVICE_OBJECT junk, PIRP Irp, PDEVICE_EXTENSION pdx)
	{							// OnInterrupt

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->polllock, &oldirql);
	pdx->pollpending = FALSE;		// allow another poll to be started
	PVOID powercontext = pdx->powercontext;
	pdx->powercontext = NULL;
	KeReleaseSpinLock(&pdx->polllock, oldirql);

	// If the poll completed successfully, do whatever it is we do when we
	// get an interrupt (in this sample, that's answering an IOCTL) and
	// reissue the read. We're trying to have a read outstanding on the
	// interrupt pipe all the time except when power is off.

	if (NT_SUCCESS(Irp->IoStatus.Status))
		{						// device signalled an interrupt
		KdPrint((DRIVERNAME " - Interrupt!\n"));

		PIRP intirp = GenericUncacheControlRequest(pdx->pgx, &pdx->InterruptIrp);
		if (intirp)
			CompleteRequest(intirp, STATUS_SUCCESS, 0);
		else
			InterlockedIncrement(&pdx->numints);

		// Unless we're in the middle of a power-off sequence, reissue the
		// polling IRP. Normally, SaveContext would have tried to cancel the
		// IRP, and we won't get to this statement because STATUS_CANCELLED
		// will fail the NT_SUCCESS test. We don't have any guarantee that the
		// IRP will actually complete with STATUS_CANCELLED, though. Hence this test.
		
		if (!powercontext)
			StartInterruptUrb(pdx); // issue next polling request
		}						// device signalled an interrupt
#if DBG	
	else
		{
		KdPrint((DRIVERNAME " - Interrupt polling IRP %X failed - %X (USBD status %X)\n",
			Irp, Irp->IoStatus.Status, URB_STATUS(pdx->PollingUrb)));
		}
#endif

	// If we cancelled the poll during a power-down sequence, notify our
	// power management code that it can continue.

	if (powercontext)
		GenericSaveRestoreComplete(powercontext);

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp); // balances acquisition in StartInterruptUrb

	return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnInterrupt

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID ResetDevice(PDEVICE_OBJECT fdo)
	{							// ResetDevice
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);
	IO_STATUS_BLOCK iostatus;

	PIRP Irp = IoBuildDeviceIoControlRequest(IOCTL_INTERNAL_USB_RESET_PORT,
		pdx->LowerDeviceObject, NULL, 0, NULL, 0, TRUE, &event, &iostatus);
	if (!Irp)
		return;

	NTSTATUS status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	if (status == STATUS_PENDING)
		{
		KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
		status = iostatus.Status;
		}

	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - Error %X trying to reset device\n", status));
	}							// ResetDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ResetPipe(PDEVICE_OBJECT fdo, USBD_PIPE_HANDLE hpipe)
	{							// ResetPipe
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	URB urb;

	urb.UrbHeader.Length = (USHORT) sizeof(_URB_PIPE_REQUEST);
	urb.UrbHeader.Function = URB_FUNCTION_RESET_PIPE;
	urb.UrbPipeRequest.PipeHandle = hpipe;

	NTSTATUS status = SendAwaitUrb(fdo, &urb);
	if (!NT_SUCCESS(status))
		KdPrint((DRIVERNAME " - Error %X trying to reset a pipe\n", status));
	return status;
	}							// ResetPipe

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID RestoreContext(PDEVICE_OBJECT fdo, DEVICE_POWER_STATE oldstate, DEVICE_POWER_STATE newstate, PVOID context)
	{							// RestoreContext

	// If power is on, make sure we have a read outstanding on our interrupt pipe

	if (newstate == PowerDeviceD0)
		StartInterruptUrb((PDEVICE_EXTENSION) fdo->DeviceExtension);

	// Notify the power management code that we're done with this operation

	GenericSaveRestoreComplete(context);
	}							// RestoreContext

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID SaveContext(PDEVICE_OBJECT fdo, DEVICE_POWER_STATE oldstate, DEVICE_POWER_STATE newstate, PVOID context)
	{							// SaveContext
	ASSERT(context);

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// If device is losing power, cancel any pending interrupt poll operation.
	// Defer the power operation until the cancel finishes

	if (newstate > PowerDeviceD0)
		{						// losing power
		KIRQL oldirql;
		KeAcquireSpinLock(&pdx->polllock, &oldirql);
		if (pdx->pollpending)
			{					// cancel poll
			pdx->powercontext = context;
			IoCancelIrp(pdx->PollingIrp);
			KeReleaseSpinLock(&pdx->polllock, oldirql);
			return;				// defer notification until IRP finishes
			}					// cancel poll
		KeReleaseSpinLock(&pdx->polllock, oldirql);
		}						// losing power

	// No need to cancel the poll, so notify power management code immediately

	GenericSaveRestoreComplete(context);
	}							// SaveContext

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS SendAwaitUrb(PDEVICE_OBJECT fdo, PURB urb)
	{							// SendAwaitUrb
	PAGED_CODE();
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IO_STATUS_BLOCK iostatus;
	PIRP Irp = IoBuildDeviceIoControlRequest(IOCTL_INTERNAL_USB_SUBMIT_URB,
		pdx->LowerDeviceObject, NULL, 0, NULL, 0, TRUE, &event, &iostatus);

	if (!Irp)
		{
		KdPrint((DRIVERNAME " - Unable to allocate IRP for sending URB\n"));
		return STATUS_INSUFFICIENT_RESOURCES;
		}

	PIO_STACK_LOCATION stack = IoGetNextIrpStackLocation(Irp);
	stack->Parameters.Others.Argument1 = (PVOID) urb;
	NTSTATUS status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	if (status == STATUS_PENDING)
		{
		KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
		status = iostatus.Status;
		}
	return status;
	}							// SendAwaitUrb

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	PAGED_CODE();
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	URB urb;					// URB for use in this subroutine

	// Read our device descriptor. The only real purpose to this would be to find out how many
	// configurations there are so we can read their descriptors. In this simplest of examples,
	// there's only one configuration.

	UsbBuildGetDescriptorRequest(&urb, sizeof(_URB_CONTROL_DESCRIPTOR_REQUEST), USB_DEVICE_DESCRIPTOR_TYPE,
		0, 0, &pdx->dd, NULL, sizeof(pdx->dd), NULL);
	status = SendAwaitUrb(fdo, &urb);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - Error %X trying to read device descriptor\n", status));
		return status;
		}

	ASSERT(pdx->dd.bNumConfigurations == 1); // only expect one configuration

	MSGUSBSTRING(fdo, DRIVERNAME " - Configuring device from %ws\n", pdx->dd.iManufacturer);
	MSGUSBSTRING(fdo, DRIVERNAME " - Product is %ws\n", pdx->dd.iProduct);
	MSGUSBSTRING(fdo, DRIVERNAME " - Serial number is %ws\n", pdx->dd.iSerialNumber);

	// Read the descriptor of the first configuration. This requires two steps. The first step
	// reads the fixed-size configuration descriptor alone. The second step reads the
	// configuration descriptor plus all imbedded interface and endpoint descriptors.

	USB_CONFIGURATION_DESCRIPTOR tcd;
	UsbBuildGetDescriptorRequest(&urb, sizeof(_URB_CONTROL_DESCRIPTOR_REQUEST), USB_CONFIGURATION_DESCRIPTOR_TYPE,
		0, 0, &tcd, NULL, sizeof(tcd), NULL);
	status = SendAwaitUrb(fdo, &urb);
	if (!NT_SUCCESS(status))
		{
		KdPrint((DRIVERNAME " - Error %X trying to read configuration descriptor 1\n", status));
		return status;
		}

	ULONG size = tcd.wTotalLength;
	PUSB_CONFIGURATION_DESCRIPTOR pcd = (PUSB_CONFIGURATION_DESCRIPTOR) ExAllocatePool(NonPagedPool, size);
	if (!pcd)
		{
		KdPrint((DRIVERNAME " - Unable to allocate %X bytes for configuration descriptor\n", size));
		return STATUS_INSUFFICIENT_RESOURCES;
		}

	__try
		{
		UsbBuildGetDescriptorRequest(&urb, sizeof(_URB_CONTROL_DESCRIPTOR_REQUEST), USB_CONFIGURATION_DESCRIPTOR_TYPE,
			0, 0, pcd, NULL, size, NULL);
		status = SendAwaitUrb(fdo, &urb);
		if (!NT_SUCCESS(status))
			{
			KdPrint((DRIVERNAME " - Error %X trying to read configuration descriptor 1\n", status));
			return status;
			}
                                   
		MSGUSBSTRING(fdo, DRIVERNAME " - Selecting configuration named %ws\n", pcd->iConfiguration);

		// Locate the descriptor for the one and only interface we expect to find

		PUSB_INTERFACE_DESCRIPTOR pid = USBD_ParseConfigurationDescriptorEx(pcd, pcd,
			-1, -1, -1, -1, -1);
		ASSERT(pid);
                                   
		MSGUSBSTRING(fdo, DRIVERNAME " - Selecting interface named %ws\n", pid->iInterface);

		// Create a URB to use in selecting a configuration.

		USBD_INTERFACE_LIST_ENTRY interfaces[2] = {
			{pid, NULL},
			{NULL, NULL},		// fence to terminate the array
			};

		PURB selurb = USBD_CreateConfigurationRequestEx(pcd, interfaces);
		if (!selurb)
			{
			KdPrint((DRIVERNAME " - Unable to create configuration request\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
			}

		__try
			{

			// Verify that the interface describes exactly the endpoints we expect

			if (pid->bNumEndpoints != 1)
				{
				KdPrint((DRIVERNAME " - %d is the wrong number of endpoints\n", pid->bNumEndpoints));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}

			PUSB_ENDPOINT_DESCRIPTOR ped = (PUSB_ENDPOINT_DESCRIPTOR) pid;
			ped = (PUSB_ENDPOINT_DESCRIPTOR) USBD_ParseDescriptors(pcd, tcd.wTotalLength, ped, USB_ENDPOINT_DESCRIPTOR_TYPE);
			if (!ped || ped->bEndpointAddress != 0x82 || ped->bmAttributes != USB_ENDPOINT_TYPE_INTERRUPT || ped->wMaxPacketSize != 4)
				{
				KdPrint((DRIVERNAME " - Endpoint has wrong attributes\n"));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}
			++ped;

			PUSBD_INTERFACE_INFORMATION pii = interfaces[0].Interface;
			ASSERT(pii->NumberOfPipes == pid->bNumEndpoints);

			// Submit the set-configuration request

			status = SendAwaitUrb(fdo, selurb);
			if (!NT_SUCCESS(status))
				{
				KdPrint((DRIVERNAME " - Error %X trying to select configuration\n", status));
				return status;
				}

			// Save the configuration and pipe handles

			pdx->hconfig = selurb->UrbSelectConfiguration.ConfigurationHandle;
			pdx->hintpipe = pii->Pipes[0].PipeHandle;

			// Start out with the device powered down.

			GenericIdleDevice(pdx->pgx, PowerDeviceD3);

			// Transfer ownership of the configuration descriptor to the device extension
			
			pdx->pcd = pcd;
			pcd = NULL;
			}
		__finally
			{
			ExFreePool(selurb);
			}

		}
	__finally
		{
		if (pcd)
			ExFreePool(pcd);
		}

	return STATUS_SUCCESS;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS StartInterruptUrb(PDEVICE_EXTENSION pdx)
	{							// StartInterruptUrb

	// If the interrupt polling IRP is currently running, don't try to start
	// it again.

	BOOLEAN startirp;
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->polllock, &oldirql);
	if (pdx->pollpending)
		startirp = FALSE;
	else
		startirp = TRUE, pdx->pollpending = TRUE;
	KeReleaseSpinLock(&pdx->polllock, oldirql);

	if (!startirp)
		return STATUS_DEVICE_BUSY;	// already pending

	PIRP Irp = pdx->PollingIrp;
	PURB urb = pdx->PollingUrb;
	ASSERT(Irp && urb);

	// Acquire the remove lock so we can't remove the device while the IRP
	// is still active.

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		{
		pdx->pollpending = 0;
		return status;
		}

	// Initialize the URB we use for reading the interrupt pipe

	UsbBuildInterruptOrBulkTransferRequest(urb, sizeof(_URB_BULK_OR_INTERRUPT_TRANSFER),
		pdx->hintpipe, &pdx->intdata, NULL, 4, USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK, NULL);

	// Install "OnInterrupt" as the completion routine for the polling IRP.
	
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnInterrupt, pdx, TRUE, TRUE, TRUE);

	// Initialize the IRP for an internal control request

	PIO_STACK_LOCATION stack = IoGetNextIrpStackLocation(Irp);
	stack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
	stack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;
	stack->Parameters.Others.Argument1 = urb;

	// This IRP might have been cancelled the last time it was used, in which case
	// the cancel flag will still be on. Clear it to prevent USBD from thinking that it's
	// been cancelled again! A better way to do this would be to call IoReuseIrp,
	// but that function is not declared in WDM.H.

	Irp->Cancel = FALSE;

	return IoCallDriver(pdx->LowerDeviceObject, Irp);
	}							// StartInterruptUrb

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID StopInterruptUrb(PDEVICE_EXTENSION pdx)
	{							// StopInterruptUrb
	if (pdx->pollpending)
		IoCancelIrp(pdx->PollingIrp);
	}							// StopInterruptUrb

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// Cancel the interrupt polling URB in case it's currently active

	StopInterruptUrb(pdx);

	// If it's okay to touch our hardware (i.e., we're processing an IRP_MN_STOP_DEVICE),
	// deconfigure the device.
	
	if (oktouch)
		{						// deconfigure device
		URB urb;
		UsbBuildSelectConfigurationRequest(&urb, sizeof(_URB_SELECT_CONFIGURATION), NULL);
		NTSTATUS status = SendAwaitUrb(fdo, &urb);
		if (!NT_SUCCESS(status))
			KdPrint((DRIVERNAME " - Error %X trying to deconfigure device\n", status));
		}						// deconfigure device

	if (pdx->pcd)
		ExFreePool(pdx->pcd);
	pdx->pcd = NULL;
	}							// StopDevice
