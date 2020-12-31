// LocalFileSystem.h -- Interface for the CLocalFileSystem class
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef LOCALFILESYSTEM_H
#define LOCALFILESYSTEM_H

#include "FileSystem.h"			// base class dcls

#ifndef SETINITSEG
#define SETINITSEG
#pragma warning(disable:4075) // nonstandard init seg
#pragma init_seg("INITCODE")
#pragma warning(default:4075)
#endif

///////////////////////////////////////////////////////////////////////////////
// CLocalFileSystem

class CLocalFileSystem : public CFileSystem
{								// CLocalFileSystem
public:
	CLocalFileSystem();
	virtual ~CLocalFileSystem();

	CLocalFileSystem*	m_next;	// next instance
	CLocalFileSystem*	m_prev;	// previous instance
	PVRP		m_vrp;			// volume we think is mounted now
	PVOID		m_dpb;			// DOS drive parameter block
	HVM			m_lockowner;	// which VM owns the lock on this volume
	BYTE		m_drive;		// drive letter
	BYTE		m_origdrive;	// original drive letter
	BYTE		m_outstanding;	// # outstanding IORs
	BYTE		m_flags;		// flags

	enum LFSFLAGS {
		VOLLOCKED = 0x01,		// volume is locked
		};

	static BOOL MountVolumeThunk(pioreq pir);
	static CFileSystem* CreateNew();
	static BOOL	Register(CFileSystem* (*createnew)());
	static void OnCommandComplete(PIOR ior);
	static CLocalFileSystem* First;

	PIOR		CreateIOR(DWORD flags = 0);
	PIOR		CreateIOR(DWORD opcode, DWORD flags);
	void		DestroyIOR(PIOR ior);
	void		SatisfyCriteria(PIOR ior);
	void		SendCommand(PIOR ior);
	void		SendCommandAndWait(PIOR ior);
	PBYTE		ReadBootSector();
	int			ReadSectorNow(ULONG sector, PBYTE buffer);
	int			WriteSectorNow(ULONG sector, PBYTE buffer);
	BOOL		ReadOnly();

	// Overridable member functions:

	virtual int	MountVolume(pioreq pir);	// can override, but shouldn't need to
	virtual int	VerifyVolume(pioreq pir);	// can override, but shouldn't need to
	virtual int	UnloadVolume(pioreq pir);	// should override
	virtual int	MountChildVolume(pioreq pir);
	virtual int	MapDrive(pioreq pir);		// can override, but shouldn't need to
	virtual int	UnmapDrive(pioreq pir);		// can override, but shouldn't need to

	virtual BOOL	OurVolume(pioreq pir);	// MUST OVERRIDE
	virtual BOOL	SameVolume(CLocalFileSystem* old); // MUST OVERRIDE
	virtual void	GetVolumeLabel(PDWORD pVolSer, char* pVolLabel); // MUST OVERRIDE

	// Overrides of base-class request functions

	virtual int		Ioctl16Drive(pioreq pir);
	virtual int		DirectDiskIO(pioreq pir);
};								// CLocalFileSystem

#endif // LOCALFILESYSTEM_H