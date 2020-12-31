#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <vwin32.h>
#include <vxdwraps.h>

typedef struct tagMYSTUFF
	{
	int foo;
	} MYSTUFF, *PMYSTUFF;

DWORD tcboffset;

DWORD AllocateSlot();
BOOL OnSysDynamicDeviceInit();
BOOL OnSysDynamicDeviceExit();
BOOL OnCreateThread(PTCB thread);
VOID OnDestroyThread(PTCB thread);

#pragma warning(disable:4035)
DWORD __declspec(naked) _AllocateThreadDataSlot()
	{
	VMMJmp(_AllocateThreadDataSlot);
	}

void _FreeThreadDataSlot(DWORD tcboffset)
	{
	_asm push tcboffset
	VMMCall(_FreeThreadDataSlot);
	}

PTCB Get_Sys_Thread_Handle()
	{
	VMMCall(Get_Sys_Thread_Handle);
	_asm mov eax, edi
	}

PTCB Get_Next_Thread_Handle(PTCB thread)
	{
	_asm mov edi, thread
	VMMCall(Get_Next_Thread_Handle);
	_asm mov eax, edi
	}
#pragma warning(default:4035)

DWORD AllocateSlot()
	{							// AllocateSlot
	PTCB first, thread;
	DWORD offset = _AllocateThreadDataSlot();
	if (!offset)
		return 0;
	first = thread = Get_Sys_Thread_Handle();
	do	{						// initialize slot in each thread
		*(PDWORD) ((DWORD) thread + offset) = 0;
		thread = Get_Next_Thread_Handle(thread);
		}						// initialize slot in each thread
	while (thread != first);
	return offset;
	}							// AllocateSlot

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	PTCB first, thread;
	tcboffset = AllocateSlot();
	if (!tcboffset)
		return FALSE;

	first = thread = Get_Sys_Thread_Handle();
	do	{						// allocate stuff for each thread
		if (!(*(PMYSTUFF*)((DWORD) thread + tcboffset) =
			_HeapAllocate(sizeof(MYSTUFF), HEAPZEROINIT)))
			{					// can't allocate
			OnSysDynamicDeviceExit(); // cleanup
			return FALSE;		// fail device load
			}					// can't allocate
		thread = Get_Next_Thread_Handle(thread);
		}						// allocate stuff for each thread
	while (thread != first);
	return TRUE;
	}							// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	PTCB first, thread;
	if (!tcboffset)
		return TRUE;			// shouldn't be possible
	first = thread = Get_Sys_Thread_Handle();
	do	{						// cleanup existing threads
		OnDestroyThread(thread);
		thread = Get_Next_Thread_Handle(thread);
		}						// cleanup existing threads
	while (thread != first);
	_FreeThreadDataSlot(tcboffset);
	return TRUE;   // i.e., okay to unload
	}							// OnSysDynamicDeviceExit

BOOL OnCreateThread(PTCB thread)
	{							// OnCreateThread
	PMYSTUFF* pcell = (PMYSTUFF*) ((DWORD) thread + tcboffset);
	PMYSTUFF pstuff = (PMYSTUFF) _HeapAllocate(sizeof(MYSTUFF),
	HEAPZEROINIT);
	if (!pstuff)
		return FALSE;			// fail thread creation
	*pcell = pstuff;
	return TRUE;
	}							// OnCreateThread

VOID OnDestroyThread(PTCB thread)
	{							// OnDestroyThread
	PMYSTUFF* pcell = (PMYSTUFF*)((DWORD) thread + tcboffset);
	PMYSTUFF pstuff = *pcell;
	*pcell = NULL;
	if (pstuff)
		_HeapFree(pstuff, 0);
	}							// OnDestroyThread

DWORD OnW32DeviceIoControl(PDIOCPARAMETERS p)
	{							// OnW32DeviceIoControl
	return 0;
	}							// OnW32DeviceIoControl
