// RAMDISK.C -- Sample Port Driver
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#include "iosdcls.h"			// VMM and IOS headers
#pragma hdrstop

#include "ramdisk.h"

VOID OnRequest(PIOP iop);		// I/O request processor

///////////////////////////////////////////////////////////////////////////////
// Static data

#pragma VxD_LOCKED_DATA_SEG

int ndevices = 0;				// # devices we've found

#pragma VxD_PAGEABLE_DATA_SEG

///////////////////////////////////////////////////////////////////////////////
// Initialization code and data

#pragma VxD_INIT_CODE_SEG

extern DRP theDRP;				// device registration packet

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	ASSERT(ndevices == 0);
	IOS_Register(&theDRP);
	return theDRP.DRP_reg_result == DRP_REMAIN_RESIDENT;
	}							// OnSysDynamicDeviceInit

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Asynchronous event processing:

#pragma VxD_LOCKED_CODE_SEG
#pragma VxD_LOCKED_DATA_SEG
#undef CURSEG
#define CURSEG() LCODE

USHORT OnInitialize(PAEP_bi_init aep);
USHORT OnBootComplete(PAEP_boot_done aep);
USHORT OnConfigDcb(PAEP_dcb_config aep);
USHORT OnUnconfigDcb(PAEP_dcb_unconfig aep);
USHORT OnDeviceInquiry(PAEP_inquiry_device aep);
USHORT OnUninitialize(PAEP_bi_uninit aep);

VOID OnAsyncRequest(PAEP aep)
	{							// OnAsyncEvent
	typedef USHORT (*PEF)(PAEP);
	static PEF evproc[AEP_MAX_FUNC+1] =
		{(PEF) OnInitialize		//  0 AEP_INITIALIZE
		,NULL					//  1 AEP_SYSTEM_CRIT_SHUTDOWN
		,(PEF) OnBootComplete	//  2 AEP_BOOT_COMPLETE
		,(PEF) OnConfigDcb		//  3 AEP_CONFIG_DCB
		,(PEF) OnUnconfigDcb	//  4 AEP_UNCONFIG_DCB
		,NULL					//  5 AEP_IOP_TIMEOUT
		,(PEF) OnDeviceInquiry	//  6 AEP_DEVICE_INQUIRY
		,NULL					//  7 AEP_HALF_SEC
		,NULL					//  8 AEP_1_SEC
		,NULL					//  9 AEP_2_SECS
		,NULL					// 10 AEP_4_SECS
		,NULL					// 11 AEP_DBG_DOT_CMD
		,NULL					// 12 AEP_ASSOCIATE_DCB
		,NULL					// 13 AEP_REAL_MODE_HANDOFF
		,NULL					// 14 AEP_SYSTEM_SHUTDOWN
		,(PEF) OnUninitialize	// 15 AEP_UNINITIALIZE
		,NULL					// 16 AEP_DCB_LOCK
		,NULL					// 17 AEP_MOUNT_VERIFY
		,NULL					// 18 AEP_CREATE_VRP
		,NULL					// 19 AEP_DESTROY_VRP
		,NULL					// 20 AEP_REFRESH_DRIVE
		,NULL					// 21 AEP_PEND_UNCONFIG_DCB
		,NULL					// 22 AEP_1E_VEC_UPDATE
		,NULL					// 23 AEP_CHANGE_RPM
		};
	PEF proc;

	ASSERT(aep->AEP_func < arraysize(evproc));

	if (aep->AEP_func < arraysize(evproc) && (proc = evproc[aep->AEP_func]))
		aep->AEP_result = proc(aep);
	else
		aep->AEP_result = (USHORT) AEP_FAILURE;
	}							// OnAsyncEvent

///////////////////////////////////////////////////////////////////////////////
// AEP_INITIALIZE asks us to initialize the controller and to obtain and
// initialize a Device Data Block (DDB) describing the controller

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnInitialize(PAEP_bi_init aep)
	{							// OnInitialize
	PRAMDISKDDB ddb;			// pointer to new device descriptor block

	if (!(ddb = (PRAMDISKDDB) IspCreateDdb(sizeof(RAMDISKDDB), 0)))
		return (USHORT) AEP_FAILURE;		// couldn't create DDB

	return AEP_SUCCESS;
	}							// OnInitialize

