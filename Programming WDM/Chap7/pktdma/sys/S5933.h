// S5933.H -- Programming interface for AMCC S5933
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#ifndef S5933_H
#define S5933_H

// References are to page numbers in "PCI Products Data Book S5920/S5933"
// (Applied Micro Curcuits Corporation 1998)

// With regard to DMA, note that a "read" means a memory-to-device transfer,
// whereas a "write" means a device-to-memory transfer

///////////////////////////////////////////////////////////////////////////////
// Operation register offsets from base port address (I/O mapped) -- p. 3-51

#define OMB1		0x00		// outgoing mailbox register 1
#define OMB2		0x04		// outgoing mailbox register 2
#define OMB3		0x08		// outgoing mailbox register 3
#define OMB4		0x0C		// outgoing mailbox register 4
#define IMB1		0x10		// incoming mailbox register 1
#define IMB2		0x14		// incoming mailbox register 2
#define IMB3		0x18		// incoming mailbox register 3
#define IMB4		0x1C		// incoming mailbox register 4
#define FIFO		0x20		// bidirectional FIFO port
#define MWAR		0x24		// write address register
#define MWTC		0x28		// write transfer count register
#define MRAR		0x2C		// read address register
#define MRTC		0x30		// read transfer count register
#define MBEF		0x34		// mailbox empty/full status
#define INTCSR		0x38		// interrupt control/status register
#define MCSR		0x3C		// bus master control/status register

///////////////////////////////////////////////////////////////////////////////
// Bits in INTCSR register (pp. 3-59 ff.)

// Control Flags:

#define INTCSR_OMBI_BYTE_SELECT_MASK	0x00000003	// byte select for outgoing mailbox interrupt 
#define INTCSR_OMBI_BYTE_SELECT_SHIFT	0
#define INTCSR_OMBI_REG_SELECT_MASK		0x0000000C	// register select for ditto
#define INTCSR_OMBI_REG_SELECT_SHIFT	2
#define INTCSR_OMBI_ENABLE				0x00000010	// ditto enabled if "1"

//										0x000000E0	// reserved (always zero)
#define INTCSR_IMBI_BYTE_SELECT_MASK	0x00000300	// byte select for incoming mailbox interrupt
#define INTCSR_IMBI_BYTE_SELECT_SHIFT	8
#define INTCSR_IMBI_REG_SELECT_MASK		0x00000C00	// register select for ditto
#define INTCSR_IMBI_REG_SELECT_SHIFT	10
#define INTCSR_IMBI_ENABLE				0x00001000	// ditto enabled if "1"

//										0x00002000	// reserved (always zero)
#define INTCSR_WTCI_ENABLE				0x00004000	// interrupt on write transfer complete
#define INTCSR_RTCI_ENABLE				0x00008000	// interrupt on read transfer complete

#define INTCSR_MB1						0			// mailbox register 1
#define INTCSR_MB2						1			// mailbox register 2
#define INTCSR_MB3						2			// mailbox register 3
#define INTCSR_MB4						3			// mailbox register 4

#define INTCSR_BYTE0					0			// mailbox byte 0
#define INTCSR_BYTE1					1			// mailbox byte 1
#define INTCSR_BYTE2					2			// mailbox byte 2
#define INTCSR_BYTE3					3			// mailbox byte 3

// Status flags:

#define INTCSR_OMBI						0x00010000	// outgoing mailbox interrupt (R/WC)
#define INTCSR_IMBI						0x00020000	// incoming mailbox interrupt (R/WC)
#define INTCSR_WTCI						0x00040000	// write transfer complete interrupt (R/WC)
#define INTCSR_RTCI						0x00080000	// read transfer complete interrupt (R/WC)
#define INTCSR_MASTER_ABORT				0x00100000	// interrupt due to master abort (R/WC)
#define INTCSR_TARGET_ABORT				0x00200000	// interrupt due to target abort (R/WC)
//										0x00400000	// reserved (always zero)
#define INTCSR_INTERRUPT_PENDING		0x00800000	// summary flag (R/O)

#define INTCSR_INTERRUPT_MASK			0x003F0000	// mask for all interrupt flags

// FIFO & endian management flags:

