// Vport.cpp -- Implementation of the CPort class
// Copyright (C) 1996 by Walter Oney
// All rights reserved

#include "stdvxd.h"
#pragma hdrstop

#undef CURSEG
#define CURSEG() LCODE			// everything in locked code
#pragma VxD_LOCKED_DATA_SEG		// ditto data

CPort* CPort::CPortAnchor;

// The following typedef overcomes a bug in C10 that causes an error 2410
// ambiguous member name) with inline-assembler references to class members

typedef class CPort CPORT;

// Use SetNfyFlag and ClrNfyFlag to change m_NfyFlag bits atomically (since
// flags settings are also changed by the interrupt procedure)

#define SetNfyFlag(mask) { \
	_asm mov ecx, this \
	_asm or [ecx]CPORT.m_NfyFlags, mask \
	}

#define ClrNfyFlag(mask) { \
	_asm mov ecx,this \
	_asm and word ptr [ecx]CPORT.m_NfyFlags,not mask \
	}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ctor & dtor

CPort::CPort(char *name, DWORD iobase, DWORD irq, DEVNODE devnode)
	{							// CPort::CPort
	m_signature = 'TROP';
	ASSERT(strlen(name) < sizeof(m_name));
	strcpy(m_name, name);
	m_iobase = iobase;
	m_irq = irq;
	m_devnode = devnode;

	m_contend = NULL;
	m_open = FALSE;
	m_owner = NULL;
	m_hContend = NULL;

	m_EvNotify = NULL;
	m_RxNotify = NULL;
	m_TxNotify = NULL;

	m_next = CPortAnchor;
	m_prev = NULL;
	if (m_next)
		m_next->m_prev = this;
	CPortAnchor = this;
	}							// CPort::CPort

///////////////////////////////////////////////////////////////////////////////

CPort::~CPort()
	{							// CPort::~CPort
	if (m_prev)
		m_prev->m_next = m_next;
	else
		CPortAnchor = m_next;

	if (m_next)
		m_next->m_prev = m_prev;
	}							// CPort::~CPort

///////////////////////////////////////////////////////////////////////////////
// Static member function:

void CPort::DeleteAll()
	{							// CPort::DeleteAll
	while (CPortAnchor)
		delete CPortAnchor;
	}							// CPort::DeleteAll

///////////////////////////////////////////////////////////////////////////////
// Some missing VCOMM wrappers:

void VCOMM_Map_Ring0DCB_To_Win32(_DCB* r0dcb, PWIN32DCB r3dcb)
	{
	_asm mov eax, r0dcb
	_asm mov edx, r3dcb
	VxDCall(VCOMM_Map_Ring0DCB_To_Win32)
	}

void VCOMM_Map_Win32DCB_To_Ring0(PWIN32DCB r3dcb, _DCB* r0dcb)
	{
	_asm mov eax, r3dcb
	_asm mov edx, r0dcb
	VxDCall(VCOMM_Map_Win32DCB_To_Ring0)
	}

///////////////////////////////////////////////////////////////////////////////
// C-function thunks to interface between VCOMM and appropriate CPort
// member functions:

#define CPORT(hp) ((CPort *) ((DWORD) hp - FIELDOFFSET(CPort, CPort::m_pd)))

#define PF0(f) BOOL f(PortData* hp) {return CPORT(hp)->f();}
#define PF1(f, a1t) BOOL f(PortData* hp, a1t a1) {return CPORT(hp)->f(a1);}
#define PF2(f, a1t, a2t) BOOL f(PortData* hp, a1t a1, a2t a2) {return CPORT(hp)->f(a1, a2);}
#define PF3(f, a1t, a2t, a3t) BOOL f(PortData* hp, a1t a1, a2t a2, a3t a3) {return CPORT(hp)->f(a1, a2, a3);}
#define PF4(f, a1t, a2t, a3t, a4t) BOOL f(PortData* hp, a1t a1, a2t a2, a3t a3, a4t a4) {return CPORT(hp)->f(a1, a2, a3, a4);}

PF2(ClearError, _COMSTAT*, int*)
PF0(Close)
PF2(EnableNotification, PCOMMNOTIFYPROC, DWORD)
PF3(EscapeFunction, DWORD, DWORD, PVOID)
PF2(GetCommConfig, PCOMMCONFIG, PDWORD)
PF1(GetCommState, _DCB*)
PF2(GetEventMask, DWORD, PDWORD)
PF1(GetProperties, _COMMPROP*)
PF1(GetQueueStatus, _COMSTAT*)
PF1(GetError, int*)
PF1(GetModemStatus, PDWORD)
PF1(Purge, DWORD)
PF3(Read, PCHAR, DWORD, PDWORD)
PF2(SetCommConfig, PCOMMCONFIG, DWORD)
PF2(SetCommState, _DCB*, DWORD)
PF2(SetEventMask, DWORD, PDWORD)
PF1(SetModemStatusShadow, PBYTE)
PF3(SetReadCallback, DWORD, PCOMMNOTIFYPROC, DWORD)
PF4(Setup, PCHAR, DWORD, PCHAR, DWORD)
PF3(SetWriteCallback, DWORD, PCOMMNOTIFYPROC, DWORD)
PF1(TransmitChar, CHAR)
PF3(Write, PCHAR, DWORD, PDWORD)

