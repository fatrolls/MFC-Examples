// Lpfs.cpp -- Low Performance File System sample program
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#define NULL 0

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

#include "lpfs.h"

void OnAsyncEvent(PAEP aep);
CFileSystem* CreateInstance();

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

#pragma VxD_PAGEABLE_DATA_SEG

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_INIT_CODE_SEG
#pragma VxD_INIT_DATA_SEG

extern "C" extern DRP theDRP;

SYSCTL BOOL OnDeviceInit(HVM hVM, DWORD refdata)
	{							// OnDeviceInit
	if (!IOS_Get_Version())
		return FALSE;			// IOS not loaded (?)
	theDRP.DRP_aer = (PVOID) OnAsyncEvent;
	IOS_Register(&theDRP);

	return CLocalFileSystem::Register(CLpfs::CreateNew);
	}							// OnDeviceInit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_LOCKED_CODE_SEG
#pragma VxD_LOCKED_DATA_SEG

void OnAsyncEvent(PAEP aep)
	{							// OnAsyncEvent
	aep->AEP_result = AEP_SUCCESS;
	}							// OnAsyncEvent

CLpfs::CLpfs()
	{							// CLpfs::CLpfs
	m_openfiles = NULL;
	}							// CLpfs::CLpfs

CLpfs::~CLpfs()
	{							// CLpfs::~CLpfs
	}							// CLpfs::~CLpfs

// Static member function:

CFileSystem* CLpfs::CreateNew()
	{							// CreateInstance
	return new CLpfs();
	}							// CreateInstance

///////////////////////////////////////////////////////////////////////////////
// Is the volume associated with this request on of ours?

BOOL CLpfs::OurVolume(pioreq pir)
	{							// CLpfs::OurVolume
	PBYTE bootsec = ReadBootSector();
	if (!bootsec)
		{						// couldn't read boot sector
		pir->ir_error = m_error;
		return FALSE;
		}						// couldn't read boot sector
	BOOL ours = memcmp(bootsec + 3, "WALTONEY", 8) == 0;
	_HeapFree(bootsec, 0);
	if (!ours)
		return FALSE;

	// Dummy up a root directory in sector 64 that describes a file
	// named HelloWorld.txt

	DirectoryEntry e;
	e.created = e.modified = e.accessed = IFSMgr_Get_DOSTime();
	e.size = 0;
	e.sector = 65;
	e.attr = 0;

	char* longname = "HelloWorld.txt";
	e.namelen = (BYTE) BCSToUni(e.longname, (PBYTE) longname, strlen(longname), BCS_WANSI);
	CreateBasis(e.basename, e.longname, e.namelen);
	AppendBasisTail(e.basename, 1);
	e.namelen >>= 1;			// length should be in characters
	WriteSectorNow(64, (PBYTE) &e);

	return TRUE;
	}							// CLpfs::OurVolume

///////////////////////////////////////////////////////////////////////////////
// Is the same volume still mounted on this device?

BOOL CLpfs::SameVolume(CLocalFileSystem* fs)
	{							// CLpfs::SameVolume
	return TRUE;
	}							// CLpfs::SameVolume

///////////////////////////////////////////////////////////////////////////////

void CLpfs::GetVolumeLabel(PDWORD pVolSer, char* pVolLabel)
	{							// CLpfs::GetVolumeLabel
	PBYTE bootsec = ReadBootSector();
	if (!bootsec)
		return;
	*pVolSer = *(PDWORD) (bootsec + 0x39);
	memcpy(pVolLabel, bootsec + 0x43, 11);
	pVolLabel[11] = 0;
	_HeapFree(bootsec, 0);
	}							// CLpfs::GetVolumeLabel

///////////////////////////////////////////////////////////////////////////////

