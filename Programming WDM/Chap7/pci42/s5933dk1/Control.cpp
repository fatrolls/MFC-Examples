// Control.cpp -- IOCTL handlers for s5933dk1 driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

struct _MAILBOX_WORKITEM : public _WORKITEM {
	ULONG mask;					// mask of bits to inspect
	ULONG mbef;					// desired value of masked MBEF
	};
typedef struct _MAILBOX_WORKITEM MAILBOX_WORKITEM, *PMAILBOX_WORKITEM;

struct _DMA_WORKITEM : public _WORKITEM {
	PUCHAR buffer;				// data buffer address
	ULONG nbytes;				// remaining byte count
	ULONG numxfer;				// number transferred so far
	BOOLEAN isread;				// TRUE if read, FALSE if write
	};
typedef struct _DMA_WORKITEM DMA_WORKITEM, *PDMA_WORKITEM;

// TODO Add support for add-on interrupts (via a constant poll, since the
// ISA card doesn't have an interrupt), for add-on initiated DMA, for
// nvRAM programming, for pass-through operations, and for built-in self test
// simulation

///////////////////////////////////////////////////////////////////////////////

BOOLEAN ReadDmaCallback(PDEVICE_EXTENSION pdx, PDMA_WORKITEM item, PVOID context);
NTSTATUS ReadWriteDma(PDEVICE_EXTENSION pdx, PIRP Irp, BOOLEAN isread);
NTSTATUS ReadWriteMailbox(PDEVICE_EXTENSION pdx, PREADWRITE_MAILBOX_PARAMS p);
NTSTATUS ResetDevice(PDEVICE_EXTENSION pdx);
NTSTATUS WaitMailbox(PDEVICE_EXTENSION pdx, PMAILBOX_WAIT_PARAMS p, PIRP Irp);
BOOLEAN WaitMailboxCallback(PDEVICE_EXTENSION pdx, PMAILBOX_WORKITEM item, PVOID context);
BOOLEAN WriteDmaCallback(PDEVICE_EXTENSION pdx, PDMA_WORKITEM item, PVOID context);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchCleanup(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchCleanup
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	CleanupWorkItems(pdx, stack->FileObject);
	
	return STATUS_SUCCESS;
	}							// DispatchCleanup

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

	case IOCTL_GET_VERSION:				// code == 0x800
		{						// IOCTL_GET_VERSION
		if (cbout < sizeof(ULONG))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}
		*(PULONG) Irp->AssociatedIrp.SystemBuffer = 0x0004000A;
		info = sizeof(ULONG);
		break;
		}						// IOCTL_GET_VERSION

	case IOCTL_RESET:				// code == 0x801
		{						// IOCTL_RESET
		status = ResetDevice(pdx);
		break;
		}						// IOCTL_RESET

	case IOCTL_READWRITE_MAILBOX:	// code == 0x802
		{						// IOCTL_WRITE
		if (cbin < sizeof(READWRITE_MAILBOX_PARAMS))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		PREADWRITE_MAILBOX_PARAMS p = (PREADWRITE_MAILBOX_PARAMS) Irp->AssociatedIrp.SystemBuffer;

		if (p->nbytes > 3 || p->mailbox < 1 || p->mailbox > 3)
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		status = ReadWriteMailbox(pdx, p);
		if (NT_SUCCESS(status))
			info = cbout;
		break;
		}						// IOCTL_WRITE

	case IOCTL_MAILBOX_WAIT:		// code == 0x803
		{						// IOCTL_MAILBOX_WAIT
		if (cbin < sizeof(MAILBOX_WAIT_PARAMS))
			{
			status = STATUS_INVALID_PARAMETER;
			break;
			}

		PMAILBOX_WAIT_PARAMS p = (PMAILBOX_WAIT_PARAMS) Irp->AssociatedIrp.SystemBuffer;

		// If a work item was queued, release the remove lock (so pendancy of this
		// operation doesn't hold up PnP events) and return STATUS_PENDING. Completion
		// of the work item will complete the IRP.

		status = WaitMailbox(pdx, p, Irp);
		if (status == STATUS_PENDING)
			{					// not finished yet
			IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
			return STATUS_PENDING;
			}					// not finished yet

		break;
		}						// IOCTL_MAILBOX_WAIT

	case IOCTL_READ_DMA:		// code == 0x804
	case IOCTL_WRITE_DMA:		// code == 0x805
		status = ReadWriteDma(pdx, Irp, code == IOCTL_READ_DMA);

		if (status == STATUS_PENDING)
			{					// not finished yet
			IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
			return STATUS_PENDING;
			}					// not finished yet
		
		break;

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

