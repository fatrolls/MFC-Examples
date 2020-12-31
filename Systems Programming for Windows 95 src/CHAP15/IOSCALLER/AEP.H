/****************************************************************************
*                                                                           *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY     *
* KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE       *
* IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR     *
* PURPOSE.                                                                  *
*                                                                           *
* Copyright (C) 1993-95  Microsoft Corporation.  All Rights Reserved.       *
*                                                                           *
****************************************************************************/

/****************************************************************************\
*
* AEP (Asynchronous Event Packet) Data Structure
*
\****************************************************************************/

#define 	AEP_PrivateLen          32      /* Random Length Assignment         */

/* Definitions for AER Functions */

#define AEP_INITIALIZE				0	/* initialize driver/interface */
#define AEP_SYSTEM_CRIT_SHUTDOWN 1	/* indicates system critical shutdown */
#define AEP_BOOT_COMPLETE			2	/* booting done - switch to run time*/
#define AEP_CONFIG_DCB				3	/* configure device */
#define AEP_UNCONFIG_DCB 			4	/* unconfigure device */
#define AEP_IOP_TIMEOUT         	5	/* iop timeout occured */
#define AEP_DEVICE_INQUIRY      	6	/* get device indentification data  */
#define AEP_HALF_SEC				7	/* 1/2 second interval notification */
#define AEP_1_SEC					8	/* one second interval notification */
#define AEP_2_SECS					9	/* two second interval notification */
#define AEP_4_SECS					10	/* four second interval notification*/
#define AEP_DBG_DOT_CMD				11	/* parameters for '.I' debug command*/
#define AEP_ASSOCIATE_DCB			12	/* associate logical DCBs w/ physical */
#define AEP_REAL_MODE_HANDOFF		13	/* IFSMGR about to hook in */
#define AEP_SYSTEM_SHUTDOWN 		14	/* indicates system shutdown */
#define AEP_UNINITIALIZE			15	/* uninitialize driver/interface */
#define AEP_DCB_LOCK  				16	/* logical dcb is going to be locked */
#define AEP_MOUNT_NOTIFY			17	/* notify drivers of volume mount */
#define AEP_CREATE_VRP				18	/* notify drivers of VRP creation */
#define AEP_DESTROY_VRP				19	/* notify drivers of VRP destruction */
#define AEP_REFRESH_DRIVE			20	/* tell drivers to refresh drive data */
#define AEP_PEND_UNCONFIG_DCB		21	/* tell drivers that DCB removal is pending */
#define AEP_1E_VEC_UPDATE			22	/* notify int13 of a possible change in the */
							/* int 1eh vector for copy protection */
#define AEP_CHANGE_RPM			23	/* inform driver vsd to change the floppy spindle speed */

#define AEP_MAX_FUNC				23 /* maximum legal function */

typedef struct AEPHDR { /* */

	USHORT  	AEP_func;			/* Function Code                    */
	USHORT  	AEP_result;			/* result: zero = no error          */
	ULONG   	AEP_ddb;			/* driver data block Pointer        */
	UCHAR 	AEP_lgn;				/* curr. load group num. -- got from DVT */
	UCHAR		AEP_align[3];		/* preserve dword alignment */

} AEP, *PAEP;

/* generic AEP result codes follow */

#define AEP_SUCCESS           0  /* good status */
#define AEP_FAILURE          -1  /* bad status */

