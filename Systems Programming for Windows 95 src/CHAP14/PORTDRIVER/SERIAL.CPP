// serial.cpp -- Implementation of CSerialPort class
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#include "stdvxd.h"
#pragma hdrstop

#include "serial.h"

#undef CURSEG
#define CURSEG() LCODE
#pragma VxD_LOCKED_DATA_SEG

void inline out(DWORD port, BYTE data)
	{							// out
	_asm mov edx, port
	_asm mov al, data
	_asm out dx, al
	}							// out

#pragma warning(disable:4035)
BYTE inline in(DWORD port)
	{							// in
	_asm mov edx, port
	_asm in  al,dx
	}							// in
#pragma warning(default:4035)

// Use SetFlag and ClrFlag to change m_flags bits atomically (since
// flags settings are also changed by the interrupt procedure)

typedef CSerialPort CSERIALPORT;		// C10 bug

#define SetFlag(mask) { \
	_asm mov ecx, this \
	_asm or [ecx]CSERIALPORT.m_flags, mask \
	}

#define ClrFlag(mask) { \
	_asm mov ecx,this \
	_asm and word ptr [ecx]CSERIALPORT.m_flags,not mask \
	}

#define SetHSFlag(mask) { \
	_asm mov ecx, this \
	_asm or [ecx]CSERIALPORT.m_HSFlag, mask \
	}

#define ClrHSFlag(mask) { \
	_asm mov ecx,this \
	_asm and word ptr [ecx]CSERIALPORT.m_HSFlag,not mask \
	}

// Table relating baud-rate index manifests to divisor values

static WORD DivisorFromIndex[] =
	{1047						// CBR_100
	,384						// CBR_300
	,192						// CBR_600
	,96							// CBR_1200
	,48							// CBR_2400
	,24							// CBR_4800
	,12							// CBR_9600
	,8							// CBR_14400
	,6							// CBR_19200
	,0							// FF19 (reserved)
	,0							// FF1A (reserved)
	,3							// CBR_38400
	,0							// FF1C (reserved)
	,0							// FF1D (reserved)
	,0							// FF1E (reserved)
	,2							// CBR_56000
	};

#pragma warning(disable:4035)
DWORD NAKED VXDINLINE Get_System_Time()
{
	VMMJmp(Get_System_Time)
}
#pragma warning(default:4035)

