// Read/Write request processors for loopback driver
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

struct _RWCONTEXT : public _URB
	{							// struct _RWCONTEXT
	ULONG_PTR va;				// virtual address for next segment of transfer
	ULONG length;				// length remaining to transfer
	PMDL mdl;					// partial MDL
	ULONG numxfer;				// cumulate transfer count
	BOOLEAN multistage;			// TRUE if multistage transfer
	};							// struct _RWCONTEXT

typedef struct _RWCONTEXT RWCONTEXT, *PRWCONTEXT;

NTSTATUS OnReadWriteComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT ctx);

#define MAXTRANSFER PAGE_SIZE

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

NTSTATUS OnReadWriteComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT ctx)
	{							// OnReadWriteComplete
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	BOOLEAN read = (ctx->UrbBulkOrInterruptTransfer.TransferFlags & USBD_TRANSFER_DIRECTION_IN) != 0;
	ctx->numxfer += ctx->UrbBulkOrInterruptTransfer.TransferBufferLength;

#if DBG
	USBD_STATUS urbstatus = URB_STATUS(ctx);
	if (!USBD_SUCCESS(urbstatus))
		KdPrint(("LOOPBACK -  %s failed with USBD status %X\n", read ? "Read" : "Write", urbstatus));
#endif

	// If this stage completed without error, resubmit the URB to perform the
	// next stage

	NTSTATUS status = Irp->IoStatus.Status;
	if (NT_SUCCESS(status) && ctx->length)
		{						// start next stage

		// Calculate length of next stage of the transfer

		ULONG seglen = ctx->length;
		if (seglen > MAXTRANSFER)

	#if (MAXTRANSFER >= PAGE_SIZE)
			seglen = (ULONG_PTR) PAGE_ALIGN(ctx->va) + PAGE_SIZE - ctx->va;
	#else
			seglen = MAXTRANSFER;
	#endif

		// We're now in arbitrary thread context, so the virtual address of the
		// user buffer is currently meaningless. IoBuildPartialMdl copies physical
		// page numbers from the original IRP's probed-and-locked MDL, however,
		// so our process context doesn't matter.

		IoBuildPartialMdl(Irp->MdlAddress, ctx->mdl, (PVOID) ctx->va, seglen);

		// Reinitialize the URB

		ctx->UrbBulkOrInterruptTransfer.TransferBufferLength = seglen;

		// The "next" stack location is the one belonging to the driver
		// underneath us. It's been mostly set to zero and must be reinitialized.

		PIO_STACK_LOCATION stack = IoGetNextIrpStackLocation(Irp);
		stack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
		stack->Parameters.Others.Argument1 = (PVOID) (PURB) ctx;
		stack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;
		IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnReadWriteComplete,
			(PVOID) ctx, TRUE, TRUE, TRUE);

		ctx->va += seglen;
		ctx->length -= seglen;

		// Pass the recycled IRP down and ignore the return code from IoCallDriver. If
		// this stage gets completed synchronously, this very completion routine will
		// already have been called recursively to deal with it. If not, the IRP is
		// now active again. In either case, we want the current invocation IoCompleteRequest
		// to stop working on this IRP.

		IoCallDriver(pdx->LowerDeviceObject, Irp);
		return STATUS_MORE_PROCESSING_REQUIRED; // halt completion process in its tracks!
		}						// start next stage

	// The request is complete now

	if (NT_SUCCESS(status))
		Irp->IoStatus.Information = ctx->numxfer;
	else
		{					// had an error
		if (read)
			InterlockedIncrement(&pdx->inerror);
		else
			InterlockedIncrement(&pdx->outerror);

		KdPrint(("LOOPBACK - %s finished with error %X\n", read ? "Read" : "Write", status));
		}					// had an error

	ExFreePool(ctx->mdl);
	ExFreePool(ctx);
	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);

	return status;
	}							// OnReadWriteComplete

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// ReadWrite
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
		
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	BOOLEAN read = stack->MajorFunction == IRP_MJ_READ;

	USBD_PIPE_HANDLE hpipe = read ? pdx->hinpipe : pdx->houtpipe;
	LONG haderr;
	if (read)
		haderr = InterlockedExchange(&pdx->inerror, 0);
	else
		haderr = InterlockedExchange(&pdx->outerror, 0);
	if (haderr && !NT_SUCCESS(ResetPipe(fdo, hpipe)))
		ResetDevice(fdo);

	// Our strategy will be to do the transfer in stages up to MAXTRANSFER bytes
	// long using a single URB that we resubmit during the completion routine.
	// Note that chained URBs via UrbLink are not supported in either Win98 or Win2K.

	PRWCONTEXT ctx = (PRWCONTEXT) ExAllocatePool(NonPagedPool, sizeof(RWCONTEXT));
	if (!ctx)
		{
		KdPrint((DRIVERNAME " - Can't allocate memory for context structure\n"));
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return CompleteRequest(Irp, STATUS_INSUFFICIENT_RESOURCES, 0);
		}
	RtlZeroMemory(ctx, sizeof(RWCONTEXT));

	ULONG length = Irp->MdlAddress ?  MmGetMdlByteCount(Irp->MdlAddress) : 0;
	if (!length)
		{						// zero-length read
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return CompleteRequest(Irp, STATUS_SUCCESS, 0);
		}						// zero-length read
	ULONG_PTR va = (ULONG_PTR) MmGetMdlVirtualAddress(Irp->MdlAddress);

	ULONG urbflags =  USBD_SHORT_TRANSFER_OK | (read ? USBD_TRANSFER_DIRECTION_IN : USBD_TRANSFER_DIRECTION_OUT);

	// Calculate the length of the segment we'll transfer in the first stage.
	// If we're using PAGE_SIZE as our maximum transfer length (which would be the
	// default used by USBD), do a short initial transfer to get us up to a page
	// boundary.

	ULONG seglen = length;
	if (seglen > MAXTRANSFER)

