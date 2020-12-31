// REQMON.C -- VSD to monitor I/O requests
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#include "iosdcls.h"			// VMM and IOS headers
#include <vwin32.h>
#include <winerror.h>
#pragma hdrstop

#include "reqmon.h"

void ReturnBlock(PMONINFO mip);
PMONINFO GetBlock();
VOID OnRequest(PIOP iop);
VOID OnRequestComplete(PIOP iop);
VOID DoCallDown(PIOP iop);
VOID DoCallBack(PIOP iop);
void InsertCallBack(PIOP iop, VOID (*callback)(PIOP), ULONG refdata);

USHORT OnInitialize(PAEP_bi_init aep);
USHORT OnUninitialize(PAEP_bi_uninit aep);
USHORT OnBootComplete(PAEP_boot_done aep);
USHORT OnConfigDcb(PAEP_dcb_config aep);
USHORT OnUnconfigDcb(PAEP_dcb_unconfig aep);

///////////////////////////////////////////////////////////////////////////////
// Static data

#pragma VxD_LOCKED_DATA_SEG

int ndevices = 0;				// # devices we've found
PTCB thread = NULL;				// handle of ring-3 thread
DWORD userproc = NULL;			// user procedure to call
VMMLIST list;					// list handle

#pragma VxD_PAGEABLE_DATA_SEG

///////////////////////////////////////////////////////////////////////////////
// Initialization code and data

#pragma VxD_INIT_CODE_SEG

extern DRP theDRP;				// device registration packet

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	list = List_Create(LF_ASYNC | LF_ALLOC_ERROR, sizeof(MONINFO));
	if (!list)
		return FALSE;
	IOS_Register(&theDRP);
	return TRUE;				// stay resident no matter what IOS says
	}							// OnSysDynamicDeviceInit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	if (list)
		List_Destroy(list);
	return TRUE;
	}							// OnSysDynamicDeviceExit

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

void OnTerminateThread(PTCB ht)
	{							// OnTerminateThread
	if (ht == thread)
		thread = NULL, userproc = NULL;
	}							// OnTerminateThread

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

DWORD OnDeviceIoControl(PDIOCPARAMETERS p)
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

	case REQMON_GETIVTADDR:
		{						// GETIVTADDR
		PVMMDDB ddb = Get_DDB(IOS_DEVICE_ID, NULL);
		_IVT* ivt = (_IVT*) ((DWORD) ddb + 0x58);
		if (!p->lpvOutBuffer || p->cbOutBuffer < 4)
			return ERROR_INVALID_PARAMETER;
		*(_IVT**) p->lpvOutBuffer = ivt;
		if (p->lpcbBytesReturned)
			*(PDWORD) p->lpcbBytesReturned = 4;
		break;
		}						// GETIVTADDR

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
	mip = List_Allocate(list);
	_asm popfd

	return mip;
	}							// GetBlock

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Asynchronous event processing:

#pragma VxD_LOCKED_CODE_SEG
#pragma VxD_LOCKED_DATA_SEG
#undef CURSEG
#define CURSEG() LCODE

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
		,NULL					//  6 AEP_DEVICE_INQUIRY
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
// VSDs needn't do anything during AEP_INITIALIZE and should always
// return success

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnInitialize(PAEP_bi_init aep)
	{							// OnInitialize
	return AEP_SUCCESS;
	}							// OnInitialize

///////////////////////////////////////////////////////////////////////////////

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnUninitialize(PAEP_bi_uninit aep)
	{							// OnUninitialize
	ASSERT(ndevices == 0);

	return AEP_SUCCESS;
	}							// OnUninitialize

///////////////////////////////////////////////////////////////////////////////
// AEP_BOOT_COMPLETE asks us if we want to stay loaded or not.

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnBootComplete(PAEP_boot_done aep)
	{							// OnBootComplete
	return ndevices ? AEP_SUCCESS : AEP_FAILURE; // unload if no devices
	}							// OnBootComplete

