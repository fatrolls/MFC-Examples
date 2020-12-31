/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File RawSocketServerWorker.h
// class CWizRawSocketListener
//
// 16/07/1996 17:53                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizRawSocketServerWorker_H
#define __CWizRawSocketServerWorker_H

#include "ThreadDispatcher.h"
#include "RawSocket.h"

/////////////////////////////////////////////////////////////////////////////
// class CWizRawSocketServerWorker
class CWizRawSocketListener : public CWizMultiThreadedWorker
{
public:
	// Exceptions hierarchy
	struct Xeption {}; // common
	struct XCannotCreate : public Xeption {};  // createsocket fail
	struct XCannotSetHook : public Xeption {}; // WSASetBlockingHook fail
	struct XCannotSetHookEvent : public Xeption {}; // SetEven fail
	struct XCannotListen : public Xeption {};		// Listen fail
// Constructors:
	CWizRawSocketListener (int nPort); // Constructor do almost nothing
// Destructor:
	virtual ~CWizRawSocketListener ();
public:
// Operations:
// Virtual operations:
	// Interface for CWizThreadDispatcher
	virtual void Prepare();
	virtual BOOL WaitForData (HANDLE hShutDownEvent);
	virtual BOOL TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent);
	virtual void CleanUp();
	// Pure virtual function - do something
	// with the socket connected to the client.
	// Should return TRUE if needs to continue I/O.
	virtual BOOL ReadWrite   (CWizReadWriteSocket& socket) = 0;
protected:

// Implementation:
// Virtual implementation:
protected:
// Data Members:
	CWizSyncSocket*				m_pListenSocket;
	int							m_nPort;
	SOCKET						m_hAcceptedSocket;
};

/////////////////////////////////////////////////////////////////////////////
#endif // __CWizRawSocketServerWorker_H


