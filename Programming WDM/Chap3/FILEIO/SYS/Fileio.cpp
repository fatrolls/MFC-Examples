// FileIO.cpp -- Portable routines for file reading and writing
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"

#ifdef _X86_

extern "C" NTSTATUS __cdecl Win98OpenFile(PWCHAR filename, BOOLEAN read, PHANDLE phandle);
extern "C" NTSTATUS __cdecl Win98CloseFile(HANDLE handle);
extern "C" ULONG __cdecl Win98GetFileSize(HANDLE handle);
extern "C" NTSTATUS __cdecl Win98ReadFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread);
extern "C" NTSTATUS __cdecl Win98WriteFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread);

NTSTATUS Win2KOpenFile(PWCHAR filename, BOOLEAN read, PHANDLE phandle);
NTSTATUS Win2KCloseFile(HANDLE handle);
unsigned __int64 Win2KGetFileSize(HANDLE handle);
NTSTATUS Win2KReadFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread);
NTSTATUS Win2KWriteFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread);

///////////////////////////////////////////////////////////////////////////////

NTSTATUS OpenFile(PWCHAR filename, BOOLEAN read, PHANDLE phandle)
	{							// OpenFile
	if (win98)
		return Win98OpenFile(filename, read, phandle);
	else
		return Win2KOpenFile(filename, read, phandle);
	}							// OpenFile

///////////////////////////////////////////////////////////////////////////////

NTSTATUS CloseFile(HANDLE handle)
	{							// CloseFile
	if (win98)
		return Win98CloseFile(handle);
	else
		return Win2KCloseFile(handle);
	}							// CloseFile

///////////////////////////////////////////////////////////////////////////////

unsigned __int64 GetFileSize(HANDLE handle)
	{							// GetFileSize
	if (win98)
		return Win98GetFileSize(handle);
	else
		return Win2KGetFileSize(handle);
	}							// GetFileSize

///////////////////////////////////////////////////////////////////////////////

NTSTATUS ReadFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread)
	{							// ReadFile
	if (win98)
		return Win98ReadFile(handle, buffer, nbytes, pnumread);
	else
		return Win2KReadFile(handle, buffer, nbytes, pnumread);
	}							// ReadFile

///////////////////////////////////////////////////////////////////////////////

NTSTATUS WriteFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumwritten)
	{							// WriteFile
	if (win98)
		return Win98WriteFile(handle, buffer, nbytes, pnumwritten);
	else
		return Win2KWriteFile(handle, buffer, nbytes, pnumwritten);
	}							// WriteFile

///////////////////////////////////////////////////////////////////////////////

#else // not _X86_
	#define Win2KOpenFile OpenFile
	#define Win2KCloseFile CloseFile
	#define Win2KGetFileSize GetFileSize
	#define Win2KReadFile ReadFile
	#define Win2KWriteFile WriteFile
#endif // not _X86_

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

NTSTATUS Win2KOpenFile(PWCHAR filename, BOOLEAN read, PHANDLE phandle)
	{							// Win2KOpenFile
	NTSTATUS status;
	OBJECT_ATTRIBUTES oa;
	UNICODE_STRING usname;
	HANDLE hfile;
	IO_STATUS_BLOCK iostatus;

	// Initialize the object attributes structure we'll use to open the file.
	// The OBJ_KERNEL_HANDLE flag is new and prevents user-mode code from closing
	// this handle and redirecting it to some other resource.

	RtlInitUnicodeString(&usname, filename);
	InitializeObjectAttributes(&oa, &usname, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	if (read)
		status = ZwCreateFile(&hfile, GENERIC_READ, &oa, &iostatus, NULL,
			0, FILE_SHARE_READ, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
	else
		status = ZwCreateFile(&hfile, GENERIC_WRITE, &oa, &iostatus, NULL,
			FILE_ATTRIBUTE_NORMAL, 0, FILE_OVERWRITE_IF, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);

	if (NT_SUCCESS(status))
		*phandle = hfile;
	return status;
	}							// Win2KOpenFile

///////////////////////////////////////////////////////////////////////////////

NTSTATUS Win2KCloseFile(HANDLE handle)
	{							// Win2KCloseFile
	return ZwClose(handle);
	}							// Win2KCloseFile

///////////////////////////////////////////////////////////////////////////////

unsigned __int64 Win2KGetFileSize(HANDLE handle)
	{							// Win2KGetFileSize
	NTSTATUS status;
	IO_STATUS_BLOCK iostatus;
	FILE_STANDARD_INFORMATION fi;

	status = ZwQueryInformationFile(handle, &iostatus, (PVOID) &fi, sizeof(fi), FileStandardInformation);
	if (!NT_SUCCESS(status))
		return 0;

	return fi.EndOfFile.QuadPart;
	}							// Win2KGetFileSize

///////////////////////////////////////////////////////////////////////////////

NTSTATUS Win2KReadFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumread)
	{							// Win2KReadFile
	IO_STATUS_BLOCK iostatus;
	ZwReadFile(handle, NULL, NULL, NULL, &iostatus, buffer, nbytes, NULL, NULL);
	if (NT_SUCCESS(iostatus.Status))
		*pnumread = iostatus.Information;
	return iostatus.Status;
	}							// Win2KReadFile

///////////////////////////////////////////////////////////////////////////////

NTSTATUS Win2KWriteFile(HANDLE handle, PVOID buffer, ULONG nbytes, PULONG pnumwritten)
	{							// Win2KWriteFile
	IO_STATUS_BLOCK iostatus;
	ZwWriteFile(handle, NULL, NULL, NULL, &iostatus, buffer, nbytes, NULL, NULL);
	if (NT_SUCCESS(iostatus.Status))
		*pnumwritten = iostatus.Information;
	return iostatus.Status;
	}							// Win2KWriteFile