// Port function table for use during OpenComm:

#define PF (BOOL (*)())

PortFunctions functions =
	{PF SetCommState, PF GetCommState, PF Setup, PF TransmitChar,
	PF Close, PF GetQueueStatus, PF ClearError, PF SetModemStatusShadow,
	PF GetProperties, PF EscapeFunction, PF Purge, PF SetEventMask,
	PF GetEventMask, PF Write, PF Read, PF EnableNotification,
	PF SetReadCallback, PF SetWriteCallback, PF GetModemStatus,
	PF GetCommConfig, PF SetCommConfig, PF GetError, NULL};

///////////////////////////////////////////////////////////////////////////////
// Port registration and creation logic:

// AddPort calls VCOMM to add the port to its list of ports and initializes
// the contention resolution protocol for the port.

BOOL CPort::AddPort(DWORD refdata)
	{							// CPort::AddPort
	if (!VCOMM_Add_Port(refdata, (PFN) CPort::PreOpen, m_name))
		return FALSE;
	if ((m_contend = (PCONTENTIONPROC) VCOMM_Get_Contention_Handler(m_name)))
		m_resource = VCOMM_Map_Name_To_Resource(m_name);
	return TRUE;
	}							// CPort::AddPort

///////////////////////////////////////////////////////////////////////////////
// PreOpen is a static member function that VCOMM calls to open a port.
// If successful, we return the address of the PortData structure imbedded
// in the CPort structure. VCOMM uses that address as a port handle, and
// the C-language thunks defined immediately above go backward to find the
// address of the CPort object itself.

PortData* CPort::PreOpen(char *name, HVM hVM, int* pError)
	{							// CPort::PreOpen
	CPort* port;
	ASSERT(pError);

	for (port = CPortAnchor; port; port = port->m_next)
		if (strcmp(name, port->m_name) == 0)
			{					// try to open port
			if (port->m_open)
				{				// already open
				*pError = IE_OPEN;
				return NULL;
				}				// already open
			if (port->Open(hVM, pError))
				{				// opened okay
				port->m_open = TRUE;
				return &port->m_pd;
				}				// opened okay
			port->Release();	// release if already acquired
			return NULL;		// return with whatever Open stored in pError
			}					// try to open port
	
	*pError = IE_HARDWARE;		// report lack of hardware
	ASSERT(FALSE);				// should never get here with unknown port
	return NULL;				// no such port
	}							// CPort::PreOpen

///////////////////////////////////////////////////////////////////////////////
// OnPortStolen is a static member function that contention handlers call
// when they are stealing our port.

BOOL CPort::OnPortStolen(CPort* port, BOOL owned)
	{							// OnPortStolen
	if (owned)
		port->m_pd.LossByte &= ~1;
	else
		port->m_pd.LossByte |= 1;
	return TRUE;				// okay to steal port
	}							// OnPortStolen

// The compiler isn't willing to let us use the address of OnPortStolen
// as an argument to the contention function, but we know better:

DWORD pPortStolen = (DWORD) CPort::OnPortStolen;

///////////////////////////////////////////////////////////////////////////////
// ManageTimer is a static member function that manages the timer for all
// the ports controlled by this driver

HTIMEOUT TimeOutHandle;			// timeout event handle

void TimeoutProc();				// forward dcl
void OnTimeout(DWORD extra, DWORD refdata);

void CPort::ManageTimer()
	{							// CPort::ManageTimer
	CPort* port;
	for (port = CPortAnchor; port; port = port->m_next)
		if (!(port->m_MiscFlags & MF_CLRTIMER) && port->m_RxTrigger != 0xFFFFFFFF)
			{					// need a timeout for at least one port
			if (!TimeOutHandle)
				TimeOutHandle = Set_Global_Time_Out((VMM_TIMEOUT_HANDLER) TimeoutProc, 100, 0);
			return;
			}					// need a timeout for at least one port

	// No port needs a timeout, so cancel the timeout event if one
	// is currently scheduled. For some reason, __Cancel_Time_Out isn't
	// defined here, so we can't just do a direct VMMCall.

	_asm xor esi, esi
	_asm xchg esi, TimeOutHandle // note: atomic operation

#ifdef __Cancel_Time_Out		// should be defined by VMM_Service in vmm.h!!
	#pragma message("__Cancel_Time_Out is finally #defined at line " __LINE__)
	VMMCall(Cancel_Time_Out)
#else
	HTIMEOUT temp;
	_asm mov temp, esi
	Cancel_Time_Out(temp);
#endif

	}							// CPort::ManageTimer

