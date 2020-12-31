/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** This header file came from MTF10.PS.
**
** Copyright, 1995, Samuel R. Blackburn
*/

#if ! defined( MICROSOFT_TAPE_FORMAT_HEADER )

#define MICROSOFT_TAPE_FORMAT_HEADER

/**  Name:          mtf.h
     Description:   Structures and constants used in writing MTF and OTC.
     Notes:         References are made throughout this header to a Logical
                    Block Address (LBA).  The LBA of a given DBLK is its
                    offset in Logical Blocks from the FIRST SSET of the set
                    it is associated with.  The size of a Logical Block for
                    a given tape is defined in the Tape Header.  The LBA is
                    used along with the Physical Block Address (PBA) to
                    calculate the physical location of a DBLK on tape.
                    TAPE and EOTM DBLKs have no associated SSET, so the
                    concept of an LBA is not defined for these blocks.
                    The SSET DBLK itself is at LBA 0.  However, if a set
                    crosses EOM and a continuation tape is written, the
                    LBA in the continuation SSET will contain an adjusted
                    logical offset, along with a PBA, to allow for the
                    calculation of physical locations of DBLKs on the
                    continuation tape.
**/
/* Defines for DBLK Common Block Attribute Bits
   The lower 16 bits of the Common Block Attribute are reserved for general
   attribute bits, (those which may appear in more than one type of DBLK), the upper
   16 bits are reserved for attributes which are specific to one type of DBLK.
   Note: the Common Block specific bit definitions overlap, and the block type is
         used to determine the meaning of a given bit.
*/
/* General: */
#define MTF_DB_CONT_BIT              BIT0  /* Indicates continuation DBLK  */
#define MTF_DB_ENCRYPT_BIT           BIT1  /* data is encrypted            */
#define MTF_DB_COMPRESS_BIT          BIT2  /* Data is  software compressed */
#define MTF_DB_EOS_AT_EOM_BIT        BIT3  /* End Of Media encountered
            during End Of Set processing */
#define MTF_DB_VAR_BLKS_BIT          BIT4  /* DBLK data is variable length */
#define MTF_DB_SESSION_BIT           BIT5  /* This set contains interleaved
                                              data streams(multiple sessions)*/
/* TAPE DBLK */
#define MTF_DB_SM_EXISTS             BIT16  /* Tape contains OTC Set Map    */
#define MTF_DB_FDD_ALLOWED           BIT17  /* Sets on tape may contain OTC
            File/Directory Detail        */
#define MTF_DB_SM_ALT_PART           BIT18  /* OTC Set Map is written on an
            alternate partition          */
#define MTF_DB_FDD_ALT_PART          BIT19  /* OTC File/Directory Data is
            written on an alternate partition */
#define MTF_DB_EOM_BETWEEN_SETS_BIT  BIT20 /* End Of Media encountered after End
                                              Of Set processing            */
/* SSET DBLK */
#define MTF_DB_FDD_EXISTS            BIT16  /* Set contains OTC F/DD        */
/* ESET DBLK */
#define MTF_DB_FDD_ABORTED_BIT       BIT16 /* OTC F/DD not written         */
#define MTF_DB_END_OF_FAMILY_BIT     BIT17 /* Tape may not be appended to  */
#define MTF_DB_ABORTED_SET_BIT       BIT18 /* Backup was aborted           */
#define MTF_DB_SET_VERIFIED_BIT      BIT19 /* On DC2000 Devices, CRC/ECC verify
                                              was done                     */
#define MTF_DB_SET_COMPARED_BIT      BIT17 /* This set was auto-verified after
                                             backup                       */
