/*****************************************************************************/
/*																			 */
/*	  Sample VxD illustrating how to do DMA from a VxD						 */
/*																			 */
/*****************************************************************************/

// To test this sample, you will need to prevent VFBACKUP from loading (because
// it loads VFD.VXD, which virtualizes DMA channel 2). One way to do this
// is to rename the StaticVxD named value in HKLM\System\CurrentControlSet
// \Services\VxD\VFBACKUP to something else. You will also need to disable
// the real A-drive in Device Manager. For example, Uncheck the box that
// makes it part of your current configuration. Finally, you will have to
// remove the ForcedConfig from the A-drive's hardware key. You'll usually
// find this in HKLM\Enum\Root\*PNP0700\0000. You should rename this value
// so you can restore it later.


#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vpicd.h>
#include <vxdwraps.h>
#include <configmg.h>
#include "vdmad.h"				// N.B.: Our own header file
#include "crs.h"				// ditto

///////////////////////////////////////////////////////////////////////////////
// Useful general-purpose definitions

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
	#define FIELDOFFSET(type, field)    ((DWORD)(&((type *)0)->field))
#endif

///////////////////////////////////////////////////////////////////////////////

DMAHANDLE dmahandle;			// virtualized DMA channel handle
HIRQ irqhandle;					// virtualized IRQ handle
DWORD baseport;					// I/O base address (i.e., 3F2)
VMM_SEMAPHORE waitsem;			// semaphore to wait on

CONFIGRET CM_HANDLER OnConfigure(CONFIGFUNC cf, SUBCONFIGFUNC scf, DEVNODE devnode, DWORD refdata, ULONG flags);
void Hw_Int_Proc_Thunk();
BOOL Hw_Int_Proc(HIRQ hirq, DWORD refdata);
void FdcWakeup();
void FdcWrite(DWORD baseport, BYTE* data, int length);
void FdcWait(DWORD baseport);

///////////////////////////////////////////////////////////////////////////////

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	waitsem = Create_Semaphore(0);
	return waitsem != NULL;
	}							// OnSysDynamicDeviceInit

///////////////////////////////////////////////////////////////////////////////

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	if (waitsem)
		Destroy_Semaphore(waitsem);
	return TRUE;
	}							// OnSysDynamicDeviceExit

///////////////////////////////////////////////////////////////////////////////

CONFIGRET OnPnpNewDevnode(DEVNODE devnode, DWORD loadtype)
	{							// OnPnpNewDevnode
	return CM_Register_Device_Driver(devnode, OnConfigure, 0, CM_REGISTER_DEVICE_DRIVER_REMOVABLE | CM_REGISTER_DEVICE_DRIVER_DISABLEABLE);
	}							// OnPnpNewDevnode

///////////////////////////////////////////////////////////////////////////////

CONFIGRET CM_HANDLER OnConfigure(CONFIGFUNC cf, SUBCONFIGFUNC scf, DEVNODE devnode, DWORD refdata, ULONG flags)
	{							// OnConfigure
	switch (cf)
		{						// handle configuration function

	case CONFIG_START:
		{						// CONFIG_START
		CMCONFIG config;
		DWORD channel;
		DWORD irq;
		VID vid = {0, 0, (DWORD) Hw_Int_Proc_Thunk};

		CM_Get_Alloc_Log_Conf(&config, devnode, CM_GET_ALLOC_LOG_CONF_ALLOC);
		ASSERT(config.wNumIOPorts == 1);
		ASSERT(config.wNumIRQs == 1);
		ASSERT(config.wNumDMAs == 1);

		baseport = config.wIOPortBase[0];
		channel = config.bDMALst[0];
		irq = config.bIRQRegisters[0];

		ASSERT(baseport == 0x3F2);
		ASSERT(channel == 2);
		ASSERT(irq == 6);

		dmahandle = VDMAD_Virtualize_Channel(channel, NULL);
		ASSERT(dmahandle);

		vid.VID_IRQ_Number = (USHORT) irq;
		irqhandle = VPICD_Virtualize_IRQ(&vid);
		ASSERT(irqhandle);

		return CR_SUCCESS;
		}						// CONFIG_START

	case CONFIG_STOP:
	case CONFIG_REMOVE:
		if (dmahandle)
			{					// unvirtualize DMA channel
			VDMAD_Unvirtualize_Channel(dmahandle);
			dmahandle = NULL;
			}					// unvirtualize DMA channel
		if (irqhandle)
			{					// unvirtualize IRQ
			VPICD_Force_Default_Behavior(irqhandle);
			irqhandle = NULL;
			}					// unvirtualize IRQ
		return CR_SUCCESS;

	default:
		return CR_DEFAULT;
		}						// handle configuration function
	}							// OnConfigure

///////////////////////////////////////////////////////////////////////////////

void __declspec(naked) Hw_Int_Proc_Thunk()
	{							// Hw_Int_Proc_Thunk
	_asm
		{						// call hw int proc
		push edx				; ref data (if any)
		push eax				; IRQ handle
		call Hw_Int_Proc		; call C program
		add  esp, 8				; lose args
		cmp  eax, 1				; turn TRUE return into CLC
		ret						; return to VPICD
		}						// call hw int proc
	}							// Hw_Int_Proc_Thunk

