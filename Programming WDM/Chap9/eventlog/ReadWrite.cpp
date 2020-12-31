// Read/Write request processors for eventlog driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "eventlog.h"

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID LogEvent(NTSTATUS code, PDEVICE_OBJECT fdo)
	{							// LogEvent
	if (win98)
		return;					// Win98 doesn't support event logging, so don't bother

	PWSTR myname = L"EventLog";

	ULONG packetlen = (wcslen(myname) + 1) * sizeof(WCHAR) + sizeof(IO_ERROR_LOG_PACKET) + 4;
	if (packetlen > ERROR_LOG_MAXIMUM_SIZE)
		return;					// packet will be too big

	PIO_ERROR_LOG_PACKET p = (PIO_ERROR_LOG_PACKET) IoAllocateErrorLogEntry(fdo, (UCHAR) packetlen);
	if (!p)
		return;

	memset(p, 0, sizeof(IO_ERROR_LOG_PACKET));
	p->MajorFunctionCode = IRP_MJ_PNP;
	p->ErrorCode = code;
	p->DumpDataSize = 4;
	p->DumpData[0] = 0x2A2A2A2A;

	p->StringOffset = sizeof(IO_ERROR_LOG_PACKET) + p->DumpDataSize - sizeof(ULONG);
	p->NumberOfStrings = 1;
	wcscpy((PWSTR) ((PUCHAR) p + p->StringOffset), myname);

	IoWriteErrorLogEntry(p);
	}							// LogEvent

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
	{							// StartDevice
	LogEvent(EVENTLOG_MSG_TEST, fdo);
	return STATUS_SUCCESS;
	}							// StartDevice

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
	{							// StopDevice
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	}							// StopDevice
