// VDMAD.H -- Declarations for VDMAD interfaces
// Copyright (C) 1995, 1996 by Walter Oney
// All rights reserved

#ifndef VDMAD_H
#define VDMAD_H

typedef DWORD DMAHANDLE;
typedef void (__cdecl DMACALLBACKFCN)(DMAHANDLE, PVMMCB);
typedef DMACALLBACKFCN* LPDMACALLBACKFCN;

// Mode bits:

#define DMA_type_verify		0x00
#define DMA_type_write		0x04
#define DMA_type_read		0x08
#define DMA_AutoInit		0x10
#define DMA_AdrDec			0x20

#define DMA_demand_mode		0x00
#define DMA_single_mode		0x40
#define DMA_block_mode		0x80
#define DMA_cascade			0xC0

#define DMA_chan_sel		0x03

// State flag bits (instead of channel selection bits in mode byte)

#define DMA_masked			0x01
#define DMA_requested		0x02

// Extended mode bits:

#define Programmed_IO		0x0100
#define PS2_AutoInit		0x0200
#define Transfer_Data		0x0400
#define Write_Mem			0x0800
#define _16_bit_xfer		0x4000

typedef struct DMA_Descriptor_Struc
{
DWORD	DDS_size;
DWORD	DDS_linear;
WORD	DDS_seg;
WORD	DDS_bufferID;
DWORD	DDS_physical;
} DMAD, *PDMAD;

#define DMA_Buf_Copy		0x02
#define DMA_No_Alloc_Buf	0x04
#define DMA_Align_64K		0x10
#define DMA_Align_128K		0x20
#define DMA_Get_PgTable		0x40
#define DMA_Allow_NPs		0x80

// Error codes:

#define DMA_Not_Contiguous		1
#define DMA_Not_Aligned			2
#define DMA_Lock_Failed			3
#define DMA_No_Buffer			4
#define DMA_Buffer_Too_Small	5
#define DMA_Buffer_In_Use		6
#define DMA_Invalid_Region		7
#define DMA_Region_Not_Locked	8
#define DMA_Table_Too_Small		9
#define DMA_Invalid_Buffer	    10
#define DMA_Copy_Out_Range	    11
#define DMA_Invalid_Channel	    12
#define DMA_Disable_Cnt_Overflow	13
#define DMA_Disable_Cnt_Underflow	14
#define DMA_Func_Not_Supported		15
#define DMA_NonZero_Reserved_Flags	16

//	Flag definitions for Scatter_Lock and Scatter_Unlock:

#define DMA_SL_Get_PgTable		0x01	// page table copy for scatter/gather lock
#define DMA_SL_Allow_NPs		0x02	// not-present pages allowed in scatter/gather lock
#define DMA_SL_Dont_Dirty		0x04	// pages should not be marked as dirty

#define VDMAD_Callbacks_ReadNotify	1	// extended read notify
#define VDMAD_Callbacks_Valid		1

#define VDMAD_Callback_ReadCount	1
#define VDMAD_Callback_ReadPage		2
#define VDMAD_Callback_ReadBase		3

#define VDMAD_Service Declare_Service
#pragma warning(disable:4003)	// not enough parameters

Begin_Service_Table(VDMAD)

VDMAD_Service(VDMAD_Get_Version, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Virtualize_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Region_Info, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_Region_Info, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Virt_State, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_Virt_State, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_Phys_State, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Mask_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_UnMask_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Lock_DMA_Region, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Unlock_DMA_Region, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Scatter_Lock, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Scatter_Unlock, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Reserve_Buffer_Space, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Request_Buffer, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Release_Buffer, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Copy_To_Buffer, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Copy_From_Buffer, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Default_Handler, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Disable_Translation, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Enable_Translation, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_EISA_Adr_Mode, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_EISA_Adr_Mode, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Unlock_DMA_Region_No_Dirty, VxD_LOCKED_CODE)

#ifdef  WIN40SERVICES

VDMAD_Service(VDMAD_Phys_Mask_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Phys_Unmask_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Unvirtualize_Channel, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_IO_Address, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Phys_Count, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Phys_Status, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Max_Phys_Page, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_Channel_Callbacks, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Get_Virt_Count, VxD_LOCKED_CODE)
VDMAD_Service(VDMAD_Set_Virt_Count, VxD_LOCKED_CODE)

#endif // WIN40SERVICES

End_Service_Table(VDMAD)

#pragma warning(default:4003)
#pragma warning(disable:4035)		// no return value

#define NAKED __declspec(naked)

#define ET_WASENABLED	0x0100		// translation was already enabled
#define ET_NOTENABLED	0x0001		// not yet enabled

VXDINLINE DWORD VDMAD_Copy_From_Buffer(BYTE id, DWORD address, DWORD off, DWORD nbytes)
{
	_asm mov bl, id
	_asm mov esi, address
	_asm mov edi, off
	_asm mov ecx, nbytes
	VxDCall(VDMAD_Copy_From_Buffer)
	_asm
		{
		jc	error
		xor	al, al
	error:
		movzx eax, al
		}
}

VXDINLINE DWORD VDMAD_Copy_To_Buffer(BYTE id, DWORD address, DWORD off, DWORD nbytes)
{
	_asm mov bl, id
	_asm mov esi, address
	_asm mov edi, off
	_asm mov ecx, nbytes
	VxDCall(VDMAD_Copy_From_Buffer)
	_asm
		{
		jc	error
		xor	al, al
	error:
		movzx eax, al
		}
}

