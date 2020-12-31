// Read/Write request processors for usbiso driver
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

typedef struct _RWCONTEXT {
	LIST_ENTRY list;			// list for queuing context structures
	PDEVICE_EXTENSION pdx;		// our device extension address
	PIRP mainirp;				// the main r/w IRP
	NTSTATUS status;			// ending status for main IRP
	ULONG numxfer;				// total number of bytes transferred
	ULONG numirps;				// total number of sub-irps
	LONG numpending;			// number of sub-irps not yet finished
	LONG refcnt;				// reference count (initially 2)
	struct {
		PIRP irp;				// subsidiary IRP
		PURB urb;				// URB packaged with sub-IRP
		PMDL mdl;				// partial MDL for the URB
		} sub[1];
	} RWCONTEXT, *PRWCONTEXT;

BOOLEAN DestroyContextStructure(PRWCONTEXT ctx);
VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
NTSTATUS OnReadWriteComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT context);
NTSTATUS OnStageComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT context);

NTSTATUS SelectAlternateInterface(PDEVICE_OBJECT fdo);
NTSTATUS SelectDefaultInterface(PDEVICE_OBJECT fdo);

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

#pragma LOCKEDCODE

BOOLEAN DestroyContextStructure(PRWCONTEXT ctx)
	{							// DestroyContextStructure

	// Decrement the reference count. If it goes to zero, delete
	// all the subsidiary IRPs and the context structure itself.

	if (InterlockedDecrement(&ctx->refcnt) > 0)
		return FALSE;					// still potentially in use
	for (ULONG i = 0; i < ctx->numirps; ++i)
		if (ctx->sub[i].irp)
			IoFreeIrp(ctx->sub[i].irp);
	ExFreePool(ctx);
	return TRUE;
	}							// DestroyContextStructure

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
		{						// not deleted
		if (InterlockedIncrement(&pdx->handles) == 1)
			{					// no handles previously open
			status = SelectAlternateInterface(fdo);
			if (!NT_SUCCESS(status))
				{				// error selecting alternate interface
				InterlockedDecrement(&pdx->handles);
				IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);
				}				// error selecting alternate interface
			}					// no handles previously open
		}						// not deleted
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
	if (InterlockedDecrement(&pdx->handles) == 0)
		SelectDefaultInterface(fdo);
	
	// Release the remove lock to match the acquisition done in DispatchCreate

	if (!win98)
		IoReleaseRemoveLock(&pdx->RemoveLock, stack->FileObject);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
	}							// DispatchClose

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchRead(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchRead
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	ASSERT(pdx->hinpipe);

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);

	// Reset pipe if previous request had an error

	LONG haderr;
	haderr = InterlockedExchange(&pdx->inerror, 0);
	if (haderr && !NT_SUCCESS(ResetPipe(fdo, pdx->hinpipe)))
		ResetDevice(fdo);

	ULONG length = Irp->MdlAddress ?  MmGetMdlByteCount(Irp->MdlAddress) : 0;
	if (!length)
		{						// zero-length read
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return CompleteRequest(Irp, STATUS_SUCCESS, 0);
		}						// zero-length read

	// Calculate the number of IRPs that we need to submit in order to fulfill the
	// request. One of the ingredients of the calculation is the "packet size" the
	// endpoint uses during each frame. We have to know this number a priori, because
	// it doesn't have a fixed relationship to the endpoint's transfer size. Another
	// ingredient of the calculation is the fact that one URB can accomodate only 255
	// packets. The last ingredient is the maximum transfer size we declared when we
	// first configured the pipe. This driver left the default value in place. Given
	// the value of 16 used here for the packet size, we'll end up with a "segsize" of
	// 4080 bytes in fact.

	ULONG packsize = 16;		// known because we write the firmware
	ULONG segsize = USBD_DEFAULT_MAXIMUM_TRANSFER_SIZE; // default we left in place
	if (segsize / packsize > 255)
		segsize = 255 * packsize;	// maximum based on # packets allowed
	ULONG numirps = (length + segsize - 1) / segsize;

	// Allocate a context structure for use in the main IRP's completion and cancel routines.
	// Build as many IRPs (and URBs) as are required to fulfill the request.

	ULONG ctxsize = sizeof(RWCONTEXT) + (numirps - 1) * sizeof(((PRWCONTEXT) 0)->sub);
	PRWCONTEXT ctx = (PRWCONTEXT) ExAllocatePool(NonPagedPool, ctxsize);
	if (!ctx)
		{
		KdPrint((DRIVERNAME	" - unable to allocate %d bytes for record keeping\n", ctxsize));
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return CompleteRequest(Irp, STATUS_INSUFFICIENT_RESOURCES, 0);
		}
	RtlZeroMemory(ctx, ctxsize);

	ctx->numirps = ctx->numpending = numirps;
	ctx->pdx = pdx;
	ctx->mainirp = Irp;
	ctx->refcnt = 2;			// one for OnReadWriteComplete, one forOnCancelReadWrite
	Irp->Tail.Overlay.DriverContext[0] = (PVOID) ctx; // for cancel routine

	ULONG i;
	CCHAR stacksize = pdx->LowerDeviceObject->StackSize + 1; // 1 extra for OnStageComplete
	PUCHAR va = (PUCHAR) MmGetMdlVirtualAddress(Irp->MdlAddress);

	for (i = 0; i < numirps; ++i)
		{						// for each IRP

		// Create a subsidiary IRP

		PIRP subirp = IoAllocateIrp(stacksize, FALSE);
		if (!subirp)
			break;				// can't create subsidiary IRP
		ctx->sub[i].irp = subirp;

		// Determine how many packets are required and allocate an URB big enough for all of them

		if (segsize > length)
			segsize = length;	// last transfer is short

		ULONG npackets = (segsize + packsize - 1) / packsize; // # packets needed in this stage
		ASSERT(npackets <= 255);	// else we didn't calculate segsize correctly
		ULONG size = GET_ISO_URB_SIZE(npackets); // size of URB needed for that many packets
		PURB urb = (PURB) ExAllocatePool(NonPagedPool, size);
		if (!urb)
			break;

		ctx->sub[i].urb = urb;

		// Create a partial MDL to map this segment. This is necessary because the offset fields in
		// the packet descriptors we'll build must begin at zero for each URB. (It would have been better
		// if they were just relative to whatever MDL in in the URB.)

		PMDL mdl = IoAllocateMdl((PVOID) va, segsize, FALSE, FALSE, NULL);
		if (!mdl)
			break;				// can't allocate memory for MDL
		IoBuildPartialMdl(Irp->MdlAddress, mdl, (PVOID) va, segsize);
		ctx->sub[i].mdl = mdl;
		va += segsize;			// for next iteration

		// Initialize the URB

		RtlZeroMemory(urb, size);
		urb->UrbIsochronousTransfer.Hdr.Length = (USHORT) size;
		urb->UrbIsochronousTransfer.Hdr.Function = URB_FUNCTION_ISOCH_TRANSFER;
		urb->UrbIsochronousTransfer.PipeHandle = pdx->hinpipe;
		urb->UrbIsochronousTransfer.TransferFlags = USBD_TRANSFER_DIRECTION_IN | USBD_SHORT_TRANSFER_OK | USBD_START_ISO_TRANSFER_ASAP;
		urb->UrbIsochronousTransfer.TransferBufferLength = segsize;
		urb->UrbIsochronousTransfer.TransferBufferMDL = mdl;
		urb->UrbIsochronousTransfer.NumberOfPackets = npackets;

		// Initialize the buffer offset in each packet. The host controller will fill in the packet
		// length in one of two ways. For an input operation, it gets set to whatever the device
		// supplies. For an output operation, the host controller driver sets it based on the buffer
		// offsets.

		ULONG offset = 0;			// packet offset within subsidiary MDL

		for (ULONG j = 0; j < npackets; ++j)
			{						// for each packet
			urb->UrbIsochronousTransfer.IsoPacket[j].Offset = offset;
			ULONG packlen = length > packsize ? packsize : length;
			urb->UrbIsochronousTransfer.IsoPacket[j].Length = 0;

			length -= packlen;
			offset += packlen;
			}						// for each packet

		// Initialize the subsidiary IRP. The first stack location is for use by OnStageComplete,
		// which needs several pieces of information it's inconvenient to pass in a single
		// context pointer. The second stack location will describe an internal IOCTL for USBD.

		IoSetNextIrpStackLocation(subirp);
		PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(subirp);
		stack->DeviceObject = fdo;
		stack->Parameters.Others.Argument1 = (PVOID) urb;
		stack->Parameters.Others.Argument2 = (PVOID) mdl;

		stack = IoGetNextIrpStackLocation(subirp);
		stack->MajorFunction = IRP_MJ_INTERNAL_DEVICE_CONTROL;
		stack->Parameters.Others.Argument1 = (PVOID) urb;
		stack->Parameters.DeviceIoControl.IoControlCode = IOCTL_INTERNAL_USB_SUBMIT_URB;
		
		IoSetCompletionRoutine(subirp, (PIO_COMPLETION_ROUTINE) OnStageComplete,
			(PVOID) ctx, TRUE, TRUE, TRUE);
		}						// for each IRP

	// If the IRP/URB construction loop finished early, there must have been a memory allocation
	// error.

	if (i < numirps)
		status = STATUS_INSUFFICIENT_RESOURCES;

	// See if the main IRP has already been cancelled.

	else
		{						// check for cancellation
		IoSetCancelRoutine(Irp, OnCancelReadWrite);
		if (Irp->Cancel)
			{
			status = STATUS_CANCELLED;

			// The main IRP has been cancelled. If the cancellation just happened and our
			// cancel routine was called, the following call to IoSetCancelRoutine will
			// return NULL. In this case, both our cleanup code (see below) and the cancel
			// routine will be calling DestroyContextStructure. One or the other of those
			// calls will finish the cleanup of the structure. Otherwise, it will no longer
			// be possible for our cancel routine to get called and we should get rid of
			// its now-unnecessary claim on the structure.

			if (IoSetCancelRoutine(Irp, NULL))
				--ctx->refcnt;
			}
		else
			status = STATUS_SUCCESS;
		}						// check for cancellation

	// Install a completion routine for the main IRP. It will normally be called when
	// the last stage IRP finishes. It might get called pretty soon, though, if we
	// fail the IRP before submitting the stage IRPs.

	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnReadWriteComplete,
		(PVOID) ctx, TRUE, TRUE, TRUE);
	IoMarkIrpPending(Irp);
	IoSetNextIrpStackLocation(Irp);	// so our completion routine will get called

	// If we need to fail the main IRP, cleanup and fail it now.

	if (!NT_SUCCESS(status))
		{						// abort now
		for (i = 0; i < numirps; ++i)
			{					// release memory we were able to allocate
			if (ctx->sub[i].urb)
				ExFreePool(ctx->sub[i].urb);
			if (ctx->sub[i].mdl)
				IoFreeMdl(ctx->sub[i].mdl);
			}					// release memory we were able to allocate
		CompleteRequest(Irp, status, 0); // will trigger completion routine
		return STATUS_PENDING;
		}						// abort now

	ASSERT(length == 0);		// IRP construction loop didn't work right if not true

	// Install a completion routine for the main IRP. Once this is in place, submit the
	// subsidiary IRPs. Note that we can't touch the main IRP pointer after we submit the
	// subsidiary IRPs because the sub-IRP completion routine (OnStageComplete) may complete it.

	for (i = 0; i < numirps; ++i)
		IoCallDriver(pdx->LowerDeviceObject, ctx->sub[i].irp);

	return STATUS_PENDING;
	}							// DispatchRead

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