BOOLEAN ReadDmaCallback(PDEVICE_EXTENSION pdx, PDMA_WORKITEM item, PVOID context)
	{							// ReadDmaCallback
	while (item->nbytes)
		{						// read available data

		// See if there is any data available to be read.

		ULONG gcsts = READ_PORT_ULONG(AGCSTS);	// read general control/status register
		if (gcsts & GCSTS_RFIFO_EMPTY)
			break;				// no data to read

		ULONG numxfer;

		switch (item->nbytes)
			{					// read some data bytes

		case 1:
			*item->buffer = READ_PORT_UCHAR((PUCHAR) AFIFO);
			numxfer = 1;
			break;

		case 2:
			((PUSHORT) (item->buffer))[0] = READ_PORT_USHORT((PUSHORT) AFIFO);
			numxfer = 2;
			break;

		case 3:
			READ_PORT_BUFFER_UCHAR((PUCHAR) AFIFO, item->buffer, 3);
			numxfer = 3;
			break;

		default:
			((PULONG) (item->buffer))[0] = READ_PORT_ULONG(AFIFO);
			numxfer = 4;
			break;
			}					// read some data bytes

		item->buffer += numxfer;
		item->numxfer += numxfer;
		item->nbytes -= numxfer;
		}						// read available data

	if (!item->nbytes)
		{						// operation is complete
		PIRP Irp = item->Irp;
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = item->numxfer;
		return FALSE;			// to complete the item
		}						// operation is complete

	return TRUE;				// operation not complete yet
	}							// ReadDmaCallback

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ReadWriteDma(PDEVICE_EXTENSION pdx, PIRP Irp, BOOLEAN isread)
	{							// ReadWriteDma
	PMDL mdl = Irp->MdlAddress;
	if (!mdl)
		return STATUS_SUCCESS;	// no MDL means zero length request, so succeed it right now

	ULONG nbytes = MmGetMdlByteCount(mdl);
	if (nbytes & 3)
		return STATUS_INVALID_PARAMETER; // byte count must be even # dwords

	PDMA_WORKITEM item = (PDMA_WORKITEM) ExAllocatePool(NonPagedPool, sizeof(DMA_WORKITEM));
	if (!item)
		return STATUS_INSUFFICIENT_RESOURCES;

	item->buffer = (PUCHAR) MmGetSystemAddressForMdl(mdl);
	item->nbytes = nbytes;
	item->numxfer = 0;

	InitializeWorkItem(item, isread ? (WORKITEM_CALLBACK) ReadDmaCallback : (WORKITEM_CALLBACK) ReadDmaCallback, NULL, Irp);

	return QueueWorkItem(pdx, item);
	}							// ReadWriteDma

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ReadWriteMailbox(PDEVICE_EXTENSION pdx, PREADWRITE_MAILBOX_PARAMS p)
	{							// ReadWriteMailbox
	static PULONG imailbox[4] = {AIMB1, AIMB2, AIMB3, AIMB4};
	static PULONG omailbox[4] = {AOMB1, AOMB2, AOMB3, AOMB4};

	if (p->read)
		{						// read from mailbox
		PULONG mailbox = imailbox[p->mailbox - 1];
		switch (p->nbytes)
			{					// select on byte count

		case 1:
			p->buffer[0] = READ_PORT_UCHAR((PUCHAR) mailbox);
			break;

		case 2:
			((PUSHORT)(p->buffer))[0] = READ_PORT_USHORT((PUSHORT) mailbox);
			break;

		case 3:
			READ_PORT_BUFFER_UCHAR((PUCHAR) mailbox, p->buffer, 3);
			break;

		case 4:
			((PULONG)(p->buffer))[0] = READ_PORT_ULONG(mailbox);
			break;
			}					// select on byte count
		}						// read from mailbox

	else
		{						// write to mailbox
		PULONG mailbox = omailbox[p->mailbox - 1];
		switch (p->nbytes)
			{					// select on byte count

		case 1:
			WRITE_PORT_UCHAR((PUCHAR) mailbox, p->buffer[0]);
			break;

		case 2:
			WRITE_PORT_USHORT((PUSHORT) mailbox, ((PUSHORT)(p->buffer))[0]);
			break;

		case 3:
			WRITE_PORT_BUFFER_UCHAR((PUCHAR) mailbox, p->buffer, 3);
			break;

		case 4:
			WRITE_PORT_ULONG(mailbox, ((PULONG)(p->buffer))[0]);
			break;
			}					// select on byte count
		}						// write to mailbox

	return STATUS_SUCCESS;
	}							// ReadWriteMailbox

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS ResetDevice(PDEVICE_EXTENSION pdx)
	{							// ResetDevice

	// Reset the device by writing "1" bits to the reset flags in the general
	// control/status register. It's not necessary to reset any of these bits
	// to "0" afterwards. Other bits in GCSTS are R/O and unaffected by this

	WRITE_PORT_ULONG(AGCSTS, GCSTS_RESET);

	// Disable all add-on interrupts

	WRITE_PORT_ULONG(AINT, INT_INTERRUPT_MASK);

	return STATUS_SUCCESS;
	}							// ResetDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS WaitMailbox(PDEVICE_EXTENSION pdx, PMAILBOX_WAIT_PARAMS p, PIRP Irp)
	{							// WaitMailbox
	PMAILBOX_WORKITEM item = (PMAILBOX_WORKITEM) ExAllocatePool(NonPagedPool, sizeof(MAILBOX_WORKITEM));
	if (!item)
		return STATUS_INSUFFICIENT_RESOURCES;

	InitializeWorkItem(item, (WORKITEM_CALLBACK) WaitMailboxCallback, NULL, Irp);
	item->mask = p->mask;
	item->mbef = p->mbef;

	if (!WaitMailboxCallback(pdx, item, NULL))
		{						// no need to wait
		ExFreePool(item);
		return STATUS_SUCCESS;
		}						// no need to wait

	return QueueWorkItem(pdx, item);
	}							// WaitMailbox

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

