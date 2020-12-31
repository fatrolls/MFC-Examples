// DriverEntry.cpp - Main program for SEHTEST sample driver
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"

#define DRIVERNAME "SEHTEST"

///////////////////////////////////////////////////////////////////////////////

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
	{							// DriverEntry
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	PVOID p = (PVOID) 1;

	__try
		{
		KdPrint((DRIVERNAME " - About to generate exception\n"));
		ProbeForWrite(p, 4, 4);
		KdPrint((DRIVERNAME " - You shouldn't see this message\n"));
		}
	__except(EXCEPTION_EXECUTE_HANDLER)
		{
		KdPrint((DRIVERNAME " - Exception was caught\n"));
		}

	KdPrint((DRIVERNAME " - Program kept control after exception\n"));

	__try
		{
		return STATUS_UNSUCCESSFUL;
		}
	__finally
		{
		KdPrint((DRIVERNAME " - Failing DriverEntry; cleanup handler got control first\n"));
		}

	KdPrint((DRIVERNAME " - You shouldn't see this message\n"));

	return STATUS_SUCCESS;		// never reached
	}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#if DBG && defined(_X86_)
#pragma LOCKEDCODE

extern "C" void __declspec(naked) __cdecl _chkesp()
	{
	_asm je okay
	ASSERT(!DRIVERNAME " - Stack pointer mismatch!");
okay:
	_asm ret
	}

#endif // DBG