/* EOTM DBLK */
#define MTF_DB_NO_ESET_PBA           BIT16 /* Tape doesn't contain an ESET */
#define MTF_DB_INVALID_ESET_PBA      BIT17 /* PBA not available on device  */
/* Macro to make a UINT32 representation of the 4 byte IDs */
#define MTF_MARKER(a,b,c,d)
(UINT32)((((UINT32)d)<<24)+\
(((UINT32)c)<<16)+\
(((UINT32)b)<<8)+\
(UINT32)a))
/* Structure definition for unsigned 64 bit integers */
typedef struct {
     UINT32 lsw ;   /* Least significant 32 bits */
     UINT32 msw ;   /* Most significant 32 bits  */
} UINT64, *UINT64_PTR;
/* Compressed date structure for storing dates in minimal space on tape
     BYTE 0    BYTE 1    BYTE 2    BYTE 3    BYTE 4
    76543210  76543210  76543210  76543210  76543210
    yyyyyyyy  yyyyyymm  mmdddddh  hhhhmmmm  mmssssss  */
typedef struct {
     UINT8     dt_field[5] ;
} MTF_DATE_TIME, * MTF_DATE_TIME_PTR ;
/* Tape Address Structure used for size and offset of variable length
   fields in DBLKs (i.e. the backup set name in an SSET). */
typedef struct {
     UINT16    data_size ;        /* Size of the data   */
     UINT16    data_offset ;      /* Offset to the data */
} MTF_TAPE_ADDRESS, *MTF_TAPE_ADDRESS_PTR ;
/* Structure definitions for stream header/descriptor */
typedef struct {
   UINT32   stream_id ;             /* Identifier for a stream */
   UINT16   stream_fs_attribute ;   /* File System Attributes */
   UINT16   stream_tf_attribute ;   /* Tape Format Attributes */
   UINT64   stream_length ;         /* Length of the data stream */
   UINT16   encryption_algorithm ;  /* Data Encryption Algorithm */
   UINT16   compression_algorithm ; /* Data Compression Algorithm */
   UINT16   checksum ;              /* word-wise XOR checksum of prev fields */
} MTF_STREAM_DESC, * MTF_STREAM_DESC_PTR ;
typedef struct {
   UINT32   stream_id ;             /* Identifier for stream */
   UINT16   stream_fs_attribute ;   /* File System Attributes */
   UINT16   stream_tf_attribute ;   /* Tape Format Attributes */
   UINT64   stream_length ;         /* Length of the data stream */
   UINT16   encryption_algorithm ;  /* Data Encryption Algorithm */
   UINT16   compression_algorithm ; /* Data Compression Algorithm */
   UINT64   stream_object ;         /* LBA of DBLK associated with stream */
   UINT64   stream_session_id ;     /* LBA of Start of Session (SSES) DBLK */
   UINT16   checksum ;              /* word-wise XOR checksum of prev fields */
} MTF_ISTREAM_DESC, * MTF_ISTREAM_DESC_PTR ;
/* Defines for stream Identifers */
#define  MTF_STANDARD_DATA       MTF_MARKER( 'S','T','A','N' )
#define  MTF_NT_SECURITY_DATA    MTF_MARKER( 'N','A','C','L' )
#define  MTF_NTFS_EA_DATA        MTF_MARKER( 'N','T','E','A' )
#define  MTF_HPFS_SECURITY_DATA  MTF_MARKER( 'O','A','C','L' )
#define  MTF_HPFS_EA_DATA        MTF_MARKER( 'O','2','E','A' )
#define  MTF_OTC_SET_MAP_DATA    MTF_MARKER( 'T','S','M','P' )
#define  MTF_OTC_FILE_DD_DATA    MTF_MARKER( 'T','F','D','D' )
#define  MTF_PATH_NAME_STREAM    MTF_MARKER( 'P','N','A','M' )
#define  MTF_FILE_NAME_STREAM    MTF_MARKER( 'F','N','A','M' )
#define  MTF_MAC_RESOURCE        MTF_MARKER( 'M','R','S','C' )
#define  MTF_NOVELL_286          MTF_MARKER( 'N','2','8','6' )
#define  MTF_NOVELL_386          MTF_MARKER( 'N','3','8','6' )
#define  MTF_CRC_STREAM          MTF_MARKER( 'S','C','R','C' )
#define  MTF_NTFS_ALT_DATA       MTF_MARKER( 'A','D','A','T' )
#define  MTF_STRMPAD             MTF_MARKER( 'S','P','A','D' )