BOOLEAN WaitMailboxCallback(PDEVICE_EXTENSION pdx, PMAILBOX_WORKITEM item, PVOID context)
	{							// WaitMailboxCallback
	ULONG mbef = READ_PORT_ULONG(AMBEF);
	mbef &= item->mask;
	if (mbef == item->mbef)
		{						// wait satisifed
		item->Irp->IoStatus.Status = STATUS_SUCCESS;
		item->Irp->IoStatus.Information = 0;
		return FALSE;			// stop polling loop
		}						// wait satisfied

	return TRUE;				// keep polling
	}							// WaitMailboxCallback

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

BOOLEAN WriteDmaCallback(PDEVICE_EXTENSION pdx, PDMA_WORKITEM item, PVOID context)
	{							// WriteDmaCallback
	while (item->nbytes)
		{						// write available data

		// See if there's room to write more data. Note that the S5933 always
		// moves data in 32-bit chunks through the FIFO, so finding the FIFO
		// non-full means there's room for at least 4 bytes.

		ULONG gcsts = READ_PORT_ULONG(AGCSTS);	// read general control/status register
		if (gcsts & GCSTS_WFIFO_FULL)
			break;				// no room for more data

		ULONG numxfer;

		switch (item->nbytes)
			{					// write some data bytes

		case 1:
			WRITE_PORT_UCHAR((PUCHAR) AFIFO, *item->buffer);
			numxfer = 1;
			break;

		case 2:
			WRITE_PORT_USHORT((PUSHORT) AFIFO, ((PUSHORT) (item->buffer))[0]);
			numxfer = 2;
			break;

		case 3:
			WRITE_PORT_BUFFER_UCHAR((PUCHAR) AFIFO, item->buffer, 3);
			numxfer = 3;
			break;

		default:
			WRITE_PORT_ULONG(AFIFO, ((PULONG) (item->buffer))[0]);
			numxfer = 4;
			break;
			}					// write some data bytes

		item->buffer += numxfer;
		item->numxfer += numxfer;
		item->nbytes -= numxfer;
		}						// write available data

	if (!item->nbytes)
		{						// operation is complete
		PIRP Irp = item->Irp;
		Irp->IoStatus.Status = STATUS_SUCCESS;
		Irp->IoStatus.Information = item->numxfer;
		return FALSE;			// to complete the item
		}						// operation is complete

	return TRUE;				// operation not complete yet
	}							// WriteDmaCallback