VOID OnCancelReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// OnCancelReadWrite
	
	IoReleaseCancelSpinLock(Irp->CancelIrql);

	// Attempt to cancel all the subsidiary IRPs for this IRP. The main IRP cannot
	// have progressed in the cancellation process past our own completion routine,
	// so it's safe to use DriverContext as a pointer to the context structure.

	PRWCONTEXT ctx = (PRWCONTEXT) Irp->Tail.Overlay.DriverContext[0];
	for (ULONG i = 0; i < ctx->numirps; ++i)
		IoCancelIrp(ctx->sub[i].irp);

	// Release our claim on the context structure and subsidiary IRP pointers. If
	// the completion routine has already run, it's up to us to finish the
	// completion process for this IRP.

	PDEVICE_EXTENSION pdx = ctx->pdx;

	if (DestroyContextStructure(ctx))
		{						// we're last
		CompleteRequest(Irp, STATUS_CANCELLED, 0);
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		}						// we're last
	}							// OnCancelReadWrite

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnReadWriteComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT ctx)
	{							// OnReadWriteComplete
	ASSERT(ctx->mainirp == Irp);
	PDEVICE_EXTENSION pdx = ctx->pdx;

	if (NT_SUCCESS(Irp->IoStatus.Status))
		Irp->IoStatus.Information = ctx->numxfer;
	else
		InterlockedIncrement(&pdx->inerror);

	// Release the context structure. If the cancel routine has run (or can't ever
	// run), we'll return a normal status. If the cancel routine is working now as
	// well, however, return STATUS_MORE_PROCESSING_REQUIRED to stop the completion
	// process for the time being.

	if (DestroyContextStructure(ctx))
		{						// we're last
		IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
		return STATUS_SUCCESS;
		}						// we're last
	else
		return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnReadWriteComplete

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

NTSTATUS OnStageComplete(PDEVICE_OBJECT fdo, PIRP Irp, PRWCONTEXT ctx)
	{							// OnStageComplete
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	PIRP mainirp = ctx->mainirp;
	PURB urb = (PURB) stack->Parameters.Others.Argument1;

	NTSTATUS status = Irp->IoStatus.Status;
	if (NT_SUCCESS(status))
		ctx->numxfer += urb->UrbIsochronousTransfer.TransferBufferLength;
	else
		{
		KdPrint((DRIVERNAME " - read failed with status %X (USBD status %X)\n", status, URB_STATUS(urb)));
		ctx->status = status;
		}

#if DBG
	KdPrint((DRIVERNAME " - iso transfer started in frame %8.8lX, %d packets had errors\n",
		urb->UrbIsochronousTransfer.StartFrame, urb->UrbIsochronousTransfer.ErrorCount));
	for (ULONG i = 0; i < urb->UrbIsochronousTransfer.NumberOfPackets; ++i)
		{						// for each packet
		PUSBD_ISO_PACKET_DESCRIPTOR pipd = &urb->UrbIsochronousTransfer.IsoPacket[i];
		KdPrint((DRIVERNAME " - Packet %d, %d bytes, ending status %8.8lX\n", i, pipd->Length, pipd->Status));
		}						// for each packet
#endif

	ExFreePool(urb);
	IoFreeMdl((PMDL) stack->Parameters.Others.Argument2);

	if (InterlockedDecrement(&ctx->numpending) == 0)
		{						// complete main IRP

		// Clear the main IRP's cancel pointer in preparation for completing it. If
		// the cancel routine has already run (or is now running), it called/will call
		// DestroyContextStructure. If IoSetCancelRoutine returns a non-NULL value,
		// however, it means that the cancel routine can never be called. We should
		// therefore use up its reference to the context structure so the main
		// completion routine can delete it.

		if (IoSetCancelRoutine(mainirp, NULL))
			InterlockedDecrement(&ctx->refcnt);	// cancel routine can no longer run
		mainirp->IoStatus.Status = ctx->status;
		IoCompleteRequest(mainirp, IO_NO_INCREMENT);
		}						// complete main IRP

	// Return STATUS_MORE_PROCESSING_REQUIRED to prevent IoCompleteRequest from
	// queuing an APC to release the memory for this subsidiary IRP. A comment
	// in OnReadWriteComplete explains what's going on here

	return STATUS_MORE_PROCESSING_REQUIRED;
	}							// OnStageComplete

//////////////////////////////////////////////////////////////////////////////

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

NTSTATUS SelectAlternateInterface(PDEVICE_OBJECT fdo)
	{							// SelectAlternateInterface
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// Locate the descriptor for the alternate interface we want

	PUSB_INTERFACE_DESCRIPTOR pid = USBD_ParseConfigurationDescriptorEx(pdx->pcd, pdx->pcd,
		0, 1, -1, -1, -1);

	if (!pid)
		{
		KdPrint((DRIVERNAME " - No alternatate interface defined\n"));
		return STATUS_DEVICE_CONFIGURATION_ERROR;
		}

	// Verify the characteristics of the interface

	PUSB_CONFIGURATION_DESCRIPTOR pcd = pdx->pcd;
	PUSB_ENDPOINT_DESCRIPTOR ped = (PUSB_ENDPOINT_DESCRIPTOR) pid;
	ped = (PUSB_ENDPOINT_DESCRIPTOR) USBD_ParseDescriptors(pcd, pcd->wTotalLength, ped, USB_ENDPOINT_DESCRIPTOR_TYPE);

	if (!ped || ped->bmAttributes != USB_ENDPOINT_TYPE_ISOCHRONOUS || ped->wMaxPacketSize < 16)
		{
		KdPrint((DRIVERNAME " - Alternate interface has wrong attributes\n"));
		return STATUS_DEVICE_CONFIGURATION_ERROR;
		}
	
	// Allocate an URB big enough to describe the alternate interface. First determine
	// how many pipes will be opened

	ULONG size = GET_SELECT_INTERFACE_REQUEST_SIZE(pid->bNumEndpoints);
	PURB urb = (PURB) ExAllocatePool(NonPagedPool, size);
	if (!urb)
		{
		KdPrint((DRIVERNAME " - can't allocate %d bytes for Select Interface URB\n", size));
		return STATUS_INSUFFICIENT_RESOURCES;
		}
	RtlZeroMemory(urb, size);

	// Build and submit the URB

	UsbBuildSelectInterfaceRequest(urb, (USHORT) size, pdx->hconfig, 0, 1);
	urb->UrbSelectInterface.Interface.Length = GET_USBD_INTERFACE_SIZE(pid->bNumEndpoints);
	urb->UrbSelectInterface.Interface.Pipes[0].MaximumTransferSize = PAGE_SIZE;

	status = SendAwaitUrb(fdo, urb);
	if (NT_SUCCESS(status))
		{
		pdx->hinpipe = urb->UrbSelectInterface.Interface.Pipes[0].PipeHandle;
		MSGUSBSTRING(fdo, DRIVERNAME " - Selecting interface named %ws\n", pid->iInterface);
		status = STATUS_SUCCESS;
		}
	else
		KdPrint((DRIVERNAME " - Error %X trying to select alternate interface\n", status));


	ExFreePool(urb);
	return status;
	}							// SelectAlternateInterface

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS SelectDefaultInterface(PDEVICE_OBJECT fdo)
	{							// SelectDefaultInterface
	NTSTATUS status;
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	
	// Allocate an URB big enough to describe the default interface. First determine
	// how many pipes will be opened

	PUSB_INTERFACE_DESCRIPTOR pid = USBD_ParseConfigurationDescriptorEx(pdx->pcd, pdx->pcd,
		0, 0, -1, -1, -1);
	ASSERT(pid);
	ULONG size = GET_SELECT_INTERFACE_REQUEST_SIZE(pid->bNumEndpoints);
	PURB urb = (PURB) ExAllocatePool(NonPagedPool, size);
	if (!urb)
		{
		KdPrint((DRIVERNAME " - can't allocate %d bytes for Select Interface URB\n", size));
		return STATUS_INSUFFICIENT_RESOURCES;
		}
	RtlZeroMemory(urb, size);

	// Build and submit the URB

	UsbBuildSelectInterfaceRequest(urb, (USHORT) size, pdx->hconfig, 0, 0);
	urb->UrbSelectInterface.Interface.Length = GET_USBD_INTERFACE_SIZE(pid->bNumEndpoints);
	status = SendAwaitUrb(fdo, urb);
	if (NT_SUCCESS(status))
		{
		pdx->hinpipe = NULL;
		MSGUSBSTRING(fdo, DRIVERNAME " - Selecting interface named %ws\n", pid->iInterface);
		status = STATUS_SUCCESS;
		}
	else
		KdPrint((DRIVERNAME " - Error %X trying to select default interface\n", status));


	ExFreePool(urb);
	return status;
	}							// SelectDefaultInterface

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

			if (pid->bNumEndpoints != 0)
				{
				KdPrint((DRIVERNAME " - %d is the wrong number of endpoints\n", pid->bNumEndpoints));
				return STATUS_DEVICE_CONFIGURATION_ERROR;
				}

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
			pdx->hinpipe = NULL;

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
