// ==========================================================================
// 						Class Implementation : COXSerialCommFile
// ==========================================================================

// Source file : oxscfile.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXSCFILE.H"
#include "OXSCCNST.H"


//private headers
#include "OXRSERCM.H"


COXSerialCommFile::COXSerialCommFile() :
m_hCommDevice(NULL)
	{
	m_bCloseOnDelete = TRUE;
	}

COXSerialCommFile::~COXSerialCommFile()
	{
    if (m_hCommDevice)
        Close();
	}

BOOL COXSerialCommFile::Open(const COXSerialCommConfig& config, 
							 COXSerialCommException* pException /* = NULL */)
	{
	if (pException)
		{
		pException->m_ext_cause = COXSerialCommException::none;
		pException->m_strFileName = config.GetCommName();
		}
	
    if (m_hCommDevice)
		Close();
	
    if (!config.IsPortAvailable())
		{
		if (pException)
			pException->m_ext_cause = COXSerialCommException::notAvailable;
		return FALSE;
		}
	
    VERIFY ( (m_hCommDevice =::CreateFile(config.GetCommName(), 
		GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL)) != 
		INVALID_HANDLE_VALUE);
	
	if (m_hCommDevice == INVALID_HANDLE_VALUE)
		{
		if (pException)
			pException->m_ext_cause = COXSerialCommException::notAvailable;
		return FALSE;
		}
	
    ::SetupComm(m_hCommDevice, config.m_nSizeReceivingQueue, 
		config.m_nSizeTransmissionQueue);
	
    DCB dcb;
    ::GetCommState(m_hCommDevice, &dcb);
    dcb.BaudRate = config.m_nBaudRate;
    dcb.ByteSize = config.m_nByteSize;
    dcb.Parity = config.m_nParity;
    dcb.StopBits = config.m_nStopBits;
    dcb.fBinary = TRUE;
    dcb.fParity = TRUE;
    dcb.fNull = FALSE;
    if (config.m_eFlowControl == COXSerialCommConfig::HARDWARE)
		{ 
		dcb.fOutxCtsFlow = TRUE;
		dcb.fOutxDsrFlow = TRUE;
		dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
		dcb.fDsrSensitivity = TRUE;
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
		}
	else
		{
		dcb.fOutxCtsFlow = FALSE;
		dcb.fOutxDsrFlow = FALSE;
		dcb.fDtrControl = DTR_CONTROL_ENABLE;
		dcb.fDsrSensitivity = FALSE;
		dcb.fRtsControl = RTS_CONTROL_ENABLE;
		}
    dcb.XonLim = 1;
    dcb.XoffLim = (WORD)(config.m_nSizeReceivingQueue / 2);
    if (config.m_eFlowControl == COXSerialCommConfig::XON_XOFF)
		{
        dcb.fOutX = TRUE;
        dcb.fInX = TRUE;
		}
	else
		{
        dcb.fOutX = FALSE;
        dcb.fInX = FALSE;
		}             
    dcb.fAbortOnError = TRUE;
	
    VERIFY ( ::SetCommState(m_hCommDevice, &dcb) != FALSE );
    COMSTAT tmp;
	
	
    GetCommException(tmp);		
	SetTimeouts(config.m_nDsrTimeout, config.m_nCtsTimeout);
	
    PurgeRx();
    PurgeTx();						   
	
    m_strFileName = config.GetCommName();
	
    return TRUE;
	}

BOOL COXSerialCommFile::SetTimeouts(DWORD dwRxTimeout/*=5000*/, DWORD dwTxTimeout/*=5000*/)
	{
    if (m_hCommDevice == NULL)
		{
        TRACE(_T("'COXSerialCommFile::SetTimeouts': NULL handle !"));
		ASSERT(FALSE);
        return FALSE;
		}
	
    COMMTIMEOUTS  commTimeOuts ;
    commTimeOuts.ReadIntervalTimeout = dwRxTimeout;
    commTimeOuts.ReadTotalTimeoutMultiplier = 1;
    commTimeOuts.ReadTotalTimeoutConstant = dwRxTimeout;
    commTimeOuts.WriteTotalTimeoutMultiplier = 1;
    commTimeOuts.WriteTotalTimeoutConstant = dwTxTimeout;
	
    SetCommTimeouts( m_hCommDevice, &commTimeOuts ) ;
	return TRUE;
	}


