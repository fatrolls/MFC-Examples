// WDMSTUB.CPP -- Stubs for missing Win2K WDM service functions
// Copyright (C) 1998 by Walter Oney
// All rights reserved

#include "stdvxd.h"
#include "NonStubs.h"

CCHAR cKeNumberProcessors = 1;
BOOLEAN bKdDebuggerEnabled = 0;

///////////////////////////////////////////////////////////////////////////////
// From NTDDK.H (missing from beta-3 DDK?)

NTKERNELAPI PIO_WORKITEM NTAPI IoAllocateWorkItem(PDEVICE_OBJECT DeviceObject);
NTKERNELAPI VOID NTAPI IoFreeWorkItem(PIO_WORKITEM item);
NTKERNELAPI VOID NTAPI IoQueueWorkItem(PIO_WORKITEM pIOWorkItem, PIO_WORKITEM_ROUTINE Routine, WORK_QUEUE_TYPE QueueType, PVOID Context);

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG

// Names of functions stubbed by this VxD. This isn't the array we actually pass
// to PELDR -- it's the array we use when we construct a list of functions
// that aren't already implemented by NTKERN. The names must be in resident storage
// because we don't copy them when we build the export table.

static char* names[] = {
	"PoRegisterSystemState",
	"PoSetSystemState",
	"PoUnregisterSystemState",
	"IoReportTargetDeviceChangeAsynchronous",
	"ExSystemTimeToLocalTime",
	"ExLocalTimeToSystemTime",
	"IoCreateNotificationEvent",
	"IoCreateSynchronizationEvent",
	"IoAllocateWorkItem",
	"IoFreeWorkItem",
	"IoQueueWorkItem",
	"PsGetVersion",
	"RtlUshortByteSwap",
	"RtlUlongByteSwap",
	"RtlUlonglongByteSwap",
	"RtlInt64ToUnicodeString",
	"KeEnterCritcalRegion",
	"KeLeaveCriticalRegion",
	"KeSetTargetProcessorDpc",
	"KeNumberProcessors",
	"KdDebuggerEnabled",
	"IoReuseIrp",
	};

static char* remlocknames[] = {
	"IoAcquireRemoveLockEx",
	"IoReleaseRemoveLockEx",
	"IoReleaseRemoveLockAndWaitEx",
	"IoInitializeRemoveLockEx",
	};

// Addresses of stub functions (must line up with names array)

static PFN addresses[] = {
	(PFN) PoRegisterSystemState,
	(PFN) PoSetSystemState,
	(PFN) PoUnregisterSystemState,
	(PFN) IoReportTargetDeviceChangeAsynchronous,
	(PFN) ExSystemTimeToLocalTime,
	(PFN) ExLocalTimeToSystemTime,
	(PFN) IoCreateNotificationEvent,
	(PFN) IoCreateSynchronizationEvent,
	(PFN) IoAllocateWorkItem,
	(PFN) IoFreeWorkItem,
	(PFN) IoQueueWorkItem,
	(PFN) PsGetVersion,
	(PFN) RtlUshortByteSwap,
	(PFN) RtlUlongByteSwap,
	(PFN) RtlUlonglongByteSwap,
	(PFN) RtlInt64ToUnicodeString,
	(PFN) KeEnterCriticalRegion,
	(PFN) KeLeaveCriticalRegion,
	(PFN) KeSetTargetProcessorDpc,
	(PFN) &cKeNumberProcessors,
	(PFN) &bKdDebuggerEnabled,
	(PFN) IoReuseIrp,
	};

static PFN remlockaddresses[] = {
	(PFN) IoAcquireRemoveLockEx,
	(PFN) IoReleaseRemoveLockEx,
	(PFN) IoReleaseRemoveLockAndWaitEx,
	(PFN) IoInitializeRemoveLockEx,
	};

__int64 GetZoneBias();
DWORD buildnum;

HPEEXPORTTABLE hExportTable = 0;

///////////////////////////////////////////////////////////////////////////////
// Declarations of kernel-mode routines must be compiled without a __declspec(dllimport)
// directive, which precludes using WDMVXD.LIB to resolve references within this
// source module. Hence, we define our own implementation of these functions:

#pragma warning(disable:4035)

NTKERNELAPI KIRQL NTAPI KeGetCurrentIrql()
	{
	VMMCall(ObsoleteKeGetCurrentIrql);
	}

