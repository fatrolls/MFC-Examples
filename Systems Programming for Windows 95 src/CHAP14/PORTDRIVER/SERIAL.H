// serial.h -- Interface to CSerialPort class
// Copyright (C) 1995 by Walter Oney
// All rights reserved

#ifndef SERIAL_H
#define SERIAL_H

#include <vpicd.h>

#ifndef VPORT_H
	#error "Include vport.h before serial.h"
#endif

///////////////////////////////////////////////////////////////////////////////

class CSerialPort : public CPort
{
public:

enum SERIALPORTS
	{IER			= 1			// interrupt enable register
	,IIDR			= 2			// interrupt id register (input)
	,FIFOR			= 2			// FIFO control register (output)
	,LCR			= 3			// line control register
	,MCR			= 4			// modem control register
	,LSR			= 5			// line status register
	,MSR			= 6			// modem status register
	};

enum IERBITS
	{IER_MS			= 0x08		// modem status interrupt enable
	,IER_RLS		= 0x04		// line status interrupt enable
	,IER_THRE		= 0x02		// transmit holding register empty interrupt enable
	,IER_RDA		= 0x01		// receive data available interrupt enable
	};

enum IIDRBITS
	{FIFO_E2		= 0x80		// FIFO enable 2
	,FIFO_E1		= 0x40		// FIFO enable 1
	,IIDR_MASK		= 0x06		// interrupt ID mask
	,IIDR_PEND		= 0x01		// interrupt pending
	,IID_MS			= 0			// modem status interrupt
	,IID_THRE		= 2			// Tx holding register empty interrupt
	,IID_RDA		= 4			// Rx data available interrupt
	,IID_RLS		= 6			// line status interrupt
	};

enum FIFOBITS
	{FIFO_TRIG14	= 0xC0		// Rx int after 14 chars
	,FIFO_TRIG08	= 0x80		//  after 8 chars
	,FIFO_TRIG04	= 0x40		//  after 4 chars
	,FIFO_TRIG01	= 0x00		//  after 1 char
	,FIFO_XRESET	= 0x04		// Tx reset
	,FIFO_RRESET	= 0x02		// Rx reset
	,FIFO_ENABLE	= 0x01		// Enable FIFO
	};

enum LCRBITS
	{LCR_DLAB		= 0x80		// divisor latch enable
	,LCR_BREAK		= 0x40		// break
	,LCR_SPAR		= 0x20
	,LCR_EVEN		= 0x10		// even parity
	,LCR_PARITY		= 0x08		// honor parity
	,LCR_STOP		= 0x04		// stop bits
	,LCR_WORD		= 0x03		// word size - 5
	};

enum MCRBITS
	{MCR_LOOP		= 0x10		// loopback
	,MCR_OUT2		= 0x08		// OUT2 signal
	,MCR_OUT1		= 0x04		// OUT1 signal
	,MCR_RTS		= 0x02		// request to send
	,MCR_DTR		= 0x01		// data terminal ready
	};

enum LSRBITS
	{LSR_TSHE		= 0x40		// transmitter shift registry empty
	,LSR_THRE		= 0x20		// transmit holding register empty
	,LSR_BREAK		= 0x10		// break detected
	,LSR_FRAME		= 0x08		// framing error
	,LSR_PARITY		= 0x04		// parity error
	,LSR_OVERRUN	= 0x02		// overrun
	,LSR_DATA		= 0x01		// receive data available
	};

enum MSRBITS
	{MSR_DCD		= 0x80		// carrier detect
	,MSR_RI			= 0x40		// ring indicate
	,MSR_DSR		= 0x20		// data set ready
	,MSR_CTS		= 0x10		// clear to send
	,MSR_DDCD		= 0x08		// delta DCD
	,MSR_DRI		= 0x04		// delta RI
	,MSR_DDSR		= 0x02		// delta DSR
	,MSR_DCTS		= 0x01		// delta CTS
	};

// Bits in m_flags (#defined so we can use them in inline assembler):

#define fUseDSR			0x01
#define fNoFIFO			0x02	// no FIFO on serial chip
#define fFIFOchkd		0x04	// we've checked the FIFO
#define fFIFOpre		0x08	// FIFO was enabled when we started
#define fNoTxFifo		0x10	// no transmit FIFO on chip
#define fEOF			0x20	// EOF character received (same as dcb FEof flag)
#define fTxImmed		0x40	// immediate character pending (same as dcb Ftximmed flag)
#define fFIFOForcedOff	0x80	// FIFO forced off
#define fEFlagsMask		0x1F	// flags to preserve when initializing flags

// Bits in m_HSFlags (ditto)

#define XOffPending		0x01	// waiting to send Xoff
#define EnqPending		0x01	//   ENQ
#define EtxPending		0x01	//   ETX
	
#define HHSDropped		0x02	// hand shaking lines dropped
	
#define XOnPending		0x04	// waiting to send Xon
#define AckPending		0x04	//   ACK
	
#define XOffReceived	0x08	// Xoff received (must == fXOffHold)
#define EnqSent			0x08	// ENQ sent
#define EtxSent			0x08	// ETX sent
	
#define XOffSent		0x10	// XOff sent (must == fXOffSent)
#define EnqReceived		0x10	// ENQ received
#define EtxReceived		0x10	// ETX received
	
#define HHSDown			0x20	// handshaking lines are down
#define BreakSet		0x40	// output break set (must == LCR_BREAK)
#define HHSAlwaysDown	0x80	// handshaking lines always down

#define HSPending		(XOffPending | XOnPending)
#define HSReceived		(XOffReceived | HHSDown)
#define HSSent			(XOffSent | HHSDropped)
#define CannotXmit		(HSPending | HSReceived | BreakSet)

// Attributes