void COXSerialCommFile::Close()
	{
    if (m_hCommDevice)
		{
		PurgeRx();
		PurgeTx();
		CloseHandle(m_hCommDevice);
		m_hCommDevice = NULL;
		}
	}

UINT COXSerialCommFile::Read( void* lpBuf, UINT nCount )
	{
	DWORD	dwByteRead = 0;	
	
    if (m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::Read': NULL handle !"));
		ASSERT(FALSE);
        return 0;
		}
	
	if (!ReadFile(m_hCommDevice, lpBuf, nCount, &dwByteRead, NULL))
		{
		if (GetLastError() == ERROR_HANDLE_EOF)
			AfxThrowSerialCommException(COXSerialCommException::rxTimeout, m_strFileName);
		else
			{
			COMSTAT comstat;
			AfxThrowSerialCommException(GetCommException(comstat), m_strFileName);
			}
		}
/*	else
		{
		if (dwByteRead != (DWORD)nCount)
			{
			AfxThrowSerialCommException(COXSerialCommException::rxTimeout, m_strFileName);
			}
		}
*/	
	return dwByteRead;        	
	}

void COXSerialCommFile::Write( const void* lpBuf, UINT nCount )
	{
	DWORD	dwByteWritten;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::Write': NULL handle !"));
		ASSERT(FALSE);
        return;
		}
	
	WriteFile(m_hCommDevice, lpBuf, nCount, &dwByteWritten, NULL);  
	if (dwByteWritten != nCount)
		{
		COMSTAT tmp;
		AfxThrowSerialCommException(GetCommException(tmp), m_strFileName);
		}
	}

void COXSerialCommFile::PurgeRx()
	{
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::PurgeRx': NULL handle !"));
        ASSERT(FALSE);
        return;
		}
	PurgeComm(m_hCommDevice, PURGE_RXABORT | PURGE_RXCLEAR);
	}

void COXSerialCommFile::PurgeTx()
	{
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::PurgeTx': NULL handle !"));
        ASSERT(FALSE);
        return;
		}
	PurgeComm(m_hCommDevice, PURGE_TXABORT | PURGE_TXCLEAR);
	}

BOOL COXSerialCommFile::IsTxQueueEmpty() const
	{
	COMSTAT comstat;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::IsTxQueueEmpty': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
    GetCommException(comstat);
    return (comstat.cbOutQue == 0) ? TRUE : FALSE; 
	}

BOOL COXSerialCommFile::IsRxQueueEmpty() const
	{
	COMSTAT comstat;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::IsRxQueueEmpty': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
    GetCommException(comstat);
    return (comstat.cbInQue == 0) ? TRUE : FALSE; 
	}

void COXSerialCommFile::SetDTR(BOOL bValue)
	{
	int nFunction;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::SetDTR': NULL handle !"));
        ASSERT(FALSE);
        return;
		}
    nFunction = (bValue == TRUE) ? SETDTR : CLRDTR;
    ::EscapeCommFunction(m_hCommDevice, nFunction);
	}

void COXSerialCommFile::SetRTS(BOOL bValue)
	{
	int nFunction;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::SetRTS': NULL handle !"));
        ASSERT(FALSE);
        return;
		}
	nFunction = (bValue == TRUE) ? SETRTS : CLRRTS;
	::EscapeCommFunction(m_hCommDevice, nFunction);
	}

BOOL COXSerialCommFile::GetCTS() const
	{	  
	DWORD dwPortStatus;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::GetCTS': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
	GetCommModemStatus(m_hCommDevice, &dwPortStatus);
	return ( (dwPortStatus & MS_CTS_ON) ? TRUE : FALSE);
	}

BOOL COXSerialCommFile::GetDSR() const
	{
	DWORD dwPortStatus;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::GetDSR': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
	GetCommModemStatus(m_hCommDevice, &dwPortStatus);
	return ( (dwPortStatus & MS_DSR_ON) ? TRUE : FALSE);
	}

BOOL COXSerialCommFile::GetCD() const
	{
	DWORD dwPortStatus;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::GetCD': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
	GetCommModemStatus(m_hCommDevice, &dwPortStatus);
	return ( (dwPortStatus & MS_RLSD_ON) ? TRUE : FALSE);
	}