#define INTCSR_ENDIAN_NONE				0			// no conversion
#define INTCSR_ENDIAN_16				1			// 16-bit endian conversion
#define INTCSR_ENDIAN_32				2			// 32-bit endian conversion
#define INTCSR_ENDIAN_64				3			// 64-bit endian conversion
#define INTCSR_ENDIAN_MASK				0x03000000	// mask for endian conversion
#define INTCSR_ENDIAN_SHIFT				24			// shift for endian conversion

#define INTCSR_ADVANCE_BYTE0			0			// advance on byte 0
#define INTCSR_ADVANCE_BYTE1			1			// advance on byte 1
#define INTCSR_ADVANCE_BYTE2			2			// advance on byte 2
#define INTCSR_ADVANCE_BYTE3			3			// advance on byte 3
#define INTCSR_ADVANCE_PCI_MASK			0x0C000000	// mask for pci interface advance control
#define INTCSR_ADVANCE_PCI_SHIFT		26			// shift for ditto
#define INTCSR_ADVANCE_ADDON_MASK		0x30000000	// mask for add-on interface advance control
#define INTCSR_ADVANCE_ADDON_SHIFT		28			// shift for ditto

#define INTCSR_IN_TOGGLE				0x40000000	// inbound fifo dword toggle bytes 4-7 (must have endian_64 if set)
#define INTCSR_OUT_TOGGLE				0x80000000	// outbound fifo dword toggle bytes 4-7 (must have endian_64 if set)

///////////////////////////////////////////////////////////////////////////////
// Bits in MCSR (pp. 3-63 ff.)

#define MCSR_RFIFO_FULL					0x00000001	// PCI to add-on FIFO is full
#define MCSR_RFIFO_4PLUS				0x00000002	// at least 4 empty words in PCI to add-on FIFO
#define MCSR_RFIFO_EMPTY				0x00000004	// PCI to add-on FIFO completely empty
#define MCSR_WFIFO_FULL					0x00000008	// add-on to PCI FIFO is full
#define MCSR_WFIFO_4PLUS				0x00000010	// at least 4 valid words in add-on to PCI FIFO
#define MCSR_WFIFO_EMPTY				0x00000020	// add-on to PCI FIFO is completely empty
#define MCSR_RTCZ						0x00000040	// read transfer (PCI to add-on) count is zero
#define MCSR_WTCZ						0x00000080	// write transfer (add-on to PCI) count is zero
#define MCSR_WRITE_PRIORITY				0x00000100	// give writes priority over reads
#define MCSR_WRITE_NEED4				0x00000200	// don't request bus until at least 4 FIFO locations filled
#define MCSR_WRITE_ENABLE				0x00000400	// enable bus-mastering write (to memory) transfer
//										0x00000800	// reserved (always zero)
#define MCSR_READ_PRIORITY				0x00001000	// give reads priority over writes
#define MCSR_READ_NEED4					0x00002000	// don't request bus until at least 4 FIFO locations empty
#define MCSR_READ_ENABLE				0x00004000	// enable bus-mastering read (from memory) transfer
#define MCSR_READ_MULTIPLE				0x00008000	// enable read-multiple

#define MCSR_NVRAM_ADDRESS				0x00FF0000	// address/data port for NVRAM access

#define MCSR_ADDON_RESET				0x01000000	// activate add-on reset pin
#define MCSR_OFIFO_RESET				0x02000000	// reset (mark empty) PCI to add-on FIFO
#define MCSR_IFIFO_RESET				0x04000000	// reset (mark full) add-on to PCI FIFO
#define MCSR_MAILBOX_RESET				0x08000000	// reset mailbox flags
#define MCSR_RESET						0x0F000000	// all reset flags

#define MCSR_FIFO_LOOPBACK				0x10000000	// FIFO loopback mode

// NVRAM control commands

#define MCSR_LOAD_ADDRESS_LO			0x80000000	// load low address byte (W)
#define MCSR_LOAD_ADDRESS_HI			0xA0000000	// load high address byte (W)
#define MCSR_BEGIN_WRITE				0xC0000000	// begin write (W)
#define MCSR_BEGIN_READ					0xE0000000	// begin read (W)

