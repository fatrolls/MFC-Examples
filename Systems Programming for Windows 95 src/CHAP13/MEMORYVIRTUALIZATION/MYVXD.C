/*****************************************************************************/
/*																			 */
/*	  Sample VxD to illustrate how to virtualize a memory-mapped device		 */
/*																			 */
/*	  N.B.: I never tested this sample! I only verified that I could get it	 */
/*	  to compile.															 */
/*																			 */
/*****************************************************************************/

#define WANTVXDWRAPS
#include <basedef.h>
#include <vmm.h>
#include <vxdwraps.h>

void * __cdecl memcpy(void *, const void *, int); // from string.h
#pragma intrinsic(memcpy)

PVMMCB hOwner;
PBYTE GetPrivateVideoBuffer(PVMMCB);
PBYTE GetRealVideoBuffer(void);
void MapPrivateVideoPages(PVMMCB);
void MapRealVideoPages(PVMMCB);
BOOL OnCreateVM(PVMMCB hVM);

DWORD _Allocate_Device_CB_Area(DWORD nbytes, DWORD flags);
DWORD _MapIntoV86(PVOID hMem, HVM hVM, DWORD VMLinPgNum, int nPages, DWORD PageOff, DWORD flags);
DWORD _PhysIntoV86(DWORD PhysPage, HVM hVM, DWORD VMLinPgNum, int nPages, DWORD flags);
DWORD _Assign_Device_V86_Pages(DWORD VMLinPage, int nPages, HVM hVM, DWORD flags);

typedef struct tagMYSTUFF
	{
	PVOID pVidBuff;				// linear address of video buffer
	} MYSTUFF, *PMYSTUFF;

DWORD cboffset;					// offset of MYSTUFF in VMCB
#define GetStuff(hvm) ((PMYSTUFF) ((DWORD) hvm + cboffset))
#define MYVXD_DEVICE_ID 0x4242	// a dummy!!!
#define BUFSIZE (8*4096)		// 8 pages of data

BOOL OnSetDeviceFocus(PVMMCB hVM, DWORD devid, DWORD flags,
	PVMMCB hProblemVM)
	{							// OnSetDeviceFocus
	if (devid && devid != MYVXD_DEVICE_ID)
		return TRUE;			// ignore request for another device
	memcpy(GetPrivateVideoBuffer(hOwner), GetRealVideoBuffer(),
		BUFSIZE);
	memcpy(GetRealVideoBuffer(), GetPrivateVideoBuffer(hVM),
		BUFSIZE);
	MapPrivateVideoPages(hOwner);
	MapRealVideoPages(hVM);
	hOwner = hVM;
	return TRUE;
	}							// OnSetDeviceFocus

PBYTE GetRealVideoBuffer(void)
	{							// GetRealVideoBuffer
	return _MapPhysToLinear(0xB8000, 8 * 4096, 0);
	}							// GetRealVideoBuffer

BOOL OnDeviceInit(PVMMCB hVM, DWORD refdata)
	{							// OnDeviceInit
	if (!_Assign_Device_V86_Pages(0xB8, 8, NULL, 0))
		return FALSE;			// can't globally assign pages

	cboffset = _Allocate_Device_CB_Area(sizeof(MYSTUFF), 0);
	if (!cboffset)
		return FALSE;
	return OnCreateVM(hVM);		// initialize system VM data now
	}							// OnDeviceInit

BOOL OnCreateVM(PVMMCB hVM)
	{							// OnCreateVM
	PVOID pVidBuff;
	pVidBuff = (PVOID) _PageAllocate(8, PG_VM, (HVM) hVM, 0, 0, 0, 0,
		PAGEZEROINIT);
	if (!pVidBuff)
		return FALSE;
	GetStuff(hVM)->pVidBuff = pVidBuff;
	return TRUE;
	}							// OnCreateVM

BOOL OnDestroyVM(PVMMCB hVM)
	{							// OnDestroyVM
	_PageFree(GetStuff(hVM)->pVidBuff, 0);
	return TRUE;
	}							// OnDestroyVM

PBYTE GetPrivateVideoBuffer(PVMMCB hVM)
	{							// GetPrivateVideoBuffer
	return GetStuff(hVM)->pVidBuff;
	}							// GetPrivateVideoBuffer

void MapPrivateVideoPages(PVMMCB hVM)
	{							// MapPrivateVideoPages
	_MapIntoV86(GetStuff(hVM)->pVidBuff, (HVM) hVM, 0xB8, 8, 0, 0);
	}							// MapPrivateVideoPages

void MapRealVideoPages(PVMMCB hVM)
	{							// MapRealVideoPages
	_PhysIntoV86(0xB8, (HVM) hVM, 0xB8, 8, 0);
	}							// MapRealVideoPages

