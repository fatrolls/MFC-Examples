
#include "iosdcls.h"

#include <string.h>
#pragma intrinsic(memcmp, memcpy, memset, strcat, strcmp, strcpy, strlen)

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
	#define FIELDOFFSET(type, field) ((DWORD)(&((type *)0)->field))
#endif

#ifndef arraysize
	#define arraysize(p) (sizeof(p)/sizeof((p)[0]))
#endif

ILB theILB;

BOOL OnSysDynamicDeviceInit()
	{							// OnSysDynamicDeviceInit
	DRP theDRP;
	PDCB dcb;
	BYTE mbr[512];
	
	// Register with IOS. Since we're not a layer driver, we can leave
	// most of the DRP fields zero.
	
	memset(&theDRP, 0, sizeof(theDRP));
	theDRP.DRP_ilb = &theILB;
	IOS_Register(&theDRP);

	// Locate the important data structures for the D-drive. On my
	// system, this is a SCSI disk inaccessible in real mode. Then
	// build an I/O packet to read sector 0 from the physical device.

	dcb = IspGetDcb(3);

///////////////////////////////////////////////////////////////////////////////
// External user method:

	// File system drivers and other callers of IOS_Send_Command usually
	// work with fields of the VRP to build an IOP, and then they
	// work with the imbedded IOR. These clients normally create the
	// VRP in the first place by calling IOS_Requestor_Service, so they
	// already have a pointer to it. In both cases, the client uses the
	// ISP_CREATE_IOP service to actually allocate the memory block. The
	// returned pointer is actually to the memory block IOS allocates
	// rather than to the IOP. My IspCreateIop wrapper compensates for
	// this by returning the IOP address, so beware if you decide to
	// call the underlying service routine directly. 

	{							// external user method
	PVRP vrp = (PVRP) dcb->DCB_cmn.DCB_vrp_ptr;
	
	USHORT size = vrp->VRP_max_req_size + vrp->VRP_max_sgd * sizeof(SGD);
	USHORT offset = (USHORT) vrp->VRP_delta_to_ior;
	PIOR ior = IspCreateIor(size, offset, ISP_M_FL_MUST_SUCCEED);

	// Fill in required fields of the IOR block. The "private client" field
	// is often used to hold the "offset" value to make it a little more
	// convenient to free the memory later, but that's up to the writer
	// of the driver

	ior->IOR_next = 0;					// used for request queueing by lots of downstream people
	ior->IOR_start_addr[1] = 0;			// assume only 32-bits worth of sector number
	ior->IOR_flags = IORF_VERSION_002;	// this is how IOS knows we're giving it a new-style IOR
	ior->IOR_private_client = offset;	// a common use for this field
	ior->IOR_req_vol_handle = (ULONG) vrp;
	ior->IOR_sgd_lin_phys = (ULONG) (ior + 1); // where scatter/gather descriptors can be built
	ior->IOR_num_sgds = 0;				// incremented by criteria routine, so must start at zero
	ior->IOR_vol_designtr = 3;			// i.e., this is the D drive

	// Complete the IOR with information specific to the request we're
	// making. In this case, we want to read 1 sector from sector 0 into
	// our internal data buffer. This will be a synchronous operation,
	// meaning that IOS_Send_Command won't return until the read finishes.

	ior->IOR_func = IOR_READ;			// flag as read request
	ior->IOR_flags |= IORF_SYNC_COMMAND // don't return until complete
		| IORF_HIGH_PRIORITY			// used for adminstrative-type requests, but optional
		| IORF_BYPASS_VOLTRK;			// we want to bypass volume tracking and just read the MBR
	ior->IOR_start_addr[0] = 0;			// reading sector zero
	ior->IOR_buffer_ptr = (ULONG) mbr;	// buffer to read into
	ior->IOR_xfer_count = 1;			// transfer 1 sector

	// Even though the TSD will add the partition offset in to the sector
	// address, most clients do it themselves and leave the IORF_LOGICAL_START_SECTOR
	// flag clear. We're actually trying to read physical sector zero in
	// this sample, though, so we don't adjust it at all.

//	ior->IOR_start_addr[0] += vrp->VRP_partition_offset;

	// Call the so-called "criteria" routine to turn sector counts into
	// byte counts, create physical SGD descriptors, and satisfy other
	// demands of the layer drivers. External users call the external
	// criteria routine:

	IlbIoCriteria(ior);

	// We're finally ready to issue the request. Many external clients
	// actually submit requests using the 3.1 block-device structures
	// instead of the IOS structures we're using here. IOS tells the
	// difference by inspecting the IORF_VERSION_002 flag. If set,
	// the caller is using new-style stuff.

	IOS_SendCommand(ior, dcb);

	// Now we can release the memory used for the I/O request packet.
	// We saved the offset of the IOR from the start of the memory block
	// in the "private client" area to make this a little more convenient.

	IspDeallocMem((PVOID) ((DWORD) ior - ior->IOR_private_client));
	}							// external user method

///////////////////////////////////////////////////////////////////////////////
// Internal user method:

	// Layer drivers creating internal requests usually work directly
	// with info in the DCB, and they deal with the IOP rather than
	// the imbedded IOR:

	{							// internal user method
	USHORT offset = (USHORT) (dcb->DCB_cmn.DCB_expansion_length + FIELDOFFSET(IOP, IOP_ior));
	USHORT size = offset + sizeof(IOR) + dcb->DCB_max_sg_elements * sizeof(SGD);
	PIOP iop = IspCreateIop(size, offset, ISP_M_FL_MUST_SUCCEED);
	PIOR ior = &iop->IOP_ior;

	// Before submitting an internal request, the two DCB pointer fields
	// of the IOP must be completed. The criteria routine barfs otherwise.

	iop->IOP_original_dcb = (ULONG) dcb;
	iop->IOP_physical_dcb = (ULONG) dcb->DCB_cmn.DCB_physical_dcb;

	// Fill in required fields in the IOR. The earlier remarks about
	// external users apply here too. The main difference is how we
	// fill in the volume handle and "designator"

	ior->IOR_next = 0;					// used for request queueing by lots of downstream people
	ior->IOR_start_addr[1] = 0;			// assume only 32-bits worth of sector number
	ior->IOR_flags = IORF_VERSION_002;	// this is how IOS knows we're giving it a new-style IOR
	ior->IOR_private_client = offset;	// a common use for this field
	ior->IOR_req_vol_handle = dcb->DCB_cmn.DCB_vrp_ptr;
	ior->IOR_sgd_lin_phys = (ULONG) (ior + 1); // where scatter/gather descriptors can be built
	ior->IOR_num_sgds = 0;				// incremented by criteria routine, so must start at zero
	ior->IOR_vol_designtr = dcb->DCB_cmn.DCB_unit_number;

	// Fill in request-specific info. This is just like the external
	// client does it, except that an internal client would get
	// the partition starting sector from the DCB:

	ior->IOR_func = IOR_READ;			// flag as read request
	ior->IOR_flags |= IORF_SYNC_COMMAND // don't return until complete
		| IORF_HIGH_PRIORITY			// used for adminstrative-type requests, but optional
		| IORF_BYPASS_VOLTRK;			// we want to bypass volume tracking and just read the MBR
	ior->IOR_start_addr[0] = 0;			// reading sector zero
	ior->IOR_buffer_ptr = (ULONG) mbr;	// buffer to read into
	ior->IOR_xfer_count = 1;			// transfer 1 sector
//	ior->IOR_start_addr[0] += dcb->DCB_cmn.DCB_Partition_Start;

	// Use the internal criteria routine to massage the request:

	IlbIntIoCriteria(iop);

	// Submit the request using the internal interface. The third argument
	// to this interface is either zero (when you want the request to start
	// at the top of the calldown stack) or the address of the request
	// routine ABOVE the one you want called.

	IlbInternalRequest(iop, dcb, NULL);

	IspDeallocMem((PVOID) ((DWORD) ior - ior->IOR_private_client));
	}							// internal user method

	
	return FALSE;				// nothing further, so unload
	}							// OnSysDynamicDeviceInit

BOOL OnSysDynamicDeviceExit()
	{							// OnSysDynamicDeviceExit
	return TRUE;
	}							// OnSysDynamicDeviceExit