BOOL Hw_Int_Proc(HIRQ hirq, DWORD refdata)
	{							// Hw_Int_Proc
	int i;
	BYTE status[7];				// 7 status bytes
	
	for (i = 0; i < 7; ++i)
		{						// read status from controller
		BYTE c;
		FdcWait(baseport);
		_asm
			{					// read next status byte
			mov	edx, baseport	; DX = port to read from
			add	dx, 3			;   ..
			in	al, dx			; read status byte
			mov	c, al			;   ..
			}					// read next status byte
		status[i] = c;
		}						// read status from controller

	VPICD_Phys_EOI(hirq);
	Schedule_Global_Event(FdcWakeup, waitsem);
	return TRUE;
	}							// Hw_Int_Proc

void __declspec(naked) FdcWakeup()
	{							// FdcWakeup
	_asm mov eax, edx			; EDX (ref data) = semaphore handle
	VMMCall(Signal_Semaphore_No_Switch);	// wakeup waiting thread
	_asm ret
	}							// FdcWakeup

///////////////////////////////////////////////////////////////////////////////

void ApiEntry(HVM hVM, PTCB tcb, PCRS pRegs)
	{							// ApiEntry
	static BYTE cmd[] = {3, 0xAF, 2, 0xE6, 0, 0, 0, 1, 2, 0x12, 0x1B, 255}; // read sector cmd
	DWORD buffer;				// flat address of client's buffer
	DWORD code;

	// Initialize the floppy disk controller
	
	_asm
		{						// initialize floppy controller
		mov	edx, baseport		; DX = base port (3F2)
		mov	al, 1Ch				; 0001 1 1 00 => motor A on, DMA, REST, select A
		out	dx, al				;   ..
		jmp	delay1
	delay1:
		jmp	delay2
	delay2:
		add	dx, 5				; DX = 3F7
		xor	al, al
		out	dx, al
		}						// initialize floppy controller

	// Setup DMA channel 2 to transfer 512 bytes to the buffer at client
	// DS:BX

	buffer = Client_Ptr_Flat(DS, BX);
	
	do	{						// force address translation on this channel
		code = VDMAD_Enable_Translation(dmahandle, hVM);
		}						// force address translation on this channel
	while ((code & ET_WASENABLED) != ET_WASENABLED);

	VDMAD_Set_Virt_State(dmahandle, hVM, buffer,
		512, DMA_type_write | DMA_single_mode);
	VDMAD_Default_Handler(dmahandle, hVM);
	
	// Program the floppy controller with a read-sector command to read
	// sector 0
	
	FdcWrite(baseport, cmd, sizeof(cmd));

	// Wait for the operation to complete

	Wait_Semaphore(waitsem, BLOCK_SVC_INTS);

	_asm
		{						// turn motor off
		mov	edx, baseport
		mov	al, 0Ch
		out	dx, al
		}						// turn motor off
	}							// ApiEntry

void FdcWrite(DWORD baseport, BYTE* data, int length)
	{							// FdcWrite
	while (length-- > 0)
		{						// for each byte
		BYTE c = *data++;		// next byte to write
		FdcWait(baseport);		// wait until it's okay to write
		_asm
			{					// write data byte
			mov	edx, baseport	; compute port address
			add	dx, 3			;   ..
			mov	al, c			; AL = next data byte
			out	dx, al			; output data byte
			}					// write data byte
		}						// for each byte
	}							// FdcWrite						

void FdcWait(DWORD baseport)
	{							// FdcWait
	_asm
		{						// wait for floppy controller
		mov	edx, baseport		; base port address
		add	dx, 2				; point to status port
	waitloop:
		in	al, dx				; read status byte
		test al, 80h			; wait for ready bit to become one
		jz	waitloop			;   ..
		}						// wait for floppy controller
	}							// FdcWait

///////////////////////////////////////////////////////////////////////////////
// Untested example of programming a DMA transfer the hard way:

#pragma warning(disable:4035)
VXDINLINE BOOL Time_Slice_Sleep(DWORD timeout)
{
	_asm mov eax, timeout
	VMMCall(Time_Slice_Sleep)
	_asm mov eax, 0
	_asm setnz al				; 1 => timeout completed
}
#pragma warning(default:4035)

DWORD foo(DWORD address, DWORD size, WORD mode, BYTE align, VMM_SEMAPHORE sem)
	{							// foo
	DWORD code;
	DWORD result;
	BYTE id;

	code = VDMAD_Lock_DMA_Region(address, size, align, &result);
	if (code == 0 && result >= (VDMAD_Get_Max_Phys_Page() << 12))
		{						// beyond maximum
		VDMAD_Unlock_DMA_Region(address, size);
		code = DMA_Invalid_Region;
		}						// beyond maximum
	if (code)
		{						// try to buffer transfer
		while ((code = VDMAD_Request_Buffer(address, size, &result, &id)) == DMA_Buffer_In_Use)
			Time_Slice_Sleep(100);
		if (code)
			return code;		// must be Buffer_Too_Small
		}						// try to buffer transfer
	VDMAD_Set_Region_Info(dmahandle, id, TRUE, address, size, result);
	if (id && (mode & DMA_type_read))
		VDMAD_Copy_To_Buffer(id, address, 0, size);
	VDMAD_Set_Phys_State(dmahandle, mode);
	VDMAD_UnMask_Channel(dmahandle, Get_Sys_VM_Handle());

	Wait_Semaphore(sem, BLOCK_SVC_INTS);		// time passes...

	VDMAD_Mask_Channel(dmahandle);
	if (id)
		{						// buffered xfer
		if (mode & DMA_type_write)
			VDMAD_Copy_From_Buffer(id, address, 0, size);
		VDMAD_Release_Buffer(id);
		}						// buffered xfer
	else
		if (mode & DMA_type_write)
			VDMAD_Unlock_DMA_Region(address, size);
		else
			VDMAD_Unlock_DMA_Region_No_Dirty(address, size);
	return 0;
	}							// foo
