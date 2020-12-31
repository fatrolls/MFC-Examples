// LocalFileSystem.cpp -- Implementation of CLocalFileSystem
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

#include "LocalFileSystem.h"
#include "crs.h"				// for IOCTL handling

///////////////////////////////////////////////////////////////////////////////

CLocalFileSystem* CLocalFileSystem::First = NULL;

CLocalFileSystem::CLocalFileSystem()
	{							// CLocalFileSystem::CLocalFileSystem
	m_outstanding = 0;
	m_flags = 0;
	m_lockowner = NULL;

	m_next = First;
	m_prev = NULL;
	if (First)
		First->m_prev = this;
	First = this;
	}							// CLocalFileSystem::CLocalFileSystem

CLocalFileSystem::~CLocalFileSystem()
	{							// CLocalFileSystem::~CLocalFileSystem
	ASSERT(m_outstanding == 0);
	if (m_next)
		m_next->m_prev = m_prev;
	if (m_prev)
		m_prev->m_next = m_next;
	else
		First = m_next;
	}							// CLocalFileSystem::~CLocalFileSystem

BOOL CLocalFileSystem::Register(CFileSystem* (*createnew)())
	{							// CLocalFileSystem::Register
	if (!CFileSystem::Register(createnew))
		return FALSE;
	if (IFSMgr_Get_Version() < IFSMGRVERSION)
		return FALSE;			// we're running on a back-level system
	if ((ProviderId = IFSMgr_RegisterMount(MountVolumeThunk, IFSMGRVERSION, NORMAL_FSD)) < 0)
		return FALSE;
	return TRUE;
	}							// CLocalFileSystem::Register

CFileSystem* CLocalFileSystem::CreateNew()
	{							// CLocalFileSystem::CreateNew
	return new CLocalFileSystem;
	}							// CLocalFileSystem::CreateNew

///////////////////////////////////////////////////////////////////////////////
// MountVolumeThunk is a static member function that interfaces between
// IFS and our volume-handling member functions

int CLocalFileSystem::MountVolumeThunk(pioreq pir)
	{							// CLocalFileSystem::MountVolumeThunk
	pir->ir_error = ERROR_ACCESS_DENIED; // assume error

	switch (pir->ir_flags)
		{						// select volume mount function

	case IR_FSD_MOUNT:
		{						// IR_FSD_MOUNT
		// For reasons I don't understand, actually accessing my C-drive
		// during the initial mount request causes weird downstream
		// behavior from IOS, followed by a crash.

		if (pir->ir_mntdrv == 2)
			break;				// ignore C-drive (?)

		CLocalFileSystem* lfs = (CLocalFileSystem*) (*CreateNewFcn)();
		lfs->m_vrp = (PVRP) pir->ir_volh;
		lfs->m_drive = lfs->m_origdrive = (BYTE) pir->ir_mntdrv;
		lfs->m_dpb = pir->ir_rh;
		if ((pir->ir_error = lfs->MountVolume(pir)) == 0)
			{					// successfully mounted
			pir->ir_rh = (rh_t) lfs;
			lfs->m_vrp->VRP_fsd_hvol = (ULONG) lfs;
			lfs->m_vrp->VRP_fsd_entry = (ULONG) MountVolumeThunk;
			}					// successfully mounted
		else
			delete lfs;			// error trying to mount volume
		break;
		}						// IR_FSD_MOUNT

	case IR_FSD_VERIFY:
		{						// IR_FSD_VERIFY
		CLocalFileSystem* lfs = (CLocalFileSystem*) CreateNew();
		CLocalFileSystem* old = (CLocalFileSystem*) pir->ir_drvh; // undoc!
		lfs->m_drive = lfs->m_origdrive = old->m_drive;
		lfs->m_vrp = old->m_vrp;
		pir->ir_error = lfs->VerifyVolume(pir);
		delete lfs;				// used just for verification
		break;
		}						// IR_FSD_VERIFY

	case IR_FSD_UNLOAD:
		{						// IR_FSD_UNLOAD
		CLocalFileSystem* lfs = (CLocalFileSystem*) pir->ir_drvh; // undoc!
		pir->ir_error = lfs->UnloadVolume(pir);

		// Note that the file system object gets deleted by
		// DisconnectResource later on
		break;
		}						// IR_FSD_UNLOAD

	case IR_FSD_MOUNT_CHILD:
		{						// IR_FSD_MOUNT_CHILD
		CLocalFileSystem* lfs = (CLocalFileSystem*) pir->ir_rh;
		pir->ir_error = lfs->MountChildVolume(pir);
		break;
		}						// IR_FSD_MOUNT_CHILD

	case IR_FSD_MAP_DRIVE:
		{						// IR_FSD_MAP_DRIVE
		CLocalFileSystem* lfs = (CLocalFileSystem*) pir->ir_rh;
		pir->ir_error = lfs->MapDrive(pir);
		break;
		}						// IR_FSD_MAP_DRIVE

	case IR_FSD_UNMAP_DRIVE:
		{						// IR_FSD_UNMAP_DRIVE
		CLocalFileSystem* lfs = (CLocalFileSystem*) pir->ir_rh;
		pir->ir_error = lfs->UnmapDrive(pir);
		break;
		}						// IR_FSD_UNMAP_DRIVE

	default:
		ASSERT(!"Invalid FS_MountVolume function");
		break;
		}						// select volume mount function

	return pir->ir_error;
	}							// CLocalFileSystem::MountVolumeThunk