/*
**	AEP_INITIALIZE definition:
**
**	IOS makes this during the registration of a layer driver. In the case
** of a port driver registration IOS checks to see if the init was a success.
** If so IOS sends down an AEP_INQUIRE_DCB discussed below. If the 
** AEP_INQUIRE was successful IOS sends an AEP_CONFIG_DCB call to all the
** layer drivers. It then repeats the AEP_INQUIRE_DCB call. In the case of
** SCSI IOS makes as many inquiries as is specified in AEP_bi_i_max_target
** returned in the AEP_INITIALIZE call. Also in the case of SCSI the scan 
** order can be sepcified AEP_bi_flags. If AEP_BI_FL_SCSI_SCAN_DOWN is set 
** the scanning is done in the reverse order. 
**
** The driver can also set AEP_BI_FL_SEND_CONFIG_AGAIN in AEP_bi_flags. If 
** this is set IOS will redo the whole sequence of AEP_INITIALIZE, 
** AEP_INQUIRE and AEP_CONFIG again. This is typically not needed as IOS
** will call the port driver again if the port driver controls more than 
** controller. 
**
** Note that in the case of a non-scsi port diver IOS sends down as 
** AEP_INQUIRY until the driver says AEP_NO_MORE_DEVICES in the result 
** field.  If the result of the AEP_INQUIRY was AEP_NO_INQ_DATA then the
** next location is inquired and there is no config call sent out.
**
*/
typedef struct AEP_bi_init { /* */

	struct AEPHDR	AEP_bi_i_hdr;		/* Standard Header */
	ULONG		AEP_bi_reference_data; 	/* optional value passed in from drp */
	UCHAR		AEP_bi_flags;				/* flags defined below */
	CHAR		AEP_bi_i_max_target;		/* max scsi target id */
	CHAR		AEP_bi_i_max_lun;			/* max scsi lun */
	ULONG		AEP_bi_i_dcb;				/* init dcb for port drivers */
	PVOID		AEP_bi_i_hdevnode;  		/* handle to devnode for this adapter */
	PVOID		AEP_bi_i_regkey;    		/* registry key for this adapter */
	UCHAR		AEP_bi_i_align[1];		/* preserve dword alignment */

} AEP_bi_init, *PAEP_bi_init;

/*
** define flags for AEP_bi_flags
*/

#define AEP_BI_FL_SCSI_SCAN_DOWN 0x01    /* device requires reverse ID scanning */
#define AEP_BI_FL_SEND_CONFIG_AGAIN 0x02 /* device wants this config info again */


/*
**	AEP_DEVICE_INQUIRY definition:
**
** This call is of interest only to port drivers. The inquiry data is 
** filled into the DCB_product_ID, DCB_vendor_ID and DCB_REV_LEVEL fields.
** Refer to discussion of AEP_INITIALIZE above for more details. 
**
*/
typedef struct AEP_inquiry_device { /* */

	struct AEPHDR	AEP_i_d_hdr; 	/* Standard Header */
	ULONG		AEP_i_d_dcb;			/* dcb pointer	*/

} AEP_inquiry_device, *PAEP_inquiry_device;

/* AEP_i_d_status values */

#define AEP_NO_INQ_DATA      1  /* No inquiry data available                */
#define AEP_NO_MORE_DEVICES  2  /* no more devices of this type             */


/*
**	AEP_UNINITIALIZE definition:
**
** This is broadcast by IOS during the process of deallocating a DDB. Note 
** that as far as port drivers are concerned there is typically one DDB
** per controller. Port drivers use this AEP call to dealloc any 
** resources that they may have allocated to handle i/o to the controller
** represented by that DDB. For instance, IRQ and port trappings should be 
** be freed at this time.
**
** Note that the DDB is part of the standard AEP header.  
**
*/
typedef struct AEP_bi_uninit { /* */

	struct AEPHDR	AEP_bi_u_hdr; 	/* Standard Header */

} AEP_bi_uninit, *PAEP_bi_uninit;


/*
**	AEP_BOOT_COMPLETE definition:
**
** This call out is made by IOS at init_complete time and at the end of 
** loading, initing/registering a port driver. 
**
** If a driver chooses to be unloaded at this time it should return an error
** on this AEP. This will result in deregistration and unloading of the 
** driver.  No DDB pointer is passed on this call, so only one call will be 
** received. For instance a VSD can return failure if it has determined that
** it has not inserted itself in any one of the DCBs in the system.
**
*/
typedef struct AEP_boot_done { /* */

	struct AEPHDR	AEP_b_d_hdr; 	/* AEP_BOOT_COMPLETE */

} AEP_boot_done, *PAEP_boot_done;