void __declspec(naked) TimeoutProc()
	{							// TimeoutProc
	_asm
		{
		xor	 eax, eax			; clear event variable
		xchg eax, TimeOutHandle
		test eax, eax			; was it already cancelled?
		jz   goback				; if yes, don't do anything else

		push edx				; reference data
		push ecx				; extra number of milliseconds
		call OnTimeout			; go handle timeout
		add  esp, 8				; lose args

	goback:
		ret						; return to VMM
		}
	}							// TimeoutProc

// Limitation of inline assembler syntax: no way to call a static
// member function

void OnTimeout(DWORD extra, DWORD refdata)
	{							// OnTimeout
	CPort::OnTimeout(extra, refdata);
	}							// OnTimeout

void CPort::OnTimeout(DWORD extra, DWORD refdata)
	{							// CPort::OnTimeout
	CPort* port;
	for (port = CPortAnchor; port; port = port->m_next)
		if (!(port->m_MiscFlags & MF_CLRTIMER)		    // timer enabled for port
			&& port->m_RxTrigger != 0xFFFFFFFF			// wants receive notifications
			&& port->m_pd.QInCount						// something in queue
			&& !(port->m_NfyFlags & CN_RECEIVE)) // hasn't already been sent
			{					// send notification
			BYTE notify;		// really send notification?
			
			// The idle flag is zero immediately after the mini-driver
			// reads a character. Skip the notification the first time
			// the timer goes off because the queue may fill up and we'll
			// send a notification for the usual reason that we exceed
			// its threshold
			
			_asm
				{				// check idle flag
				mov ebx, port
				xor [ebx]CPORT.m_NfyFlags, CN_IDLE ; MUST be 0x80
				setns al		; 1 if this isn't 1st timer call
				mov notify, al
				}				// check idle flag
			if (notify)
				port->CallNotifyProc(CN_RECEIVE);
			}					// send notification
	TimeOutHandle = Set_Global_Time_Out((VMM_TIMEOUT_HANDLER) TimeoutProc, 100, 0);
	}							// CPort::OnTimeout

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// Overridable base-class functions

BOOL CPort::Acquire(HVM hVM)
	{							// CPort::Acquire
	ASSERT_VALID_CPORT(this);
	ASSERT(!m_hContend && !m_owner);

	if (m_contend)
		{						// have contention procedure
		if (!m_resource)
			return FALSE;		// but no resource handle?
		m_hContend = (*m_contend)(ACQUIRE_RESOURCE, m_resource,
			pPortStolen, this, TRUE); // try to steal if owned
		if (m_hContend)
			{					// we've got it
			m_owner = hVM;
			return TRUE;
			}					// we've got it
		return FALSE;
		}						// have contention procedure
	m_owner = hVM;
	return TRUE;
	}							// CPort::Acquire

///////////////////////////////////////////////////////////////////////////////