int CLpfs::DeleteFile(pioreq pir)
	{							// CLpfs::DeleteFile
#ifdef DEBUG
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: Delete %s (attr %X)\r\n", path, pir->ir_attr);
#endif // DEBUG

	return pir->ir_error = ERROR_ACCESS_DENIED;
	}							// CLpfs::DeleteFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::Dir(pioreq pir)
	{							// CLpfs::Dir
#ifdef DEBUG
	static char *fname[] = {"CREATE_DIR", "DELETE_DIR", "CHECK_DIR",
		"QUERY83_DIR", "QUERYLONG_DIR"};
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: %s %s\r\n", fname[pir->ir_flags], path);
#endif // DEBUG

	switch (pir->ir_flags)
		{						// select directory function

	///////////////////////////////////////////////////////////////////////////
	// CREATE_DIR: Create a new directory with the specified name. LPFS
	// only has one directory, so we always fail this call.
		
	case CREATE_DIR:
		return pir->ir_error = ERROR_ACCESS_DENIED;

	///////////////////////////////////////////////////////////////////////////
	// DELETE_DIR: Delete the directory with the specified name. LPFS doesn't
	// let you delete the root directory, so we always fail this call.

	case DELETE_DIR:
		return pir->ir_error = ERROR_ACCESS_DENIED;

	///////////////////////////////////////////////////////////////////////////
	// CHECK_DIR: See if the specified directory exists. LPFS only has a root
	// directory, so fail a check request for anything else

	case CHECK_DIR:
		if (!IFSIsRoot(pir->ir_ppath))
			return pir->ir_error = ERROR_PATH_NOT_FOUND;
		return pir->ir_error = 0;

	///////////////////////////////////////////////////////////////////////////
	// QUERY83_DIR: Convert the input path to a pure 8.3 version in ir_ppath2.
	// Since LPFS only has a root directory, this is pretty easy to do.

	case QUERY83_DIR:
		memcpy(pir->ir_ppath2, pir->ir_ppath, pir->ir_ppath->pp_totalLength);
		return pir->ir_error = 0;

	///////////////////////////////////////////////////////////////////////////
	// QUERYLONG_DIR: Convert the input path to a pure long-name version in
	// ir_ppath2. This is also pretty trivial for us.

	case QUERYLONG_DIR:
		memcpy(pir->ir_ppath2, pir->ir_ppath, pir->ir_ppath->pp_totalLength);
		return pir->ir_error = 0;

	default:
		ASSERT(!"Invalid DIR function");
		return pir->ir_error = ERROR_INVALID_FUNCTION;
		}						// select directory function
	}							// CLpfs::Dir

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FileAttributes(pioreq pir)
	{							// CLpfs::FileAttributes
#ifdef DEBUG
	static char *fname[] = {
		"GET_ATTRIBUTES",
		"SET_ATTRIBUTES",
		"GET_ATTRIB_COMP_FILESIZE",
		"SET_ATTRIB_MODIFY_DATETIME",
		"GET_ATTRIB_MODIFY_DATETIME",
		"SET_ATTRIB_LAST_ACCESS_DATETIME",
		"GET_ATTRIB_LAST_ACCESS_DATETIME",
		"SET_ATTRIB_CREATION_DATETIME",
		"GET_ATTRIB_CREATION_DATETIME",
		"GET_ATTRIB_FIRST_CLUST",
		};
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: %s %s\r\n", fname[pir->ir_flags], path);
#endif // DEBUG

	DirectoryEntry e;
	ULONG sector;
	
	if (!FindDirectoryEntry(pir->ir_ppath, &e, sector))
		return pir->ir_error = m_error;
	m_error = 0;

	switch (pir->ir_flags)
		{						// select subfunction
	case GET_ATTRIBUTES:
		pir->ir_attr = e.attr;
		break;

	case SET_ATTRIBUTES:
		e.attr = pir->ir_attr;
		if (ReadOnly())
			m_error = ERROR_WRITE_PROTECT;
		else
			m_error = WriteSectorNow(sector, (PBYTE) &e);
		break;

	case GET_ATTRIB_COMP_FILESIZE:
		pir->ir_size = e.size;
		break;

	case SET_ATTRIB_MODIFY_DATETIME:
		e.modified = pir->ir_dostime;
		if (ReadOnly())
			m_error = ERROR_WRITE_PROTECT;
		else
			m_error = WriteSectorNow(sector, (PBYTE) &e);
		break;

	case GET_ATTRIB_MODIFY_DATETIME:
		pir->ir_dostime = e.modified;
		break;

	case SET_ATTRIB_LAST_ACCESS_DATETIME:
		e.accessed = pir->ir_dostime;
		if (ReadOnly())
			m_error = ERROR_WRITE_PROTECT;
		else
			m_error = WriteSectorNow(sector, (PBYTE) &e);
		break;

	case GET_ATTRIB_LAST_ACCESS_DATETIME:
		pir->ir_dostime = e.accessed;
		break;

	case SET_ATTRIB_CREATION_DATETIME:
		e.created = pir->ir_dostime;
		if (ReadOnly())
			m_error = ERROR_WRITE_PROTECT;
		else
			m_error = WriteSectorNow(sector, (PBYTE) &e);
		break;

	case GET_ATTRIB_CREATION_DATETIME:
		pir->ir_dostime = e.created;
		break;

	case GET_ATTRIB_FIRST_CLUST:
		return pir->ir_error = ERROR_INVALID_FUNCTION;
		}						// select subfunction
	
	return pir->ir_error = m_error;
	}							// CLpfs::FileAttributes

///////////////////////////////////////////////////////////////////////////////

BOOL CLpfs::FindDirectoryEntry(ParsedPath* path, DirectoryEntry* ep, ULONG& sector, BOOL wantfile /* = TRUE */)
	{							// CLpfs::FindDirectoryEntry
	CPosition pos(path, wantfile);
	GetRootDirectoryEntry(ep, sector);
	while (!pos.AtEnd() && FindNextDirectoryEntry(pos, ep, sector))
		pos.Step();				// descend through pathname
	return pos.AtEnd();
	}							// CLpfs::FindDirectoryEntry

void CLpfs::GetRootDirectoryEntry(DirectoryEntry* ep, ULONG& sector)
	{							// CLpfs::GetRootDirectoryEntry
	memset(ep, 0, sizeof(DirectoryEntry));
	ep->size = sizeof(DirectoryEntry); // LPFS only has one file
	ep->attr = FILE_ATTRIBUTE_DIRECTORY;
	ep->sector = 64;			// LPFS has its root directory at sector 64
	sector = 0;
	}							// CLpfs::GetRootDirectoryEntry

