// FILEIO98.CPP -- VxD interfaces for File I/O operations
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifdef _X86_

#if DBG
	#define DEBUG
#else
	#undef DEBUG
#endif

extern "C" {

#define WANTVXDWRAPS
#include <basedef.h>
#include <debug.h>
#include <vmm.h>
#include "ifsmgr.h"
#include <vxdwraps.h>
#include <string.h>

typedef struct _FILE_HANDLE {
	DWORD hfile;				// file system handle
	BOOL i21;					// TRUE if opened via INT 21 call
	DWORD pos;					// file position for IFSMgr R/W calls
	} FILE_HANDLE, *PFILE_HANDLE;

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

///////////////////////////////////////////////////////////////////////////////

#pragma warning(disable:4035)

DWORD SeekI21File(DWORD hfile, DWORD pos, int origin)
	{							// SeekI21File
	_asm mov eax, 4200h			; fcn 42: seek
	_asm mov al, byte ptr origin
	_asm mov ebx, hfile
	_asm mov edx, pos
	_asm mov ecx, edx
	_asm shr ecx, 16
	_asm push 21h

	VMMCall(Exec_VxD_Int)

	_asm movzx eax, ax
	_asm shl edx, 16
	_asm or eax, edx
	}							// SeekI21File

#pragma warning(default:4035)

///////////////////////////////////////////////////////////////////////////////

ULONG Win98OpenFile(PWORD filename, BYTE read, PFILE_HANDLE* phandle)
	{							// Win98OpenFile
	DWORD hfile;
	DWORD actiontaken;
	BOOL i21;

	// Convert name to OEM character set

	char name[MAX_PATH];
	name[UniToBCS((PBYTE) name, filename, wcslen(filename) * 2, sizeof(name)-2, BCS_OEM)] = 0;

	// Intepret SystemRoot if it's present as the first directory name in the path

	_strlwr(name);
	if (memcmp(name, "\\systemroot", 11) == 0)
		{						// path relative to system root
		char* windir = Get_Config_Directory();
		char newname[MAX_PATH];
		strcpy(newname, windir);
		newname[strlen(windir)-1] = 0;	// remove NULL at end of directory name
		strcat(newname, name + 11);
		strcpy(name, newname);
		}						// path relative to system root

	// Develop arguments to the open function

	WORD modeflags = read ? ACCESS_READONLY : ACCESS_WRITEONLY;
	WORD shareflags = read ? SHARE_DENYWRITE : SHARE_DENYREADWRITE;
	WORD attrib = 0;
	BYTE action = read ? ACTION_OPENEXISTING : ACTION_CREATEALWAYS;
	BYTE flags = 0;

	int code;

	if (VMM_GetSystemInitState() >= SYSSTATE_PREINITCOMPLETE)
		{						// call IFSMgr
		code = R0_OpenCreateFile(TRUE, modeflags | shareflags, attrib, action, flags, name, &hfile, &actiontaken);
		i21 = FALSE;
		}						// call IFSMgr
	else
		{						// use INT 21
		_asm
			{					// prepare for INT 21
			mov eax, 6C00h		; AX = function code (extended open/create)
			mov bx, modeflags	; BX = mode & share flags
			or  bx, shareflags
			mov cx, attrib;		; CX = attributes when creating file
			mov dl, action		; DL = action code
			xor dh, dh			; DH = flags (must be zero)
			lea esi, name		; ESI -> name of file to open
			push 21h			; push 21h as arg for Exec_Vxd_Int
			}					// prepare for INT 21
	
		VMMCall(Exec_VxD_Int);
		
		_asm
			{					// test return code
			movzx eax, ax
			jc    error			; skip if error
			mov   hfile, eax
			xor	  eax, eax		; STATUS_SUCCESS
error:
			mov   code, eax		; save error code
			}					// test return code

		i21 = TRUE;
		}						// use INT 21

	if (code != 0)
		return 0xC0000001;		// STATUS_UNSUCCESSFUL
		
	PFILE_HANDLE hp = (PFILE_HANDLE) _HeapAllocate(sizeof(FILE_HANDLE), 0);
	if (!hp)
		return 0xC000009A;		// STATUS_INSUFFICIENT_RESOURCES

	hp->hfile = hfile;
	hp->i21 = i21;
	hp->pos = 0;
	*phandle = hp;
	return 0;					// STATUS_SUCCESS
	}							// Win98OpenFile

///////////////////////////////////////////////////////////////////////////////

ULONG Win98CloseFile(PFILE_HANDLE handle)
	{							// Win98CloseFile
	if (handle->i21)
		{						// close INT 21 handle
		_asm mov eax, 3E00h		; fcn 3E: close file
		_asm mov esi, handle
		_asm mov ebx, [esi]FILE_HANDLE.hfile
		_asm push 21h
		VMMCall(Exec_VxD_Int)
		}						// close INT 21 handle
	else
		R0_CloseFile(handle->hfile);

	_HeapFree(handle, 0);

	return 0;					// STATUS_SUCCESS
	}							// Win98CloseFile

///////////////////////////////////////////////////////////////////////////////

ULONG Win98GetFileSize(PFILE_HANDLE handle)
	{							// Win98GetFileSize
	DWORD eof;

	if (handle->i21)
		{						// get size using INT 21 handle
		DWORD curpos = SeekI21File(handle->hfile, 0, SEEK_CUR);
		eof = SeekI21File(handle->hfile, 0, SEEK_END);
		SeekI21File(handle->hfile, curpos, SEEK_SET);
		}						// get size using INT 21 handle
	else
		{						// use IFSMgr
		if (R0_GetFileSize(handle->hfile, &eof) != 0)
			eof = 0xFFFFFFFF;
		}						// use IFSMgr

	return eof;
	}							// Win98GetFileSize

///////////////////////////////////////////////////////////////////////////////

ULONG Win98ReadFile(PFILE_HANDLE handle, PBYTE buffer, ULONG nbytes, PULONG pnumread)
	{							// Win98ReadFile
	int code;
	DWORD numread;

	if (handle->i21)
		{						// read via INT 21 handle
		_asm mov eax, 3F00h		; fcn 3F: read file
		_asm mov esi, handle
		_asm mov ebx, [esi]FILE_HANDLE.hfile
		_asm mov ecx, nbytes
		_asm mov edx, buffer
		_asm push 21h
		VMMCall(Exec_VxD_Int)
		_asm mov numread, eax	; assume success
		_asm sbb eax, eax		; EAX = 0 if success, -1 if error
		_asm mov code, eax
		}						// read via INT 21 handle
	else
		code = R0_ReadFile(TRUE, handle->hfile, nbytes, handle->pos, buffer, &numread);

	if (code == 0)
		{						// success
		*pnumread = numread;
		handle->pos += numread;
		return 0;				// STATUS_SUCCESS
		}						// success

	return 0xC0000001;			// STATUS_UNSUCCESSFUL
	}							// Win98ReadFile

///////////////////////////////////////////////////////////////////////////////

ULONG Win98WriteFile(PFILE_HANDLE handle, PBYTE buffer, ULONG nbytes, PULONG pnumwritten)
	{							// Win98WriteFile
	int code;
	DWORD numwritten;

	if (handle->i21)
		{						// write via INT 21 handle
		_asm mov eax, 4000h		; fcn 40: write file
		_asm mov esi, handle
		_asm mov ebx, [esi]FILE_HANDLE.hfile
		_asm mov ecx, nbytes
		_asm mov edx, buffer
		_asm push 21h
		VMMCall(Exec_VxD_Int)
		_asm mov numwritten, eax	; assume success
		_asm sbb eax, eax		; EAX = 0 if success, -1 if error
		_asm mov code, eax
		}						// write via INT 21 handle
	else
		code = R0_WriteFile(TRUE, handle->hfile, nbytes, handle->pos, buffer, &numwritten);

	if (code == 0)
		{						// success
		*pnumwritten = numwritten;
		handle->pos += numwritten;
		return 0;				// STATUS_SUCCESS
		}						// success

	return 0xC0000001;			// STATUS_UNSUCCESSFUL
	}							// Win98WriteFile

} // extern "C"

#endif // _X86_
