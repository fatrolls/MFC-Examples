// ==========================================================================
// 					Class Specification : COXCommunicator
// ==========================================================================

// Header file : OXCommunicator.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)
//	YES	Derived from CSocket

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	NO	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Desciption :         
//	This class can be used to create a client server communication
//   using WinSockets.
//	This class can be used as a client that will connect to a server
//   This is much like the base class CSocket
//		* Initialize(nTimeOut, pCancelWnd)
//		* Create()
//		* Connect(sRemoteAddress, nRemotePort)
//	When you use this class as a server that listens to multiple clients
//   a socket for each client connection will be created.
//		* Initialize(nTimeOut, pCancelWnd)
//		* Create(nServerPort)
//		* Listen()
//	Yo end a communication, just call
//		* Close()
//	To simplify the communications two archives are available,
//	 one for reading and one for writing
//		* GetInStream()
//		* GetOutStream()

// All client connections are also COXCommunicator objects
// They will be created automatically when a server gets a request 
//  from a new client.  They can be address by a handle HCLIENT_COMMUNICATOR

// All callbacks are virtual functions of this class


// Remark:
//	This type of communication will block like a socket
//  This means that during Send() and Receive() the entire thread will block
//   until the function completes
//  There are three exceptions to this rule :
//		1) A timer can be specified.  When the time out is reached
//		   the blocking operation will be cancelled
//		2) Tou can specify a cancel window.  All the messages for this
//		   window and its children will still be dispatched
//		3) WM_PAINT messages will still be dispatched

//	While a communicator is blocking, it may not start a new operation
//  Such a recursive call could occur when the cancel window would
//   initiate a new operation.  So be sure to avoid this situation


// Prerequisites (necessary conditions):

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXCOMMUNICATOR_H__
#define __OXCOMMUNICATOR_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#include <afxtempl.h>

#define HCLIENT_COMMUNICATOR long


class OX_CLASS_DECL COXCommunicator : public CSocket
{
DECLARE_DYNAMIC(COXCommunicator)

// Data members -------------------------------------------------------------
public:
	
protected:
	COXCommunicator* m_pMasterCommunicator;
	CMap<COXCommunicator*, COXCommunicator*, HCLIENT_COMMUNICATOR, HCLIENT_COMMUNICATOR> m_connections;
	CSocketFile* m_pFile;
	CArchive* m_pInStream;
	CArchive* m_pOutStream;
	HWND m_hCancelWindow;
	UINT m_nTimeOut;
	UINT m_nTimerID;
	UINT m_nStreamBufferSize;

	static HCLIENT_COMMUNICATOR m_nLastUsedHandle;
	static CMap<UINT, UINT, COXCommunicator*, COXCommunicator*> m_TimerToCommunicator;

private:
	
// Member functions ---------------------------------------------------------
public:

	COXCommunicator(UINT nStreamBufferSize = 4096, COXCommunicator* pMasterCommunicator = NULL);
	// --- In  : nStreamBufferSize : The size of the buffer used for the input and output stream
	//				If you intend to use very large objects, increase the buffer size
	//			 pMasterCommunicator : The master communicator to notify
	//								   This parameter is only used for client connections
	//								   and should always by NULL
	// --- Out : 
	// --- Returns :
	// --- Effect : Constructs the object

	HCLIENT_COMMUNICATOR GetClientHandle(COXCommunicator* pClientCommunicator);
	// --- In  : pClientCommunicator : The client communicator which handle is requested
	// --- Out : 
	// --- Returns : The handle of the specified communicator (or NULL when not found)
	// --- Effect : 

	COXCommunicator* GetClientCommunicator(HCLIENT_COMMUNICATOR hClient);
	// --- In  : hClient : The client communicator handle which object is requested
	// --- Out : 
	// --- Returns : A pointer to the specified communicator (or NULL when not found)
	// --- Effect : 

	void Initialize(UINT uTimeOut = 10000, CWnd* pCancelWnd = NULL);
	// --- In  : uTimeOut : Time out value in milli seconds
	//			 pCancelWnd : Pointer to the cancel window
	// --- Out : 
	// --- Returns : 
	// --- Effect : Initializes the communicator

	void SetCancelWindow(CWnd* pCancelWnd);
	// --- In  : pCancelWnd : Pointer to the cancel window
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets a new cancel window

	void SetTimeOut(UINT uTimeOut);
	// --- In  : uTimeOut : Time out value in milli seconds
	// --- Out : 
	// --- Returns : 
	// --- Effect : Sets a new timeout value