///////////////////////////////////////////////////////////////////////////////
// AEP_CONFIG_DCB gives us the chance to hook into the calldown stack for
// every DCB in the system

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnConfigDcb(PAEP_dcb_config aep)
	{							// OnConfigDcb
	PDCB dcb = (PDCB) aep->AEP_d_c_dcb;
	if (!(dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL))
		return AEP_SUCCESS;
	if ((IspInsertCalldown(dcb, OnRequest, (PDDB) aep->AEP_d_c_hdr.AEP_ddb, 0,
		dcb->DCB_cmn.DCB_dmd_flags, aep->AEP_d_c_hdr.AEP_lgn)))
		++ndevices;				// this will cause us to stay loaded after next AEP_BOOT_COMPLETE
	return AEP_SUCCESS;
	}							// OnConfigDcb

///////////////////////////////////////////////////////////////////////////////
// AEP_UNCONFIG_DCB informs us that the physical device represented by a DCB
// is going away

#pragma VxD_PAGEABLE_CODE_SEG

USHORT OnUnconfigDcb(PAEP_dcb_unconfig aep)
	{							// OnUnconfigDcb
	PDCB dcb = (PDCB) aep->AEP_d_u_dcb;
	if (!(dcb->DCB_cmn.DCB_device_flags & DCB_DEV_PHYSICAL))
		return AEP_SUCCESS;
	ASSERT(ndevices > 0);
	--ndevices;					// we hooked into every possible VxD
	return AEP_SUCCESS;
	}							// OnUnconfigDcb

///////////////////////////////////////////////////////////////////////////////
// Request handler:

#pragma VxD_LOCKED_CODE_SEG

VOID OnRequest(PIOP iop)
	{							// OnRequest
	if (userproc)
		InsertCallBack(iop, OnRequestComplete, 0);
	DoCallDown(iop);
	}							// OnRequest

VOID OnRequestComplete(PIOP iop)
	{							// OnRequestComplete
	#define ior iop->IOP_ior
	DWORD funcode = ior.IOR_func;
	PDCB dcb = (PDCB) iop->IOP_physical_dcb;
	PMONINFO mip = GetBlock();

	if (mip)
		{						// notify ring-3 app
		mip->dcb = dcb;
		mip->opcode = (BYTE) ior.IOR_func;
		mip->status = (BYTE) ior.IOR_status;
		mip->sector = ior.IOR_start_addr[0];
		
		mip->nbytes = 0;
		if (ior.IOR_func <= IOR_WRITEV)
			{					// compute transfer length
			if (ior.IOR_flags & IORF_SCATTER_GATHER)
				{				// request used scatter/gather records
				_BlockDev_Scatter_Gather* sgp = (_BlockDev_Scatter_Gather*) ior.IOR_buffer_ptr;
				while (sgp->BD_SG_Count)
					mip->nbytes += sgp->BD_SG_Count, ++sgp;
				}				// request used scatter/gather records
			else
				mip->nbytes = ior.IOR_xfer_count;
			}					// compute transfer length

		if (!userproc || !_VWIN32_QueueUserApc(userproc, (DWORD) mip, thread))
			ReturnBlock(mip);			
		}						// notify ring-3 app

	DoCallBack(iop);
	}							// OnRequest Complete

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

// InsertCallBack adds an entry to the callback list

void InsertCallBack(PIOP iop, VOID (*callback)(PIOP), ULONG refdata)
	{							// InsertCallBack
	IOP_callback_entry* cbp = (IOP_callback_entry*) iop->IOP_callback_ptr;
	ASSERT(cbp >= iop->IOP_callback_table && cbp < iop->IOP_callback_table + arraysize(iop->IOP_callback_table));
	cbp->IOP_CB_address = (ULONG) callback;
	cbp->IOP_CB_ref_data = refdata;
	iop->IOP_callback_ptr += sizeof(IOP_callback_entry);
	}							// InsertCallBack