/*
**	AEP_CONFIG_DCB definition:
**
** IOS circulates all the DCBs in the system, both physical and logical, to
** all the layer drivers via this call. This is made as and when each layer
** is initialized. Typicall a port driver init results in the creation of
** one or more physical DCBs. These are circulated through all the layers.
** Each layer driver can choose to insert itself in the call down list for
** this DCB if necessary. For instance a driver interested in seeing requests
** to a CDRON will insert itself in that DCB. The device types are defined 
** in dcb.h.
**
**	Also if a layer satisfies a specific demand that is stipulated in the DCB
** dmd flags it must turn off the demand bit, indicating to the layers above
** that the demand has been met.
**
*/
typedef struct AEP_dcb_config { /* */

	struct AEPHDR	AEP_d_c_hdr; 	/* Standard Header */
	ULONG		AEP_d_c_dcb;			/* 32-bit ptr to DCB */
				
} AEP_dcb_config, *PAEP_dcb_config;


/*
**	AEP_UNCONFIG_DCB definition:
**
** This notification is made by IOS when a DCB is being destroyed. A layer
** typically just makes a note of the fact that the DCB is going away. For
** instance the driver could dec a count of DCBs that it has inserted itself
** in if the DCB being UNCONFIG'd is one that is of interest to it. Then 
** in a subseuqent AEP_BOOT_COMPKETE call it could return an error if the 
** count is 0.
** 
*/
typedef struct AEP_dcb_unconfig { /* */

	struct AEPHDR	AEP_d_u_hdr; 	/* Standard Header */
	ULONG		AEP_d_u_dcb;			/* 32-bit offset of DCB */

} AEP_dcb_unconfig, *PAEP_dcb_unconfig;


/*
**	AEP_PEND_CONFIG_DCB definition:
**
** This is the first AEP call the IOS makes when a DCB is being destroyed.
** Layer drivers are expected to not initiate any further i/o to the device
** after this call is made. 
*/
typedef struct AEP_dcb_unconfig_pend { /* */

	struct AEPHDR	AEP_d_u_p_hdr;	/* AEP_PEND_UNCONFIG_DCB */
	ULONG		AEP_d_u_p_dcb;			/* 32-bit offset of DCB    */

} AEP_dcb_unconfig_pend, *PAEP_dcb_unconfig_pend;


/*
** AEP_IOP_TIMEOUT definition:
**
** Once an IOP is issued to IOS via IOS_SendCommand a 15 second timer is 
** started on the IOP. When this goes to zero all layer drivers are notified
** of this IOP via this AEP. Note that if the i/o is done and the IOP is
** released within 15 seconds this will not happen. 
**
*/
typedef struct AEP_iop_timeout_occurred { /* */

	struct AEPHDR	AEP_i_t_o_hdr;	/* Standard Header */
	ULONG		AEP_i_t_o_iop;			/* pointer to offending iop */
				
} AEP_iop_timeout_occurred, *PAEP_iop_timeout_occurred;


