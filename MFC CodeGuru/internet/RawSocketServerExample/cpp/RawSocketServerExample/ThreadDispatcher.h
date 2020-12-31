/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Header File ThreadDispatcher.h
// class CWizThreadDispatcher
//
// 15/07/1996 11:54                             Author: Poul
///////////////////////////////////////////////////////////////////

#ifndef __CWizThreadDispatcher_H
#define __CWizThreadDispatcher_H

/////////////////////////////////////////////////////////////////////////////
// Class Interface for CWizThreadDispatcher.
// The derived class must implement:
// 1. WaitForData.
//	The function received handle to event which becomes signaled
// when the server shuts down.
// The function must return FALSE if received shut down signal,
// or wait until some data becomes availible (or whatever) and
// return TRUE;
// 2. TreatData
//	The function received handle to event which becomes signaled
// when the server shuts down, and the handle to event when it
// started to treat data (or whatever), i.e. when it's safe to
// call WaitForData again.
// IMPORTANT!!! You MUST Set hDataTakenEvent somewhere in the
// function, or deadlock will occur!!! DUMNED!!!
// The function must return FALSE if received shut down signal,
// or wait until data treatmen finished (or whatever) and
// return TRUE;
class CWizMultiThreadedWorker
{
	public:
		CWizMultiThreadedWorker() {}
		virtual ~CWizMultiThreadedWorker() {}

		virtual void Prepare     () = 0;
		virtual BOOL WaitForData (HANDLE hShutDownEvent) = 0;
		virtual BOOL TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent) = 0;
		virtual void CleanUp     () =  0;

	class Stack
		{
		public:
			Stack(CWizMultiThreadedWorker& rW)
				: m_rW(rW)
				{ m_rW.Prepare(); }
			~Stack()
				{ m_rW.CleanUp(); }
		private:
			CWizMultiThreadedWorker& m_rW;
		};
};
/////////////////////////////////////////////////////////////////////////////
// class CWizThreadDispatcher
class CWizThreadDispatcher
{
public:
// Constructors:
	// Usially MaxThreads = (2..5)*NumberOfProcessors
	CWizThreadDispatcher (CWizMultiThreadedWorker &rWorker, int MaxThreads = 5);
// Destructor:
	virtual ~CWizThreadDispatcher ();
public:
// Operations:
	void	Start();	// Starts Dispatching
	void	Stop(BOOL bWait = TRUE); // Signals to stop and (?) waits for all threads to exit
	void	MsgStop (CWnd* pWnd, UINT Message); // Signals to stop all threads, 
												// posts Message to pWnd and exits
	void	WaitShutDown();			 // Waits for all threads to exit after signaling to stop

public:
// Classes 
	// Exceptions the class can throw: (+CMemoryException)
	struct Xeption {};
	struct XCannotCreate : public Xeption {};
	struct XWaitFailed : public Xeption {};
	// Event wrapper
	class Event
	{
	public:
		Event(BOOL bManualReset);
		~Event();
		void	Set();
		HANDLE	m_h;
	};
protected:
	class WorkerThread
	{
	public:
		WorkerThread(CWizMultiThreadedWorker &rWorker, 
				HANDLE hDataReadyEvent,
				HANDLE hStartedTreatEvent,
				HANDLE hShutDownEvent);
		friend UINT AFX_CDECL CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);
	private:
		UINT Run();

		enum { DataWaitHCount = 2 };
		CWizMultiThreadedWorker&	m_rWorker;
		HANDLE	m_hDataWait [DataWaitHCount];
		HANDLE	m_hStartedTreatEvent;
	};
// Implementation:
	friend UINT AFX_CDECL CWizThreadDispatcherFun(LPVOID pParam);
	friend UINT AFX_CDECL CWizThreadDispatcher_WorkerThread_Fun(LPVOID pParam);

// Virtual implementation:
	virtual UINT  Run();
// Data members
	enum { StartedTreatmentEventsCount = 2};

	int							m_nMaxThreads;
	CWizMultiThreadedWorker&	m_rWorker;
	Event						m_ShutDownEvent;
	Event						m_HasDataEvent;
	Event						m_StartedDataTreatEvent;
	HANDLE						m_ahStartedTreatmentEvents[StartedTreatmentEventsCount];
	HANDLE*						m_ahWorkersHandles;
	HANDLE						m_hThisThread;
	CWnd*						m_pWnd;					
	UINT						m_nMessage;
};

/////////////////////////////////////////////////////////////////////////////
inline CWizThreadDispatcher::Event::Event(BOOL bManualReset)
	: m_h (::CreateEvent(NULL, bManualReset, FALSE, NULL))
{
	if (m_h == NULL)
		throw CWizThreadDispatcher::XCannotCreate();
}

inline CWizThreadDispatcher::Event::~Event()
{
	if (m_h != NULL)
		VERIFY(::CloseHandle(m_h));
}

inline void CWizThreadDispatcher::Event::Set()
{
	ASSERT(m_h != NULL);
	SetEvent(m_h); // May fail because is set already
}
///////////////////////////////////////////////////////////////////
#endif // __CWizThreadDispatcher_H