#pragma warning(default:4035)

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_INIT_CODE_SEG

#pragma warning(disable:4035)

DWORD Convert_Decimal_String(char*& s)
	{
	_asm mov esi, s
	_asm mov edx, [esi]
	VMMCall(Convert_Decimal_String)
	_asm mov [esi], edx
	}

BOOLEAN Test_Debug_Installed()
	{
	VMMCall(Test_Debug_Installed)
	_asm setnz al
	}

#pragma warning(default:4035)

SYSCTL BOOL __cdecl OnDeviceInit(DWORD dwRefData)
	{							// OnDeviceInit

	// Construct the name, ordinal, and address tables for functions we're going
	// to stub. In various releases of Windows 98 and Millenium, some or all of
	// these functions will be supported by the operating system, and we don't
	// want to preempt the standard implementation.

	char** stubnames = (char**) _HeapAllocate(sizeof(names) + sizeof(remlocknames), HEAPZEROINIT); // largest we might ever need
	if (!stubnames)
		return FALSE;

	PFN* stubaddresses = (PFN*) _HeapAllocate(sizeof(addresses) + sizeof(remlockaddresses), HEAPZEROINIT);
	if (!stubaddresses)
		{
		_HeapFree(stubnames, 0);
		return FALSE;
		}

	WORD* ordinals = (WORD*) _HeapAllocate((arraysize(names) + arraysize(remlocknames)) * sizeof(WORD), HEAPZEROINIT);
	if (!ordinals)
		{
		_HeapFree(stubaddresses, 0);
		_HeapFree(stubnames, 0);
		return FALSE;
		}

	int i, istub;
	for (i = 0, istub = 0; i < arraysize(names); ++i)
		{						// for each possible stub
		if (_PELDR_GetProcAddress((HPEMODULE) "ntoskrnl.exe", names[i], NULL) == 0)
			{					// stub this function
			Debug_Printf("WDMSTUB - Stubbing %s\n", names[i]);
			stubnames[istub] = names[i];
			ordinals[istub] = istub;
			stubaddresses[istub] = addresses[i];
			++istub;
			}					// stub this function
		else
			Debug_Printf("WDMSTUB - %s already implemented - not stubbing it\n", names[i]);
		}						// for each possible stub

	// We have a special problem with the remove lock functions, in that Win98SE leaves out
	// just IoRemoveLockAndWaitEx. We'll stub all of them if we find this function missing.

	if (_PELDR_GetProcAddress((HPEMODULE) "ntoskrnl.exe", "IoReleaseRemoveLockAndWaitEx", NULL) == 0)
		{						// stub remove lock functions
		Debug_Printf("WDMSTUB - Stubbing all remove lock functions\n");
		for (i = 0; i < arraysize(remlocknames); ++i)
			{					// for each remove lock function
			stubnames[istub] = remlocknames[i];
			ordinals[istub] = istub;
			stubaddresses[istub] = remlockaddresses[i];
			++istub;
			}					// for each remove lock function
		}						// stub remove lock functions
	else
		Debug_Printf("WDMBSTUB - Not stubbing remove lock functions\n");

	// Create an export table to provide for these functions

	if (_PELDR_AddExportTable(&hExportTable, "ntoskrnl.exe", istub,
		istub, 0, (PVOID*) stubnames, ordinals, stubaddresses, NULL) != 0)
		{						// can't define exports
		Debug_Printf("WDMSTUB -- Unable to define export table\n");
		_HeapFree(ordinals, 0);
		_HeapFree(stubaddresses, 0);
		_HeapFree(stubnames, 0);
		return FALSE;
		}						// can't define exports

	// See if debugger running

	bKdDebuggerEnabled = Test_Debug_Installed();

	// Get build number from HKLM\Software\Microsoft\Windows\CurrentVersion[VersionNumber]

	VMMHKEY hkey;
	if (_RegOpenKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_SETUP, &hkey) == 0)
		{						// get value
		char value[64];
		DWORD size = sizeof(value);
		if (_RegQueryValueEx(hkey, "VersionNumber", NULL, NULL, (PBYTE) value, &size) == 0)
			{					// parse value
			char* p = value;
			Convert_Decimal_String(p);	// major version number
			if (*p == '.')
				++p;
			Convert_Decimal_String(p);	// minor version number
			if (*p == '.')
				++p;
			buildnum = Convert_Decimal_String(p);	// build number
			}					// parse value
		_RegCloseKey(hkey);
		}						// get value

	return TRUE;
	}							// OnDeviceInit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG

PVOID PoRegisterSystemState(PVOID hstate, ULONG flags)
	{							// PoRegisterSystemState
	ASSERT(KeGetCurrentIrql() < DISPATCH_LEVEL);
	Debug_Printf("PoRegisterSystemState(%8.8lX, %8.8lX)\n", hstate, flags);
	return NULL;
	}							// PoRegisterSystemState

VOID PoSetSystemState(ULONG flags)
	{							// PoSetSystemState
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
	Debug_Printf("PoSetSystemState(%8.8lX)\n", flags);
	}							// PoSetSystemState

VOID PoUnregisterSystemState(PVOID hstate)
	{							// PoUnregisterSystemState
	ASSERT(KeGetCurrentIrql() < DISPATCH_LEVEL);
	Debug_Printf("PoUnregisterSystemState(%8.8lX)\n", hstate);
	}							// PoUnregisterSystemState

NTSTATUS IoReportTargetDeviceChangeAsynchronous(PDEVICE_OBJECT pdo, PVOID NfyStruct, PDEVICE_CHANGE_COMPLETE_CALLBACK Callback, PVOID Context)
	{							// IoReportTargetDeviceChangeAsynchronous
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
	Debug_Printf("IoReportTargetDeviceChangeAsynchronous(%8.8lX)\n", pdo);
	return STATUS_NOT_IMPLEMENTED;
	}							// IoReportTargetDeviceChangeAsynchronous

VOID ExSystemTimeToLocalTime(PLARGE_INTEGER systime, PLARGE_INTEGER localtime)
	{							// ExSystemTimeToLocalTime
	localtime->QuadPart = systime->QuadPart - GetZoneBias();
	}							// ExSystemTimeToLocalTime

VOID ExLocalTimeToSystemTime(PLARGE_INTEGER localtime, PLARGE_INTEGER systime)
	{							// ExLocalTimeToSystemTime
	systime->QuadPart = localtime->QuadPart + GetZoneBias();
	}							// ExLocalTimeToSystemTime

PKEVENT IoCreateNotificationEvent(PUNICODE_STRING EventName, PHANDLE EventHandle)
	{							// IoCreateNotificationEvent
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	Debug_Printf("IoCreateNotificationEvent %ws\n", EventName->Buffer);
	return NULL;
	}							// IoCreateNotificationEvent

PKEVENT IoCreateSynchronizationEvent(PUNICODE_STRING EventName, PHANDLE EventHandle)
	{							// IoCreateSynchronizationEvent
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	Debug_Printf("IoCreateSynchronizationEvent %ws\n", EventName->Buffer);
	return NULL;
	}							// IoCreateSynchronizationEvent

PIO_WORKITEM IoAllocateWorkItem(PDEVICE_OBJECT DeviceObject)
	{							// IoAllocateWorkItem
	return AllocateWorkItem(DeviceObject);
	}							// IoAllocateWorkItem

VOID IoFreeWorkItem(PIO_WORKITEM item)
	{							// IoFreeWorkItem
	FreeWorkItem(item);
	}							// IoFreeWorkItem

VOID IoQueueWorkItem(PIO_WORKITEM item, PIO_WORKITEM_ROUTINE Routine, WORK_QUEUE_TYPE QueueType, PVOID Context)
	{							// IoQueueWorkItem
	QueueWorkItem(item, Routine, QueueType, Context);
	}							// IoQueueWorkItem

BOOLEAN PsGetVersion(PULONG MajorVersion, PULONG MinorVersion, PULONG BuildNumber, PUNICODE_STRING spnum)
	{							// PsGetVersion
	#undef Get_VMM_Version
	USHORT version;
	ULONG dbgver;
	VMMCall(Get_VMM_Version);
	_asm mov version, ax
	_asm mov dbgver, ecx

	if (MajorVersion)
		*MajorVersion = version >> 8;
	if (MinorVersion)
		*MinorVersion = version & 255;
	if (BuildNumber)
		*BuildNumber = buildnum;
	if (spnum)
		spnum->Length = 0;

	return dbgver != 0;
	}							// PsGetVersion