BOOL COXSerialCommFile::GetRI() const
	{
	DWORD dwPortStatus;
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::GetRI': NULL handle !"));
        ASSERT(FALSE);
        return FALSE;
		}
	GetCommModemStatus(m_hCommDevice, &dwPortStatus);
	return ( (dwPortStatus & MS_RING_ON) ? TRUE : FALSE);
	}

COXSerialCommException::VALUE COXSerialCommFile::GetCommException(COMSTAT& comstat) const
	{
	COXSerialCommException::VALUE exception = COXSerialCommException::none;
	DWORD dwError = 0;											  
	
    if ( m_hCommDevice == NULL )
		{
		TRACE(_T("'COXSerialCommFile::GetCommException': NULL handle !"));
        ASSERT(FALSE);
		return COXSerialCommException::ioError;
		}
	
	VERIFY (::ClearCommError(m_hCommDevice, &dwError, &comstat));
	if (dwError != 0)
		{
		if (dwError & CE_RXPARITY)
			exception = COXSerialCommException::parityError;
		else if (dwError & CE_OVERRUN)
			exception = COXSerialCommException::overrunError;
		else if (dwError & CE_FRAME)   
			exception = COXSerialCommException::frameError;
		else if (dwError & CE_BREAK)
			exception = COXSerialCommException::breakDetect;
		else if (dwError & CE_IOE)
			exception = COXSerialCommException::ioError;
		else if (dwError & CE_MODE)
			exception = COXSerialCommException::modeError;
		else if (dwError & CE_RXOVER)
			exception = COXSerialCommException::rxQueueOverflow;
		else if (dwError & CE_TXFULL)
			exception = COXSerialCommException::txQueueFull;
		else
			exception = COXSerialCommException::none;
		}
    return exception;
	}


BOOL COXSerialCommFile::SetCommMask(const DWORD dwEventMask)
{
	if (m_hCommDevice == NULL)
	{
		TRACE(_T("'COXSerialCommFile::SetCommMask': NULL handle !"));
        ASSERT(FALSE);
		return FALSE;
	}

	return ::SetCommMask(m_hCommDevice, dwEventMask);
}

BOOL COXSerialCommFile::GetCommMask(DWORD& dwEventMask) const
{
	if (m_hCommDevice == NULL)
	{
		TRACE(_T("'COXSerialCommFile::GetCommMask': NULL handle !"));
        ASSERT(FALSE);
		return FALSE;
	}

	return ::GetCommMask(m_hCommDevice, &dwEventMask);
}

BOOL COXSerialCommFile::GetCommProperties(LPCOMMPROP lpCommProp) const
{
	if (m_hCommDevice == NULL)
	{
		TRACE(_T("'COXSerialCommFile::GetCommProperties': NULL handle !"));
        ASSERT(FALSE);
		return FALSE;
	}

	return ::GetCommProperties(m_hCommDevice, lpCommProp);
}

UINT COXSerialCommFile::GetBytesToRead() const
{
	if (m_hCommDevice == NULL)
	{
		TRACE(_T("'COXSerialCommFile::GetBytesToRead': NULL handle !"));
        ASSERT(FALSE);
		return 0;
	}

	COXSerialCommException::VALUE exception = COXSerialCommException::none;

	COMSTAT cs;
	::ZeroMemory((void*)&cs,sizeof(cs));
	if ((exception = GetCommException(cs)) != COXSerialCommException::none)
	{
		AfxThrowSerialCommException(exception, m_strFileName);
		return 0;
	}
	
	return cs.cbInQue;
}

UINT COXSerialCommFile::GetBytesToWrite() const
{
	if (m_hCommDevice == NULL)
	{
		TRACE(_T("'COXSerialCommFile::GetBytesToWrite': NULL handle !"));
        ASSERT(FALSE);
		return 0;
	}

	COXSerialCommException::VALUE exception = COXSerialCommException::none;

	COMSTAT cs;
	::ZeroMemory((void*)&cs,sizeof(cs));
	if ((exception = GetCommException(cs)) != COXSerialCommException::none)
	{
		AfxThrowSerialCommException(exception, m_strFileName);
		return 0;
	}
	
	return cs.cbOutQue;
}
