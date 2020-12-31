// Vport.h -- Interface to CPort class
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#ifndef VPORT_H
#define VPORT_H

typedef void (*PCOMMNOTIFYPROC)(PortData* hPort, DWORD refdata, DWORD lEvent, DWORD lSubEvent);
typedef DWORD (*PCONTENTIONPROC)(int, ...);

#define NAKED __declspec(naked)

///////////////////////////////////////////////////////////////////////////////
// Extracts from VCOMMW32.INC:

typedef struct tagWIN32DCB
	{								// Win32 DCB
	DWORD	DCBLength;				// 00
	DWORD	BaudRate;				// 04
	DWORD	BitMask;				// 08
	WORD	Reserved;				// 0C
	WORD	XonLim;					// 0E
	WORD	XoffLim;				// 10
	BYTE	ByteSize;				// 12
	BYTE	Parity;					// 13
	BYTE	StopBits;				// 14
	BYTE	XonChar;				// 15
	BYTE	XoffChar;				// 16
	BYTE	ErrorChar;				// 17
	BYTE	EofChar;				// 18
	BYTE	EvtChar;				// 19
	WORD	PackWORD;				// 1A
	} WIN32DCB, *PWIN32DCB;			// [1C]

typedef struct tagCOMMCONFIG
	{
	DWORD	dwSize;					// 00
	WORD	wVersion;				// 04
	WORD	wAlignDCB;				// 06
	WIN32DCB dcb;					// 08-24
	DWORD	dwProviderSubType;		// 24
	DWORD	dwProviderOffset;		// 28
	DWORD	dwProviderSize;			// 2C
	} COMMCONFIG, *PCOMMCONFIG;		// [30]

///////////////////////////////////////////////////////////////////////////////
// Base class for serial ports

class CPort
{
public:
	static CPort*	CPortAnchor;	// anchor of CPort structures

// Non-standard flags in m_NfyFlags (#define so we can use inline
// assembler with them):

#define CN_IDLE			0x80		// host has gone idle
#define CN_NOTIFY		0x40		// notifications enabled

// Flags in m_MiscFlags:

enum MISCFLAGS
	{MF_TXQSET			= 0x0001	// transmit queue has been setup
	,MF_RXQINTERNAL		= 0x0002	// we allocated Rx queue
	,MF_TXQINTERNAL		= 0x0004	// we allocated Tx queue
	,MF_CLRTIMER		= 0x0008	// timer logic disabled
	,MF_IGNORECOMMERROR	= 0x0010	// ignore read errors
	,MF_DISCARD 		= 0x0020	// discard input characters
	,MF_STATESETONCE	= 0x0040	// SetCommState done once
	};

// Attributes

public:
	CPort*			m_next;			// chain to next port
	CPort*			m_prev;			// chain to previous port

	PortData		m_pd;			// VCOMM PortData structure
	_DCB			m_dcb;			// ring-0 device control block
	DWORD			m_signature;	// signature "PORT"
	char			m_name[8];		// name of port (COMx)
	DWORD			m_iobase;		// base I/O address
	DWORD			m_irq;			// IRQ number
	DEVNODE			m_devnode;		// our device node
	PCONTENTIONPROC	m_contend;		// contention handling function
	DWORD			m_resource;		// resource handle for contention handler
	DWORD			m_hContend;		// contention handle returned by ACQUIRE_RESOURCE call
	BOOL			m_open;			// true when port is open
	HVM				m_owner;		// handle of VM that owns port
	PDWORD			m_pRxTime;		// address of place to store last Rx time
	PDWORD			m_pEvent;		// address of event word
	DWORD			m_eventmask;	// mask for events to notify about
	PBYTE			m_pMsrShadow;	// address of MSR shadow byte
	DWORD			m_TxTrigger;	// transmit trigger
	DWORD			m_RxTrigger;	// receive trigger