NTSTATUS IoAcquireRemoveLockEx(PIO_REMOVE_LOCK p, PVOID tag, PCSTR file, ULONG line, ULONG size)
	{							// IoAcquireRemoveLockEx
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
	return AcquireRemoveLock(p, tag, file, line, size);
	}							// IoAcquireRemoveLockEx

VOID IoReleaseRemoveLockEx(PIO_REMOVE_LOCK p, PVOID tag, ULONG size)
	{							// IoReleaseRemoveLockEx
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);
	ReleaseRemoveLock(p, tag, size);
	}							// IoReleaseRemoveLockEx

VOID IoReleaseRemoveLockAndWaitEx(PIO_REMOVE_LOCK p, PVOID tag, ULONG size)
	{							// IoReleaseRemoveLockAndWaitEx
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	ReleaseRemoveLockAndWait(p, tag, size);
	}							// IoReleaseRemoveLockAndWaitEx

VOID IoInitializeRemoveLockEx(PIO_REMOVE_LOCK p, ULONG tag, ULONG maxminutes, ULONG hwm, ULONG size)
	{							// IoInitializeRemoveLockEx
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	InitializeRemoveLock(p, tag, maxminutes, hwm, size);
	}							// IoInitializeRemoveLockEx

#pragma warning(disable:4035)

USHORT FASTCALL RtlUshortByteSwap(USHORT source)
	{							// RtlUshortByteSwap
	_asm movzx eax, cx
	_asm xchg ah, al
	}							// RtlUshortByteSwap

ULONG FASTCALL RtlUlongByteSwap(ULONG source)
	{							// RtlUlongByteSwap
	_asm mov eax, ecx
	_asm bswap eax
	}							// RtlUlongByteSwap

ULONGLONG FASTCALL RtlUlonglongByteSwap(ULONGLONG source)
	{							// RtlUlonglongByteSwap
	_asm mov eax, ecx
	_asm xchg eax, edx
	_asm bswap eax
	_asm bswap edx
	}							// RtlUlonglongByteSwap

#pragma warning(default:4035)

NTSTATUS RtlInt64ToUnicodeString(ULONGLONG value, ULONG base, PUNICODE_STRING string)
	{							// RtlInt64ToUnicodeString
	return STATUS_NOT_IMPLEMENTED;
	}							// RtlInt64ToUnicodeString

VOID KeEnterCriticalRegion()
	{							// KeEnterCriticalRegion
	ASSERT(KeGetCurrentIrql() == PASSIVE_LEVEL);
	KfRaiseIrql(APC_LEVEL);
	}							// KeEnterCriticalRegion

VOID KeLeaveCriticalRegion()
	{							// KeLeaveCriticalRegion
	ASSERT(KeGetCurrentIrql() == APC_LEVEL);
	KfLowerIrql(PASSIVE_LEVEL);
	}							// KeLeaveCriticalRegion

VOID KeSetTargetProcessorDpc(PRKDPC dpc, CCHAR number)
	{							// KeSetTargetProcessorDpc
	}							// KeSetTargetProcessorDpc

VOID KeSetImportanceDpc(PRKDPC dpc, KDPC_IMPORTANCE importance)
	{							// KeSetImportanceDpc
	}							// KeSetImportanceDpc

VOID IoReuseIrp(PIRP Irp, NTSTATUS status)
	{							// IoReuseIrp
	ReuseIrp(Irp, status);
	}							// IoReuseIrp

///////////////////////////////////////////////////////////////////////////////

__int64 GetZoneBias()
	{							// GetZoneBias
	DWORD hkey;
	if (_RegOpenKey(HKEY_LOCAL_MACHINE, REGSTR_PATH_TIMEZONE, &hkey) != 0)
		return 0;

	__int64 bias;
	DWORD actbias;
	DWORD size = sizeof(actbias);

	if (_RegQueryValueEx(hkey, REGSTR_VAL_TZACTBIAS, NULL, NULL, &actbias, &size) == 0)
		{						// compute 100-ns bias
		actbias *= 3600;
		_asm mov eax, actbias
		_asm mov ecx, 10000000
		_asm mul ecx
		_asm mov dword ptr bias, eax
		_asm mov dword ptr bias+4, edx

		}						// compute 100-ns bias
	else
		bias = 0;

	_RegCloseKey(hkey);
	return bias;
	}							// GetZoneBias

///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:4035)

LONG __stdcall Get_System_Time()
	{							// Get_System_Time
	VMMCall(Get_System_Time)
	}							// Get_System_Time