#define MCSR_NVRAM_BUSY					0x80000000	// busy (R)
	
///////////////////////////////////////////////////////////////////////////////
// Masks for MBEF register (p. 3-58):

#define MBEF_INCOMING		0xFFFF0000			// bits for incoming mailbox bytes
#define MBEF_OUTGOING		0x0000FFFF			// bits for outgoing mailbox bytes

#define MBEF_IN4_3			0x80000000
#define MBEF_IN4_2			0x40000000
#define MBEF_IN4_1			0x20000000
#define MBEF_IN4_0			0x10000000
#define MBEF_IN3_3			0x08000000
#define MBEF_IN3_2			0x04000000
#define MBEF_IN3_1			0x02000000
#define MBEF_IN3_0			0x01000000
#define MBEF_IN2_3			0x00800000
#define MBEF_IN2_2			0x00400000
#define MBEF_IN2_1			0x00200000
#define MBEF_IN2_0			0x00100000
#define MBEF_IN1_3			0x00080000
#define MBEF_IN1_2			0x00040000
#define MBEF_IN1_1			0x00020000
#define MBEF_IN1_0			0x00010000

#define MBEF_OUT4_3			0x00008000
#define MBEF_OUT4_2			0x00004000
#define MBEF_OUT4_1			0x00002000
#define MBEF_OUT4_0			0x00001000
#define MBEF_OUT3_3			0x00000800
#define MBEF_OUT3_2			0x00000400
#define MBEF_OUT3_1			0x00000200
#define MBEF_OUT3_0			0x00000100
#define MBEF_OUT2_3			0x00000080
#define MBEF_OUT2_2			0x00000040
#define MBEF_OUT2_1			0x00000020
#define MBEF_OUT2_0			0x00000010
#define MBEF_OUT1_3			0x00000008
#define MBEF_OUT1_2			0x00000004
#define MBEF_OUT1_1			0x00000002
#define MBEF_OUT1_0			0x00000001
	
///////////////////////////////////////////////////////////////////////////////
// Miscellaneous constants

#define S5933_ALIGNMENT_MASK	0x00000003		// transfers must begin on 4-byte boundary
#define S5933_MAXIMUM_COUNT		0x03FFFFFF		// maximum transfer count (bytes)

///////////////////////////////////////////////////////////////////////////////
// S5933DK1 ISA card operation register addresses (p. 3-67)

// The sense of mailbox transfers is the opposite from the S5933: an S5933 "inbound" mailbox
// is an add-on "outbound" mailbox. The sense of DMA transfers is the same: an S5933 "read"
// moves data from memory to the S5933, and an add-on "read" moves data from the S5933 to
// the add-on.

#define AIMB1				((PULONG) 0x300)
#define AIMB2				((PULONG) 0x304)
#define AIMB3				((PULONG) 0x308)
#define AIMB4				((PULONG) 0x30C)
#define AOMB1				((PULONG) 0x310)
#define AOMB2				((PULONG) 0x314)
#define AOMB3				((PULONG) 0x318)
#define AOMB4				((PULONG) 0x31C)
#define AFIFO				((PULONG) 0x320)
#define AMWAR				((PULONG) 0x324)
#define APTA				((PULONG) 0x328)		// pass-through address
#define APTD				((PULONG) 0x32C)		// pass-through data
#define AMRAR				((PULONG) 0x330)
#define AMBEF				((PULONG) 0x334)
#define AINT				((PULONG) 0x338)
#define AGCSTS				((PULONG) 0x33C)
#define AMWTC				((PULONG) 0x718)
#define AMRTC				((PULONG) 0x71C)

///////////////////////////////////////////////////////////////////////////////
// Bits in INT register (p. 3-74 ff.):

// Control Flags:

#define INT_IMBI_BYTE_SELECT_MASK		0x00000003	// byte select for incoming (PCI to add-on) mailbox interrupt 
#define INT_IMBI_BYTE_SELECT_SHIFT		0
#define INT_IMBI_REG_SELECT_MASK		0x0000000C	// register select for ditto
#define INT_IMBI_REG_SELECT_SHIFT		2
#define INT_IMBI_ENABLE					0x00000010	// ditto enabled if "1"

