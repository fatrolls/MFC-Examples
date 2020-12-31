// CRS.H -- DDK accessing macros for client registers
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#ifndef CRS_H
#define CRS_H

#define _ClientAL pRegs->CBRS.Client_AL
#define _ClientBL pRegs->CBRS.Client_BL
#define _ClientCL pRegs->CBRS.Client_CL
#define _ClientDL pRegs->CBRS.Client_DL
#define _ClientAH pRegs->CBRS.Client_AH
#define _ClientBH pRegs->CBRS.Client_BH
#define _ClientCH pRegs->CBRS.Client_CH
#define _ClientDH pRegs->CBRS.Client_DH

#define _ClientAX pRegs->CWRS.Client_AX
#define _ClientBX pRegs->CWRS.Client_BX
#define _ClientCX pRegs->CWRS.Client_CX
#define _ClientDX pRegs->CWRS.Client_DX
#define _ClientSI pRegs->CWRS.Client_SI
#define _ClientDI pRegs->CWRS.Client_DI
#define _ClientBP pRegs->CWRS.Client_BP
#define _ClientSP pRegs->CWRS.Client_SP
#define _ClientIP pRegs->CWRS.Client_IP
#define _ClientFlags pRegs->CWRS.Client_Flags
#define _ClientAltIP pRegs->CWRS.Client_Alt_IP
#define _ClientAltSP pRegs->CWRS.Client_Alt_SP

#define _ClientEAX pRegs->CRS.Client_EAX
#define _ClientEBX pRegs->CRS.Client_EBX
#define _ClientECX pRegs->CRS.Client_ECX
#define _ClientEDX pRegs->CRS.Client_EDX
#define _ClientESI pRegs->CRS.Client_ESI
#define _ClientEDI pRegs->CRS.Client_EDI
#define _ClientEBP pRegs->CRS.Client_EBP
#define _ClientESP pRegs->CRS.Client_ESP
#define _ClientEIP pRegs->CRS.Client_EIP
#define _ClientEFlags pRegs->CRS.Client_EFlags
#define _ClientCS pRegs->CRS.Client_CS
#define _ClientDS pRegs->CRS.Client_DS
#define _ClientES pRegs->CRS.Client_ES
#define _ClientFS pRegs->CRS.Client_FS
#define _ClientGS pRegs->CRS.Client_GS
#define _ClientSS pRegs->CRS.Client_SS
#define _ClientAltESP pRegs->CRS.Client_Alt_ESP
#define _ClientAltEIP pRegs->CRS.Client_Alt_EIP
#define _ClientAltEFlags pRegs->CRS.Client_Alt_EFlags
#define _ClientAltCS pRegs->CRS.Client_Alt_CS
#define _ClientAltDS pRegs->CRS.Client_Alt_DS
#define _ClientAltES pRegs->CRS.Client_Alt_ES
#define _ClientAltFS pRegs->CRS.Client_Alt_FS
#define _ClientAltGS pRegs->CRS.Client_Alt_GS
#define _ClientAltSS pRegs->CRS.Client_Alt_SS

#ifndef FIELDOFFSET
	#define FIELDOFFSET(type, field)    ((DWORD)(&((type *)0)->field))
#endif

#define Client_Ptr_Flat(seg, off) Map_Flat(\
    FIELDOFFSET(struct Client_Reg_Struc, Client_##seg), \
	FIELDOFFSET(struct Client_Word_Reg_Struc, Client_##off))
#pragma warning(disable:4035)
VXDINLINE DWORD Map_Flat(BYTE segment, BYTE off)
{
	_asm mov ah, segment
	_asm mov al, off
	VMMCall(Map_Flat)
}
#pragma warning(default:4035)

#endif