/* Defines for file system stream attributes */
#define  MTF_STREAM_PLAIN     0     /* No special conditions for stream */
#define  MTF_STREAM_MOD_READ  1     /* Stream altered by read operation */
#define  MTF_STREAM_CONT_SEC  2     /* Stream contains security data    */
#define  MTF_STREAM_NON_PORT  3     /* Data only for same OS saved from */
#define  MTF_CONT_STREAM      0x20  /* This stream is continued from a
                                       previous tape. */
/* Defines for tape format stream attributes */
#define  MTF_STREAM_CONTINUE  0     /* This is a continuation stream */
#define  MTF_STREAM_VARIABLE  1     /* The data size for this stream is variable */
#define  MTF_STREAM_VAR_END   2     /* This is the last part of variable length data */
/* Defines for data alignment within streams */
#define  MTF_STREAM_ALIGN_MASK   0xC000
#define  MTF_STREAM_ALIGN_4      0x0000   /* 4 byte alignment        */
#define  MTF_STREAM_ALIGN_2      0x4000   /* 2 byte alignment        */
#define  MTF_STREAM_ALIGN_4      0x8000   /* 1 byte alignment        */
#define  MTF_STREAM_ALIGN_RSVD   0xC000   /* Reserved for future use */
/* MTF DBLK types */
#define  MTF_TAPE_N     "TAPE"    /* Tape Header             */
#define  MTF_VOLB_N     "VOLB"    /* Volume Descriptor       */
#define  MTF_SSET_N     "SSET"    /* Start of Backup Set     */
#define  MTF_ESET_N     "ESET"    /* End of Backup Set       */
#define  MTF_EOTM_N     "EOTM"    /* End of Tape             */
#define  MTF_DIRB_N     "DIRB"    /* Directory Descriptor    */
#define  MTF_FILE_N     "FILE"    /* File Descriptor         */
#define  MTF_IMAG_N     "IMAG"    /* Image Descriptor        */
#define  MTF_CFIL_N     "CFIL"    /* Corrupt File Descriptor */
#define  MTF_ESPB_N     "ESPB"    /* End of Set Pad Descriptor */
#define  MTF_SSES_N     "SSES"    /* Start Of Session Descriptor */
#define  MTF_ESES_N     "ESES"    /* End of Session Descriptor */
#define  MTF_EOBJ_N     "EOBJ"    /* End of Object Descriptor */
/*   The "block header" is common to all logical tape blocks.  The software need only
     analyze the block header to determine the type of tape block it is and whether
     the software understands this particular tape block or not.  All ordering is
     little endian (INTEL low byte, high byte).    */