//										0x000000E0	// reserved (always zero)
#define INT_OMBI_BYTE_SELECT_MASK		0x00000300	// byte select for outgoing (add-on to PCI) mailbox interrupt
#define INT_OMBI_BYTE_SELECT_SHIFT		8
#define INT_OMBI_REG_SELECT_MASK		0x00000C00	// register select for ditto
#define INT_OMBI_REG_SELECT_SHIFT		10
#define INT_OMBI_ENABLE					0x00001000	// ditto enabled if "1"

//										0x00002000	// reserved (always zero)
#define INT_WTCI_ENABLE					0x00004000	// interrupt on write (add-on to PCI) transfer complete
#define INT_RTCI_ENABLE					0x00008000	// interrupt on read (PCI to add-on) transfer complete

#define INT_MB1							0			// mailbox register 1
#define INT_MB2							1			// mailbox register 2
#define INT_MB3							2			// mailbox register 3
#define INT_MB4							3			// mailbox register 4

#define INT_BYTE0						0			// mailbox byte 0
#define INT_BYTE1						1			// mailbox byte 1
#define INT_BYTE2						2			// mailbox byte 2
#define INT_BYTE3						3			// mailbox byte 3

// Status flags:

#define INT_IMBI						0x00010000	// incoming mailbox interrupt (R/WC)
#define INT_OMBI						0x00020000	// outgoing mailbox interrupt (R/WC)
#define INT_WTCI						0x00040000	// write transfer complete interrupt (R/WC)
#define INT_RTCI						0x00080000	// read transfer complete interrupt (R/WC)
#define INT_BISTI						0x00100000	// interrupt due to BIST request (R/WC)
#define INT_ABORT						0x00200000	// interrupt due to master or target abort (R/WC)
//										0x00400000	// reserved (always zero)
#define INT_INTERRUPT_PENDING			0x00800000	// summary flag (R/O)

#define INT_INTERRUPT_MASK				0x003F0000	// mask for all interrupt flags

///////////////////////////////////////////////////////////////////////////////
// Bits in GCSTS register (p. 3.77 ff.):

#define GCSTS_WFIFO_FULL				0x00000001	// add-on to PCI FIFO is full
#define GCSTS_WFIFO_4PLUS				0x00000002	// at least 4 empty words in add-on to PCI FIFO
#define GCSTS_WFIFO_EMPTY				0x00000004	// add-on to PCI FIFO completely empty
#define GCSTS_RFIFO_FULL				0x00000008	// PCI to add-on FIFO is full
#define GCSTS_RFIFO_4PLUS				0x00000010	// at least 4 valid words in PCI to add-on FIFO
#define GCSTS_RFIFO_EMPTY				0x00000020	// PCI to add-on is completely empty
#define GCSTS_RTCZ						0x00000040	// read (PCI to add-on) transfer count is zero
#define GCSTS_WTCZ						0x00000080	// write (add-on to PCI) transfer count is zero

//										0x00000F00	// reserved (always zero)
#define GCSTS_BIST_CODE					0x0000F000	// results of built-in self test
#define GCSTS_NVRAM_ADDRESS				0x00FF0000	// address/data port for NVRAM access

//										0x01000000	// reserved (always zero)
#define GCSTS_OFIFO_RESET				0x02000000	// reset (mark empty) PCI to add-on FIFO
#define GCSTS_IFIFO_RESET				0x04000000	// reset (mark full) add-on to PCI FIFO
#define GCSTS_MAILBOX_RESET				0x08000000	// reset mailbox flags
#define GCSTS_RESET						0x0E000000	// all reset flags

#define GCSTS_TC_ENABLE					0x10000000	// use transfer counts for addon-initiated DMA

// NVRAM control commands

#define GCSTS_LOAD_ADDRESS_LO			0x80000000	// load low address byte (W)
#define GCSTS_LOAD_ADDRESS_HI			0xA0000000	// load high address byte (W)
#define GCSTS_BEGIN_WRITE				0xC0000000	// begin write (W)
#define GCSTS_BEGIN_READ				0xE0000000	// begin read (W)

#define GCSTS_NVRAM_BUSY				0x80000000	// busy (R)

#endif // S5933_H