///////////////////////////////////////////////////////////////////////////////
// AEP_BOOT_COMPLETE asks us if we want to stay loaded or not.

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnBootComplete(PAEP_boot_done aep)
	{							// OnBootComplete
	return ndevices ? AEP_SUCCESS : AEP_FAILURE; // unload if no devices
	}							// OnBootComplete

///////////////////////////////////////////////////////////////////////////////
// AEP_CONFIG_DCB asks us to configure a Device Control Block (DCB) for a
// single physical device. A real driver fills in geometry information. We do
// that plus allocate a block of memory to contain the data for the drive

#pragma VxD_PAGEABLE_CODE_SEG

void InitRamDisk(DWORD base, DWORD nsec);

USHORT OnConfigDcb(PAEP_dcb_config aep)
	{							// OnConfigDcb
	PDCB dcb = (PDCB) aep->AEP_d_c_dcb;
	ASSERT(dcb);
	if (!(dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL))
		return AEP_SUCCESS;		// only configure physical DCBs
	ASSERT(memcmp(dcb->DCB_vendor_id, "WALTONEY", 8) == 0);

	// We need a place to save the address of the memory block we'll
	// allocate. Use the DCB_Port_Specific field for this purpose. The
	// IOS architecture really should have provided for per-level data storage
	// similar to how I/O request packets, but they didn't. It would be too bad
	// if several port-level drivers all tried to use this same field!

	if (!(dcb->DCB_Port_Specific = (ULONG) _PageAllocate(2048, PG_SYS,
		NULL, 0, 0, 0, NULL, PAGEZEROINIT | PAGELOCKEDIFDP)))
		return (USHORT) AEP_FAILURE;		// can't get memory for device

	InitRamDisk(dcb->DCB_Port_Specific, 4096);	// initialize like a disk

	dcb->DCB_cmn.DCB_device_type = DCB_type_disk;	// we are a disk
	dcb->DCB_cmn.DCB_device_flags |= DCB_DEV_WRITEABLE;

	// Fill in the actual geometry of the drive and set a flag for
	// the TSD that we've done so
	
	dcb->DCB_max_xfer_len = 0xFFFFFFFF;
	dcb->DCB_actual_sector_cnt[0] = 4096; // 4096 * 512 = 2 MB
	dcb->DCB_actual_sector_cnt[1] = 0;
	dcb->DCB_actual_blk_size = 512;
	dcb->DCB_actual_head_cnt = 1;
	dcb->DCB_actual_cyl_cnt = 1;
	dcb->DCB_actual_spt = 4096;
	dcb->DCB_cmn.DCB_TSD_Flags |= DCB_TSD_ACTUAL_PRE_SET;

	// Add our request processing routine to the calldown stack for
	// the device.

	if (!(IspInsertCalldown(dcb, OnRequest, (PDDB) aep->AEP_d_c_hdr.AEP_ddb, 0,
		dcb->DCB_cmn.DCB_dmd_flags | DCB_dmd_serialize,
		 aep->AEP_d_c_hdr.AEP_lgn)))
		return (USHORT) AEP_FAILURE;

	++ndevices;					// this will cause us to stay loader after next AEP_BOOT_COMPLETE
	return AEP_SUCCESS;
	}							// OnConfigDcb

// Helper routine to initialize a block of memory as a RAM disk