typedef struct {
     UINT8  block_type[4] ;         /* Unique identifier, see above      */
     UINT32 block_attribs ;         /* Tape Format attributes            */
     UINT16 offset_to_data ;        /* From start of DBLK in bytes       */
     UINT8  machine_os_id    ;      /* Machine/OS id where written       */
     UINT8  machine_os_version ;    /* Machine/OS version where written  */
     UINT64 displayable_size ;      /* Displayable data size             */
     UINT64 logical_block_address ; /* See note at top of file           */
     UINT64 session_id ;            /* Logical Block Address of SSES DBLK */
     UINT32 control_block_id ;      /* Used for error recovery           */
     MTF_TAPE_ADDRESS string_storage ;   /* Location of string storage   */
     MTF_TAPE_ADDRESS os_specific_data ; /* Location of OS specific data */
     UINT8  string_type ;           /* Single byte or UNICODE            */
     UINT8  reserved ;              /* Reserved for future use           */
     UINT16 hdr_chksm ;             /* Checksum of the block header.  The
                                       algorithm is: XOR each double word
                                       preceeding this one and store the result
                                       here. (When the checksum is verified the
                                       'block_type' is checked for a non_zero value
                                       also. */
} MTF_DB_HDR, * MTF_DB_HDR_PTR ;
/* Block Attribute Bit Definitions */
/* Tape Header DBLK Structure (TAPE) */
typedef struct {
     MTF_DB_HDR       block_header ;              /* Common header         */
     UINT32           tape_id_number ;            /* Unique family ID      */
     UINT32           tape_attributes ;           /* External Attributes   */
     UINT16           tape_seq_number ;           /* Sequence in family    */
     UINT16           password_encryption_algor ; /* Unique algorithm ID   */
     UINT16           ecc_alg ;                   /* Unique algorithm ID   */
     UINT16           otc_type ;                  /* On Tape Catalog Type  */
     MTF_TAPE_ADDRESS tape_name ;                 /* Offset/Size of string */
     MTF_TAPE_ADDRESS tape_description ;          /* Offset/Size of string */
     MTF_TAPE_ADDRESS tape_password ;             /* Offset/Size of string */
     MTF_TAPE_ADDRESS software_name ;             /* Offset/Size of string */
     UINT16           logical_block_size ;        /* Alignment factor      */
     UINT16           software_vendor_id ;        /* Backup Vendor         */
     MTF_DATE_TIME    tape_date ;
     UINT8            tape_format_version_major ; /* Integer value         */
} MTF_TAPE, * MTF_TAPE_PTR ;
#define MTF_ECC_NONE  0
#define MTF_OTC_TYPE  1  /* Type of OTC, this type value is reserved for MTF */
/* Start of Backup Set DBLK Structure (SSET) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           sset_attribs ;  /* External Attributes               */
     UINT16           pswd_encr_alg ; /* Password encryption algorithm ID  */
     UINT16           data_encr_alg ; /* Data encryption algorithm ID      */
     UINT16           data_comp_alg ; /* Data compressionalgorithm ID      */
     UINT16           set_number ;    /* Number of set in family           */
     MTF_TAPE_ADDRESS set_name ;      /* Offset/Size of set name string    */
     MTF_TAPE_ADDRESS set_descr ;     /* Offset/Size of description string */
     MTF_TAPE_ADDRESS set_password ;  /* Offset/Size of password string    */
     MTF_TAPE_ADDRESS user_name ;     /* Offset/Size of user name string   */
     UINT64           pba ;           /* Physical Block Address            */
     MTF_DATE_TIME    backup_date ;   /* Date/Time backup was started      */
     UINT8            sftwr_ver_mjr ; /* Major software revision (integer) */
     UINT8            sftwr_ver_mnr ; /* Minor software revision (integer) */
     INT8             time_zone ;     /* Time zone where backed up         */
     UINT8            tape_format_version_minor ; /*                       */
     UINT8            tape_catalog_version ;
}
MTF_SSET, *MTF_SSET_PTR;

/* End of Backup Set DBLK Structure (ESET) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           eset_attribs ;  /* External Attributes               */
     UINT32           corrupt_count ; /* Number of corrupt file in the set */
     UINT64           sm_pba ;        /* Physical Address of OTC Set Map   */
     UINT64           fdd_pba ;       /* PBA of OTC File/Directory Detail  */
     UINT16           fdd_seq_num ;   /* Tape number where F/DD begins     */
     UINT16           set_number ;    /* Number of set in family           */
     MTF_DATE_TIME    backup_date ;   /* Date and time of backup           */
} MTF_ESET, * MTF_ESET_PTR ;
/* End of Tape DBLK Structure (EOTM) */
typedef struct {
     MTF_DB_HDR  block_hdr ;          /* Common header                     */
     UINT32      eset_pba ;           /* Physical Address of last on tape  */
} MTF_EOTM, * MTF_EOTM_PTR ;
/* Directory DBLK Structure (DIRB) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           dirb_attribs ;  /* External Attributes               */
     MTF_DATE_TIME    last_mod_date ; /* Last Modified Date                */
     MTF_DATE_TIME    create_date ;   /* Date created                      */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date (before this)    */
     MTF_DATE_TIME    last_acc_date ; /* Last Access Date                  */
     UINT32           dir_id ;        /* For error recovery                */
     MTF_TAPE_ADDRESS dir_name ;      /* Offset/Size of path string        */
} MTF_DIR, * MTF_DIR_PTR ;
/* File DBLK Structure (FILE) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           file_attribs ;  /* External Attributes               */
     MTF_DATE_TIME    last_mod_date ; /* Last Modified Date                */
     MTF_DATE_TIME    create_date ;   /* Date created                      */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date (before this)    */
     MTF_DATE_TIME    last_acc_date ; /* Last Access Date                  */
     UINT32           dir_id ;        /* Of DIRB where file exists         */
     UINT32           file_id ;       /* For error recovery                */
     MTF_TAPE_ADDRESS file_name ;     /* Offset/Size of file name string   */
} MTF_FILE, * MTF_FILE_PTR ;
/* Image DBLK Structure (IMAG) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           imag_attribs ;  /* External Attributes               */
     UINT32           part_size ;     /* Size of partition in bytes        */
     UINT32           bytes_in_sect ; /* Number of bytes per sector        */
     UINT32           no_of_sectors ; /* Number of sectors                 */
     UINT32           rel_sect_no ;   /* Relative sector number            */
     UINT32           sect_part_no ;  /* Partition number of sector        */
     UINT16           part_sys_ind ;  /* Partition system indicator        */
     UINT16           no_of_heads ;   /* Number of heads                   */
     MTF_TAPE_ADDRESS part_name ;     /* Offset/Size of partition name     */
} MTF_IMAG, * MTF_IMAG_PTR ;
/* Corrupt File DBLK Structure (CFIL) */
typedef struct {
     MTF_DB_HDR  block_hdr ;          /* Common header                     */
     UINT32      cfil_attribs ;       /* External Attributes               */
     UINT32      file_id ;            /* Same as associated FILE           */
     UINT32      directory_id ;       /* Same as associated FILE           */
     UINT64      stream_offset ;      /* Offset in data stream where read failed. */
     UINT32      corrupt_stream_id ;  /* Data Stream where corruption occurs */
} MTF_CFIL, * MTF_CFIL_PTR ;