void CPort::CallNotifyProc(int code)
	{							// CPort::CallNotifyProc
	ASSERT_VALID_CPORT(this);
	ASSERT(!(code & 0xFF00));

	// VCOMM incorrectly destroys EBX during a notification callback. Therefore,
	// use EBX for the "this" reference in the next little bit of code so
	// that we'll save and restore it

	_asm mov ebx, this
	_asm mov al, byte ptr code
	_asm or [ebx]CPORT.m_NfyFlags, al ; merge to get sent notifications flag
	DWORD events = *m_pEvent;
	
	// Call the ring-0 notification procedure appropriate to the event code.
	// Note that VCOMM maintains equivalent client pointers in the PortData
	// structure (lpClientEventNotify, etc.). We're not supposed to touch
	// those!
	
	switch (code)
		{						// select which notify proc to call

	case CN_EVENT:
		ASSERT(m_EvNotify);
		(*m_EvNotify)(&m_pd, m_EvData, code, events);
		break;

	case CN_RECEIVE:
		ASSERT(m_RxNotify);
		(*m_RxNotify)(&m_pd, m_RxData, code, events);
		break;

	case CN_TRANSMIT:
		ASSERT(m_TxNotify);
		(*m_TxNotify)(&m_pd, m_TxData, code, events);
		break;

	default:
		ASSERT(FALSE);			// unknown notification code
		}						// select which notify proc to call
	}							// CPort::CallNotifyProc

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::ClearError(_COMSTAT* pComstat, int* pError)
	{							// CPort::ClearError
	ASSERT_VALID_CPORT(this);
	if (pComstat)
		GetQueueStatus(pComstat);	// should not be able to fail
	ASSERT(pError);
	*pError = (int) m_pd.dwCommError;
	m_pd.dwCommError = 0;
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::ClearError

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::Close()
	{							// CPort::Close
	ASSERT_VALID_CPORT(this);
	m_pd.dwLastError = 0;		// assume no problems
	if (!m_open)
		return TRUE;			// isn't open in the first place

	if (!trmcom())
		return FALSE;			// mini-driver couldn't close
	Release();					// release from contention manager
	m_open = FALSE;

	if (m_MiscFlags & MF_RXQINTERNAL)
		{						// release Rx buffer
		ASSERT(m_pd.QInAddr);
		_HeapFree((PVOID) m_pd.QInAddr, 0);
		m_pd.QInAddr = NULL;
		m_MiscFlags &= ~MF_RXQINTERNAL;
		}						// release Rx buffer

	if (m_MiscFlags & MF_TXQINTERNAL)
		{						// release Tx buffer
		ASSERT(m_pd.QOutAddr);
		_HeapFree((PVOID) m_pd.QOutAddr, 0);
		m_pd.QOutAddr = NULL;
		m_MiscFlags &= ~MF_TXQINTERNAL;
		}						// release Tx buffer

	m_MiscFlags |= MF_CLRTIMER;
	ManageTimer();
	return TRUE;
	}							// CPort::Close

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::EnableNotification(PCOMMNOTIFYPROC pCallback, DWORD refdata)
	{							// CPort::EnableNotification
	ASSERT_VALID_CPORT(this);
	ClrNfyFlag(CN_NOTIFY);		// prevent any notifications during changeover
	m_EvNotify = pCallback;
	m_EvData = refdata;
	if (pCallback)
		{						// wants notifications
		ASSERT(m_pEvent);
		
		// Prevent possible race with people who discover events and
		// try to notify about them so we don't notify twice

		_asm pushfd
		_asm cli				
		m_NfyFlags |= CN_NOTIFY;
		DWORD pending = m_eventmask & *m_pEvent;
		_asm popfd
		if (pending)
			CallNotifyProc(CN_EVENT);
		}						// wants notifications
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::EnableNotification

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::EscapeFunction(DWORD lFunc, DWORD InData, PVOID pOutData)
	{							// CPort::EscapeFunction
	ASSERT_VALID_CPORT(this);
	m_pd.dwLastError = 0;

	switch (lFunc)
		{						// process escape function

	case PEEKCHAR:				// lFunc == 200
		if (!m_pd.QInCount)
			return FALSE;		// no pending input character
		ASSERT(pOutData);
		*(PBYTE) pOutData = ((char *) m_pd.QInAddr)[m_pd.QInGet];
		break;

	case ENABLETIMERLOGIC:		// lFunc == 21
		m_MiscFlags &= ~MF_CLRTIMER;
		break;

	case IGNOREERRORONREADS:	// lFunc == 20
		m_MiscFlags |= MF_IGNORECOMMERROR;
		break;

	case CLRTIMERLOGIC:			// lFunc == 16
		m_MiscFlags |= MF_CLRTIMER;
		break;

	case SETUPDATETIMEADDR:		// lFunc == 19
		m_pRxTime = (PDWORD) InData;
		break;

	default:
		if (cextfcn(lFunc, InData, pOutData))
			break;				// mini-driver handled it
		m_pd.dwLastError = (DWORD) IE_EXTINVALID;
		return FALSE;			// unknown escape
		}						// process escape function
	return TRUE;
	}							// CPort::EscapeFunction

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::GetCommConfig(PCOMMCONFIG lpCC, PDWORD lpSize)
	{							// CPort::GetCommConfig
	ASSERT_VALID_CPORT(this);
	ASSERT(lpSize);

	DWORD size = *lpSize;
	*lpSize = sizeof(COMMCONFIG);

	if (size < sizeof(COMMCONFIG) || !lpCC)
		return TRUE;			// this is how SERIAL behaves, but it seems wrong
	
	lpCC->dwProviderOffset = 0;
	lpCC->dwProviderSize = 0;
	lpCC->dwSize = sizeof(COMMCONFIG);
	lpCC->wVersion = 0x0100;
	lpCC->dwProviderSubType = GetProviderSubType();
	VCOMM_Map_Ring0DCB_To_Win32(&m_dcb, &lpCC->dcb);
	
	return TRUE;
	}							// CPort::GetCommConfig

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::GetCommState(_DCB* pDCB)
	{							// CPort::GetCommState
	ASSERT_VALID_CPORT(this);
	*pDCB = m_dcb;
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::GetCommState

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::GetEventMask(DWORD mask, PDWORD pEvents)
	{							// CPort::GetEventMask
	ASSERT_VALID_CPORT(this);
	ASSERT(pEvents);
	_asm pushfd
	_asm cli
	*pEvents = *m_pEvent;		// return all current events
	*m_pEvent &= ~mask;			// clear selected events
	_asm popfd
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::GetEventMask

///////////////////////////////////////////////////////////////////////////////
// Mini-driver should override and call base-class first, then fill
// in device specific parts of the structure

BOOL CPort::GetProperties(_COMMPROP* pCommProp)
	{							// CPort::GetProperties
	ASSERT_VALID_CPORT(this);
	memset(pCommProp, 0, sizeof(_COMMPROP));
	pCommProp->wPacketLength = sizeof(_COMMPROP);
	pCommProp->wPacketVersion = 2;
	pCommProp->dwServiceMask = SP_SERIALCOMM;
	pCommProp->dwCurrentRxQueue = m_pd.QInSize;
	pCommProp->dwCurrentTxQueue = m_pd.QOutSize;

	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::GetProperties

///////////////////////////////////////////////////////////////////////////////
// Mini-driver should override, fill in BitMask, then call base-class fcn

BOOL CPort::GetQueueStatus(_COMSTAT* pComstat)
	{							// CPort::GetQueueStatus
	ASSERT_VALID_CPORT(this);
	m_pd.dwLastError = 0;
	pComstat->cbInque = m_pd.QInCount;
	pComstat->cbOutque = m_pd.QOutCount;
	return TRUE;
	}							// CPort::GetQueueStatus

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::GetError(int* pError)
	{							// CPort::GetError
	ASSERT_VALID_CPORT(this);
	ASSERT(pError);
	*pError = m_pd.dwLastError;
	return TRUE;
	}							// CPort::GetError

///////////////////////////////////////////////////////////////////////////////
// Mini-driver should replace the base class fcn

BOOL CPort::GetModemStatus(PDWORD pModemStatus)
	{							// CPort::GetModemStatus
	ASSERT_VALID_CPORT(this);
	ASSERT(pModemStatus);
	*pModemStatus = *m_pMsrShadow & MS_Modem_Status;
	return TRUE;
	}							// CPort::GetModemStatus

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::Open(HVM hVM, int* pError)
	{							// CPort::Open
	ASSERT_VALID_CPORT(this);
	ASSERT(!m_open);
	
	memset(&m_pd, 0, sizeof(m_pd)); // do this before VCD can muck with LossByte
	memset(&m_dcb, 0, sizeof(m_dcb));

	if (!Acquire(hVM))
		{						// physical port is in use
		*pError = IE_OPEN;
		return FALSE;
		}						// physical port is in use

	m_pd.PDLength = sizeof(m_pd);
	m_pd.PDVersion = 0x010A;	// version 1.1 of PortData structure
	m_pd.PDfunctions = &functions;
	m_pd.PDNumFunctions = sizeof(functions) / sizeof(BOOL (*)());
	m_pd.dwCommError = 0;
	
	m_dcb.XonLim = 0xFFFFFFFF;
	m_dcb.XoffLim = 0xFFFFFFFF;
	m_dcb.BitMask = fBinary;
	m_dcb.XonChar = 0x11;		// Ctrl+Q
	m_dcb.XoffChar = 0x13;		// Ctrl+S

	m_pRxTime = &m_pd.dwLastReceiveTime;
	m_pEvent = &m_pd.dwDetectedEvents;
	m_eventmask = 0;
	m_pMsrShadow = &m_pd.bMSRShadow;
	m_RxTrigger = 0xFFFFFFFF;
	m_TxTrigger = 0;
	m_NfyFlags = 0;
	m_MiscFlags = 0;

	return inicom(pError);
	}							// CPort::Open

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::Purge(DWORD	qType)
	{							// CPort::Purge
	ASSERT_VALID_CPORT(this);
	switch (qType)
		{						// purge requested queue

	case 0:						// Tx queue
		{						// flush Tx queue
		DWORD count = m_pd.QOutCount;
		_asm pushfd
		_asm cli
		m_pd.QOutCount = 0;
		m_pd.QOutGet = 0;
		m_pd.QOutPut = 0;
		_asm popfd

		if (count && m_TxTrigger)
			CallNotifyProc(CN_TRANSMIT); // we're below Tx trigger now			

		Flush(qType);
		break;
		}						// flush Tx queue
	
	case 1:						// Rx queue
		_asm pushfd
		_asm cli
		m_pd.QInCount = 0;
		m_pd.QInGet = 0;
		m_pd.QInPut = 0;
		_asm popfd

		Flush(qType);
		ClrNfyFlag(CN_RECEIVE);

		break;
	
	default:
		ASSERT(FALSE);			// incorrect queue type
		break;
		}						// purge requested queue
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::Purge

///////////////////////////////////////////////////////////////////////////////
// Mini-driver should override, call base-class fcn, and then check for
// needing to X-on the transmitter, etc.

BOOL CPort::Read(PCHAR buf, DWORD cbRequest, PDWORD pRxCount)
	{							// CPort::Read
	ASSERT_VALID_CPORT(this);
	ASSERT(pRxCount);

	if (!(m_MiscFlags & MF_IGNORECOMMERROR) && m_pd.dwCommError)
		{						// pending errors, so stop
		m_pd.dwLastError = m_pd.dwCommError;
		return FALSE;
		}						// pending errors, so stop

	m_pd.dwLastError = 0;
	DWORD numread = m_pd.QInCount; // we'll copy this many bytes
	if (!numread)
		{						// quick out if queue empty
		*pRxCount = 0;
		return TRUE;			// it's success because there's no error
		}						// quick out if queue empty

	if (numread > cbRequest)
		numread = cbRequest;	// (unless that's more than caller wants)
	DWORD get = m_pd.QInGet; 
	DWORD ncopy = m_pd.QInSize - get; // # avail until end of buffer
	if (ncopy > numread)
		ncopy = numread;		// won't need 2d copy
	memcpy(buf, (PCHAR) m_pd.QInAddr + get, ncopy);
	
	if (ncopy == numread)
		get += ncopy;			// we'll advance QInGet to here
	else
		{						// wraparound to start of buffer
		buf += ncopy;
		ncopy = numread - ncopy;
		memcpy(buf, (PCHAR) m_pd.QInAddr, ncopy); // copy from start of buffer
		get = ncopy;
		}						// wraparound to start of buffer

	// Changing the QInCount and altering the notify flag mask
	// needs to be protected against simultaneous access by
	// our interrupt handler. Note that interrupt handler can only
	// increase QInCount and never touches QInGet.

	ASSERT(get <= m_pd.QInSize);
	ASSERT(m_pd.QInCount >= numread);

	m_pd.QInGet = get;

	_asm pushfd
	_asm cli
	m_pd.QInCount -= numread;
	m_NfyFlags &= ~CN_RECEIVE;	// allow notifications again
	_asm popfd

	*pRxCount = numread;
	return TRUE;
	}							// CPort::Read

///////////////////////////////////////////////////////////////////////////////

void CPort::Release()
	{							// CPort::Release
	ASSERT_VALID_CPORT(this);
	m_owner = NULL;
	if (m_hContend)
		{						// release port
		ASSERT(m_contend);
		(*m_contend)(RELEASE_RESOURCE, m_hContend, pPortStolen);
		m_hContend = NULL;
		}						// release port
	}							// CPort::Release

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetCommConfig(PCOMMCONFIG lpCC, DWORD dwSize)
	{							// CPort::SetCommConfig
	ASSERT_VALID_CPORT(this);
	if (dwSize < sizeof(COMMCONFIG))
		{						// too small
		m_pd.dwLastError = (DWORD) IE_INVALIDPARAM;
		return FALSE;
		}						// too small
	_DCB r0dcb;
	memset(&r0dcb, 0, sizeof(r0dcb)); // some fields won't get initialized!
	VCOMM_Map_Win32DCB_To_Ring0(&lpCC->dcb, &r0dcb);
	return SetCommState(&r0dcb, 0xFFFFFFFF);
	}							// CPort::SetCommConfig

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetCommState(_DCB* pDCB, DWORD ActionMask)
	{							// CPort::SetCommState
	ASSERT_VALID_CPORT(this);

	if ((m_pd.LossByte & 1) && !StealPort())
		{						// port stolen
		m_pd.dwLastError = (DWORD) IE_DEFAULT;
		return FALSE;
		}						// port stolen
	if (!CheckState(pDCB, ActionMask))
		return FALSE;			// error in mini-port specific parts
	BeginSetState();			// prepare to change state of port

	DWORD ChangedMask = 0;		// assume nothing changed yet
		
	#define ss(m) if (ActionMask & f##m) { \
		if (m_dcb.m != pDCB->m) ChangedMask |= f##m; \
		m_dcb.m = pDCB->m;}
		
	ss(BaudRate)
	ss(BitMask)
	ss(XonLim)
	ss(XoffLim)
	ss(ByteSize)
	ss(Parity)
	ss(StopBits)
	ss(XonChar)
	ss(XoffChar)
	ss(ErrorChar)
	ss(EofChar)
	ss(EvtChar1)
	ss(EvtChar2)
	ss(RlsTimeout)
	ss(CtsTimeout)
	ss(DsrTimeout)
	ss(TxDelay)

	EndSetState(ChangedMask);	// install new parameters
	m_MiscFlags |= MF_STATESETONCE;
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::SetCommState

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetEventMask(DWORD mask, PDWORD pEvents)
	{							// CPort::SetEventMask
	ASSERT_VALID_CPORT(this);
	m_eventmask = mask;
	
	// Calling with NULL event word ptr allows caller to change the mask.
	
	if (pEvents)
		m_pEvent = pEvents;
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::SetEventMask

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetModemStatusShadow(PBYTE pShadow)
	{							// CPort::SetModemStatusShadow
	ASSERT_VALID_CPORT(this);
	ASSERT(pShadow);
	m_pMsrShadow = pShadow;	
	m_pd.dwLastError = 0;
	return TRUE;
	}							// CPort::SetModemStatusShadow

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetReadCallback(DWORD RxTrigger, PCOMMNOTIFYPROC pCallback, DWORD refdata)
	{							// CPort::SetReadCallback
	ASSERT_VALID_CPORT(this);
	if (RxTrigger != 0xFFFFFFFF && RxTrigger > m_pd.QInSize)
		RxTrigger = m_pd.QInSize;	// make it sensible
	if (!pCallback)
		RxTrigger = 0xFFFFFFFF;	// reset if no callback fcn
	
	// Prevent race while changing over to new notification parameters

	_asm pushfd
	_asm cli
	m_RxNotify = pCallback;
	m_RxData = refdata;
	m_RxTrigger = RxTrigger;
	_asm popfd

	if (!m_pd.QInCount)
		*m_pRxTime = 0;
	ManageTimer();
	return TRUE;
	}							// CPort::SetReadCallback

///////////////////////////////////////////////////////////////////////////////
// This implementation of Setup mimics what SERIAL.VXD does. This works
// correctly if called zero or more times for external buffers followed
// by zero or more times for internal buffers. It leaks memory if called
// to assign an external buffer if an internal buffer has already been
// assigned.

BOOL CPort::Setup(PCHAR RxQueue, DWORD RxLength, PCHAR TxQueue, DWORD TxLength)
	{							// CPort::Setup
	ASSERT_VALID_CPORT(this);

	m_pd.dwLastError = 0;		// no error
	m_pd.QInCount = 0;
	m_pd.QInGet = 0;
	m_pd.QInPut = 0;
	m_pd.QOutCount = 0;
	m_pd.QOutGet = 0;
	m_pd.QOutPut = 0;

	if (!RxQueue)
		{						// need internal buffer
		ASSERT(RxLength);
		if (m_MiscFlags & MF_RXQINTERNAL)
			{					// reallocate existing buffer
			RxQueue = (PCHAR) _HeapReAllocate((PVOID) m_pd.QInAddr, RxLength, 0);
			if (!RxQueue)
				return FALSE;
			}					// reallocate existing buffer
		else
			{					// allocate buffer 1st time
			RxQueue = (PCHAR) _HeapAllocate(RxLength, 0);
			if (!RxQueue)
				return FALSE;	// means no change made
			m_MiscFlags |= MF_RXQINTERNAL;
			}					// allocate buffer 1st time
		}						// need internal buffer
	else
		{						// using external buffer
		ASSERT(!(m_MiscFlags & MF_RXQINTERNAL)); // SERIAL doesn't test this case (BUG?)
		}						// using external buffer
	m_pd.QInAddr = (DWORD) RxQueue;
	m_pd.QInSize = RxLength;

	if (!TxQueue)
		if (TxLength)
			{					// need internal buffer
			if (m_MiscFlags & MF_TXQINTERNAL)
				{				// reallocate existing buffer
				TxQueue = (PCHAR) _HeapReAllocate((PVOID) m_pd.QOutAddr, TxLength, 0);
				if (!TxQueue)
					return FALSE;
				}				// reallocate existing buffer
			else
				{				// allocate buffer 1st time
				TxQueue = (PCHAR) _HeapAllocate(TxLength, 0);
				if (!TxQueue)
					{			// can't allocate
					if (m_MiscFlags & MF_RXQINTERNAL)
						{		// release internal buffer
						_HeapFree((PVOID) m_pd.QInAddr, 0);
						m_MiscFlags &= ~MF_RXQINTERNAL;
						}		// release internal buffer
					return FALSE;
					}			// can't allocate
				m_MiscFlags |= MF_TXQINTERNAL;
				}				// allocate buffer 1st time
			}					// need internal buffer
		else
			{					// no Tx buffer
			ASSERT(!(m_MiscFlags & MF_TXQINTERNAL));
			}					// no Tx buffer

	m_pd.QOutAddr = (DWORD) TxQueue;
	m_pd.QOutSize = TxLength;
	if (TxQueue)
		m_MiscFlags |= MF_TXQSET;

	return TRUE;
	}							// CPort::Setup

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::SetWriteCallback(DWORD TxTrigger, PCOMMNOTIFYPROC pCallback, DWORD refdata)
	{							// CPort::SetWriteCallback
	ASSERT_VALID_CPORT(this);
	if (TxTrigger == 0xFFFFFFFF)
		TxTrigger = 0;			// allow -1 to mean "no trigger"
	if ((m_MiscFlags & MF_TXQSET) && TxTrigger > m_pd.QOutSize)
		TxTrigger = m_pd.QOutSize;
	if (!pCallback)
		TxTrigger = 0;

	// Prevent race while changing over to new notification parameters

	_asm pushfd
	_asm cli
	m_TxNotify = pCallback;
	m_TxData = refdata;
	m_TxTrigger = TxTrigger;
	if (m_pd.QOutCount < TxTrigger)
		m_NfyFlags |= CN_TRANSMIT; // no notification till we exceed trigger
	_asm popfd

	return TRUE;
	}							// CPort::SetWriteCallback

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::StealPort()
	{							// CPort::StealPort
	ASSERT_VALID_CPORT(this);
	if (!(m_pd.LossByte & 1))
		return TRUE;			// we never lost it
	ASSERT(m_contend && m_hContend);
	if ((*m_contend)(STEAL_RESOURCE, m_hContend, pPortStolen))
		{						// stole it back
		m_pd.LossByte &= ~1;
		return TRUE;
		}						// stole it back
	return FALSE;
	}							// CPort::StealPort

///////////////////////////////////////////////////////////////////////////////
// Mini-driver should completely replace base-class fcn

BOOL CPort::TransmitChar(CHAR ch)
	{							// CPort::TransmitChar
	ASSERT_VALID_CPORT(this);
	return FALSE;
	}							// CPort::TransmitChar

///////////////////////////////////////////////////////////////////////////////

BOOL CPort::Write(PCHAR buf, DWORD cbRequest, PDWORD pTxCount)
	{							// CPort::Write
	ASSERT_VALID_CPORT(this);
	ASSERT(pTxCount);
	DWORD nwritten;
	m_pd.dwLastError = 0;
	
	if (m_MiscFlags & MF_TXQSET)
		{						// using an output buffer
		nwritten = m_pd.QOutSize - m_pd.QOutCount; // maximum we can transfer
		if (nwritten > cbRequest)
			nwritten = cbRequest;	// don't send more than we've been given
		
		DWORD put = m_pd.QOutPut; // where we can start copying to
		DWORD ncopy = m_pd.QOutSize - put; // most we can copy now
		if (ncopy > nwritten)
			ncopy = nwritten;	// but not more than we've got room for
		memcpy((PCHAR) m_pd.QOutAddr + put, buf, ncopy);

		if (ncopy == nwritten)
			put += ncopy;		// only need 1 copy
		else
			{					// wraparound to start of buffer
			buf += ncopy;
			ncopy = nwritten - ncopy; // amount left to do
			memcpy((PCHAR) m_pd.QOutAddr, buf, ncopy);
			put = ncopy;
			}					// wraparound to start of buffer

		// Protect update of buffering parameters against interference
		// by our interrupt procedure

		m_pd.QOutPut = put;

		_asm pushfd
		_asm cli
		if ((m_pd.QOutCount += nwritten) >= m_TxTrigger)
			m_NfyFlags &= ~CN_TRANSMIT; // start checking trigger now
		_asm popfd
		}						// using an output buffer
	else
		{						// no output buffer setup
		
		// We're not using an output buffer, so redirect the buffering
		// parameters to the caller's buffer. This needs to be protected
		// against access by the interrupt routine until we're done.
		
		_asm pushfd
		_asm cli
		m_pd.QOutAddr = (DWORD) buf;
		m_pd.QOutSize = cbRequest;
		m_pd.QOutCount = cbRequest;
		m_pd.QOutPut = 0;
		m_pd.QOutGet = 0;
		if (cbRequest >= m_TxTrigger)
			m_NfyFlags &= ~CN_TRANSMIT; // start checking trigger now
		_asm popfd

		nwritten = cbRequest;	// pretend all of it written
		}						// no output buffer setup

	KickTx();					// try to restart output
	if (nwritten < cbRequest)
		m_pd.dwCommError |= CE_TXFULL; // buffer became full
	*pTxCount = nwritten;
	return TRUE;
	}							// CPort::Write

///////////////////////////////////////////////////////////////////////////////
// Defaults for mini-port callouts:

BOOL	CPort::cextfcn(DWORD lFunc, DWORD InData, PVOID pOutData){return FALSE;} // part of EscapeFunction
BOOL	CPort::inicom(int* pError){return TRUE;} // part of Open
BOOL	CPort::trmcom(){return TRUE;} // part of Close

void	CPort::BeginSetState(){}
void	CPort::EndSetState(DWORD ChangedMask){}
void	CPort::Flush(DWORD qType){}	// part of Purge
BOOL	CPort::CheckState(_DCB* pDCB, DWORD ActionMask){return TRUE;}
DWORD	CPort::GetProviderSubType(){return 0;} // for filling in COMMCONFIG
void	CPort::KickTx(){}