///////////////////////////////////////////////////////////////////////////////
// IFSMGR calls MountVolume to see if a logical volume contains our
// file system.

int CLocalFileSystem::MountVolume(pioreq pir)
	{							// CLocalFileSystem::MountVolume
	if (!OurVolume(pir))
		return ERROR_ACCESS_DENIED;

	// Check for this being a duplicate of a volume that's already
	// mounted

	for (CLocalFileSystem* fs = First; fs; fs = fs->m_next)
		if (fs != this && SameVolume(fs))
			return ERROR_IFSVOL_EXISTS;

	#undef vt	
	#define vt(f) f##Thunk,
	
	static volfunc volfuncs = {
		IFSMGRVERSION,			// vfn_version
		IFS_REVISION,			// vfn_revision
		NUM_VOLFUNC, {			// vfn_size
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
		vt(EmptyFunc)
		vt(Ioctl16Drive)
		vt(GetDiskParms)
		vt(FindFirstFile)
		vt(DirectDiskIO)
		}};
	
	pir->ir_vfunc = &volfuncs;
	return 0;
	}							// CLocalFileSystem::MountVolume

///////////////////////////////////////////////////////////////////////////////
// VOLTRACK calls VerifyVolume directly if the port driver reports that
// the media in the drive has changed. The undocumented entry conditions
// are as follows:
//		ir_drvh -> our handle (i.e., CLocalFileSystem*) for the volume that used to be mounted
//		ir_data -> 256-byte area to receive the new volume label
// We are supposed to exit with a zero return code if the same volume
// is still mounted on this device. VFAT also sets ir_aux2 to the 32-bit
// volume serial number from the boot sector and copies the volume label
// to the ir_data area, but VOLTRACK doesn't actually use that info.

int CLocalFileSystem::VerifyVolume(pioreq pir)
	{							// CLocalFileSystem::VerifyVolume
	if (SameVolume((CLocalFileSystem*) pir->ir_drvh))
		return 0;
	GetVolumeLabel((PDWORD) &pir->ir_aux2.aux_ul, (char*) pir->ir_data);
	return -1;
	}							// CLocalFileSystem::VerifyVolume

///////////////////////////////////////////////////////////////////////////////
// Someone (?) calls UnloadVolume directly to unconditionally dismount a
// volume. In general, you need to flush any caches and cleanup any other
// resources you're holding on behalf of the volume. The undocumented
// entry condition is:
//		ir_drvh -> our handle (i.e., CLocalFileSystem*) for the volume to unload