VXDINLINE DWORD VDMAD_Enable_Translation(DMAHANDLE hdma, HVM hVM)
{
	_asm mov eax, hdma
	_asm mov ebx, hVM
	VxDCall(VDMAD_Enable_Translation)
	_asm mov eax, 0
	_asm setz al
	_asm setc ah
}

VXDINLINE void NAKED VDMAD_Default_Handler(DMAHANDLE hdma, HVM hVM)
{
	_asm mov eax, hdma
	_asm mov ebx, hVM
	VxDJmp(VDMAD_Default_Handler)
}

VXDINLINE DWORD NAKED VDMAD_Get_Max_Phys_Page(void)
{
	VxDJmp(VDMAD_Get_Max_Phys_Page)
}

VXDINLINE DWORD VDMAD_Lock_DMA_Region(DWORD address, DWORD nbytes, BYTE alignment, PDWORD presult)
{
	_asm mov esi, address
	_asm mov ecx, nbytes
	_asm mov dl, alignment
	VxDCall(VDMAD_Lock_DMA_Region)
	_asm
		{						// decode return
		mov	ebx, presult
		jc	error
		mov	[ebx], edx			; physical address
		mov	eax, 1
		jmp	done
	error:
		mov	[ebx], ecx			; # bytes which could be locked
		movzx eax, al			; zero extend error code
	done:
		}						// decode return
}

VXDINLINE NAKED void VDMAD_Mask_Channel(DMAHANDLE hdma)
{
	_asm mov eax, hdma
	VxDJmp(VDMAD_UnMask_Channel)
}

VXDINLINE DWORD VDMAD_Request_Buffer(DWORD address, DWORD nbytes, PDWORD pphys, PBYTE pid)
{
	_asm mov esi, address
	_asm mov ecx, nbytes
	VxDCall(VDMAD_Request_Buffer)
	_asm
		{
		jc	error
		mov	eax, pphys
		mov	[eax], edx			; physical address
		mov	eax, pid
		mov	byte ptr [eax], bl	; buffer id
		xor	eax, eax
	error:
		movzx eax, al
		}
	Touch_Register(EBX)
}

VXDINLINE BOOL VDMAD_Release_Buffer(BYTE id)
{
	_asm mov bl, id
	VxDCall(VDMAD_Release_Buffer)
	_asm mov eax, 0
	_asm setnc al
}

VXDINLINE void NAKED VDMAD_Reserve_Buffer_Space(DWORD npages, DWORD maxaddr)
{
	_asm mov eax, npages
	_asm mov ecx, maxaddr
	VxDJmp(VDMAD_Reserve_Buffer_Space)
}

VXDINLINE void NAKED VDMAD_Set_Region_Info(DMAHANDLE hdma, BYTE id, BYTE locked, DWORD address, DWORD nbytes, DWORD physaddr)
{
	_asm
		{
		mov	eax, hdma
		mov	bl, id
		mov	bh, locked
		mov	esi, address
		mov	ecx, nbytes
		mov	edx, physaddr
		}
	VxDJmp(VDMAD_Set_Region_Info)
}

VXDINLINE void NAKED VDMAD_Set_Phys_State(DMAHANDLE hdma, WORD mode)
{
	_asm mov eax, hdma			
	_asm mov dx, mode
	VxDJmp(VDMAD_Set_Phys_State)	// note: EBX not actually used, despite doc
}

VXDINLINE NAKED void VDMAD_Set_Virt_State(DMAHANDLE hdma, HVM hVM, DWORD address, DWORD count, WORD mode)
{
	_asm
		{						// load parameters
		mov	eax, hdma
		mov	ebx, hVM
		mov	esi, address
		mov	ecx, count
		mov	dx, mode
		}						// load parameters
	VxDJmp(VDMAD_Set_Virt_State)
}

VXDINLINE NAKED void VDMAD_UnMask_Channel(DMAHANDLE hdma, HVM hVM)
{
	_asm mov eax, hdma
	_asm mov ebx, hVM
	VxDJmp(VDMAD_UnMask_Channel)
}

VXDINLINE BOOL VDMAD_Unlock_DMA_Region(DWORD address, DWORD nbytes)
{
	_asm mov esi, address
	_asm mov ecx, nbytes
	VxDCall(VDMAD_Unlock_DMA_Region)
	_asm mov eax, 0
	_asm setnc al
}

VXDINLINE BOOL VDMAD_Unlock_DMA_Region_No_Dirty(DWORD address, DWORD nbytes)
{
	_asm mov esi, address
	_asm mov ecx, nbytes
	VxDCall(VDMAD_Unlock_DMA_Region_No_Dirty)
	_asm mov eax, 0
	_asm setnc al
}

VXDINLINE BOOL VDMAD_Unvirtualize_Channel(DMAHANDLE hdma)
{
	_asm mov eax, hdma
	VxDCall(VDMAD_Unvirtualize_Channel)
	_asm mov eax, 0
	_asm setnc al
	Touch_Register(edx)
}

VXDINLINE DMAHANDLE VDMAD_Virtualize_Channel(DWORD channel, LPDMACALLBACKFCN callback)
{
	_asm mov eax, channel
	_asm mov esi, callback
	VxDCall(VDMAD_Virtualize_Channel)
	_asm
		{
		jnc noerror
		xor eax, eax
	noerror:
		}
	Touch_Register(edx)
}

#pragma warning(default:4035)

#endif // VDMAD_H