/* Volume DBLK Structure (VOLB) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT32           volb_attribs ;  /* External Attributes               */
     MTF_TAPE_ADDRESS device_name ;   /* Offset/Size of device name string */
     MTF_TAPE_ADDRESS volume_name ;   /* Offset/Size of volume name string */
     MTF_TAPE_ADDRESS machine_name ;  /* Offset/Size of machine name       */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date \(before this\)    */
} MTF_VOL, * MTF_VOL_PTR ;
/* Start Of Session DBLK Structure (SSES) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT64 session_id ;
    /* Logical Block Address of this DBLK */
} MTF_SSES, * MTF_SSES_PTR ;
/* End Of Session DBLK Structure (ESES) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT64           session_id ;    /* Logical Block Address of the SSES DBLK
                                         that marks the start of this session  */
} MTF_ESES, * MTF_ESES_PTR ;
/* End Of Object DBLK Structure (EOBJ) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
     UINT64           session_id ;
    /* Logical Block Address of the SSES DBLK
                                         that marks the start of this session  */
     UINT64           object_lba ;
    /* Logical Block Address of the DBLK
                                         that marks the start of the object just
                                         backed up in this session  */
} MTF_EOBJ, * MTF_EOBJ_PTR ;
/* End Of Set Pad DBLK Structure (ESPB) */
typedef struct {
     MTF_DB_HDR       block_hdr ;     /* Common header                     */
} MTF_ESPB, * MTF_ESPB_PTR ;
/ On Tape Catalog (OTC) Structures */
/* Set Map Header Structure */
typedef struct {
     UINT32    family_id ;    /* Unique tape family ID                     */
     UINT16    num_set_recs ; /* Number of Set Map entries to follow       */
     UINT8     pad[2] ;       /* Ensure 4 byte alignment of first SM entry */
} MTF_SM_HDR, * MTF_SM_HDR_PTR ;
/* Set Map Entry Structure */
typedef struct {
     UINT16           length ;        /* Length of entry (including
                                         strings) in bytes                 */
     UINT16           sset_seq_num ;  /* Tape number where set begins      */
     UINT32           blk_attribs ;   /* Tape Format Attributes            */
     UINT32           set_attribs ;   /* External Attributes               */
     UINT64           sset_pba ;      /* Address of associated SSET        */
     UINT64           fdd_pba ;       /* Address of associated F/DD        */
     UINT16           fdd_seq_num ;   /* Tape number where F/DD begins     */
     UINT16           set_num ;       /* Backup Set Number                 */
     UINT64           lba ;           /* See note at top of file           */
     UINT32           num_dirs ;      /* Number of directories in set      */
     UINT32           num_files ;     /* Number of files in set            */
     UINT32           corrupt_count ; /* Number of corrupt files in set    */
     UINT64           disp_size ;     /* Displayable size of assoc. SSET   */
     UINT16           num_volumes ;   /* No. of OTC vol entries to follow  */
     UINT16           pswd_encr_alg ; /* Password Encryption Algorithm ID  */
     MTF_TAPE_ADDRESS set_name ;      /* Offset/Size of set name string    */
     MTF_TAPE_ADDRESS password ;      /* Offset/Size of description string */
     MTF_TAPE_ADDRESS set_descr ;     /* Offset/Size of password string    */
     MTF_TAPE_ADDRESS user_name ;     /* Offset/Size of user name string   */
     MTF_DATE_TIME    backup_date ;   /* Date/Time backup was started      */
     INT8             time_zone ;     /* Time zone where backed up         */
     UINT8            os_id ;         /* Machine/OS id where written       */
     UINT8            os_ver ;        /* Machine/OS version where written  */
     UINT8            string_type ;   /* Type of strings stored            */
     UINT8            tape_format_version_minor ;
     UINT8            tape_catalog_version;
} MTF_SM_ENTRY, * MTF_SM_ENTRY_PTR ;
/* Common File/Directory Detail Entry Header Structure */
typedef struct {
     UINT32    length ;               /* Length of entry (including
                                         strings) in bytes                 */
     UINT8     type[4] ;              /* As in associated DBLK             */
     UINT16    seq_num ;              /* Tape number of associated DBLK    */
     UINT32    blk_attribs ;          /* Tape Format Attributes            */
     UINT32    lba ;                  /* See note at top of file           */
     UINT64    disp_size ;            /* Displayable size of assoc. DBLK   */
     INT32     link ;
     UINT8     os_id ;                /* Machine/OS id where written       */
     UINT8     os_ver ;               /* Machine/OS version where written  */
     UINT8     string_type ;          /* Type of strings stored            */
     UINT8     pad ;                  /* Pad to alignment boundary         */
} MTF_FDD_HDR, * MTF_FDD_HDR_PTR ;
/* File/Directory Detail Volume Entry Structure */
typedef struct {
     UINT32           vol_attribs ;   /* volb_attribs of associated VOLB   */
     MTF_TAPE_ADDRESS device_name ;   /* Offset/Size of device name string */
     MTF_TAPE_ADDRESS vol_name ;      /* Offset/Size of volume name string */
     MTF_TAPE_ADDRESS machine_name ;  /* Offset/Size of machine name       */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date (before this)    */
} MTF_FDD_VOL, * MTF_FDD_VOL_PTR ;
/* File/Directory Detail Directory Entry Structure */
typedef struct {
    MTF_DATE_TIME    last_mod_date ; /* Last Modified Date                */
     MTF_DATE_TIME    create_date ;   /* Date created                      */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date (before this)    */
     MTF_DATE_TIME    last_acc_date ; /* Last Access Date                  */
     UINT32           dir_attribs ;   /* dirb_attribs of associated DIRB   */
     MTF_TAPE_ADDRESS dir_name ;      /* Offset/Size of path string        */
} MTF_FDD_DIR, * MTF_FDD_DIR_PTR ;
/* File/Directory Detail File Entry Structure */
typedef struct {
     MTF_DATE_TIME    last_mod_date ; /* Last Modified Date                */
     MTF_DATE_TIME    create_date ;   /* Date created                      */
     MTF_DATE_TIME    backup_date ;   /* Last Backup Date (before this)    */
     MTF_DATE_TIME    last_acc_date ; /* Last Access Date                  */
     UINT32           file_attribs ;  /* file_attribs of associated FILE   */
     MTF_TAPE_ADDRESS file_name ;     /* Offset/Size of file name string   */
} MTF_FDD_FILE, * MTF_FDD_FILE_PTR ;

#endif // MICROSOFT_TAPE_FORMAT_HEADER