int CLocalFileSystem::UnloadVolume(pioreq pir)
	{							// CLocalFileSystem::UnloadVolume
	return 0;
	}							// CLocalFileSystem::UnloadVolume

///////////////////////////////////////////////////////////////////////////////
// MountChildVolume is for mounting a volume that's really a file located on
// some other volume. The differences between these two functions in VFAT
// are very small (basically, VFAT does its removable volume label smashing
// and DPB lookup only for a parent volume). If you don't do either of these
// things, you can just use the same function for both parent and child mounts.

int CLocalFileSystem::MountChildVolume(pioreq pir)
	{							// CLocalFileSystem::MountChildVolume
	return MountVolume(pir);
	}							// CLocalFileSystem::MountChildVolume

///////////////////////////////////////////////////////////////////////////////
// Someone (?) calls MapDrive to change the drive letter under which we
// access a volume. The partially documented entry conditions are:
//		ir_rh		-> our handle (i.e., CLocalFileSystem*) for the volume
//		ir_options	=  new drive letter
//		ir_pos		=  original drive letter (an undocumented fact)

int CLocalFileSystem::MapDrive(pioreq pir)
	{							// CLocalFileSystem::MapDrive
	m_drive = (BYTE) pir->ir_options;
	m_origdrive = (BYTE) pir->ir_pos; // undoc!
	return 0;
	}							// CLocalFileSystem::MapDrive

///////////////////////////////////////////////////////////////////////////////
// Someone (?) calls UnmapDrive directly to restore the original drive letter.
// The undocumented entry condition is:
//		ir_rh -> our handle (i.e., CLocalFileSystem*) for the volume

int CLocalFileSystem::UnmapDrive(pioreq pir)
	{							// CLocalFileSystem::UnmapDrive
	m_drive = m_origdrive;
	return 0;
	}							// CLocalFileSystem::UnmapDrive

///////////////////////////////////////////////////////////////////////////////
// These base-class functions should be overriden to provide customized handling
// for your file system:

BOOL CLocalFileSystem::OurVolume(pioreq pir)
	{							// CLocalFileSystem::OurVolume
	ASSERT(!"Using base-class OurVolume");	// you need to override this function
	return FALSE;
	}							// CLocalFileSystem::OurVolume

BOOL CLocalFileSystem::SameVolume(CLocalFileSystem* old)
	{							// CLocalFileSystem::SameVolume
	ASSERT(!"Using base-class SameVolume");	// you need to override this function
	return TRUE;
	}							// CLocalFileSystem::SameVolume

void CLocalFileSystem::GetVolumeLabel(PDWORD pVolSer, char* pVolLabel)
	{							// CLocalFileSystem::GetVolumeLabel
	ASSERT(!"Using base-class SameVolume");	// you need to override this function
	*pVolSer = 0xDEADF00D;
	strcpy(pVolLabel, "NO NAME");
	}							// CLocalFileSystem::GetVolumeLabel

///////////////////////////////////////////////////////////////////////////////

PIOR CLocalFileSystem::CreateIOR(DWORD flags /* = 0 */)
	{							// CLocalFileSystem::CreateIOR
	ASSERT(m_vrp != NULL);
	if (!m_vrp)
		return NULL;			// no VRP?

	DWORD size = m_vrp->VRP_max_req_size + m_vrp->VRP_max_sgd * sizeof(SGD);
	DWORD offset = m_vrp->VRP_delta_to_ior;
	PIOR ior = IspCreateIor((USHORT) size, (USHORT) offset, ISP_M_FL_MUST_SUCCEED);
	if (!ior)
		return NULL;

	ior->IOR_next = 0;					// used for request queueing by lots of downstream people
	ior->IOR_start_addr[1] = 0;			// assume only 32-bits worth of sector number
	ior->IOR_flags = IORF_VERSION_002 | flags;	// this is how IOS knows we're giving it a new-style IOR
	ior->IOR_private_client = offset;	// a common use for this field
	ior->IOR_req_vol_handle = (ULONG) m_vrp;
	ior->IOR_sgd_lin_phys = (ULONG) (ior + 1); // where scatter/gather descriptors can be built
	ior->IOR_num_sgds = 0;				// incremented by criteria routine, so must start at zero
	ior->IOR_vol_designtr = m_drive;	// drive number

	++m_outstanding;

	return ior;
	}							// CLocalFileSystem::CreateIOR