void InitRamDisk(DWORD base, DWORD nsec)
	{							// InitRamDisk
	#pragma pack(1)

	typedef struct tagBPB
		{						// BIOS parameter block
		WORD secsize;			// 00 sector size
		BYTE clustsize;			// 02 cluster size (in sectors)
		WORD numrsv;			// 03 # reserved sectors
		BYTE numfat;			// 05 # FATs
		WORD numfiles;			// 06 # entries in root directory
		WORD numsectors;		// 08 # sectors on disk
		BYTE media;				// 0A media descriptor
		WORD fatsectors;		// 0B # sectors in each FAT
		} BPB, *PBPB;			// BIOS parameter block [0D]

	typedef struct tagPARTITION
		{						// partition record
		BYTE indicator;			// 00 boot indicator (80 = active partition)
		BYTE starthead;			// 01 start head
		BYTE startsec;			// 02 bits 0-5: start sector, bits 6-7: bits 8-9 of start track
		BYTE starttrack;		// 03 bits 0-7 of start track
		BYTE parttype;			// 04 partition type
		BYTE endhead;			// 05 end head
		BYTE endsec;			// 06 end sector
		BYTE endtrack;			// 07 end track
		DWORD bias;				// 08 sector bias to start of partition
		DWORD partsize;			// 0C partition size in sectors
		} PARTITION, *PPARTITION;

	typedef struct tagBOOTSECT
		{						// boot sector
		BYTE jmpinst[3];		//  00 JMP to boot code
		char vendid[8];			//  03 vendor id
		struct tagBPB;			//  0B bios parameter block
		WORD tracksectors;		//  18 # sectors per track
		WORD numtracks;			//  1A # heads (tracks)
		DWORD numhidden;		//  1C # hidden sectors
		DWORD totsectors;		//  20 # sectors if disk > 32 MB
		BYTE drive;				//  24 physical drive #
		BYTE rsv1;				//  25 reserved
		BYTE xboot;				//  26 extended boot signature (29h)
		DWORD volid;			//  27 volume ID
		char label[11];			//  2B volume label
		char fattype[8];		//  36 FAT12 or FAT16 plus 3 spaces
		BYTE junk[384];			//  3E other stuff, including bootstrap loader
		PARTITION part[4];		// 1BE partition table
		WORD signature;			// 1FE signature (0xAA55)
		} BOOTSECT, *PBOOTSECT; // boot sector [200]
	
	#pragma pack()

	PBOOTSECT bsp = (PBOOTSECT) base;
	PWORD fat = (PWORD) (base + 512);

	// Fill in dummy boot sector so we look like a disk

	ASSERT(!(nsec & 0xFFFF0000)); // else too big for BPB format

	bsp->jmpinst[0] = 0xEB;
	bsp->jmpinst[1] = 0x3C;
	bsp->jmpinst[2] = 0x90;
	memcpy(bsp->vendid, "WALTONEY", 8);
	bsp->secsize = 512;					// each sector is 512 bytes long
	bsp->clustsize = 1;					// one sector per cluster
	bsp->numrsv = 1;					// no reserved sectors besides this one
	bsp->numfat = 1;					// one FAT should be enough
	bsp->numfiles = 128;				// more than enough to prove the point!
	bsp->numsectors = 0;				// fill in totsectors instead
	bsp->media = 0xF8;					// claim we're a fixed disk
	bsp->fatsectors = (WORD) ((nsec + nsec + 511) / 512);
	bsp->tracksectors = (WORD) nsec;	// only 1 track, so all sectors are on it
	bsp->numtracks = 1;					// 1 track
	bsp->numhidden = 0;					// no hidden sectors
	bsp->totsectors = nsec;				// this many sectors
	bsp->drive = 0x80;					// flag for a hard drive
	bsp->xboot = 0x29;					// flag as extended boot sector
	bsp->volid = base;					// use base address as volume ID
	memcpy(bsp->label, "NO NAME    ", 11);
	memcpy(bsp->fattype, "FAT16   ", 8);
	
	bsp->part[0].indicator = 0x80;
	bsp->part[0].parttype = 4;			// DOS 16-bit FAT
	bsp->part[0].bias = 0;
	bsp->part[0].partsize = nsec;
	
	bsp->signature = 0xAA55;					// boot sector signature

	// Initialize the start of the FAT at sector 1

	fat[0] = 0xFFF8;			// reserved bytes
	fat[1] = 0xFFFF;
	}							// InitRamDisk