/*
**	AEP_DBG_DOT_CMD definition:
**
** The AEP_dot_command function provides a means for debug "dot" commands 
** entered by the user into the windows system debugger to be propogated to
** each layer.   So, a layer can easily implement support for a "dot" 
** command without having to directly interface with the debugger.
**
** Each layer will receive a call for each debug "dot" command that begins 
** with ".I" at their AEP handler, with the AEP packet as defined below:
**
** The AEP_d_c_pkeyword member provides a pointer to the subkeyword typed by 
** the user.   For example ".IXYZ" will result in the "XYZ" keyword being
** passed in.   The AEP_d_c_key_len member contains the length of this 
** keyword.
**
** The AEP_d_c_flags member contains flags which indicate which numeric 
** parameters are present.  For example, if the user typed ".IXYZ 1 46", 
** the flags AEP_NUM_1_PRES and AEP_NUM_2_PRES flags would be set,  
** AEP_d_c_num_1 member would contain hexadecimal 1, and AEP_d_c_num_2 would 
** contain hexadecimal 46.
**
*/
typedef struct AEP_dot_command { /* */

	struct AEPHDR	AEP_i_t_o_hdr;	/* Standard Header */
	UCHAR		AEP_d_c_flags;			/* AEP flags */
	PVOID		AEP_d_c_pkeyword;		/* pointer to keyword string	*/
	UCHAR		AEP_d_c_key_len;		/* length of keyword (max 32)	*/
	ULONG		AEP_d_c_num_1;			/* first numeric parameter	*/
	ULONG		AEP_d_c_num_2;			/* second numeric parameter */
	ULONG		AEP_d_c_num_3;			/* third numeric parameter	*/

} AEP_dot_command, *PAEP_dot_command;


/* AEP_dot_command flags */

#define AEP_D_C_NUM_1_PRES      0x01  /* numeric parameter 1 is present     */
#define AEP_D_C_NUM_2_PRES      0x02  /* numeric parameter 2 is present     */
#define AEP_D_C_NUM_3_PRES      0x04  /* numeric parameter 3 is present     */
#define MAX_DOT_CMD_KEYWORD_SIZE 16 /* max number of chars in .I keyword    */


/*
** AEP_SYSTEM_SHUTDOWN definition:
**
** This broadcast is made to the layer drivers at System_Exit time.
*/
typedef struct AEP_sys_shutdown { /* */

	struct AEPHDR	AEP_s_s_hdr;	/* AEP_SYSTEM_SHUTDOWN */

} AEP_sys_shutdown, *PAEP_sys_shutdown;


/*
**	AEP_SYSTEM_CRIT_SHUTDOWN definition:
**
** This broadcast is made to the layer drivers at Sys_Critical_Exit time.
*/
typedef struct AEP_sys_crit_shutdown { /* */

	struct AEPHDR	AEP_s_c_s_hdr; /* AEP_SYSTEM_CRIT_SHUTDOWN */
										
} AEP_sys_crit_shutdown, *PAEP_sys_crit_shutdown;


/*
**	AEP_ASSOCIATE_DCB definition:
**
** This issued by IOS from an ISP_ASSOCIATE_DCB sercice. Refer to ISP.H
** for a description. Essentially a layer driver can specify additional 
** logical volumes that are associated with a particulr physical drive that
** the TSD cannot deduce for itself. Note that these logical volumes need 
** to be present in real mode as well.  
**
**	BUGBUG: This was originally intended for use by the compression driver. 
** This is no longer the case. The compression driver uses the 
** ISP_ASSOCIATE_DCB for this purpose. This service may be removed for M7. 
**
*/
typedef struct AEP_assoc_dcb {

	struct AEPHDR	AEP_a_d_hdr; 	/* AEP_ASSOCIATE_DCB */
	PVOID 	AEP_a_d_pdcb;			/* Pointer to physical DCB */
	ULONG 	AEP_a_d_drives;		/* Bitmap of associated logical drives */

} AEP_assoc_dcb, *PAEP_assoc_dcb;


/*
** AEP_REAL_MODE_HANDOFF definition:
**
** This is linked to the IRS_rm_handoff command. Refer to irs.h. This IRS 
** is made by the IFSMGR just before it hooks out the int 21 vector. IOS in
** turn informs the layer drivers of this by making this AEP broadcast. This
** indicates to the drivers that this is the last chance they have to do 
** int 21s through DOS. 
*/
typedef struct AEP_rm_handoff {

	struct AEPHDR	AEP_r_m_h_hdr;	/* AEP_REAL_MODE_HANDOFF */

} AEP_rm_handoff, *PAEP_rm_handoff;