PIOR CLocalFileSystem::CreateIOR(DWORD opcode, DWORD flags)
	{							// CLocalFileSystem::CreateIOR
	PIOR ior = CreateIOR(flags);
	if (ior)
		ior->IOR_func = (USHORT) opcode;
	return ior;
	}							// CLocalFileSystem::CreateIOR

///////////////////////////////////////////////////////////////////////////////

void CLocalFileSystem::DestroyIOR(PIOR ior)
	{							// CLocalFileSystem::DestroyIOR
	ASSERT(ior != NULL);
	ASSERT(m_vrp && ior->IOR_private_client == m_vrp->VRP_delta_to_ior);
	ASSERT(m_outstanding > 0);
	--m_outstanding;
	IspDeallocMem((PVOID) ((DWORD) ior - ior->IOR_private_client));
	}							// CLocalFileSystem::DestroyIOR

///////////////////////////////////////////////////////////////////////////////

void CLocalFileSystem::SatisfyCriteria(PIOR ior)
	{							// CLocalFileSystem::SatisfyCriteria
	ASSERT(ior != NULL);
	if (IlbIoCriteria(ior) != 0)
		ior->IOR_flags |= IORF_DOUBLE_BUFFER;
	}							// CLocalFileSystem::SatisfyCriteria

///////////////////////////////////////////////////////////////////////////////

void CLocalFileSystem::SendCommand(PIOR ior)
	{							// CLocalFileSystem::SendCommand
	ASSERT(ior != NULL);
	ASSERT(m_vrp != NULL);

	// All of the Microsoft FSDs make the following adjustment to the
	// starting sector. Rather than figure out why, I elected to
	// just parrot them.
	
	if (m_vrp->VRP_demand_flags & VRP_dmd_removable_supp)
		{						// use physical sector
		ior->IOR_flags &= ~IORF_LOGICAL_START_SECTOR;
		ior->IOR_start_addr[0] += m_vrp->VRP_partition_offset;
		}						// use physical sector
	else
		ior->IOR_flags |= IORF_LOGICAL_START_SECTOR;

	// There's a comment in DEVIOCTL.ASM (part of the VDEF sample) to
	// the effect that IOS hoses EDI even when it shouldn't. This
	// seems pretty astounding, but let's assume the comment is
	// right

	_asm push edi
	
	IOS_SendCommand(ior, (PDCB) m_vrp->VRP_device_handle);

	_asm pop edi
	}							// CLocalFileSystem::SendCommand

///////////////////////////////////////////////////////////////////////////////

#define IOR_completion_flag _ureq._IOR_requestor_usage[0]

void CLocalFileSystem::SendCommandAndWait(PIOR ior)
	{							// CLocalFileSystem::SendCommandAndWait
	if (ior->IOR_flags & IORF_SYNC_COMMAND)
		SendCommand(ior);

	// The following logic for doing an asynchronous command is essentially
	// lifted right out of VFAT

	else
		{						// handle command asynchronously
		ior->IOR_completion_flag = 0;
		ior->IOR_callback = (CMDCPLT) OnCommandComplete;
		ior->IOR_req_req_handle = (ULONG) ior;
		SendCommand(ior);

		while (TRUE)
			{					// wait for command to finish
			_asm cli			// prevent signal until after we block
			if (ior->IOR_completion_flag)
				break;			// it's done
			IFSMgr_Block((ULONG) &ior->IOR_completion_flag);
			}					// wait for command to finish
		_asm sti
		}						// handle command asynchronously
	}							// CLocalFileSystem::SendCommandAndWait

