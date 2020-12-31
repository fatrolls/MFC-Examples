// myvxd.cpp -- VxD for monitoring IFS API calls
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#include "myvxd.h"

void ReturnBlock(PMONINFO mip);
PMONINFO GetBlock();
int HookProc(pIFSFunc fsdproc, int fcn, int drive, int flags, int cp, pioreq pir);

///////////////////////////////////////////////////////////////////////////////
// Overrides for library new and delete operators.

void* ::operator new(unsigned int size)
{
	return _HeapAllocate(size, 0);
}

void ::operator delete(void* p)
{
	if (p)
		_HeapFree(p, 0);
}

///////////////////////////////////////////////////////////////////////////////
// Static data

#pragma VxD_LOCKED_DATA_SEG

PTCB thread = NULL;				// handle of ring-3 thread
DWORD userproc = NULL;			// user procedure to call
VMMLIST list;					// list handle
ppIFSFileHookFunc prevhook;		// previous API hook fcn address

#pragma VxD_PAGEABLE_DATA_SEG

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_INIT_CODE_SEG

SYSCTL BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	list = List_Create(LF_ASYNC | LF_ALLOC_ERROR, sizeof(MONINFO));
	if (!list)
		return FALSE;
	prevhook = IFSMgr_InstallFileSystemApiHook(HookProc);
	if (!prevhook)
		{						// couldn't setup file system hook
		List_Destroy(list);
		return FALSE;
		}						// couldn't setup file system hook
	return TRUE;
	}							// OnSysDynamicDeviceInit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

SYSCTL BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	userproc = NULL;
	IFSMgr_RemoveFileSystemApiHook(HookProc);
	if (list)
		List_Destroy(list);
	return TRUE;
	}							// OnSysDynamicDeviceExit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

SYSCTL void OnTerminateThread(PTCB ht)
	{							// OnTerminateThread
	if (ht == thread)
		thread = NULL, userproc = NULL;
	}							// OnTerminateThread

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

SYSCTL DWORD OnDeviceIoControl(PDIOCPARAMETERS p)
	{							// OnDeviceIoControl
	switch (p->dwIoControlCode)
		{						// select on IOCTL code

	case 0:						// VWIN32 pinging us during CreateFile
	case -1:					// CloseHandle
		break;
	
	case REQMON_SETMONITORADDRESS:
		{						// SETMONITORADDRESS
		if (!p->lpvInBuffer || p->cbInBuffer < 4)
			return ERROR_INVALID_PARAMETER;
		thread = Get_Cur_Thread_Handle();
		userproc = *(PDWORD) p->lpvInBuffer;
		break;
		}						// SETMONITORADDRESS
	
	case REQMON_RETURNBLOCK:
		{						// RETURNBLOCK
		PMONINFO mip;
		if (!p->lpvInBuffer || p->cbInBuffer < 4)
			return ERROR_INVALID_PARAMETER;
		mip = *(PMONINFO*) p->lpvInBuffer;
		ASSERT(mip);
		ReturnBlock(mip);
		break;
		}						// RETURNBLOCK

	default:
		return ERROR_INVALID_FUNCTION;

		}						// select on IOCTL code
	
	return 0;
	}							// OnDeviceIoControl

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG

void ReturnBlock(PMONINFO mip)
	{							// ReturnBlock
	_asm pushfd
	_asm cli
	List_Deallocate(list, (VMMLISTNODE) mip);
	_asm popfd
	}							// ReturnBlock

PMONINFO GetBlock()
	{							// GetBlock
	PMONINFO mip;

	_asm pushfd
	_asm cli
	mip = (PMONINFO) List_Allocate(list);
	_asm popfd

	return mip;
	}							// GetBlock

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG

int HookProc(pIFSFunc fsdproc, int fcn, int drive, int flags, int cp, pioreq pir)
	{							// HookProc
	PMONINFO p;
	if (userproc && (p = GetBlock()))
		{						// record info
		p->fcn = fcn;
		p->drive = drive;
		p->flags = flags;
		p->cp = cp;
		p->req = *pir;

		static BYTE haspath[] = {
			0, 0, 0, 0,						// READ-FCNNEXT
			0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// SEEK-FCNCLOSE
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			1,								// CONNECT
			1,								// DELETE
			1,								// DIR
			1,								// FILEATTRIB
			0, 0,							// FLUSH, GETDISKINFO
			1,								// OPEN
			1,								// RENAME
			1,								// SEARCH
			0, 0, 0, 0, 0,					// QUERY - GETDISKPARMS
			1,								// FINDOPEN
			0};								// DASDIO

		if (fcn < arraysize(haspath) && haspath[fcn] && pir->ir_ppath != (ParsedPath*) 0xFFFFFBBB)
			{					// convert 1st pathname
			int len = UniToBCSPath(p->path1, pir->ir_ppath->pp_elements, sizeof(p->path1)-1, BCS_OEM);
			if (len >= 0)
				p->path1[len] = 0;
			}					// convert 1st pathname
		else
			p->path1[0] = 0;

		if (fcn == IFSFN_RENAME && pir->ir_ppath2 != (ParsedPath*) 0xFFFFFBBB)
			{					// convert 2d pathname
			int len = UniToBCSPath(p->path2, pir->ir_ppath2->pp_elements, sizeof(p->path2)-1, BCS_OEM);
			if (len >= 0)
				p->path2[len] = 0;
			}					// convert 2d pathname
		else
			p->path2[0] = 0;

		if (!_VWIN32_QueueUserApc(userproc, (DWORD) p, thread))
			ReturnBlock(p);
		}						// record info
	return (**prevhook)(fsdproc, fcn, drive, flags, cp, pir);
	}							// HookProc