/*
**	AEP_DCB_LOCK definition:
**
** This call is linked to the IRS_QUERY_VOLUME_LOCK service. Refer to irs.h.
** This IRS call is made by the IFSMGR when an exclusive volume lock is 
** about to be serviced. IOS in turn queries all layer drivers to determine
** whether there are any volumes that are associated with the volume that 
** is going to be locked. For instance if a compression driver recieves this
** AEP informing it that one of its host volumes is going to be locked, it 
** needs to indicate all the compressed volumes associated with that host 
** in the AEP_d_l_drives bitmap. This ensures that the IFSMGR will lock all
** the compressed volumes as well. 
**
** Also the layer drivers should stop doing caching or any thing else that 
** that should not be done on a volume when a lock is in place. Please refer
** to the exclusive lock specification for more details. Note that the 
** layer drivers will be informed about a exclusive volume lock release via
** the AEP_drive_refresh call.
**
*/
typedef struct AEP_lock_dcb {

	struct AEPHDR	AEP_d_l_hdr; 	/* AEP_DCB_LOCK */
	PVOID 	AEP_d_l_pdcb;			/* Pointer to logical DCB */
	ULONG 	AEP_d_l_drives;		/* Bitmap of logical drives */
	UCHAR 	AEP_d_l_designtr;
	UCHAR 	AEP_d_l_align[3];		/* pad to dword boundary */

} AEP_lock_dcb, *PAEP_lock_dcb;


/*
**  AEP_MOUNT_NOTIFY definitions
**
**  This call is made when the IFS Manager has successfully mounted a
**  new volume, but before the operation which caused the mount has
**  been completed.
**
**	This call is made to allow a driver which creates child volumes from
**  special files on the volume (e.g., a DBLSPACE driver which causes
**  CVFs to appear as volumes) to find such files and prepare them
**  for mounting.  Conceivably, it could be used by other drivers
**  who want to know when a new volume is mounted for other purposes.
**
**  The callee's response can have the following effects:
**
**  - The original volume can be associated with a different drive,
**    e.g., the original volume could be moved from drive A: to
**    drive H:.  If such a move is made and the target drive is
**    already in use, IFSMGR will attempt to unmount the current
**    volume for that drive.  Note that either or both the original
**    volume's effective and actual drives may be changed.  E.g.,
**    drive G: is the host for DBLSPACE drive E:, E: and G: are
**    swapped (meaning if there were no compressed drive E:, G:
**    would be known as E:), and G: is also host for another
**    compressed drive H:.  E:, G:, and H: are all visible in
**    real mode.  The user's first access may touch any of these
**    drives first.  Whichever drive letter is used first, G: will
**    be the first drive mounted.  Thus, the Compressed Volume
**    Manager will respond that the drive's effective name is really
**    G: and its actual name is really E:.
**
**  - A bitmap of child volumes to mount can be returned.  The low-
**    order bit corresponds to drive A: and so forth.  For each
**    bit in the bitmap, the IFSMGR will send a mount child volume
**    command to the same FSD that mounted the original volume.
**    The child volumes and their parent (the original volume) share
**    the same VRP; this is the mechanism by which the relationship
**    among the volumes is maintained.
**
**  If the returned bitmap is zero, then the IFSMGR takes no additional
**  action regardless of any change in the drive number.  Thus, the
**  valid responses are to do nothing, or to cause one or more child
**  volumes to be mounted, optionally moving the parent to a new
**  drive while reusing the original drive for one of the child
**  volumes.
*/