	HIRQ	m_irqhandle;		// virtualized IRQ handle
	DWORD	m_oldmask;			// original mask state of our IRQ
	DWORD	m_TxFifoTrigger;	// # bytes to send to chip at once
	DWORD	m_QOutMod;			// output count modulo XonLim since last ENQ
	DWORD	m_XOffPoint;		// point at which we should send Xoff

	WORD	m_flags;			// port flags

	BYTE	m_HSFlag;			// handshaking flag
	BYTE	m_HHSLines;			// DTR/RTS bits for handshaking
	BYTE	m_OutHHSLines;		// lines that must be high to output
	BYTE	m_ImmedChar;		// char to Tx immediately
	BYTE	m_RxFifoTrigger;	// Rx FIFO control bits
	BYTE	m_LSRShadow;		// LSR at last interrupt
	BYTE	m_ErrorMask;		// error bits to preserve from LSR
	BYTE	m_RxMask;			// mask to strip parity bits from received data
	BYTE	m_MSRTimeout;		// MSR lines subject to timeouts
	BYTE	m_MSRInfinite;		// MSR lines NOT subject to timeouts

// Methods

public:
	CSerialPort(char *name, DWORD iobase, DWORD irq, DEVNODE devnode);
	virtual ~CSerialPort();

	static void	HwIntProcThunk();
	BOOL		HwIntProc();
	void		MaskIRQ(){VPICD_Physically_Mask(m_irqhandle);}
	void		UnmaskIRQ(){VPICD_Physically_Unmask(m_irqhandle);}
	void		ForceOut(char ch);
	void		SendXon();
	void		WaitXmitEmpty();
	BYTE		CheckTimeouts(DWORD value);
	
	// Base-class overrides:
	
	virtual BOOL	GetProperties(_COMMPROP* pCommProp);
	virtual BOOL	GetQueueStatus(_COMSTAT* pComstat);
	virtual BOOL	GetModemStatus(PDWORD pModemStatus);
	virtual BOOL	Read(PCHAR buf, DWORD cbRequest, PDWORD pRxCount);
	virtual BOOL	TransmitChar(CHAR ch);
	virtual BOOL	Write(PCHAR buf, DWORD cbRequest, PDWORD pTxCount);

	// Callout functions:

	virtual BOOL	cextfcn(DWORD lFunc, DWORD InData, PVOID pOutData);
	virtual BOOL	inicom(int* pError);
	virtual BOOL	trmcom();
	virtual void	BeginSetState();
	virtual BOOL	CheckState(_DCB* pDCB, DWORD ActionMask);
	virtual void	EndSetState(DWORD ChangedMask);
	virtual void	Flush(DWORD qType);
	virtual DWORD	GetProviderSubType();
	virtual void	KickTx();
};


#endif // SERIAL_H