BOOL CLpfs::FindNextDirectoryEntry(const CPosition pos, DirectoryEntry* ep, ULONG& sector)
	{							// CLpfs::FindNextDirectoryEntry
	ASSERT(!pos.AtEnd());
	PathElement* element = pos.Current();
	int elsize = element->pe_length;
	
	BOOL islong = elsize > 12;
	USHORT basename[11];
	if (!islong)
		ShortToLossyFcb(basename, element->pe_unichars, elsize);

	// LPFS has a very non-optimal directory format in which each entry
	// occupies an entire sector and all the entries are contiguous on the
	// disk. You'd never design a real file system this way, of course.
	// It only works here because we only allow one file and one level
	// of directory.
	
	sector = ep->sector;		// sector of 1st directory entry
	ULONG lastsector = sector + (ep->size / sizeof(DirectoryEntry));
	DirectoryEntry e;

	for (; sector < lastsector; ++sector)
		{						// search directory
		if (m_error = ReadSectorNow(sector, (PBYTE) &e))
			return FALSE;		// error reading directory entry
		
		// Check for a match between the path element and the upper-case
		// version of the long name in the directory entry
		
		if (e.namelen*2 == elsize-2)
			{					// check for matching long name
			USHORT ucname[LFNMAXNAMELEN];
			UniToUpper(ucname, e.longname, e.namelen*2);
			if (memcmp(ucname, element->pe_unichars, elsize-2) == 0)
				break;			// long names match
			}					// check for matching long name
		
		// If the path element is in 8.3 format, also check to see if it's
		// the same as the short name recorded in the directory entry
		
		if (!islong && memcmp(ep->basename, basename, sizeof(basename)) == 0)
			break;				// short names match
		}						// search directory

	if (sector < lastsector)
		{						// found the entry
		*ep = e;
		return TRUE;
		}						// found the entry

	m_error = pos.AtEnd() ? ERROR_FILE_NOT_FOUND : ERROR_PATH_NOT_FOUND;
	return FALSE;
	}							// CLpfs::FindNextDirectoryEntry

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FlushVolume(pioreq pir)
	{							// CLpfs::FlushVolume
#ifdef DEBUG
	Debug_Printf("LPFS: FLUSH");
	if (pir->ir_options & VOL_DISCARD_CACHE)
		Debug_Printf(" VOL_DISCARD_CACHE");
	if (pir->ir_options & VOL_REMOUNT)
		Debug_Printf(" VOL_REMOUNT");
	Debug_Printf("\r\n");
#endif DEBUG

	ASSERT(m_outstanding == 0);

	if (pir->ir_options & VOL_REMOUNT)
		{						// remount volume
		return pir->ir_error = ERROR_INVALID_FUNCTION; // TODO
		}						// remount volume

	// If we were using VCACHE, we'd flush our cache buffers now.
	// In addition, we need to send our disk drive a flush command.

	PIOR ior = CreateIOR((pir->ir_options & VOL_DISCARD_CACHE)
		? IOR_FLUSH_DRIVE_AND_DISCARD : IOR_FLUSH_DRIVE, 0);
	if (!ior)
		return pir->ir_error = ERROR_NOT_ENOUGH_MEMORY;
	SendCommandAndWait(ior);
	DestroyIOR(ior);			// ignore any error

	return pir->ir_error = 0;
	}							// CLpfs::FlushVolume

///////////////////////////////////////////////////////////////////////////////

int CLpfs::GetDiskInfo(pioreq pir)
	{							// CLpfs::GetDiskInfo
#ifdef DEBUG
	Debug_Printf("LPFS: GETDISKINFO\r\n");
#endif
	
	pir->ir_length = 512;		// bytes per sector
	pir->ir_size = 4096;		// total number of allocation units
	pir->ir_sectors = 1;		// number of sectors per allocation unit
	pir->ir_numfree = 42;		// number of free allocation units (a lie)
	return pir->ir_error = 0;
	}							// CLpfs::GetDiskInfo

///////////////////////////////////////////////////////////////////////////////

int CLpfs::OpenFile(pioreq pir)
	{							// CLpfs::OpenFile
#ifdef DEBUG
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: OPEN %s, access %X, action %X, attr %X\r\n", path, pir->ir_flags, pir->ir_options, pir->ir_attr);
#endif // DEBUG
	
	// Since LPFS only supports one file that can't be deleted or
	// renamed, it's always an error if we're asked to open a file
	// with some other name. A real file system would go on to
	// create a new file, etc.
	
	int mode = pir->ir_flags & ACCESS_MODE_MASK;
	int options = pir->ir_options;
	DirectoryEntry e;
	ULONG sector;
	if (!FindDirectoryEntry(pir->ir_ppath, &e, sector))
		{						// file not found
		if (options & ACTION_NEXISTS_CREATE)
			m_error = ERROR_ACCESS_DENIED; // we're not going to create it
		return pir->ir_error = m_error;
		}						// file not found

	if (!(options & (ACTION_EXISTS_OPEN | ACTION_TRUNCATE)))
		return pir->ir_error = ERROR_FILE_EXISTS; // doesn't want existing file

	// We're going to open the file, so capture the current time

	e.accessed = IFSMgr_Get_DOSTime();
	if (mode == ACCESS_WRITEONLY || mode == ACCESS_READWRITE)
		e.modified = e.accessed;
	if (m_error = WriteSectorNow(sector, (PBYTE) &e))
		return pir->ir_error = m_error;

	#undef vt
	#define vt(f) f##Thunk,

	static hndlmisc openmisc = {
		IFS_VERSION,
		IFS_REVISION,
		NUM_HNDLMISC, {
		vt(FileSeek)
		vt(CloseFile)
		vt(CommitFile)
		vt(LockFile)
		vt(FileDateTime)
		vt(EmptyFunc)			// NamedPipeUNCRequest
		vt(EmptyFunc)			// NamedPipeHandleInfo
		vt(EnumerateHandle)
		}};
	
	CFile* fp = new CFile(this, &e, sector);
	if (mode == ACCESS_WRITEONLY || mode == ACCESS_READWRITE)
		{						// open for writing
		fp->m_flags |= CFile::FF_OUTPUT;
		if (options & ACTION_TRUNCATE)
			TruncateFile(fp);
		fp->m_pos = fp->m_size; // append from here
		}						// open for writing

	pir->ir_fh = (fh_t) fp;
	pir->ir_dostime = e.modified;
	pir->ir_size = e.size;
	pir->ir_attr = e.attr;
	SetHandleFunc(pir, ReadFileThunk, WriteFileThunk, &openmisc);
		
	return pir->ir_error = 0;
	}							// CLpfs::OpenFile