///////////////////////////////////////////////////////////////////////////////
// AEP_UNCONFIG_DCB informs us that the physical device represented by a DCB
// is going away

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnUnconfigDcb(PAEP_dcb_unconfig aep)
	{							// OnUnconfigDcb
	PDCB dcb = (PDCB) aep->AEP_d_u_dcb;
	ASSERT(dcb);

	// We will get UNCONFIG calls for logical DCBs that are associated
	// with the physical device. We need to ignore these calls! We will
	// also occasionally get calls for DCBs that have nothing to do with
	// us at all (?)

	if (!(dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL)
		|| memcmp(dcb->DCB_vendor_id, "WALTONEY", 8) != 0)
		return AEP_SUCCESS;		// ignore unconfig of logical DCB

	if (dcb->DCB_Port_Specific)
		{						// release memory
		_PageFree((PVOID) dcb->DCB_Port_Specific, 0);
		dcb->DCB_Port_Specific = 0;
		}						// release memory
	--ndevices;					// this will cause to unload after next AEP_BOOT_COMPLETE
	ASSERT(ndevices >= 0);
	return AEP_SUCCESS;
	}							// OnUnconfigDcb

///////////////////////////////////////////////////////////////////////////////
// AEP_DEVICE_INQUIRY asks us whether there's a physical device at a given
// controller-relative index. In this sample, we support one device per
// controller. A real device would examine BIOS entries or use some hardware-
// oriented method to enumerate the devices

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnDeviceInquiry(PAEP_inquiry_device aep)
	{							// OnDeviceInquiry
	PDCB dcb = (PDCB) aep->AEP_i_d_dcb;
	ASSERT(dcb);
	if (dcb->DCB_unit_on_ctl > 0)
		return AEP_NO_MORE_DEVICES;

	memcpy(dcb->DCB_vendor_id, "WALTONEY", 8);
	memcpy(dcb->DCB_product_id, "RAM Disk        ", 16);
	memcpy(dcb->DCB_rev_level, "0001", 4);
	
	return AEP_SUCCESS;
	}							// OnDeviceInquiry

///////////////////////////////////////////////////////////////////////////////
// AEP_UNINITIALIZE means the DDB is about to be deleted, meaning
// the controller is about to be removed.

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnUninitialize(PAEP_bi_uninit aep)
	{							// OnUninitialize
	return AEP_SUCCESS;
	}							// OnUninitialize

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// I/O request processing:

#pragma VxD_LOCKED_CODE_SEG

void DoCallDown(PIOP iop);
void DoCallBack(PIOP iop);

