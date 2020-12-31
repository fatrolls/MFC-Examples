// FileSystem.h -- Interface for the CFileSystem class
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#ifndef SETINITSEG
#define SETINITSEG
#pragma warning(disable:4075) // nonstandard init seg
#pragma init_seg("INITCODE")
#pragma warning(default:4075)
#endif

///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

#include <string.h>
#pragma intrinsic(memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen)

#ifdef DEBUG
	#define ASSERT(e) if(!(e)){Debug_Printf("Assertion failure in " __FILE__ ", line %d: " #e "\r\n", __LINE__);\
		_asm int 1\
		}
#else
	#define ASSERT(e)
#endif

#ifndef MAKELONG
	#define MAKELONG(low, high) ((LONG)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))
#endif

#ifndef FIELDOFFSET
	#define FIELDOFFSET(type, field) ((DWORD)(&((type *)0)->field))
#endif

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

#ifndef min
	#define min(a,b) ((a) > (b) ? (b) : (a))
#endif

#ifndef max
	#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

///////////////////////////////////////////////////////////////////////////////
// CFileSystem class:

extern "C" extern ILB theILB;

class CFileSystem
{								// CFileSystem
public:
	CFileSystem();
	virtual ~CFileSystem();

	static CFileSystem* (*CreateNewFcn)();
	static int ProviderId;
	static BOOL Register(CFileSystem* (*createnew)());

	// Virtual FSD functions used by all types of file system:

	#undef vt
	#define vt(f) virtual int f(pioreq pir);

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

	// The following table declares the static thunks that interface
	// between IFS and various virtual FSD functions:
	
	#undef vt
	#define vt(f) static int f##Thunk(pioreq pir);

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
};								// CFileSystem

#endif // FILESYSTEM_H