///////////////////////////////////////////////////////////////////////////////

CLpfs::CFile::CFile(CLpfs* fs, CLpfs::DirectoryEntry* ep, ULONG dirsector)
	{							// CFile::CFile
	m_next = fs->m_openfiles;
	m_prev = NULL;
	if (m_next)
		m_next->m_prev = this;
	fs->m_openfiles = this;

	m_fs = fs;
	m_direntry = dirsector;
	m_size = ep->size;
	m_pos = 0;
	m_sector = ep->sector;
	m_flags = 0;
	}							// CFile::CFile

CLpfs::CFile::~CFile()
	{							// CFile::~CFile
	if (m_next)
		m_next->m_prev = m_prev;
	if (m_prev)
		m_prev->m_next = m_next;
	else
		m_fs->m_openfiles = m_next;
	}							// CFile::~CFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::RenameFile(pioreq pir)
	{							// CLpfs::RenameFile
#ifdef DEBUG
	BYTE path1[MAX_PATH], path2[MAX_PATH];
	int len = UniToBCSPath(path1, pir->ir_ppath->pp_elements, sizeof(path1)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path1[len] = 0;
	len = UniToBCSPath(path2, pir->ir_ppath2->pp_elements, sizeof(path2)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path2[len] = 0;
	Debug_Printf("LPFS: RENAME %s (attr %X) to %s (attr %X)\r\n", path1, pir->ir_attr, path2, pir->ir_attr2);
#endif // DEBUG

	// Make sure we're not dealing with a read-only volume

	if (ReadOnly())
		return pir->ir_error = ERROR_WRITE_PROTECT;
	
	// Prepare for a wild-card search over the source directory. There can
	// only be wild cards if the source name is in 8.3 format, and LPFS
	// ignores the problem anyway when we finally get to the point of
	// constructing a new name, so this generality is actually pretty useless
	// here.
	
	int numrenamed = 0;
	CScanPos pos(this);
	DirectoryEntry e;
	if ((m_error = pos.Prepare(pir, &e)))
		return pir->ir_error = m_error;

	// Locate the target directory. In LPFS, it will always be the same as
	// the source directory (because there's only one directory).
	
	BOOL newlong = (pir->ir_attr2 & (FILE_FLAG_KEEP_CASE | FILE_FLAG_IS_LFN)) != 0;
	PathElement* pattern = IFSLastElement(pir->ir_ppath2);
	int elsize = pattern->pe_length;
	string_t newname;
	if (pir->ir_attr2 & FILE_FLAG_KEEP_CASE)
		newname = pir->ir_uFName;
	else
		newname = pattern->pe_unichars;
	if (elsize-2 > sizeof(e.longname))
		return pir->ir_error = ERROR_ACCESS_DENIED; // new name is too long

	ULONG junk;
	DirectoryEntry tde;			// description of target directory
	if (!FindDirectoryEntry(pir->ir_ppath2, &tde, junk, FALSE))
		{						// can't find target directory
		if (m_error == ERROR_FILE_NOT_FOUND)
			m_error = ERROR_PATH_NOT_FOUND;
		return pir->ir_error = m_error;
		}						// can't find target directory

	BOOL samedir = TRUE;		// always true for LPFS
	
	// Locate each of the files that's supposed to be renamed
	
	while ((m_error = pos.FindNext(&e)) == 0)
		{						// for each target file
		ULONG esector = pos.sector; // where the current directory entry is

		// Determine the new name for this file. We'll only have wild cards
		// for an 8.3 name, which makes it relatively straightforward (but
		// still beyond the scope of this sample) to construct the new name.

		;						// I.e., just use unmodified "newname" & "pattern"

		// We'll scan the directory looking for the new name of the file.
		// As part of the process, also compute a numeric "tail" for the
		// new short name of the file

		USHORT basename[11];
		int maxtail = 0;
		CreateBasis(basename, newname, elsize-2);

		ULONG sector = tde.sector;	// starting point for rescan
		ULONG lastsector = sector + (tde.size / sizeof(DirectoryEntry));
		DirectoryEntry dup;

		for (; sector < lastsector; ++sector)
			{					// look for duplicate of new name
			if (samedir && sector == esector)
				continue;		// skip looking at the target entry

			if ((m_error = ReadSectorNow(sector, (PBYTE) &dup)))
				return pir->ir_error = m_error;
			
			// To check for a duplicate long name, use the upper-case
			// version of the name in the directory because file
			// search operations are case-insensitive
			
			if (dup.namelen*2 == elsize-2)
				{				// check for duplicate long name
				USHORT ucname[LFNMAXNAMELEN];
				UniToUpper(ucname, dup.longname, elsize-2);
				if (memcmp(ucname, pattern->pe_unichars, elsize-2) == 0)
					return pir->ir_error = ERROR_ACCESS_DENIED; // duplicate name
				}				// check for duplicate long name
		
			// See if the short name of this file matches the new basis name
			// except for the numeric tail. If so, remember the largest
			// tail value we ever see.
			
			int tail = MatchBasisName(basename, dup.basename);
			if (tail > maxtail)
				maxtail = tail;
			if (tail == -1 && !newlong)
				return pir->ir_error = ERROR_ACCESS_DENIED; // duplicate name
			}					// look for duplicate of new name

		// No duplicate, so rename the file. 

		memcpy(e.longname, newname, elsize-2);
		e.namelen = (elsize-2)/2;
		if (newlong)
			AppendBasisTail(basename, maxtail+1); // make up a short name
		memcpy(e.basename, basename, sizeof(e.basename));
		
		// In real life, we might need to allocate a new entry in the target
		// directory. In LPFS, we're always renaming in the source directory,
		// so just rewrite the entry we found earlier.
		
		if (samedir)
			{					// rewrite directory entry
			m_error = WriteSectorNow(esector, (PBYTE) &e);
			if (m_error)
				return pir->ir_error = m_error;
			}					// rewrite directory entry
		else
			ASSERT(FALSE);		// can't happen in LPFS

		++numrenamed;
		}						// for each target file
	
	if (m_error == ERROR_NO_MORE_FILES)
		if (numrenamed)
			m_error = 0;		// had at least one match
		else
			m_error = ERROR_FILE_NOT_FOUND;

	return pir->ir_error = m_error;
	}							// CLpfs::RenameFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::SearchFile(pioreq pir)
	{							// CLpfs::SearchFile
#ifdef DEBUG
	static char* fname[] = {"SEARCH_FIRST", "SEARCH_NEXT"};
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: %s %s (attr %X)\r\n", fname[pir->ir_flags], path, pir->ir_attr);
#endif // DEBUG

	switch (pir->ir_flags)
		{						// select subfunction
	
	case SEARCH_FIRST:
		{						// SEARCH_FIRST
		srch_entry* sep = (srch_entry*) pir->ir_data;
		sep->se_key.sk_attr = pir->ir_attr;

		// Handle request for volume label as a special case
		
		if (LOBYTE(pir->ir_attr) == FILE_ATTRIBUTE_LABEL)
			{					// looking for volume label
			PBYTE bootsec = ReadBootSector();
			if (bootsec)
				{				// copy volume label
				memcpy(sep->se_name, bootsec + 43, 11);
				sep->se_name[11] = 0;
				_HeapFree(bootsec, 0);
				return pir->ir_error = 0;
				}				// copy volume label
			return pir->ir_error = m_error;
			}					// looking for volume label

		BYTE excludemask = (~pir->ir_attr) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY);
		
		// Convert search name (which ought to be an 8.3 name, possibly
		// with wildcards) to an FCB format name for use with IFSMgr_MetaMatch
		
		PathElement* name = (PathElement*)((PBYTE) pir->ir_ppath + pir->ir_ppath->pp_prefixLength);
		ASSERT(!(pir->ir_attr & FILE_FLAG_IS_LFN));
		USHORT basename[11];
		ShortToLossyFcb(basename, name->pe_unichars, name->pe_length);
		int matchsemantics = UFLG_DOS;
		if (pir->ir_attr & FILE_FLAG_WILDCARDS)
			matchsemantics |= UFLG_META;

		// Find the directory entry for the subdirectory within which
		// we're supposed to search
		
		DirectoryEntry e;
		ULONG sector;
		if (!FindDirectoryEntry(pir->ir_ppath, &e, sector, FALSE))
			{					// can't find directory
			if (m_error == ERROR_FILE_NOT_FOUND || m_error == ERROR_PATH_NOT_FOUND)
				m_error = ERROR_PATH_NOT_FOUND;
			return pir->ir_error = m_error;
			}					// can't find directory
		
		// Search the directory for the first matching file
		
		sector = e.sector;
		ULONG lastsector = sector + (e.size / sizeof(DirectoryEntry));
		for (; sector < lastsector; ++sector)
			{					// search directory
			if (m_error = ReadSectorNow(sector, (PBYTE) &e))
				return pir->ir_error = m_error;
			if (e.attr & excludemask)
				continue;
			if (IFSMgr_MetaMatch(basename, e.basename, matchsemantics))
				break;			// found match
			}					// search directory
		if (sector >= lastsector)
			return pir->ir_error = ERROR_NO_MORE_FILES;

		// We have a match. Fill in the DOS-format find-data area
		// at ir_data. In real life, we'd record enough info in the
		// 4 bytes at sk_localFSD to allow us to resume the search
		// at SEARCH_NEXT. Because of our poor choice of data structures,
		// 4 bytes wouldn't be enough, though.

		memcpy(sep->se_key.sk_pattern, basename, sizeof(basename));
		sep->se_attrib = e.attr;
		*(dos_time*)&sep->se_time = e.modified;
		sep->se_size = e.size;

		USHORT shortname[12];
		int len = FcbToShort(shortname, e.basename, FALSE);
		sep->se_name[UniToBCS((PBYTE) sep->se_name, shortname, len, 12, BCS_OEM)] = 0;
		
		return pir->ir_error = 0;
		}						// SEARCH_FIRST

	case SEARCH_NEXT:
		{						// SEARCH_FIRST
		return pir->ir_error = ERROR_NO_MORE_FILES; // because there's only one on the disk
		}						// SEARCH_FIRST
	
	default:
		ASSERT(FALSE);
		return pir->ir_error = ERROR_INVALID_FUNCTION;
		}						// select subfunction
	}							// CLpfs::SearchFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::QueryResourceInfo(pioreq pir)
	{							// CLpfs::QueryResourceInfo
#ifdef DEBUG
	BYTE path[MAX_PATH];
	if (pir->ir_options < 2)
		{						// level 0 or 1 has name
		int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
		if (len < 0)
			len = 0;
		path[len] = 0;
		}						// level 0 or 1 has name
	else
		path[0] = 0;
	Debug_Printf("LPFS: QUERY level %d %s\r\n", pir->ir_options, path);
#endif // DEBUG

	if (pir->ir_options == 2)
		{						// answer level 2 query
		pir->ir_length = MAKELONG(sizeof(((DirectoryEntry*) NULL)->longname), 260);
		pir->ir_options = FS_CASE_IS_PRESERVED | FS_UNICODE_STORED_ON_DISK | FS_VOL_SUPPORTS_LONG_NAMES;
		return pir->ir_error = 0;
		}						// answer level 2 query
	return pir->ir_error = ERROR_INVALID_FUNCTION;
	}							// CLpfs::QueryResourceInfo

///////////////////////////////////////////////////////////////////////////////
// It's okay for an FSD to fail a GetDiskParms request if it doesn't map
// an MS-DOS drive.

int CLpfs::GetDiskParms(pioreq pir)
	{							// CLpfs::GetDiskParms
#ifdef DEBUG
	Debug_Printf("LPFS: GETDISKPARMS\r\n");
#endif
	return pir->ir_error = ERROR_INVALID_FUNCTION;
	}							// CLpfs::GetDiskParms

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FindFirstFile(pioreq pir)
	{							// CLpfs::FindFirstFile
#ifdef DEBUG
	BYTE path[MAX_PATH];
	int len = UniToBCSPath(path, pir->ir_ppath->pp_elements, sizeof(path)-1, BCS_OEM);
	if (len < 0)
		len = 0;
	path[len] = 0;
	Debug_Printf("LPFS: FIND_FIRST %s (attr %X)\r\n", path, pir->ir_attr);
#endif // DEBUG

	// Set output parameters for IFS to use in case we return success

	#undef vt
	#define vt(f) f##Thunk,

	static hndlmisc findmisc = {
		IFS_VERSION,
		IFS_REVISION,
		NUM_HNDLMISC, {
		vt(EmptyFunc)			// HM_SEEK
		vt(FindClose)			// HM_CLOSE
		vt(EmptyFunc)			// HM_COMMIT
		vt(EmptyFunc)			// HM_FILELOCKS
		vt(EmptyFunc)			// HM_FILETIMES
		vt(EmptyFunc)			// HM_PIPEREQUEST
		vt(EmptyFunc)			// HM_HANDLEINFO
		vt(EnumerateHandle)		// HM_ENUMHANDLE
		}};

	// It's not obvious from the doc, but ir_hfunc already points
	// to a "hndlfunc" structure that we're supposed to complete.

	SetHandleFunc(pir, FindNextFileThunk, EmptyFuncThunk, &findmisc);

	_WIN32_FIND_DATA* fdp = (_WIN32_FIND_DATA*) pir->ir_data;

	// Handle request for volume label as a special case
	
	if (LOBYTE(pir->ir_attr) == FILE_ATTRIBUTE_LABEL)
		{						// looking for volume label
		PBYTE bootsec = ReadBootSector();
		if (bootsec)
			{					// copy volume label
			BCSToUni(fdp->cFileName, bootsec + 43, 11, BCS_OEM);
			fdp->cFileName[11] = 0; // no-one will care about 8.3 version of label
			fdp->cAlternateFileName[0] = 0;
			fdp->dwFileAttributes = FILE_ATTRIBUTE_LABEL;
			pir->ir_fh = NULL;	// should never need this
			_HeapFree(bootsec, 0);
			return pir->ir_error = 0;
			}					// copy volume label
		return pir->ir_error = m_error;
		}						// looking for volume label

	DirectoryEntry e;
	CScanPos* pos = new CScanPos(this);
	if ((m_error = pos->Prepare(pir, &e)) || (m_error = pos->FindNext(&e)))
		{						// directory or file not found
		delete pos;
		return pir->ir_error = m_error;
		}						// directory or file not found

	FindFill(fdp, &e);
	return pir->ir_error = 0;
	}							// CLpfs::FindFirstFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FindNextFile(pioreq pir)
	{							// CLpfs::FindNextFile
#ifdef DEBUG
	Debug_Printf("LPFS: FINDNEXT\r\n");
#endif

	CScanPos* pos = (CScanPos*) pir->ir_fh;
	DirectoryEntry e;
	if (!pos || (m_error = pos->FindNext(&e)))
		return pir->ir_error = ERROR_NO_MORE_FILES;
	FindFill((_WIN32_FIND_DATA*) pir->ir_data, &e);
	return pir->ir_error = 0;
	}							// CLpfs::FindNextFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FindClose(pioreq pir)
	{							// CLpfs::FindClose
#ifdef DEBUG
	Debug_Printf("LPFS: FINDCLOSE\r\n");
#endif
	CScanPos* pos = (CScanPos*) pir->ir_fh;
	if (pos)
		delete pos;
	return pir->ir_error = 0;
	}							// CLpfs::FindClose

///////////////////////////////////////////////////////////////////////////////

void CLpfs::FindFill(_WIN32_FIND_DATA* fdp, DirectoryEntry* ep)
	{							// CLpfs::FindFill
	fdp->dwFileAttributes = ep->attr;
	fdp->ftCreationTime = IFSMgr_DosToWin32Time(ep->created);
	fdp->ftLastAccessTime = IFSMgr_DosToWin32Time(ep->accessed);
	fdp->ftLastWriteTime = IFSMgr_DosToWin32Time(ep->modified);
	fdp->nFileSizeHigh = 0;
	fdp->nFileSizeLow = ep->size;
	
	memcpy(fdp->cFileName, ep->longname, ep->namelen*2);
	fdp->cFileName[ep->namelen] = 0;
	fdp->cAlternateFileName[FcbToShort(fdp->cAlternateFileName, ep->basename, FALSE)/2] = 0;
	}							// CLpfs::FindFill

///////////////////////////////////////////////////////////////////////////////

int CLpfs::EnumerateHandle(pioreq pir)
	{							// CLpfs::EnumerateHandle
#ifdef DEBUG
	static char *fname[] = {
		"ENUMH_GETFILEINFO",
		"ENUMH_GETFILENAME",
		"ENUMH_GETFINDINFO",
		"ENUMH_RESUMEFIND",
		"ENUMH_RESYNCFILEDIR",
		};
	Debug_Printf("LPFS: %s %X\r\n", fname[pir->ir_flags], pir->ir_fh);
#endif
	return pir->ir_error = ERROR_INVALID_FUNCTION;
	}							// CLpfs::EnumerateHandle

///////////////////////////////////////////////////////////////////////////////

int CLpfs::ReadFile(pioreq pir)
	{							// CLpfs::ReadFile
	CFile* fp = (CFile*) pir->ir_fh;
	PBYTE dp = (PBYTE) pir->ir_data;
	ULONG nbytes = (ULONG) pir->ir_length;
	ULONG pos = (ULONG) pir->ir_pos;

	if (pos > fp->m_size)
		pos = fp->m_size;
	if (pos + nbytes > fp->m_size)
		nbytes = fp->m_size - pos;

	// In real life, you should build and execute an asynchronous read
	// for a realistic number of sectors, probably into a sector cache
	// maintained via VCACHE. In this simple example, we'll just do a
	// synchronous read for the one-and-only sector the file can
	// occupy.

	BYTE data[512];
	m_error = ReadSectorNow(fp->m_sector, data);
	memcpy(dp, data + pos, nbytes);

	pos += nbytes;
	fp->m_pos = pos;

	pir->ir_pos = pos;
	pir->ir_length = nbytes;
	return pir->ir_error = m_error;
	}							// CLpfs::ReadFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::WriteFile(pioreq pir)
	{							// CLpfs::WriteFile
	if (ReadOnly())
		return pir->ir_error = ERROR_WRITE_PROTECT;

	CFile* fp = (CFile*) pir->ir_fh;
	ASSERT(fp->m_flags & CFile::FF_OUTPUT);
	PBYTE dp = (PBYTE) pir->ir_data;
	ULONG nbytes = (ULONG) pir->ir_length;
	ULONG pos = (ULONG) pir->ir_pos;

	// In real life, you'd extend the file so it's big enough to
	// hold the new data. You'd also schedule asynchronous writes,
	// probably through a cache maintained via VCACHE. In this example,
	// we'll just rewrite the data immediately.
	
	if (pos > 512)
		pos = 512;
	if (pos + nbytes > 512)
		nbytes = 512-pos;

	if (nbytes == 0)
		{						// truncate file at this location
		fp->m_pos = pos;
		TruncateFile(fp);
		}						// truncate file at this location
	else
		{						// write some data
		BYTE data[512];
		if (m_error = ReadSectorNow(fp->m_sector, data))
			return pir->ir_error = m_error;
		memcpy(data + pos, dp, nbytes);
		if (m_error = WriteSectorNow(fp->m_sector, data))
			return pir->ir_error = m_error;
		}						// write some data

	pos += nbytes;
	fp->m_pos = pos;
	if (pos > fp->m_size)
		fp->m_size = pos;

	pir->ir_length = nbytes;
	pir->ir_pos = pos;
	return pir->ir_error = 0;
	}							// CLpfs::WriteFile

///////////////////////////////////////////////////////////////////////////////

void CLpfs::TruncateFile(CLpfs::CFile* fp)
	{							// CLpfs::TruncateFile
	fp->m_size = fp->m_pos;
	}							// CLpfs::TruncateFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FileSeek(pioreq pir)
	{							// CLpfs::FileSeek
	CFile* fp = (CFile*) pir->ir_fh;
	ULONG pos = pir->ir_pos;
	switch (pir->ir_flags)
		{						// select on seek origin option
	case FILE_BEGIN:
		break;					// relative to beginning
	case FILE_END:
		pos += fp->m_size;		// relative to file size
		break;
	default:
		ASSERT(FALSE);
		break;
		}						// select on seek origin option
	fp->m_pos = pos;
	pir->ir_pos = pos;
	return pir->ir_error = 0;
	}							// CLpfs::FileSeek

///////////////////////////////////////////////////////////////////////////////

int CLpfs::CloseFile(pioreq pir)
	{							// CLpfs::CloseFile
	CFile* fp = (CFile*) pir->ir_fh;
	if (fp->m_flags & CFile::FF_OUTPUT)
		{						// file was open for output
		DirectoryEntry e;
		if (m_error = ReadSectorNow(fp->m_direntry, (PBYTE) &e))
			return pir->ir_error = m_error;
		e.size = fp->m_size;
		m_error = WriteSectorNow(fp->m_direntry, (PBYTE) &e);
		}						// file was open for output
	delete fp;
	pir->ir_pos = 0;			// no file locks to remember
	return pir->ir_error = m_error;
	}							// CLpfs::CloseFile

///////////////////////////////////////////////////////////////////////////////

int CLpfs::FileDateTime(pioreq pir)
	{							// CLpfs::FileDateTime
	CFile* fp = (CFile*) pir->ir_fh;
	DirectoryEntry e;
	if (m_error = ReadSectorNow(fp->m_direntry, (PBYTE) &e))
		return pir->ir_error = m_error;
	BOOL changed = FALSE;
	switch (pir->ir_flags)
		{						// perform requested operation
	case GET_MODIFY_DATETIME:
		pir->ir_dostime = e.modified;
		pir->ir_options = 0;
		break;

	case SET_MODIFY_DATETIME:
		if (!(fp->m_flags & CFile::FF_OUTPUT))
			return pir->ir_error = ERROR_ACCESS_DENIED;
		e.modified = pir->ir_dostime;
		changed = TRUE;
		break;

	case GET_LAST_ACCESS_DATETIME:
		pir->ir_dostime = e.accessed;
		pir->ir_options = 0;
		break;

	case SET_LAST_ACCESS_DATETIME:
		if (!(fp->m_flags & CFile::FF_OUTPUT))
			return pir->ir_error = ERROR_ACCESS_DENIED;
		e.accessed = pir->ir_dostime;
		changed = TRUE;
		break;

	case GET_CREATION_DATETIME:
		pir->ir_dostime = e.created;
		pir->ir_options = 0;
		break;

	case SET_CREATION_DATETIME:
		if (!(fp->m_flags & CFile::FF_OUTPUT))
			return pir->ir_error = ERROR_ACCESS_DENIED;
		e.created = pir->ir_dostime;
		changed = TRUE;
		break;
		}						// perform requested operation

	if (changed)
		m_error = WriteSectorNow(fp->m_direntry, (PBYTE) &e);
	else
		m_error = 0;
	return pir->ir_error = m_error;
	}							// CLpfs::FileDateTime

///////////////////////////////////////////////////////////////////////////////

int CLpfs::CScanPos::Prepare(pioreq pir, DirectoryEntry* ep)
	{							// CLpfs::CScanPos::Prepare
	PathElement* name = IFSLastElement(pir->ir_ppath);
	namelen = name->pe_length;
	memcpy(pattern, name->pe_unichars, namelen); // copy & null terminate
	pattern[namelen/2] = 0;
	
	matchsemantics = 0;
	attr = pir->ir_attr;
	if (attr & (FILE_FLAG_KEEP_CASE | FILE_FLAG_IS_LFN))
		matchsemantics |= UFLG_NT;
        else
            matchsemantics |= UFLG_DOS;
	if (attr & FILE_FLAG_WILDCARDS)
		matchsemantics |= UFLG_META;
	hasdot = (attr & FILE_FLAG_HAS_DOT) != 0;

	excludemask = (BYTE) ((~attr) & (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_DIRECTORY));

	if (!fs->FindDirectoryEntry(pir->ir_ppath, ep, sector, FALSE))
		{					// can't find directory
		if (fs->m_error == ERROR_FILE_NOT_FOUND || fs->m_error == ERROR_PATH_NOT_FOUND)
			fs->m_error = ERROR_PATH_NOT_FOUND;
		return fs->m_error;
		}					// can't find directory

	sector = ep->sector - 1;	// because FindNext will increment to start with
	lastsector = ep->sector + (ep->size / sizeof(DirectoryEntry));

	return 0;
	}							// CLpfs::CScanPos::Prepare

///////////////////////////////////////////////////////////////////////////////

int CLpfs::CScanPos::FindNext(DirectoryEntry* ep)
	{							// CLpfs::CScanPos::FindNext
	for (++sector; sector < lastsector; ++sector)
		{					// search directory
		if (fs->m_error = fs->ReadSectorNow(sector, (PBYTE) ep))
			return fs->m_error;	// error reading directory entry
		
		// Modified version of TestMustMatch macro from IFS.H, for use
		// here since we don't have an ioreq with must-match flags during
		// a FindNextFile

		#undef TestMustMatch
		#define TestMustMatch(ir_attr, attr) \
			((((ir_attr & (attr)<<8) ^ ir_attr)	& FILE_ATTRIBUTE_MUSTMATCH) == 0)
		
		if (ep->attr & excludemask || !TestMustMatch(attr, ep->attr))
			continue;

		// IFSMgr_MetaMatch expects to compare two upper-cased, null
		// terminated Unicode strings (nice of them to tell us...)

		USHORT thisname[LFNMAXNAMELEN+1];
		thisname[UniToUpper(thisname, ep->longname, ep->namelen*2)/2] = 0;

		if (IFSMgr_MetaMatch(pattern, thisname, matchsemantics))
			return 0;			// found match

		// No match under the long name. Try the short name

		thisname[FcbToShort(thisname, ep->basename, hasdot)/2] = 0;
		if (IFSMgr_MetaMatch(pattern, thisname, matchsemantics))
			return 0;		// found match
		}					// search directory
	return ERROR_NO_MORE_FILES;
	}							// CLpfs::CScanPos::FindNext

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