	BOOL IsOpen();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether a valid socket is associated with this communicator
	// --- Effect : 

	BOOL IsListening();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this communicator is listening
	// --- Effect : 

	BOOL IsBlocking();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this communicator is blocking on an operation
	// --- Effect : 

	BOOL AreAnyBlocking();
	// --- In  : 
	// --- Out : 
	// --- Returns : Whether this communicator or any client communicators
	//				 are blocking on an operation
	// --- Effect : 

	void CancelAllBlockingCalls();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Cancels the blocking call of this communicator and all the 
	//				client communicators

	DWORD GetMaxReadable();
	// --- In  : 
	// --- Out : 
	// --- Returns : Determine the maximum number of bytes that can be read with 
	//               one Receive() call.
	//			 	 This is normally the same as the total amount of data queued
	// --- Effect : 

	CArchive* GetInStream();
	// --- In  : 
	// --- Out : 
	// --- Returns : The input stream of which may be read
	// --- Effect : The communicator must be open
	//				Use IsBufferEmpty() to see whether data is still waiting

	CArchive* GetOutStream();
	// --- In  : 
	// --- Out : 
	// --- Returns : The output stream to which may be written
	// --- Effect : The communicator must be open
	
	// Notifications of a client communicator
	virtual void OnClientCreate(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator);
	// --- In  : hClient : The handle of the client communicator
	//			 pClientCommunicator : A pointer to the client communicator
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that a new client communicator has been created

	virtual void OnClientReceive(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode);
	// --- In  : hClient : The handle of the client communicator
	//			 pClientCommunicator : A pointer to the client communicator
	//			 nSize : The number of bytes that can be read in one Receive()
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that the specified client communicator has received data
	//				which can be read using the input stream of the communicator

	virtual void OnClientClose(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator, int nErrorCode);
	// --- In  : hClient : The handle of the client communicator
	//			 pClientCommunicator : A pointer to the client communicator
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that the specified client communicator has closed

	virtual void OnClientDestroy(HCLIENT_COMMUNICATOR hClient, COXCommunicator* pClientCommunicator);
	// --- In  : hClient : The handle of the client communicator
	//			 pClientCommunicator : A pointer to the client communicator
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that an existent client communicator will be destroyed

	// Notifications of this communicator
	virtual void OnServerReceive(DWORD nSize, int nErrorCode);
	// --- In  : nSize : The number of bytes that can be read in one Receive()
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that this communicator has received data
	//				which can be read using the input stream

	virtual void OnServerClose(int nErrorCode);
	// --- In  : nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies that this communicator has closed

	// The following functions have the save effect as those of the base class CSocket
	// with the additional features of a timeout value and a cancel window
	virtual BOOL Accept(CAsyncSocket& rConnectedSocket,
		SOCKADDR* lpSockAddr = NULL, int* lpSockAddrLen = NULL);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void Close();

	virtual BOOL OnMessagePending();
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Overrides the base class implementation to add additional features

#ifdef _DEBUG
	virtual void AssertValid() const;
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : AssertValid performs a validity check on this object 
	//				by checking its internal state. 
	//				In the Debug version of the library, AssertValid may assert and 
	//				thus terminate the program.
	
	virtual void Dump(CDumpContext& dc) const;
	// --- In  : dc : The diagnostic dump context for dumping, usually afxDump.
	// --- Out : 
	// --- Returns :
	// --- Effect : Dumps the contents of the object to a CDumpContext object. 
	//				It provides diagnostic services for yourself and 
	//				 other users of your class. 
	//				Note  The Dump function does not print a newline character
	//				 at the end of its output. 
#endif

	virtual ~COXCommunicator();
	// --- In  :
	// --- Out : 
	// --- Returns :
	// --- Effect : Destructor of the object

protected:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);

	void OnNotifyReceive(COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode);
	void OnNotifyClose(COXCommunicator* pClientCommunicator, int nErrorCode);
	void OnNotifyKill(COXCommunicator* pClientCommunicator, int nErrorCode);

	void CreateTimer();
	void CloseTimer();
	static UINT StartTimer(COXCommunicator* pCommunicator, UINT nTimeOut);
	static void StopTimer(UINT nTimerID);
	static void CALLBACK TimerProc(HWND  hWnd, UINT nMsg, UINT nTimerID, DWORD dwTime);

	virtual BOOL ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen);
	virtual int ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags);
	virtual int SendToHelper(const void* lpBuf, int nBufLen,
		const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags);

private:
                   
};

#endif // __OXCOMMUNICATOR_H__
// ==========================================================================
