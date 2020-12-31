// ==========================================================================
// 							Class Specification : COXSerialCommFile
// ==========================================================================

// Header file : OXSCFILE.H

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Is derived from CFile
//	NO  Two stage creation (constructor & Initialize())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	COXSerialCommFile class
//		The COXSerialCommFile class is the main class which controls the serial port.
//		It is derived from CFile and is therefor compatible with MFC serialization.
//		Next to the derived interface, COXSerialCommFile is extended with some other
//		function for controlling the handshake signals, the read and write buffers and
//		the time-out values.
//

// Remark:
//		If the following error appears the only solution is to add at the top of the 
//		initinstance the following code: (the default depth is only 8!. Maximum = 120.)
//		int QueueDepth = 32;
//		while (!::SetMessageQueue(QueueDepth))
//			QueueDepth--;		                                    
//                                                  
//		ERROR MESSAGE:
//			FATAL ERROR!
//			The Windows message queue is full!
//			Rs232 messages lost!
//			Increase the message queue depth.



// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXSCFILE_H_
#define __OXSCFILE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include "OXSCCFG.H"
#include "OXSCEXCP.H"


class OX_CLASS_DECL COXSerialCommFile : public CFile
{
// Data Members
public:

protected:
	HANDLE  m_hCommDevice;

private:

// Member Functions
public:
	COXSerialCommFile();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: Constructs the object and initialize the internal state

	virtual ~COXSerialCommFile();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: Destructs the object

	BOOL Open(const COXSerialCommConfig& config, COXSerialCommException* pException = NULL);
	// --- In: config: the configurations of the serial communication device to open
	//		   pException:
	// --- Out: none
	// --- Returns: if the opening was successful
	// --- Effect: opens the serial communication device configured in the config struct.

	virtual void Close();
	// --- In: none
	// --- Out: none
	// --- Returns: none
	// --- Effect: closes this serial comunication device

	BOOL SetTimeouts(DWORD dwRxTimeout=5000, DWORD dwTxTimeout=5000); // time in milliseconds
	// --- In: dwRxTimeout:
	//		   dwTxTimeout:
	// --- Out: none
	// --- Returns: if ot was successful or not
	// --- Effect: sets the time-out parameters for all read and write operations on this serial
	//			   communications device. 
	
	BOOL IsOpen() const;
	// --- In: none
	// --- Out: none 
	// --- Returns: if the port is already opened or not
	// --- Effect: none

	UINT Read( void* lpBuf, UINT nCount );
	// --- In: none
	// --- Out: lpBuf: reserved memory block to receive data
	//			nCount: size of the reserved buffer 
	// --- Returns: actual number of bytes received
	// --- Effect:

	void Write( const void* lpBuf, UINT nCount );
	// --- In: lpBuf: address of data block to transmit
	//		   nCount: number of bytes to transmit
	// --- Out: none
	// --- Returns: none
	// --- Effect: transmits the data to the serial port

	void PurgeRx();         
	// --- In: none 
	// --- Out: none 
	// --- Returns: none
	// --- Effect: makes the receive queue empty

	void PurgeTx();                                         
	// --- In: none 
	// --- Out: none 
	// --- Returns: none
	// --- Effect: makes the transmit queue empty

	BOOL IsRxQueueEmpty() const;                                  
	// --- In: none
	// --- Out: none
	// --- Returns: if the Receive queue is empty or not
	// --- Effect: none

	BOOL IsTxQueueEmpty() const;                                  
	// --- In: none
	// --- Out: none
	// --- Returns: if the Transmit queue is empty or not
	// --- Effect: none

	void SetDTR(BOOL bValue); 
	// --- In: bValue: new value of the DTR flag
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the handshake signal 'DTR' (data terminal ready )

	void SetRTS(BOOL bValue);
	// --- In: bValue: new value of the RTS flag
	// --- Out: none
	// --- Returns: none
	// --- Effect: Sets the handshake signal 'RDSR' (request to send)