typedef struct AEP_mnt_notify {

	struct AEPHDR	AEP_m_n_hdr;/* AEP_MOUNT_NOTIFY */
	PVOID 	AEP_m_n_pvrp;		/* VRP of drive */
	ULONG 	AEP_m_n_drivemap;	/* Bitmap of "child" volumes */
	ULONG 	AEP_m_n_drive;		/* Drive number of drive just mounted */
	ULONG	AEP_m_n_effective_drive; /* Effective drive number */
	ULONG	AEP_m_n_actual_drive; /* Actual drive number */

} AEP_mnt_notify, *PAEP_mnt_notify;

#define	AEP_M_N_SUCCESS	AEP_SUCCESS /* Call succeeded */


/*
** AEP_CREATE_VRP/AEP_DESTROY_VRP definitions
**
**	AEP_CREATE_VRP
**
**  Call is made when a VRP "goes into service", i.e., when it is
**  determinded by the IFSMGR that a VRP describes a newly mounted volume.
**  VRPs are actually created any time a mount is attempted, but this
**  message is not sent if the mount fails for any reason (among which
**  is ERROR_VOLUME_EXISTS, a successful remount of a volume).
**  The mounted volume must be a parent volume; this call is not
**  issued when child volumes are successfully mounted.
**
**  This call is made for symmetry with AEP_DESTROY_VRP.  There are
**  no known users of this call.
**
**  This call is informational.  The callee's response is ignored.
**
**	AEP_DESTROY_VRP
**
**  Call is made when a VRP "goes out of service", i.e., when it is
**  determinded by the IFSMGR that the volume and any child volumes
**  associated with the volume have been fully unmounted by the FSD
**  that mounted them.
**
**  This call is used, for example, by the DBLSPACE VxD to determine
**  when it can dispose of its data structures for a particular set
**  of child volumes.
**
**  This call is informational.  The callee's response is ignored.
**
*/
typedef struct AEP_vrp_create_destroy {

	struct AEPHDR	AEP_v_cd_hdr; 	/* AEP_CREATE_VRP/AEP_DESTROY_VRP */
	PVOID 	AEP_v_cd_pvrp;	   	/* VRP pointer */
	ULONG 	AEP_v_cd_drive;		/* Drive number */

} AEP_vrp_create_destroy, *PAEP_vrp_create_destroy;


/*
** AEP_REFRESH_DRIVE definitions:
**
**	This call is made by IOS to inform the layer drivers that an exclusive
** lock on the volume specified in AEP_d_r_drive is being released. Note 
** that at this point all on disk file system related data structures could
** have been moved. Please refer to the exclusive vol lock spec for more 
** details. 
** 
*/
typedef struct AEP_drive_refresh {

	struct AEPHDR	AEP_d_r_hdr;	/* AEP_REFRESH_DRIVE */
	ULONG 	AEP_d_r_drive;			/* Drive number */

} AEP_drive_refresh, *PAEP_drive_refresh;


/*
** AEP_UPDATE_1e_VEC definitions:
**
**	This call is made by IOS to inform the int13 vxd that the vector associated
** with the diskette parameter table has been updated by IO.SYS, and int13
** should use the current value as the base vector to compare for copy proctection
** 
*/
typedef struct AEP_update_1e_vec {

	struct AEPHDR	AEP_u_1e_hdr;	/* AEP_REFRESH_DRIVE */

} AEP_update_1e_vec, *PAEP_update_1e_vec;


/*
** AEP_CHANGE_RPM definitions:
**
**	This call is made by IOS to inform the 3mode floppy driver vsd to
** change the floppy spindle speed to 360 or 300 rpm.
** 
*/
typedef struct AEP_rpm_change {

	struct AEPHDR	AEP_rc_hdr;	/* AEP_CHANGE_RPM */
	USHORT AEP_rc_speed;		/* target floppy spindle speed */

} AEP_rpm_change, *PAEP_rpm_change;

#define AEP_RC_360_RPM	    0x0001	/* Set floppy spindle to 360 rpm */
#define AEP_RC_300_RPM	    0x0002	/* Set floppy spindle to 300 rpm */


