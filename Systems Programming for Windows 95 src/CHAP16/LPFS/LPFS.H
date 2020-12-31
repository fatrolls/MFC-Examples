// LPFS.H -- Declarations for Low Performance File System
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef LPFS_H
#define LPFS_H

#define SYSCTL extern "C"

#include "LocalFileSystem.h"

#ifndef SETINITSEG
#define SETINITSEG
#pragma warning(disable:4075) // nonstandard init seg
#pragma init_seg("INITCODE")
#pragma warning(default:4075)
#endif

///////////////////////////////////////////////////////////////////////////////
// CLpfs class

class CLpfs : public CLocalFileSystem
{								// CLpfs
public:
	CLpfs();
	virtual ~CLpfs();

	// Directory entry. One of the reasons why this is a *low* performance
	// file system is the fact that we reserve space for a very long
	// file name in every directory entry. This would be really stoopid if
	// it weren't for the fact that there's only one file on one of our disks!

	struct DirectoryEntry
		{						// DirectoryEntry
		dos_time created;		//  00 when created
		dos_time modified;		//  04 when last modified
		dos_time accessed;		//  08 when last accessed
		ULONG size;				//  0C size of file
		ULONG sector;			//  10 sector where file starts
		BYTE attr;				//  14 file attributes
		BYTE namelen;			//  15 length of long name
		USHORT basename[11];	//  16 8.3 name (Unicode)
		USHORT longname[234];	//  2C long name (Unicode)
		};						// 200 DirectoryEntry

	class CPosition
		{						// ParsedPathname iterator
		public:
			CPosition(ParsedPath* path, BOOL wantfile)
				{m_path = path;m_pos = 4;m_last = wantfile ? path->pp_totalLength : path->pp_prefixLength;}

			ParsedPath*		m_path;		// pathname structure being traversed
			int				m_pos;		// current position in structure
			int				m_last;		// last offset to examine

			BOOL			AtEnd() const {return m_pos >= m_last;}
			PathElement*	Current() const {return (PathElement*)((PBYTE) m_path + m_pos);}
			void			Step(){m_pos += Current()->pe_length;}
		};						// ParsedPathname iterator

	class CFile
		{						// CFile
		public:
			CFile(CLpfs* fs, DirectoryEntry* ep, ULONG dirsector);
			~CFile();

			CFile*	m_next;		// next open file
			CFile*	m_prev;		// previous open file
			CLpfs*	m_fs;		// owning file system object
			ULONG	m_direntry;	// sector where directory entry is
			ULONG	m_size;		// current size of file
			ULONG	m_pos;		// current position in file
			ULONG	m_sector;	// sector where file is located
			BYTE	m_flags;	// flags

			enum FILEFLAGS {
				FF_OUTPUT = 0x01,	// opened for output
				};
		};						// CFile

	class CScanPos
		{						// CScanPos
		public:
			CScanPos(CLpfs* p){fs = p;}
			~CScanPos(){}
			
			CLpfs* fs;			// containing file system object
			int namelen;		// length of long name
			int matchsemantics;	// match semantcis for IFSMgr_MetaMatch
			BOOL hasdot;		// does long name have a dot in it?
			ULONG sector;		// current directory entry
			ULONG lastsector;	// last directory entry
			DWORD attr;			// attributes from original FindFirst
			USHORT pattern[LFNMAXNAMELEN+1]; // search pattern
			BYTE excludemask;	// exlude files haveing any of these attributes

			int Prepare(pioreq pir, DirectoryEntry* ep);
			int FindNext(DirectoryEntry* ep);
		};						// CScanPos

	virtual BOOL	OurVolume(pioreq pir);
	virtual void	GetVolumeLabel(PDWORD pVolSer, char* pVolLabel);
	virtual BOOL	SameVolume(CLocalFileSystem* fs);
	BOOL			FindDirectoryEntry(ParsedPath* path, DirectoryEntry* ep, ULONG& sector, BOOL wantfile = TRUE);
	void			GetRootDirectoryEntry(DirectoryEntry* ep, ULONG& sector);
	BOOL			FindNextDirectoryEntry(const CPosition pos, DirectoryEntry* ep, ULONG& sector);
	virtual void	TruncateFile(CFile* fp);
	void			FindFill(_WIN32_FIND_DATA* fdp, DirectoryEntry* ep);
	
	static CFileSystem* CreateNew();

	int				m_error;		// error code to return
	CFile*			m_openfiles;	// anchor of open file list

	// Request function overrides:

	#undef vt
	#define vt(f) virtual int f(pioreq pir);
	
	vt(DeleteFile)
	vt(Dir)
	vt(FileAttributes)
	vt(FlushVolume)
	vt(GetDiskInfo)
	vt(OpenFile)
	vt(RenameFile)
	vt(SearchFile)
	vt(QueryResourceInfo)
	vt(GetDiskParms)
	vt(FindFirstFile)

	vt(FindNextFile)
	vt(FindClose)

	vt(ReadFile)
	vt(WriteFile)
	vt(FileSeek)
	vt(CloseFile)
	vt(EnumerateHandle)
	vt(FileDateTime)
};								// CLpfs

#endif // LPFS_H