void CLocalFileSystem::OnCommandComplete(PIOR ior)
	{							// CLocalFileSystem::OnCommandComplete
	ior->IOR_completion_flag = 1;
	IFSMgr_Wakeup((ULONG) &ior->IOR_completion_flag);
	}							// CLocalFileSystem::OnCommandComplete

///////////////////////////////////////////////////////////////////////////////

PBYTE CLocalFileSystem::ReadBootSector()
	{							// CLocalFileSystem::ReadBootSector
	PBYTE buffer = (PBYTE) _HeapAllocate(m_vrp->VRP_block_size, 0);
	if (!buffer)
		return NULL;			// can't get memory for boot sector
	if (ReadSectorNow(0, buffer))
		{						// request had error
		_HeapFree(buffer, 0);
		return NULL;
		}						// request had error
	return buffer;
	}							// CLocalFileSystem::ReadBootSector

///////////////////////////////////////////////////////////////////////////////

int CLocalFileSystem::ReadSectorNow(ULONG sector, PBYTE buffer)
	{							// CLocalFileSystem::ReadSectorNow
	PIOR ior = CreateIOR(IOR_READ, IORF_BYPASS_VOLTRK | IORF_HIGH_PRIORITY);
	ASSERT(!(ior->IOR_flags & (IORF_CHAR_COMMAND | IORF_SCATTER_GATHER))); // don't set these flags!
	ior->IOR_start_addr[0] = sector;
	ior->IOR_buffer_ptr = (ULONG) buffer;
	ior->IOR_xfer_count = 1;
	SatisfyCriteria(ior);
	SendCommandAndWait(ior);
	int status = (int) ior->IOR_status;
	DestroyIOR(ior);

	if (status >= IORS_ERROR_DESIGNTR)
		return IOSMapIORSToI21(status);
	else
		return 0;
	}							// CLocalFileSystem::ReadSectorNow

///////////////////////////////////////////////////////////////////////////////

int CLocalFileSystem::WriteSectorNow(ULONG sector, PBYTE buffer)
	{							// CLocalFileSystem::WriteSectorNow
	PIOR ior = CreateIOR(IOR_WRITE, IORF_BYPASS_VOLTRK | IORF_HIGH_PRIORITY);
	ASSERT(!(ior->IOR_flags & (IORF_CHAR_COMMAND | IORF_SCATTER_GATHER))); // don't set these flags!
	ior->IOR_start_addr[0] = sector;
	ior->IOR_buffer_ptr = (ULONG) buffer;
	ior->IOR_xfer_count = 1;
	SatisfyCriteria(ior);
	SendCommandAndWait(ior);
	int status = (int) ior->IOR_status;
	DestroyIOR(ior);
	
	if (status >= IORS_ERROR_DESIGNTR)
		return IOSMapIORSToI21(status);
	else
		return 0;
	}							// CLocalFileSystem::WriteSectorNow

///////////////////////////////////////////////////////////////////////////////
// Most file systems simply pass IOCTL requests along to the disk drive.
// The following code came directly from the VDEF sample:

int CLocalFileSystem::Ioctl16Drive(pioreq pir)
	{							// CLocalFileSystem::Ioctl16Drive
	if ((m_flags & VOLLOCKED) && m_lockowner != Get_Cur_VM_Handle())
		return pir->ir_error = ERROR_ACCESS_DENIED;
	PIOR ior = CreateIOR(IOR_GEN_IOCTL, IORF_SYNC_COMMAND);
	if (!ior)
		return pir->ir_error = ERROR_NOT_ENOUGH_MEMORY;

	// macro to simplify grossly long field name access:
	#define ioctl(f) ior->_ureq.sdeffsd_req_usage._IOR_ioctl_##f
	
	CLIENT_STRUCT* pRegs = (CLIENT_STRUCT*) pir->ir_cregptr;	
	ioctl(client_params) = (ULONG) pRegs;
	ioctl(function) = _ClientAX;
	ASSERT(_ClientBL-1 == m_drive);
	ioctl(drive) = m_drive;
	ioctl(control_param) = _ClientCX;

	if (pir->ir_options & IOCTL_PKT_LINEAR_ADDRESS)
		ioctl(buffer_ptr) = (ULONG) pir->ir_data; // flat buffer address
	else
		{						// 16-bit IOCTL
		ior->IOR_flags |= IORF_16BIT_IOCTL;
		ioctl(buffer_ptr) = (ULONG) Client_Ptr_Flat(DS, DX);
		}						// 16-bit IOCTL

	SendCommandAndWait(ior);	// send IOCTL and wait for it to finish
	USHORT status = ior->IOR_status;
	_ClientAX = (USHORT) ioctl(return);
	DestroyIOR(ior);

	if (status >= IORS_ERROR_DESIGNTR)	
		status = (USHORT) IOSMapIORSToI21(status);
	else
		status = 0;				// success after error is still success

	return pir->ir_error = (int) status;
	}							// CLocalFileSystem::Ioctl16Drive

///////////////////////////////////////////////////////////////////////////////

BOOL CLocalFileSystem::ReadOnly()
	{							// CLocalFileSystem::ReadOnly
	return (m_vrp->VRP_event_flags & VRP_ef_write_protected) != 0;
	}							// CLocalFileSystem::ReadOnly

///////////////////////////////////////////////////////////////////////////////

int CLocalFileSystem::DirectDiskIO(pioreq pir)
	{							// CLocalFileSystem::DirectDiskIO
	DWORD opcode;
	DWORD pageflags = PAGEMAPGLOBAL;
	DWORD iorflags = IORF_BYPASS_VOLTRK | IORF_HIGH_PRIORITY | IORF_SYNC_COMMAND;

	switch (pir->ir_flags)
		{						// switch on function code
	case DIO_ABS_READ_SECTORS:
		opcode = IOR_READ;
		pageflags |= PAGEMARKDIRTY;
		break;
	case DIO_ABS_WRITE_SECTORS:
		opcode = IOR_WRITE;
		break;
	case DIO_SET_LOCK_CACHE_STATE:
		return pir->ir_error = 0; // ignore this request
		}						// switch on function code

	// Lock the memory pages that are involved in the operation

	DWORD nbytes = pir->ir_length * m_vrp->VRP_block_size;
	if (!nbytes)
		return pir->ir_error = 0;	// do nothing if nothing to transfer

	DWORD buffer = (DWORD) pir->ir_data;
	DWORD firstpage = buffer >> 12;
	DWORD npages = ((buffer + nbytes - 1) >> 12) - firstpage + 1;
	DWORD locked = _LinPageLock(firstpage, npages, pageflags);
	if (locked)
		pir->ir_data = (ubuffer_t) ((locked & ~4095) | (buffer & 4095));
	else
		iorflags |= IORF_DOUBLE_BUFFER;

	// Build and execute an I/O request block

	PIOR ior = CreateIOR(opcode, iorflags);
	ior->IOR_xfer_count = pir->ir_length;
	ior->IOR_start_addr[0] = pir->ir_pos;
	ior->IOR_buffer_ptr = (DWORD) pir->ir_data;
	SatisfyCriteria(ior);
	SendCommandAndWait(ior);
	pir->ir_error = (short) ((ior->IOR_status >= IORS_ERROR_DESIGNTR) ? IOSMapIORSToI24(ior->IOR_status, opcode) : 0);
	DestroyIOR(ior);

	// Unlock the memory pages involved in the operation

	if (locked)
		_LinPageUnlock(locked >> 12, npages, PAGEMAPGLOBAL);

	return pir->ir_error;
	}							// CLocalFileSystem::DirectDiskIO

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
