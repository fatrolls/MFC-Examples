// FileSystem.cpp -- Implementation of CFileSystem
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#define NULL 0
class CFileSystem;
#define rh_t CFileSystem*

extern "C" {
#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>
#include <winerror.h>
#include "iosdcls.h"
#include "ifsmgr.h"
	} // extern "C"

#pragma hdrstop

#include "FileSystem.h"

///////////////////////////////////////////////////////////////////////////////

CFileSystem* (*CFileSystem::CreateNewFcn)() = NULL;
int CFileSystem::ProviderId = 0;

CFileSystem::CFileSystem()
	{							// CFileSystem::CFileSystem
	}							// CFileSystem::CFileSystem

CFileSystem::~CFileSystem()
	{							// CFileSystem::~CFileSystem
	}							// CFileSystem::~CFileSystem

BOOL CFileSystem::Register(CFileSystem* (*createnew)())
	{							// CFileSystem::Register
	CreateNewFcn = createnew;
	return TRUE;
	}							// CFileSystem::Register

///////////////////////////////////////////////////////////////////////////////

#undef vt
#define vt(f) int CFileSystem::f##Thunk(pioreq pir) {return pir->ir_error = ((CFileSystem*)(pir->ir_rh))->f(pir);}

vt(EmptyFunc)

vt(DeleteFile)
vt(Dir)
vt(FileAttributes)
vt(FlushVolume)
vt(GetDiskInfo)
vt(OpenFile)
vt(RenameFile)
vt(SearchFile)
vt(QueryResourceInfo)
vt(DisconnectResource)
vt(NamedPipeUNCRequest)
vt(Ioctl16Drive)
vt(GetDiskParms)
vt(FindFirstFile)
vt(DirectDiskIO)

vt(FindClose)
vt(FindNextFile)

vt(ReadFile)
vt(WriteFile)
vt(FileSeek)
vt(CloseFile)
vt(CommitFile)
vt(LockFile)
vt(FileDateTime)
vt(NamedPipeHandleInfo)
vt(EnumerateHandle)

// Default implementations of FSD functions that should be overridden:

#undef vt
#define vt(f) int CFileSystem::f(pioreq pir) { \
	ASSERT(!"Using base-class " #f); \
	return pir->ir_error = ERROR_INVALID_FUNCTION;}

vt(DeleteFile)
vt(Dir)
vt(FileAttributes)
vt(FlushVolume)
vt(GetDiskInfo)
vt(OpenFile)
vt(RenameFile)
vt(SearchFile)
vt(QueryResourceInfo)
vt(NamedPipeUNCRequest)
vt(Ioctl16Drive)
vt(GetDiskParms)
vt(FindFirstFile)
vt(DirectDiskIO)

vt(FindClose)
vt(FindNextFile)

vt(ReadFile)
vt(WriteFile)
vt(FileSeek)
vt(CloseFile)
vt(CommitFile)
vt(LockFile)
vt(FileDateTime)
vt(NamedPipeHandleInfo)
vt(EnumerateHandle)

// An instance that wants to supply an empty function should point to
// EmptyFunc, which doesn't ASSERT when called:

int CFileSystem::EmptyFunc(pioreq pir)
	{							// CFileSystem::EmptyFunc
	return pir->ir_error = ERROR_INVALID_FUNCTION;
	}							// CFileSystem::EmptyFunc

///////////////////////////////////////////////////////////////////////////////

int CFileSystem::DisconnectResource(pioreq pir)
	{							// CLocalFileSystem::DisconnectResource
	delete this;
	return pir->ir_error = 0;
	}							// CLocalFileSystem::DisconnectResource

///////////////////////////////////////////////////////////////////////////////