	DWORD			m_EvData;		// reference data for EvNotify proc
	DWORD			m_RxData;		// reference data for RxNotify proc
	DWORD			m_TxData;		// reference data for TxNotify proc
	PCOMMNOTIFYPROC	m_EvNotify;		// ring-zero notification procedure
	PCOMMNOTIFYPROC	m_RxNotify;		// ring-zero read notification procedure
	PCOMMNOTIFYPROC	m_TxNotify;		// ring-zero write notification procedure

	WORD			m_MiscFlags;	// miscellaneous flags

	BYTE			m_NfyFlags;		// flags for notifications

// Methods

public:
	CPort(char *name, DWORD iobase, DWORD irq, DWORD devnode);
	virtual ~CPort();

	static void DeleteAll();
	static PortData* PreOpen(char *name, HVM hVM, int* pError);
	static BOOL OnPortStolen(CPort* port, BOOL stolen);
	static void ManageTimer();
	static void OnTimeout(DWORD extra, DWORD refdata);
	
	BOOL			AddPort(DWORD refdata);

// Overridable functions:

	virtual BOOL	Acquire(HVM hVM);
	virtual void	CallNotifyProc(int code);
	virtual BOOL	ClearError(_COMSTAT* pComstat, int* pError);
	virtual BOOL	Close();
	virtual BOOL	EnableNotification(PCOMMNOTIFYPROC pCallback, DWORD refdata);
	virtual BOOL	EscapeFunction(DWORD lFunc, DWORD InData, PVOID pOutData);
	virtual BOOL	GetCommConfig(PCOMMCONFIG lpCC, PDWORD lpSize);
	virtual BOOL	GetCommState(_DCB* pDCB);
	virtual BOOL	GetEventMask(DWORD mask, PDWORD pEvents);
	virtual BOOL	GetProperties(_COMMPROP* pCommProp);
	virtual BOOL	GetQueueStatus(_COMSTAT* pComstat);
	virtual BOOL	GetError(int* pError);
	virtual BOOL	GetModemStatus(PDWORD pModemStatus);
	virtual BOOL	Open(HVM hVM, int* pError);
	virtual BOOL	Purge(DWORD qType);
	virtual BOOL	Read(PCHAR buf, DWORD cbRequest, PDWORD pRxCount);
	virtual void	Release();
	virtual BOOL	SetCommConfig(PCOMMCONFIG lpCC, DWORD dwSize);
	virtual BOOL	SetCommState(_DCB* pDCB, DWORD ActionMask);
	virtual BOOL	SetEventMask(DWORD mask, PDWORD pEvents);
	virtual BOOL	SetModemStatusShadow(PBYTE pShadow);
	virtual BOOL	SetReadCallback(DWORD RxTrigger, PCOMMNOTIFYPROC pCallback, DWORD refdata);
	virtual BOOL	Setup(PCHAR RxQueue, DWORD cbRxQueue, PCHAR TxQueue, DWORD cbTxQueue);
	virtual BOOL	SetWriteCallback(DWORD TxTrigger, PCOMMNOTIFYPROC pCallback, DWORD refdata);
	virtual BOOL	StealPort();
	virtual BOOL	TransmitChar(CHAR ch);
	virtual BOOL	Write(PCHAR buf, DWORD cbRequest, PDWORD pTxCount);

// Mini-driver callouts:

	virtual BOOL	cextfcn(DWORD lFunc, DWORD InData, PVOID pOutData); // part of EscapeFunction
	virtual	BOOL	inicom(int* pError); // part of Open
	virtual BOOL	trmcom(); // part of Close

	virtual void	BeginSetState();
	virtual void	EndSetState(DWORD ChangedMask);
	virtual void	Flush(DWORD qType);	// part of Purge
	virtual BOOL	CheckState(_DCB* pDCB, DWORD ActionMask);
	virtual	DWORD	GetProviderSubType(); // for filling in COMMCONFIG
	virtual void	KickTx();
};

#define ASSERT_VALID_CPORT(p) ASSERT(((CPort *) p)->m_signature == 'TROP')

#endif // VPORT_H