VOID NAKED VXDINLINE Time_Slice_Sleep(DWORD ms)
{
	_asm mov eax, ms
	VMMJmp(Time_Slice_Sleep)
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ctor & dtor

CSerialPort::CSerialPort(char *name, DWORD iobase, DWORD irq, DEVNODE devnode)
	: CPort(name, iobase, irq, devnode)
	{							// CSerialPort::CSerialPort
	m_irqhandle = NULL;
	m_flags = 0;
	m_HSFlag = 0;
	m_HHSLines = 0;
	m_OutHHSLines = 0;
	m_ImmedChar = 0;
	m_QOutMod = 0;
	m_LSRShadow = 0;
	m_ErrorMask = LSR_FRAME | LSR_PARITY | LSR_OVERRUN;
	m_RxMask = 255;
	m_XOffPoint = 0xFFFFFFFF;	// default is never send Xoff
	m_MSRTimeout = 0;
	m_MSRInfinite = 255;

	// Setup FIFO according to parameters recorded in the registry

	struct
		{BYTE FifoOn;			// enable FIFO?
		BYTE TxFifoSize;		// size of Tx FIFO
		BYTE DSROn;				// force DSR on?
		BYTE RxTrigger;			// Rx trigger bits for FIFO
		} settings = {2, 16, 0, FIFO_TRIG08};
	DWORD junk = sizeof(settings);

	if (CM_Read_Registry_Value(m_devnode, NULL, "Settings,", REG_BINARY,
		&settings, &junk, CM_REGISTRY_HARDWARE) == CR_SUCCESS)
		{						// interpret registry settings
		m_RxFifoTrigger = settings.RxTrigger;
		if (settings.DSROn)
			SetFlag(fUseDSR);
		if (settings.FifoOn <= 1)
			{					// forced setting for FIFO
			SetFlag(fFIFOchkd);
			if (!settings.FifoOn)
				SetFlag(fNoFIFO); // don't use it
			}					// forced setting for FIFO
		if ((m_TxFifoTrigger = settings.TxFifoSize) <= 1)
			SetFlag(fNoTxFifo);
		}						// interpret registry settings
	else
		{						// use default settings
		m_RxFifoTrigger = FIFO_TRIG08;
		m_TxFifoTrigger = 16;
		}						// use default settings
	}							// CSerialPort::CSerialPort

CSerialPort::~CSerialPort()
	{							// CSerialPort::~CSerialPort
	ASSERT(!m_irqhandle);		// should have been unvirtualized!
	}							// CSerialPort::~CSerialPort

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inicom is the mini-driver function for opening a port

BOOL CSerialPort::inicom(int* pError)
	{							// CSerialPort::inicom
	if (in(m_iobase + IIDR) & 0x30)
		{						// port doesn't really exist
		*pError = IE_HARDWARE;
		return FALSE;
		}						// port doesn't really exist

	// Virtualize our assigned IRQ
	
	ASSERT(m_irq);
	VID vid =
		{(USHORT) m_irq,		// irq number
		VPICD_OPT_REF_DATA		// want ref data passed to HwIntProc
		| VPICD_OPT_CAN_SHARE,	// we can share this IRQ
		(DWORD) HwIntProcThunk,	// Hw_Int_Proc
		0,						// Virt_Int_Proc
		0,						// EOI_Proc
		0,						// Mask_Change_Proc
		0,						// IRET_Proc
		0,						// IRET_Time_Out
		(DWORD) this};			// Hw_Int_Ref

	m_irqhandle = VPICD_Virtualize_IRQ(&vid);
	ASSERT(m_irqhandle);
	if (!m_irqhandle)
		{						// can't virtualize our IRQ
		*pError = IE_HARDWARE;
		return FALSE;
		}						// can't virtualize our IRQ

	// Remember physical mask state for when we close the device

	m_oldmask = VPICD_Get_Complete_Status(m_irqhandle, Get_Sys_VM_Handle()) & VPICD_STAT_PHYS_MASK;

	// Determine the baud rate currently programmed into this port by
	// reading the divisor register

	BYTE lcr = in(m_iobase + LCR);
	out(m_iobase + LCR, lcr | LCR_DLAB); // set divisor latch in line ctl reg
	DWORD divisor = in(m_iobase) + (in(m_iobase+1) << 8);
	out(m_iobase + LCR, lcr);	// disable divisor latch
	if (divisor)
		m_dcb.BaudRate = 115200/divisor;
	else
		m_dcb.BaudRate = 0;

	m_dcb.ByteSize = 8;			// default to 8 data bits

	// Initialize port flags

	if (in(m_iobase + IIDR) & FIFO_E2)
		SetFlag(fFIFOpre);	// remember that FIFO was originally enabled
	ClrFlag(fEFlagsMask);		// clear initial state
	SetFlag(fFIFOForcedOff);

	// Turn on OUT2 line so adapter will interrupt when we allow it to.

	out(m_iobase + MCR, in(m_iobase + MCR) | MCR_OUT2);
	UnmaskIRQ();
	
	return TRUE;
	}							// CSerialPort::inicom

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trmcom is the mini-driver function for closing a port

BOOL CSerialPort::trmcom()
	{							// CSerialPort::trmcom
	m_MiscFlags |= MF_DISCARD;	// we're discarding data
	m_pd.dwCommError = 0;		// clear comm errors
	m_pd.QInCount = 0;			// input buffer is empty
	SendXon();					// wake up host if need be

	// Wait for the output queue to empty. SERIAL just does a tight
	// loop waiting for the queue to empty, allowing up to 250 ms
	// for each character. I think this logic could probably be
	// improved!

	if (!(m_HSFlag & HHSAlwaysDown))
		{						// wait for queue to drain
		DWORD curcount;
		BOOL timeout = FALSE;
		while (!timeout && (curcount = m_pd.QOutCount))
			{					// while queue nonempty
			DWORD starttime = Get_System_Time();
			while (m_pd.QOutCount == curcount)
				if ((DWORD) (Get_System_Time() - starttime) >= 250)
					{			// timed out
					timeout = TRUE;
					break;
					}			// timed out
			}					// while queue nonempty
		}						// wait for queue to drain

	// We want to clear the OUT2 flag to stop the port from interrupting.
	// A comment in SERUTIL.ASM (part of SERIAL.VXD) indicates that
	// some ports will then generate a spurious interrupt that can't
	// be identified because the IIDR won't be set. The workaround for
	// this problem is complex: mask the IRQ, put the port into loopback
	// mode, send a NUL to generate a receive interrupt, reset OUT2, and
	// then unmask the IRQ.

	if (!(m_pd.LossByte & 1) || StealPort())
		{						// we still own the port
		out(m_iobase + IER, IER_RDA); // only allow rcv interrupts
		IO_Delay();
		WaitXmitEmpty();
		out(m_iobase + FIFOR, (m_flags & fFIFOpre)
			? (FIFO_TRIG08 | FIFO_XRESET | FIFO_RRESET | FIFO_ENABLE) : 0);
		MaskIRQ();
		
		BYTE mcr = in(m_iobase + MCR);
		out(m_iobase + MCR, mcr | MCR_LOOP); // turn on loopback
		IO_Delay();
		out(m_iobase, 0);		// send NUL to generate an interrupt
		IO_Delay();
		WaitXmitEmpty();
		out(m_iobase + MCR, mcr & (MCR_DTR | MCR_RTS)); // preserve only DTR & RTS
		IO_Delay();
		UnmaskIRQ();			// should cause receive interrupt
		out(m_iobase + IER, 0);	// stop the chip from interrupting
		IO_Delay();
		MaskIRQ();				// now mask the IRQ for good
		}						// we still own the port

	// Decide whether to leave our IRQ masked or not. Then unvirtualize
	// it.

	if (VPICD_Get_Virtualization_Count(m_irq) > 1 || !m_oldmask)
		UnmaskIRQ();			// leave unmasked
	VPICD_Force_Default_Behavior(m_irqhandle);
	m_irqhandle = NULL;

	return TRUE;
	}							// CSerialPort::trmcom

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cextfcn is the mini-driver function for handling escape functions

BOOL CSerialPort::cextfcn(DWORD lFunc, DWORD InData, PVOID pOutData)
	{							// CSerialPort::cextfcn
	BOOL result = TRUE;			// assume we'll recognize this fcn

	switch (lFunc)
		{						// perform escape fcn

	///////////////////////////////////////////////////////////////////////////

	case Dummy:					// lFunc == 0
	case RESETDEV:				// lFunc == 7 (a printer escape)
		break;

	///////////////////////////////////////////////////////////////////////////

	case SETXOFF:				// lFunc == 1
		SetHSFlag(XOffReceived); // pretend we received an Xoff
		break;

	///////////////////////////////////////////////////////////////////////////

	case SETXON:				// lFunc == 2
		ClrHSFlag(XOffReceived); // pretend we received an Xon
		KickTx();
		break;

	///////////////////////////////////////////////////////////////////////////

	case SETRTS:				// lFunc == 3
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		out(m_iobase + MCR, in(m_iobase + MCR) | MCR_RTS);
		break;
		_asm popfd

	///////////////////////////////////////////////////////////////////////////

	case CLRRTS:				// lFunc == 4
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		out(m_iobase + MCR, in(m_iobase + MCR) & ~MCR_RTS);
		_asm popfd
		break;

	///////////////////////////////////////////////////////////////////////////

	case SETDTR:				// lFunc == 5
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		out(m_iobase + MCR, in(m_iobase + MCR) | MCR_DTR);
		_asm popfd
		break;

	///////////////////////////////////////////////////////////////////////////

	case CLRDTR:				// lFunc == 6
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		out(m_iobase + MCR, in(m_iobase + MCR) & ~MCR_DTR);
		_asm popfd
		break;

	///////////////////////////////////////////////////////////////////////////

	case GETCOMBASEIRQ:			// lFunc == 10
	case GETCOMBASEIRQ1:		// lFunc == 11 (compatibility)
		*(PDWORD) pOutData = MAKELONG(m_iobase, m_irq);
		break;

	///////////////////////////////////////////////////////////////////////////

	case SETBREAK:				// lFunc == 12
		{						// SETBREAK
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		SetHSFlag(BreakSet);
		BYTE lcr = in(m_iobase + LCR);
		IO_Delay();
		out(m_iobase + LCR, lcr | LCR_BREAK);
		_asm popfd
		break;
		}						// SETBREAK

	///////////////////////////////////////////////////////////////////////////

	case CLEARBREAK:			// lFunc == 13
		{						// CLEARBREAK
		_asm pushfd				// protect against interference by an interrupt
		_asm cli
		ClrHSFlag(BreakSet);
		BYTE lcr = in(m_iobase + LCR);
		IO_Delay();
		out(m_iobase + LCR, lcr & ~LCR_BREAK);
		_asm popfd
		break;
		}						// CLEARBREAK

	///////////////////////////////////////////////////////////////////////////
	
	default:
		result = FALSE;			// unsupported escape
		break;
		}						// perform escape fcn

	return result;
	}							// CSerialPort::cextfcn

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CheckState verifies port-specific parameters in a _DCB structure

BOOL CSerialPort::CheckState(_DCB* pDCB, DWORD ActionMask)
	{							// CSerialPort::CheckState
	if ((ActionMask & fStopBits) && pDCB->StopBits > TWOSTOPBITS)
		{						// invalid stop bits
		m_pd.dwLastError = (DWORD) IE_DEFAULT;
		return FALSE;
		}
	if ((ActionMask & fParity) && pDCB->Parity > SPACEPARITY)
		{						// invalid parity
		m_pd.dwLastError = (DWORD) IE_DEFAULT;
		return FALSE;
		}						// invalid parity
	if ((ActionMask & fByteSize) && (pDCB->ByteSize < 5 || pDCB->ByteSize > 8))
		{						// invalid byte size
		m_pd.dwLastError = (DWORD) IE_BYTESIZE;
		return FALSE;
		}						// invalid byte size
	if (ActionMask & fBaudRate)
		{						// validate baud rate
		DWORD rate = pDCB->BaudRate;
		if (rate >= CBR_110)
			{					// specifying index
			DWORD index = rate - CBR_110;
			if (index >= (DWORD) arraysize(DivisorFromIndex) || !DivisorFromIndex[index])
				{				// invalid index
				m_pd.dwLastError = (DWORD) IE_BAUDRATE;
				return FALSE;
				}				// invalid index
			}					// specifying index
		else
			{					// specifying rate
			if (rate < 2 || rate > 115200)
				{				// invalid rate
				m_pd.dwLastError = (DWORD) IE_BAUDRATE;
				return FALSE;
				}				// invalid rate
			}					// specifying rate
		}						// validate baud rate
	return TRUE;
	}							// CSerialPort::CheckState

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// BeginSetState prepares to change the state of the port.

void CSerialPort::BeginSetState()
	{							// CSerialPort::BeginSetState
	out(m_iobase + IER, 0);		// disable port interrupts
	}							// CSerialPort::BegSetState

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EndSetState completes the change of the port's state

void CSerialPort::EndSetState(DWORD ChangedMask)
	{							// CSerialPort::EndSetState

	// Develop bit masks for timeouts that are enabled or infinite

	if (ChangedMask & (fRlsTimeout | fCtsTimeout | fDsrTimeout))
		{						// one or more timeouts changed
		m_MSRTimeout = ~CheckTimeouts(0) & (MSR_DCD | MSR_CTS | MSR_DSR);
		m_MSRInfinite = CheckTimeouts(0xFFFFFFFF);
		}						// one or more timeouts changed
	
	// Set the Line Control Register
	
	if (ChangedMask & (fParity | fByteSize | fStopBits))
		{						// modem control bits changed
		static BYTE parity[] =
			{0									// NOPARITY
			,LCR_PARITY							// ODDPARITY
			,LCR_PARITY | LCR_EVEN				// EVENPARITY
			,LCR_PARITY            | LCR_SPAR	// MARKPARITY
			,LCR_PARITY | LCR_EVEN | LCR_SPAR	// SPACEPARITY
			};
		static BYTE stopbits[] = {0, 0, LCR_STOP};

		BYTE lcr = (m_dcb.ByteSize - 5)
			| parity[m_dcb.Parity]
			| stopbits[m_dcb.StopBits];
		out(m_iobase + LCR, lcr);

		m_RxMask = (BYTE) (255 >> (8 - m_dcb.ByteSize)); // preserves only relevant bits
		if (m_dcb.Parity == NOPARITY)
			{					// no parity checking
			m_dcb.BitMask &= ~fParity;
			m_ErrorMask = LSR_FRAME | LSR_OVERRUN;
			}					// no parity checking
		else
			m_ErrorMask = LSR_FRAME | LSR_PARITY | LSR_OVERRUN;
		}						// modem control bits changed
	
	// Set the baud rate
	
	if (ChangedMask & fBaudRate)
		{						// baud rate changing
		WORD divisor;
		BYTE lcr = in(m_iobase + LCR) & ~LCR_DLAB;
		out(m_iobase + LCR, lcr | LCR_DLAB); // access divisor registers
		if (m_dcb.BaudRate >= CBR_110)
			divisor = DivisorFromIndex[m_dcb.BaudRate - CBR_110];
		else
			divisor = (USHORT) (115200 / m_dcb.BaudRate);
		out(m_iobase, LOBYTE(divisor));
		IO_Delay();
		out(m_iobase + 1, HIBYTE(divisor));
		IO_Delay();
		out(m_iobase + LCR, lcr); // clear DLAB now
		}						// baud rate changing
	
	// Set hardware handshaking masks
	
	if (ChangedMask & fBitMask)
		{						// flags have changed
		BYTE mcr = MCR_OUT2;
		m_HHSLines = 0;
		m_OutHHSLines = 0;

		if (!(m_dcb.BitMask & fDTRDisable))
			{					// use DTR
			mcr |= MCR_DTR;
			if (m_dcb.BitMask & fDTRFlow)
				m_HHSLines |= MCR_DTR;
			}					// use DTR
		if (!(m_dcb.BitMask & fRTSDisable))
			{					// use RTS
			mcr |= MCR_RTS;
			if (m_dcb.BitMask & fRTSFlow)
				m_HHSLines |= MCR_RTS;
			}					// use RTS
		out(m_iobase + MCR, mcr);	// setup modem control register
		m_OutHHSLines = (LOBYTE(m_dcb.BitMask) << 1) & (MSR_DSR | MSR_CTS);
								// fOutXDSRFlow and fOutXCTSFlow
		}						// flags have changed
	
	m_XOffPoint = m_pd.QInSize - m_dcb.XoffLim;
	
	// Setup the FIFO the first time we get a chance and every time
	// the baud rate changes
	
	if (!(m_MiscFlags & MF_STATESETONCE) || (ChangedMask & fBaudRate))
		{						// setup FIFO
		out(m_iobase + FIFOR, 0);	// disable FIFO
		for (int i = 0; i < 16; ++i)
			if (in(m_iobase + LSR) & LSR_DATA)
				in(m_iobase);	// read & discard data byte
			else
				break;
		m_flags &= ~fFIFOForcedOff;
		if ((m_flags & fNoFIFO) || m_dcb.BaudRate < 4800
			|| m_dcb.BaudRate >= CBR_110 && m_dcb.BaudRate < CBR_4800)
			m_flags |= fFIFOForcedOff, m_TxFifoTrigger = 1;
		else
			{					// try to enable FIFO
			out(m_iobase + FIFOR, FIFO_ENABLE | FIFO_RRESET | FIFO_XRESET | m_RxFifoTrigger);
			if (!(m_flags & fFIFOchkd))
				{				// haven't checked FIFO yet
				IO_Delay();
				m_flags |= fFIFOchkd; // indicate it's been checked
				if ((in(m_iobase + IIDR) & (FIFO_E2 | FIFO_E1)) != (FIFO_E2 | FIFO_E1))
					{			// isn't enabled after all
					m_flags |= fNoFIFO | fFIFOForcedOff;
					out(m_iobase + FIFOR, 0); // disable the FIFO
					m_TxFifoTrigger = 1;
					}			// isn't enabled after all
				}				// haven't checked FIFO yet
			}					// try to enable FIFO
		DWORD starttime = Get_System_Time(); // delay up to 200 ms
		do	{					// wait for chip to settle
			in(m_iobase);
			Time_Slice_Sleep(100);
			}					// wait for chip to settle
		while ((DWORD) (Get_System_Time() - starttime) < 200);
		}						// setup FIFO
	
	// Record the initial modem status
	
	in(m_iobase + MSR);			// read & discard
	IO_Delay();
	*m_pMsrShadow = in(m_iobase + MSR);
	m_HSFlag = 0;

	// According to a comment in SERFUNC.ASM (part of SERIAL.VXD),
	// some modems set CTS but not DSR, which means that hardware
	// handshaking based on seeing both CTS and DSR won't work. But
	// Win 3.0 didn't check this so soon, so preserve compatibility
	// if told we're dealing with a 3.0 app.
	
	BYTE hslines = *m_pMsrShadow & m_OutHHSLines;
	if (!(m_dcb.BitMask & fWin30Compat)	&& hslines != m_OutHHSLines)
		if (m_OutHHSLines == (MSR_DSR | MSR_CTS)
			|| (m_flags & fUseDSR)
			|| hslines == MSR_CTS)
			m_HSFlag |= HHSDown | HHSAlwaysDown;
		else
			m_HHSLines &= MSR_DSR; // ignore DSR

	// Enable adapter interrupts finally. Leave Tx Holding register
	// interrupts disabled until the next call to KickTx.

	_asm pushfd
	_asm cli
	out(m_iobase + IER, IER_RDA | IER_RLS | IER_MS);
	IO_Delay();
	in(m_iobase + LSR);			// clear any line status interrupt
	in(m_iobase);				// clear any receive data interrupt
	_asm popfd
	}							// CSerialPort::EndSetState

BYTE CSerialPort::CheckTimeouts(DWORD value)
	{							// CSerialPort::CheckTimeouts
	BYTE mask = 0;
	if (m_dcb.RlsTimeout == value)
		mask |= MSR_DCD;
	if (m_dcb.CtsTimeout == value)
		mask |= MSR_CTS;
	if (m_dcb.DsrTimeout == value)
		mask |= MSR_DSR;
	return mask;
	}							// CSerialPort::CheckTimeouts

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Flush completes purging the Rx or Tx queue

void CSerialPort::Flush(DWORD qType)
	{							// CSerialPort::Flush
	if (qType)
		SendXon();				// queue is empty, so re-enable host
	}							// CSerialPort::Flush

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GetProviderSubType returns the provider subtype to return from a
// call to GetCommConfig

DWORD CSerialPort::GetProviderSubType()
	{							// CSerialPort::GetProviderSubType
	return PST_RS232;
	}							// CSerialPort::GetProviderSubType

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// KickTx attempts to restart data transmission by forcing a Tx empty
// interrupt. In SERIAL.VXD, this routine is always called with interrupts
// already disabled. We don't guarantee the state of the interrupt
// flag in this driver.

void CSerialPort::KickTx()
	{							// CSerialPort::KickTx
	_asm pushfd
	_asm cli

	if ((m_pd.LossByte & 1) && !StealPort())
		{						// port was stolen
		m_pd.QOutCount = 0;		// flush the output queue
		m_QOutMod = 0;
		m_pd.QOutPut = m_pd.QOutGet;
		}						// port was stolen
	else
		{						// enable Tx interrupts
		BYTE ier = in(m_iobase + IER);
		if (!(ier & IER_THRE))
			{					// change interrupt enable register
			out(m_iobase + IER, ier | IER_THRE);
			IO_Delay();
			out(m_iobase + IER, ier | IER_THRE); // do it twice
			}					// change interrupt enable register
		}						// enable Tx interrupts

	_asm popfd
	}							// CSerialPort::KickTx

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class GetProperties function:

BOOL CSerialPort::GetProperties(_COMMPROP* pCommProp)
	{							// CSerialPort::GetProperties
	if (!CPort::GetProperties(pCommProp))
		return FALSE;
	
	pCommProp->dwMaxBaud = BAUD_USER;
	pCommProp->dwProvSubType = PST_RS232;
	pCommProp->dwProvCapabilities = PCF_DTRDSR | PCF_RTSCTS | PCF_RLSD | PCF_PARITY_CHECK
		| PCF_XONXOFF | PCF_SETXCHAR | PCF_TOTALTIMEOUTS | PCF_INTTIMEOUTS;
	pCommProp->dwSettableParams = SP_PARITY | SP_BAUD | SP_DATABITS | SP_STOPBITS
		| SP_HANDSHAKING | SP_PARITY_CHECK | SP_RLSD;
	pCommProp->dwSettableBaud = BAUD_USER + (BAUD_128K - 1); // i.e., 75-56K + user
	pCommProp->wSettableData = DATABITS_5 | DATABITS_6 | DATABITS_7 | DATABITS_8;
	pCommProp->wSettableStopParity = STOPBITS_10 | STOPBITS_15 | STOPBITS_20
		| PARITY_NONE | PARITY_ODD | PARITY_EVEN | PARITY_MARK | PARITY_SPACE;
	return TRUE;
	}							// CSerialPort::GetProperties

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class GetQueueStatus function:

BOOL CSerialPort::GetQueueStatus(_COMSTAT* pComstat)
	{							// CSerialPort::GetQueueStatus
	
	// fRlsdHold is left zero because this driver (and SERIAL too)
	// doesn't use DCD for handshaking.

	pComstat->BitMask = (
		((*m_pMsrShadow & m_OutHHSLines) >> 4)		// fCTSHold (01), fDSRHold (02)
		| (m_HSFlag & (XOffReceived | XOffSent))	// fXOffHold (08), fXOffSent (10)
		| (m_flags & (fEOF | fTxImmed))				// fEof (20), fTxim (40)
		) & 255;

	return CPort::GetQueueStatus(pComstat);
	}							// CSerialPort::GetQueueStatus

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class GetModemStatus function:

BOOL CSerialPort::GetModemStatus(PDWORD pModemStatus)
	{							// CSerialPort::GetModemStatus
	*pModemStatus = in(m_iobase + MSR) & MS_Modem_Status;
	return TRUE;
	}							// CSerialPort::GetModemStatus

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class Read function:

BOOL CSerialPort::Read(PCHAR buf, DWORD cbRequest, PDWORD pRxCount)
	{							// CSerialPort::Read
	if (!CPort::Read(buf, cbRequest, pRxCount))
		return FALSE;
	
	// SERIAL.ASM (part of SERIAL.VXD) has logic to detect an EOF.
	// As best I can determine, this logic results in returning TRUE
	// and a byte count of zero, just as would happen if the input
	// queue had been empty but no EOF character were present. This
	// looks like a bug, because I don't see how anyone is supposed
	// to tell the difference between a no-character return that means
	// EOF and one that just means there's nothing in the queue right
	// now.

	// See if we should send an X-on to the transmitter

	if (m_pd.QInCount <= m_dcb.XonLim)
		SendXon();
	return TRUE;
	}							// CSerialPort::Read

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class TransmitChar function:

BOOL CSerialPort::TransmitChar(CHAR ch)
	{							// CSerialPort::TransmitChar
	m_ImmedChar = ch;			// save char to xmit BEFORE setting flag
	SetFlag(fTxImmed);			// remember we have a character to transmit
	KickTx();
	return TRUE;
	}							// CSerialPort::TransmitChar

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Override for base-class Write function

BOOL CSerialPort::Write(PCHAR buf, DWORD cbRequest, PDWORD pTxCount)
	{							// CSerialPort::Write
	DWORD timer = 0;			// timeout counter (# times through waiting loop)
	DWORD timeouts = 0;			// lines which have timed out
	BYTE downlines;				// MSR bits which are down
	while ((downlines = ((*m_pMsrShadow & m_MSRTimeout) ^ m_MSRTimeout)))
		{						// until all lines are up or timeout
		for (int i = 0; i < 11 && !timeouts; ++i)
			{					// retry for about 1 ms
			if ((downlines & MSR_DCD) && timer >= m_dcb.RlsTimeout)
				timeouts |= CE_RLSDTO;
			if ((downlines & MSR_DSR) && timer >= m_dcb.DsrTimeout)
				timeouts |= CE_DSRTO;
			if ((downlines & MSR_CTS) && timer >= m_dcb.CtsTimeout)
				timeouts |= CE_CTSTO;
			}					// retry for about 1 ms
		if (timeouts)
			break;
		++timer;				
		}						// until all lines are up or timeout
	if (timeouts)
		{						// one or more lines timed out
		m_pd.dwCommError |= timeouts; // update error flags
		m_pd.dwLastError = 0;	// indicate no error (?)
		*pTxCount = 0;			// nothing transferred
		return TRUE;			// not an error nevertheless
		}						// one or more lines timed out

	return CPort::Write(buf, cbRequest, pTxCount);
	}							// CSerialPort::Write
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hardware interrupt handler:

// Circumlocution to allow call to member function from inline assembler:

BOOL (CSerialPort::*pHwIntProc)() = CSerialPort::HwIntProc;

void __declspec(naked) CSerialPort::HwIntProcThunk()
	{							// CSerialPort::HwIntProcThunk
	_asm sti					; allow interrupts
	_asm mov  ecx, edx			; ECX = "this" pointer
	_asm call [pHwIntProc]
	_asm cmp  eax, 1			; STC if FALSE return value
	_asm ret
	}							// CSerialPort::HwIntProcThunk

BOOL CSerialPort::HwIntProc()
	{							// CSerialPort::HwIntProc
	if (m_pd.LossByte & 1)
		return FALSE;			// port was stolen away
	BYTE intid = in(m_iobase + IIDR); // read interrupt id
	if ((intid & IIDR_PEND))
		return FALSE;			// this port isn't interrupting

	DWORD oldevents = *m_pEvent;	// current event word

	// Loop until no more interrupts are pending. Note the peculiar
	// organization of the loop and the switch. Breaking from the
	// switch causes a check for being ready to transmit. Continuing
	// skips that but repeats the IIDR read that forms the "do" condition.
	
	do	{						// handle all pending interrupts
		switch (intid & (IIDR_MASK))
			{					// select on interrupt type

		///////////////////////////////////////////////////////////////////////

		case IID_MS:			// modem status
			{					// IID_MS
			BYTE msr = in(m_iobase + MSR);
			
			// Update modem status shadow byte
			
			*m_pMsrShadow = msr;

			// Update event word. We're depending on the following
			// bit assignments for flags in the event word:
			//	EV_CTS    00000000 00001000b
			//	EV_DSR    00000000 00010000b
			//	EV_RLSD   00000000 00100000b
			//	EV_RING   00000001 00000000b

			//	EV_CTSS   00000100 00000000b
			//	EV_DSRS   00001000 00000000b
			//	EV_RLSDS  00010000 00000000b
			//	EV_RingTe 00100000 00000000b

			static BYTE linemask[16] =
				{0
				,(EV_CTS							 )/8
				,(         EV_DSR					 )/8
				,(EV_CTS | EV_DSR					 )/8
				,(                  EV_RING			 )/8
				,(EV_CTS |          EV_RING			 )/8
				,(         EV_DSR | EV_RING			 )/8
				,(EV_CTS | EV_DSR | EV_RING			 )/8
				,(                            EV_RLSD)/8
				,(EV_CTS					| EV_RLSD)/8
				,(         EV_DSR		    | EV_RLSD)/8
				,(EV_CTS | EV_DSR		    | EV_RLSD)/8
				,(                  EV_RING | EV_RLSD)/8
				,(EV_CTS |          EV_RING | EV_RLSD)/8
				,(         EV_DSR | EV_RING | EV_RLSD)/8
				,(EV_CTS | EV_DSR | EV_RING | EV_RLSD)/8};

			static BYTE deltamask[16] =
				{0
				,(EV_CTSS                 				  )/256
				,(          EV_DSRS						  )/256
				,(EV_CTSS | EV_DSRS						  )/256
				,(                    EV_RingTe			  )/256 
				,(EV_CTSS |           EV_RingTe			  )/256
				,(          EV_DSRS | EV_RingTe			  )/256
				,(EV_CTSS | EV_DSRS | EV_RingTe			  )/256
				,(                                EV_RLSDS)/256
				,(EV_CTSS					    | EV_RLSDS)/256
				,(          EV_DSRS		        | EV_RLSDS)/256
				,(EV_CTSS | EV_DSRS		        | EV_RLSDS)/256
				,(                    EV_RingTe | EV_RLSDS)/256
				,(EV_CTSS |           EV_RingTe | EV_RLSDS)/256
				,(          EV_DSRS | EV_RingTe | EV_RLSDS)/256
				,(EV_CTSS | EV_DSRS | EV_RingTe | EV_RLSDS)/256};

			*m_pEvent |= (deltamask[msr&15] << 8) | (linemask[msr>>4] << 3);

			// If we're doing a hardware handshaking protocol, see if it
			// makes sense to restart transmitting

			if (!m_OutHHSLines)
				break;			// no hardware handshaking, so check buffer immediately
			if ((m_OutHHSLines & msr) != msr)
				{				// lines not set for Tx
				m_HSFlag |= HHSDown;
				continue;		// skip Tx check
				}				// lines not set for Tx
			m_HSFlag &= ~(HHSDown | HHSAlwaysDown); // it's okay to send now
			if (!m_pd.QOutCount)
				continue;		// no pending output data
			}					// IID_MS

		// Note sleazy fall-thru from/to neighboring switch cases!

		FakeXmitEmpty:
			_asm
				{				// enable THRE interrupts
				mov edx, this
				mov edx, [edx]CPort.m_iobase
				inc edx			; Interrupt Enable Register
				in	al, dx		; read IER
				test al, 2		; is THRE interrupt enabled?
				jnz	enabled		; if yes, don't re-enable

				or	al, 2		; re-enable it
				out	dx, al		;   ..
				jmp	delay1a
			delay1a:
				jmp	delay2a
			delay2a:
				out	dx, al		; SERIAL says 8250 bug requires 2 outs here
			enabled:
				jmp delay3a
			delay3a:
				jmp	delay4a
			delay4a:
				}				// enable THRE interrupts

			if (!(in(m_iobase + LSR) & LSR_THRE))
				continue;		// THRE isn't empty

		///////////////////////////////////////////////////////////////////////

		case IID_THRE:			// transmit holding register empty
			{					// IID_THRE

			// First see if we have some important single character to
			// send, such as a handshaking char, an Xon, or the so-called
			// "immediate" character. These characters have precedence
			// over queued output.
			
			if (!(in(m_iobase + LSR) & LSR_THRE)
				|| (m_HSFlag & (HHSDown | BreakSet)))
				{				// can't transmit now
				
				// Control comes here when, for any of a variety of
				// reasons, it's not possible to transmit right now.
				// Disable the Transmit Holding Register Empty interrupt
				// for the time being. It'll get re-enabled later when
				// we discover that we can transmit once again. If you're
				// upset by the label and a couple of GOTO's, you should
				// have seen the astonishing spaghetti code in SERIAL.ASM
				// that boils down to the logic you see here!

			cantxmit:	
				out(m_iobase + IER, in(m_iobase + IER) & ~IER_THRE);
				continue;
				}				// can't transmit now

			// Send an Xon if necessary. Note that we've just discovered
			// that the Tx register is empty and the handshaking lines (if
			// any) are set so it's physically OK to transmit.
			
			if (!(m_dcb.BitMask & (fEnqAck | fEtxAck))
				&& (m_HSFlag & HSPending))
				{				// send an Xon
				m_HSFlag &= ~(XOnPending | XOffSent);
				out(m_iobase, m_dcb.XonChar);
				continue;
				}				// send an Xon

			if (m_HSFlag & CannotXmit)
				goto cantxmit;	// i.e, we've been Xoff'ed, etc.

			if (m_flags & fTxImmed)
				{				// have immediate character
				m_flags &= ~fTxImmed;
				out(m_iobase, m_ImmedChar);
				continue;
				}				// have immediate character

			// No special characters to transmit. See if the output
			// buffer is empty. If so, flag a TxEmpty event and quit
			// after disabling the THRE interrupt
			
			if (!m_pd.QOutCount)
				{				// no pending output
				*m_pEvent |= EV_TXEMPTY;
				goto cantxmit;
				}				// no pending output

			if ((m_dcb.BitMask & (fEtxAck | fEnqAck))
				&& m_QOutMod++ == m_dcb.XonLim)
				{					// send Etx or Enq
				m_QOutMod = 0;
				m_HSFlag |= EtxSent; // EnqSent is numerically the same
				out(m_iobase, m_dcb.XoffChar);
				continue;
				}					// send Etx or Enq

			// Take 1 or more characters from the output queue. TxFifoTrigger
			// got initialized either to 1 (no FIFO) or to the size of the
			// FIFO queue.

			int nbytes = min(m_TxFifoTrigger, m_pd.QOutCount);
			m_pd.QOutCount -= nbytes;
			DWORD get = m_pd.QOutGet;
			while (nbytes--)
				{				// send burst of characters
				char ch = ((PCHAR) m_pd.QOutAddr)[get];
				out(m_iobase, ch);
				if (++get >= m_pd.QOutSize)
					get = 0;
				}				// send burst of characters
			m_pd.QOutGet = get;
			*m_pEvent |= EV_TXCHAR;
			if (m_pd.QOutCount < m_TxTrigger
				&& !(m_NfyFlags & CN_TRANSMIT))
				CallNotifyProc(CN_TRANSMIT);
			
			continue;
			}					// IID_THRE

		///////////////////////////////////////////////////////////////////////

		case IID_RDA:			// received data available
			{					// IID_RDA
			*m_pRxTime = Get_Last_Updated_System_Time();
			m_NfyFlags &= ~CN_IDLE; // not idle
			BYTE lsr;
			if ((lsr = m_LSRShadow))
				{				// merge errors from last LSR interrupt
				m_pd.dwCommError |= m_LSRShadow & m_ErrorMask;
				m_LSRShadow = 0;
				}				// merge errors from last LSR interrupt
			*m_pEvent |= EV_RXCHAR;

			// Loop reading characters until there aren't any more
			
			do	{				// read all pending characters
				char ch = in(m_iobase); // read the next character

				// If we've exhausted the buffer, or if we think we
				// already saw an EOF character, we can't read any
				// more data. Set the overrun error and keep reading
				// so as to purge the pending input.
				
				if (m_pd.QInCount >= m_pd.QInSize
					|| (m_flags & fEOF))
					{			// can't read any more
					m_pd.dwCommError |= CE_RXOVER;
					continue;
					}			// can't read any more

				// If there was just a parity error, subsitute any
				// error character we were given
				
				if ((lsr & LSR_PARITY)
					&& (m_dcb.BitMask & fPErrChar))
					ch = m_dcb.ErrorChar; // substitute error char

				else
					{			// have good character
					ch &= m_RxMask; // strip parity bits (if any)
					if (!ch && (m_dcb.BitMask & fNullStrip))
						continue;	// ignore a nul if we've been told to

					if (!(m_dcb.BitMask & fBinary)
						&& ch == m_dcb.EofChar)
						{		// we've reached EOF
						m_flags |= fEOF;
						continue;
						}		// we've reached EOF

					// Check for getting an Xon or Xoff. These are flow
					// control indicators rather than data bytes.
					
					if (m_dcb.BitMask & fOutX)
						{		// output handshaking
						if (ch == m_dcb.XoffChar)
							{	// Xoff received
							m_HSFlag |= XOffReceived; // we've received an Xoff, ENQ, or ETX
							if (!(m_dcb.BitMask & (fEnqAck | fEtxAck)))
								continue;
							if (m_pd.QInCount > m_dcb.XonLim)
								continue;
							m_HSFlag &= ~(XOffReceived | XOnPending | XOffSent);
							ForceOut(m_dcb.XonChar);
							continue;
							}	// Xoff received

						if (ch == m_dcb.XonChar)
							{	// Xon received
							m_HSFlag &= ~XOffReceived; // cancel previous Xoff
							if (m_dcb.BitMask & (fEnqAck | fEtxAck))
								m_HSFlag &= ~EnqSent;
							goto FakeXmitEmpty;
							}	// Xon received
						}		// output handshaking
					}			// have good character

				// Check for receiving a special event character
				
				if (ch == m_dcb.EvtChar1)
					*m_pEvent |= EV_RXFLAG; // we received the event char

				// Check for needing to discard input while we're
				// purging the input queue
				
				if (m_MiscFlags & MF_DISCARD)
					continue;
				
				// Finally, add the new character to the input queue
				
				((PCHAR) m_pd.QInAddr)[m_pd.QInPut] = ch;
				if (++m_pd.QInPut >= m_pd.QInSize)
					m_pd.QInPut = 0;
				++m_pd.QInCount;

				// If flow control is enabled and we've reached the point
				// where we're worried about the buffer overflowing,
				// tell the host to stop transmitting.
			
				if (m_pd.QInCount >= m_XOffPoint
					&& !(m_HSFlag & HSSent))
					{				// stop transmitter
					if (m_HHSLines)
						{			// drop hardware handshaking lines
						out(m_iobase + MCR, in(m_iobase + MCR) & ~m_HHSLines);
						m_HSFlag |= HHSDropped; // show lines have been dropped
						}			// drop hardware handshaking lines
					if (m_dcb.BitMask & fInX)
						{			// send Xoff character
						m_HSFlag |= XOffSent;
						ForceOut(m_dcb.XoffChar);
						}			// send Xoff character
					}				// stop transmitter

				if (m_pd.QInCount < m_RxTrigger)
					m_NfyFlags &= ~CN_RECEIVE; // fell below threshhold
				else if (!(m_NfyFlags & CN_RECEIVE))
					CallNotifyProc(CN_RECEIVE); // not yet notified
				}				// read all pending characters
			while (in(m_iobase + LSR) & LSR_DATA);

			break;				// to check for Tx being possible
			}					// IDD_RDA

		///////////////////////////////////////////////////////////////////////

		case IID_RLS:			// line status 
			{					// IID_RLS
			*m_pEvent |= EV_ERR;	// indicate an error
			BYTE lsr = in(m_iobase + LSR);
			if (lsr & (LSR_PARITY | LSR_FRAME | LSR_OVERRUN))
				m_LSRShadow = lsr; // save for read error detection
			if (lsr & LSR_BREAK)
				*m_pEvent |= EV_BREAK; // indicate break detected
			break;				// to check Tx possibilities
			}					// IID_RLS

			}					// select on interrupt type

		// Cases which "break" from the switch come here to see if we
		// have any pending output data. This abundantly redundant code
		// comes straight from SERIAL.VXD, where somebody obviously
		// figured out some obscure facts about how the UART recognizes
		// that you're trying to enable THRE interrupts.

		if (!m_pd.QOutCount)
			continue;			// no pending output data

		_asm
			{					// hammer on THRE interrupt flag
			mov ebx, this
			mov edx, [ebx]CPort.m_iobase
			inc edx				; interrupt enable register
			in  al, dx			; read IER
			and al, not 2		; i.e., not IER_THRE
			jmp delay1
		delay1:
			jmp	delay2
		delay2:
			out dx, al			; disable THRE interrupts
			or  al, 2			; enable them again
			jmp delay3
		delay3:
			jmp delay4
		delay4:
			out dx, al			; (twice)
			jmp	delay5
		delay5:
			jmp	delay6
		delay6:
			jmp	delay7
		delay7:
			out dx, al			; (thrice -- we really mean it!!)
			}					// hammer on THRE interrupt flag

		}						// handle all pending interrupts
	while (!((intid = in(m_iobase + IIDR)) & IIDR_PEND)); // condition of "do" loop

	VPICD_Phys_EOI(m_irqhandle);

	// Notify client of any new events

	*m_pEvent &= m_eventmask;	// clear events in which client not interested
	if ((m_NfyFlags & CN_NOTIFY) && (*m_pEvent & ~oldevents))
		CallNotifyProc(CN_EVENT);

	return TRUE;				// i.e., we've handled this interrupt
	}							// CSerialPort::HwIntProc

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CSerialPort::ForceOut(char ch)
	{							// CSerialPort::ForceOut
	WaitXmitEmpty();
	out(m_iobase, ch);
	}							// CSerialPort::ForceOut

// A comment in SERUTIL.ASM says that waiting for the THRE bit to 
// come on in the LSR isn't reliable on some comm cards, so it
// applies an overall 200 ms timeout to the loop.

void CSerialPort::WaitXmitEmpty()
	{							// CSerialPort::WaitXmitEmpty
	if (in(m_iobase + LSR) & LSR_THRE)
		return;
	DWORD starttime = Get_System_Time();
	while (!(in(m_iobase + LSR) & LSR_THRE))
		if ((DWORD) (Get_System_Time() - starttime) >= 200)
			break;
	}							// CSerialPort::WaitXmitEmpty

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CheckXon is called to send an Xon to the host as part of closing the
// port or flushing the input queue.

void CSerialPort::SendXon()
	{							// SendXon
	if ((m_dcb.BitMask & (fEnqAck | fEtxAck)))
		{						// using ENQ/ETX
		if (!(m_HSFlag & (EnqReceived | HHSDropped)))
			return;				// we never sent the Xoff
		}						// using ENQ/ETX
	else if (!(m_HSFlag & HSSent))
		return;

	_asm pushfd
	_asm cli

	if (m_HHSLines)
		{						// raise hardware handshaking lines
		out(m_iobase + MCR, in(m_iobase + MCR) | m_HHSLines);
		m_HSFlag &= ~HHSDropped;
		}						// raise hardware handshaking lines

	if ((m_dcb.BitMask & (fEnqAck | fEtxAck)) && (m_HSFlag & EnqReceived)
		|| (m_HSFlag & XOffSent))
		{						// send Xon
		m_HSFlag &= ~XOffSent;		// XOffSent == EnqReceived
		m_HSFlag |= XOnPending;
		KickTx();
		}						// send Xon

	_asm popfd
	}							// SendXon