	BOOL GetCTS() const;
	// --- In: none
	// --- Out: none
	// --- Returns: the state of the 'CTS' (clear to send) flag
	// --- Effect: none
 
	BOOL GetDSR() const;
	// --- In: none
	// --- Out: none
	// --- Returns: the state of the 'DSR' (data set ready) flag
	// --- Effect: none

	BOOL GetCD() const;
	// --- In: none
	// --- Out: none
	// --- Returns: the state of the 'CD' (carrier detect) flag
	// --- Effect: none

	BOOL GetRI() const;
	// --- In: none
	// --- Out: none
	// --- Returns: the state of the 'RI' (ring indicator) flag
	// --- Effect: none

	HANDLE GetSafeHandle() const;
	// --- In: none
	// --- Out: none 
	// --- Returns: a HANDLE to the COMM Device or NULL if no open handle exists
	// --- Effect: 
	// --- Note: You may call this function on a non-attached COMM device. It will
	//           return NULL.

	BOOL SetCommMask(const DWORD dwEventMask);
	// --- In: dwEventMask: Specifies the events to be enabled. A value of zero
	//                      disables all events. The below table summarizes the
	//                      possible values for dwEventMask, you may combine these
	//                      using the bit-wise OR operator.
	//
	//         Value        Meaning 
	//         --------------------------------------------------------------------
	//         EV_BREAK     A break was detected on input. 
	//         EV_CTS       The CTS (clear-to-send) signal changed state. 
	//         EV_DSR       The DSR (data-set-ready) signal changed state. 
	//         EV_ERR       A line-status error occurred. Line-status errors are CE_FRAME, 
	//                      CE_OVERRUN, and CE_RXPARITY. 
	//         EV_RING      A ring indicator was detected. 
	//         EV_RLSD      The RLSD (receive-line-signal-detect) signal changed state. 
	//         EV_RXCHAR    A character was received and placed in the input buffer. 
	//         EV_RXFLAG    The event character was received and placed in the input 
	//                      buffer. The event character is specified in the device's
	//                      DCB structure, which is applied to a serial port by using
	//                      the SetCommState function. 
	//         EV_TXEMPTY   The last character in the output buffer was sent. 
	//
	// --- Out: none
	// --- Returns: If the function succeeds, the return value is nonzero. Otherwise it is zero.
	// --- Effect: The SetCommMask function specifies the set of events that can be monitored 
	//             for a particular communications resource.

	BOOL GetCommMask(DWORD& dwEventMask) const;
	// --- In: dwEventMask: a reference to a DWORD value to receive the event mask
	// --- Out: dwEventMask: this value receives the event mask 
	//                       (see COXSerialCommFile::SetCommMask for more information)
	// --- Returns: If the function succeeds, the return value is nonzero. Otherwise it is zero.
	// --- Effect: none

	BOOL GetCommProperties(LPCOMMPROP lpCommProp) const;
	// --- In: lpCommProp: address of communications properties structure
	// --- Out: lpCommProp: Pointer to a COMMPROP structure in which the 
	//                      communications properties information is returned
	// --- Returns: If the function succeeds, the return value is nonzero. Otherwise it is zero.
	// --- Effect: The GetCommProperties function returns information from a device driver
	//             about the configuration settings that are supported by the driver

	UINT GetBytesToRead() const;
	// --- In: none
	// --- Out: none
	// --- Returns: Number of bytes waiting to be read from the COMM port, 0 if none.
	// --- Effect: none

	UINT GetBytesToWrite() const;
	// --- In: none
	// --- Out: none
	// --- Returns: Number of bytes waiting to be sent to the COMM port, 0 if none.
	// --- Effect: none

protected:
	COXSerialCommException::VALUE GetCommException(COMSTAT& comstat) const;

private:

};

inline BOOL COXSerialCommFile::IsOpen() const
{ 
	return GetSafeHandle() != NULL;
}

inline HANDLE COXSerialCommFile::GetSafeHandle() const
{
	return this == NULL ? NULL : m_hCommDevice;
}

#endif // __OXSCFILE_H_