#if (MAXTRANSFER >= PAGE_SIZE)
		seglen = (ULONG_PTR) PAGE_ALIGN(va) + PAGE_SIZE - va;
#else
		seglen = MAXTRANSFER;
#endif

	// Allocate an MDL for each segment of the transfer. The length parameter here
	// is chosen so that the MDL has the capacity to describe two physical pages,
	// which is the most that any stage will ever need.

	PMDL mdl = IoAllocateMdl((PVOID) va, PAGE_SIZE, FALSE, FALSE, NULL);
	if (!mdl)
		{					// can't allocate MDL
		KdPrint((DRIVERNAME " - Can't allocate memory for MDL\n"));
		ExFreePool(ctx);
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return CompleteRequest(Irp, STATUS_INSUFFICIENT_RESOURCES, 0);
		}					// can't allocate MDL

	// Initialize the (partial) MDL to describe the first segment's subset of the user
	// buffer.

	IoBuildPartialMdl(Irp->MdlAddress, mdl, (PVOID) va, seglen);

	UsbBuildInterruptOrBulkTransferRequest(ctx, sizeof(_URB_BULK_OR_INTERRUPT_TRANSFER),
		hpipe, NULL, mdl, seglen, urbflags, NULL);

	// Set context structure parameters to pick up where we just left off

	ctx->va = va + seglen;
	ctx->length = length - seglen;
	ctx->mdl = mdl;
	ctx->numxfer = 0;

	// Use the original Read or Write IRP as a container for the URB

	stack = IoGetNextIrpStackLocation(Irp);
	stack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
	stack->Parameters.Others.Argument1 = (PVOID) (PURB) ctx;
	stack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;

	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnReadWriteComplete,
		(PVOID) ctx, TRUE, TRUE, TRUE);

	// Pass the request down. It might happen that the bus driver completes this segment
	// of the request synchronously (it won't, but we shouldn't assume that will be true 
	// forever). If we simply return a success code here, it might also happen (depending
	// on who exactly built this IRP) that the I/O manager will decide it's okay to
	// release the IRP right now. In that case, our completion routine will blunder badly
	// by reusing the IRP. To avoid this happening, we want to be sure we return STATUS_PENDING
	// if there are more stages to go. For a discussion of the problem, see Rajeev Nagar,
	// "Windows NT File System Internals" (O'Reilly 1997) at 658-60. I'm indebted to a spirited
	// online discussion for pointing out this potential problem. Note that marking the IRP
	// pending here may cause IoCompleteRequest to schedule a completion APC when none is really
	// needed. This could cause a minor loss of performance. Logic to mark the IRP pending only
	// when actually required would be convoluted and fragile, however.

	IoMarkIrpPending(Irp);
	status = IoCallDriver(pdx->LowerDeviceObject, Irp);
	if (!NT_SUCCESS(status) && !NT_SUCCESS(ResetPipe(fdo, hpipe)))
		ResetDevice(fdo);

	return STATUS_PENDING;	
	}							// ReadWrite

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

			if (pid->bNumEndpoints != 2)
				{
				KdPrint((DRIVERNAME " - %d is the wrong number of endpoints\n", pid->bNumEndpoints));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}

			PUSB_ENDPOINT_DESCRIPTOR ped = (PUSB_ENDPOINT_DESCRIPTOR) pid;
			ped = (PUSB_ENDPOINT_DESCRIPTOR) USBD_ParseDescriptors(pcd, tcd.wTotalLength, ped, USB_ENDPOINT_DESCRIPTOR_TYPE);
			if (!ped || ped->bEndpointAddress != 0x82 || ped->bmAttributes != USB_ENDPOINT_TYPE_BULK || ped->wMaxPacketSize != 64)
				{
				KdPrint((DRIVERNAME " - Endpoint has wrong attributes\n"));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}
			++ped;
			if (!ped || ped->bEndpointAddress != 0x2 || ped->bmAttributes != USB_ENDPOINT_TYPE_BULK || ped->wMaxPacketSize != 64)
				{
				KdPrint((DRIVERNAME " - Endpoint has wrong attributes\n"));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}
			++ped;

			PUSBD_INTERFACE_INFORMATION pii = interfaces[0].Interface;
			ASSERT(pii->NumberOfPipes == pid->bNumEndpoints);

			// Initialize the maximum transfer size for each of the endpoints

			pii->Pipes[0].MaximumTransferSize = PAGE_SIZE;
			pii->Pipes[1].MaximumTransferSize = PAGE_SIZE;

			// Submit the set-configuration request

			status = SendAwaitUrb(fdo, selurb);
			if (!NT_SUCCESS(status))
				{
				KdPrint((DRIVERNAME " - Error %X trying to select configuration\n", status));
				return status;
				}

			// Save the configuration and pipe handles

			pdx->hconfig = selurb->UrbSelectConfiguration.ConfigurationHandle;
			pdx->hinpipe = pii->Pipes[0].PipeHandle;
			pdx->houtpipe = pii->Pipes[1].PipeHandle;

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

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

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