VOID OnRequest(PIOP iop)
	{							// OnRequest
	#define ior iop->IOP_ior
	DWORD funcode = ior.IOR_func;
	PDCB dcb = (PDCB) iop->IOP_physical_dcb;

	ior.IOR_status = IORS_SUCCESS; // assume it'll succeed
	dcb->DCB_cmn.DCB_device_flags |= DCB_DEV_IO_ACTIVE;

	switch (funcode)
		{					// dispatch function processor

	///////////////////////////////////////////////////////////////////////
	
	case IOR_READ:			// IOR_func == 0
		{					// IOR_READ
		DWORD sector = ior.IOR_start_addr[0];
		PBYTE diskdata = (PBYTE) (dcb->DCB_Port_Specific + sector * dcb->DCB_actual_blk_size);

		ASSERT(sector < dcb->DCB_actual_sector_cnt[0]);
		ASSERT(ior.IOR_start_addr[1] == 0);

		if (ior.IOR_flags & IORF_SCATTER_GATHER)
			{				// have scatter/gather structures
			_BlockDev_Scatter_Gather* sgd = (_BlockDev_Scatter_Gather*) ior.IOR_buffer_ptr;
			PBYTE memdata;
			DWORD nbytes;
			while ((nbytes = sgd->BD_SG_Count))
				{			// for each s/g structure
				memdata = (PBYTE) sgd->BD_SG_Buffer_Ptr; // linear address!
				if (!(ior.IOR_flags & IORF_CHAR_COMMAND))
					nbytes *= dcb->DCB_actual_blk_size;
				memcpy(memdata, diskdata, nbytes);
				diskdata += nbytes;
				++sgd;
				}			// for each s/g structure
			}				// have scatter/gather structures
		else
			{				// have simple buffer address
			PBYTE memdata = (PBYTE) ior.IOR_buffer_ptr;
			DWORD nbytes = ior.IOR_xfer_count;
			if (!(ior.IOR_flags & IORF_CHAR_COMMAND))
				nbytes *= dcb->DCB_actual_blk_size;
			memcpy(memdata, diskdata, nbytes);
			}				// have simple buffer address
		
		break;
		}					// IOR_READ

	///////////////////////////////////////////////////////////////////////
	
	case IOR_WRITE:			// IOR_func == 1
		{					// IOR_WRITE
		DWORD sector = ior.IOR_start_addr[0];
		PBYTE diskdata = (PBYTE) (dcb->DCB_Port_Specific + sector * dcb->DCB_actual_blk_size);

		ASSERT(sector);		// why is anyone rewriting the boot sector??
		ASSERT(sector < dcb->DCB_actual_sector_cnt[0]);
		ASSERT(ior.IOR_start_addr[1] == 0);

		if (ior.IOR_flags & IORF_SCATTER_GATHER)
			{				// have scatter/gather structures
			_BlockDev_Scatter_Gather* sgd = (_BlockDev_Scatter_Gather*) ior.IOR_buffer_ptr;
			PBYTE memdata;
			DWORD nbytes;
			while ((nbytes = sgd->BD_SG_Count))
				{			// for each s/g structure
				memdata = (PBYTE) sgd->BD_SG_Buffer_Ptr; // linear address!
				if (!(ior.IOR_flags & IORF_CHAR_COMMAND))
					nbytes *= dcb->DCB_actual_blk_size;
				memcpy(diskdata, memdata, nbytes);
				diskdata += nbytes;
				++sgd;
				}			// for each s/g structure
			}				// have scatter/gather structures
		else
			{				// have simple buffer address
			PBYTE memdata = (PBYTE) ior.IOR_buffer_ptr;
			DWORD nbytes = ior.IOR_xfer_count;
			if (!(ior.IOR_flags & IORF_CHAR_COMMAND))
				nbytes *= dcb->DCB_actual_blk_size;
			memcpy(diskdata, memdata, nbytes);
			}				// have simple buffer address
		
		break;
		}					// IOR_WRITE

	///////////////////////////////////////////////////////////////////////

	default:
		dcb->DCB_cmn.DCB_device_flags &= ~DCB_DEV_IO_ACTIVE;
		DoCallDown(iop);
		return;
		}					// dispatch function processor

	dcb->DCB_cmn.DCB_device_flags &= ~DCB_DEV_IO_ACTIVE;
	DoCallBack(iop);		// we're done with this request

	#undef ior
	}							// OnRequest

// DoCallDown passes a request to the next lower layer. Note that the
// documentation about how to do this is totally wrong: you don't just
// add sizeof(DCB_cd_entry) to the calldown pointer, you follow a
// linked list from one calldown entry to the next.

void __declspec(naked) DoCallDown(PIOP iop)
	{							// DoCallDown
	_asm
		{						// call down to next layer
		mov	ecx, [esp+4]
		mov	eax, [ecx]IOP.IOP_calldown_ptr
		mov eax, [eax]DCB_cd_entry.DCB_cd_next
		mov [ecx]IOP.IOP_calldown_ptr, eax
		jmp [eax]DCB_cd_entry.DCB_cd_io_address
		}						// call down to next layer
	}							// DoCallDown

// DoCallBack handles completion of an I/O request by calling the
// previous level's callback routine.

void __declspec(naked) DoCallBack(PIOP iop)
	{							// DoCallBack
	_asm
		{						// call back to previous layer
		mov ecx, [esp+4]
		sub [ecx]IOP.IOP_callback_ptr, size IOP_callback_entry
		mov eax, [ecx]IOP.IOP_callback_ptr
		jmp [eax]IOP_callback_entry.IOP_CB_address
		}						// call back to previous layer
	}							// DoCallBack
